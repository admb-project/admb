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
#include <sstream>
using std::istringstream;

#include <admodel.h>
#include <df1b2fun.h>
#include <adrndeff.h>

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

void get_inverse_sparse_hessian(dcompressed_triplet & st, hs_symbolic& S,
  uostream& ofs1,ofstream& ofs,int usize,int xsize,dvector& u);

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
void function_minimizer::hess_routine_random_effects(void)
{
#if defined(USE_ADPVM)
  if (ad_comm::pvm_manager)
  {
    switch (ad_comm::pvm_manager->mode)
    {
    case 1: //master
      hess_routine_noparallel_random_effects();
      break;
    case 2: //slave
      hess_routine_slave_random_effects();
      break;
    default:
      cerr << "Illegal value for mode" << endl;
      ad_exit(1);
    }
  }
  else
#endif
  {
      hess_routine_noparallel_random_effects();
  }
}
dvector get_solution_vector(int npts);

/**
 * Description not yet available.
 * \param
 */
void function_minimizer::hess_routine_noparallel_random_effects(void)
{ 
#ifdef OPT_LIB
  // get the number of active parameters
  int nvar = (int)initial_params::nvarcalc();
#else
  size_t _nvar = initial_params::nvarcalc();
  assert(_nvar <= INT_MAX);
  int nvar = (int)_nvar;
#endif
  //if (adjm_ptr) set_labels_for_hess(nvar);
  independent_variables x(1,nvar);
  initial_params::xinit(x);        // get the initial values into the x vector
  double f;
  double delta=1.e-4;
  dvector g1(1,nvar);
  dvector g0(1,nvar);
  dvector g2(1,nvar);
  dvector gbest(1,nvar);
  dvector hess(1,nvar);
  dvector hess1(1,nvar);
  dvector hess2(1,nvar);
  //double eps=.1;
  gradient_structure::set_YES_DERIVATIVES();
  gbest.fill_seqadd(1.e+50,0.);

  dvector ddd(1,nvar);
  gradcalc(0,ddd);
  adstring tmpstring;

  {
    first_hessian_flag=1;
    {
      g1=(*lapprox)(x,f,this);
      g0=g1;
    }
    // modify so thaqt we have l_uu and dux for delta method
    // DF feb 15 05
    //if (lapprox->hesstype==2 || lapprox->hesstype==3)
    if (lapprox->hesstype==2 )
    {
      if (lapprox->block_diagonal_hessian)
      {
        //if (ad_comm::wd_flag)
        tmpstring = ad_comm::adprogram_name + ".rhes";
        ofstream ofs((char*)(tmpstring));
            ofs << "   value      std.dev" << endl;
        int mmin=lapprox->block_diagonal_hessian->indexmin();
        int mmax=lapprox->block_diagonal_hessian->indexmax();
        int i,j;
        int ii=1;
        dvector & u= lapprox->uhat;
        for (i=mmin;i<=mmax;i++)
        {
          if (allocated((*(lapprox->block_diagonal_hessian))(i)))
          {
            dmatrix m= inv((*(lapprox->block_diagonal_hessian))(i));
            dvector d=sqrt(diagonal(m));
            int jmin=d.indexmin();
            int jmax=d.indexmax();
            for (j=jmin;j<=jmax;j++)
            {
              //if (ii<=u.indexmax())
              {
                ofs << setprecision(5) << setscientific()
                    << setw(14) << u(ii++) << " " << d(j) << endl;;
              }
            }
          }
        }
      }
      else if (lapprox->bHess)
      {
        //if (ad_comm::wd_flag)
        tmpstring = ad_comm::adprogram_name + ".rhes";
        ofstream ofs((char*)(tmpstring));
            ofs << "   value      std.dev" << endl;
        int mmin=lapprox->bHess->indexmin();
        int mmax=lapprox->bHess->indexmax();
        //int i,j;
        int i;
        //int ii=1;
        dvector & u= lapprox->uhat;
        dvector e(mmin,mmax);
        //choleski_decomp(*lapprox->bHess);
        int ierr;

        banded_lower_triangular_dmatrix tmp=choleski_decomp(*lapprox->bHess,
          ierr);
        e.initialize();
        for (i=mmin;i<=mmax;i++)
        {
          e(i)=1.0;
          dvector v=solve(tmp,e);
          e(i)=0;

          double d=sqrt(v*v);
            ofs << setprecision(5) << setscientific()
                << setw(14) << u(i) << " " << d << endl;;
        }
      }
    }
    else
    {
      int i;
      //if (ad_comm::wd_flag)
      dmatrix m;
      tmpstring = ad_comm::adprogram_name + ".rhes";
      ofstream ofs((char*)(tmpstring));
          ofs << "   value      std.dev" << endl;
      //int ii=1;
      tmpstring = ad_comm::adprogram_name + ".luu";
      uostream ofs1((char*)(tmpstring));
      dvector & u= lapprox->uhat;
      if (lapprox->hesstype !=3)
      {
        if (allocated(lapprox->Hess))
        {
          m= inv(lapprox->Hess);
          int mmin=m.indexmin();
          int mmax=m.indexmax();
          for (i=mmin;i<=mmax;i++)
          {
            ofs << setprecision(5) << setscientific()
                << setw(14) << u(i) << " " << sqrt(m(i,i)) << endl;;
          }
          // save l_uu and l_xu for covariance calculations
          ofs1 << lapprox->usize << lapprox->xsize;
          ofs1 << m;
        }
        else if (lapprox->sparse_triplet2)
        {
          dcompressed_triplet & st= *(lapprox->sparse_triplet2);
          hs_symbolic& S= *(lapprox->sparse_symbolic2);
          get_inverse_sparse_hessian(st,S,ofs1,ofs,lapprox->usize,
            lapprox->xsize,u);
          // save l_uu and l_xu for covariance calculations
        }
      }
      else
      {
        if (lapprox->bHess)
        {
          int ierr=0;
          int mmin=lapprox->bHess->indexmin();
          int mmax=lapprox->bHess->indexmax();
          const banded_lower_triangular_dmatrix& C=
            quiet_choleski_decomp(*lapprox->bHess,ierr);
          ivector e(mmin,mmax);
          e.initialize();
          if (ierr==0)
          {
            ofs1 << lapprox->usize << lapprox->xsize;
            for (int i=mmin;i<=mmax;i++)
            {
              if (i>1) e(i-1)=0;
              e(i)=1;
              dvector w=solve_trans(C,solve(C,e));
              ofs << setprecision(5) << setscientific()
                  << setw(14) << u(i) << " " << sqrt(w(i)) << endl;;
              ofs1 << w;
            }
          }
          else
          {
          }
        }
      }
      if (!ofs)
      {
        cerr << "Error writing to file " << tmpstring << endl;
        ad_exit(1);
      }
      // save l_uu and l_xu for covariance calculations
      ofs1 << lapprox->Dux;
      if (!ofs1)
      {
        cerr << "Error writing to file " << tmpstring << endl;
        ad_exit(1);
      }
      ofs1.close();
    }

    {
      tmpstring = ad_comm::adprogram_name + ".luu";
      uistream uis1((char*)(tmpstring));
      int i = 0, j = 0;
      uis1 >> i >> j;
      cout << i << " " << j << endl;
    }

    int npts=2;
    int on,nopt = 0;
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hpts",nopt))>-1)
    {
      if (nopt !=1)
      {
        cerr << "Usage -hpts option needs non-negative integer  -- ignored.\n";
      }
      else
      {
        npts=atoi(ad_comm::argv[on+1]);
      }
    }

    double _delta=0.0;

    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hsize",nopt))>-1)
    {
      if (!nopt)
      {
        cerr << "Usage -hsize option needs number  -- ignored" << endl;
      }
      else
      {
        istringstream ist(ad_comm::argv[on+1]);
        ist >> _delta;

        if (_delta<=0)
        {
          cerr << "Usage -hsize option needs positive number  -- ignored.\n";
          _delta=0.0;
        }
      }
      if (_delta>0)
      {
        delta=_delta;
      }
    }

    // get a number which is exactly representable
    double sdelta=1.0+delta;
    sdelta-=1.0;
    {
      //
      uostream uos("hessian.bin");
      uos << npts;
      for (int i=1;i<=nvar;i++)
      {
        cout << "Estimating row " << i << " out of " << nvar
             << " for hessian" << endl;

        for (int j=-npts;j<=npts;j++)
        {
          if (j !=0)
          {
            double f=0.0;
            double xsave=x(i);
            x(i)=xsave+j*sdelta;
            g1=(*lapprox)(x,f,this);
            x(i)=xsave;
            uos << i << j << sdelta << g1;
          }
          else
          {
            uos << i << j << sdelta << g0;
          }
        }
      }
    }
    // check for accuracy
    {
      uistream uis("hessian.bin");
      uis >> npts;
      dvector v=get_solution_vector(npts);
      v.shift(-npts);
      dmatrix tmp(-npts,npts,1,nvar);
      dmatrix hess(1,nvar,1,nvar);
      ivector iind(-npts,npts);
      ivector jind(-npts,npts);
      double sd = 0;
      int i;
      for (i=1;i<=nvar;i++)
      {
        for (int j=-npts;j<=npts;j++)
        {
          uis >> iind(j) >> jind(j) >> sd >> tmp(j);
        }
        hess(i)=(v*tmp).shift(1);
        hess(i)/=sd;
      }
      {
        adstring tmpstring="admodel.hes";
        if (ad_comm::wd_flag)
        {
          tmpstring = ad_comm::adprogram_name + ".hes";
        }
        uostream ofs((char*)tmpstring);
        ofs << nvar;
        dmatrix shess(1,nvar,1,nvar);
        double maxerr=0.0;
        for (i=1;i<=nvar;i++)
        {
          for (int j=1;j<=nvar;j++)
          {
            shess(i,j)=(hess(i,j)-hess(j,i))/
             (1.e-3+sfabs(hess(i,j))+fabs(hess(j,i)));
            if (shess(i,j)>maxerr) maxerr=shess(i,j);
          }
        }
        ofstream ofs1("hesscheck");
        ofs1 << "maxerr = " << maxerr << endl << endl;
        ofs1 << setw(10) << hess << endl << endl;
        ofs1 << setw(10) << shess << endl;
        ofs << hess;
        ofs << gradient_structure::Hybrid_bounded_flag;
        initial_params::set_inactive_only_random_effects();
        dvector tscale(1,nvar);   // need to get scale from somewhere
        /*int check=*/initial_params::stddev_scale(tscale,x);
        ofs << tscale;
      }
    }
   /*
    first_hessian_flag=0;
    double sdelta1;
    double sdelta2;
    lapprox->fmc1.fringe=1.e-9;
    for (int i=1;i<=nvar;i++)
    {
      hess_calcreport(i,nvar);

      double f=0.0;
      double xsave=x(i);
      sdelta1=x(i)+delta;
      sdelta1-=x(i);
      x(i)=xsave+sdelta1;
      g1=(*lapprox)(x,f,this);

      sdelta2=x(i)-delta;
      sdelta2-=x(i);
      x(i)=xsave+sdelta2;
      g2=(*lapprox)(x,f,this);
      x(i)=xsave;
      hess1=(g1-g2)/(sdelta1-sdelta2);

      sdelta1=x(i)+eps*delta;
      sdelta1-=x(i);
      x(i)=xsave+sdelta1;
      g1=(*lapprox)(x,f,this);

      x(i)=xsave-eps*delta;
      sdelta2=x(i)-eps*delta;
      sdelta2-=x(i);
      x(i)=xsave+sdelta2;
      g2=(*lapprox)(x,f,this);
      x(i)=xsave;

      initial_params::set_inactive_only_random_effects();
      initial_params::reset(dvar_vector(x));
      double eps2=eps*eps;
      hess2=(g1-g2)/(sdelta1-sdelta2);
      hess=(eps2*hess1-hess2) /(eps2-1.);

      ofs << hess;
    }
   */
  }
}

