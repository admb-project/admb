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
/*
#if defined(__x86_64) || (defined(_MSC_VER) && defined(_M_X64))
  #include <stdint.h>
#endif
*/

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_matrix::allocate(int mmin,int mmax,int cmin,int cmax,
  double _minb,double _maxb)
{
  minb=_minb;
  maxb=_maxb;
  df1b2_init_matrix::allocate(mmin,mmax,cmin,cmax);
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_matrix::allocate(int mmin,int mmax,int cmin,int cmax,
  double _minb,double _maxb,const char * s)
{
  minb=_minb;
  maxb=_maxb;
  df1b2_init_matrix::allocate(mmin,mmax,cmin,cmax,s);
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_matrix::allocate(int mmin,int mmax,
  const index_type& cmin,const index_type& cmax,double _minb,double _maxb,
  const char * s)
{
  minb=_minb;
  maxb=_maxb;
  df1b2_init_matrix::allocate(mmin,mmax,cmin,cmax,s);
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_matrix::allocate(int mmin,int mmax,
  const index_type& cmin,const index_type& cmax,double _minb,double _maxb,
  int phase,const char * s)
{
  minb=_minb;
  maxb=_maxb;
  df1b2_init_matrix::allocate(mmin,mmax,cmin,cmax,phase,s);
  df1b2matrix::operator = ((minb+maxb)/2.0);
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_matrix::allocate(int mmin,int mmax,int cmin,int cmax,
  double _minb,double _maxb,int phase,const char * s)
{
  minb=_minb;
  maxb=_maxb;
  df1b2_init_matrix::allocate(mmin,mmax,cmin,cmax,phase,s);
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const df1b2matrix& _m,const init_df1b2vector& _v, const int& _ii,
  double fmin,double fmax,const df1b2variable& fpen)
{
  ADUNCONST(int,ii)
  ADUNCONST(df1b2matrix,m)
  ADUNCONST(init_df1b2vector,v)
  int min=m.indexmin();
  int max=m.indexmax();
  for (int i=min;i<=max;i++)
  {
    int cmin=m(i).indexmin();
    int cmax=m(i).indexmax();
    for (int j=cmin;j<=cmax;j++)
    {
      m(i,j)=boundp(v(ii++),fmin,fmax,fpen);
    }
  }
}

void set_value(const df1b2matrix& _m,const init_df1b2vector& _v, const int& _ii,
  double fmin,double fmax,const df1b2variable& fpen,double s)
{
  ADUNCONST(int,ii)
  ADUNCONST(df1b2matrix,m)
  ADUNCONST(init_df1b2vector,v)
  int min=m.indexmin();
  int max=m.indexmax();
  for (int i=min;i<=max;i++)
  {
    int cmin=m(i).indexmin();
    int cmax=m(i).indexmax();
    for (int j=cmin;j<=cmax;j++)
    {
      m(i,j)=boundp(v(ii++),fmin,fmax,fpen,s);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_matrix::set_value(const init_df1b2vector& _x,
  const int& ii,const df1b2variable& pen)
{
  init_df1b2vector& x=(init_df1b2vector&) _x;
  int ii1=ii;
  if (initial_df1b2params::pointer_table)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      int cmin=(*this)(i).indexmin();
      int cmax=(*this)(i).indexmax();
      for (int j=cmin;j<=cmax;j++)
      {
#if defined(__x86_64) || (defined(_MSC_VER) && defined(_M_X64))
        intptr_t tmp =(intptr_t)(&((*this)(i,j)));
#else
        int tmp= (int)( &((*this)(i,j)) );
#endif
        (*initial_df1b2params::pointer_table)(ii1)(1)=tmp;
        (*initial_df1b2params::pointer_table)(ii1)(2)=x(ii1).ind_index;
        ii1++;
      }
    }
  }
  if (scalefactor==0.0)
  {
    ::set_value(*this,x,ii,minb,maxb,pen);
  }
  else
  {
    ::set_value(*this,x,ii,minb,maxb,pen,scalefactor);
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const df1b2_init_bounded_matrix & _v,const dvector& x,
  const int& _ii,double fmin,double fmax)
{
  ADUNCONST(int,ii)
  ADUNCONST(df1b2_init_bounded_matrix,v)
  double fpen=0.0;
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    int cmin=v(i).indexmin();
    int cmax=v(i).indexmax();
    for (int j=cmin;j<=cmax;j++)
    {
      v(i,j)=boundp(x(ii++),fmin,fmax,fpen);
    }
  }
}


void set_value(const df1b2_init_bounded_matrix & _v,const dvector& x,
  const int& _ii,double fmin,double fmax,double s)
{
  ADUNCONST(int,ii)
  ADUNCONST(df1b2_init_bounded_matrix,v)
  double fpen=0.0;
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    int cmin=v(i).indexmin();
    int cmax=v(i).indexmax();
    for (int j=cmin;j<=cmax;j++)
    {
      v(i,j)=boundp(x(ii++),fmin,fmax,fpen,s);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_matrix::set_value(const dvector& x,
  const int& ii)
{
  //double pen=0.0;
  ::set_value(*this,x,ii,minb,maxb);
}
