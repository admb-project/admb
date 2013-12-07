include objects.lst

OPT=$(OBJECTS: = ..\..\..\build\objects\contrib\optlp-contrib-src-)
SAF=$(OBJECTS: = ..\..\..\build\objects\contrib\saflp-contrib-src-)

all: $(OPT) $(SAF)

$(OPT):: $(@B:optlp-contrib-src-=).cpp
	..\..\..\admb -c -f $?
	copy $(?:.cpp=.obj) $@

$(SAF):: $(@B:saflp-contrib-src-=).cpp
	..\..\..\admb -c $?
	copy $(?:.cpp=.obj) $@

includes: $(HEADERS)
	copy $(HEADERS) $(CONTRIB_INCLUDE)

clean:
	del /Q $(OBJECTS)
