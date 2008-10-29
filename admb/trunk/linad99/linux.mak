#macros for making safe library for DJGPP
CC = gcc
LL = tlib
FLAGS = -funroll-loops -m486 -I . -I /c/nlinad94 -I /c/ntools -x c++ -O3 -c -o $(LIBPATH)/$*.obj -D __GNUDOS__ -D OPT_LIB 
LIBPATH = /dave/nh94/gcco_unroll
SRCPATH = /c/nh94
LIBNAME = libadmod.a

.SUFFIXES: .obj .cpp .CPP
vpath %.obj $(LIBPATH)$
vpath %.cpp /nh94

include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj


$(OBJ0): %.obj: $(SRCPATH)/%.cpp
	$(CC) $(FLAGS)  $<
#$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<




