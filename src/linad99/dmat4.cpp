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
 * Description not yet available.
 * \param
 */
struct dvec_ptr_ptr
{
  void** m;
};

/**
Assign values in other to dmatrix.

\param other dmatrix
*/
dmatrix& dmatrix::operator=(const dmatrix& other)
{
  if (allocated(*this))
  {
    if (rowmin() != other.rowmin() || rowmax() != other.rowmax()
        || colmin() != other.colmin() || colmax() != other.colmax())
    {
      cerr << "Incompatible array bounds in "
           << "dmatrix& dmatrix::operator=(const dmatrix&)\n";
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
      dvector* iter = other.begin();
      std::for_each(begin(), end(), [&iter](dvector& v) {
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
Add element-wise matrix values other to dmatrix.

\param other dmatrix
*/
dmatrix& dmatrix::operator+=(const dmatrix& other)
{
  if (rowmin() != other.rowmin() || rowmax() != other.rowmax() )
  {
    cerr << "Incompatible array bounds in "
         << "dmatrix& dmatrix::operator+=(const dmatrix&)\n";
    ad_exit(1);
  }
#if (__cplusplus <= 199711L)
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i) += other.elem(i);
  }
#else
  dvector* iter = other.begin();
  std::for_each(begin(), end(), [&iter](dvector& v) {
    v += *iter;
    ++iter;
  });
#endif
  return *this;
}
/**
Substract element-wise matrix values other from dmatrix.

\param other dmatrix
*/
dmatrix& dmatrix::operator-=(const dmatrix& other)
{
  if (rowmin() != other.rowmin() || rowmax() != other.rowmax() )
  {
    cerr << "Incompatible array bounds in "
         << "dmatrix& dmatrix::operator-=(const dmatrix&)\n";
    ad_exit(1);
  }
#if (__cplusplus <= 199711L)
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    elem(i) -= other.elem(i);
  }
#else
  dvector* iter = other.begin();
  std::for_each(begin(), end(), [&iter](dvector& v) {
    v -= *iter;
    ++iter;
  });
#endif
  return *this;
}
