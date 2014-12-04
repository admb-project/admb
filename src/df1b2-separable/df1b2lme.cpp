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
#  include <admodel.h>
#  include <df1b2fun.h>
#  include <adrndeff.h>

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::get_hessian_components_banded_lme
  (function_minimizer * pfmin)
{
  int mmin=variance_components_vector->indexmin();
  int mmax=variance_components_vector->indexmax();
  dmatrix *tmpHess=0;
  switch(hesstype)
  {
  case 3:
    cerr << "error -- Has not been impelmented" << endl;
    ad_exit(1);
    break;
  case 4:
    if (Hess_components==0)
    {
      int umin=Hess.indexmin();
      int umax=Hess.indexmax();
      tmpHess=new dmatrix(umin,umax,umin,umax);
      Hess_components=new d3_array(mmin,mmax,umin,umax,umin,umax);
      if (tmpHess==0 || Hess_components==0)
      {
        cerr << "error allocating memory" << endl;
        ad_exit(1);
      }
      df1b2_gradlist::set_no_derivatives();
      int nvar=initial_params::nvarcalc_all();
      dvector x(1,nvar);
      initial_params::xinit_all(x);
      initial_df1b2params::reset_all(x);
      for (int i=1;i<=nvar;i++) y(i)=x(i);
      step=get_newton_raphson_info_banded(pfmin);
      *tmpHess=Hess;
    }
    break;
  default:
    cerr << "Illegal value for hesstype here" << endl;
    ad_exit(1);
  }

  dvector df0=exp(-2.0*value(*variance_components_vector));

  dvector vsave(mmin,mmax);
  vsave=value(*variance_components_vector);
  for(int ic=mmin;ic<=mmax;ic++)
  {
    (*variance_components_vector)(ic)+=0.2;

    // test newton raphson
    switch(hesstype)
    {
    case 3:
      bHess->initialize();
      break;
    case 4:
      Hess.initialize();
      break;
    default:
      cerr << "Illegal value for hesstype here" << endl;
      ad_exit(1);
    }

    df1b2_gradlist::set_no_derivatives();
    int nvar=initial_params::nvarcalc_all();
    dvector x(1,nvar);
    initial_params::xinit_all(x);
    initial_df1b2params::reset_all(x);
    for (int i=1;i<=nvar;i++) y(i)=x(i);
    step=get_newton_raphson_info_banded(pfmin);

    switch(hesstype)
    {
    case 3:
      cerr << "error -- Has not been impelmented" << endl;
      ad_exit(1);
      //(*bHess_components)(ic)= *bHess;
      break;
    case 4:
      if (!tmpHess)
      {
        throw std::bad_alloc();
      }
      else
      {
        if (var_flag==1)
        {
          (*Hess_components)(ic)= (Hess-*tmpHess)/0.2;
        }
        else
        {
          double dfp=
          exp(-2.0*value(*variance_components_vector)(ic));
          (*Hess_components)(ic)= (Hess-*tmpHess)/(dfp-df0(ic));
        }
        (*variance_components_vector)(ic)-=0.2;
      }
      break;
    default:
      cerr << "Illegal value for hesstype here" << endl;
      ad_exit(1);
    }
  }
  *variance_components_vector=vsave;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix laplace_approximation_calculator::get_hessian_from_components_lme
  (function_minimizer * pfmin)
{
  int mmin=variance_components_vector->indexmin();
  int mmax=variance_components_vector->indexmax();

  initial_params::set_inactive_only_random_effects();
  independent_variables xx(1,mmax-mmin+1);
  initial_params::xinit(xx);    // get the initial values into the
  dvar_vector vxx=dvar_vector(xx);
  initial_params::reset(vxx);    // get current x values into the model
  int umin=Hess.indexmin();
  int umax=Hess.indexmax();
  dvar_matrix vHess(umin,umax,umin,umax);
  vHess.initialize();
  switch(hesstype)
  {
  case 3:
    cerr << "error -- Has not been impelmented" << endl;
    ad_exit(1);
    break;
  case 4:
    {
      for(int ic=mmin;ic<=mmax;ic++)
      {
        if (var_flag==1)
        {
          vHess+=
            (*variance_components_vector)(ic)*((*Hess_components)(ic));
        }
        else
        {
          vHess+= exp(-2.0*(*variance_components_vector)(ic))*
            ((*Hess_components)(ic));
        }
      }
    }
    break;
  default:
    cerr << "Illegal value for hesstype here" << endl;
    ad_exit(1);
  }
  return vHess;
}


/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::banded_calculations_lme
  (const dvector& _x,const double& _f,function_minimizer * pfmin)
{
  // for use when there is no separability
  ADUNCONST(dvector,x)
  ADUNCONST(double,f)
  //int i,j;

  initial_params::set_inactive_only_random_effects();
  gradient_structure::set_NO_DERIVATIVES();
  initial_params::reset(x);    // get current x values into the model
  gradient_structure::set_YES_DERIVATIVES();

  initial_params::set_active_only_random_effects();
  dvector g=get_gradient_lme(pfmin);

  reset_gradient_stack();
  // this is the main loop to do inner optimization
  //for (i=1;i<=xsize;i++) { y(i)=x(i); }
  //for (i=1;i<=usize;i++) { y(i+xsize)=uhat(i); }

  dvar_matrix vHess=get_hessian_from_components_lme(pfmin);
  //cout << setprecision(12) << "norm(vHess) = " << norm(value(vHess)) << endl;

  dvariable ld;
  dvariable tmp=0.0;
  dvariable sgn;

  dvector step=value(solve(vHess,g,tmp,sgn));
  if (value(sgn)<=0)
  {
    cerr << "sgn sucks" << endl;
  }
  int mmin=variance_components_vector->indexmin();
  int mmax=variance_components_vector->indexmax();
  int nv=mmax-mmin+1;
  dvector g1(1,nv);
  ld=0.5*tmp;
  gradcalc(nv,g1);
  uhat-=step;

  initial_params::set_active_only_random_effects();
  double maxg=max(fabs(get_gradient_lme(uhat,pfmin)));
  if (maxg > 1.e-12)
  {
    cout << "max g = " << maxg << endl;
  }

  double f2=0.0;
  dvector g2=get_gradient_lme_hp(f2,pfmin);
  f=f2+value(ld);
  return g1+g2;
}

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::get_gradient_lme
  (function_minimizer * pfmin)
{
  dvector g(1,usize);
  dvector ub(1,usize);
  independent_variables u(1,usize);
  gradcalc(0,g);
  initial_params::xinit(u);    // get the initial values into the
  uhat=u;

  dvariable pen=0.0;
  dvariable vf=0.0;
  pen=initial_params::reset(dvar_vector(u));
  *objective_function_value::pobjfun=0.0;
  pfmin->AD_uf_inner();
  vf+=*objective_function_value::pobjfun;

  objective_function_value::fun_without_pen=value(vf);
  vf+=pen;
  gradcalc(usize, g, vf);
  return g;
}

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::get_gradient_lme
  (const dvector& x,function_minimizer * pfmin)
{
  dvector g(1,usize);
  dvector ub(1,usize);
  independent_variables u(1,usize);
  u=x;
  gradcalc(0,g);

  dvariable pen=0.0;
  dvariable vf=0.0;
  pen=initial_params::reset(dvar_vector(u));
  *objective_function_value::pobjfun=0.0;
  pfmin->AD_uf_inner();
  vf+=*objective_function_value::pobjfun;

  objective_function_value::fun_without_pen=value(vf);
  vf+=pen;
  gradcalc(usize, g, vf);
  return g;
}

/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::get_gradient_lme_hp
  (const double& _f,function_minimizer * pfmin)
{
  ADUNCONST(double,f)
  //double fb=1.e+100;
  dvector g(1,xsize);
  dvector ub(1,xsize);
  independent_variables u(1,xsize);
  //gradcalc(xsize,g);
  initial_params::restore_start_phase();
  initial_params::set_inactive_random_effects();
  initial_params::xinit(u);    // get the initial values into the

  dvariable pen=0.0;
  dvariable vf=0.0;
  pen=initial_params::reset(dvar_vector(u));
  *objective_function_value::pobjfun=0.0;
  pfmin->AD_uf_inner();
  vf+=*objective_function_value::pobjfun;

  objective_function_value::fun_without_pen=value(vf);
  vf+=pen;
  f=value(vf);
  gradcalc(xsize,g);
  return g;
}
