







#		*Translator Definitions*

#CC = f:\msc\bin\cl386

CC=bcc32

FLAGS =  /c /Ox /G4 -DOPT_LIB -DDOS386 -D__MSC__

TASM = TASM

TLIB = tlib

TLINK = tlink

LIBPATH = D:\BC\LIB;\AUT\FEBCOP\NBS

INCLUDEPATH = D:\BC\INCLUDE;\AUT\FEBCOP;.



.cpp.obj : 

  $(CC) -v -3 -H -Hc -c -f -W $<



.c.obj : 

  $(CC) -v -3 -H -Hc -c -f -Ox $<



#		*List Macros*





EXE1_dependencies =  \

 catage2.obj \

 dvect9.obj \

 dvect7.obj \

 fmm_disp.obj \

 model_mi.obj \

 newmodmn.obj \

 newmodm2.obj \

 newmodm3.obj \

 newmodm4.obj \

 dmat3.obj



#		*Explicit Rules*

newlanal.exe: $(EXE1_dependencies)  $(EXE2_dependencies) 

#  tlink32 /Tpe /v @parfxo.rsp

  tlink32 /m /v /Tpe /S:12000 @parfxo.rsp 



