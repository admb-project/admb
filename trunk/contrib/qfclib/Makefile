include objects.lst

OPT=$(OBJECTS: = ..\..\..\build\objects\contrib\optlp-contrib-qfclib-)
SAF=$(OBJECTS: = ..\..\..\build\objects\contrib\saflp-contrib-qfclib-)

all: $(OPT) $(SAF)

$(OPT):: $(@B:optlp-contrib-qfclib-=).cpp
	..\..\..\admb -c -f $?
	copy $(?:.cpp=.obj) $@

$(SAF):: $(@B:saflp-contrib-qfclib-=).cpp
	..\..\..\admb -c $?
	copy $(?:.cpp=.obj) $@

includes: $(HEADERS)
	copy $(HEADERS) $(CONTRIB_INCLUDE)

clean:
	del /Q $(OBJECTS)
