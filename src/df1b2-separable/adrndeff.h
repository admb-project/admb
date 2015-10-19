/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "BSD" license.
 *
 * License:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2.  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3.  Neither the name of the  University of California, Otter Research,
 * nor the ADMB Foundation nor the names of its contributors may be used
 * to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 * \file
 * Description not yet available.
 */

#if !defined(__RANDEFFECTS__)
#  define __RANDEFFECTS__

#  include <admodel.h>

class dcompressed_triplet;
class hs_symbolic;
class dvar_compressed_triplet;

/**
 * Description not yet available.
 */
class random_effects_number : public param_init_number
{
  virtual void set_random_effects_active();
  virtual void set_random_effects_inactive();
  virtual void set_only_random_effects_active();
  virtual void set_only_random_effects_inactive();
};

/**
 * Description not yet available.
 */
class random_effects_bounded_number : public param_init_bounded_number
{
  virtual void set_random_effects_active();
  virtual void set_random_effects_inactive();
  virtual void set_only_random_effects_active();
  virtual void set_only_random_effects_inactive();
};

/**
 * Description not yet available.
 */
class random_effects_vector : public param_init_vector
{
  virtual void set_random_effects_active();
  virtual void set_random_effects_inactive();
  virtual void set_only_random_effects_active();
  virtual void set_only_random_effects_inactive();
};


class random_effects_bounded_vector;

/**
 * Description not yet available.
 */
class random_effects_bounded_vector : public param_init_bounded_vector
{
  virtual void set_random_effects_active();
  virtual void set_random_effects_inactive();
  virtual void set_only_random_effects_active();
  virtual void set_only_random_effects_inactive();
};

/**
 * Description not yet available.
 */
class random_effects_matrix : public param_init_matrix
{
  virtual void set_random_effects_active();
  virtual void set_random_effects_inactive();
  virtual void set_only_random_effects_active();
  virtual void set_only_random_effects_inactive();
};

/**
 * Description not yet available.
 */
class random_effects_bounded_matrix : public param_init_bounded_matrix
{
  virtual void set_random_effects_active();
  virtual void set_random_effects_inactive();
  virtual void set_only_random_effects_active();
  virtual void set_only_random_effects_inactive();
};

class gauss_hermite_stuff;

class nested_calls_shape;
//class sparse_symbolic;

/**
 * Description not yet available.
 */
class nested_calls_indices
{
  imatrix * ptr1;
  i3_array * ptr2;
  i4_array * ptr3;
  i5_array * ptr4;
public:
  nested_calls_indices(void) : ptr1(0),ptr2(0),ptr3(0),ptr4(0){}
  ivector & level1(int i) {return (*ptr1)(i);}
  ivector & level2(int i,int j) {return (*ptr2)(i,j);}
  ivector & level3(int i,int j,int k) {return (*ptr3)(i,j,k);}
  ivector & level4(int i,int j,int k,int l) {return (*ptr4)(i,j,k,l);}
  void allocate(const nested_calls_shape& nsc);
};

/**
 * Description not yet available.
 */
class nested_calls_shape
{
  ivector * ptr1;
  imatrix * ptr2;
  i3_array * ptr3;
  i4_array * ptr4;
public:
  nested_calls_shape(void) : ptr1(0),ptr2(0),ptr3(0),ptr4(0){}
  ivector * get_ptr1(void);
  imatrix * get_ptr2(void);
  i3_array * get_ptr3(void);
  i4_array * get_ptr4(void);
  void trim(void);
  void allocate(int);
  void allocate(int,int);
  void allocate(int,int,int);
  void allocate(int,int,int,int);
  void initialize(void);
  ~nested_calls_shape();
  int & level1(int i) {return (*ptr1)(i);}
  int & operator () (int i) {return (*ptr1)(i);}
  int & level2(int i,int j) {return (*ptr2)(i,j);}
  int & operator () (int i,int j) {return (*ptr2)(i,j);}
  int & level3(int i,int j,int k) {return (*ptr3)(i,j,k);}
  int & operator () (int i,int j,int k) {return (*ptr3)(i,j,k);}
  int & level4(int i,int j,int k,int l) {return (*ptr4)(i,j,k,l);}
  int & operator () (int i,int j,int k,int l) {return (*ptr4)(i,j,k,l);}
};

/**
 * Description not yet available.
 */
