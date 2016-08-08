include objects.lst

!IF DEFINED(DEBUG)
OPT=$(OBJECTS: = ..\..\build\objects\debug\contrib-optlp-ecolib-)
SAF=$(OBJECTS: = ..\..\build\objects\debug\contrib-saflp-ecolib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\dist\contrib-optlp-ecolib-)
SAF=$(OBJECTS: = ..\..\build\objects\dist\contrib-saflp-ecolib-)
!ENDIF

all: $(OPT) $(SAF)

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
