/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <df1b2fun.h>

re_objective_function_value * re_objective_function_value::pobjfun=0;
adpool::adpool(){;}
adpool::~adpool(){;}

void laplace_approximation_calculator::build_up_nested_shape(void){;}
int laplace_approximation_calculator::saddlepointflag=0; 
int laplace_approximation_calculator::sparse_hessian_flag=0; 
int laplace_approximation_calculator::print_importance_sampling_weights_flag=0;
dvar_vector * laplace_approximation_calculator::variance_components_vector=0;
init_df1b2vector * funnel_init_var::py=0;

adpool * df1b2variable::pool= new adpool();

//void function_minimizer::hess_routine_random_effects(){;}
//void function_minimizer::quasi_newton_block(int,int,independent_variables&,const dvector&,const double&){;}
init_df1b2vector::~init_df1b2vector(){;}
init_df1b2vector::init_df1b2vector(){;}
void function_minimizer::trust_region_update(int nvar,int _crit,
  independent_variables& x,const dvector& _g,const double& _f){;}

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::operator () 
    (const dvector& _x,const double& _f, function_minimizer * pfmin)
{
  dvector x(1,1);
  return x;
}

void laplace_approximation_calculator::check_hessian_type(class function_minimizer *pfm){;}

nested_calls_shape::~nested_calls_shape(void){;}

void laplace_approximation_calculator::check_hessian_type2
  (function_minimizer * pfmin){;}

laplace_approximation_calculator::~laplace_approximation_calculator(){;}

void laplace_approximation_calculator::get_hessian_components_banded_lme
  (function_minimizer * pfmin){;}

const int df1b2variable::adpool_vectorsize=10;
double initial_df1b2params::cobjfun=0.0;
int initial_df1b2params::separable_flag=0;
int initial_df1b2params::have_bounded_random_effects=0;
int initial_df1b2params::separable_calculation_type=0;
int df1b2variable::adpool_counter=0;
adpool * df1b2variable::adpool_vector[10];
int df1b2variable::nvar_vector[10];
imatrix * initial_df1b2params::pointer_table=0;
//int global_nvar=0;
class df1b2_gradlist;

df1b2_gradlist * f1b2gradlist = NULL;
df1b2_gradlist * localf1b2gradlist = 0;
df1b2_gradlist * globalf1b2gradlist = 0;

int df1b2variable::noallocate=0;

initial_df1b2params ** initial_df1b2params::varsptr 
  =new P_INITIAL_DF1B2PARAMS[1000];
int initial_df1b2params::num_initial_df1b2params=0;         // array

int initial_df1b2params::num_initial_df1b2params_sav=0;         // array
initial_df1b2params ** initial_df1b2params::varsptr_sav=0; 

int initial_df1b2params::current_phase=0;

int df1b2variable::adpool_stack_pointer=0;
const int df1b2variable::adpool_stack_size=10;
adpool * df1b2variable::adpool_stack[10];
int df1b2variable::adpool_nvar_stack[10];



init_df1b2variable ** init_df1b2variable::list=0;
int df1b2variable::nvar=0; 
int df1b2variable::minder=0; 
int df1b2variable::maxder=0; 
int df1b2variable::blocksize=0; 
int init_df1b2variable::num_variables=0;
int df1b2_gradlist::no_derivatives=0;
int df1b2variable::passnumber=0;
int ad_dstar::n=0;

/**
 * Description not yet available.
 * \param
 */
  int initial_params::nvarcalc_all()
  {
    int nvar=0;
    return nvar;
  }

/**
 * Description not yet available.
 * \param
 */
  void initial_params::xinit_all(const dvector& _x)
  {
  }

/**
 * Description not yet available.
 * \param
 */
  dvariable initial_params::reset_all(const dvar_vector& x,const dvector& __pen)
  {
    dvariable pen=0.0;
    return pen;
  }

