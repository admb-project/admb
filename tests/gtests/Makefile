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
 test_idea.cpp\
 test_multinomial.cpp\
 test_multi_index.cpp\
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
 test_atomic.cpp\
 test_shared_ptr.cpp\
 test_param_init_bounded_dev_vector.cpp\
 test_experimenting_mcmc.cpp\
 test_gradient_descent.cpp\
 test_deep_learning.cpp\
 test_cast.cpp\
 test_valarray.cpp\
 test_vector.cpp\
 test_xpools.cpp\
 main.cpp

all: clean gtest-all
	$(MAKE) run

googletest-read-only:
	git clone --depth=1 https://github.com/google/googletest.git googletest-read-only

gtest-all.obj: googletest-read-only
	$(CXX) /c /EHsc /Igoogletest-read-only\googletest\include /Igoogletest-read-only\googletest /Fo$@ googletest-read-only\googletest\src\gtest-all.cc

gtest-all: gtest-all.obj $(GTESTS_ALL)
	set CXXFLAGS=/Igoogletest-read-only\googletest\include
	..\..\admb $(ADMB_OPTIONS) $?

run:
	gtest-all

clean:
	del gtest-all.obj
	del gtest-all.exe
