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
#include <fvar.hpp>
#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h>
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif
double evaluate_function(const dvector& x,function_minimizer * pfmin);
void get_second_ders(int xs,int us,const init_df1b2vector y,dmatrix& Hess,
  dmatrix& Dux, df1b2_gradlist * f1b2gradlist,function_minimizer * pfmin,
  laplace_approximation_calculator* lap);
double calculate_laplace_approximation(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);

double calculate_importance_sample(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);

double calculate_importance_sample_funnel(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);

dmatrix choleski_decomp_positive(const dmatrix& M,double b);

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::
  check_derivatives(const dvector& _x,function_minimizer * pfmin,double f)
{
  cerr << "need to define this" << endl;
  ad_exit(1);
}

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::
  default_calculations_check_derivatives(const dvector& _x,
    function_minimizer * pfmin, const double& _f)
{
  // for use when there is no separability
  ADUNCONST(dvector,x)
  int i,j;
  double& f = (double&)_f;

  initial_params::set_inactive_only_random_effects();
  gradient_structure::set_NO_DERIVATIVES();
  initial_params::reset(x);    // get current x values into the model


  pfmin->AD_uf_inner();
  double fval1=value(*objective_function_value::pobjfun);

  gradient_structure::set_YES_DERIVATIVES();

  initial_params::set_active_only_random_effects();
  initial_params::xinit(uhat);    // get current x values into the model
  //int lmn_flag=0;
  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm1)
    {
      ad_comm::ptm1->get_elapsed_time_and_reset();
    }
    if (ad_comm::ptm)
    {
      ad_comm::ptm->get_elapsed_time_and_reset();
    }
  }
  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << " Time pos 0 "
          << time << endl;
      }
    }
  }

  double maxg = 0;
  dvector uhat_old(1,usize);
  //double f_from_1=0.0;

  for (i=1;i<=xsize;i++)
  {
    y(i)=x(i);
  }
  for (i=1;i<=usize;i++)
  {
    y(i+xsize)=uhat(i);
  }

  int ierr=0;
  int niters=0;
  if (function_minimizer::first_hessian_flag)
    niters=num_nr_iters+1;
  else
    niters=num_nr_iters;

  int nv=0;
  if (quadratic_prior::get_num_quadratic_prior()>0)
  {
    nv=initial_df1b2params::set_index();
    if (allocated(used_flags))
    {
      if (used_flags.indexmax() != nv)
      {
        used_flags.safe_deallocate();
      }
    }
    if (!allocated(used_flags))
    {
      used_flags.safe_allocate(1,nv);
    }
  }

  for(int ii=1;ii<=niters;ii++)
  {
    if (quadratic_prior::get_num_quadratic_prior()>0)
    {
      check_pool_size();
    }
    {
      // test newton raphson
      Hess.initialize();
      cout << "Checking derivatives " << ii << endl;
      check_derivatives(x,pfmin,fval1);

      if (quadratic_prior::get_num_quadratic_prior()>0)
      {
        laplace_approximation_calculator::where_are_we_flag=2;
        /*double maxg = */evaluate_function_quiet(uhat,pfmin);
        laplace_approximation_calculator::where_are_we_flag=0;
        quadratic_prior::get_cHessian_contribution(Hess,xsize);
        quadratic_prior::get_cgradient_contribution(grad,xsize);
      }

      /*
      if (ii == 1)
        { double diff = fabs(re_objective_function_value::fun_without_pen - objective_function_value::fun_without_pen); }
      */

#ifdef DIAG
      int print_hess_in_newton_raphson_flag=0;
      if (print_hess_in_newton_raphson_flag)
      {
        cout << norm2(Hess-trans(Hess)) << endl;
        if (ad_comm::global_logfile)
        {
          (*ad_comm::global_logfile) << setprecision(4) << setscientific()
            << setw(12) << sort(eigenvalues(Hess)) << endl;
          (*ad_comm::global_logfile) << setprecision(4) << setscientific()
            << setw(12) << Hess << endl;
        }
      }
#endif

      dvector step;
#if defined(USE_ATLAS)
      if (!ad_comm::no_atlas_flag)
      {
        step=-atlas_solve_spd(Hess,grad,ierr);
      }
      else
      {
        dmatrix A=choleski_decomp_positive(Hess,ierr);
        if (!ierr)
        {
          step=-solve(Hess,grad);
          //step=-solve(A*trans(A),grad);
        }
      }
      if (ierr)
      {
        f1b2gradlist->reset();
        f1b2gradlist->list.initialize();
        f1b2gradlist->list2.initialize();
        f1b2gradlist->list3.initialize();
        f1b2gradlist->nlist.initialize();
        f1b2gradlist->nlist2.initialize();
        f1b2gradlist->nlist3.initialize();
        break;
      }
#else
      step=-solve(Hess,grad);
#endif

      if (ad_comm::time_flag)
      {
        if (ad_comm::ptm)
        {
          double time=ad_comm::ptm->get_elapsed_time_and_reset();
          if (ad_comm::global_logfile)
          {
            (*ad_comm::global_logfile) << " time_in solve " <<  ii << "  "
              << time << endl;
          }
        }
      }

      f1b2gradlist->reset();
      f1b2gradlist->list.initialize();
      f1b2gradlist->list2.initialize();
      f1b2gradlist->list3.initialize();
      f1b2gradlist->nlist.initialize();
      f1b2gradlist->nlist2.initialize();
      f1b2gradlist->nlist3.initialize();

      uhat_old=uhat;
      uhat+=step;

      double maxg_old=maxg;
      maxg=fabs(evaluate_function(uhat,pfmin));
      if (maxg>maxg_old)
      {
        uhat=uhat_old;
        evaluate_function(uhat,pfmin);
        break;
      }
      if (maxg < 1.e-13)
      {
        break;
      }
    }
    for (i=1;i<=usize;i++)
    {
      y(i+xsize)=uhat(i);
    }
  }

  if (num_nr_iters<=0)
  {
    evaluate_function(uhat,pfmin);
  }

  for (i=1;i<=usize;i++)
  {
    y(i+xsize)=uhat(i);
  }


  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time_and_reset();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << " Time in reset and evaluate function"
          << time << endl;
      }
    }
  }
  get_second_ders(xsize,usize,y,Hess,Dux,f1b2gradlist,pfmin,this);
  //int sgn=0;

  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time_and_reset();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << " Time in dget second ders "
          << time << endl;
      }
    }
  }
  if (!ierr)
  {
    if (num_importance_samples==0)
    {
      //cout << "Hess " << endl << Hess << endl;
      f=calculate_laplace_approximation(x,uhat,Hess,xadjoint,uadjoint,
        Hessadjoint,pfmin);
    }
    else
    {
      if (isfunnel_flag==0)
      {
        f=calculate_importance_sample(x,uhat,Hess,xadjoint,uadjoint,
          Hessadjoint,pfmin);
      }
      else
      {
        f=calculate_importance_sample_funnel(x,uhat,Hess,xadjoint,uadjoint,
          Hessadjoint,pfmin);
      }
    }
  }
  else
  {
    f=1.e+30;
  }

  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time_and_reset();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << "Time in calculate laplace approximation "
          << time << endl;
      }
    }
  }

  for (int ip=num_der_blocks;ip>=1;ip--)
  {
    df1b2variable::minder=minder(ip);
    df1b2variable::maxder=maxder(ip);
    int mind=y(1).minder;
    int jmin=max(mind,xsize+1);
    int jmax=min(y(1).maxder,xsize+usize);
    for (i=1;i<=usize;i++)
    {
      for (j=jmin;j<=jmax;j++)
      {
        //Hess(i,j-xsize)=y(i+xsize).u_bar[j-mind];
        y(i+xsize).get_u_bar_tilde()[j-mind]=Hessadjoint(i,j-xsize);
      }
    }

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

        re_objective_function_value::fun_without_pen=
          value(*re_objective_function_value::pobjfun);

        (*re_objective_function_value::pobjfun)+=pen;
        (*re_objective_function_value::pobjfun)+=zz;

        set_dependent_variable(*re_objective_function_value::pobjfun);
        df1b2_gradlist::set_no_derivatives();
        df1b2variable::passnumber=1;
        df1b2_gradcalc1();
      }

      for (i=1;i<=usize;i++)
      {
        for (j=jmin;j<=jmax;j++)
        {
          //Hess(i,j-xsize)=y(i+xsize).u_bar[j-mind];
          y(i+xsize).get_u_bar_tilde()[j-mind]=Hessadjoint(i,j-xsize);
        }
      }

      //int mind=y(1).minder;
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

    if (ad_comm::time_flag)
    {
      if (ad_comm::ptm)
      {
        double time=ad_comm::ptm->get_elapsed_time_and_reset();
        if (ad_comm::global_logfile)
        {
          (*ad_comm::global_logfile) << " time for 3rd derivatives "
            << time << endl;
        }
      }
    }

    dvector dtmp(1,xsize);
    for (i=1;i<=xsize;i++)
    {
      dtmp(i)=*y(i).get_u_tilde();
    }
    if (initial_df1b2params::separable_flag)
    {
#ifndef OPT_LIB
      assert(nvar <= INT_MAX);
#endif
      dvector scale(1,(int)nvar);   // need to get scale from somewhere
      /*int check=*/initial_params::stddev_scale(scale,x);
      dvector sscale=scale(1,Dux(1).indexmax());
      for (i=1;i<=usize;i++)
      {
        Dux(i)=elem_prod(Dux(i),sscale);
      }
      dtmp=elem_prod(dtmp,sscale);
    }

    for (i=1;i<=xsize;i++)
    {
      xadjoint(i)+=dtmp(i);
    }
    for (i=1;i<=usize;i++)
      uadjoint(i)+=*y(xsize+i).get_u_tilde();
  }
 // *****************************************************************
 // new stuff to deal with quadraticprior
 // *****************************************************************

    int xstuff=3;
    if (xstuff && df1b2quadratic_prior::get_num_quadratic_prior()>0)
    {
      initial_params::straight_through_flag=0;
      funnel_init_var::lapprox=0;
      block_diagonal_flag=0;
#ifndef OPT_LIB
      assert(nvar <= INT_MAX);
#endif
      dvector scale1(1,(int)nvar);   // need to get scale from somewhere
      initial_params::set_inactive_only_random_effects();
      /*int check=*/initial_params::stddev_scale(scale1,x);

      laplace_approximation_calculator::where_are_we_flag=3;
      quadratic_prior::in_qp_calculations=1;
      funnel_init_var::lapprox=this;
      df1b2_gradlist::set_no_derivatives();
      dvector scale(1,(int)nvar);   // need to get scale from somewhere
      /*check=*/initial_params::stddev_scale(scale,x);
      dvector sscale=scale(1,Dux(1).indexmax());

      for (i=1;i<=usize;i++)
      {
        Dux(i)=elem_div(Dux(i),sscale);
      }

      if (xstuff>1)
      {
        df1b2quadratic_prior::get_Lxu_contribution(Dux);
      }
      quadratic_prior::in_qp_calculations=0;
      funnel_init_var::lapprox=0;
      laplace_approximation_calculator::where_are_we_flag=0;

      for (i=1;i<=usize;i++)
      {
        Dux(i)=elem_prod(Dux(i),sscale);
      }
      //local_dtemp=elem_prod(local_dtemp,sscale);

      if (xstuff>2)
      {
        dvector tmp=evaluate_function_with_quadprior(x,usize,pfmin);
        for (i=1;i<=xsize;i++)
        {
          xadjoint(i)+=tmp(i);
        }
      }

      if (xstuff>2)
      {
        quadratic_prior::get_cHessian_contribution_from_vHessian(Hess,xsize);
      }
    }

 // *****************************************************************
 // new stuff to deal with quadraticprior
 // *****************************************************************
  if (ad_comm::ptm)
  {
    /*double time=*/ad_comm::ptm->get_elapsed_time_and_reset();
  }

#if defined(USE_ATLAS)
      if (!ad_comm::no_atlas_flag)
      {
        //xadjoint -= uadjoint*atlas_solve_spd_trans(Hess,Dux);
        xadjoint -= atlas_solve_spd_trans(Hess,uadjoint)*Dux;
      }
      else
      {
        //xadjoint -= uadjoint*solve(Hess,Dux);
        xadjoint -= solve(Hess,uadjoint)*Dux;
      }
#else
      //xadjoint -= uadjoint*solve(Hess,Dux);
      xadjoint -= solve(Hess,uadjoint)*Dux;
#endif


  if (ad_comm::ptm)
  {
    double time=ad_comm::ptm->get_elapsed_time_and_reset();
    if (ad_comm::global_logfile)
    {
      (*ad_comm::global_logfile) << " Time in second solve "
        << time << endl;
    }
  }
  if (ad_comm::ptm1)
  {
    double time=ad_comm::ptm1->get_elapsed_time_and_reset();
    if (ad_comm::global_logfile)
    {
      (*ad_comm::global_logfile) << " Total time in function evaluation "
        << time << endl << endl;
    }
  }

  return xadjoint;
}
