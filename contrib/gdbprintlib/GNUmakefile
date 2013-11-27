ifneq (,$(findstring sh.exe,$(SHELL)))
  SHELL=cmd
endif

all: $(addprefix $(PREFIX_OBJ), gdbprintlib.obj)

$(PREFIX_OBJ)%.obj: %.cpp
ifeq ($(SHELL),cmd)
	..\..\admb -c $(OPTION) $<
	copy $(basename $<).obj $@
else
	../../admb -c $(OPTION) $<
	cp $(basename $<).obj $@
endif

test:

clean:
ifeq ($(SHELL),cmd)
	del gdbprintlib.obj
	del gdbprintlib.o
else
	@rm -vf gdbprintlib.obj
	@rm -vf gdbprintlib.o
endif