class laplace_approximation_calculator
{
public:
  int init_switch;
  nested_calls_indices nested_indices;
  nested_calls_shape nested_shape;
  int separable_call_level;
  int dd_nr_flag;
  int no_re_ders_flag;
  dmatrix * antiepsilon;
  i3_array * triplet_information;
  imatrix * compressed_triplet_information;
  imatrix * calling_set;
  dvector *  importance_sampling_values;
  dvector *  importance_sampling_weights;
  int is_diagnostics_flag;
  static int saddlepointflag;
  static int alternative_user_function_flag;
  static int sparse_hessian_flag;
  static int antiflag;
  int rseed;
  static int print_importance_sampling_weights_flag;
  static dvar_vector * variance_components_vector;
  // 1 in inner opt 2 in newton-raphson 3 in laplace approximation
  static int where_are_we_flag;
  // 1 in inner opt 2 in newton-raphson 3 in
  int num_separable_calls;
  // 1 in inner opt 2 in newton-raphson 3 in
  int separable_calls_counter;
  ivector nested_separable_calls_counter;
  ivector nested_tree_position;
  // 1 in inner opt 2 in newton-raphson 3 in
  ivector* num_local_re_array;
  // 1 in inner opt 2 in newton-raphson 3 in
  ivector* num_local_fixed_array;
  int use_outliers;
  int use_gauss_hermite;
  int in_gauss_hermite_phase;
  int multi_random_effects;
  int no_function_component_flag;
  dvector * separable_function_difference;
  gauss_hermite_stuff * gh;
  dvar_matrix * importance_sampling_components;
  int importance_sampling_counter;
  d3_array * block_diagonal_hessian;
  d3_array * block_diagonal_ch;
  dvar3_array * block_diagonal_vch;
  d3_array * block_diagonal_Dux;
  imatrix * block_diagonal_re_list;
  imatrix * block_diagonal_fe_list;
  d3_array * block_diagonal_vhessianadjoint;
  dvar3_array * block_diagonal_vhessian;
  dvector local_dtemp;
  double inner_crit;
  double max_separable_g;
  double nr_crit;
  ivector used_flags;
  int have_users_hesstype;
  int inner_maxfn;
  int nr_debug;
  int inner_lmnflag;
  int inner_lmnsteps;
  int inner_iprint;
  int inner_noprintx;
  function_minimizer * pmin;
  int block_diagonal_flag;
  int bw;
  int xsize;
  int usize;
  int nvariables;
  unsigned int nvar;
  ivector minder;
  ivector maxder;
  int num_der_blocks;
  int num_nr_iters;
  int num_importance_samples;
  dmatrix epsilon;
  int hesstype;
  int var_flag;
  int have_bounded_random_effects;
  int isfunnel_flag;
  int nfunnelblocks;
  int bHess_pd_flag;
  banded_symmetric_dmatrix * bHess;
  banded_symmetric_dmatrix * bHessadjoint;
  dcompressed_triplet * sparse_triplet;
  ivector * sparse_iterator;
  int sparse_count;
  int sparse_count_adjoint;
  dcompressed_triplet * sparse_triplet2;
  dvar_compressed_triplet * vsparse_triplet;
  dcompressed_triplet * vsparse_triplet_adjoint;
  hs_symbolic * sparse_symbolic;
  hs_symbolic * sparse_symbolic2;

  void make_sparse_triplet(void);
  void check_for_need_to_reallocate(int ip);
  void get_newton_raphson_info(function_minimizer * pmin);
  void get_newton_raphson_info_slave(function_minimizer * pmin);
  void get_newton_raphson_info_master(function_minimizer * pmin);
  dvector get_newton_raphson_info_block_diagonal(function_minimizer * pmin);
  dvector get_newton_raphson_info_banded(function_minimizer * pmin);
  double do_one_feval(const dvector& x,function_minimizer * pfmin);
  void test_trust_region_method(function_minimizer * pmin);
  void get_complete_hessian(dmatrix& H,function_minimizer * pfmin);
  void get_complete_hessian(dmatrix& H,dvector& g,function_minimizer * pfmin);
  dvector lincg(dvector& x,dvector& c, dmatrix& H,double tol,double Delta,
    function_minimizer * pfmin,double& truef,double& e,double& f,
    double& fbest,int& iflag,int& iter,int maxfn);
  dvector test_trust_region_method(const dvector& _x,const double& _f,
    function_minimizer * pfmin);
  dmatrix get_gradient_for_hessian_calcs(const dmatrix& local_Hess,
    double & f);
  fmm fmc1;
  //fmmt1 fmc1;
  fmm fmc;
  dvector scale;
  dvector curv;
  dvector xadjoint;
  dvector check_local_uadjoint;
  dvector check_local_uadjoint2;
  dvector check_local_xadjoint;
  dvector check_local_xadjoint2;
  dvector uadjoint;
  dvector uhat;
  dvector ubest;
  dvector grad;
  dvector * grad_x_u;
  dvector * grad_x;
  dvector step;
  dmatrix Hess;
  d3_array * Hess_components;
  dmatrix * pHess_non_quadprior_part;
  imatrix * derindex;
  dmatrix Hessadjoint;
  dmatrix Dux;
  init_df1b2vector y;
  dvector get_uhat_quasi_newton_block_diagonal(const dvector& x,
    function_minimizer * pfmin);
  dvector get_uhat_quasi_newton(const dvector& x,function_minimizer * pfmin);
  dvector get_uhat_quasi_newton_qd(const dvector& x,function_minimizer * pfmin);
  void set_u_dot(int i);

