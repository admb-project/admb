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
#  include <fvar.hpp>
#  include <admodel.h>
#  include <df1b2fun.h>
#  include <adrndeff.h>
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

dmatrix choleski_decomp_positive(const dmatrix& M,double b);

//dvector laplace_approximation_calculator::default_calculations
 // (const dvector& _x,const double& _f,function_minimizer * pfmin)

#if defined(USE_ADPVM)
/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::test_trust_region_method
  (const dvector& _x,const double& _f,function_minimizer * pfmin)
{
  // for use when there is no separability
  ADUNCONST(dvector,x)
  //ADUNCONST(double,f)
  //int i,j;
  int i;

  initial_params::set_inactive_only_random_effects();
  gradient_structure::set_NO_DERIVATIVES();
  initial_params::reset(x);    // get current x values into the model
  gradient_structure::set_YES_DERIVATIVES();

 /*
  initial_params::set_active_only_random_effects();
  int lmn_flag=0;
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

  double maxg;
  double maxg_save;
  dvector uhat_old(1,usize);
  double f_from_1=0.0;
  if (!inner_lmnflag)
  {
    if (!ADqd_flag)
    {
      uhat=get_uhat_quasi_newton(x,pfmin);
      maxg=fabs(fmc1.gmax);
      f_from_1=fmc1.bestf;
    }
    else
      uhat=get_uhat_quasi_newton_qd(x,pfmin);
  }
  else
  {
    uhat=get_uhat_lm_newton(x,pfmin);
  }

  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      double time=ad_comm::ptm->get_elapsed_time_and_reset();
      if (ad_comm::global_logfile)
      {
        (*ad_comm::global_logfile) << " Time in inner optimization "
          << time << endl;
      }
    }
  }
 */
  for (i=1;i<=xsize;i++)
  {
    y(i)=x(i);
  }
  for (i=1;i<=usize;i++)
  {
    y(i+xsize)=uhat(i);
  }
  int n=xsize+usize;
  dvector xx(1,n);
  for (i=1;i<=n;i++)
  {
    xx(i)=value(y(i));
  }
  double bestf=do_one_feval(xx,pfmin);
  double Delta=10;
  double lambda;
  cout << "input Delta" << endl;
  cin >> Delta;
  cout << "input lambda" << endl;
  cin >> lambda;
  int outer_iter=0;
  int max_iteration=10;
  do
  {
    outer_iter++;
    //int ierr=0;
    //int niters=0;
    dvector g(1,n);
    dmatrix H(1,n,1,n);

    // test newton raphson
    get_complete_hessian(H,g,pfmin);

    double tol=1.e-6;
    //int itmax=1000;
    //int itol=1;
    //int iter=0;
    //double err=0;
    //lambda=1;

    //cout << "input Delta" << endl;
    //cin >> Delta;
    //cout << "input lambda" << endl;
    //cin >> lambda;

    int i;

    for (i=1;i<=n;i++)
    {
      H(i,i)+=lambda;
    }

    cout << "initial fun value - " << double(0.5)*xx*(H*xx)+xx*g;
    double truef=do_one_feval(xx,pfmin);
    cout << "real function value = " << truef << endl;
    double estdiff;
    double truediff;
    int iflag=0;
    int inner_iter=0;
    //int oldbest=(int)bestf;
    int maxfn=15;
    dvector xret=lincg(xx,g,H,tol,Delta,pfmin,truef,estdiff,
     truediff,bestf,iflag,inner_iter,maxfn);
    cout << " norm(g) = " << norm(g)
         << "  norm(H*xret+g) = " << norm(H*xret+g)
         << "  norm(H*xret-g) = " << norm(H*xret-g)
         << " inner_iter = " << inner_iter << endl;
    if (iflag==1)
    {
      Delta/=5.0;
    }
    for (i=1;i<=n;i++)
    {
      y(i)+=xret(i);
    }
    for (i=1;i<=n;i++)
    {
      xx(i)=value(y(i));
    }

    f1b2gradlist->reset();
    f1b2gradlist->list.initialize();
    f1b2gradlist->list2.initialize();
    f1b2gradlist->list3.initialize();
    f1b2gradlist->nlist.initialize();
    f1b2gradlist->nlist2.initialize();
    f1b2gradlist->nlist3.initialize();
  }
  while(outer_iter<=max_iteration);
  return xx;
}
#endif

/**
 * Description not yet available.
 * \param
 */
