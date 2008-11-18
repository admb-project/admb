# makefile for AUTODIF examples using Zortech compiler and make utility
# change the definitions of these macros to suit your system

# path to search for Zortech header files and fvar.hpp
INCLUDE = C:\ZOR\INCLUDE;\AUTODIF\INCLUDE

# path to search for AUTODIF libraries
LIB = \AUTODIF\LIB

# compiler flags
#         compile only
#         |   32 bit DOS extended memory model
#         |   |  surpress warnings
#         |   |  |
CFLAGS = -c -mx -w

# compiler to use
CC = ztc 

# linker command to use for DOSX version
LL = ztc -mx

# linker command to use for large model version
#LL = ztc -ml

# autodif library to use
LIBRARY = adx7.lib

# rule to make all examples
all: simple.exe hemholtz.exe minimize.exe newt.exe io_examp.exe mixture.exe \
     normsim.exe robust.exe robsim.exe winit.exe neur1.exe bigmin.exe

# rules for individual executables
io_examp.exe: io_examp.obj
  $(LL) io_examp.obj $(LIB)\$(LIBRARY)

mixture.exe: mixture.h mixture.obj fcomp_m.obj like.obj normaliz.obj \
  nvarcal.obj reset.obj savepar.obj xinit.obj 
  $(LL) mixture.obj fcomp_m.obj like.obj normaliz.obj nvarcal.obj \
  reset.obj savepar.obj xinit.obj $(LIB)\$(LIBRARY)

normsim.exe: normsim.obj
  $(LL) normsim.obj $(LIB)\$(LIBRARY)
 
hemholtz.exe: hemholtz.obj hem_func.obj 
  $(LL) hemholtz.obj hem_func.obj $(LIB)\$(LIBRARY)
 
minimize.exe: minimize.obj userfun.obj 
  $(LL) minimize.obj userfun.obj $(LIB)\$(LIBRARY)
 
newt.exe: newt.obj
  $(LL) newt.obj $(LIB)\$(LIBRARY)

simple.exe: simple.obj fcomp_s.obj 
  $(LL) simple.obj fcomp_s.obj $(LIB)\$(LIBRARY)

robust.exe: robust.obj rob_reg.obj fcomp_r.obj
  $(LL) robust.obj rob_reg.obj fcomp_r.obj $(LIB)\$(LIBRARY)

robsim.exe: robsim.obj
  $(LL) robsim.obj $(LIB)\$(LIBRARY)

neur1.exe: neur1.obj
  $(LL) neur1.obj $(LIB)\$(LIBRARY)

winit.exe: winit.obj
  $(LL) winit.obj $(LIB)\$(LIBRARY)

bigmin.exe: bigmin.obj
  ztc -mx bigmin.obj $(LIB)\autdifx7.lib

bigmin.obj: bigmin.cpp
  $(CC)   -c -mx -w- -I$(INCLUDE) bigmin.cpp 

# implicit rule
.cpp.obj:
  $(CC) $(CFLAGS) -I$(INCLUDE) $< 
