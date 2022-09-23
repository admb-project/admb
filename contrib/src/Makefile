include objects.lst

!IF ([cl 2>&1 | findstr /C:" 19." > nul] == 0)
CXXVERSION=-cl19
!ELSE
CXXVERSION=-cl
!ENDIF
!IF ([cl 2>&1 | findstr /C:" x64" > nul] == 0)
OSNAME=-win64
!ELSE
OSNAME=-win32
!ENDIF

!IF DEFINED(DEBUG)
!IF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win64"
OPT=$(OBJECTS: = ..\..\build\objects\win64-cl19-debug\contrib-optlp-src-)
SAF=$(OBJECTS: = ..\..\build\objects\win64-cl19-debug\contrib-saflp-src-)
!ELSEIF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win32"
OPT=$(OBJECTS: = ..\..\build\objects\win32-cl19-debug\contrib-optlp-src-)
SAF=$(OBJECTS: = ..\..\build\objects\win32-cl19-debug\contrib-saflp-src-)
!ELSEIF "$(CXXVERSION)"=="-cl" && "$(OSNAME)"=="-win64"
OPT=$(OBJECTS: = ..\..\build\objects\win64-cl-debug\contrib-optlp-src-)
SAF=$(OBJECTS: = ..\..\build\objects\win64-cl-debug\contrib-saflp-src-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\win32-cl-debug\contrib-optlp-src-)
SAF=$(OBJECTS: = ..\..\build\objects\win32-cl-debug\contrib-saflp-src-)
!ENDIF
!ELSE
!IF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win64"
OPT=$(OBJECTS: = ..\..\build\objects\win64-cl19\contrib-optlp-src-)
SAF=$(OBJECTS: = ..\..\build\objects\win64-cl19\contrib-saflp-src-)
!ELSEIF "$(CXXVERSION)"=="-cl19" && "$(OSNAME)"=="-win32"
OPT=$(OBJECTS: = ..\..\build\objects\win32-cl19\contrib-optlp-src-)
SAF=$(OBJECTS: = ..\..\build\objects\win32-cl19\contrib-saflp-src-)
!ELSEIF "$(CXXVERSION)"=="-cl" && "$(OSNAME)"=="-win64"
OPT=$(OBJECTS: = ..\..\build\objects\win64-cl\contrib-optlp-src-)
SAF=$(OBJECTS: = ..\..\build\objects\win64-cl\contrib-saflp-src-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\win32-cl\contrib-optlp-src-)
SAF=$(OBJECTS: = ..\..\build\objects\win32-cl\contrib-saflp-src-)
!ENDIF
!ENDIF

!IF DEFINED(SAFE_ONLY)
all: $(SAF)
!ELSE
all: $(OPT) $(SAF)
!ENDIF

$(OPT):: $(@B:contrib-optlp-src-=).cpp
!IF DEFINED(DEBUG)
	..\..\admb -c -f -o $@ $?
!ELSE
	..\..\admb -c -f -g -o $@ $?
!ENDIF

$(SAF):: $(@B:contrib-saflp-src-=).cpp
!IF DEFINED(DEBUG)
	..\..\admb -c -o $@ $?
!ELSE
	..\..\admb -c -g -o $@ $?
!ENDIF

includes: $(HEADERS)
	copy $(HEADERS) $(CONTRIB_INCLUDE)

clean:
	del /Q $(OBJECTS)
