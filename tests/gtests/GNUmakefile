ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
    ADMB_HOME=..\\..\\..
  else
    ifndef TERM
      export SHELL=cmd
      CMDSHELL=cmd
    endif
    ifndef CMDSHELL
      EXT=.sh
    endif
  endif
endif

ifdef DEBUG
ADMB_OPTIONS=-g
endif

ifeq ($(CMDSHELL),cmd)
GTEST_DIR=googletest-read-only\\googletest
else
GTEST_DIR=googletest-read-only/googletest
endif

GTESTS_ALL=\
 test_atomic.cpp\
 test_shared_ptr.cpp\
 test_adstring_strcase.cpp\
 test_fmm_control.cpp\
 test_adstring_array.cpp\
 test_option_match.cpp\
 test_lvector.cpp\
 test_adpool.cpp\
 test_param_init_d3array.cpp\
 test_spline.cpp\
 test_banded_symmetric_dmatrix.cpp\
 test_line_adstring.cpp\
 test_multi_index.cpp\
 test_adtimer.cpp\
 test_idea.cpp\
 test_df_file.cpp\
 test_multinomial.cpp\
 test_param_init_vector_vector.cpp\
 test_param_init_matrix_vector.cpp\
 test_param_init_bounded_vector_vector.cpp\
 test_param_init_number_vector.cpp\
 test_pow.cpp\
 test_dvariable.cpp\
 test_lmatrix.cpp\
 test_dvar_matrix.cpp\
 test_ad_integer.cpp\
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
 test_dvar6_array.cpp\
 test_dvar7_array.cpp\
 test_arr_link.cpp\
 test_arr_list.cpp\
 test_dfpool.cpp\
 test_df1b2_init_number_vector.cpp\
 test_init_df1b2vector.cpp\
 test_param_init_bounded_number.cpp\
 test_param_init_bounded_vector.cpp\
 test_df1b2_init_bounded_number_vector.cpp\
 test_df1b23array.cpp\
 test_d3_array.cpp\
 test_d4_array.cpp\
 test_d5_array.cpp\
 test_d6_array.cpp\
 test_d7_array.cpp\
 test_data_matrix.cpp\
 test_tiny_ad.cpp\
 test_adjson.cpp\
 test_dmatrix.cpp\
 test_size_count.cpp\
 test_sub_unallocated.cpp\
 test_dvar4_array.cpp\
 test_utils.cpp\
 test_cifstream.cpp\
 test_dvar5_array.cpp\
 test_param_init_number.cpp\
 test_df3_three_vector.cpp\
 test_param_init_bounded_matrix_vector.cpp\
 test_param_init_bounded_number_matrix.cpp\
 test_adlist_ptr.cpp\
 test_param_init_bounded_number_vector.cpp\
 test_fill_seqadd.cpp\
 test_adstring.cpp\
 test_ad_comm.cpp\
 test_ivector.cpp\
 test_imatrix.cpp\
 test_i3_array.cpp\
 test_i4_array.cpp\
 test_i5_array.cpp\
 test_dvar_vector_position.cpp\
 test_atan2.cpp\
 test_gradcalc.cpp\
 test_autodif.cpp\
 test_param_init_bounded_dev_vector.cpp\
 test_experimenting_mcmc.cpp\
 test_gradient_descent.cpp\
 test_deep_learning.cpp\
 test_cast.cpp\
 test_valarray.cpp\
 test_vector.cpp\
 test_issues.cpp\
 test_funnel.cpp\
 test_math.cpp\
 test_return_arrays.cpp\
 test_df_file.cpp\
 test_async.cpp\
 test_df1b2variable.cpp\
 test_df1b2vector.cpp\
 test_move.cpp\
 test_move_dvar_vector.cpp\
 test_omp.cpp\
 test_simple_async.cpp\
 test_template.cpp\
 test_admb_messages.cpp\
 test_param_init_bounded_number_matrix.cpp\
 test_data_number.cpp\
 test_rvalue.cpp\
 test_dfsdmat.cpp\
 test_data_int.cpp\
 test_dvar_compressed_triplet.cpp\
 test_dcompressed_triplet.cpp\
 test_df1_three_vector.cpp\
 test_df1_three_matrix.cpp\
 test_df1_two_vector.cpp\
 test_df1_two_matrix.cpp\
 test_df1_one_vector.cpp\
 test_df1_one_matrix.cpp\
 test_hs_smatrix.cpp\
 test_dvar_hs_smatrix.cpp\
 test_hs_symbolic.cpp\
 test_hs_smatrix.cpp\
 test_df3_one_vector.cpp\
 test_df3_one_matrix.cpp\
 test_df3_three_vector.cpp\
 test_df3_three_matrix.cpp\
 test_df3_two_vector.cpp\
 test_df3_two_matrix.cpp\
 test_df1b2matrix.cpp\
 test_nested_calls_shape.cpp\
 test_df1b2bessel.cpp\
 test_funnel_init_df1b2variable.cpp\
 test_laplace_approximation_calculator.cpp\
 test_df1b2atan2.cpp\
 test_shareinfo.cpp\
 test_quadratic_prior.cpp\
 test_evaluate_function.cpp\
 test_gradient_structure_thread.cpp\
 test_dll_param_init_bounded_vector.cpp\
 test_ad_double.cpp\
 test_prevariable.cpp\
 test_independent_variables.cpp\
 main.cpp

