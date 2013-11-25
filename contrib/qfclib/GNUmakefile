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

test:
	make --directory=tests

clean:
ifneq ($(SHELL),sh.exe)
	@rm -vf *.obj
	@rm -vf *.o
	@rm -vf tests/testfunction.htp
	@rm -vf tests/testfunction
	@rm -vf tests/nf1b2list1
	@rm -vf tests/variance
	@rm -vf tests/f1b2list12
	@rm -vf tests/f1b2list13
	@rm -vf tests/testfunctionre.log
	@rm -vf tests/testfunctionre.cpp
	@rm -vf tests/eigv.rpt
	@rm -vf tests/testfunction.log
	@rm -vf tests/testfunction.cpp
	@rm -vf tests/testfunctionre.htp
	@rm -vf tests/nf1b2list12
	@rm -vf tests/f1b2list1
	@rm -vf tests/nf1b2list13
	@rm -vf tests/fmin.log
	@rm -vf tests/testfunctionre
endif
