include objects.lst

!IF ([cl /? 2>&1 | findstr /C:"Compiler Version 19." > nul] == 0)
CXXVERSION=-cl19
!ENDIF
!IF ([cl /? 2>&1 | findstr /C:" x64" > nul] == 0)
OSNAME=-vsx64
!ELSEIF ([cl /? 2>&1 | findstr /C:" x86" > nul] == 0)
OSNAME=-vsx86
!ENDIF

!IF DEFINED(DEBUG)
!IF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-vsx64"
OPT=$(OBJECTS: = ..\..\build\objects\vsx64-cl19\contrib-optlp-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\vsx64-cl19\contrib-saflp-statslib-)
!ELSEIF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-vsx86"
OPT=$(OBJECTS: = ..\..\build\objects\vsx86-cl19\contrib-optlp-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\vsx86-cl19\contrib-saflp-statslib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\vs-cl\contrib-optlp-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\vs-cl\contrib-saflp-statslib-)
!ENDIF
!ELSE
!IF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-vsx64"
OPT=$(OBJECTS: = ..\..\build\objects\vsx64-cl19\contrib-optlp-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\vsx64-cl19\contrib-saflp-statslib-)
!ELSEIF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-vsx86"
OPT=$(OBJECTS: = ..\..\build\objects\vsx86-cl19\contrib-optlp-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\vsx86-cl19\contrib-saflp-statslib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\vs-cl\contrib-optlp-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\vs-cl\contrib-saflp-statslib-)
!ENDIF
!ENDIF

!IF DEFINED(SAFE_ONLY)
all: $(SAF)
!ELSE
all: $(OPT) $(SAF)
!ENDIF

$(OPT):: $(@B:contrib-optlp-statslib-=).cpp
	..\..\admb -c -f $?
	copy $(?:.cpp=.obj) $@

$(SAF):: $(@B:contrib-saflp-statslib-=).cpp
	..\..\admb -c $?
	copy $(?:.cpp=.obj) $@

includes: $(HEADERS)
	copy $(HEADERS) $(CONTRIB_INCLUDE)

clean:
	del /Q $(OBJECTS)
