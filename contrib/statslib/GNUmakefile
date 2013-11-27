ifneq (,$(findstring sh.exe,$(SHELL)))
  SHELL=cmd
endif

include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJECTS))

$(PREFIX_OBJ)%.obj: %.cpp
ifeq ($(SHELL),cmd)
	..\..\admb -c $(OPTION) $<
	copy $(basename $<).obj $@
else
	../../admb -c $(OPTION) $<
	cp $(basename $<).obj $@
endif

clean:
ifeq ($(SHELL),cmd)
	-del *.obj
	-del *.o
else
	@rm -vf *.obj
	@rm -vf *.o
endif
