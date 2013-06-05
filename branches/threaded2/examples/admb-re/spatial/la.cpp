

/*
 * $Id: df1b2lap.cpp 1001 2011-04-07 22:36:54Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <sstream>
using std::istringstream;

#if defined(USE_LAPLACE)
#  include <admodel.h>
#  include <df1b2fun.h>
#  include <adrndeff.h>
#include <fvar.hpp>

#define PI 3.14159265358979323846

extern  int no_stuff;
static int write_sparse_flag;
extern  int noboundepen_flag;



double calculate_laplace_approximation_no_sparse(const dvector& x,
  const dvector& u0,
  const dmatrix& _Hess,const dvector& _xadjoint,const dvector& _uadjoint,
  const dmatrix& _Hessadjoint,function_minimizer * pmin)
{
  ADUNCONST(dvector,xadjoint)
  ADUNCONST(dvector,uadjoint)
  ADUNCONST(dmatrix,Hessadjoint)
  ADUNCONST(dmatrix,Hess)
  const int xs=x.size();
  const int us=u0.size();
  gradient_structure::set_YES_DERIVATIVES();
  int nvar;
  dcompressed_triplet & lst = *(pmin->lapprox->sparse_triplet2);
  hs_symbolic & ssymb=*(pmin->lapprox->sparse_symbolic2);
    
  if (pmin->lapprox->sparse_hessian_flag==0)
  {
    nvar=x.size()+u0.size()+u0.size()*u0.size();
  }
  else
  {
    int sz= lst.indexmax()-lst.indexmin()+1;
    nvar=x.size()+u0.size()+sz;
  }
  independent_variables y(1,nvar);
  
  // need to set random effects active together with whatever
  // init parameters should be active in this phase
  initial_params::set_inactive_only_random_effects(); 
  initial_params::set_active_random_effects(); 
  /*int onvar=*/initial_params::nvarcalc(); 
  initial_params::xinit(y);    // get the initial values into the
  y(1,xs)=x;

  int i,j;
  dvar_vector d(1,xs+us);

  dmatrix Hess_save;
  // contribution for quadratic prior
  if (quadratic_prior::get_num_quadratic_prior()>0)
  {
    if (allocated(Hess_save)) Hess_save.deallocate();
    int mmin=Hess.indexmin();
    int mmax=Hess.indexmax();
    Hess_save.allocate(mmin,mmax,mmin,mmax);
    Hess_save=Hess;
    int & vxs = (int&)(xs);
    quadratic_prior::get_cHessian_contribution(Hess,vxs);
  }
 // Here need hooks for sparse matrix structures
  int ii=xs+us+1;
  if (pmin->lapprox->sparse_hessian_flag==0)
  {
    for (i=1;i<=us;i++)
      for (j=1;j<=us;j++)
      y(ii++)=Hess(i,j);
  }
  else
  {
    int smin=lst.indexmin();
    int smax=lst.indexmax();
    for (i=smin;i<=smax;i++)
      y(ii++)=lst(i);
  }

//#if !defined(__MSVC32__)
  if (quadratic_prior::get_num_quadratic_prior()>0)
  {
    Hess=Hess_save;
  }
