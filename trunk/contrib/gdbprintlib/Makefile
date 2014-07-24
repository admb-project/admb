include objects.lst

OPT=$(OBJECTS: = ..\..\build\objects\contrib\optlp-contrib-gdbprintlib-)
SAF=$(OBJECTS: = ..\..\build\objects\contrib\saflp-contrib-gdbprintlib-)

all: $(OPT) $(SAF)

$(OPT):: $(@B:optlp-contrib-gdbprintlib-=).cpp
	..\..\admb -c -f $?
	copy $(?:.cpp=.obj) $@

$(SAF):: $(@B:saflp-contrib-gdbprintlib-=).cpp
	..\..\admb -c $?
	copy $(?:.cpp=.obj) $@

includes: $(HEADERS)
	for %%a in ($(HEADERS)) do copy %%a $(CONTRIB_INCLUDE)

clean:
	del /Q $(OBJECTS)