ERRORS=\
 test_dll_param_init_bounded_vector.cpp\
 test_cfenv.cpp\
 test_dependent_variables_information.cpp\
 test_grad_stack.cpp\
 test_gradient_structure.cpp\
 test_gradient_structure2.cpp\
 test_humungous_pointer.cpp\
 test_nuts.cpp\
 main.cpp

GTESTS_DEV=\
 test_interface.obj\
 main.cpp

ifdef GTESTS_DEV
GTESTS=$(GTESTS_DEV)
else
GTESTS=$(GTESTS_ALL)
endif

ifeq ($(CXX),openCC)
  GTESTS:=$(filter-out test_adjson.cpp,$(GTESTS))
endif
ifeq ($(SAFE_ONLY),yes)
  GTESTS:=$(filter-out test_adjson.cpp,$(GTESTS))
endif

all: clean
	$(MAKE) googletest-read-only
	$(MAKE) gtest-all
	$(MAKE) run

run:
ifeq ($(CMDSHELL),cmd)
	gtest-all
else
	./gtest-all
endif

others:
	$(MAKE) finance
	$(MAKE) scalefactor

finance: clean
	$(MAKE) gtest-finance
ifeq ($(CMDSHELL),cmd)
	gtest-finance
else
	./gtest-finance
endif

scalefactor: clean
	$(MAKE) gtest-scalefactor
ifeq ($(CMDSHELL),cmd)
	gtest-scalefactor
else
	./gtest-scalefactor
endif

dev: clean
	$(MAKE) gtest-dev
ifeq ($(CMDSHELL),cmd)
	gtest-dev
else
	./gtest-dev
endif

memcheck: gtest-all
	valgrind -v --tool=memcheck ./gtest-all

ifeq ($(CMDSHELL),cmd)
thread_funnel5.obj: thread_funnel5.cpp
	set "CXXFLAGS=$(CXXFLAGS) -I$(GTEST_DIR)\\include" && ..\\..\\admb -c $(ADMB_OPTIONS) test_thread_funnel.cpp
else
thread_funnel5.obj: ../thread_funnel/forest/thread_funnel5.cpp
	CXXFLAGS="-I$(GTEST_DIR)/include -I../thread_funnel/forest" ../../admb$(EXT) -o thread_funnel5.obj -c $(ADMB_OPTIONS) ../thread_funnel/forest/thread_funnel5.cpp
endif

test_thread_funnel.obj: test_thread_funnel.cpp
ifeq ($(CMDSHELL),cmd)
	set "CXXFLAGS=$(CXXFLAGS) -I$(GTEST_DIR)\\include" && ..\\..\\admb -c $(ADMB_OPTIONS) test_thread_funnel.cpp
else
	CXXFLAGS="-I$(GTEST_DIR)/include -I../thread_funnel/forest" ../../admb$(EXT) -c $(ADMB_OPTIONS) test_thread_funnel.cpp
endif

test_interface.obj: test_interface.cpp
ifeq ($(CMDSHELL),cmd)
	set "set CXXFLAGS=$(CXXFLAGS) -I$(GTEST_DIR)\\include" && ..\\..\\admb -c $(ADMB_OPTIONS) test_interface.cpp
else
	CXXFLAGS="-I$(GTEST_DIR)/include -I../thread_funnel/forest -I../interface/include" ../../admb$(EXT) -c $(ADMB_OPTIONS) test_interface.cpp
endif

test_df1b2atan2.obj: test_df1b2atan2.cpp df1b2atan2.obj
ifeq ($(CMDSHELL),cmd)
	set "CXXFLAGS=$(CXXFLAGS) -I$(GTEST_DIR)\\include" && ..\\..\\admb -c $(ADMB_OPTIONS) test_df1b2atan2.cpp
else
	CXXFLAGS=-I$(GTEST_DIR)/include ../../admb$(EXT) -c $(ADMB_OPTIONS) test_df1b2atan2.cpp
