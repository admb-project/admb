ifeq ($(TERM),cygwin)
else
ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif
endif

ADMB_OPTIONS=-g

ifeq ($(SHELL),cmd)
GTEST_DIR=googletest-read-only\\googletest
else
GTEST_DIR=googletest-read-only/googletest
endif

GTESTS=\
 test_adstring_strcase.cpp\
 test_fmm_control.cpp\
 test_adstring_array.cpp\
 test_dlist.cpp\
 test_ad_comm.cpp\
 test_gradient_structure.cpp\
 test_option_match.cpp\
 test_lvector.cpp\
 test_adpool.cpp\
 test_dmatrix.cpp\
 test_param_init_bounded_number_vector.cpp\
 test_param_init_d3array.cpp\
 test_spline.cpp\
 test_banded_symmetric_dmatrix.cpp\
 test_line_adstring.cpp\
 test_multi_index.cpp\
 test_adtimer.cpp\
 test_idea.cpp\
 test_df_file.cpp\
 test_multinomial.cpp\
 test_multi_index.cpp\
 test_cifstream.cpp\
 test_param_init_vector_vector.cpp\
 test_param_init_matrix_vector.cpp\
 test_param_init_bounded_vector_vector.cpp\
 test_param_init_number_vector.cpp\
 test_pow.cpp\
 test_dvariable.cpp\
 test_imatrix.cpp\
 test_lmatrix.cpp\
 test_dvar_matrix.cpp\
 test_ad_integer.cpp\
 test_ivector.cpp\
 test_cspline.cpp\
 test_dvar_vector.cpp\
 test_index_type.cpp\
 test_smart_counter.cpp\
 test_df1_three_variable.cpp\
 test_df1_one_variable.cpp\
 test_df1_two_variable.cpp\
 test_param_init_matrix.cpp\
 test_objective_function_value.cpp\
 test_df3_one_variable.cpp\
 test_df3_three_variable.cpp\
 test_df3_two_variable.cpp\
 test_param_init_bounded_matrix.cpp\
 test_param_init_vector.cpp\
 test_init_adstring.cpp\
 test_init_line_adstring.cpp\
 test_dll_param_matrix.cpp\
 test_dvector.cpp\
 test_dvar3_array.cpp\
 test_arr_link.cpp\
 test_df1b2_init_number_vector.cpp\
 test_init_df1b2vector.cpp\
 test_param_init_bounded_number.cpp\
 test_param_init_bounded_vector.cpp\
 test_df1b2_init_bounded_number_vector.cpp\
 test_adstring.cpp\
 test_df1b23array.cpp\
 test_d3_array.cpp\
 test_data_matrix.cpp\
 test_tiny_ad.cpp\
 test_adjson.cpp\
 main.cpp

ifeq ($(CXX),openCC)
  GTESTS:=$(filter-out test_adjson.cpp,$(GTESTS))
endif

##Need to debug this
## test_autodif.cpp
## test_data_number.cpp
## test_df1b2variable.cpp
## test_atan2.cpp
## test_dll_param_init_bounded_vector.cpp

#cfenv is not completely supported by most compilers
#  test_cfenv.cpp

# test_df1b2atan2.obj\
# df1b2atan2.obj\
# scalefactor.obj\

all: clean gtest-all
ifeq ($(SHELL),cmd)
	gtest-all
else
	./gtest-all
endif

memcheck: gtest-all
	valgrind -v --tool=memcheck ./gtest-all

test_df1b2atan2.obj: test_df1b2atan2.cpp df1b2atan2.obj
ifeq ($(SHELL),cmd)
	CXXFLAGS=-I$(GTEST_DIR)\\include ..\\..\\admb -c $(ADMB_OPTIONS) test_df1b2atan2.cpp
else
	CXXFLAGS=-I$(GTEST_DIR)/include ../../admb$(EXT) -c $(ADMB_OPTIONS) test_df1b2atan2.cpp
endif

df1b2atan2.obj: df1b2atan2.cpp
ifeq ($(SHELL),cmd)
	..\\..\\admb -c $(ADMB_OPTIONS) $^
else
	../../admb$(EXT) -c $(ADMB_OPTIONS) $^
endif

test_scalefactor.obj: test_scalefactor.cpp scalefactor.obj
ifeq ($(SHELL),cmd)
	set CXXFLAGS=-I$(GTEST_DIR)/include & ..\\..\\admb -c $(ADMB_OPTIONS) test_scalefactor.cpp
