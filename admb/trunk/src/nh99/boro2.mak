



#		*Translator Definitions*

#CC = f:\msc\bin\cl386

CC=bcc32

FLAGS =  /c /Ox /G4 -DOPT_LIB -DDOS386 -D__MSC__

TASM = TASM

TLIB = tlib

TLINK = tlink

LIBPATH = D:\BC\LIB;\AUT\FEBCOP\NBS

INCLUDEPATH = D:\BC\INCLUDE;\AUT\FEBCOP;.

.SUFFIXES: .cpp .o32



.cpp.o32 : 

	$(CC) -v -Id:\zinc35\include -4 -H -Hc -c -f -W -DOPT_LIB -o$*.o32 $<



.c.o32 : 

	$(CC)  -4 -H -Hc -c -f -Ox -tW -o$*.o32 $<



#		*List Macros*



EXE_dependencies =  \

 t.o32 \

 monte.o32 \

 bet_rand.o32 

#		*Explicit Rules*

newlanal.exe: $(EXE_dependencies) 

#  tlink32 /Tpe /v @parfxo.rsp

	tlink32 /Tpe /v /S:10000 @parfx2.rsp 











