include objects.lst

!IF ([cl /? 2>&1 | findstr /C:"Compiler Version 19." > nul] == 0)
CXXVERSION=-cl19
!ENDIF
!IF ([cl /? 2>&1 | findstr /C:" x64" > nul] == 0)
OSNAME=-win64
!ELSEIF ([cl /? 2>&1 | findstr /C:" x86" > nul] == 0)
OSNAME=-win32
!ENDIF

!IF DEFINED(DEBUG)
!IF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win64"
OPT=$(OBJECTS: = ..\..\build\objects\win64-cl19-debug\contrib-optlp-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\win64-cl19-debug\contrib-saflp-statslib-)
!ELSEIF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win32"
OPT=$(OBJECTS: = ..\..\build\objects\win32-cl19-debug\contrib-optlp-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\win32-cl19-debug\contrib-saflp-statslib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\win-cl-debug\contrib-optlp-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\win-cl-debug\contrib-saflp-statslib-)
!ENDIF
!ELSE
!IF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win64"
OPT=$(OBJECTS: = ..\..\build\objects\win64-cl19\contrib-optlp-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\win64-cl19\contrib-saflp-statslib-)
!ELSEIF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win32"
OPT=$(OBJECTS: = ..\..\build\objects\win32-cl19\contrib-optlp-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\win32-cl19\contrib-saflp-statslib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\win-cl\contrib-optlp-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\win-cl\contrib-saflp-statslib-)
!ENDIF
!ENDIF

!IF DEFINED(SAFE_ONLY)
all: $(SAF)
!ELSE
all: $(OPT) $(SAF)
!ENDIF

$(OPT):: $(@B:contrib-optlp-statslib-=).cpp
!IF DEFINED(DEBUG)
	..\..\admb -c -f $?
!ELSE
	..\..\admb -c -f -g $?
!ENDIF

	copy $(?:.cpp=.obj) $@

$(SAF):: $(@B:contrib-saflp-statslib-=).cpp
!IF DEFINED(DEBUG)
	..\..\admb -c $?
!ELSE
	..\..\admb -c -g $?
!ENDIF
	copy $(?:.cpp=.obj) $@


includes: $(HEADERS)
	copy $(HEADERS) $(CONTRIB_INCLUDE)

clean:
	del /Q $(OBJECTS)
