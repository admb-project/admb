.AUTODEPEND

#		*Translator Definitions*
CC = bcc +IO_EXAMP.CFG
TASM = TASM
TLINK = tlink


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
  io_examp.obj \
  bs\autodif.lib

#		*Explicit Rules*
io_examp.exe: io_examp.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/LC:\TC\LIB @&&|
c0l.obj+
io_examp.obj
io_examp
		# no map file
\autodif\bs\autodif.lib+
fp87.lib+
mathl.lib+
cl.lib+
graphics.lib
|


#		*Individual File Dependencies*
io_examp.obj: io_examp.cpp 

#		*Compiler Configuration File*
io_examp.cfg: io_examp.mak
  copy &&|
-ml
-1
-f287
-v
-H=IO_EXAMP.SYM
-I.;C:\TC\INCLUDE
-LC:\TC\LIB
| io_examp.cfg


