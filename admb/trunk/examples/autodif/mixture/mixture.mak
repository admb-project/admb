.AUTODEPEND

#		*Translator Definitions*
CC = bcc +MIXTURE.CFG
TASM = TASM
TLINK = tlink


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*


EXE_dependencies =  \
  mixture.obj \
  fcomp.obj \
  like.obj \
  normaliz.obj \
  nvarcal.obj \
  reset.obj \
  savepar.obj \
  xinit.obj \
  autodif.lib

#		*Explicit Rules*
mixture.exe: mixture.cfg $(EXE_dependencies)
  $(TLINK) /v/x/c/P-/LC:\TC\LIB;D:\AUTODIF\BS @&&|
c0l.obj+
mixture.obj+
fcomp.obj+
like.obj+
normaliz.obj+
nvarcal.obj+
reset.obj+
savepar.obj+
xinit.obj
mixture
		# no map file
autodif.lib+
fp87.lib+
mathl.lib+
cl.lib+
graphics.lib
|


#		*Individual File Dependencies*
mixture.obj: mixture.cpp 

fcomp.obj: fcomp.cpp 

like.obj: like.cpp 

normaliz.obj: normaliz.cpp 

nvarcal.obj: nvarcal.cpp 

reset.obj: reset.cpp 

savepar.obj: savepar.cpp 

xinit.obj: xinit.cpp 

#		*Compiler Configuration File*
mixture.cfg: mixture.mak
  copy &&|
-ml
-2
-f287
-N
-v
-H=MIXTURE.SYM
-IC:\TC\INCLUDE;.;D:\AUTODIF
-LC:\TC\LIB;D:\AUTODIF\BS
| mixture.cfg


