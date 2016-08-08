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
#if defined(USE_DD)
#  define USE_DD_STUFF
#endif

#  include <admodel.h>
#  include <df1b2fun.h>
#  include <adrndeff.h>
double calculate_laplace_approximation(const dvector& x,const dvector& u0,
  const banded_symmetric_dmatrix& bHess,const dvector& _xadjoint,
  const dvector& _uadjoint,
  const banded_symmetric_dmatrix& _bHessadjoint,function_minimizer * pmin);
double calculate_laplace_approximation(const dvector& x,const dvector& u0,
  const dmatrix& Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin);

#if defined(USE_DD_STUFF)
#  if defined(_MSC_VER)
    extern "C" _export  void dd_newton_raphson(int n,double * v,double * diag,
      double * ldiag, double * yy);
#  else
    extern "C" void dd_newton_raphson(int n,double * v,double * diag,
      double * ldiag, double * yy);
#  endif
#endif

/**
 * Description not yet available.
 * \param
 */
void positivize(const banded_symmetric_dmatrix& _m,double id)
{
  ADUNCONST(banded_symmetric_dmatrix,m)
  int mmin=m.indexmin();
  int mmax=m.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    m(i,i)+=id;
  }
}

/**
 * Description not yet available.
 * \param
 */
class safe_choleski_solver
{
public:
  safe_choleski_solver(double id);
  int hadbad;
  int dirty;
  double id;
  double angle;
  dvector solve(const banded_symmetric_dmatrix& _m,const dvector&_v);
};

/**
 * Description not yet available.
 * \param
 */
safe_choleski_solver::safe_choleski_solver(double _id)
{
  id=_id;
  hadbad=0;
  dirty=0;
}

banded_lower_triangular_dmatrix quiet_choleski_decomp(
  const banded_symmetric_dmatrix& _M, int& ierr);
/*
banded_lower_triangular_dmatrix quiet_choleski_decomp(
  const banded_symmetric_dmatrix& _M,const int& _ierr)
{
  int & ierr = (int &) _ierr;
  ADUNCONST(banded_symmetric_dmatrix,M)
  int minsave=M.indexmin();
  M.shift(1);
  int n=M.indexmax();

  int bw=M.bandwidth();
  banded_lower_triangular_dmatrix L(1,n,bw);
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  double tmp;
    if (M(1,1)<=0)
    {
      ierr=1;
      return L;
    }
  L(1,1)=sqrt(M(1,1));
  for (i=2;i<=bw;i++)
  {
    L(i,1)=M(i,1)/L(1,1);
  }

  for (i=2;i<=n;i++)
  {
    for (j=i-bw+1;j<=i-1;j++)
    {
      if (j>1)
      {	
        tmp=M(i,j);
        for (k=i-bw+1;k<=j-1;k++)
        {
	  if (k>0 && k>j-bw)
            tmp-=L(i,k)*L(j,k);
        }
        L(i,j)=tmp/L(j,j);
      }
    }
    tmp=M(i,i);
    for (k=i-bw+1;k<=i-1;k++)
    {
      if (k>0)	
        tmp-=L(i,k)*L(i,k);
    }
    if (tmp<=0)
    {
      ierr=1;
      return L;
    }
    L(i,i)=sqrt(tmp);
  }
  M.shift(minsave);
  L.shift(minsave);

  return L;
}
*/

/**
 * Description not yet available.
 * \param
 */
dvector safe_choleski_solver::solve
  (const banded_symmetric_dmatrix& _m,const dvector&_v)
{
  int ierr=0;
  ADUNCONST(dvector,v)
  ADUNCONST(banded_symmetric_dmatrix,m)
  int mmin=m.indexmin();
  //int mmax=m.indexmax();
  if (hadbad && id>0.0)
  {
    positivize(m,id);
   dirty=1;
  }
  m.shift(1);
  v.shift(1);
  int ibreak=1;
  dvector w;
  do
  {
    const banded_lower_triangular_dmatrix& C=quiet_choleski_decomp(m,ierr);
    if (ierr==0)
    {
      id/=2.0;
      w=solve_trans(C,::solve(C,v));
      dvector delta=m*w;
      dvector err=solve_trans(C,::solve(C,v-delta));
      dvector w1=w+err;
      cout << norm(w1-w) << endl;
      if (norm(err)>1.e-10)
      {
        cout << "precisionerror" << endl;
      }
      angle=w*v/(norm(w)*norm(v));
      ibreak=0;
    }
    else
    {
      id*=2.0;
      positivize(m,id);
      ierr=0;
      dirty=1;
      hadbad=1;
    }
  }
  while(ibreak);
  m.shift(mmin);
  w.shift(mmin);
  v.shift(mmin);
  return w;
}

