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
  void dvar_vector::fill_seqadd( CGNU_DOUBLE base, CGNU_DOUBLE offset)
  {
    RETURN_ARRAYS_INCREMENT();
    double temp=0;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
       elem(i)=base+temp;
       temp=temp+offset;
    }
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Description not yet available.
 * \param
 */
  void dvar_matrix::colfill_seqadd(BOR_CONST int& j, CGNU_DOUBLE base, CGNU_DOUBLE offset)
  {
    double temp=0;
    RETURN_ARRAYS_INCREMENT();
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=base+temp;
      temp=temp+offset;
    }
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Description not yet available.
 * \param
 */
  void dvar_matrix::rowfill_seqadd(BOR_CONST int& i, CGNU_DOUBLE base, CGNU_DOUBLE offset)
  {
    double temp=0;
    RETURN_ARRAYS_INCREMENT();
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=base+temp;
      temp=temp+offset;
    }
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Description not yet available.
 * \param
 */
  void dvar_matrix::colfill(int j,_CONST dvar_vector& v)
  {
    RETURN_ARRAYS_INCREMENT();
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      (*this)[i][j]=v[i];
    }
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Description not yet available.
 * \param
 */
  void dvar_matrix::rowfill(int i,_CONST dvar_vector& v)
  {
    RETURN_ARRAYS_INCREMENT();
    // for (int j=colmin(); j<=colmax(); j++)
    // {
    //   (*this)[i][j]=v[j];
    // }
    (*this)[i]=v;
    RETURN_ARRAYS_DECREMENT();
  }
