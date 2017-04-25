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
#include <fvar.hpp>
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

/**
Returns new vector containing all values from t1 and t2.
\param t1 vector
\param t2 vector
*/
dvector operator&(const dvector& t1, const dvector& t2)
{
  unsigned int size = t1.size() + t2.size();
#ifndef OPT_LIB
  assert(size <= INT_MAX);
#endif
  dvector tmp(1, static_cast<int>(size));
  int min = t1.indexmin();
  int max = t1.indexmax();
  int ii = 0;
  int i;
  for (i = min; i <= max; ++i)
  {
    tmp(++ii) = t1(i);
  }
  min = t2.indexmin();
  max = t2.indexmax();
  for (i = min; i <= max; ++i)
  {
    tmp(++ii) = t2(i);
  }
  return tmp;
}
/**
Returns new vector containing all values from t1 and t2.
\param t1 vector
\param t2 vector
*/
dvar_vector operator&(const dvar_vector& t1, const dvar_vector& t2)
{
  unsigned int size = t1.size() + t2.size();
  dvar_vector tmp(1, static_cast<int>(size));
  int min = t1.indexmin();
  int max = t1.indexmax();
  int ii = 0;
  int i;
  for (i = min; i <= max; ++i)
  {
    tmp(++ii) = t1(i);
  }
  min = t2.indexmin();
  max = t2.indexmax();
  for (i = min; i <= max; ++i)
  {
    tmp(++ii) = t2(i);
  }
  return tmp;
}
