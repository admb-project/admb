include objects.lst

!IF DEFINED(DEBUG)
OPT=$(OBJECTS: = ..\..\build\objects\debug\contrib-optlp-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\debug\contrib-saflp-statslib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\dist\contrib-optlp-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\dist\contrib-saflp-statslib-)
!ENDIF

all: $(OPT) $(SAF)

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
