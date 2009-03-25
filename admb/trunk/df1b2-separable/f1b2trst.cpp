/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#if defined(USE_LAPLACE)
#  include <admodel.h>
#  include <df1b2fun.h>
#  include <adrndeff.h>
//#include <vmon.h>

void function_minimizer::trust_region_update(int nvar,int _crit,
  independent_variables& x,const dvector& _g,const double& _f)
{
  double & f= (double&)_f;
  dvector & g= (dvector&)_g;
  int unvar=1;
  fmm fmc(nvar);
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

  uistream uis("admodel.hes");
  if (!uis)
  {
    cerr << "Error trying to open file admodel.hes" << endl;
    ad_exit(1);
  }
  int hnvar;
  uis >> hnvar;
  dmatrix Hess(1,hnvar,1,hnvar);
  uis >> Hess;
  if (!uis)
  {
    cerr << "Error trying to read Hessian from admodel.hes" << endl;
    ad_exit(1);
  }

  dmatrix tester(1,hnvar,1,hnvar);

  tester=Hess;

  dvector e=sort(eigenvalues(Hess));

  double lambda=-e(1)+100.;

  for (int i=1;i<=hnvar;i++)
  {
    tester(i,i)+=lambda;
  }
  dvector step =  x-solve(tester,g);
  
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

    g=(*lapprox)(step,f,this);
    
  }

} // end block for quasi newton minimization

#endif