else
	CXXFLAGS=-I$(GTEST_DIR)/include ../../admb$(EXT) -c $(ADMB_OPTIONS) test_scalefactor.cpp
endif

scalefactor.obj: scalefactor.tpl
ifeq ($(SHELL),cmd)
	set CXXFLAGS="-Dmain=scalefactor" & ..\\..\\admb -c $^
else
	CXXFLAGS=-Dmain=scalefactor ../../admb$(EXT) -c $^
endif

test_scalefactor: test_scalefactor.obj main.obj gtest-all.obj scalefactor.obj
ifeq ($(SHELL),cmd)
	set CXXFLAGS=-I$(GTEST_DIR)\\include & set LDFLAGS=-pthread & ..\\..\\admb $(ADMB_OPTIONS) $^
else
	CXXFLAGS="$(CXXFLAGS) -I$(GTEST_DIR)/include" LDFLAGS=-pthread ../../admb$(EXT) $(ADMB_OPTIONS) $^
endif

test_finance.obj: test_finance.cpp finance.obj
ifeq ($(SHELL),cmd)
	set CXXFLAGS=-I$(GTEST_DIR)/include & ..\\..\\admb -c $(ADMB_OPTIONS) test_finance.cpp
else
	CXXFLAGS=-I$(GTEST_DIR)/include ../../admb$(EXT) -c $(ADMB_OPTIONS) test_finance.cpp
endif

finance.obj: finance.tpl
ifeq ($(SHELL),cmd)
	set CXXFLAGS="-Dmain=finance" & ..\\..\\admb -c $^
else
	CXXFLAGS=-Dmain=finance ../../admb$(EXT) -c $^
endif

test_finance: test_finance.obj main.obj gtest-all.obj finance.obj
ifeq ($(SHELL),cmd)
	set CXXFLAGS=-I$(GTEST_DIR)\\include & set LDFLAGS=-pthread & ..\\..\\admb $(ADMB_OPTIONS) $^
	copy ..\\..\\examples\\admb\\finance\\finance.dat
else
	CXXFLAGS="$(CXXFLAGS) -I$(GTEST_DIR)/include" LDFLAGS=-pthread ../../admb$(EXT) $(ADMB_OPTIONS) $^
	cp ../../examples/admb/finance/finance.dat .
endif

gtest-all: gtest-all.obj $(GTESTS)
ifeq ($(SHELL),cmd)
	set CXXFLAGS=-I$(GTEST_DIR)\\include & set LDFLAGS=-pthread & ..\\..\\admb $(ADMB_OPTIONS) $^
else
	CXXFLAGS="$(CXXFLAGS) -I$(GTEST_DIR)/include" LDFLAGS=-pthread ../../admb$(EXT) $(ADMB_OPTIONS) $^
endif

test_nuts.obj: test_nuts.cpp
ifeq ($(SHELL),cmd)
	set CXXFLAGS=-I$(GTEST_DIR)/include & ..\\..\\admb -c $(ADMB_OPTIONS) test_nuts.cpp
else
	CXXFLAGS=-I$(GTEST_DIR)/include ../../admb$(EXT) -c $(ADMB_OPTIONS) test_nuts.cpp
endif

nuts_da.obj: nuts_da.cpp nuts_da.h
ifeq ($(SHELL),cmd)
	set CXXFLAGS=-I$(GTEST_DIR)/include & ..\\..\\admb -c $(ADMB_OPTIONS) nuts_da.cpp
else
	CXXFLAGS=-I$(GTEST_DIR)/include ../../admb$(EXT) -c $(ADMB_OPTIONS) nuts_da.cpp
endif

nuts2:
	matlab -nodesktop -nodisplay -r "run nutsmatlab/demo.m;quit;"

test_nuts.txt: nutsmatlab/nuts_da.m
	matlab -nodesktop -nodisplay -r "run nutsmatlab/demo.m;quit;" > test_nuts.txt

nuts: test_nuts.txt test_nuts
ifeq ($(SHELL),cmd)
	test_nuts
else
	./test_nuts
endif

test_nuts: main.cpp gtest-all.obj test_nuts.obj nuts_da.obj
ifeq ($(SHELL),cmd)
	set CXXFLAGS=-I$(GTEST_DIR)\\include & set LDFLAGS=-pthread & ..\\..\\admb $(ADMB_OPTIONS) test_nuts.obj gtest-all.obj nuts_da.obj main.cpp
