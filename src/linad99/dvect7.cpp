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
dvector log(const dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=log(t1.elem(i));
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
dvector exp(const dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=exp(t1.elem(i));
     }
     return(tmp);
  }

/**
 * Description not yet available.
 * \param
 */
dvector fabs(const dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=fabs(t1.elem(i));
     }
     return(tmp);
  }

/**
Returns the maximum value of vector vec.
Note: vec is an allocated vector.

\param vec scalar vector
*/
double max(const dvector& vec)
{
  int indexmin = vec.indexmin();
  int indexmax = vec.indexmax();
  double maximum = vec.elem(indexmin);
  for (int i = indexmin + 1; i <= indexmax; ++i)
  {
    double value = vec.elem(i);
    if (value > maximum) maximum = value;
  }
  return maximum;
}
/**
Returns the minimum value of vector vec.
Note: vec is an allocated vector.

\param vec scalar vector
 */
double min(const dvector& vec)
{
  int indexmin = vec.indexmin();
  int indexmax = vec.indexmax();
  double minimum = vec.elem(indexmin);
  for (int i = indexmin + 1; i <= indexmax; ++i)
  {
    double value = vec.elem(i);
    if (value < minimum) minimum = value;
  }
  return minimum;
}
