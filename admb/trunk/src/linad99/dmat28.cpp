/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

void get_eigenv(const dvector& _d,const dvector& _e,const dmatrix& _z);

#if !defined(OPT_LIB)
dvector banded_symmetric_dmatrix::operator () (int i)
{
  return d(i);
}

_CONST dvector banded_symmetric_dmatrix::operator () (int i) _CONST
{
  return d(i);
}

_CONST double& banded_symmetric_dmatrix::operator () (int i,int j) _CONST
{
  return d(i-j,i);
}

double& banded_symmetric_dmatrix::operator () (int i,int j)
{
  return d(i-j,i);
}

dvector banded_lower_triangular_dmatrix::operator () (int i)
{
  return d(i);
}

_CONST dvector banded_lower_triangular_dmatrix::operator () (int i) _CONST
{
  return d(i);
}

double& banded_lower_triangular_dmatrix::operator () (int i,int j)
{
  return d(i-j,i);
}

_CONST double& banded_lower_triangular_dmatrix::operator () (int i,int j) _CONST
{
  return d(i-j,i);
}

#endif


banded_symmetric_dmatrix::banded_symmetric_dmatrix(
  const banded_symmetric_dmatrix& BB,int _lb,int _ub) : d(0,BB.bw-1) , bw(BB.bw)
{
  banded_symmetric_dmatrix& B= (banded_symmetric_dmatrix&) BB;
  if (_lb<B.indexmin() || _ub>B.indexmax())
  {
    cerr << "bounds error" << endl;
    ad_exit(1);
  }
  d.allocate(0,bw-1);
  for (int i=0;i<=bw-1;i++)
  {
    d(i)=B.d(i)(i+_lb,_ub);
  }
}

void banded_symmetric_dmatrix::shift(int j)
{
  for (int i=0;i<bw;i++)
    d(i).shift(j+i);
}

void banded_lower_triangular_dmatrix::shift(int j)
{
  for (int i=0;i<bw;i++)
    d(i).shift(j+i);
}

 banded_symmetric_dmatrix::banded_symmetric_dmatrix
  (int _min,int _max,int _bw)
{
  bw=_bw;
  ivector  lb(0,bw-1);
  lb.fill_seqadd(_min,1);
  d.allocate(0,bw-1,lb,_max);
}

banded_symmetric_dmatrix::banded_symmetric_dmatrix
  (_CONST dvar_matrix_position& pos)
{
  int nrl=pos.row_min;
  int nrh=pos.row_max;
  int cmin=pos.lb(nrl);
  int cmax=pos.ub(nrl);
  bw=nrh-nrl+1;
  ivector lb(nrl,nrh);
  lb.fill_seqadd(cmin,1);
  d.allocate(nrl,nrh,lb,cmax);
}

banded_lower_triangular_dmatrix::banded_lower_triangular_dmatrix
  (_CONST dvar_matrix_position& pos)
{
  int nrl=pos.row_min;
  int nrh=pos.row_max;
  int cmin=pos.lb(nrl);
  int cmax=pos.ub(nrl);
  bw=nrh-nrl+1;
  ivector  lb(nrl,nrh);
  lb.fill_seqadd(cmin,1);
  d.allocate(nrl,nrh,lb,cmax);
}


dmatrix::dmatrix(_CONST banded_lower_triangular_dmatrix& S)
{
  int imin=S.indexmin();
  int imax=S.indexmax();
  int bw=S.bandwidth();
  allocate(imin,imax,imin,imax);
  for (int i=imin;i<=imax;i++)
  {
    for (int j=imin;j<=imax;j++)
    {
      if (j<=i)
      {
        if ( (i-j) < bw)
          (*this)(i,j)=S(i,j);
        else
          (*this)(i,j)=0.0;
      }
      else
      {
        (*this)(i,j)=0.0;
      }
    }
  }
}

dmatrix::dmatrix(_CONST banded_symmetric_dmatrix& S)
{
  int imin=S.indexmin();
  int imax=S.indexmax();
  int bw=S.bandwidth();
  allocate(imin,imax,imin,imax);
  int i1;
  int j1;
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
      else
        (*this)(i,j)=0.0;
    }
  }
}