//#endif

  dvar_vector vy=dvar_vector(y); 
  initial_params::stddev_vscale(d,vy);
  dvar_matrix vHess;
  if (pmin->lapprox->sparse_hessian_flag==0)
  {
    vHess.allocate(1,us,1,us);
  }
  initial_params::reset(vy);    // get the initial values into the
  ii=xs+us+1;
  if (initial_df1b2params::have_bounded_random_effects)
  {
    for (i=1;i<=us;i++)
    {
      if (d(i+xs)>0.0)
      {
        for (j=1;j<=us;j++)
        {
          if (d(j+xs)>0.0)
            vHess(i,j)=vy(ii++)/(d(i+xs)*d(j+xs));
          else
            vHess(i,j)=vy(ii++)/d(i+xs);
        }
      }
      else
      {
        for (j=1;j<=us;j++)
        {
          if (d(j+xs)>0.0)
            vHess(i,j)=vy(ii++)/d(j+xs);
          else
            vHess(i,j)=vy(ii++);
        }
      }
    }
  }
  else
  {
    if (laplace_approximation_calculator::sparse_hessian_flag==0)
    {
      for (i=1;i<=us;i++)
      {
        for (j=1;j<=us;j++)
        {
          vHess(i,j)=vy(ii++);
        }
      }
    }
    else
    {
      int mmin=lst.indexmin();
      int mmax=lst.indexmax();
      dvar_compressed_triplet * vsparse_triplet = 
        pmin->lapprox->vsparse_triplet;
   
      if (vsparse_triplet==0)
      {
        pmin->lapprox->vsparse_triplet=
          new dvar_compressed_triplet(mmin,mmax,us,us);
        vsparse_triplet = pmin->lapprox->vsparse_triplet;
        for (i=mmin;i<=mmax;i++)
        {
          (*vsparse_triplet)(1,i)=lst(1,i);
          (*vsparse_triplet)(2,i)=lst(2,i);
        }
      }
      else
      {
        if (!allocated(*vsparse_triplet))
        {
          (*vsparse_triplet).allocate(mmin,mmax,us,us);
          for (i=mmin;i<=mmax;i++)
          {
            (*vsparse_triplet)(1,i)=lst(1,i);
            (*vsparse_triplet)(2,i)=lst(2,i);
          }
        } 
      }
      dcompressed_triplet * vsparse_triplet_adjoint = 
        pmin->lapprox->vsparse_triplet_adjoint;
   
      if (vsparse_triplet_adjoint==0)
      {
        pmin->lapprox->vsparse_triplet_adjoint=
          new dcompressed_triplet(mmin,mmax,us,us);
        vsparse_triplet_adjoint = pmin->lapprox->vsparse_triplet_adjoint;
        for (i=mmin;i<=mmax;i++)
        {
          (*vsparse_triplet_adjoint)(1,i)=lst(1,i);
          (*vsparse_triplet_adjoint)(2,i)=lst(2,i);
        }
      }
      else
      {
        if (!allocated(*vsparse_triplet_adjoint))
        {
          (*vsparse_triplet_adjoint).allocate(mmin,mmax,us,us);
          for (i=mmin;i<=mmax;i++)
          {
            (*vsparse_triplet_adjoint)(1,i)=lst(1,i);
            (*vsparse_triplet_adjoint)(2,i)=lst(2,i);
          }
        } 
      }
      vsparse_triplet->get_x()=vy(ii,ii+mmax-mmin).shift(1);
    }
  }
   dvariable vf=0.0;

   
   *objective_function_value::pobjfun=0.0;
   pmin->AD_uf_outer();
   if ( no_stuff==0 && quadratic_prior::get_num_quadratic_prior()>0)
   {
     quadratic_prior::get_M_calculations();
   }
   vf+=*objective_function_value::pobjfun;

   int sgn=0;
   dvariable ld;
   if (ad_comm::no_ln_det_choleski_flag)
   {
     if(laplace_approximation_calculator::saddlepointflag==0)
     {
       ld=0.5*ln_det(vHess,sgn);
     }
     else 
     {
       ld=0.5*ln_det(-vHess,sgn);
     }
   }
   else
   {
     if(laplace_approximation_calculator::saddlepointflag==0)
     {
       int ierr=0;
       if (pmin->lapprox->sparse_hessian_flag==0)
       {
         ld=0.5*ln_det_choleski_error(vHess,ierr);
         if (ierr==1)
         {
           ofstream ofs("hessian.diag");
           ofs << vHess << endl;
           ofs <<  x << endl;
           ofs <<  u0 << endl;
           ofs << "Matrix not positive definite in Ln_det_choleski"
               << endl;
           ad_exit(1);
         }
       }
       else
       {
         //double ld1=0.5*ln_det(*(pmin->lapprox->sparse_triplet),
         //  *(pmin->lapprox->sparse_symbolic));

         if (write_sparse_flag)
         {
           //ofstream ofs("sparse");
           //ofs << *(pmin->lapprox->vsparse_triplet) << endl;
         }
         ld=0.5*ln_det(*(pmin->lapprox->vsparse_triplet),
           ssymb,*(pmin->lapprox->sparse_triplet2));
           //*(pmin->lapprox->sparse_symbolic2),pmin->lapprox);
         //cout << ld-ld1 << endl;
       }
     }
     else 
     {
       if (pmin->lapprox->sparse_hessian_flag==0)
       {
         ld=0.5*ln_det_choleski(-vHess);
       }
       else
       {
         cerr << "need to fix this" << endl;
         ad_exit(1);
         //ld+=ln_det(-*(pmin->lapprox->vsparse_triplet));
       }
     }
   }

   int ps1=0;
   if (ps1)
   {
     dmatrix cHess=value(vHess);
     cout << " ln_det = " << ld << " ";
     dvector eig=eigenvalues(cHess);
     dmatrix r(1,2,1,eig.indexmax());
     dvector num(1,eig.indexmax());
     num.fill_seqadd(1,1);
     r(1)=eig;
     r(2)=num;
     dmatrix tt=trans(r);
     dmatrix ss=trans(sort(tt,1));
     cout << ss(1,1)  << " " << ss(1,eig.indexmax()) << " " ;
     int nnn=(int)ss(2,1);
     dmatrix d=eigenvectors(cHess);
     //cout << " d " << d(nnn) << " " << d(nnn)*cHess*d(nnn) << endl;
     dmatrix t=trans(d);
     r(1)=t(nnn);
     r(2)=num;
     dmatrix tt2=trans(r);
     dmatrix ss2=trans(sort(tt2,1));
     
     cout << " t " << setprecision(3) << ss2(1)(1,5) << " --- " << t(nnn)*cHess*t(nnn) << endl;
     cout << "   " << setprecision(3) << ss2(2)(1,5) << endl;
     //cout << " t " << t(1) << " " << t(1)*cHess*t(2) << endl;
   }

   int nx=0;
   if (nx==0)
   {
     vf+=ld;
   }
   double f=value(vf);
   f-=us*0.5*log(2.0*PI);
   dvector g(1,nvar);
   gradcalc(nvar,g);
  
  ii=1;
  for (i=1;i<=xs;i++)
    xadjoint(i)=g(ii++);
  for (i=1;i<=us;i++)
    uadjoint(i)=g(ii++);
  if (pmin->lapprox->sparse_hessian_flag==0)
  {
    if (allocated(Hessadjoint))
    {
      for (i=1;i<=us;i++)
        for (j=1;j<=us;j++)
          Hessadjoint(i,j)=g(ii++);
    }
  }
  else
  {
    dcompressed_triplet * vsparse_triplet_adjoint = 
      pmin->lapprox->vsparse_triplet_adjoint;

    int smin=lst.indexmin();
    int smax=lst.indexmax();
    for (i=smin;i<=smax;i++)
    {
      (*vsparse_triplet_adjoint)(i)=g(ii);
      ii++;
    }
  }
  return f;
}
#endif
