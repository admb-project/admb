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
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    last = elem(i).fill_seqadd(last, offset);
  }
  return last;
}
