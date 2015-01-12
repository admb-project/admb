/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

banded_lower_triangular_dvar_matrix::banded_lower_triangular_dvar_matrix
   (_CONST banded_lower_triangular_dvar_matrix& S) : d(S.d), bw(S.bw) 
{}

banded_symmetric_dvar_matrix::banded_symmetric_dvar_matrix
   (_CONST banded_symmetric_dvar_matrix& S) : d(S.d), bw(S.bw) 
{}

  
#if !defined(OPT_LIB)
dvar_vector banded_symmetric_dvar_matrix::operator () (int i)
{
  return d(i);
}
prevariable banded_symmetric_dvar_matrix::operator () (int i,int j)
{
  return d(i-j,i);
}

prevariable banded_lower_triangular_dvar_matrix::operator () (int i,int j)
{
  return d(i-j,i);
}

#  if defined(USE_CONST)
  const prevariable banded_lower_triangular_dvar_matrix::operator () 
    (int i,int j) const 
  {
    return d(i-j,i);
  }
#  endif


dvar_vector banded_lower_triangular_dvar_matrix::operator () (int i)
{
  return d(i);
}
#endif

/*
void banded_symmetric_dmatrix::initialize(void)
{
  for (int i=rowmin();i<=rowmax();i++)
  {
    (*this)(i).initialize();
  }
}

void banded_lower_triangular_dmatrix::initialize(void)
{
  for (int i=rowmin();i<=rowmax();i++)
  {
    (*this)(i).initialize();
  }
}
*/

void banded_symmetric_dvar_matrix::initialize(void)
{
  for (int i=rowmin();i<=rowmax();i++)
  {
    (*this)(i).initialize();
  }
}

void banded_lower_triangular_dvar_matrix::initialize(void)
{
  for (int i=rowmin();i<=rowmax();i++)
  {
    (*this)(i).initialize();
  }
}

banded_symmetric_dvar_matrix::banded_symmetric_dvar_matrix
  (int _min,int _max,int _bw)
{
  bw=_bw;
  ivector  lb(0,_bw-1);
  lb.fill_seqadd(_min,1);
  d.allocate(0,_bw-1,lb,_max);
}

banded_symmetric_dmatrix value(_CONST banded_symmetric_dvar_matrix&v)
{
  int bw=v.bandwidth();
  banded_symmetric_dmatrix w(v.indexmin(),v.indexmax(),v.bw);
  for (int i=0;i<=bw-1;i++)
  {
    w.d(i)=value(v.d(i));
  }
  return w;
}

banded_lower_triangular_dmatrix value
  (_CONST banded_lower_triangular_dvar_matrix&v)
{
  int bw=v.bandwidth();
  banded_lower_triangular_dmatrix w(v.indexmin(),v.indexmax(),v.bw);
  for (int i=0;i<=bw-1;i++)
  {
    w.d(i)=value(v.d(i));
  }
  return w;
}



ostream& operator << (BOR_CONST ostream& _ofs,_CONST banded_symmetric_dvar_matrix& S1)
{
  ostream& ofs= (ostream&) _ofs;
  banded_symmetric_dvar_matrix& S= (banded_symmetric_dvar_matrix&) S1;
  
  int imin=S.indexmin();
  int imax=S.indexmax();
  int bw=S.bandwidth();
  int i1;
  int j1;
  for (int i=imin;i<=imax;i++)
  {
    for (int j=imin;j<=imax;j++)
    {
      if (j<i) 
      {
	j1=j;
	i1=i;
      }
      else
      {
	j1=i;
	i1=j;
      }
      if ( (i1-j1) < bw)
        ofs << S(i1,j1) << " ";
      else
        ofs << 0.0 << " ";
    }
    if (i<imax) ofs << endl;
  }
  return (ostream&)ofs;
}

banded_lower_triangular_dvar_matrix::banded_lower_triangular_dvar_matrix
  (int _min,int _max,int _bw)
{
  bw=_bw;
  ivector  lb(0,_bw-1);
  lb.fill_seqadd(_min,1);
  d.allocate(0,_bw-1,lb,_max);
}


ostream& operator << (BOR_CONST ostream& _ofs,_CONST banded_lower_triangular_dvar_matrix& S1)
{
  ostream& ofs= (ostream&) _ofs;
  banded_lower_triangular_dvar_matrix& S=(banded_lower_triangular_dvar_matrix&) S1;
  int imin=S.indexmin();
  int imax=S.indexmax();
  int bw=S.bandwidth();
  for (int i=imin;i<=imax;i++)
  {
    for (int j=imin;j<=imax;j++)
    {
      if (j<=i)
      {
        if ( (i-j) < bw)
          ofs << S(i,j) << " ";
        else
          ofs << 0.0 << " ";
      }
      else
      {
        ofs << 0.0 << " ";
      }
    }
    if (i<imax) ofs << endl;
  }
  return (ostream&)ofs;
}