void laplace_approximation_calculator::get_complete_hessian
  (dmatrix& H,dvector& g,function_minimizer * pfmin)
{
  int i,j,ip;

  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
        (*ad_comm::global_logfile) << " Starting Newton-Raphson "
          <<  endl;
    }
  }

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
    (*re_objective_function_value::pobjfun)=double(0.0);

#if defined(USE_DDOUBLE)
#undef double
    df1b2variable pen=double(0.0);
    df1b2variable zz=double(0.0);
#define double dd_real
#else
    df1b2variable pen=0.0;
    df1b2variable zz=0.0;
#endif
    initial_df1b2params::reset(y,pen);
     //cout << setprecision(15) << y << endl;
    if (initial_df1b2params::separable_flag)
    {
      H.initialize();
      grad.initialize();
    }

    double time1 = 0;
    if (ad_comm::time_flag)
    {
      if (ad_comm::ptm)
      {
        time1=ad_comm::ptm->get_elapsed_time();
      }
    }

    pfmin->user_function();

    if (ad_comm::time_flag)
    {
      if (ad_comm::ptm)
      {
        if (ad_comm::global_logfile)
        {
          double time=ad_comm::ptm->get_elapsed_time();
          (*ad_comm::global_logfile) << "       Time in user_function() "
            <<  ip << "  " << time-time1 << endl;
        }
      }
    }

    re_objective_function_value::fun_without_pen
      =value(*re_objective_function_value::pobjfun);

    (*re_objective_function_value::pobjfun)+=pen;
    (*re_objective_function_value::pobjfun)+=zz;

    //cout << setprecision(15) << *re_objective_function_value::pobjfun << endl;
    //cout << setprecision(15) << pen << endl;
    if (!initial_df1b2params::separable_flag)
    {
      set_dependent_variable(*re_objective_function_value::pobjfun);
      df1b2_gradlist::set_no_derivatives();
      df1b2variable::passnumber=1;
      df1b2_gradcalc1();
      int mind=y(1).minder;
      int jmin=max(mind,1);
      int jmax=min(y(1).maxder,xsize+usize);
      for (i=1;i<=xsize+usize;i++)
        for (j=jmin;j<=jmax;j++)
          H(i,j)=y(i).u_bar[j-mind];

    // ****************************************************************
    // ****************************************************************
    // ****************************************************************
    // temporary shit
     /*
      for (i=1;i<=usize;i++)
      {
        for (j=jmin;j<=jmax;j++)
        {
          //Hess(i,j-xsize)=y(i+xsize).u_bar[j-mind];
          y(i+xsize).get_u_bar_tilde()[j-mind]=Hessadjoint(i,j-xsize);
        }
      }
      cout << Hess << endl;
      df1b2variable::passnumber=2;
      df1b2_gradcalc1();

      df1b2variable::passnumber=3;
      df1b2_gradcalc1();
     */
    // ****************************************************************
    // ****************************************************************
    // ****************************************************************
    // ****************************************************************
      for (j=jmin;j<=jmax;j++)
        g(j)= re_objective_function_value::pobjfun->u_dot[j-mind];
    }
    if (ip<num_der_blocks)
      f1b2gradlist->reset();
  }


  // just to match master pvm routine
  if (ad_comm::time_flag)
  {
    if (ad_comm::ptm)
    {
      /*double time=*/ad_comm::ptm->get_elapsed_time();
    }
  }
}



#define EPS 1.0e-14



/*
int main(int argc,char * argv[])
{
  int n=4;
  dmatrix H(1,n,1,n);

  double lambda;
  lambda=1.0;

  dvector g(1,n);
  dvector x(1,n);
  double tol=1.e-6;
  int itmax=1000;
  int itol=1;
  int iter=0;
  double err=0;
  double Delta=20;
  H.initialize();
  lambda=1;

  g=1.0;
  x=0.0;
  H(1,1)=1;
  H(2,2)=2;
  H(3,3)=3;
  H(4,4)=3;
  //cout << "input lambda" << endl;
  //cin >> lambda;

  for (int i=1;i<=n;i++)
  {
    H(i,i)+=lambda;
  }
  cout << "initial fun value - " << 0.5*x*(H*x)+x*g;
  double truef=do_one_feval(x_k,pfmin);
  cout << "real function value = " << truef << endl;
  dvector xret=lincg(x,g,H,tol,Delta,truef,estdiff);

  cout << H*xret << "   " <<  g << endl;
  exit(0);

}
*/

