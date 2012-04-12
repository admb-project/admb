/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#if defined(USE_LAPLACE)
#include <df1b2fun.h>
#include <adrndeff.h>
#include <admodel.h>

void function_minimizer::quasi_newton_block_pvm_master_random_effects
  (int nvar,int _crit,
  independent_variables& x,const dvector& _g,const double& _f)
{
  double & f= (double&)_f;
  dvector& g=(dvector&) _g;
  // *********************************************************
  // block for quasi-newton minimization
  tracing_message(traceflag,"C2");
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



  int unvar=1;
  if (random_effects_flag)
  {
    initial_params::set_active_only_random_effects(); 
    //cout << nvar << endl;
    unvar=initial_params::nvarcalc(); // get the number of active
    initial_params::restore_start_phase(); 
    initial_params::set_inactive_random_effects(); 
    int nvar1=initial_params::nvarcalc(); // get the number of active
    if (nvar1 != nvar)
    {
      cerr << "failed sanity check in "
       "void function_minimizer::quasi_newton_block" << endl;
      ad_exit(1);
    }
  }

  if (!random_effects_flag || !unvar)
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
  else
  {

    // calculate the number of random effects unvar
    // this turns on random effects variables and turns off
    // everything else
    //cout << nvar << endl;
    initial_params::set_active_only_random_effects(); 
    //cout << nvar << endl;
    int unvar=initial_params::nvarcalc(); // get the number of active
    //df1b2_gradlist::set_no_derivatives();

    if (lapprox)
    {
      delete lapprox;
      lapprox=0;
      df1b2variable::pool->deallocate();

      for (int i=0;i<df1b2variable::adpool_counter;i++)
      {
        delete df1b2variable::adpool_vector[i];
        df1b2variable::adpool_vector[i]=0;
        df1b2variable::nvar_vector[i]=0;
        df1b2variable::adpool_counter=0;
      }
    }
    lapprox=new laplace_approximation_calculator(nvar,unvar,1,nvar+unvar,
      this); 
    initial_df1b2params::current_phase=initial_params::current_phase;
    
    initial_df1b2params::save_varsptr();
    allocate();
    initial_df1b2params::restore_varsptr();

    df1b2_gradlist::set_no_derivatives();
    int nvar=initial_params::nvarcalc_all(); 
    dvector y(1,nvar);
    initial_params::xinit_all(y); 
    initial_df1b2params::reset_all(y);

    //vmon_begin();
    while (fmc.ireturn>=0)
    {
      fmc.fmin(f,x,g);
      send_int_to_slaves(fmc.ireturn);
      if (fmc.ireturn>0)
      {
        //int arrive=check_pvm_message(1,1);
        //if (arrive)
        //  cout << arrive << endl;
        g=(*lapprox)(x,f,this);
        //g=lapprox->default_calculations_parallel_master(x,f,this);
        //arrive=check_pvm_message(1,1);
        //if (arrive)
        //  cout << arrive << endl;
      }
      //cout << setprecision(16) << f << " " << x << " " << g << endl;
    }
    //vmon_done();
    // turn off the random effects
    initial_params::set_inactive_only_random_effects(); 
    //df1b2variable::pool.deallocate();
    
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

/*
void function_minimizer::pvm_master_function_evaluation_random_effects
  (double& f,independent_variables& x,const dvector & _g,int nvar)
{
  dvector& g=(dvector&) _g;
  g=lapprox->function_default_calculations_parallel(x,f,this); 
}
*/
  // void function_minimizer::function_evaluation_block_pvm_slave(void)
  // {
  //   gradient_structure::set_YES_DERIVATIVES();
  //   reset_gradient_stack();
  //   //gradcalc(nvar,g);
  //   do
  //   {
  //     int ireturn=get_int_from_master();
  //     if (ireturn<0) break;
  //     pvm_slave_function_evaluation();
  //   }
  //   while(1);
  //   gradient_structure::set_NO_DERIVATIVES();
  // }
  // 
  // void function_minimizer::pvm_slave_function_evaluation(void)
  // {
  //   dvariable vf=0.0;
  //   dvar_vector vx=get_x_from_master();
  //   vf=initial_params::reset(vx);
  //   *objective_function_value::pobjfun=0.0;
  //   userfunction();
  //   vf+=*objective_function_value::pobjfun;
  //   send_int_to_master(67);
  //   send_f_to_master(vf);
  //   slave_gradcalc();
  // }
  // 
  // void function_minimizer::pvm_slave_function_evaluation_noder(void)
  // {
  //   dvariable vf=0.0;
  //   dvar_vector vx=get_x_from_master();
  //   vf=initial_params::reset(vx);
  //   *objective_function_value::pobjfun=0.0;
  //   userfunction();
  //   vf+=*objective_function_value::pobjfun;
  //   send_int_to_master(67);
  //   send_f_to_master(vf);
  // }
  // 

#endif // #if defined(USE_LAPLACE)
