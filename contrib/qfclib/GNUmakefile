ifeq ($(OS),Windows_NT)
EXT=.sh
endif

include objects.lst

all: $(addprefix $(PREFIX), $(OBJECTS))

$(PREFIX)%.obj: %.cpp
ifeq ($(SHELL),sh.exe)
	..\..\admb -c $(OPTION) $<
	copy $(basename $<).obj $@
	copy qfclib.h $(CONTRIB_DIR)\include
else
	../../admb$(EXT) -c $(OPTION) $<
	cp $(basename $<).obj $@
	cp qfclib.h $(CONTRIB_DIR)/include
endif

test:
	$(MAKE) --directory=tests

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