/*
dvector laplace_approximation_calculator::lincg(dvector& x,
  dvector& c, dmatrix& H,double tol,double Delta,function_minimizer * pfmin,
  double& truef,double& estdiff,double& truediff,double& bestf,
  int& iflag,int& inner_iter,int maxfn)
{
  iflag=0;
  int n=c.indexmax();
  dvector g_k(1,n);
  dvector p_k(1,n);
  dvector x_k(1,n);
  dvector xbest_k(1,n);
  double alpha_k;
  double beta_k;
  double n2gk=0.0;
  x_k=0.0;
  g_k=c;
  //g_k=H*x+c;
  p_k=-g_k;
  n2gk=norm2(g_k);
  int improve_flag=0;
  inner_iter=0;
  xbest_k=0;

  do
  {
    if (++inner_iter > maxfn)
      return xbest_k;

    dvector v=H*p_k;
    double tmp2=p_k*v;
    cout << tmp2 << endl;

    if  (tmp2 <=0.0)
    {
      cout << "matrix not positive definite " << tmp2 << endl;
     // find point at boubndary

     double a=norm2(p_k);
     double b=2.0*x_k*p_k;
     double cc=norm2(x_k)-square(Delta);
     double d=sqrt(b*b-4*a*cc);
     double r1=(-b+d)/(2.0*a);
     double r2=(-b-d)/(2.0*a);

     cout << " the roots are " << r1 << "  " << r2 << endl;
     if (r1>0)
     {
       x_k=x_k+r1*p_k;
     }
     else
     {
       x_k=x_k+r2*p_k;
     }
     cout << "function value = "  << 0.5*(x_k*(H*x_k)) + x_k*c <<
       " norm(x_k) =  " << norm(x_k) << endl;
     break;
    }

    alpha_k=n2gk/(tmp2);
    x_k+=alpha_k*p_k;

    double nxk=norm(x_k);
    if (nxk>Delta)
    {
      // we have goneoutside the trust region
      cout << " we have gone outside the trust region " << endl;
      // find point at boubndary

      double a=norm2(p_k);
      double b=2.0*x_k*p_k;
      double cc=norm2(x_k)-square(Delta);
      double d=b*b-4*a*cc;
      if (d<0)
        cout <<" d = " << d << endl;
      d=sqrt(d);
      double r1=(-b+d)/(2.0*a);
      double r2=(-b-d)/(2.0*a);

      cout << " the roots are " << r1 << "  " << r2 << endl;
      dvector y_1=x_k+r1*p_k;
      dvector y_2=x_k+r2*p_k;
      if (fabs(r1)<fabs(r2))
      {
        x_k=x_k+r1*p_k;
      }
      else
      {
        x_k=x_k+r2*p_k;
      }
      cout << norm(y_1) << " " << norm(y_2) << endl;
      cout << "r1 function value = "  << 0.5*(y_1*(H*y_1)) + y_1*c <<
          "  r2 functiomn value = "  << 0.5*(y_2*(H*y_2)) + y_2*c <<
              " normp_k = " << norm(p_k)  << sqrt(n2gk) << endl;
      break;
    }

    g_k+= alpha_k*v;
    double tmp=n2gk;
    n2gk=norm2(g_k);
    beta_k=n2gk/tmp;
    p_k=-g_k+beta_k*p_k;
    cout << "estimated function value = "
         << truef + 0.5*(x_k*(H*x_k)) + x_k*c << endl;
    double tf=do_one_feval(x+x_k,pfmin);
    cout << "real function value = " << tf << endl;
    if (tf<=bestf)
    {
     improve_flag=1;
     xbest_k=x_k;
     cout << "norm(H*xbest_k+c)" << norm(H*xbest_k+c)  << endl;
     bestf=tf;
    }
    else
    {
      if (improve_flag==0) iflag=1;
      return xbest_k;
    }
  }
  while (n2gk>tol);
  estdiff=0.5*(x_k*(H*x_k)) + x_k*c;
  cout << "estimated function value = "
    << truef + estdiff << endl;
  double tf=do_one_feval(x+x_k,pfmin);
  truediff=tf-truef;
  truef=tf;
  cout << "real function value = " << tf << endl;
  return xbest_k;
}
*/

/**
 * Description not yet available.
 * \param
 */
