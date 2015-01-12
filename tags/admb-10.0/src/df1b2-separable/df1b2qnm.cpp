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
#if defined(USE_LAPLACE)
#  include <admodel.h>
#  include <df1b2fun.h>
#  include <adrndeff.h>
//#include <vmon.h>
static int no_stuff=0;
//static void xxxy(void) {}

/**
 * Description not yet available.
 * \param
 */
void function_minimizer::quasi_newton_block(int nvar,int _crit,
  independent_variables& x,const dvector& _g,const double& _f)
{
  int ifn_trap=0;
  int itn_trap=0;
  int on=0;
  int nopt=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-fntrap",nopt))>-1)
  {
    if (nopt !=2)
    {
      cerr << "Usage -fntrap option needs two non-negative integers  -- ignored" << endl;
    }
    else
    {   
      ifn_trap=atoi(ad_comm::argv[on+1]);
      itn_trap=atoi(ad_comm::argv[on+2]);
    }
  }

  double & f= (double&)_f;
  dvector & g= (dvector&)_g;
  // *********************************************************
  // block for quasi-newton minimization
  //int itnold=0;
  int nx=nvar;
  if (negdirections) 
  {
    nx=negdirections->indexmax(); 
  }
  fmm fmc(nx);
  int on1;
  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-nox"))>-1)
  {
    fmc.noprintx=1;
  }
  fmc.maxfn= maxfn;
  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-dd",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -iprint option needs integer  -- ignored" << endl;
      //fmc.iprint=iprint;
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

  double _dfn=1.e-2;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-dfn",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -dfn option needs number  -- ignored" << endl;
    }
    else
    {   
  
      istrstream ist(ad_comm::argv[on+1]);
      ist >> _dfn;
  
      if (_dfn<=0)
      {
        cerr << "Usage -dfn option needs positive number  -- ignored" << endl;
        _dfn=0.0;
      } 
    }
  }
  if (_dfn>0) 
  {
    fmc.dfn=_dfn;
  }

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
    if (negdirections==0)
    {
      while (fmc.ireturn>=0)
      {
        fmc.fmin(f,x,g);
        if (fmc.ireturn>0)
        {
          dvariable vf=0.0;
          vf=initial_params::reset(dvar_vector(x));
          *objective_function_value::pobjfun=0.0;
          pre_userfunction();
          if ( no_stuff ==0 && quadratic_prior::get_num_quadratic_prior()>0)
          {
            quadratic_prior::get_M_calculations();
          }
          vf+=*objective_function_value::pobjfun;
          f=value(vf);
          gradcalc(nvar,g);
        }
      }
    }
    else
    {

      int i;
      int nx=negdirections->indexmax();
      independent_variables u(1,nx);
      dvector gu(1,nx);
      for (i=1;i<=nx;i++) u(i)=1.e-3;
      dvector x0(1,x.indexmax());
      x0=x;
      while (fmc.ireturn>=0)
      {
        fmc.fmin(f,u,gu);
        if (fmc.ireturn>0)
        {
          dvariable vf=0.0;
          x=x0;
          for (i=1;i<=nx;i++)
          {
            x+=u(i)*(*negdirections)(i);
          }
          vf=initial_params::reset(dvar_vector(x));
          *objective_function_value::pobjfun=0.0;
          pre_userfunction();
          if ( no_stuff ==0 && quadratic_prior::get_num_quadratic_prior()>0)
          {
            quadratic_prior::get_M_calculations();
          }
          vf+=*objective_function_value::pobjfun;
          f=value(vf);
          gradcalc(nvar,g);
          gu=(*negdirections)*g;
        }
      }
      x=x0;
      for (i=1;i<=nx;i++)
      {
        x+=u(i)*(*negdirections)(i);
      }
      delete negdirections;
      negdirections=0;
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
    if (lapprox==0)
    {
      cerr << "Error allocating memory for lapprox" << endl;
      ad_exit(1);
    }
    initial_df1b2params::current_phase=initial_params::current_phase;
    
    initial_df1b2params::save_varsptr();
    allocate();
    initial_df1b2params::restore_varsptr();

    df1b2_gradlist::set_no_derivatives();
    int nvar=initial_params::nvarcalc_all(); 
    dvector y(1,nvar);
    initial_params::xinit_all(y); 
    initial_df1b2params::reset_all(y);

    gradient_structure::set_NO_DERIVATIVES();
    //vmon_begin();
    // see what kind of hessian we are dealing with
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

        // Print Hessian type and related info       
        switch(lapprox->hesstype)
        {
        case 1:
          cout << "Hessian type 1 " << endl;
          break;
        case 2:
          cout << "\nBlock diagonal Hessian (Block size =" <<
		 (lapprox->usize)/(lapprox->num_separable_calls) << ")\n" << endl;
          break;
        case 3:
          cout << "\nBanded Hessian (Band width = " << lapprox->bw << ")\n" << endl;
          break;
        case 4:
          cout << "Hessian type 4 " << endl;
          break;
        default:
          cerr << "This can't happen" << endl;
          ad_exit(1);
        }

      }
    }

   /*
    cout << "NEED to remove !!!! " << endl;
    initial_df1b2params::separable_flag=0;
    lapprox->hesstype=1;
   */

    // linear mixed effects optimization
    if (laplace_approximation_calculator::variance_components_vector) 
    {
      if (!lapprox)
      {
        cerr << "this can't happen" << endl;
        ad_exit(1);
      }
      lapprox->get_hessian_components_banded_lme(this);
    }

    if (negdirections==0)
    {
      while (fmc.ireturn>=0)
      {
        fmc.fmin(f,x,g);
        if (fmc.ireturn>0)
        {
          if (ifn_trap)
          {
            if (ifn_trap==fmc.ifn && itn_trap == fmc.itn)
            {
              cout << "we are here" << endl;
            }
          }
          g=(*lapprox)(x,f,this);
          if (lapprox->init_switch==0)
          {
            if (f<fmc.fbest)
            {
              lapprox->ubest=lapprox->uhat;
            }
          }
        }
      }
    }
    else
    {
      int i;
      int nx=negdirections->indexmax();
      independent_variables u(1,nx);
      dvector x0(1,x.indexmax());
      x0=x;
      dvector gu(1,nx);
      for (i=1;i<=nx;i++) u(i)=1.e-3;
      while (fmc.ireturn>=0)
      {
        fmc.fmin(f,u,gu);
        if (fmc.ireturn>0)
        {
          x=x0;
          for (i=1;i<=nx;i++)
          {
            x+=u(i)*(*negdirections)(i);
          }
          g=(*lapprox)(x,f,this);
          gu=(*negdirections)*g;
        }
      }
      x=x0;
      for (i=1;i<=nx;i++)
      {
        x+=u(i)*(*negdirections)(i);
      }
      delete negdirections;
      negdirections=0;
    }
    initial_params::set_inactive_only_random_effects(); 
  }

  if (funnel_init_var::py)
  {
    delete funnel_init_var::py;
    funnel_init_var::py=0;
  }
  gradient_structure::set_NO_DERIVATIVES();
  ffbest=fmc.fbest;
  g=fmc.gbest(1,fmc.gbest.indexmax());
  iexit=fmc.iexit;
  ifn=fmc.ifn;
  ihflag=fmc.ihflag;
  ihang=fmc.ihang;
  maxfn_flag=fmc.maxfn_flag;
  quit_flag=fmc.quit_flag;
  objective_function_value::gmax=fabs(fmc.gmax);
} // end block for quasi newton minimization

#endif
