/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
Add values to dvector element-wise.

\param values dvector
*/
dvector& dvector::operator+=(const dvector& values)
{
  if (indexmin() != values.indexmin() || indexmax() != values.indexmax())
  {
    cerr << " Incompatible array bounds in "
         << "dvector& operator+=(const dvector&)\n";
    ad_exit(1);
  }
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    elem(i) += values.elem(i);
  }
  return *this;
}
/**
Subtract values from dvector element-wise.

\param values dvector
 */
dvector& dvector::operator-=(const dvector& values)
{
  if (indexmin() != values.indexmin() || indexmax() != values.indexmax())
  {
    cerr << " Incompatible array bounds in "
         << "dvector& operator-=(const dvector&)\n";
    ad_exit(1);
  }
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    elem(i) -= values.elem(i);
  }
  return *this;
}
/**
Add value to each element of dvector.

\param value double
*/
dvector& dvector::operator+=(const double value)
{
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    elem(i) += value;
  }
  return *this;
}
/**
Subtract value to each element of dvector.

\param value double
*/
dvector& dvector::operator-=(const double value)
{
  for (int i = indexmin(); i <= indexmax(); ++i)
  {
    elem(i) -= value;
  }
  return *this;
}
