/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
void initial_df1b2params::reset_all(const dvector& x)
{
  int ii=1;
  for (int i=0;i<num_initial_df1b2params;i++)
  {
    (varsptr[i])->set_value(x,ii);
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_vector::set_value(const dvector& x,const int& _ii)
{
  ADUNCONST(int,ii)
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    //cout << x(ii) << " ";
    (*this)(i) = (x(ii++));
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_matrix::set_value(const dvector& x,const int& _ii)
{
  ADUNCONST(int,ii)
  int rmin=indexmin();
  int rmax=indexmax();
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=(*this)(i).indexmin(); 
    int cmax=(*this)(i).indexmax(); 
    for (int j=cmin;j<=cmax;j++)
    {
      (*this)(i,j) = (x(ii++));
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const df1b2_init_bounded_vector & _v,const dvector& x,
  const int& _ii,double fmin,double fmax)
{
  ADUNCONST(int,ii)
  ADUNCONST(df1b2_init_bounded_vector,v)
  double fpen=0.0;
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    v(i)=boundp(x(ii++),fmin,fmax,fpen);
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_number::set_value(const dvector& x,const int& _ii)
{
  ADUNCONST(int,ii)
  operator = (x(ii++));
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const df1b2variable& _u,const dvector& x,const int& _ii,
  double fmin,double fmax)
{
  double fpen=0.0;
  ADUNCONST(int,ii)
  ADUNCONST(df1b2variable,u)
  u=boundp(x(ii++),fmin,fmax,fpen);
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const df1b2vector& _x,const dvector& v, const int& _ii,
  double fmin,double fmax)
{
  double fpen=0.0;
  ADUNCONST(int,ii)
  ADUNCONST(df1b2vector,x)
  int min=x.indexmin();
  int max=x.indexmax();
  for (int i=min;i<=max;i++)
  {
    (x)(i)=boundp(v(ii++),fmin,fmax,fpen);
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_vector::set_value(const dvector& x,
  const int& ii)
{
  //double pen=0.0;
  ::set_value(*this,x,ii,minb,maxb);
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_dev_vector::set_value(const dvector& x,
  const int& ii)
{
  df1b2_init_bounded_vector::set_value(x,ii);
  //df1b2variable m=mean(*this);
  //pen+=1000.0*square(m);
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_number::set_value(const dvector& x,const int& _ii)
{
  ADUNCONST(int,ii)
  //double pen=0.0;
  ::set_value(*this,x,ii,minb,maxb);
}
