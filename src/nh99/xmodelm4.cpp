/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#  include <admodel.h>
int function_minimizer::random_effects_flag=0;
int function_minimizer::test_trust_flag=0;
int function_minimizer::negative_eigenvalue_flag=0;
#if defined(USE_LAPLACE)
#  include <df1b2fun.h>
#include <adrndeff.h>
//dvariable AD_uf_inner(const dvector& x,const dvar_vector& u);
void get_second_ders(int xs,int us,const init_df1b2vector y,dmatrix& Hess,
  dmatrix& Dux, df1b2_gradlist * f1b2gradlist,function_minimizer * pfmin);
double calculate_laplace_approximation(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);

//int function_minimizer::hesstype=0;

/*
int function_minimizer::set_hessian_type(int n)
{
  if (n<0 || n>4)
  {
    cerr << "Illegal value of " << n
      << " in function_minimizer::set_hessian_type(int) " << endl;
    ad_exit(1);
  }
  hesstype=n;
}
*/

void   random_effects_userfunction(double f,const dvector& x,
  const dvector& g);

void function_minimizer::AD_uf_outer(void){;}
void function_minimizer::AD_uf_inner(void){;}
//void function_minimizer::user_function(const init_df1b2vector& x,
 // df1b2variable& f){;}
void function_minimizer::user_function(void){;}

#else      // if !defined(USE_LAPLACE)


void function_minimizer::quasi_newton_block(int nvar,int _crit,
  independent_variables& x,const dvector& _g,const double& _f)
{
  double & f= (double&)_f;
  dvector & g= (dvector&)_g;
  // *********************************************************
  // block for quasi-newton minimization
  int itnold=0;
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
#endif    // if !defined(USE_LAPLACE)
