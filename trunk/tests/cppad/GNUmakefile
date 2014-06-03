all: cppad-trunk
	$(MAKE) test
	$(MAKE) test1
	$(MAKE) run

cppad-trunk:
	svn checkout https://projects.coin-or.org/svn/CppAD/trunk $@
	pushd $@ && ./configure

test: test.cpp
	$(CXX) -Icppad-trunk -o $@  $^

test1: test1.cpp
	$(CXX) -Icppad-trunk -o $@  $^

run:
	./test
	./test1

clean:
	rm -rvf cppad-trunk
