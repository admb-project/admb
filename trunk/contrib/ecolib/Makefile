include objects.lst

OPT=$(OBJECTS: = ..\..\build\objects\contrib\optlp-contrib-ecolib-)
SAF=$(OBJECTS: = ..\..\build\objects\contrib\saflp-contrib-ecolib-)

all: $(OPT) $(SAF)

$(OPT):: $(@B:optlp-contrib-ecolib-=).cpp
	..\..\admb -c -f $?
	copy $(?:.cpp=.obj) $@

$(SAF):: $(@B:saflp-contrib-ecolib-=).cpp
	..\..\admb -c $?
	copy $(?:.cpp=.obj) $@

includes: $(HEADERS)
	copy $(HEADERS) $(CONTRIB_INCLUDE)

clean:
	del /Q $(OBJECTS)
