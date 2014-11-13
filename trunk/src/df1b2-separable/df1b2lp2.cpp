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
#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h>
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif
void get_second_ders(int xs,int us,const init_df1b2vector y,dmatrix& Hess,
  dmatrix& Dux, df1b2_gradlist * f1b2gradlist,function_minimizer * pfmin,
  laplace_approximation_calculator* lap);
double calculate_laplace_approximation(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);

static void xxx(ivector re_list,ivector fe_list){}

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::block_diagonal_calculations
  (const dvector& _x,const double& _f,function_minimizer * pfmin)
{
  // for use when there is no separability
  ADUNCONST(dvector,x)
  ADUNCONST(double,f)

  initial_params::set_inactive_only_random_effects();
  gradient_structure::set_NO_DERIVATIVES();
  initial_params::reset(x);    // get current x values into the model
  gradient_structure::set_YES_DERIVATIVES();

  initial_params::set_active_only_random_effects();
  //int lmn_flag=0;
  if (!inner_lmnflag)
  {
    if (!ADqd_flag)
      uhat=get_uhat_quasi_newton_block_diagonal(x,pfmin);
    else
      uhat=get_uhat_quasi_newton_qd(x,pfmin);
  }
  else
  {
    uhat=get_uhat_lm_newton(x,pfmin);
  }
  if (!allocated(scale))
  {
    scale.allocate(1,uhat.indexmax());
  }
  else
  {
    if (scale.indexmax() != uhat.indexmax())
    {
      scale.deallocate();
      scale.allocate(1,uhat.indexmax());
    }
  }

  if (!allocated(curv))
  {
    curv.allocate(1,uhat.indexmax());
  }
  else
  {
    if (curv.indexmax() != uhat.indexmax())
    {
      curv.deallocate();
      curv.allocate(1,uhat.indexmax());
    }
  }

  if (sparse_hessian_flag==0)
  {
    for (int i=1;i<=xsize;i++)
    {
      y(i)=x(i);
    }
    for (int i=1;i<=usize;i++)
    {
      y(i+xsize)=uhat(i);
    }
  }
  else
  {
    for (int i=1;i<=xsize;i++)
    {
      value(y(i))=x(i);
    }
    for (int i=1;i<=usize;i++)
    {
      value(y(i+xsize))=uhat(i);
    }
  }

  for(int ii=1;ii<=num_nr_iters;ii++)
  {
    {
      // test newton raphson
      //Hess.initialize();
      /*int check=*/initial_params::stddev_scale(scale,uhat);
      /*check=*/initial_params::stddev_curvscale(curv,uhat);
      max_separable_g=0.0;
      pmin->inner_opt_flag=1;
      step=get_newton_raphson_info_block_diagonal(pfmin);
      cout << "max separable g " << max_separable_g << endl;
      cout << "Newton raphson " << ii << endl;
      uhat+=step;

      evaluate_function(uhat,pfmin);
      pmin->inner_opt_flag=0;
    }

    if (sparse_hessian_flag==0)
    {
      for (int i=1;i<=usize;i++)
      {
        y(i+xsize)=uhat(i);
      }
    }
    else
    {
      for (int i=1;i<=usize;i++)
      {
        value(y(i+xsize))=uhat(i);
      }
    }
  }

  cout << initial_df1b2params::cobjfun << endl;
  xadjoint.initialize();
  uadjoint.initialize();
  block_diagonal_flag=2;
  used_flags.initialize();
  funnel_init_var::lapprox=this;
  if (use_gauss_hermite>0)
  {
    df1b2variable pen=0.0;
    initial_df1b2params::reset(y,pen);
    initial_params::straight_through_flag=0;
    block_diagonal_flag=6;
    num_separable_calls=0;
    // get the block diagonal hessians to use in importance sampling
    pfmin->user_function();
    //cout << (*pfmin->lapprox->block_diagonal_hessian) << endl;
    block_diagonal_flag=2;
    initial_params::straight_through_flag=0;

    // do importance sampling and get ders bakc to Hessian adjoint
    // new stuff for more than one random effect in each separable call
    //  Apr 17 07
    if (multi_random_effects==0)
    {
      f=do_gauss_hermite_block_diagonal(x,uhat,Hess,xadjoint,
        uadjoint,Hessadjoint,pfmin);
    }
    else
    {
      f=do_gauss_hermite_block_diagonal_multi(x,uhat,Hess,xadjoint,
        uadjoint,Hessadjoint,pfmin);
    }
    int xmax=xadjoint.indexmax();
    dvector x_con(1,xmax);
    x_con.initialize();
#ifndef OPT_LIB
    assert(nvar <= INT_MAX);
#endif
    dvector dscale(1,(int)nvar);   // need to get scale from somewhere
    dscale=1.0;
    /*int check=*/initial_params::stddev_scale(dscale,x);
    dvector sscale=dscale(1,xsize);
    // *******************************************************
    // *******************************************************
    // *******************************************************
    // derivatives from hessian adjoint back
    {
      x_con.initialize();

      for (int i=1;i<=num_separable_calls;i++)
      {
        ivector& re_list=(*block_diagonal_re_list)(i);
        ivector& fe_list=(*block_diagonal_fe_list)(i);
        dmatrix& Dux=(*block_diagonal_Dux)(i);
        dmatrix& H=(*block_diagonal_hessian)(i);
        xxx(re_list,fe_list);
        int mmax=re_list.indexmax();
        dvector tmp(1,mmax);

        for (int j=1;j<=re_list.indexmax();j++)
        {
          tmp(j)=uadjoint(re_list(j)-xmax);
        }

        if (allocated(fe_list))
        {
          if (allocated(H))
          {
            dvector tmp1=solve(H,tmp);
            dvector xtmp=tmp1*Dux;
            for (int j=1;j<=fe_list.indexmax();j++)
            {
              x_con(fe_list(j))+=xtmp(j);
            }
          }
        }
      }
      if (initial_df1b2params::separable_flag)
      {
        x_con=elem_prod(x_con,sscale);
      }
    }
    xadjoint-=x_con;
    // *******************************************************
    // *******************************************************
    // *******************************************************

    block_diagonal_flag=3;
    //pfmin->lapprox->xadjoint.initialize();
    //pfmin->lapprox->uadjoint.initialize();
    pfmin->lapprox->num_separable_calls=0;
    pfmin->lapprox->check_local_xadjoint.initialize();
    pfmin->lapprox->check_local_xadjoint2.initialize();
    pfmin->lapprox->check_local_uadjoint.initialize();
    pfmin->lapprox->check_local_uadjoint2.initialize();
    //df1b2_gradlist::set_yes_derivatives();
    //initial_df1b2params::reset(y,pen);
    pfmin->user_function();
    dvector lcx=elem_prod(check_local_xadjoint2,sscale);
    xadjoint+=lcx;
    //df1b2_gradlist::set_no_derivatives();
    funnel_init_var::lapprox=0;
    block_diagonal_flag=0;
    initial_params::set_inactive_only_random_effects();
  }
  else if (num_importance_samples>0)
  {
    df1b2variable pen=0.0;
    initial_df1b2params::reset(y,pen);
    initial_params::straight_through_flag=0;
    block_diagonal_flag=6;
    num_separable_calls=0;
    // get the block diagonal hessians to use in importance sampling
    pfmin->user_function();
    //cout << (*pfmin->lapprox->block_diagonal_hessian) << endl;
    block_diagonal_flag=2;
    initial_params::straight_through_flag=0;
    // do importance sampling and get ders bakc to Hessian adjoint
    if (isfunnel_flag==0)
    {
      if (antiflag==0)
      {
        f=calculate_importance_sample_block_diagonal_option2(x,uhat,Hess,
          xadjoint,uadjoint,Hessadjoint,pfmin);
      }
      else
      {
        f=calculate_importance_sample_block_diagonal_option_antithetical(x,
          uhat,Hess,xadjoint,uadjoint,Hessadjoint,pfmin);
      }
    }
    else
    {
      f=calculate_importance_sample_block_diagonal_funnel(x,uhat,Hess,xadjoint,
        uadjoint,Hessadjoint,pfmin);
    }

    int xmax=xadjoint.indexmax();
    dvector x_con(1,xmax);
    x_con.initialize();
#ifndef OPT_LIB
    assert(nvar <= INT_MAX);
#endif
    dvector dscale(1,(int)nvar);   // need to get scale from somewhere
    dscale=1.0;
    /*int check=*/initial_params::stddev_scale(dscale,x);
    dvector sscale=dscale(1,xsize);
    // *******************************************************
    // *******************************************************
    // *******************************************************
    // derivatives from hessian adjoint back
    {
      x_con.initialize();

      for (int i=1;i<=num_separable_calls;i++)
      {
        dmatrix& H=(*block_diagonal_hessian)(i);
        if (allocated(H))
        {
          ivector& re_list=(*block_diagonal_re_list)(i);
          ivector& fe_list=(*block_diagonal_fe_list)(i);
          dmatrix& Dux=(*block_diagonal_Dux)(i);
          xxx(re_list,fe_list);
          int mmax=re_list.indexmax();
          dvector tmp(1,mmax);

          for (int j=1;j<=re_list.indexmax();j++)
          {
            tmp(j)=uadjoint(re_list(j)-xmax);
          }

          if (allocated(fe_list))
          {
            dvector tmp1=solve(H,tmp);
            dvector xtmp=tmp1*Dux;
            for (int j=1;j<=fe_list.indexmax();j++)
            {
              x_con(fe_list(j))+=xtmp(j);
            }
          }
        }
      }
      if (initial_df1b2params::separable_flag)
      {
        //for (i=1;i<=usize;i++)
        //{
        //  Dux(i)=elem_prod(Dux(i),sscale);
        //}
        x_con=elem_prod(x_con,sscale);
      }
    }
    xadjoint-=x_con;
    // *******************************************************
    // *******************************************************
    // *******************************************************

    block_diagonal_flag=3;
    //pfmin->lapprox->xadjoint.initialize();
    //pfmin->lapprox->uadjoint.initialize();
    pfmin->lapprox->num_separable_calls=0;
    pfmin->lapprox->check_local_xadjoint.initialize();
    pfmin->lapprox->check_local_xadjoint2.initialize();
    pfmin->lapprox->check_local_uadjoint.initialize();
    pfmin->lapprox->check_local_uadjoint2.initialize();
    //df1b2_gradlist::set_yes_derivatives();
    //initial_df1b2params::reset(y,pen);
    pfmin->user_function();
    dvector lcx=elem_prod(check_local_xadjoint2,sscale);
    xadjoint+=lcx;
    //df1b2_gradlist::set_no_derivatives();
    funnel_init_var::lapprox=0;
    block_diagonal_flag=0;
    initial_params::set_inactive_only_random_effects();
  }
  else
  {
    if (function_minimizer::first_hessian_flag)
    {
      // need hessin of random effects for stddeV report
      df1b2variable pen=0.0;
      initial_df1b2params::reset(y,pen);
      initial_params::straight_through_flag=0;
      block_diagonal_flag=6;
      allocate_block_diagonal_stuff();
      num_separable_calls=0;
      // get the block diagonal hessians to use in importance sampling
      pfmin->user_function();
      //cout << (*pfmin->lapprox->block_diagonal_hessian) << endl;
      block_diagonal_flag=2;
    }
    initial_params::straight_through_flag=1;
    df1b2variable pen=0.0;
    if (saddlepointflag==2)
    {
      pmin->inner_opt_flag=0;
      f=get_fx_fu(pfmin);
    }
    initial_df1b2params::reset(y,pen);
    pmin->inner_opt_flag=1;
    pfmin->pre_user_function();
    pmin->inner_opt_flag=0;
    initial_params::straight_through_flag=0;
    if (saddlepointflag!=2)
    {
      f=initial_df1b2params::cobjfun;
    }
    else
    {
      xadjoint=(*grad_x_u)(1,xsize)-(*grad_x);
    }

    if (saddlepointflag!=2 && pmin->multinomial_weights==0)
    {
      f-=usize*.91893853320467241;
    }

    funnel_init_var::lapprox=0;
    block_diagonal_flag=0;
    dvector scale1(1,xsize);   // need to get scale from somewhere
    initial_params::set_inactive_only_random_effects();
    /*int check=*/initial_params::stddev_scale(scale1,x);
    for (int i=1;i<=xadjoint.indexmax();i++)
      xadjoint(i)*=scale1(i);
  }
  //cout << initial_df1b2params::cobjfun << endl;
  //f=initial_df1b2params::cobjfun;
  return xadjoint;
}

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::get_newton_raphson_info_block_diagonal
  (function_minimizer * pfmin)
{
  int nv=initial_df1b2params::set_index();
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

  //for (ip=1;ip<=num_der_blocks;ip++)
  {
    used_flags.initialize();

    // do we need to reallocate memory for df1b2variables?
    int ip = 0;
    check_for_need_to_reallocate(ip);

    df1b2_gradlist::set_no_derivatives();
    //cout << re_objective_function_value::pobjfun << endl;
    //cout << re_objective_function_value::pobjfun->ptr << endl;
    (*re_objective_function_value::pobjfun)=0;
    df1b2variable pen=0.0;
    df1b2variable zz=0.0;

    initial_df1b2params::reset(y,pen);

    // call function to do block diagonal newton-raphson
    // the step vector from the newton-raphson is in the vector step
    df1b2_gradlist::set_yes_derivatives();

    funnel_init_var::lapprox=this;
    //cout << funnel_init_var::lapprox << endl;
    block_diagonal_flag=1;
    pfmin->pre_user_function();
    //pfmin->user_function();
    funnel_init_var::lapprox=0;
    block_diagonal_flag=0;
  }
  return step;
}
