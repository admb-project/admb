/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Returns maximum value of all elements in ivec.

\param ivec ivector
*/
int Max(const ivector& ivec)
{
  return max(ivec);
}
/**
Returns maximum value of all elements in ivec.

\param ivec ivector
*/
int max(const ivector& t1)
{
  int min = ivec.indexmin();
  int max = ivec.indexmax();
  int maximum = ivec.elem(min);
  for (int i = min + 1; i <= max; ++i)
  {
    if (maximum < ivec.elem(i)) maximum = ivec.elem(i);
  }
  return maximum;
}
/**
Returns minimum value of all elements in ivec.

\param ivec ivector
*/
int min(const ivector& ivec)
{
  int min = ivec.indexmin();
  int max = ivec.indexmax();
  int minimum = ivec.elem(min);
  for (int i = min + 1; i <= max; ++i)
  {
    if (minimum > ivec.elem(i)) minimum = ivec.elem(i);
  }
  return minimum;
}
