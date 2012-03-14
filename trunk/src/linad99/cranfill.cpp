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
#include <fvar.hpp>

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <math.h>

/**
 * Description not yet available.
 * \param
 */
  double var(_CONST dvector& v)
  {
    double tmp;
    tmp=norm(v)/sqrt(double(v.size()));
    double tmp1;
    tmp1=mean(v);
    return(tmp*tmp-tmp1*tmp1);
  }

/**
 * Description not yet available.
 * \param
 */
  double std_dev(_CONST dvector& v)
  {
    double tmp;
    tmp=norm(v)/sqrt(double(v.size()));
    double tmp1;
    tmp1=mean(v);
    return(sqrt(tmp*tmp-tmp1*tmp1));
  }

/**
 * Description not yet available.
 * \param
 */
  double mean(_CONST dvector& v)
  {
    double tmp=0;
    for (int i=v.indexmin(); i<=v.indexmax(); i++)
    {
      tmp+=v.elem(i);
    }
    return(tmp/v.size());
  }

/**
 * Description not yet available.
 * \param
 */
  void dvector::fill_seqadd( CGNU_DOUBLE base, CGNU_DOUBLE offset)
  {
    double temp=0;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
       elem(i)=base+temp;
       temp=temp+offset;
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void ivector::fill_seqadd(int base, int offset)
  {
    int temp=0;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
       elem(i)=base+temp;
       temp=temp+offset;
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void lvector::fill_seqadd(BOR_CONST AD_LONG_INT& base,BOR_CONST AD_LONG_INT& offset)
  {
    long int temp=0;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
       elem(i)=base+temp;
       temp=temp+offset;
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void dmatrix::colfill_seqadd(BOR_CONST int& j, CGNU_DOUBLE base, CGNU_DOUBLE offset)
  {
    double temp=0;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=base+temp;
      temp=temp+offset;
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void dmatrix::colfill(int j,_CONST dvector& v)
  {
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      (*this)[i][j]=v[i];
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void dmatrix::rowfill(int i,_CONST dvector& v)
  {
    for (int j=colmin(); j<=colmax(); j++)
    {
      (*this)[i][j]=v[j];
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void dmatrix::rowfill_seqadd(BOR_CONST int& i, CGNU_DOUBLE base, CGNU_DOUBLE offset)
  {
    double temp=0;
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=base+temp;
      temp=temp+offset;
    }
  }
