#macros for making safe library for DJGPP
CC = gcc
LL = tlib
FLAGS =  -I. -I /c/nlinad94 -x c++ -O3 -c -o $(LIBPATH)/$*.obj -D __GNUDOS__ -D OPT_LIB 
LIBPATH = /dave/ntools/gcco
LIBNAME = libadt.a

.SUFFIXES: .obj .cpp .CPP
vpath %.obj $(LIBPATH)$
vpath %.cpp /c/tools94

include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj


$(OBJ0): %.obj: %.cpp
	$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<


