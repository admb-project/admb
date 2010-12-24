.PHONY: disk tpl2cpp
.SUFFIXES: .obj .cpp

LIBPATH =gcc32-rh8olp
STUBPATH =gcc32-rh8olp-stub
STUBNAME = libdf1b2stub.a
LIBNAME = libadmod.a
vpath %.obj $(LIBPATH)

include objects.lst

ifeq "CC" "$(CXX)"
OBJECTS = $(filter-out dfqromb.obj, $(OBJ0)) $(OBJ1) $(OBJ2) $(OBJ3) 
else
OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
endif

all: disk  

disk: $(DISKDIR)/lib/$(LIBNAME)  $(DISKDIR)/bin/tpl2cpp
	cp admodel.h $(DISKDIR)/include
	cp spcomm.h $(DISKDIR)/include
	cp adsplus.h $(DISKDIR)/include
	cp newredef.h $(DISKDIR)/include
	cp param_init_bounded_number_matrix.h $(DISKDIR)/include
	cp s.h $(DISKDIR)/include
	cp sedflex $(DISKDIR)/bin

$(DISKDIR)/lib/$(LIBNAME): $(OBJECTS) 
	ar -rs $@ $(LIBPATH)/*.obj

df1b2stub:
	$(CXX) $(CXXFLAGS) -o $(STUBPATH)/df1b2stub.o df1b2stub.cpp
	ar -rs $(STUBPATH)/${STUBNAME} $(STUBPATH)/df1b2stub.o

$(DISKDIR)/bin/tpl2cpp:
	$(CC) -Wno-format tpl2cpp.c -o $@

tpl2cpp.c: tpl2cpp.lex
	flex -w tpl2cpp.lex
	sed -f sedflex lex.yy.c > tpl2cpp.c

model7.obj: model7.cpp
ifdef ADMB_CONFIGURE
	$(CXX) -DADMB_CONFIGURE="${ADMB_CONFIGURE}" $(CXXFLAGS) model7.cpp -o $(LIBPATH)/model7.obj
else
	$(CXX) $(CXXFLAGS) model7.cpp -o $(LIBPATH)/model7.obj
endif

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj
