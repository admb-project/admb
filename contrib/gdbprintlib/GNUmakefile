ifeq ($(OS),Windows_NT)
EXT=.sh
endif

OBJECTS=$(addprefix $(PREFIX), gdbprintlib.obj)

all: $(OBJECTS)

$(PREFIX)%.obj: %.cpp
ifeq ($(SHELL),sh.exe)
	..\..\admb -c $(OPTION) $<
	copy $(basename $<).obj $@
	copy gdbprintlib.h $(CONTRIB_DIR)\include
else
	../../admb$(EXT) -c $(OPTION) $<
	cp $(basename $<).obj $@
	cp gdbprintlib.h $(CONTRIB_DIR)/include
endif

test:

clean:
ifeq ($(SHELL),sh.exe)
	del gdbprintlib.obj
	del gdbprintlib.o
else
	@rm -vf gdbprintlib.obj
	@rm -vf gdbprintlib.o
endif