#if defined(USE_ADPVM)

/**
 * Description not yet available.
 * \param
 */
void function_minimizer::hess_routine_slave_random_effects(void)
{
  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  //if (adjm_ptr) set_labels_for_hess(nvar);
  independent_variables x(1,nvar);
  initial_params::xinit(x);        // get the initial values into the x vector
  double f;
  double delta=1.e-6;
  double eps=.1;
  gradient_structure::set_YES_DERIVATIVES();

  dvector ddd(1,nvar);
  gradcalc(0,ddd);
  {
    {
      (*lapprox)(x,f,this);
    }
    double sdelta1;
    double sdelta2;
    lapprox->fmc1.fringe=1.e-9;
    for (int i=1;i<=nvar;i++)
    {
      double f=0.0;
      double xsave=x(i);
      sdelta1=x(i)+delta;
      sdelta1-=x(i);
      x(i)=xsave+sdelta1;
      (*lapprox)(x,f,this);

      sdelta2=x(i)-delta;
      sdelta2-=x(i);
      x(i)=xsave+sdelta2;
      (*lapprox)(x,f,this);
      x(i)=xsave;

      sdelta1=x(i)+eps*delta;
      sdelta1-=x(i);
      x(i)=xsave+sdelta1;
      (*lapprox)(x,f,this);

      x(i)=xsave-eps*delta;
      sdelta2=x(i)-eps*delta;
      sdelta2-=x(i);
      x(i)=xsave+sdelta2;
      (*lapprox)(x,f,this);
      x(i)=xsave;

      initial_params::set_inactive_only_random_effects();
      initial_params::reset(dvar_vector(x));
    }
  }
}
#endif // #if defined(USE_ADPVM)

/**
 * Description not yet available.
 * \param
 */
dvector get_solution_vector(int n)
{
  int i;
  int n1=2*n+1;
  dmatrix tmp(1,n1,1,n1);
  dvector v(1,n1);
  v.initialize();
  v(2)=1.0;
  dvector c(1,n1);
  c.fill_seqadd(-n,1);
  tmp.initialize();
  tmp(1)=1;
  tmp(2)=c;
  for (i=3;i<=n1;i++)
  {
    tmp(i)=elem_prod(tmp(i-1),c);
  }
  dmatrix tmp1=inv(tmp);
  return tmp1*v;
}
