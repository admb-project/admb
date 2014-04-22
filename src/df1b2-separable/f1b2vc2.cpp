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
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
  dvector value(const df1b2vector& _t1)
  {
     ADUNCONST(df1b2vector,t1)
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=value(t1(i));
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
  dmatrix value(const df1b2matrix& _m)
  {
    ADUNCONST(df1b2matrix,m)
    int nrl=m.indexmin();
    int nrh=m.indexmax();
    ivector ncl(nrl,nrh);
    ivector nch(nrl,nrh);
    int i;
    for (i=nrl;i<=nrh;i++)
    {
      ncl(i)=m(i).indexmin();
      nch(i)=m(i).indexmax();
    }
    dmatrix tmp(nrl,nrh,ncl,nch);
    for (i=nrl;i<=nrh;i++)
    {
      tmp(i)=value(m(i));
    }
    return tmp;
  }

/**
 * Description not yet available.
 * \param
 */
df1b2matrix&  df1b2matrix::operator = (const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)=M(i);
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2matrix&  df1b2matrix::operator = (const dmatrix& _M)
{
  ADUNCONST(dmatrix,M)
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i)=M(i);
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2matrix&  df1b2matrix::operator = (double M)
{
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    int jmin=(*this)(i).indexmin();
    int jmax=(*this)(i).indexmax();
    for (int j=jmin;j<=jmax;j++)
    {
      (*this)(i,j)=M;
    }
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2matrix&  df1b2matrix::operator = (const df1b2variable& _M)
{
  ADUNCONST(df1b2variable,M)
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    int jmin=(*this)(i).indexmin();
    int jmax=(*this)(i).indexmax();
    for (int j=jmin;i<=jmax;i++)
    {
      (*this)(i,j)=M;
    }
  }
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
df1b2matrix square(const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    // need special allocate so that = does not cause an assign.
    tmp(i).noallocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++)
    {
      tmp(i,j)=square(M(i,j));
    }
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void df1b2matrix::initialize(void)
{
  int rmin=indexmin();
  int rmax=indexmax();
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=(*this)(i).indexmin();
    int cmax=(*this)(i).indexmax();
    // need special allocate so that = does not cause an assign.
    for (int j=cmin;j<=cmax;j++)
    {
      (*this)(i,j)=0.0;
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
df1b2matrix mfexp(const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    // need special allocate so that = does not cause an assign.
    tmp(i).noallocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++)
    {
      tmp(i,j)=mfexp(M(i,j));
    }
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2matrix log(const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    // need special allocate so that = does not cause an assign.
    tmp(i).noallocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++)
    {
      tmp(i,j)=log(M(i,j));
    }
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2matrix sin(const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    // need special allocate so that = does not cause an assign.
    tmp(i).noallocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++)
    {
      tmp(i,j)=sin(M(i,j));
    }
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2matrix cos(const df1b2matrix& _M)
{
  ADUNCONST(df1b2matrix,M)
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    // need special allocate so that = does not cause an assign.
    tmp(i).noallocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++)
    {
      tmp(i,j)=cos(M(i,j));
    }
  }
  return tmp;
}
/*
df1b2matrix tan(const df1b2matrix& M)
{
  int rmin=M.indexmin();
  int rmax=M.indexmax();
  df1b2matrix tmp(rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=M(i).indexmin();
    int cmax=M(i).indexmax();
    // need special allocate so that = does not cause an assign.
    tmp(i).noallocate(cmin,cmax);
    for (int j=cmin;j<=cmax;j++)
    {
      tmp(i,j)=tan(M(i,j));
    }
  }
  return tmp;
}
*/
