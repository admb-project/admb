include objects.lst

!IF DEFINED(DEBUG)
OPT=$(OBJECTS: = ..\..\build\objects\debug\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\debug\contrib-saflp-qfclib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\dist\contrib-optlp-qfclib-)
SAF=$(OBJECTS: = ..\..\build\objects\dist\contrib-saflp-qfclib-)
!ENDIF

all: $(OPT) $(SAF)

$(OPT):: $(@B:contrib-optlp-qfclib-=).cpp
	..\..\admb -c -f $?
	copy $(?:.cpp=.obj) $@

$(SAF):: $(@B:contrib-saflp-qfclib-=).cpp
	..\..\admb -c $?
	copy $(?:.cpp=.obj) $@

includes: $(HEADERS)
	copy $(HEADERS) $(CONTRIB_INCLUDE)

clean:
	del /Q $(OBJECTS)