endif

df1b2atan2.obj: df1b2atan2.cpp
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb -c $(ADMB_OPTIONS) $^
else
	../../admb$(EXT) -c $(ADMB_OPTIONS) $^
endif

test_scalefactor.obj: test_scalefactor.cpp scalefactor.obj
ifeq ($(CMDSHELL),cmd)
	set "CXXFLAGS=$(CXXFLAGS) -I$(GTEST_DIR)\\include" && ..\\..\\admb -c $(ADMB_OPTIONS) test_scalefactor.cpp
else
	CXXFLAGS="$(CXXFLAGS) -I$(GTEST_DIR)/include" ../../admb$(EXT) -c $(ADMB_OPTIONS) test_scalefactor.cpp
endif

scalefactor.obj: scalefactor.tpl
ifeq ($(CMDSHELL),cmd)
	set "CXXFLAGS=$(CXXFLAGS) -Dmain=scalefactor" && ..\\..\\admb -c $^
else
	CXXFLAGS="$(CXXFLAGS) -Dmain=scalefactor" ../../admb$(EXT) -c $^
endif

gtest-scalefactor: test_scalefactor.obj main.cpp gtest-all.obj scalefactor.obj
ifeq ($(CMDSHELL),cmd)
	set "CXXFLAGS=$(CXXFLAGS) -I$(GTEST_DIR)\\include" && set "LDFLAGS=-pthread $(LDFLAGS)" & ..\\..\\admb -o $@.exe $(ADMB_OPTIONS) $^
else
	CXXFLAGS="$(CXXFLAGS) -I$(GTEST_DIR)/include" LDFLAGS="-pthread $(LDFLAGS)" ../../admb$(EXT) -o $@ $(ADMB_OPTIONS) $^
endif

test_finance.obj: test_finance.cpp finance.obj
ifeq ($(CMDSHELL),cmd)
	set "CXXFLAGS=$(CXXFLAGS) -I$(GTEST_DIR)\\include" && ..\\..\\admb -c $(ADMB_OPTIONS) test_finance.cpp
else
	CXXFLAGS="$(CXXFLAGS) -I$(GTEST_DIR)/include" ../../admb$(EXT) -c $(ADMB_OPTIONS) test_finance.cpp
endif

finance.obj: finance.tpl
ifeq ($(CMDSHELL),cmd)
	set "CXXFLAGS=$(CXXFLAGS) -Dmain=finance" && ..\\..\\admb -c $^
else
	CXXFLAGS="$(CXXFLAGS) -Dmain=finance" ../../admb$(EXT) -c $^
endif

gtest-finance: test_finance.obj main.cpp gtest-all.obj finance.obj
ifeq ($(CMDSHELL),cmd)
	set "CXXFLAGS=$(CXXFLAGS) -I$(GTEST_DIR)\\include" && set "LDFLAGS=-pthread $(LDFLAGS)" & ..\\..\\admb -o $@.exe $(ADMB_OPTIONS) $^
	copy ..\\..\\examples\\admb\\finance\\finance.dat
else
	CXXFLAGS="$(CXXFLAGS) -I$(GTEST_DIR)/include" LDFLAGS="-pthread $(LDFLAGS)" ../../admb$(EXT) -o $@ $(ADMB_OPTIONS) $^
	cp ../../examples/admb/finance/finance.dat .
endif

gtest-all: gtest-all.obj $(patsubst %.cpp,%.obj,$(GTESTS_ALL))
ifeq ($(CMDSHELL),cmd)
	set "CXXFLAGS=$(CXXFLAGS) -I$(GTEST_DIR)\\include" && set "LDFLAGS=-pthread $(LDFLAGS)"  & ..\\..\\admb $(ADMB_OPTIONS) $^
else
	CXXFLAGS="$(CXXFLAGS) -I$(GTEST_DIR)/include" LDFLAGS="-pthread $(LDFLAGS)" ../../admb$(EXT) $(ADMB_OPTIONS) $^
endif

gtest-dev: gtest-all.obj $(GTESTS_DEV)
ifeq ($(CMDSHELL),cmd)
	set "CXXFLAGS=$(CXXFLAGS) -I$(GTEST_DIR)\\include" && set "LDFLAGS=-pthread $(LDFLAGS)" & ..\\..\\admb -o $@ $(ADMB_OPTIONS) $^
else
	CXXFLAGS="$(CXXFLAGS) -I$(GTEST_DIR)/include" LDFLAGS="-pthread $(LDFLAGS)" ../../admb$(EXT) -o $@ $(ADMB_OPTIONS) $^
endif