/**
\todo Needs testing
*/
void laplace_approximation_calculator::
  do_newton_raphson_state_space(function_minimizer * pfmin,double f_from_1,
  int& no_converge_flag)
{
  laplace_approximation_calculator::where_are_we_flag=2;
  double fbest=1.e+100;
  double fval=1.e+100;
  double maxg=fabs(evaluate_function(fbest,uhat,pfmin));

  laplace_approximation_calculator::where_are_we_flag=0;
  dvector uhat_old(1,usize);
  safe_choleski_solver scs(0.1);
  //for(int ii=1;ii<=num_nr_iters;ii++)
  int ii=0;
  for (;;)
  {
    bHess->initialize();

    grad.initialize();

    step=get_newton_raphson_info_banded(pfmin);

#ifdef DIAG
    // check for degenerate Hessian
    int check_hessian=0;
    if (check_hessian)
    {
      ofstream ofs("hh");
      ofs << colsum(dmatrix(*bHess)) << endl;
    }
#endif

    if (!initial_params::mc_phase)
      cout << "Newton raphson " << ii << "  ";

    if (quadratic_prior::get_num_quadratic_prior()>0)
    {
      quadratic_prior::get_cHessian_contribution(Hess,xsize);
      quadratic_prior::get_cgradient_contribution(grad,xsize);
    }

    //int ierr=0;

    dvector g1(1,usize);
    maxg=fabs(evaluate_function(fval,uhat,g1,pfmin));
    if (fval>fbest)
    fbest=fval;
    if (nr_debug==1)
    {
      cout << " grad compare " << norm(g1-grad)  << endl;
    }
    step=scs.solve(*bHess,g1);
    //step=scs.solve(*bHess,grad);
    if (nr_debug==1)
    {
      cout << " angle = " << step*grad/(norm(step)*norm(grad)) << endl;
    }
    int iic=0;
    double testangle=-1;
    int extra_try=0;
    dvector utry(1,usize);
    int smallshrink=0;
    for (;;)
    {
      if (++iic>10)
      {
        break;
      }
      if (extra_try==0)
      {
        utry = uhat-step;
      }
      else
      {
        utry = uhat-0.5*step;
      }
      dvector g(1,usize);
      maxg=fabs(evaluate_function(fval,utry,g,pfmin));
      if (nr_debug==1)
      {
        cout << "  fbest-fval = " << setprecision(15)
           <<  fbest-fval  << endl;
      }
      if (fval>fbest && maxg>1.e-10)
      {
        if (maxg<1.e-10)
          smallshrink=3;
        else if (maxg<1.e-9)
          smallshrink=2;
        else if (maxg<1.e-8)
          smallshrink=1;

        if (nr_debug==1)
        {
          testangle=g*step/(norm(g)*norm(step));
          cout << fval-fbest << " step too large  angle = " << testangle
               << endl;
        }
      }
      if (fval==fbest)
      {
        testangle=g*step/(norm(g)*norm(step));
        cout << " no progress  angle = " << testangle << endl;
      }
      if (fval<=fbest)
      {
        uhat=utry;
        fbest=fval;
        testangle=g*step/(norm(g)*norm(step));
        if (nr_debug==1)
        {
          cout << "inner angle = " << testangle << endl;
        }
        if (testangle>0.4)
        {
          extra_try=extra_try+1;
          if (nr_debug==1)
          {
            cout << extra_try << endl;
          }
        }
        else
        {
          break;
        }
      }
      else
      {
        if (extra_try>0)
        {
          break;
        }
        else
        {
          if (smallshrink==0)
            step/=100.0;
          else if(smallshrink==1)
            step/=10.0;
          else if(smallshrink==2)
            step/=5;
          else if(smallshrink==3)
            step/=2;
          smallshrink=0;
        }
      }
    }

    ii++;

    if (scs.dirty==1)
    {
      scs.dirty=0;
      step=get_newton_raphson_info_banded(pfmin);

#ifdef DIAG
      int print_hessian=0;
      if (print_hessian)
      {
        ofstream ofs("hh1");
        ofs << setw(12) << setscientific() << setprecision(3) << endl;
      }
#endif

      if (quadratic_prior::get_num_quadratic_prior()>0)
      {
        quadratic_prior::get_cHessian_contribution(Hess,xsize);
        quadratic_prior::get_cgradient_contribution(grad,xsize);
      }
      if (ii>=num_nr_iters || maxg < 1.e-13 )
      {
        step=scs.solve(*bHess,g1);
      }
      //solve(*bHess,grad);
    }

    for (int i=1;i<=usize;i++)
    {
      y(i+xsize)=uhat(i);
    }

    if (scs.dirty==0)
    {
      if (ii>=num_nr_iters || maxg < 1.e-13 )
      {
        break;
      }
    }
    else
    {
      scs.dirty=0;
      scs.hadbad=0;
      if (ii>100)
      {
        cerr << "Can't get positive definite Hessian in inner optimization"
             << endl;
        break;
      }
    }
  }
}
