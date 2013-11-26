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
ifneq ($(SHELL),sh.exe)
	$(MAKE) --directory=tests
endif

clean:
ifneq ($(SHELL),sh.exe)
	@rm -vf *.obj
	@rm -vf *.o
	@rm -vf tests/tests.log
	@rm -vf tests/tests.cpp
	@rm -vf tests/admodel.hes
	@rm -vf tests/tests.par
	@rm -vf tests/tests.cor
	@rm -vf tests/tests.pin
	@rm -vf tests/variance
	@rm -vf tests/admodel.cov
	@rm -vf tests/tests.std
	@rm -vf tests/tests.htp
	@rm -vf tests/eigv.rpt
	@rm -vf tests/tests
	@rm -vf tests/tests.bar
	@rm -vf tests/tests.dat
	@rm -vf tests/fmin.log
	@rm -vf tests/tests.eva
	@rm -vf tests/admodel.dep
endif
