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
OPT=$(OBJECTS: = ..\..\build\objects-winx64-vc19\debug\contrib-optlp-ecolib-)
SAF=$(OBJECTS: = ..\..\build\objects-winx64-vc19\debug\contrib-saflp-ecolib-)
!ELSEIF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx86"
OPT=$(OBJECTS: = ..\..\build\objects-winx86-vc19\debug\contrib-optlp-ecolib-)
SAF=$(OBJECTS: = ..\..\build\objects-winx86-vc19\debug\contrib-saflp-ecolib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects-win-vc\debug\contrib-optlp-ecolib-)
SAF=$(OBJECTS: = ..\..\build\objects-win-vc\debug\contrib-saflp-ecolib-)
!ENDIF
!ELSE
!IF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx64"
OPT=$(OBJECTS: = ..\..\build\objects-winx64-vc19\dist\contrib-optlp-ecolib-)
SAF=$(OBJECTS: = ..\..\build\objects-winx64-vc19\dist\contrib-saflp-ecolib-)
!ELSEIF "$(CXXVERSION)"=="-vc19" && "$(OSNAME)"=="-winx86"
OPT=$(OBJECTS: = ..\..\build\objects-winx86-vc19\dist\contrib-optlp-ecolib-)
SAF=$(OBJECTS: = ..\..\build\objects-winx86-vc19\dist\contrib-saflp-ecolib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects-win-vc\dist\contrib-optlp-ecolib-)
SAF=$(OBJECTS: = ..\..\build\objects-win-vc\dist\contrib-saflp-ecolib-)
!ENDIF
!ENDIF

!IF DEFINED(SAFE_ONLY)
all: $(SAF)
!ELSE
all: $(OPT) $(SAF)
!ENDIF

$(OPT):: $(@B:contrib-optlp-ecolib-=).cpp
	..\..\admb -c -f $?
	copy $(?:.cpp=.obj) $@

$(SAF):: $(@B:contrib-saflp-ecolib-=).cpp
	..\..\admb -c $?
	copy $(?:.cpp=.obj) $@

includes: $(HEADERS)
	copy $(HEADERS) $(CONTRIB_INCLUDE)

clean:
	del /Q $(OBJECTS)
