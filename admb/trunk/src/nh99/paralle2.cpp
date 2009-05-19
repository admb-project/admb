/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <admodel.h>


void function_minimizer::quasi_newton_block_pvm_master(int nvar,int _crit,
  independent_variables& x,const dvector& _g,const double& _f)
{
  double & f= (double&)_f;
  dvector& g=(dvector&) _g;
  // *********************************************************
  // block for quasi-newton minimization
  tracing_message(traceflag,"C2");
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
  tracing_message(traceflag,"D2");
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
  tracing_message(traceflag,"E2");
  dvariable xf=initial_params::reset(dvar_vector(x));
  reset_gradient_stack();
  gradcalc(0,g);
  while (fmc.ireturn>=0)
  {
    tracing_message(traceflag,"F2");
    fmc.fmin(f,x,g);
    tracing_message(traceflag,"G2");
    //cout << fmc.ireturn << endl;
    send_int_to_slaves(fmc.ireturn);
    if (fmc.ireturn>0)
    {
      int arrive=check_pvm_message(1,1);
      if (arrive)
        cout << arrive << endl;
      pvm_master_function_evaluation(f,x,g,nvar);
      arrive=check_pvm_message(1,1);
      if (arrive)
        cout << arrive << endl;
      /*
      dvariable vf=0.0;
      dvar_vector vx=dvar_vector(x);
      vf=initial_params::reset(vx);
      send_x_to_slaves(vx);
      *objective_function_value::pobjfun=0.0;
      userfunction();
      vf+=*objective_function_value::pobjfun;
      dvar_vector fslave=get_f_from_slaves();
      vf+=sum(fslave);
      f=value(vf);
      gradcalc(nvar,g);
      */
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

void function_minimizer::pvm_master_function_evaluation_no_derivatives
  (double& f,independent_variables& x,int nvar)
{
  gradient_structure::set_NO_DERIVATIVES();
  dvariable vf=0.0;
  dvar_vector vx=dvar_vector(x);
  vf=initial_params::reset(vx);
  send_x_to_slaves(vx);
  *objective_function_value::pobjfun=0.0;
  userfunction();
  vf+=*objective_function_value::pobjfun;
  dvar_matrix fslave=get_f_from_slaves();
  vf+=sum(fslave);
  f=value(vf);
}

void function_minimizer::pvm_master_function_evaluation(double& f,
  independent_variables& x,const dvector & _g,int nvar)
{
  dvector& g=(dvector&) _g;
  dvariable vf=0.0;
  dvar_vector vx=dvar_vector(x);
  vf=initial_params::reset(vx);
  send_x_to_slaves(vx);
  *objective_function_value::pobjfun=0.0;
  userfunction();
  vf+=*objective_function_value::pobjfun;
  imatrix im=get_int_from_slaves();
 /*
  if (im(1,1)!=67)
  {
    cout << "Error in im" << endl;
    ad_exit(1);
  }
 */
  dvar_matrix fslave=get_f_from_slaves();
  vf+=sum(fslave);
  f=value(vf);
  gradcalc(nvar,g);
}

#if defined(USE_ADPVM)
void function_minimizer::function_evaluation_block_pvm_slave(void)
{
  gradient_structure::set_YES_DERIVATIVES();
  reset_gradient_stack();
  //gradcalc(nvar,g);
  do
  {
    int ireturn=get_int_from_master();
    if (ireturn<0) break;
    pvm_slave_function_evaluation();
  }
  while(1);
  gradient_structure::set_NO_DERIVATIVES();
}

void function_minimizer::pvm_slave_function_evaluation(void)
{
  dvariable vf=0.0;
  dvar_vector vx=get_x_from_master();
  vf=initial_params::reset(vx);
  *objective_function_value::pobjfun=0.0;
  userfunction();
  vf+=*objective_function_value::pobjfun;
  send_int_to_master(67);
  send_f_to_master(vf);
  slave_gradcalc();
}

void function_minimizer::pvm_slave_function_evaluation_no_derivatives(void)
{
  gradient_structure::set_NO_DERIVATIVES();
  dvariable vf=0.0;
  dvar_vector vx=get_x_from_master();
  vf=initial_params::reset(vx);
  *objective_function_value::pobjfun=0.0;
  userfunction();
  vf+=*objective_function_value::pobjfun;
  send_f_to_master(vf);
}

void function_minimizer::pvm_slave_function_evaluation_noder(void)
{
  dvariable vf=0.0;
  dvar_vector vx=get_x_from_master();
  vf=initial_params::reset(vx);
  *objective_function_value::pobjfun=0.0;
  userfunction();
  vf+=*objective_function_value::pobjfun;
  send_int_to_master(67);
  send_f_to_master(vf);
}
#endif //defined(USE_ADPVM)