test_nuts.obj: test_nuts.cpp
ifeq ($(CMDSHELL),cmd)
	set "CXXFLAGS=$(CXXFLAGS) -I$(GTEST_DIR)\\include" && ..\\..\\admb -c $(ADMB_OPTIONS) test_nuts.cpp
else
	CXXFLAGS=-I$(GTEST_DIR)/include ../../admb$(EXT) -c $(ADMB_OPTIONS) test_nuts.cpp
endif

nuts_da.obj: nuts_da.cpp nuts_da.h
ifeq ($(CMDSHELL),cmd)
	set "CXXFLAGS=$(CXXFLAGS) -I$(GTEST_DIR)\\include" && ..\\..\\admb -c $(ADMB_OPTIONS) nuts_da.cpp
else
	CXXFLAGS=-I$(GTEST_DIR)/include ../../admb$(EXT) -c $(ADMB_OPTIONS) nuts_da.cpp
endif

nuts2:
	/Applications/MATLAB_R2016a.app/bin/matlab -nodesktop -nodisplay -r "run nutsmatlab/demo.m;quit;"

test_nuts.txt: nutsmatlab/nuts_da.m
	/Applications/MATLAB_R2016a.app/bin/matlab -nodesktop -nodisplay -r "run nutsmatlab/demo.m;quit;" > test_nuts.txt

nuts: test_nuts.txt test_nuts
ifeq ($(CMDSHELL),cmd)
	test_nuts
else
	./test_nuts
endif

test_nuts: main.cpp gtest-all.obj test_nuts.obj nuts_da.obj
ifeq ($(CMDSHELL),cmd)
	set "CXXFLAGS=$(CXXFLAGS) -I$(GTEST_DIR)\\include" && set LDFLAGS=-pthread & ..\\..\\admb $(ADMB_OPTIONS) test_nuts.obj gtest-all.obj nuts_da.obj main.cpp
else
	CXXFLAGS="$(CXXFLAGS) -I$(GTEST_DIR)/include" LDFLAGS=-pthread ../../admb$(EXT) $(ADMB_OPTIONS) test_nuts.obj gtest-all.obj nuts_da.obj main.cpp
endif

gtest-all.obj:
ifeq ($(CMDSHELL),cmd)
	$(CXX) -c $(CXXFLAGS) -std=c++14 -g -I$(GTEST_DIR)\\include -I$(GTEST_DIR) -o $@ $(GTEST_DIR)\\src\\gtest-all.cc
else
	$(CXX) -c $(CXXFLAGS) -std=c++14 -g -I$(GTEST_DIR)/include -I$(GTEST_DIR) -o $@ $(GTEST_DIR)/src/gtest-all.cc
endif

%.obj:%.cpp
ifeq ($(CMDSHELL),cmd)
	set "CXXFLAGS=$(CXXFLAGS) -I$(GTEST_DIR)\\include" && set "LDFLAGS=-pthread $(LDFLAGS)"  & ..\\..\\admb -c $(ADMB_OPTIONS) $^
else
	CXXFLAGS="$(CXXFLAGS) -I$(GTEST_DIR)/include" LDFLAGS="-pthread $(LDFLAGS)" ../../admb$(EXT) -c $(ADMB_OPTIONS) $^
endif


googletest-read-only:
	git clone --depth=1 --branch=v1.14.0 https://github.com/google/googletest.git googletest-read-only

admb_messages:
	OPTIONS=-s $(MAKE) --directory=$@

init_bounded_number_matrix:
	OPTIONS=-s $(MAKE) --directory=$@

df33_tester:
	OPTIONS=-s $(MAKE) --directory=$@

total-clean: clean
ifeq ($(CMDSHELL),cmd)
	@if exist googletest-read-only rmdir /s /q googletest-read-only
else
	@rm -rvf googletest-read-only
endif

