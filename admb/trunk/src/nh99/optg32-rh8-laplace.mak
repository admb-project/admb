.PHONY: disk tpl2cpp

LIBPATH =gcc32-rh8olp
STUBPATH =gcc32-rh8olp-stub
STUBNAME = libdf1b2stub.a
LIBNAME = libadmod.a
SRCDIR =  src
vpath %.obj $(LIBPATH)

.SUFFIXES: .obj .cpp

include objects.lst

all: $(LIBNAME) tpl2cpp disk  


ifeq "CC" "$(CXX)"
OBJECTS = $(filter-out dfqromb.obj, $(OBJ0)) $(OBJ1) $(OBJ2) $(OBJ3) 
else
OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
endif

$(LIBNAME) :  $(OBJECTS) 
	ar -rs $(LIBNAME) $(LIBPATH)/*.obj

model7.obj: model7.cpp
ifdef ADMB_CONFIGURE
	$(CXX) -DADMB_CONFIGURE="${ADMB_CONFIGURE}" $(CXXFLAGS) model7.cpp -o $(LIBPATH)/model7.obj
else
	$(CXX) $(CXXFLAGS) model7.cpp -o $(LIBPATH)/model7.obj
endif

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj

all: $(LIBNAME)  tpl2cpp disk  

df1b2stub:
	$(CXX) $(CXXFLAGS) -o $(STUBPATH)/df1b2stub.o df1b2stub.cpp
	ar -rs $(STUBPATH)/${STUBNAME} $(STUBPATH)/df1b2stub.o

tpl2cpp.c: tpl2cpp.lex
	flex -w tpl2cpp.lex
	sed -f sedflex lex.yy.c > tpl2cpp.c

tpl2cpp:
	$(CC) -Wno-format tpl2cpp.c -o $@

disk: $(LIBNAME)  df1b2stub tpl2cpp
	cp $(LIBNAME) $(DISKDIR)/lib
	cp admodel.h $(DISKDIR)/include
	cp spcomm.h $(DISKDIR)/include
	cp adsplus.h $(DISKDIR)/include
	cp newredef.h $(DISKDIR)/include
	cp param_init_bounded_number_matrix.h $(DISKDIR)/include
	cp s.h $(DISKDIR)/include
	cp tpl2cpp $(DISKDIR)/bin
	cp sedflex $(DISKDIR)/bin
	cp $(STUBPATH)/${STUBNAME} $(DISKDIR)/lib