#include "fvar.hpp"

#ifdef __TURBOC__
#pragma hdrstop
#include <iostream.h>
#endif

#ifdef __ZTC__
#include <iostream.hpp>
#endif

#ifdef __SUN__
#include <iostream.h>
#endif
#ifdef __NDPX__
#include <iostream.h>
#endif
void dfcholeski_decomp(void);
void dfcholeski_decomp_banded(void);

dvariable ln_det_choleski(
  const banded_symmetric_dvar_matrix& MM, const int& _ierr)
{
  banded_lower_triangular_dvar_matrix tmp=choleski_decomp(MM,_ierr);
  dvariable ld=0.0;
  if (_ierr==1)
  {
    return ld;
  }
  
  int mmin=tmp.indexmin();
  int mmax=tmp.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    ld+=log(tmp(i,i));
  }
  return 2.0*ld;
}



banded_lower_triangular_dvar_matrix choleski_decomp(
  const banded_symmetric_dvar_matrix& MM, const int& _ierr)
{
  int& ierr=(int&)(_ierr);
  // kludge to deal with constantness
  ierr =0;
  banded_symmetric_dvar_matrix& M = (banded_symmetric_dvar_matrix&) MM;
  int n=M.indexmax();
  
  int bw=M.bandwidth();
  banded_lower_triangular_dvar_matrix L(1,n,bw);
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  double tmp;
    if (M(1,1)<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
       " value was " << M(1,1) << " for index  1"   <<endl;
      ierr=1;
      M(1,1)=1.0;
    }
  L.elem_value(1,1)=sqrt(value(M(1,1)));
  for (i=2;i<=bw;i++)
  {
    L.elem_value(i,1)=value(M(i,1))/L.elem_value(1,1);
  }

  for (i=2;i<=n;i++)
  {
    int jmin=admax(2,i-bw+1);
    for (j=jmin;j<=i-1;j++)
    {
      tmp=value(M(i,j));
      int kmin=max(1,j-bw+1,i-bw+1);
      for (k=kmin;k<=j-1;k++)
      {
        tmp-=L.elem_value(i,k)*L.elem_value(j,k);
      }
      L.elem_value(i,j)=tmp/L.elem_value(j,j);
    }
    tmp=value(M(i,i));
    int kmin=admax(i-bw+1,1);
    //double vmax=fabs(L.elem_value(i,kmin));
    //for (k=kmin;k<=i-1;k++)
    //{
     // if (fabs(L.elem_value(i,k))>vmax) vmax=fabs(L.elem_value(i,k));
    //}
    //tmp/=square(vmax);
    for (k=kmin;k<=i-1;k++)
    {
      tmp-=L.elem_value(i,k)*L.elem_value(i,k);
      //tmp-=square(L.elem_value(i,k)/vmax);
    }
    if (tmp<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
       " value was " << tmp << " for index " << i    <<endl;
      ierr=1;

      int print_switch=0;
      if (print_switch)
      {
        dmatrix CMM=dmatrix(value(MM));
        ofstream ofs("hh");
        {
          ofs << setprecision(3) << setscientific() << setw(11) 
              << CMM << endl<< endl;
        }
        dvector ev(CMM.indexmin(),CMM.indexmax());
        dmatrix evec=eigenvectors(CMM,ev);
        ofs << setprecision(3) << setscientific() << setw(11) 
              << ev << endl<< endl;
        ofs << setprecision(3) << setscientific() << setw(11) 
              << evec << endl<< endl;
        uostream uos("uos");
        uos << CMM.indexmax()-CMM.indexmin()+1;
        uos << CMM;
      }
      /*
      dmatrix N(1,4,1,4);

      for (int i=1;i<=4;i++)
      {
	N(i,i)=value(M(i,i));
        for (int j=1;j<i;j++)
        {
	  N(i,j)=value(M(i,j));
	  N(j,i)=value(M(i,j));
	}
      }
      cout << N << endl;
      cout << eigenvalues(N) << endl;
      cout << choleski_decomp(N) << endl;
      */

      tmp=1.0;
    }
    //L.elem_value(i,i)=vmax*sqrt(tmp);
    L.elem_value(i,i)=sqrt(tmp);
  }


 
  //banded_lower_triangular_dvar_matrix vc=nograd_assign(L);
  save_identifier_string("rs");
  L.save_dvar_matrix_position();
  save_identifier_string("rt");
  MM.save_dvar_matrix_value();
  save_identifier_string("rl");
  MM.save_dvar_matrix_position();
  save_identifier_string("ro");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dfcholeski_decomp_banded);
  
  return L;
}

