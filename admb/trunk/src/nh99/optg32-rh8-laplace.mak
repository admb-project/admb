.PHONY: disk

LIBPATH =gcc32-rh8olp
STUBPATH =gcc32-rh8olp-stub
STUBNAME = libdf1b2stub.a
LIBNAME = libadmod.a
SRCDIR =  src
vpath %.obj $(LIBPATH)

.SUFFIXES: .obj .cpp

include objects.lst

all: $(LIBPATH)/$(LIBNAME) tpl2cpp disk  


ifeq "CC" "$(CXX)"
OBJECTS = $(filter-out dfqromb.obj, $(OBJ0)) $(OBJ1) $(OBJ2) $(OBJ3) 
else
OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
endif

$(LIBPATH)/$(LIBNAME) :  $(OBJECTS) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

evalxtrn.obj: evalxtrn.cpp
	$(CXX) -O3 $(CXXFLAGS) evalxtrn.cpp -o $(LIBPATH)/$*.obj

model7.obj: model7.cpp
	$(CXX) -DADMB_CONFIGURE="${ADMB_CONFIGURE}" -O3 $(CXXFLAGS) model7.cpp -o $(LIBPATH)/model7.obj

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj

all: $(LIBPATH)/$(LIBNAME)  tpl2cpp disk  

df1b2stub:
	$(CXX) $(CXXFLAGS) -o $(STUBPATH)/df1b2stub.o df1b2stub.cpp
	ar -rs $(STUBPATH)/${STUBNAME} $(STUBPATH)/df1b2stub.o

tpl2cpp.c: tpl2cpp.lex
	flex -w tpl2cpp.lex
	sed -f sedflex lex.yy.c > tpl2cpp.c

tpl2cpp: tpl2cpp.c
	$(CC) -Wno-format tpl2cpp.c -o $@

disk: $(LIBPATH)/$(LIBNAME)  df1b2stub tpl2cpp
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/lib
	cp admodel.h $(DISKDIR)/include
	cp spcomm.h $(DISKDIR)/include
	cp adsplus.h $(DISKDIR)/include
	cp newredef.h $(DISKDIR)/include
	cp param_init_bounded_number_matrix.h $(DISKDIR)/include
	cp s.h $(DISKDIR)/include
	cp tpl2cpp $(DISKDIR)/bin
	cp sed* $(DISKDIR)/bin
	cp $(STUBPATH)/${STUBNAME} $(DISKDIR)/lib
