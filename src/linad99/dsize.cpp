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
#include "fvar.hpp"

/**
Returns total size of elements in vector x.
\param x vector
*/
unsigned int size_count(const dvector& x)
{
  return x.size();
}

/**
 * Description not yet available.
 * \param
 */
int size_count_partial(const dvector& x, int n)
{
  return n;
}

/**
Returns total size of elements in matrix x.
\param x matrix
*/
unsigned int size_count(const dmatrix& x)
{
  unsigned int count = 0;
  int min = x.rowmin();
  int max = x.rowmax();
  for (int i = min;i <= max; ++i)
  {
    count += size_count(x(i));
  }
  return count;
}

/**
 * Description not yet available.
 * \param
 */
int size_count_partial(const dmatrix& x, int n)
{
  int tmp=0;
  int min=x.rowmin();
  int max=x.rowmax();
  for (int i=min;i<=max;i++)
  {
    tmp+=size_count_partial(x(i),n);
  }
  return tmp;
}

/**
Returns total size of elements in d3_array x.
\param x matrix
*/
unsigned int size_count(const d3_array& x)
{
  unsigned int count = 0;
  int min = x.slicemin();
  int max = x.slicemax();
  for (int i = min; i <= max; ++i)
  {
    count += size_count(x(i));
  }
  return count;
}

/**
 * Description not yet available.
 * \param
 */
int size_count_partial(const d3_array& x,int n)
{
  int tmp=0;
  int min=x.slicemin();
  int max=x.slicemax();
  for (int i=min;i<=max;i++)
  {
    tmp+=size_count_partial(x(i),n);
  }
  return tmp;
}
