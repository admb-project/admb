/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */

#if defined(USE_LAPLACE)
#  include <admodel.h>
#  include <df1b2fun.h>
#  include <adrndeff.h>
void get_second_ders(int xs,int us,const init_df1b2vector y,dmatrix& Hess,
  dmatrix& Dux, df1b2_gradlist * f1b2gradlist,function_minimizer * pfmin,
  laplace_approximation_calculator* lap);
double calculate_laplace_approximation(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);

#if defined(USE_ADPVM)
/**
 * Description not yet available.
 * \param
 */
void get_second_ders_slave(int xs,int us,const init_df1b2vector _y,
  dmatrix& Hess,
  dmatrix& Dux, df1b2_gradlist * f1b2gradlist,function_minimizer * pfmin,
  laplace_approximation_calculator * lpc)
{
  // Note that xs is the number of active non random effects
  // parameters
  // us is the number of random effects parameters
  int j;
  int i;
  ADUNCONST(init_df1b2vector,y)
  int num_der_blocks=lpc->num_der_blocks;
  int xsize=lpc->xsize;
  int usize=lpc->usize;

  for (int ip=1;ip<=num_der_blocks;ip++)
  {
    df1b2variable::minder=lpc->minder(ip);
    df1b2variable::maxder=lpc->maxder(ip);
    lpc->set_u_dot(ip);
    df1b2_gradlist::set_yes_derivatives();
    (*re_objective_function_value::pobjfun)=0;
    df1b2variable pen=0.0;
    df1b2variable zz=0.0;
    initial_df1b2params::reset(y,pen);
    if (initial_df1b2params::separable_flag)
    {
      initial_df1b2params::separable_calculation_type=2;
      Hess.initialize();
      Dux.initialize();
    }

    //cout << "2D" << endl;
    pfmin->user_function();

    //pfmin->user_function(y,zz);
    (*re_objective_function_value::pobjfun)+=pen;
    (*re_objective_function_value::pobjfun)+=zz;

    if (!initial_df1b2params::separable_flag)
    {
      set_dependent_variable(*re_objective_function_value::pobjfun);
      df1b2_gradlist::set_no_derivatives();
      df1b2variable::passnumber=1;
      df1b2_gradcalc1();

      int mind=y(1).minder;
      int jmin=max(mind,xsize+1);
      int jmax=min(y(1).maxder,xsize+usize);
      dmatrix tHess(1,usize,jmin,jmax);
      for (i=1;i<=usize;i++)
        for (j=jmin;j<=jmax;j++)
        {
          //Hess(i,j-xsize)=y(i+xsize).u_bar[j-mind];
          tHess(i,j)=y(i+xsize).u_bar[j-mind];
        }
      send_dmatrix_to_master(tHess);

      jmin=max(mind,1);
      jmax=min(y(1).maxder,xsize);
      if (jmax>=jmin)
      {
        dmatrix tDux(1,usize,jmin,jmax);
        for (i=1;i<=usize;i++)
          for (j=jmin;j<=jmax;j++)
          {
            //Dux(i,j)=y(i+xsize).u_bar[j-1];
            tDux(i,j)=y(i+xsize).u_bar[j-1];
          }

        send_int_to_master(1);
        send_dmatrix_to_master(tDux);
      }
      else
      {
        send_int_to_master(0);
      }
    }
    if (ip<num_der_blocks)
      f1b2gradlist->reset();
  }
  //cout << "Hess" << endl;
  //cout << Hess << endl;
  //cout << "Dux" << endl;
  //cout << setprecision(16) << Dux << endl;
}

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::default_calculations_parallel_slave
  (const dvector& _x,const double& _f,function_minimizer * pfmin)
{
  // for use when there is no separability
  ADUNCONST(dvector,x)
  ADUNCONST(double,f)
  int i,j;
  x=get_dvector_from_master();

  initial_params::set_inactive_only_random_effects();
  gradient_structure::set_NO_DERIVATIVES();
  initial_params::reset(x);    // get current x values into the model
  gradient_structure::set_YES_DERIVATIVES();

  initial_params::set_active_only_random_effects();
  int lmn_flag=0;
  if (!inner_lmnflag)
  {
    if (!ADqd_flag)
      uhat=get_uhat_quasi_newton(x,pfmin);
    else
      uhat=get_uhat_quasi_newton_qd(x,pfmin);
  }
  else
  {
    uhat=get_uhat_lm_newton(x,pfmin);
  }

  for (i=1;i<=xsize;i++)
  {
    y(i)=x(i);
  }
  for (i=1;i<=usize;i++)
  {
    y(i+xsize)=uhat(i);
  }
  //cout << y << endl;

  for(int ii=1;ii<=num_nr_iters;ii++)
  {
    {
      // test newton raphson
      Hess.initialize();
     cout << "Newton raphson " << ii << endl;
      get_newton_raphson_info_slave(pfmin);

      step=get_dvector_from_master();

      f1b2gradlist->reset();
      f1b2gradlist->list.initialize();
      f1b2gradlist->list2.initialize();
      f1b2gradlist->list3.initialize();
      f1b2gradlist->nlist.initialize();
      f1b2gradlist->nlist2.initialize();
      f1b2gradlist->nlist3.initialize();

      uhat+=step;

      evaluate_function(uhat,pfmin);
    }

    for (i=1;i<=usize;i++)
    {
      y(i+xsize)=uhat(i);
    }
  }

  get_second_ders_slave(xsize,usize,y,Hess,Dux,f1b2gradlist,pfmin,this);
  int sgn=0;

  //f=calculate_laplace_approximation(x,uhat,Hess,xadjoint,uadjoint,
   // Hessadjoint,pfmin);


  for (int ip=num_der_blocks;ip>=1;ip--)
  {
    df1b2variable::minder=minder(ip);
    df1b2variable::maxder=maxder(ip);
    int mind=y(1).minder;
    int jmin=max(mind,xsize+1);
    int jmax=min(y(1).maxder,xsize+usize);
    dmatrix Hessadjoint=get_dmatrix_from_master();
    //for (i=1;i<=usize;i++)

    if (initial_df1b2params::separable_flag)
    {
      for (j=1;j<=xsize+usize;j++)
      {
        *y(j).get_u_tilde()=0;
      }
      Hess.initialize();
      initial_df1b2params::separable_calculation_type=3;
      pfmin->user_function();
    }
    else
    {
      if (ip<num_der_blocks)
      {
        f1b2gradlist->reset();
        set_u_dot(ip);
        df1b2_gradlist::set_yes_derivatives();
        (*re_objective_function_value::pobjfun)=0;
        df1b2variable pen=0.0;
        df1b2variable zz=0.0;

        initial_df1b2params::reset(y,pen);
        pfmin->user_function();
        (*re_objective_function_value::pobjfun)+=pen;
        (*re_objective_function_value::pobjfun)+=zz;

        set_dependent_variable(*re_objective_function_value::pobjfun);
        df1b2_gradlist::set_no_derivatives();
        df1b2variable::passnumber=1;
        df1b2_gradcalc1();
      }

      for (i=1;i<=usize;i++)
      {
        for (j=1;j<=usize;j++)
        {
          y(i+xsize).get_u_bar_tilde()[j-mind]=0;
        }
      }

      for (i=1;i<=usize;i++)
      {
        for (j=jmin;j<=jmax;j++)
        {
          //Hess(i,j-xsize)=y(i+xsize).u_bar[j-mind];
          y(i+xsize).get_u_bar_tilde()[j-mind]=Hessadjoint(i,j-xsize);
        }
      }

      int mind=y(1).minder;
      df1b2variable::passnumber=2;
      df1b2_gradcalc1();

      df1b2variable::passnumber=3;
      df1b2_gradcalc1();

      f1b2gradlist->reset();
      f1b2gradlist->list.initialize();
      f1b2gradlist->list2.initialize();
      f1b2gradlist->list3.initialize();
      f1b2gradlist->nlist.initialize();
      f1b2gradlist->nlist2.initialize();
      f1b2gradlist->nlist3.initialize();
    }

    dvector dtmp(1,xsize);
    for (i=1;i<=xsize;i++)
    {
      dtmp(i)=*y(i).get_u_tilde();
    }
    if (initial_df1b2params::separable_flag)
    {
      dvector scale(1,nvar);   // need to get scale from somewhere
      int check=initial_params::stddev_scale(scale,x);
      dvector sscale=scale(1,Dux(1).indexmax());
      for (i=1;i<=usize;i++)
      {
        Dux(i)=elem_prod(Dux(i),sscale);
      }
      dtmp=elem_prod(dtmp,sscale);
    }

    send_dvector_to_master(dtmp);
    dvector utmp(1,usize);
    for (i=1;i<=usize;i++)
    {
      utmp(i)=*y(i+xsize).get_u_tilde();
    }
    send_dvector_to_master(utmp);
  }
}

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::get_newton_raphson_info_slave
  (function_minimizer * pfmin)
{
  int i,j,ip;

  for (ip=1;ip<=num_der_blocks;ip++)
  {
    df1b2variable::minder=minder(ip);
    df1b2variable::maxder=maxder(ip);

    set_u_dot(ip);

    // do we need to reallocate memory for df1b2variables?
    check_for_need_to_reallocate(ip);
    df1b2_gradlist::set_yes_derivatives();
    //cout << re_objective_function_value::pobjfun << endl;
    //cout << re_objective_function_value::pobjfun->ptr << endl;
    (*re_objective_function_value::pobjfun)=0;
    df1b2variable pen=0.0;
    df1b2variable zz=0.0;
    initial_df1b2params::reset(y,pen);
    if (initial_df1b2params::separable_flag)
    {
      Hess.initialize();
      grad.initialize();
    }
    pfmin->user_function();
    (*re_objective_function_value::pobjfun)+=pen;
    (*re_objective_function_value::pobjfun)+=zz;
    //for (j=0;j<xsize+usize;j++)
     // cout << re_objective_function_value::pobjfun->u_dot[j] << " ";

    if (!initial_df1b2params::separable_flag)
    {
      set_dependent_variable(*re_objective_function_value::pobjfun);
      df1b2_gradlist::set_no_derivatives();
      df1b2variable::passnumber=1;
      df1b2_gradcalc1();
      int mind=y(1).minder;
      int jmin=max(mind,xsize+1);
      int jmax=min(y(1).maxder,xsize+usize);
      dmatrix tHess(1,usize,jmin,jmax);
      dvector tgrad(jmin,jmax);
      for (i=1;i<=usize;i++)
        for (j=jmin;j<=jmax;j++)
        {
          //Hess(i,j-xsize)=y(i+xsize).u_bar[j-mind];
          tHess(i,j)=y(i+xsize).u_bar[j-mind];
        }

      for (j=jmin;j<=jmax;j++)
      {
        //grad(j-xsize)= re_objective_function_value::pobjfun->u_dot[j-mind];
        tgrad(j)= re_objective_function_value::pobjfun->u_dot[j-mind];
      }
      send_dmatrix_to_master(tHess);
      send_dvector_to_master(tgrad);
    }
    if (ip<num_der_blocks)
      f1b2gradlist->reset();
  }
  {
    //for (j=0;j<xsize+usize;j++)
    //  cout << re_objective_function_value::pobjfun->u_dot[j] << " ";
    //cout << endl;
    //ofstream ofs("hess.tmp");
    //cout << Hess << endl;
    //cout << grad << endl;
  }
}
#else
void laplace_approximation_calculator::default_calculations_parallel_slave
  (const dvector& _x,const double& _f,function_minimizer * pfmin){}
void laplace_approximation_calculator::get_newton_raphson_info_slave
  (function_minimizer * pfmin){}
#endif  // #if defined(USE_ADPVM)

#endif //#if defined(USE_LAPLACE)
