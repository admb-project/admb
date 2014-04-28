/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file ranfill1.cpp
 * \brief Routines for filling objects (matrices and vectors)
 * \ingroup linad99
 * \author 
 * \author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 * \date 2/28/2011
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
void dvar_vector::fill_seqadd(const double base, const double offset)
  {
    RETURN_ARRAYS_INCREMENT();
    double temp=0;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
       elem(i) =base+temp;
       temp    =temp+offset;
    }
    RETURN_ARRAYS_DECREMENT();
  }
/**
 * Fills column of a matrix with a sequence of the form base, base+offset, base+2*offset,...
  \author Dave Fournier
  \date 2008-03-25
  \param  j the column
  \param  base is the starting value
  \param offset base+offset,base+offset*2,..., 
  \return imatrix with those value
 */
void imatrix::colfill_seqadd(int j, int base, int offset)
  {
    int temp=0;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      (*this)[i][j] = base+temp;
      temp          = temp+offset;
    }
  }
/**
 * Fills column of a matrix with a sequence of the form base, base+offset, base+2*offset,...
  \author Dave Fournier
  \date 2008-03-25
  \param  j the column
  \param  base is the starting value
  \param offset base+offset,base+offset*2,..., 
  \return dvar_matrix with those values
 */

void dvar_matrix::colfill_seqadd(const int& j, const double base,
  const double offset)
  {
    double temp=0;
    RETURN_ARRAYS_INCREMENT();
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j) =base+temp;
      temp      =temp+offset;
    }
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Fills vector with a sequence of the form base, base+offset, base+2*offset,...
  \author Dave Fournier
  \date 2008-03-25
  \param  base is the starting value
  \param offset base+offset,base+offset*2,..., 
  \return dvar_vector with those value
 */
void dvar_matrix::rowfill_seqadd(const int& i, const double base,
  const double offset)
  {
    double temp=0;
    RETURN_ARRAYS_INCREMENT();
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j) =base+temp;
      temp      =temp+offset;
    }
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Fills column of a matrix with a vector (supplied)
  \author Dave Fournier
  \date 2008-03-25
  \param  j the column
  \param  v is a vector to be inserted in the jth column
  \return dvar_matrix with those values
 */
void dvar_matrix::colfill(int j, const dvar_vector& v)
  {
    RETURN_ARRAYS_INCREMENT();
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      (*this)[i][j]=v[i];
    }
    RETURN_ARRAYS_DECREMENT();
  }

/**
 * Fills row of a matrix with a vector (supplied)
  \author Dave Fournier
  \date 2008-03-25
  \param  j the column
  \param  v is a vector to be inserted in the jth column
  \return dvar_matrix with those values
 */
void dvar_matrix::rowfill(int i, const dvar_vector& v)
  {
    RETURN_ARRAYS_INCREMENT();
    // for (int j=colmin(); j<=colmax(); j++)
    // {
    //   (*this)[i][j]=v[j];
    // }
    (*this)[i]=v;
    RETURN_ARRAYS_DECREMENT();
  }
