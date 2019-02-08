GTEST_DIR=googletest-read-only\googletest
GTESTS_ALL=main.cpp test_dmatrix.cpp

all: clean
	echo "Begin ADMB Unit tests...\n"
	$(MAKE) gtest-all.obj
	$(MAKE) gtest-all.exe

googletest-read-only:
	git clone --depth=1 https://github.com/google/googletest.git googletest-read-only

gtest-all.obj: googletest-read-only
	$(CXX) -c $(CXXFLAGS) -std=c++11 -g -I$(GTEST_DIR)\include -I$(GTEST_DIR) -o $@ $(GTEST_DIR)\src\gtest-all.cc

gtest-all.exe: gtest-all.obj $(GTESTS_ALL)
	set CXXFLAGS=-I$(GTEST_DIR)\include & set LDFLAGS=-pthread & ..\..\admb $(ADMB_OPTIONS) $^

clean:
	del gtest-all.obj
	del gtest-all.exe
