# makefile for AUTODIF examples using Borland compiler and make utility
# change the definitions of these macros to suit your system

# path to search for Borland header files and fvar.hpp
INCLUDE = C:\TC\INCLUDE;\AUTODIF\INCLUDE

# path to search for Borland libraries and AUTODIF libraries
LIB = C:\TC\LIB;\AUTODIF\LIB

# compiler flags
#         compile only
#         |  large model
#         |  |   floating point processor
#         |  |   |     enable overlays 
#         |  |   |     |  disable warnings
#         |  |   |     |  |
CFLAGS = -c -ml -f287 -v -w-

# compiler to use
CC = bcc

# linker to use
LL = tlink

# autodif library to use
LIBRARY = ade.lib

# rule to make all examples
all: simple.exe hemholtz.exe minimize.exe newt.exe io_examp.exe mixture.exe \
     normsim.exe robust.exe robsim.exe winit.exe neur1.exe nplot2.exe

# rules for individual executables
io_examp.exe: io_examp.obj
  $(LL) /v/x/c/P-/L$(LIB) @&&|
c0l.obj+
io_examp.obj
io_examp
             # leave space for no map file
$(LIBRARY)+
fp87.lib+
mathl.lib+
cl.lib+
|

mixture.exe: mixture.h mixture.obj fcomp_m.obj like.obj normaliz.obj \
  nvarcal.obj reset.obj savepar.obj xinit.obj 
  $(LL) /v/x/c/P-/L$(LIB) @&&|
c0l.obj+
mixture.obj+
fcomp_m.obj+
like.obj+
normaliz.obj+
nvarcal.obj+
reset.obj+
savepar.obj+
xinit.obj
mixture
		# no map file
$(LIBRARY)+
fp87.lib+
mathl.lib+
cl.lib+
graphics.lib
|

normsim.exe: normsim.obj
  $(LL) /v/x/c/P-/L$(LIB) @&&|
c0l.obj+
normsim.obj
normsim
             # leave space for no map file
$(LIBRARY)+
fp87.lib+
mathl.lib+
cl.lib+
|

hemholtz.exe: hemholtz.obj hem_func.obj 
  $(LL) /v/x/c/P-/L$(LIB) @&&|
c0l.obj+
hemholtz.obj +
hem_func.obj
hemholtz
             # leave space for no map file
$(LIBRARY)+
fp87.lib+
mathl.lib+
cl.lib+
|

minimize.exe: minimize.obj userfun.obj 
  $(LL) /v/x/c/P-/L$(LIB) @&&|
c0l.obj+
minimize.obj +
userfun.obj
minimize
             # leave space for no map file
$(LIBRARY)+
fp87.lib+
mathl.lib+
cl.lib+
|

newt.exe: newt.obj
  $(LL) /v/x/c/P-/L$(LIB) @&&|
c0l.obj+
newt.obj
newt
             # leave space for no map file
$(LIBRARY)+
fp87.lib+
mathl.lib+
cl.lib+
|

simple.exe: simple.obj fcomp_s.obj 
  $(LL) /v/x/c/P-/L$(LIB) @&&|
c0l.obj+
simple.obj +
fcomp_s.obj 
simple
             # leave space for no map file
$(LIBRARY)+
fp87.lib+
mathl.lib+
cl.lib+
|

robust.exe: robust.obj rob_reg.obj fcomp_r.obj
  $(LL) /v/x/c/P-/L$(LIB) @&&|
c0l.obj+
robust.obj+
rob_reg.obj+
fcomp_r.obj
robust
		# no map file
$(LIBRARY)+
fp87.lib+
mathl.lib+
cl.lib+
|

robsim.exe: robsim.obj
  $(LL) /v/x/c/P-/L$(LIB) @&&|
c0l.obj+
robsim.obj
robsim
		# no map file
$(LIBRARY)+
fp87.lib+
mathl.lib+
cl.lib+
|

neur1.exe: neur1.obj
  $(LL) /v/x/c/P-/L$(LIB) @&&|
c0l.obj+
neur1.obj
neur1
		# no map file
$(LIBRARY)+
fp87.lib+
mathl.lib+
cl.lib+
|

nplot2.exe: nplot2.obj
  $(LL) /v/x/c/P-/L$(LIB) @&&|
c0l.obj+
nplot2.obj
nplot2
		# no map file
$(LIBRARY)+
fp87.lib+
mathl.lib+
cl.lib+
graphics.lib
|

winit.exe: winit.obj
  $(LL) /v/x/c/P-/L$(LIB) @&&|
c0l.obj+
winit.obj
winit
		# no map file
$(LIBRARY)+
fp87.lib+
mathl.lib+
cl.lib+
|

# implicit rule
.cpp.obj:
  $(CC) $(CFLAGS) -I$(INCLUDE) {$< }

