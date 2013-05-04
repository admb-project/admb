GTEST_DIR=../gtest

all: gtest-all
	./gtest-all

gtest-all: gtest-all.o
	ADMB_HOME="$(ADMB_HOME)" PATH="$(ADMB_HOME)"/bin:${PATH} CXXFLAGS=-I$(GTEST_DIR)/include admb main.cpp gtest-all.o

gtest-all.o: $(GTEST_DIR)/src/gtest-all.cc
	$(CXX) -c -I$(GTEST_DIR)/include -I$(GTEST_DIR) -o $@ $<

clean:
