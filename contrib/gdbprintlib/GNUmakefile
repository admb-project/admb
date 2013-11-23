$(PREFIX_OBJ)gdbprintlib.obj: gdbprintlib.cpp
ifeq ($(SHELL),sh.exe)
	..\..\admb.cmd -c gdbprintlib.cpp
	copy gdbprintlib.obj $(PREFIX_OBJ)gdbprintlib.obj
else
	../../admb -c gdbprintlib.cpp
	cp gdbprintlib.o $(PREFIX_OBJ)gdbprintlib.obj
endif

clean:
ifeq ($(SHELL),sh.exe)
	del gdbprintlib.obj
	del gdbprintlib.o
else
	@rm -vf gdbprintlib.obj
	@rm -vf gdbprintlib.o
endif