banded_lower_triangular_dmatrix::banded_lower_triangular_dmatrix
  (int _min,int _max,int _bw)
{
  bw=_bw;
  ivector  lb(0,_bw-1);
  lb.fill_seqadd(_min,1);
  d.allocate(0,_bw-1,lb,_max);
}

ostream& operator << (BOR_CONST ostream& _ofs,_CONST banded_lower_triangular_dmatrix& S1)
{
  ostream & ofs = (ostream&) _ofs;
  banded_lower_triangular_dmatrix& S=(banded_lower_triangular_dmatrix&)(S1);
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
  return ofs;
}
banded_lower_triangular_dmatrix choleski_decomp(
  const banded_symmetric_dmatrix& MM)
{
  int ierr;
  return choleski_decomp(MM);
}

banded_lower_triangular_dmatrix choleski_decomp(
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
      if (ierr==0)
        cerr << "Error matrix not positive definite in choleski_decomp"
          <<endl;
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
      if (ierr==0)
        cerr << "Error matrix not positive definite in choleski_decomp"
          <<endl;
      ierr=1;
      return L;
    }
    L(i,i)=sqrt(tmp);
  }
  M.shift(minsave);
  L.shift(minsave);

  return L;
}

banded_symmetric_dmatrix& banded_symmetric_dmatrix::operator = 
  (const banded_symmetric_dmatrix& M)
{
  int _bw=M.bandwidth();
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  if (!allocated(d))
  {
    bw=_bw;
    ivector  lb(0,_bw-1);
    lb.fill_seqadd(mmin,1);
    d.allocate(0,_bw-1,lb,mmax);
  }
  if (bw<bandwidth()) initialize();

  if (M.indexmin() != indexmin() || M.indexmax() != indexmax()
    || M.bandwidth() > bandwidth() )
  {
    cerr << "incompatible shape in symmetric_dmatrix::operator = "
         << endl;
    ad_exit(1);

  }

  for (int i=mmin;i<=mmax;i++)
  {
    int jmin=admax(mmin,i-bw+1);
    for (int j=jmin;j<=i;j++)
    {
      (*this)(i,j)=M(i,j);
    }
  }
  return *this;
}
    

  banded_symmetric_dmatrix banded_symmetric_dmatrix::sub(int l,int u)   
  {
    return banded_symmetric_dmatrix(*this,l,u);
  }

  dvector eigenvalues(const banded_symmetric_dmatrix& _SS)
  {
    banded_symmetric_dmatrix& S = (banded_symmetric_dmatrix&) _SS;
    if (S.bandwidth() !=2)
    {
      cerr << "error bandwidth not equal 2" << endl;
      ad_exit(1);
    }
    int mmin=S.indexmin();
    int mmax=S.indexmax();
    dvector diag(mmin,mmax);
    dvector offdiag(mmin,mmax);
    diag=S(0);
    offdiag(mmin+1,mmax)=S(1);
    offdiag(mmin)=0.0;

    return get_eigen_values(diag.shift(1),offdiag.shift(1));
  }

    
  dmatrix eigenvectors(const banded_symmetric_dmatrix& _SS,const dvector& _e)
  {
    banded_symmetric_dmatrix& S = (banded_symmetric_dmatrix&) _SS;
    ADUNCONST(dvector,e);
    if (S.bandwidth() !=2)
    {
      cerr << "error bandwidth not equal 2" << endl;
      ad_exit(1);
    }
    int minsave=S.indexmin();
    S.shift(1);
    e.shift(1);
    int mmin=1;
    int mmax=S.indexmax();
    dvector diag(mmin,mmax);
    dvector offdiag(mmin,mmax);
    diag=S(0);
    offdiag(mmin+1,mmax)=S(1);
    offdiag(mmin)=0.0;
    dmatrix z(mmin,mmax,mmin,mmax);
    z.initialize();
    for (int i=mmin;i<=mmax;i++)
    {
      z(i,i)=1.0;
    }

    get_eigenv(diag,offdiag,z);
    e=diag;
    e.shift(minsave);
    S.shift(minsave);
    z.colshift(minsave);
    z.rowshift(minsave);
    return z;
  }

    
    
 