void initial_df1b2params::save_varsptr(void){;}
void initial_df1b2params::restore_varsptr(void){;}
void initial_df1b2params::reset_all(const dvector & v){;}


/*
void function_minimizer::quasi_newton_block(int nvar,int _crit,
  independent_variables& x,const dvector& _g,const double& _f)
{; }
*/

/**
 * Description not yet available.
 * \param
 */
laplace_approximation_calculator::laplace_approximation_calculator
  (int _xsize,int _usize,int _minder,int _maxder,
  function_minimizer * _pmin) : 
  local_dtemp(1,_xsize),
  pmin(_pmin),
  block_diagonal_flag(0),
  xsize(_xsize),
  usize(_usize),
  fmc1(_usize),
  fmc(_xsize),
  xadjoint(1,_xsize),
  check_local_uadjoint(1,_usize),
  check_local_uadjoint2(1,_usize),
  check_local_xadjoint(1,_xsize),
  check_local_xadjoint2(1,_xsize),
  uadjoint(1,_usize),
  uhat(1,_usize)
  {;}

void adpool::deallocate(void){;}

/**
 * Description not yet available.
 * \param
 */
void function_minimizer::quasi_newton_block(int nvar,int _crit,
  independent_variables& x,const dvector& _g,const double& _f)
{
  double & f= (double&)_f;
  dvector & g= (dvector&)_g;
  // *********************************************************
  // block for quasi-newton minimization
  //int itnold=0;
  fmm fmc(nvar);
  int on1;
  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-nox"))>-1)
  {
    fmc.noprintx=1;
  }
  fmc.maxfn= maxfn;
  int nopt=0;
  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-dd",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -iprint option needs integer  -- ignored" << endl;
      fmc.iprint=iprint;
    }
    else
    {   
      int jj=atoi(ad_comm::argv[on1+1]);
      fmc.dcheck_flag=jj;
    }
  }
  nopt=0;
  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-iprint",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -iprint option needs integer  -- ignored" << endl;
      fmc.iprint=iprint;
    }
    else
    {   
      int jj=atoi(ad_comm::argv[on1+1]);
      fmc.iprint=jj;
    }
  }
  else
  {
    fmc.iprint= iprint;
  }
  fmc.crit = crit;
  fmc.imax = imax;
  fmc.dfn= dfn;
  fmc.scroll_flag= scroll_flag;
  fmc.min_improve=min_improve;
  gradient_structure::set_YES_DERIVATIVES();
  // set convergence criterion for this phase
  if (_crit)
  {
    fmc.crit = _crit;
  }
  if (!(!convergence_criteria))
  {
    int ind=min(convergence_criteria.indexmax(),
      initial_params::current_phase);
    fmc.crit=convergence_criteria(ind);
  }
  if (!(!maximum_function_evaluations))
  {
    int ind=min(maximum_function_evaluations.indexmax(),
      initial_params::current_phase);
    fmc.maxfn= (int) maximum_function_evaluations(ind);
  }
  
  //if (!random_effects_flag)
  {
    dvariable xf=initial_params::reset(dvar_vector(x));
    reset_gradient_stack();
    gradcalc(0,g);
    while (fmc.ireturn>=0)
    {
      fmc.fmin(f,x,g);
      if (fmc.ireturn>0)
      {
        dvariable vf=0.0;
        vf=initial_params::reset(dvar_vector(x));
        *objective_function_value::pobjfun=0.0;
        userfunction();
        vf+=*objective_function_value::pobjfun;
        f=value(vf);
        gradcalc(nvar,g);
      }
    }
  }

  gradient_structure::set_NO_DERIVATIVES();
  ffbest=fmc.fbest;
  iexit=fmc.iexit;
  ifn=fmc.ifn;
  ihflag=fmc.ihflag;
  ihang=fmc.ihang;
  maxfn_flag=fmc.maxfn_flag;
  quit_flag=fmc.quit_flag;
  objective_function_value::gmax=fabs(fmc.gmax);
} // end block for quasi newton minimization

