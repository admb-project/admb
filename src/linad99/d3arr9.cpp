/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>

/**
Fills d3_array with a sequence of values starting with initial
and incrementing with offset.

\param initial value
\param offset value
\return last sequence value
*/
double d3_array::fill_seqadd(double initial, double offset)
{
  double last = initial;
  int min = indexmin();
  int max = indexmax();
  dmatrix* pti = t + min;
  for (int i = min; i <= max; ++i)
  {
    last = pti->fill_seqadd(last, offset);
    ++pti;
  }
  return last;
}
