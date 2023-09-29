all: CppAD
	cd CppAD && ./configure
	$(MAKE) test
	$(MAKE) test1
	$(MAKE) run

CppAD:
	git clone https://github.com/coin-or/CppAD.git $@

test: test.cpp
	$(CXX) -ICppAD/include -o $@ $^

test1: test1.cpp
	$(CXX) -ICppAD/include -o $@ $^

run:
	./test
	./test1

clean:
	@rm -vf test
	@rm -vf test1
