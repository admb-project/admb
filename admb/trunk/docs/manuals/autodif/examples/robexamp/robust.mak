.AUTODEPEND

#		*Translator Definitions*
CC = bcc +ROBUST.CFG
TASM = TASM
TLINK = tlink


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
  robust.obj \
  rob_reg.obj \
  fcomp_r.obj \
  autodif.lib

#		*Explicit Rules*
robust.exe: robust.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/LC:\TC\LIB;D:\AUTODIF\BS @&&|
c0l.obj+
robust.obj+
rob_reg.obj+
fcomp_r.obj
robust
		# no map file
autodif.lib+
fp87.lib+
mathl.lib+
cl.lib+
graphics.lib
|


#		*Individual File Dependencies*
robust.obj: robust.cpp 

rob_reg.obj: rob_reg.cpp 

fcomp_r.obj: fcomp_r.cpp 

#		*Compiler Configuration File*
robust.cfg: robust.mak
  copy &&|
-ml
-f287
-v
-IC:\TC\INCLUDE;D:\AUTODIF
-LC:\TC\LIB;D:\AUTODIF\BS
| robust.cfg


