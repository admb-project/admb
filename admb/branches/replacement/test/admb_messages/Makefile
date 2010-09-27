all: clean run

run: test_admb_messages
	./test_admb_messages

test_admb_messages: test_admb_messages.o
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS=" -static -L/usr/local/gtest-1.5.0/lib -lgtest -lpthread " adlink ${OPTIONS} test_admb_messages

test_admb_messages.o: test_admb_messages.cpp
	export ADMB_HOME=$(ADMB_HOME); export PATH=$(ADMB_HOME)/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS=" -static -L/usr/local/gtest-1.5.0/lib -lgtest -lpthread " adcomp ${OPTIONS} test_admb_messages

clean:
	@rm -vf test_admb_messages.o
	@rm -vf test_admb_messages
	@rm -vf variance
	@rm -vf test_admb_messages
	@rm -vf fmin.log
