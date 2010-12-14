


#macros for making optimized library for MS         
SHELL=sh
CC = cl
LL = tlib
LIBPATH = msc8olp
FLAGS = /nologo /W4 /wd4258 /wd4068 /wd4389 /wd4288 /wd4505 /wd4700 /wd4701 /wd4018 /wd4101 /wd4189 /wd4102 /wd4189 /wd4702 /wd4512 /wd4511 /wd4005 /wd4717 /wd4239 /wd4238 /wd4100 /wd4996 /wd4127 /wd4244 /wd4190 /wd4099 ${OPTIONS} ${PVMOPTION}  -DUSE_LAPLACE -DWIN32 /c -I. -I../df1b2-separable -I../nh99 -I../tools99 -D__MSVC32__=8  -DOPT_LIB /Ox /EHsc
FLAGS1 = /nologo /W4 /wd4258 /wd4068 /wd4389 /wd4288 /wd4505 /wd4700 /wd4701 /wd4018 /wd4101 /wd4189 /wd4102 /wd4189 /wd4702 /wd4512 /wd4511 /wd4005 /wd4717 /wd4239 /wd4238 /wd4100 /wd4996 /wd4127 /wd4244 /wd4190 /wd4099 ${OPTIONS} ${PVMOPTION} /GF -I../nh99 -DWIN32 /c /EHsc -I. -D__MSVC32__=8  -DOPT_LIB /Ox -I../df1b2-separable -I../tools99
LIBNAME = ado32.lib 
LIBRARIAN = tlib
DRIVECHANGE=
#DRIVECHANGE=g.bat
SRCDIR =  src
LIBDIR =  lib
INCLUDEDIR = include 

.SUFFIXES: .obj .cpp
vpath %.obj $(LIBPATH)$

include objects.lst

OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)  $(OBJSPARSE) 
$(LIBPATH)/$(LIBNAME) : $(OBJECTS)
	rm $(LIBPATH)/t.rsp ; \
	echo /OUT:$(LIBNAME)  > $(LIBPATH)/t.rsp ; \
	cd $(LIBPATH); \
	ls hs_sparse.obj $(filter-out cnorlogmix.obj ad_atlas.obj d3arr11.obj dmat_acc.obj dmat32.obj dmat8.obj dvec_acc.obj dvect21.obj f3arr12.obj f3arr18.obj imat2.obj imat1.obj fvar_m48.obj model49.obj lmat2.obj lmat1.obj i3arr1.obj fvma_acc.obj fvar_ma8.obj f3arr19.obj fvar_a52.obj ../sparse/hs_sparse.obj, $(OBJECTS) ) >> t.rsp ; \
	lib /NOLOGO @t.rsp ; 
	cd ..

$(OBJSPARSE): %.obj: %.cpp
	$(CC) $(FLAGS) /Fo$(LIBPATH)/$(@F) $<

$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.obj $(LIBPATH)       

$(OBJ1): %.obj: %.cpp
	$(CC) $(FLAGS)  $<
	mv $*.obj $(LIBPATH)       

$(OBJ2): %.obj: %.cpp
	$(CC) $(FLAGS) $<
	mv $*.obj $(LIBPATH)       

$(OBJ3): %.obj: %.cpp
	$(CC) $(FLAGS1) $<
	mv $*.obj $(LIBPATH)       

all: $(LIBPATH)/$(LIBNAME) disk

disk: 
	cp $(LIBPATH)/$(LIBNAME) $(DISKDIR)/$(LIBDIR)  ; \
	cp insx001.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx001a.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx002.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx003.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx004.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx005.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx005a.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx006.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx007.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx008.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx009.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx010.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx011.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx012.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx013.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx014.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx015.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx016.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx017.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp insx018.h $(DISKDIR)/$(INCLUDEDIR) ; \
	cp fvar.hpp $(DISKDIR)/$(INCLUDEDIR) ; \
	cp d4arr.hpp $(DISKDIR)/$(INCLUDEDIR) ; \
	cp dfpool.h  $(DISKDIR)/$(INCLUDEDIR) ; \
	cd $(DISKDIR) 
clean:
	- cd $(LIBPATH) ; rm *.obj ; rm *.lib ; rm *.o ; rm *.a
