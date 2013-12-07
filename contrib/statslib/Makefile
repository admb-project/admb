include objects.lst

OPT=$(OBJECTS: = ..\..\build\objects\contrib\optlp-contrib-statslib-)
SAF=$(OBJECTS: = ..\..\build\objects\contrib\saflp-contrib-statslib-)

all: $(OPT) $(SAF)

$(OPT):: $(@B:optlp-contrib-statslib-=).cpp
	..\..\admb -c -f $?
	copy $(?:.cpp=.obj) $@

$(SAF):: $(@B:saflp-contrib-statslib-=).cpp
	..\..\admb -c $?
	copy $(?:.cpp=.obj) $@

includes: $(HEADERS)
	copy $(HEADERS) $(CONTRIB_INCLUDE)

clean:
	del /Q $(OBJECTS)