void dfcholeski_decomp_banded(void)
{
  verify_identifier_string("ro");
  dvar_matrix_position MMpos=restore_dvar_matrix_position();
  verify_identifier_string("rl");
  banded_symmetric_dmatrix M=
    restore_banded_symmetric_dvar_matrix_value(MMpos);
  verify_identifier_string("rt");
  dvar_matrix_position vcpos=restore_dvar_matrix_position();
  verify_identifier_string("rs");
  banded_lower_triangular_dmatrix dfL=
    restore_banded_lower_triangular_dvar_matrix_derivatives(vcpos);

  int n=M.indexmax();
  int bw=M.bandwidth();

  banded_lower_triangular_dmatrix L(1,n,bw);
  banded_lower_triangular_dmatrix tmp1(1,n,bw);
  banded_lower_triangular_dmatrix dftmp1(1,n,bw);
  banded_symmetric_dmatrix dfM(1,n,bw);
  dvector tmp(1,n);
  dvector dftmp(1,n);
  tmp.initialize();
  tmp1.initialize();
  dftmp.initialize();
  dftmp1.initialize();
  dfM.initialize();
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  if (M(1,1)<=0)
  {
    cerr << "Error matrix not positive definite in choleski_decomp"
      <<endl;
    M(1,1)=1.0;
    //ad_exit(1);
  }
  L(1,1)=sqrt(M(1,1));
  for (i=2;i<=bw;i++)
  {
    L(i,1)=M(i,1)/L(1,1);
  }

  for (i=2;i<=n;i++)
  {
    int jmin=admax(2,i-bw+1);
    for (j=jmin;j<=i-1;j++)
    {
      tmp1(i,j)=M(i,j);
      int kmin=max(1,j-bw+1,i-bw+1);
      for (k=kmin;k<=j-1;k++)
      {
        tmp1(i,j)-=L(i,k)*L(j,k);
      }
      L(i,j)=tmp1(i,j)/L(j,j);
    }
    tmp(i)=M(i,i);
    int kmin=admax(i-bw+1,1);
    //double vmax=fabs(L(i,kmin));
    //for (k=kmin;k<=i-1;k++)
   // {
     // if (fabs(L(i,k))>vmax) vmax=fabs(L(i,k));
   // }
    //tmp(i)/=square(vmax);
    for (k=kmin;k<=i-1;k++)
    {
      tmp(i)-=L(i,k)*L(i,k);
      //tmp(i)-=square(L(i,k)/vmax);
    }
    if (tmp(i)<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
        <<endl;
      tmp(i)=1.0;
      //ad_exit(1);
    }
    //L(i,i)=vmax*sqrt(tmp(i));
    L(i,i)=sqrt(tmp(i));
  }
 //*******************************************************************8
 //*******************************************************************8
 //*******************************************************************8
 
  for (i=n;i>=2;i--)
  {
    //L(i,i)=sqrt(tmp(i));
    dftmp(i)+=dfL(i,i)/(2.0*L(i,i));
    dfL(i,i)=0.0;
    int kmin=admax(i-bw+1,1);
    for (k=i-1;k>=kmin;k--)
    {
      //tmp(i)-=L(i,k)*L(i,k);
      dfL(i,k)-=2.*dftmp(i)*L(i,k);
    }
    //tmp(i)=M(i,i);
    dfM(i,i)+=dftmp(i);
    dftmp(i)=0.0;
    int jmin=admax(2,i-bw+1);
    for (j=i-1;j>=jmin;j--)
    {
      //L(i,j)=tmp1(i,j)/L(j,j);
      double linv=1./L(j,j);
      dftmp1(i,j)+=dfL(i,j)*linv;
      dfL(j,j)-=dfL(i,j)*tmp1(i,j)*linv*linv;
      dfL(i,j)=0.0;
      int kmin=max(1,j-bw+1,i-bw+1);
      for (k=j-1;k>=kmin;k--)
      {
        //tmp(i,j)-=L(i,k)*L(j,k);
        dfL(i,k)-=dftmp1(i,j)*L(j,k);
        dfL(j,k)-=dftmp1(i,j)*L(i,k);
      }
      //tmp(i,j)=M(i,j);
      dfM(i,j)+=dftmp1(i,j);
      dftmp1(i,j)=0.0;
    }
  }
  double linv=1./L(1,1);
  for (i=bw;i>=2;i--)
  {
    //L(i,1)=M(i,1)/L(1,1);
    dfM(i,1)+=dfL(i,1)*linv;
    dfL(1,1)-=dfL(i,1)*M(i,1)*linv*linv;
    dfL(i,1)=0.0;
  }
  //L(1,1)=sqrt(M(1,1));
  dfM(1,1)+=dfL(1,1)/(2.*L(1,1));


 //*******************************************************************8
 //*******************************************************************8
 //*******************************************************************8
  

  dfM.save_dmatrix_derivatives(MMpos);
}


