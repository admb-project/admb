# path to search for Borland header files and fvar.hpp
INCLUDE = C:\TC\INCLUDE;D:\AUTODIF

# path to search for Borland libraries and autodif.lib
LIB = C:\TC\LIB;D:\AUTODIF\bs

# compiler flags
#         compile only
#         |  large model
#         |  |   floating point processor
#         |  |   |     enable overlays 
#         |  |   |     |
CFLAGS = -c -ml -f287 -v 

# compiler to use
CC = bcc

# linker to use
LL = tlink

# implicit rule
.cpp.obj:
  $(CC) $(CFLAGS) -I$(INCLUDE) {$< }

io_examp.exe: io_examp.obj
  $(LL) /v/x/c/P-/L$(LIB) @&&|
c0l.obj+
io_examp.obj
io_examp
             # leave space for no map file
autodif.lib+
fp87.lib+
mathl.lib+
cl.lib+
|
