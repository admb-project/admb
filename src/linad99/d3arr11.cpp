/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

#ifndef OPT_LIB
/**
Return dmatrix elment in d3_array indexed by i.

\param i index
*/
const dmatrix& d3_array::operator()(int i) const
{
  if (i < slicemin())
  {
    cerr << "matrix bound exceeded"
         << " -- row index too low in 3d_array::operator[]"
         << "value was" << i;
    ad_exit(1);
  }
  if (i > slicemax())
  {
    cerr << "matrix bound exceeded"
         << " -- row index too high in 3d_array::operator[]"
         << "value was" << i;
    ad_exit(1);
  }
  return t[i];
}
#endif
