include objects.lst

all: $(addprefix $(PREFIX_OBJ), $(OBJECTS))

$(PREFIX_OBJ)%.obj: %.cpp
ifeq ($(SHELL),sh.exe)
	..\..\admb -c $(OPTION) $<
	copy $(basename $<).obj $@
else
	../../admb -c $(OPTION) $<
	cp $(basename $<).obj $@
endif

clean:
ifeq ($(SHELL),sh.exe)
	-del *.obj
	-del *.o
else
	@rm -vf *.obj
	@rm -vf *.o
endif
