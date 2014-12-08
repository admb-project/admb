all: simple.dll

run:
	Rscript simple.r

testdll.exe: main.obj simple.dll example.dll
	$(CXX) -o $@ main.obj simple.dll example.dll

simple.dll: simple.tpl
	..\..\admb -d simple.tpl

main.obj: main.cpp
	$(CXX) -c -o $@ $^

example.dll: example.obj
	$(CXX) -shared -o $@ $^

example.obj: example.cpp
	$(CXX) -c -o $@ $^

clean:
	del /Q admodel.cov
	del /Q admodel.dep
	del /Q admodel.hes
	del /Q eigv.rpt
	del /Q example.dll
	del /Q example.obj
	del /Q fmin.log
	del /Q main.obj
	del /Q simple.bar
	del /Q simple.cor
	del /Q simple.cpp
	del /Q simple.dat
	del /Q simple.def
	del /Q simple.dll
	del /Q simple.eva
	del /Q simple.htp
	del /Q simple.log
	del /Q simple.obj
	del /Q simple.par
	del /Q simple.std
	del /Q simple.tpl
	del /Q testdll.exe
	del /Q variance
