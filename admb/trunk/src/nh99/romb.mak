

#AUTODEPEND



#		*Translator Definitions*

CC = bcc32

TASM = TASM32

TLIB = tlib

TLINK = tlink32

#BGI = c:\BC31\BGI

MFPATH=e:\newm94a

ADPATH=h:\linad94x

ZPATH=c:\zinc\source

TPATH=e:\tools94



.cpp.obx:

	$(CC) +BCC32.CFG -H -Hc -v -RT- -x- -N  -c -vi- -w- -DDOS32PP -o$*.obx {$< }



#$(CC) -DOPT_LIB -v -c -d -ml -2 -f287 -vi- -w- -H=ZFE.SYM {$< }



#		*List Macros*



#zfe16.mak \

# $(ZPATH)\i_btcat.o32 \



EXE_dependencies =  \

 qromb.obx \

 testromb.obx 



#		*Explicit Rules*





montest.exe: $(EXE_dependencies)

	$(TLINK) -s -Tpe -ax -v -S:26000 @&&|

c0x32.obj+

qromb.obx \

testromb.obx 

testromb 

testromb.map

e:\tools94\b32o45\adt32.lib+

dpmi32.lib+

bgi32.lib+

cw32.lib+

h:\linad94x\b32o45\ado32.lib,

|



