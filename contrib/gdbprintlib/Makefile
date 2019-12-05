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
OPT=$(OBJECTS: = ..\..\build\objects\debug-vsx64-cl19\contrib-optlp-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects\debug-vsx64-cl19\contrib-saflp-gdbprintlib-)
!ELSEIF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-vsx86"
OPT=$(OBJECTS: = ..\..\build\objects\debug-vsx86-cl19\contrib-optlp-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects\debug-vsx86-cl19\contrib-saflp-gdbprintlib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\debug-vs-cl\contrib-optlp-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects\debug-vs-cl\contrib-saflp-gdbprintlib-)
!ENDIF
!ELSE
!IF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-vsx64"
OPT=$(OBJECTS: = ..\..\build\objects\dist-vsx64-cl19\contrib-optlp-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects\dist-vsx64-cl19\contrib-saflp-gdbprintlib-)
!ELSEIF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-vsx86"
OPT=$(OBJECTS: = ..\..\build\objects\dist-vsx86-cl19\contrib-optlp-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects\dist-vsx86-cl19\contrib-saflp-gdbprintlib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\dist-vs-cl\contrib-optlp-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects\dist-vs-cl\contrib-saflp-gdbprintlib-)
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
