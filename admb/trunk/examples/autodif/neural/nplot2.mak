.AUTODEPEND

#		*Translator Definitions*
CC = bcc +NPLOT2.CFG
TASM = TASM
TLINK = tlink


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
  nplot2.obj \
  autodif.lib

#		*Explicit Rules*
nplot2.exe: nplot2.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/LC:\TC\LIB;D:\AUTODIF\BS @&&|
c0l.obj+
nplot2.obj
nplot2
		# no map file
autodif.lib+
fp87.lib+
mathl.lib+
cl.lib+
graphics.lib
|


#		*Individual File Dependencies*
nplot2.obj: nplot2.cpp 

#		*Compiler Configuration File*
nplot2.cfg: nplot2.mak
  copy &&|
-ml
-1
-f287
-N
-v
-H=NPLOT2.SYM
-wpin
-wcln
-wdef
-wsig
-wucp
-IC:\TC\INCLUDE;D:\AUTODIF
-LC:\TC\LIB;D:\AUTODIF\BS
-P.CPP
| nplot2.cfg


