include objects.lst

!IF ([cl 2>&1 | findstr " 19" > nul] == 0)
CXXVERSION=-cl19
!ELSE
CXXVERSION=-cl
!ENDIF
!IF ([cl 2>&1 | findstr " x64" > nul] == 0)
OSNAME=-win64
!ELSE
OSNAME=-win32
!ENDIF

!IF DEFINED(DEBUG)
!IF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win64"
OPT=$(OBJECTS: = ..\..\build\objects\win64-cl19-debug\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\win64-cl19-debug\contrib-saflp-qfclib-)
!ELSEIF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win32"
OPT=$(OBJECTS: = ..\..\build\objects\win32-cl19-debug\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\win32-cl19-debug\contrib-saflp-qfclib-)
!ELSEIF "$(CXXVERSION)"=="-cl" && "$(OSNAME)"=="-win64"
OPT=$(OBJECTS: = ..\..\build\objects\win64-cl-debug\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\win64-cl-debug\contrib-saflp-qfclib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\win32-cl-debug\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\win32-cl-debug\contrib-saflp-qfclib-)
!ENDIF
!ELSE
!IF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win64"
OPT=$(OBJECTS: = ..\..\build\objects\win64-cl19\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\win64-cl19\contrib-saflp-qfclib-)
!ELSEIF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win32"
OPT=$(OBJECTS: = ..\..\build\objects\win32-cl19\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\win32-cl19\contrib-saflp-qfclib-)
!ELSEIF "$(CXXVERSION)"=="-cl" && "$(OSNAME)"=="-win64"
OPT=$(OBJECTS: = ..\..\build\objects\win64-cl19\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\win64-cl19\contrib-saflp-qfclib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\win32-cl\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\win32-cl\contrib-saflp-qfclib-)
!ENDIF
!ENDIF

!IF DEFINED(SAFE_ONLY)
all: $(SAF)
!ELSE
all: $(OPT) $(SAF)
!ENDIF

$(OPT):: $(@B:contrib-optlp-qfclib-=).cpp
!IF DEFINED(DEBUG)
	..\..\admb -c -f -o $@ $?
!ELSE
	..\..\admb -c -f -g -o $@ $?
!ENDIF

$(SAF):: $(@B:contrib-saflp-qfclib-=).cpp
!IF DEFINED(DEBUG)
	..\..\admb -c -o $@ $?
!ELSE
	..\..\admb -c -g -o $@ $?
!ENDIF

includes: $(HEADERS)
	copy $(HEADERS) $(CONTRIB_INCLUDE)

clean:
	del /Q $(OBJECTS)
