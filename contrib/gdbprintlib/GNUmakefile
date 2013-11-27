ifeq ($(OS),Windows_NT)
EXT=.sh
endif

all: $(addprefix $(PREFIX_OBJ), gdbprintlib.obj)

$(PREFIX_OBJ)%.obj: %.cpp
ifeq ($(SHELL),sh.exe)
	..\..\admb -c $(OPTION) $<
	copy $(basename $<).obj $@
else
	../../admb$(EXT) -c $(OPTION) $<
	cp $(basename $<).obj $@
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
