.AUTODEPEND

#		*Translator Definitions*
CC = bcc +NEUR1.CFG
TASM = TASM
TLINK = tlink


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
  neur1.obj \
  autodif.lib

#		*Explicit Rules*
neur1.exe: neur1.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/LC:\TC\LIB;D:\AUTODIF\BS @&&|
c0l.obj+
neur1.obj
neur1
		# no map file
autodif.lib+
fp87.lib+
mathl.lib+
cl.lib+
graphics.lib
|


#		*Individual File Dependencies*
neur1.obj: neur1.cpp 

#		*Compiler Configuration File*
neur1.cfg: neur1.mak
  copy &&|
-ml
-1
-f287
-v
-H=NEUR1.SYM
-IC:\TC\INCLUDE;D:\AUTODIF
-LC:\TC\LIB;D:\AUTODIF\BS
| neur1.cfg


