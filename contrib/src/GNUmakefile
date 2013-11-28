ifeq ($(OS),Windows_NT)
EXT=.sh
endif

all: $(PREFIX)contrib.obj

$(PREFIX)%.obj: %.cpp
ifeq ($(SHELL),sh.exe)
	..\..\admb -c $(OPTION) $<
	copy $(basename $<).obj $@
	copy contrib.h $(CONTRIB_DIR)\include
else
	../../admb$(EXT) -c $(OPTION) $<
	cp $(basename $<).obj $@
	cp contrib.h $(CONTRIB_DIR)/include
endif

test:
ifeq ($(SHELL),sh.exe)
	..\..\admb $(OPTION) simple.tpl
	simple
else
	../../admb$(EXT) $(OPTION) simple.tpl
	./simple
endif

clean:
ifeq ($(SHELL),sh.exe)
	del contrib.obj
	del contrib.o
	del simple.obj
	del simple.o
	del simple.std
	del simple.htp
	del admodel.hes
	del variance
	del simple
	del simple.exe
	del admodel.cov
	del simple.bar
	del eigv.rpt
	del simple.eva
	del fmin.log
	del simple.log
	del simple.cpp
	del simple.par
	del simple.cor
	del admodel.dep
else
	@rm -f contrib.obj
	@rm -f contrib.o
	@rm -f simple.obj
	@rm -f simple.o
	@rm -f simple.std
	@rm -f simple.htp
	@rm -f admodel.hes
	@rm -f variance
	@rm -f simple
	@rm -f simple.exe
	@rm -f admodel.cov
	@rm -f simple.bar
	@rm -f eigv.rpt
	@rm -f simple.eva
	@rm -f fmin.log
	@rm -f simple.log
	@rm -f simple.cpp
	@rm -f simple.par
	@rm -f simple.cor
	@rm -f admodel.dep
endif