double laplace_approximation_calculator::do_one_feval
  (const dvector& x,function_minimizer * pfmin)
{
  double f=0.0;
  //double fb=1.e+100;
  dvector g(1,usize);
  dvector ub(1,usize);
  initial_params::set_active_random_effects();
  int nvar=initial_params::nvarcalc();
  int nvar1=initial_params::nvarcalc_all();
  cout << nvar << " " << nvar1 << endl;
  gradient_structure::set_NO_DERIVATIVES();
  dvariable vf=0.0;
  dvariable pen=initial_params::reset(dvar_vector(x));
  *objective_function_value::pobjfun=0.0;
  pfmin->AD_uf_inner();
  vf+=*objective_function_value::pobjfun;
  vf+=pen;
  f=value(vf);
  return f;
}

/*
dvector laplace_approximation_calculator::lincg(dvector& x,
  dvector& c, dmatrix& H,double tol,double Delta,function_minimizer * pfmin,
  double& truef,double& estdiff,double& truediff,double& bestf,
  int& iflag,int& inner_iter,int maxfn)
{
  iflag=0;
  int n=c.indexmax();
  dvector g_k(1,n);
  dvector p_k(1,n);
  dvector x_k(1,n);
  dvector xbest_k(1,n);
  double alpha_k;
  double beta_k;
  double n2gk=0.0;
  x_k=0.0;
  g_k=c;
  p_k=-g_k;
  n2gk=norm2(g_k);
  int improve_flag=0;
  inner_iter=0;
  xbest_k=0;
  cout << norm2(H*p_k+c) << endl;

  do
  {
    dvector v=H*p_k;
    double tmp2=p_k*v;
    alpha_k=n2gk/(tmp2);
    x_k+=alpha_k*p_k;
    double nxk=norm(x_k);
    g_k+= alpha_k*v;
    double tmp=n2gk;
    n2gk=norm2(g_k);
    beta_k=n2gk/tmp;
    p_k=-g_k+beta_k*p_k;
    cout << norm2(H*p_k+c) << endl;
  }
  while(1);
}
*/

/*
dvector laplace_approximation_calculator::lincg(dvector& xinit,
  dvector& c, dmatrix& H,double tol,double Delta,function_minimizer * pfmin,
  double& truef,double& estdiff,double& truediff,double& bestf,
  int& iflag,int& inner_iter,int maxfn)
{
  iflag=0;
  int n=c.indexmax();
  dmatrix g(0,20,1,n);
  dmatrix q(0,20,1,n);
  dmatrix p(0,20,1,n);
  dmatrix x(0,20,1,n);
  dmatrix r(0,20,1,n);
  dvector alpha(0,20);
  dvector beta(0,20);
  int k=0;
  x(0)=0.0;
  g(0)=H*x(0)+c;
  p(0)=-g(0);
  cout << norm(H*x(k)+c) << endl;

  do
  {
    alpha(k)=norm2(g(k))/(p(k)*H*p(k));
    x(k+1)=x(k)+alpha(k)*p(k);
    g(k+1)=g(k)+alpha(k)*H*p(k);
    beta(k)=norm2(g(k+1))/norm2(g(k));
    p(k+1)=-g(k+1)+beta(k)*p(k);
    k++;
    cout << norm(H*x(k)+c) << endl;
  }
  while(1);
}
*/

#if defined(USE_ADPVM)
/**
 * Description not yet available.
 * \param
 */
dvector laplace_approximation_calculator::lincg(dvector& xinit,
  dvector& c, dmatrix& H1,double tol,double Delta,function_minimizer * pfmin,
  double& truef,double& estdiff,double& truediff,double& bestf,
  int& iflag,int& inner_iter,int maxfn)
{
  iflag=0;
  int n=c.indexmax();
  dmatrix r(1,20,1,n);
  dmatrix p(1,20,1,n);
  dmatrix x(1,20,1,n);
  dvector alpha(1,20);
  dvector beta(1,20);
  dmatrix H=-H1;
  int k=1;
  x(1)=0.0;
  r(1)=-c;
  p(1)=r(1);
  cout << norm(H*x(k)+c) << endl;
  cout << norm(H*x(k)-c) << endl;

  do
  {
    dvector w=H*p(k);
    alpha(k)=(r(k)*H*r(k))/norm2(w);
    r(k+1)=r(k)-alpha(k)*(H*p(k));
    beta(k)=(r(k+1)*H*r(k+1))/(r(k)*H*r(k));
    p(k+1)=r(k)+beta(k)*p(k);
    x(k+1)=x(k)+alpha(k)*p(k);
    k++;
    cout << norm(H*x(k)+c) << endl;
    cout << norm(H*x(k)-c) << endl;
  }
  while(1);
  return 0;
}
#endif
