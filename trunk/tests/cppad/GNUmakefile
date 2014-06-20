all: cppad-trunk
	$(MAKE) test
	$(MAKE) test1
	$(MAKE) run

cppad-trunk:
	svn checkout https://projects.coin-or.org/svn/CppAD/trunk $@
	cd $@ && ./configure

test: test.cpp
	$(CXX) -Icppad-trunk -o $@  $^

test1: test1.cpp
	$(CXX) -Icppad-trunk -o $@  $^

run:
	./test
	./test1

clean:
	@rm -vf test
	@rm -vf test1
