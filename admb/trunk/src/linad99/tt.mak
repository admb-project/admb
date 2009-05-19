

#macros for making safe library for DJGPP
CC = gcc
LL = tlib
FLAGS = -I . -I/c/h94 -I /c/linad94x -I /c/tools94 -x c++ -O3 -S -o $(LIBPATH)/$*.s -D __GNUDOS__ -D OPT_LIB -D UX
LIBPATH = .
SRCPATH = /c/h94
LIBNAME = libadmod.a

.SUFFIXES: .obj .cpp .CPP
vpath %.obj $(LIBPATH)$
vpath %.cpp /c/h94

include objects.lst

$(LIBPATH)/$(LIBNAME) :  $(OBJ0) 
	ar -rs $(LIBPATH)/$(LIBNAME) $(LIBPATH)/*.obj


$(OBJ0): %.obj: $(SRCPATH)/%.cpp
	$(CC) $(FLAGS)  $<
#$(CC) $(FLAGS) -o$(LIBPATH)/$*.obj $<




