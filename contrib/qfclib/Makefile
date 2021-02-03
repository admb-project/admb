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
OPT=$(OBJECTS: = ..\..\build\objects\win64-cl19-debug\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\win64-cl19-debug\contrib-saflp-qfclib-)
!ELSEIF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win32"
OPT=$(OBJECTS: = ..\..\build\objects\win32-cl19-debug\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\win32-cl19-debug\contrib-saflp-qfclib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\win-cl-debug\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\win-cl-debug\contrib-saflp-qfclib-)
!ENDIF
!ELSE
!IF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win64"
OPT=$(OBJECTS: = ..\..\build\objects\win64-cl19\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\win64-cl19\contrib-saflp-qfclib-)
!ELSEIF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win32"
OPT=$(OBJECTS: = ..\..\build\objects\win32-cl19\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\win32-cl19\contrib-saflp-qfclib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\win-cl\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\win-cl\contrib-saflp-qfclib-)
!ENDIF
!ENDIF

!IF DEFINED(SAFE_ONLY)
all: $(SAF)
!ELSE
all: $(OPT) $(SAF)
!ENDIF

$(OPT):: $(@B:contrib-optlp-qfclib-=).cpp
!IF DEFINED(DEBUG)
	..\..\admb -c -f $?
!ELSE
	..\..\admb -c -f -g $?
!ENDIF
	copy $(?:.cpp=.obj) $@

$(SAF):: $(@B:contrib-saflp-qfclib-=).cpp
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
