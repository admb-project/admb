/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function function_minimizer::prof_minimize_re
*/
#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h>

#ifdef ISZERO
  #undef ISZERO
#endif
#define ISZERO(d) ((d)==0.0)

void function_minimizer::prof_minimize_re(int iprof, double sigma,
  double new_value, const double& _fprof,const int underflow_flag,
  double global_min, const double& _penalties, const double& _final_weight)
   {
     double& penalties=(double&) _penalties;
     double& fprof=(double&) _fprof;
     double& final_weight=(double&) _final_weight;
    if (!underflow_flag)
    {
     int max_profile_phases=3;
     int profile_phase=1;
     initial_params::current_phase = initial_params::max_number_phases;
     while (profile_phase <= max_profile_phases)
     {
      {
// ****************************************************************
// ****************************************************************
// ****************************************************************
// ****************************************************************
       initial_params::set_active_only_random_effects();
       //cout << nvar << endl;
       /*int unvar=*/initial_params::nvarcalc(); // get the number of active
       initial_params::restore_start_phase();
       initial_params::set_inactive_random_effects();
       int nvar=initial_params::nvarcalc(); // get the number of active

// ****************************************************************
// ****************************************************************
// ****************************************************************
// ****************************************************************


       dvector g(1,nvar);
       independent_variables x(1,nvar);
       initial_params::xinit(x);    // get the initial values into the
                                    // x vector
       fmm fmc(nvar);
       fmc.maxfn= maxfn;
       fmc.iprint= iprint;
       fmc.crit = crit;
       fmc.imax = imax;
       fmc.dfn= dfn;
       fmc.scroll_flag= scroll_flag;
       fmc.min_improve=min_improve;
       double f=0.0;
       gradient_structure::set_YES_DERIVATIVES();
       // set convergence criterion for this phase
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
         fmc.maxfn=int(maximum_function_evaluations(ind));
       }
       int itnsave=0;
       //double weight=pow(50.0,profile_phase)/(sigma*sigma);
       double weight = pow(120.0,profile_phase);
       if (!ISZERO(sigma))
       {
         weight /= (sigma*sigma);
       }
       final_weight=weight;

// ****************************************************************
// ****************************************************************
// ****************************************************************
// ****************************************************************
  {
    // calculate the number of random effects unvar
    // this turns on random effects variables and turns off
    // everything else
    //cout << nvar << endl;
    initial_params::set_active_only_random_effects();
    //cout << nvar << endl;
    int unvar=initial_params::nvarcalc(); // get the number of active
    //df1b2_gradlist::set_no_derivatives();

    if (funnel_init_var::py)
    {
      delete funnel_init_var::py;
      funnel_init_var::py=0;
    }
    if (lapprox)
    {
      delete lapprox;
      lapprox=0;
      df1b2variable::pool->deallocate();

      for (int i=1;i<df1b2variable::adpool_counter;i++)
      {
        delete df1b2variable::adpool_vector[i];
        df1b2variable::adpool_vector[i]=0;
        df1b2variable::nvar_vector[i]=0;
      }
      df1b2variable::adpool_counter=0;
    }
    lapprox=new laplace_approximation_calculator(nvar,unvar,1,nvar+unvar,
      this);
    if (!lapprox)
    {
      cerr << "Error allocating memory for lapprox" << endl;
      ad_exit(1);
    }
    initial_df1b2params::current_phase=initial_params::current_phase;

    initial_df1b2params::save_varsptr();
    allocate();
    initial_df1b2params::restore_varsptr();

    df1b2_gradlist::set_no_derivatives();
    nvar=initial_params::nvarcalc_all();
    dvector y(1,nvar);
    initial_params::xinit_all(y);
    initial_df1b2params::reset_all(y);

    gradient_structure::set_NO_DERIVATIVES();
    //vmon_begin();
    // see what kind of hessian we are dealing with
    int on=0;
    int nopt=0;
    //  DF Nov 27 11
    initial_params::set_inactive_only_random_effects();
    nvar=initial_params::nvarcalc(); // get the number of active

    if (lapprox->have_users_hesstype==0)
    {
      if (initial_df1b2params::separable_flag)
      {
        if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-newht",nopt))>-1)
        {
          lapprox->check_hessian_type2(this);
        }
        else
        {
          lapprox->check_hessian_type(this);
        }
      }
      cout << "Hesstype = " << lapprox->hesstype << endl;
    }

   /*
    cout << "NEED to remove !!!! " << endl;
    initial_df1b2params::separable_flag=0;
    lapprox->hesstype=1;
   */

    // linear mixed effects optimization
    if (laplace_approximation_calculator::variance_components_vector)
    {
      lapprox->get_hessian_components_banded_lme(this);
    }

    if (negdirections==0)
    {
      dvector g1(1,nvar);
      while (fmc.ireturn>=0)
      {
        fmc.fmin(f,x,g);
        double diff =
        new_value-value(likeprof_params::likeprofptr[iprof]->variable());
        if (fmc.itn>itnsave && diff < pow(.1,iprof)*sigma)
        {
          fmc.ifn=fmc.imax;
        }
        if (fmc.ireturn>0)
        {
          g=(*lapprox)(x,f,this);
        }
        dvariable vf=0.0;
        vf=initial_params::reset(dvar_vector(x));
        *objective_function_value::pobjfun=0.0;
      //**********************************************************
      //**********************************************************
      //**********************************************************
        if (lapprox)
        {
          if (lapprox->hesstype==2)
          {
            //lapprox->num_separable_calls=0;
            lapprox->separable_calls_counter=0;
          }
        }
      //**********************************************************
      //**********************************************************
      //**********************************************************
      //**********************************************************
        userfunction();
        dvariable tv=likeprof_params::likeprofptr[iprof]->variable();
        vf+=weight*square(new_value-tv);
        f+=value(vf);
        gradcalc(nvar,g1);
        g+=g1;
      }
    }
    initial_params::set_inactive_only_random_effects();
  }




// ****************************************************************
// ****************************************************************
// ****************************************************************
// ****************************************************************



       gradient_structure::set_NO_DERIVATIVES();
       iexit=fmc.iexit;
       ihflag=fmc.ihflag;
       ihang=fmc.ihang;
       maxfn_flag=fmc.maxfn_flag;
       quit_flag=fmc.quit_flag;
       fprof=value(initial_params::reset(dvar_vector(x)));
       *objective_function_value::pobjfun=0.0;
      //**********************************************************
      //**********************************************************
      //**********************************************************
        if (lapprox)
        {
          if (lapprox->hesstype==2)
          {
            //lapprox->num_separable_calls=0;
            lapprox->separable_calls_counter=0;
          }
        }
      //**********************************************************
      //**********************************************************
      //**********************************************************
      //**********************************************************
       userfunction();
       double tv=value(likeprof_params::likeprofptr[iprof]->variable());
       fprof+=value(*objective_function_value::pobjfun);
       penalties=weight*(new_value-tv)*(new_value-tv);
       fprof+=penalties;
       if (quit_flag=='Q') break;
       if (!quit_flag || quit_flag == 'N')
       {
         profile_phase++;
       }
      }
     }
    }
    else
    {
      fprof=global_min+20.0;
    }
   }
