include objects.lst

!IF DEFINED(DEBUG)
OPT=$(OBJECTS: = ..\..\build\objects\debug\contrib-optlp-src-)
SAF=$(OBJECTS: = ..\..\build\objects\debug\contrib-saflp-src-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\dist\contrib-optlp-src-)
SAF=$(OBJECTS: = ..\..\build\objects\dist\contrib-saflp-src-)
!ENDIF

!IF DEFINED(COVERAGE)
all: $(SAF)
!ELSE
all: $(OPT) $(SAF)
!ENDIF

$(OPT):: $(@B:contrib-optlp-src-=).cpp
	..\..\admb -c -f $?
	copy $(?:.cpp=.obj) $@

$(SAF):: $(@B:contrib-saflp-src-=).cpp
	..\..\admb -c $?
	copy $(?:.cpp=.obj) $@

includes: $(HEADERS)
	copy $(HEADERS) $(CONTRIB_INCLUDE)

clean:
	del /Q $(OBJECTS)
