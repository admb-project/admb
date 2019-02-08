all: clean
	echo "Begin ADMB Unit tests...\n"
	$(MAKE) gtest-all.obj
	$(MAKE) gtest-all

googletest-read-only:
	git clone --depth=1 https://github.com/google/googletest.git googletest-read-only

gtest-all.obj: googletest-read-only
	$(CXX) -c $(CXXFLAGS) -std=c++11 -g -Igoogletest-read-only\googletest\include -Igoogletest-read-only\googletest -o $@ googletest-read-only\googletest\src\gtest-all.cc

gtest-all: gtest-all.obj main.cpp test_dmatrix.cpp
	set CXXFLAGS=-Igoogletest-read-only\googletest\include & set LDFLAGS=-pthread & ..\..\admb $(ADMB_OPTIONS) gtest-all.obj main.cpp test_dmatrix.cpp

clean:
	del gtest-all.obj
	del gtest-all.exe
