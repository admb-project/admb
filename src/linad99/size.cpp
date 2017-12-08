/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Returns size of dvar_vector x.

\param x dvar_vector
*/
unsigned int size_count(const dvar_vector& x)
{
  return !(x) ? 0 : x.size();
}

/**
 * Description not yet available.
 * \param
 */
int size_count_partial(const dvar_vector& x,int n)
{
  if (!(x))
    return 0;
  else
    return max(0, n);
}

/**
Returns size of dvar_matrix x.

\param x dvar_matrix
*/
unsigned int size_count(const dvar_matrix& x)
{
  unsigned int size = 0;
  if (!(x) == false)
  {
    int min = x.rowmin();
    int max = x.rowmax();
    for (int i = min; i <= max; ++i)
    {
      size += size_count(x(i));
    }
  }
  return size;
}

/**
 * Description not yet available.
 * \param
 */
int size_count_partial(const dvar_matrix& x, int n)
{
  if (!(x))
    return 0;
  else
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
}
/**
Returns size of dvar3_array x.

\param x dvar3_array
*/
unsigned int size_count(const dvar3_array& x)
{
  unsigned int size = 0;
  if (!(x) == false)
  {
    int min = x.slicemin();
    int max = x.slicemax();
    for (int i = min; i <= max; ++i)
    {
      size += size_count(x(i));
    }
  }
  return size;
}
/**
Returns size of dvar4_array x.

\param x dvar4_array
*/
unsigned int size_count(const dvar4_array& x)
{
  unsigned int size = 0;
  if (!(x) == false)
  {
    int min = x.indexmin();
    int max = x.indexmax();
    for (int i = min; i <= max; ++i)
    {
      size += size_count(x(i));
    }
  }
  return size;
}
/**
Returns size of d4_array x.

\param x d4_array
*/
unsigned int size_count(const d4_array& x)
{
  unsigned int size = 0;
  if (!(x) == false)
  {
    int min = x.indexmin();
    int max = x.indexmax();
    for (int i = min; i <= max; ++i)
    {
      size += size_count(x(i));
    }
  }
  return size;
}

/**
 * Description not yet available.
 * \param
 */
int size_count_partial(const dvar3_array& x, int n)
{
  if (!(x))
    return 0;
  else
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
}