clean:
ifeq ($(CMDSHELL),cmd)
	@if exist make_sub_directory rmdir /s /q make_sub_directory
	@del test_i4_array.txt 2>NUL
	@del test_i5_array.txt 2>NUL
	@del test_init_line_adstring.dat 2>NUL
	@del test_init_adstring.dat 2>NUL
	@del test_ad_comm.log 2>NUL
	@del d5_array.txt 2>NUL
	@del d6_array.txt 2>NUL
	@del test_damtrixio.txt 2>NUL
	@del d3io.txt 2>NUL
	@del fuistreamd4_array.txt 2>NUL
	@del test_data_4iarray.cpp 2>NUL
	@del testi3array.txt 2>NUL
	@del uistreamd4_array.txt 2>NUL
	@del uos.txt 2>NUL
	@del uosivector.txt 2>NUL
	@del varr4.txt 2>NUL
	@del maxlimit.txt 2>NUL
	@del test_cifstream_adstring.txt 2>NUL
	@del test_cifstream_float.txt 2>NUL
	@del datafiledoesexist.dat 2>NUL
	@del pinfiledoesexist.pin 2>NUL
	@del test_cifstream_longlong.txt 2>NUL
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
	@del test_adstring_array.txt 2>NUL
	@del test_cifstream_darray.txt 2>NUL
	@del test_cifstream_dvariable.txt 2>NUL
	@del test_cifstream_iarray.txt 2>NUL
	@del test_cifstream_float_dos.txt 2>NUL
	@del /Q big_signature_n.txt 2>NUL
	@del /Q big_signature_r.txt 2>NUL
	@del /Q big_signature_rn.txt 2>NUL
	@del /Q maxlimit1.txt 2>NUL
	@del /Q maxlimit2.txt 2>NUL
	@del /Q maxlimit3.txt 2>NUL
	@del /Q maxlimita.txt 2>NUL
	@del /Q test_dvar_vector_read_from_file.txt 2>NUL
	@del /Q test_dvector_read_from_file2.txt 2>NUL
	@del /Q test_dvector_read_from_file3.txt 2>NUL
	@del /Q test_param_init_number.txt
	@del /Q admodel.bvs
	@del /Q corrtest
	@del /Q gtest-dev
	@del /Q gtest-finance
	@del /Q gtest-scalefactor
	@del /Q sparseness.info
	@del /Q gtest-finance.exe
	@del /Q gtest-scalefactor.exe
	@del /Q dmatrix.txt
	@del /Q dvector.txt
else
	@rm -vf test_i4_array.txt
	@rm -vf test_i5_array.txt
	@rm -vf test_init_line_adstring.dat
	@rm -vf test_init_adstring.dat
	@rm -vf test_ad_comm.log
	@rm -vf d5_array.txt
	@rm -vf d6_array.txt
	@rm -vf test_damtrixio.txt
	@rm -vf d3io.txt
	@rm -vf fuistreamd4_array.txt
	@rm -vf test_data_4iarray.cpp
	@rm -vf testi3array.txt
	@rm -vf uistreamd4_array.txt
	@rm -vf uos.txt
	@rm -vf uosivector.txt
	@rm -vf varr4.txt
	@rm -vf maxlimit.txt
	@rm -vf test_cifstream_adstring.txt
	@rm -vf test_cifstream_float.txt
	@rm -vf test_cifstream_longlong.txt
	@rm -vf training
	@rm -vf training.bar
	@rm -vf training.cor
	@rm -vf training.cpp
	@rm -vf training.eva
	@rm -vf training.htp
	@rm -vf training.log
	@rm -vf training.par
	@rm -vf training.rep
	@rm -vf training.std
	@rm -vf training2
	@rm -vf training2.bar
	@rm -vf training2.cor
	@rm -vf training2.cpp
	@rm -vf training2.eva
	@rm -vf training2.htp
	@rm -vf training2.log
	@rm -vf training2.par
	@rm -vf training2.rep
	@rm -vf training2.std
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
	@rm -vf test_adstring_array.txt
	@rm -vf test_cifstream_darray.txt
	@rm -vf test_cifstream_dvariable.txt
	@rm -vf test_cifstream_iarray.txt
	@rm -vf datafiledoesexist.dat
	@rm -vf pinfiledoesexist.pin
	@rm -vf test_cifstream_float_dos.txt
	@rm -vf big_signature_n.txt
	@rm -vf big_signature_r.txt
	@rm -vf big_signature_rn.txt
	@rm -vf maxlimit1.txt
	@rm -vf maxlimit2.txt
	@rm -vf maxlimit3.txt
	@rm -vf maxlimita.txt
	@rm -vf test_dvar_vector_read_from_file.txt
	@rm -vf test_dvector_read_from_file2.txt
	@rm -vf test_dvector_read_from_file3.txt
	@rm -vf test_param_init_number.txt
	@rm -vf admodel.bvs
	@rm -vf corrtest
	@rm -vf gtest-dev
	@rm -vf gtest-finance
	@rm -vf gtest-scalefactor
	@rm -vf sparseness.info
	@rm -vf dmatrix.txt
	@rm -vf dvector.txt
	@rm -vf varssave*.tmp
	@rm -vf gradfil*.tmp
	@rm -vf cmpdiff*.tmp
	@rm -vf model.bar
	@rm -vf model.cor
	@rm -vf model.eva
	@rm -vf model.log
	@rm -vf model.par
	@rm -vf model.std
endif
