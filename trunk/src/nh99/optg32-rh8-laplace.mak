.PHONY: disk
.SUFFIXES: .obj .cpp

LIBPATH =gcc32-rh8olp
LIBNAME = libadmod.a
vpath %.obj $(LIBPATH)

include objects.lst

ifeq ("$(CXX)","CC")
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

$(DISKDIR)/lib/$(LIBNAME): $(OBJECTS)
	ar -rs $@ $(LIBPATH)/*.obj

$(DISKDIR)/bin/tpl2cpp: tpl2cpp.c
ifeq ("$(CC)","cc")
	$(CC) -o $@ $<
else
	$(CC) -Wno-format -o $@ $<
endif

tpl2cpp.c: tpl2cpp.lex
	flex -w $<
	sed -f sedflex lex.yy.c > $@

model7.obj: model7.cpp
ifdef ADMB_CONFIGURE
	$(CXX) -DADMB_CONFIGURE="${ADMB_CONFIGURE}" $(CXXFLAGS) model7.cpp -o $(LIBPATH)/model7.obj
else
	$(CXX) $(CXXFLAGS) model7.cpp -o $(LIBPATH)/model7.obj
endif

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj
