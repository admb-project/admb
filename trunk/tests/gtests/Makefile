GTEST_DIR=../googletest-read-only

all: gtest-all
	./gtest-all

gtest-all: main.cpp test_adstring_strcase.cpp test_fmm_control.cpp test_atan2.cpp test_adstring_array.cpp test_dlist.cpp test_ad_comm.cpp test_df1b2atan2.o df1b2atan2.o
	cp $(GTEST_DIR)/gtest-all.o .
	CXXFLAGS=-I$(GTEST_DIR)/include ../../admb gtest-all.o $^

test_df1b2atan2.o: test_df1b2atan2.cpp
	CXXFLAGS=-I$(GTEST_DIR)/include ../../admb -c -r $^

df1b2atan2.o: df1b2atan2.cpp
	../../admb -c -r $^

clean:
	@rm -vf gtest-all *.o
	@rm -vf eigv.rpt
	@rm -vf fmin.log
	@rm -vf simple.log
	@rm -vf variance