  void do_separable_stuff_laplace_approximation_banded_adjoint
    (const df1b2variable& ff);

  dvector get_uhat_lm_newton2(const dvector& x,function_minimizer * pfmin);

  dvector get_uhat_lm_newton(const dvector& x,function_minimizer * pfmin);
  laplace_approximation_calculator(int _xsize,int _usize,int _minder,
    int _maxder,function_minimizer * pfmin);

  laplace_approximation_calculator(int _xsize,int _usize,ivector _minder,
    ivector _maxder, function_minimizer * pfmin);

  dvector operator () (const dvector& _x,const double& _f,
    function_minimizer * pfmin);

  dvector get_uhat(const dvector& x,function_minimizer * pfmin);

  ~laplace_approximation_calculator();

  void  do_separable_stuff(void);
  void  do_separable_stuff_newton_raphson_block_diagonal(df1b2variable&);
  void  do_separable_stuff_newton_raphson_banded(df1b2variable&);
  void  do_separable_stuff_laplace_approximation_block_diagonal(df1b2variable&);
  void  do_separable_stuff_laplace_approximation_banded(df1b2variable&);
  dvector default_calculations_check_derivatives(const dvector& _x,
    function_minimizer * pfmin,const double& f);
  dvector default_calculations(const dvector& _x,const double& _f,
    function_minimizer * pfmin);
  dvector banded_calculations(const dvector& _x,const double& _f,
    function_minimizer * pfmin);
  dvector block_diagonal_calculations(const dvector& _x,const double& _f,
    function_minimizer * pfmin);
  dvector default_calculations_parallel_master(const dvector& _x,
    const double& _f,function_minimizer * pfmin);
  void default_calculations_parallel_slave(const dvector& _x,
    const double& _f,function_minimizer * pfmin);
  void pvm_slave_function_evaluation_random_effects(void);
  dvector banded_calculations_trust_region_approach(const dvector& _uhat,
    function_minimizer * pmin);
  void do_newton_raphson_banded(function_minimizer * pmin,double,int&);
  double inner_optimization_banded(/*dvector& uhat,*/ dvector& x,
    function_minimizer * pfmin,int& no_converge_flag);
  void set_default_hessian_type(void);
  void check_hessian_type(const dvector& _x,function_minimizer * );
  void check_hessian_type(function_minimizer * pfmin);
  void check_hessian_type2(function_minimizer * pfmin);
  void do_separable_stuff_hessian_type_information(void);
  void get_block_diagonal_hessian(df1b2variable&);
  void allocate_block_diagonal_stuff(void);

  void do_separable_stuff_laplace_approximation_importance_sampling_adjoint
    (df1b2variable&);
  void get_hessian_components_banded_lme(function_minimizer * pfmin);
  dvar_matrix get_hessian_from_components_lme(function_minimizer * pfmin);
  dvector banded_calculations_lme(const dvector& _x,const double& _f,
    function_minimizer * pfmin);
  dvector get_gradient_lme(const dvector& x,function_minimizer * pfmin);
  dvector get_gradient_lme(function_minimizer * pfmin);
  dvector get_gradient_lme_hp(const double& x,function_minimizer * pfmin);
  void check_pool_size(void);
  void check_derivatives(const dvector&,function_minimizer * pfmin,
    double fval1);
  dvector local_minimization_routine(dvector& s,dmatrix& Hess,
    dvector& grad,double lambda);
  dvector local_minimization(dvector& s,dmatrix& Hess,
    dvector& grad,double lambda);
  imatrix check_sparse_matrix_structure(void);
  double get_fx_fu(function_minimizer * pfmin);
  void do_separable_stuff_x_u_block_diagonal(df1b2variable& ff);
  void generate_antithetical_rvs();
  double standard_type3_loop(int no_converge_flag);
  void do_newton_raphson_state_space
    (function_minimizer * pfmin,double f_from_1,int& no_converge_flag);
  void begin_separable_call_stuff(void);
  void end_separable_call_stuff(void);
  void build_up_nested_shape(void);
};

/**
 * Description not yet available.
 */
class gauss_hermite_stuff
{
public:
  dvar_matrix gauss_hermite_values;
  dvector x;
  dvector w;
  int is;
  multi_index * mi;

  gauss_hermite_stuff(laplace_approximation_calculator * lapprox,
    int use_gauss_hermite,int num_separable_calls ,const ivector& itmp);

  friend class laplace_approximation_calculator;
};

 ostream& operator <<  (const ostream &,const nested_calls_shape &);

#endif  //  #if !defined(__RANDEFFECTS__)
