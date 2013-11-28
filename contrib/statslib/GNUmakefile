ifeq ($(OS),Windows_NT)
EXT=.sh
endif

include objects.lst

all: $(addprefix $(PREFIX), $(OBJECTS))

$(PREFIX)%.obj: %.cpp
ifeq ($(SHELL),sh.exe)
	..\..\admb -c $(OPTION) $<
	copy $(basename $<).obj $@
	copy statsLib.h $(CONTRIB_DIR)\include
else
	../../admb$(EXT) -c $(OPTION) $<
	cp $(basename $<).obj $@
	cp statsLib.h $(CONTRIB_DIR)/include
endif

clean:
ifeq ($(SHELL),sh.exe)
	-del *.obj
	-del *.o
else
	@rm -vf *.obj
	@rm -vf *.o
endif
