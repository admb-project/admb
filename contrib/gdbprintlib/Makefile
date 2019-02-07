include objects.lst

!IF DEFINED(DEBUG)
OPT=$(OBJECTS: = ..\..\build\objects\debug\contrib-optlp-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects\debug\contrib-saflp-gdbprintlib-)
!ELSE
OPT=$(OBJECTS: = ..\..\build\objects\dist\contrib-optlp-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects\dist\contrib-saflp-gdbprintlib-)
!ENDIf

!IF DEFINED(COVERAGE)
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
