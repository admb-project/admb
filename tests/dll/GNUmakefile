ifeq ($(OS),Windows_NT)
EXT=.sh
endif

all: testso

run:
	./testso

testso: main.obj simple.so example.so
	$(CXX) -o $@ main.obj simple.so example.so

simple.so: simple.obj
	../../admb$(EXT) -d $^

simple.obj:
	cp ../../examples/admb/simple/simple.tpl .
	cp ../../examples/admb/simple/simple.dat .
	../../admb$(EXT) -c -d simple.tpl

main.obj: main.cpp
	$(CXX) -c -o $@ $^

example.so: example.obj
	$(CXX) -shared -o $@ $^

example.obj: example.cpp
	$(CXX) -c -o $@ $^

clean:
	rm -vf admodel.cov
	rm -vf admodel.dep
	rm -vf admodel.hes
	rm -vf eigv.rpt
	rm -vf example.so
	rm -vf example.obj
	rm -vf fmin.log
	rm -vf main.obj
	rm -vf simple.bar
	rm -vf simple.cor
	rm -vf simple.cpp
	rm -vf simple.dat
	rm -vf simple.def
	rm -vf simple.so
	rm -vf simple.eva
	rm -vf simple.htp
	rm -vf simple.log
	rm -vf simple.obj
	rm -vf simple.par
	rm -vf simple.std
	rm -vf simple.tpl
	rm -vf testso
	rm -vf testso.exe
	rm -vf variance