dvar_matrix::dvar_matrix(_CONST banded_symmetric_dvar_matrix& S1)
{
  banded_symmetric_dvar_matrix& S= (banded_symmetric_dvar_matrix&) S1;
  int imin=S.indexmin();
  int imax=S.indexmax();
  int bw=S.bandwidth();
  allocate(imin,imax,imin,imax);
  int i1;
  int j1;
  initialize();
  for (int i=imin;i<=imax;i++)
  {
    for (int j=imin;j<=imax;j++)
    {
      if (j<=i)
      {
	j1=j;
	i1=i;
      }
      else
      {
	j1=i;
	i1=j;
      }
      if ( (i1-j1) < bw)
        (*this)(i,j)=S(i1,j1);
    }
  }
}

dvar_matrix::dvar_matrix(_CONST banded_lower_triangular_dvar_matrix& S1)
{
  banded_lower_triangular_dvar_matrix& S=
    (banded_lower_triangular_dvar_matrix&) S1;
  int imin=S.indexmin();
  int imax=S.indexmax();
  int bw=S.bandwidth();
  allocate(imin,imax,imin,imax);
  initialize();
  for (int i=imin;i<=imax;i++)
  {
    for (int j=imin;j<=imax;j++)
    {
      if (j<=i)
      {
        if ( (i-j) < bw)
          (*this)(i,j)=S(i,j);
      }
    }
  }
}

int max(int i,int j,int k)
{
  if (i>j)
    if ( i>k)
      return i;
    else
      return k;
  else
    if ( j>k)
      return j;
    else
      return k;
}

dmatrix restore_lower_triangular_dvar_matrix_value(const dvar_matrix_position& mpos)
{
  // restores the size, address, and value information for a dvar_matrix
  banded_lower_triangular_dmatrix out((BOR_CONST dvar_matrix_position&)mpos);
  int ierr;
  int min=out.rowmin();
  int max=out.rowmax();
  for (int i=max;i>=min;i--)
  {
    dvar_vector_position vpos=restore_dvar_vector_position();
    out(i)=restore_dvar_vector_value(vpos);
  }
  return out;
}

void check_choleski_decomp(
  _CONST banded_symmetric_dvar_matrix& MM, BOR_CONST int& _ierr)
{
  int& ierr=(int&)(_ierr);
  // kludge to deal with constantness
  ierr =0;
  banded_symmetric_dvar_matrix& M = (banded_symmetric_dvar_matrix&) MM;
  int n=M.indexmax();
  
  int bw=M.bandwidth();
  banded_lower_triangular_dvar_matrix L(1,n,bw);
#ifndef SAFE_INITIALIZE
    L.initialize();
#endif

  int i,j,k;
  double tmp;
    if (M(1,1)<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
       " value was " << M(1,1) << " for index  1"   <<endl;
      ierr=1;
      return;
      M(1,1)=1.0;
    }
  L.elem_value(1,1)=sqrt(value(M(1,1)));
  for (i=2;i<=bw;i++)
  {
    L.elem_value(i,1)=value(M(i,1))/L.elem_value(1,1);
  }

  for (i=2;i<=n;i++)
  {
    int jmin=admax(2,i-bw+1);
    for (j=jmin;j<=i-1;j++)
    {
      tmp=value(M(i,j));
      int kmin=max(1,j-bw+1,i-bw+1);
      for (k=kmin;k<=j-1;k++)
      {
        tmp-=L.elem_value(i,k)*L.elem_value(j,k);
      }
      L.elem_value(i,j)=tmp/L.elem_value(j,j);
    }
    tmp=value(M(i,i));
    int kmin=admax(i-bw+1,1);
    for (k=kmin;k<=i-1;k++)
    {
      tmp-=L.elem_value(i,k)*L.elem_value(i,k);
    }
    if (tmp<=0)
    {
      cerr << "Error matrix not positive definite in choleski_decomp"
       " value was " << tmp << " for index " << i    <<endl;
      ierr=1;
      return;
      tmp=1.0;
    }
    L.elem_value(i,i)=sqrt(tmp);
  }
}

dvariable norm(const banded_symmetric_dvar_matrix& B)
{
  return sqrt(norm2(B));
}

dvariable norm2(const banded_symmetric_dvar_matrix& B)
{
  dvariable nm=0.0;
  for (int i=1;i<=B.bw-1;i++)
  {
    nm+=norm2(B.d(i));
  }
  nm*=2;
  nm+=norm2(B.d(0));
  return nm;
}

