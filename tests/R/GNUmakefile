ifeq ($(OS),Windows_NT)
EXT=.sh
endif

all:
	$(MAKE) run
	$(MAKE) run2

run: simple.so
	Rscript simple-unix.r

run2: test_example
	LD_LIBRARY_PATH=.:$(LD_LIBRARY_PATH) ./test_example

simple.so: simple.tpl
	../../admb$(EXT) -d simple.tpl

example.so: example.cpp
	$(CXX) -shared -fPIC -o $@ $^

test_example: main.cpp simple.so example.so
	$(CXX) -o $@ main.cpp simple.so example.so

clean:
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf eigv.rpt
	@rm -vf example.so
	@rm -vf example.obj
	@rm -vf fmin.log
	@rm -vf main.obj
	@rm -vf simple.bar
	@rm -vf simple.cor
	@rm -vf simple.cpp
	@rm -vf simple.dat
	@rm -vf simple.def
	@rm -vf simple.so
	@rm -vf simple.eva
	@rm -vf simple.htp
	@rm -vf simple.log
	@rm -vf simple.obj
	@rm -vf simple.par
	@rm -vf simple.std
	@rm -vf simple.dll
	@rm -vf testso
	@rm -vf testso.exe
	@rm -vf variance
	@rm -vf test_example