else
	CXXFLAGS="$(CXXFLAGS) -I$(GTEST_DIR)/include" LDFLAGS=-pthread ../../admb$(EXT) $(ADMB_OPTIONS) test_nuts.obj gtest-all.obj nuts_da.obj main.cpp
endif

gtest-all.obj: googletest-read-only
ifeq ($(SHELL),cmd)
	$(CXX) -c $(CXXFLAGS) -g -I$(GTEST_DIR)\\include -I$(GTEST_DIR) -o $@ $(GTEST_DIR)\\src\\gtest-all.cc
else
	$(CXX) -c $(CXXFLAGS) -g -I$(GTEST_DIR)/include -I$(GTEST_DIR) -o $@ $(GTEST_DIR)/src/gtest-all.cc
endif

googletest-read-only:
	git clone --depth=1 https://github.com/google/googletest.git googletest-read-only

admb_messages:
	OPTIONS=-s $(MAKE) --directory=$@

init_bounded_number_matrix:
	OPTIONS=-s $(MAKE) --directory=$@

df33_tester:
	OPTIONS=-s $(MAKE) --directory=$@

total-clean: clean
ifeq ($(SHELL),cmd)
	@if exist googletest-read-only rmdir /s /q googletest-read-only
else
	@rm -rvf googletest-read-only
endif

clean:
ifeq ($(SHELL),cmd)
	@if exist make_sub_directory rmdir /s /q make_sub_directory
	@del gtest-all.exe 2>NUL
	@del gtest-all *.obj 2>NUL
	@del eigv.rpt 2>NUL
	@del fmin.log 2>NUL
	@del simple.log 2>NUL
	@del variance 2>NUL
	@del cmpdiff.tmp 2>NUL
	@del f1b2list1 2>NUL
	@del f1b2list12 2>NUL
	@del f1b2list13 2>NUL
	@del gradfil1.tmp 2>NUL
	@del gradfil2.tmp 2>NUL
	@del nf1b2list1 2>NUL
	@del nf1b2list12 2>NUL
	@del nf1b2list13 2>NUL
	@del scalefactor.cpp 2>NUL
	@del scalefactor.htp 2>NUL
	@del scalefactor.log 2>NUL
	@del scalefactor.exe 2>NUL
	@del varssave.tmp 2>NUL
	@del admodel.cov 2>NUL
	@del admodel.dep 2>NUL
	@del admodel.hes 2>NUL
	@del hesscheck 2>NUL
	@del hessian.bin 2>NUL
	@del scalefactor.bar 2>NUL
	@del scalefactor.bgs 2>NUL
	@del scalefactor.cor 2>NUL
	@del scalefactor.eva 2>NUL
	@del scalefactor.luu 2>NUL
	@del scalefactor.par 2>NUL
	@del scalefactor.rhes 2>NUL
	@del scalefactor.std 2>NUL
	@del finance.dat 2>NUL
	@del finance.dat 2>NUL
	@del finance.b01 2>NUL
	@del finance.b02 2>NUL
	@del finance.bar 2>NUL
	@del finance.cor 2>NUL
	@del finance.cpp 2>NUL
	@del finance.eva 2>NUL
	@del finance.htp 2>NUL
	@del finance.log 2>NUL
	@del finance.p01 2>NUL
	@del finance.p02 2>NUL
	@del finance.par 2>NUL
	@del finance.std 2>NUL
	@del scalefactor.rep 2>NUL
	@del test_finance.exe 2>NUL
	@del test_scalefactor.exe 2>NUL
	@del finance.b0 2>NUL
	@del finance.p0 2>NUL
	@del test_dvector.txt 2>NUL
else
	@rm -vf finance.b0
	@rm -vf finance.p0
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
	@rm -vf scalefactor
	@rm -vf scalefactor.exe
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
	@rm -vf finance.dat
	@rm -vf finance.b01
	@rm -vf finance.b02
	@rm -vf finance.bar
	@rm -vf finance.cor
	@rm -vf finance.cpp
	@rm -vf finance.eva
	@rm -vf finance.htp
	@rm -vf finance.log
	@rm -vf finance.p01
	@rm -vf finance.p02
	@rm -vf finance.par
	@rm -vf finance.std
	@rm -vf scalefactor.rep
	@rm -vf test_finance
	@rm -vf test_scalefactor
	@rm -vf test_dvector.txt
	@rm -rvf make_sub_directory
endif
