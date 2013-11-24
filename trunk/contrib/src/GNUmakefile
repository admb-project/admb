$(PREFIX_OBJ)contrib.obj: contrib.cpp
ifeq ($(SHELL),sh.exe)
	..\..\admb -c contrib.cpp
	copy contrib.obj $(PREFIX_OBJ)contrib.obj
else
	../../admb -c contrib.cpp
	cp contrib.o $(PREFIX_OBJ)contrib.o
endif

test:
ifeq ($(SHELL),sh.exe)
	..\..\admb.cmd simple.tpl
	simple.exe
else
	../../admb simple.tpl
	./simple
endif

clean:
ifeq ($(SHELL),sh.exe)
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
