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
 * Description not yet available.
 * \param
 */
int size_count(const dvar_matrix& x)
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
      tmp+=size_count(x(i));
    }
    return tmp;
  }
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
 * Description not yet available.
 * \param
 */
int size_count(const dvar3_array& x)
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
      tmp+=size_count(x(i));
    }
    return tmp;
  }
}

/**
 * Description not yet available.
 * \param
 */
int size_count(const dvar4_array& x)
{
  if (!(x))
    return 0;
  else
  {
    int tmp=0;
    int min=x.indexmin();
    int max=x.indexmax();
    for (int i=min;i<=max;i++)
    {
      tmp+=size_count(x(i));
    }
    return tmp;
  }
}

/**
 * Description not yet available.
 * \param
 */
int size_count(const d4_array& x)
{
  if (!(x))
    return 0;
  else
  {
    int tmp=0;
    int min=x.indexmin();
    int max=x.indexmax();
    for (int i=min;i<=max;i++)
    {
      tmp+=size_count(x(i));
    }
    return tmp;
  }
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
