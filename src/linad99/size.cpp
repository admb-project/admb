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
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
int size_count(_CONST dvar_vector& x)
{
  if (!(x))
    return 0;
  else  
    return x.size();
}

/**
 * Description not yet available.
 * \param
 */
int size_count_partial(_CONST dvar_vector& x,int n)
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
int size_count(_CONST dvar_matrix& x)
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
int size_count_partial(_CONST dvar_matrix& x, int n)
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
int size_count(_CONST dvar3_array& x)
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
int size_count(_CONST dvar4_array& x)
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
int size_count(_CONST d4_array& x)
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
int size_count_partial(_CONST dvar3_array& x, int n)
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
