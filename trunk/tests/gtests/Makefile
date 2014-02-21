GTEST_DIR=googletest-read-only

GTESTS=\
 test_adstring_strcase.cpp\
 test_fmm_control.cpp\
 test_atan2.cpp\
 test_adstring.cpp\
 test_adstring_array.cpp\
 test_dlist.cpp\
 test_ad_comm.cpp\
 test_gradient_structure.cpp\
 test_option_match.cpp\
 test_lvector.cpp\
 test_df3_two_variable.cpp\
 test_adjson.cpp\
 test_df_file.cpp\
 main.cpp

# test_df1b2atan2.obj\
# df1b2atan2.obj\
# test_scalefactor.obj\
# scalefactor.obj\


all: clean gtest-all
	./gtest-all

test_df1b2atan2.obj: test_df1b2atan2.cpp df1b2atan2.obj
	CXXFLAGS=-I$(GTEST_DIR)/include ../../admb -c -r -g test_df1b2atan2.cpp

df1b2atan2.obj: df1b2atan2.cpp
	../../admb -c -r -g $^

test_scalefactor.obj: test_scalefactor.cpp scalefactor.obj
	CXXFLAGS=-I$(GTEST_DIR)/include ../../admb -c -r -g test_scalefactor.cpp

scalefactor.obj: scalefactor.tpl
	CXXFLAGS="-Dmain=scalefactor" ../../admb -c -r -g $^

gtest-all: gtest-all.obj $(GTESTS)
	CXXFLAGS=-I$(GTEST_DIR)/include LDFLAGS=-pthread ../../admb -g -r $^

gtest-all.obj: googletest-read-only
	$(CXX) -c -g -I$(GTEST_DIR)/include -I$(GTEST_DIR) -o $@ $(GTEST_DIR)/src/gtest-all.cc

googletest-read-only:
	svn checkout http://googletest.googlecode.com/svn/trunk/ googletest-read-only

clean:
	@rm -vf gtest-all *.obj
	@rm -vf eigv.rpt
	@rm -vf fmin.log
	@rm -vf simple.log
	@rm -vf variance
	@rm -vf cmpdiff.tmp
	@rm -vf f1b2list1
	@rm -vf f1b2list12
	@rm -vf f1b2list13
	@rm -vf gradfil1.tmp
	@rm -vf gradfil2.tmp
	@rm -vf nf1b2list1
	@rm -vf nf1b2list12
	@rm -vf nf1b2list13
	@rm -vf scalefactor.cpp
	@rm -vf scalefactor.htp
	@rm -vf scalefactor.log
	@rm -vf varssave.tmp
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf hesscheck
	@rm -vf hessian.bin
	@rm -vf scalefactor.bar
	@rm -vf scalefactor.bgs
	@rm -vf scalefactor.cor
	@rm -vf scalefactor.eva
	@rm -vf scalefactor.luu
	@rm -vf scalefactor.par
	@rm -vf scalefactor.rhes
	@rm -vf scalefactor.std
