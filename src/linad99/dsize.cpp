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
 * Description not yet available.
 * \param
 */
int size_count(const dvector& x)
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
 * Description not yet available.
 * \param
 */
int size_count(const dmatrix& x)
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
 * Description not yet available.
 * \param
 */
int size_count(const d3_array& x)
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
