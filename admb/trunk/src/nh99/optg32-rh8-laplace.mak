.PHONY: disk

CFLAGS=-O3
ifdef DEBUG
CFLAGS=-g
endif

ifneq ($(strip $(ADMB_VERSION)),)
  FLAGS+=-DADMB_VERSION=${ADMB_VERSION}
  FLAGS1+=-DADMB_VERSION=${ADMB_VERSION}
endif

ifneq ($(strip $(ADMB_REVISION)),)
  ifneq ('$(strip $(ADMB_REVISION))', 'exported')
    FLAGS+=-DADMB_REVISION=${ADMB_REVISION}
    FLAGS1+=-DADMB_REVISION=${ADMB_REVISION}
  endif
endif

LIBPATH =gcc32-rh8olp
STUBPATH =gcc32-rh8olp-stub
STUBNAME = libdf1b2stub.a
LIBNAME = libadmod.a
SRCDIR =  src
vpath %.obj $(LIBPATH)

.SUFFIXES: .obj .cpp

include objects.lst

all: $(LIBPATH)/$(LIBNAME) tpl2cpp disk  

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj

%.obj: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(LIBPATH)/$*.obj

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
	cp s.h $(DISKDIR)/include
	cp tpl2cpp $(DISKDIR)/bin
	cp sed* $(DISKDIR)/bin
	cp $(STUBPATH)/${STUBNAME} $(DISKDIR)/lib
