all:
	$(MAKE) run
	$(MAKE) run2

run: simple.dll
	Rscript simple.r

run2: testdll.exe
	LD_LIBRARY_PATH=. $^

simple.dll: simple.tpl
	..\..\admb -d simple.tpl

example.dll: example.cpp
	$(CXX) -shared -o $@ $^

testdll.exe: main.cpp simple.dll example.dll
	$(CXX) -o $@ main.cpp simple.dll example.dll

clean:
	@del /Q admodel.cov
	@del /Q admodel.dep
	@del /Q admodel.hes
	@del /Q eigv.rpt
	@del /Q example.dll
	@del /Q example.obj
	@del /Q fmin.log
	@del /Q main.obj
	@del /Q simple.bar
	@del /Q simple.cor
	@del /Q simple.cpp
	@del /Q simple.dat
	@del /Q simple.def
	@del /Q simple.dll
	@del /Q simple.eva
	@del /Q simple.htp
	@del /Q simple.log
	@del /Q simple.obj
	@del /Q simple.par
	@del /Q simple.std
	@del /Q simple.tpl
	@del /Q testdll.exe
	@del /Q variance
