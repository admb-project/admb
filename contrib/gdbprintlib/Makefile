include objects.lst

!IF ([cl /? 2>&1 | findstr /C:"Compiler Version 19." > nul] == 0)
CXXVERSION=-vc19
!ENDIF
!IF ([cl /? 2>&1 | findstr /C:" x64" > nul] == 0)
OSNAME=-winx64
!ELSEIF ([cl /? 2>&1 | findstr /C:" x86" > nul] == 0)
OSNAME=-winx86
!ENDIF

!IF DEFINED(DEBUG)
!IF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx64"
OPT=$(OBJECTS: = ..\..\build\objects-winx64-vc19\debug\contrib-optlp-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects-winx64-vc19\debug\contrib-saflp-gdbprintlib-)
!ELSEIF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx86"
OPT=$(OBJECTS: = ..\..\build\objects-winx86-vc19\debug\contrib-optlp-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects-winx86-vc19\debug\contrib-saflp-gdbprintlib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects-win-vc\debug\contrib-optlp-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects-win-vc\debug\contrib-saflp-gdbprintlib-)
!ENDIF
!ELSE
!IF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx64"
OPT=$(OBJECTS: = ..\..\build\objects-winx64-vc19\dist\contrib-optlp-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects-winx64-vc19\dist\contrib-saflp-gdbprintlib-)
!ELSEIF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx86"
OPT=$(OBJECTS: = ..\..\build\objects-winx86-vc19\dist\contrib-optlp-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects-winx86-vc19\dist\contrib-saflp-gdbprintlib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects-win-vc\dist\contrib-optlp-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects-win-vc\dist\contrib-saflp-gdbprintlib-)
!ENDIF
!ENDIF

!IF DEFINED(SAFE_ONLY)
all: $(SAF)
!ELSE
all: $(OPT) $(SAF)
!ENDIf

$(OPT):: $(@B:contrib-optlp-gdbprintlib-=).cpp
	..\..\admb -c -f $?
	copy $(?:.cpp=.obj) $@

$(SAF):: $(@B:contrib-saflp-gdbprintlib-=).cpp
	..\..\admb -c $?
	copy $(?:.cpp=.obj) $@

includes: $(HEADERS)
	for %%a in ($(HEADERS)) do copy %%a $(CONTRIB_INCLUDE)

clean:
	del /Q $(OBJECTS)
