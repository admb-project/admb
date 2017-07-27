/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#if (__cplusplus > 199711L)
  #include <iterator>
  #include <algorithm>
#endif
#include "fvar.hpp"

/**
Assigns element values from other to imatrix.

\param other imatrix
*/
imatrix& imatrix::operator=(const imatrix& other)
{
  if (allocated(*this))
  {
    if (rowmin() != other.rowmin() || rowmax() != other.rowmax()
        || colmin() != other.colmin() || colmax() != other.colmax())
    {
      cerr << "Incompatible array bounds in "
           << "imatrix& imatrix::operator=(const imatrix&)\n";
      ad_exit(1);
    }
    // check for condition that both matrices point to the same object
    if (m != other.m)
    {
#if (__cplusplus <= 199711L)
      for (int i = rowmin(); i <= rowmax(); ++i)
      {
        *(m+i) = other[i];
      }
#else
      ivector* iter = other.begin();
      std::for_each(begin(), end(), [&iter](ivector& v) {
        v = *iter;
        ++iter;
      });
#endif
    }
  }
  else
  {
     index_min = other.index_min;
     index_max = other.index_max;
     shape = other.shape;
     if (shape)
     {
       (shape->ncopies)++;
     }
     m = other.m;
  }
  return *this;
}
/**
Assigns value to all elements of imatrix.

\param value integer
*/
imatrix& imatrix::operator=(const int value)
{
#if (__cplusplus <= 199711L)
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    elem(i) = value;
  }
#else
  std::for_each(begin(), end(), [value](ivector& v) {
    v = value;
  });
#endif
  return *this;
}
