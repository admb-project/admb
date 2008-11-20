.AUTODEPEND

#		*Translator Definitions*
CC = bcc +ROBSIM.CFG
TASM = TASM
TLINK = tlink


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
  robsim.obj \
  autodif.lib

#		*Explicit Rules*
robsim.exe: robsim.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/LC:\TC\LIB;D:\AUTODIF\BS @&&|
c0l.obj+
robsim.obj
robsim
		# no map file
autodif.lib+
fp87.lib+
mathl.lib+
cl.lib+
graphics.lib
|


#		*Individual File Dependencies*
robsim.obj: robsim.cpp 

#		*Compiler Configuration File*
robsim.cfg: robsim.mak
  copy &&|
-ml
-2
-f287
-N
-v
-H=ROBSIM.SYM
-IC:\TC\INCLUDE;.;D:\AUTODIF
-LC:\TC\LIB;D:\AUTODIF\BS
| robsim.cfg


