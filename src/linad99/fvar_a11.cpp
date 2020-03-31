/**
 * \file
 *
 * Author: David Fournier
 *
 * Copyright (c) 2008-2020 Regents of the University of California
 */
#include "fvar.hpp"

/**
Return a copy of the maximum element in variables vector.

\ingroup misc
\param variables is a dvar_vector
\returns maximum variable
*/
dvariable max(const dvar_vector& variables)
{
  int mmin = variables.indexmin();
  int mmax = variables.indexmax();
  dvariable maximum = variables.elem(mmin);
  for (int i = mmin + 1; i <= mmax; ++i)
  {
    if (maximum < variables.elem(i)) maximum = variables.elem(i);
  }
  return maximum;
}
/**
Return a copy of the minimum element in variables vector.

\ingroup misc
\param variables is a dvar_vector
\returns minimum variable
*/
dvariable min(const dvar_vector& variables)
{
  int mmin = variables.indexmin();
  int mmax = variables.indexmax();
  dvariable minimum = variables.elem(mmin);
  for (int i = mmin + 1; i <= mmax; ++i)
  {
    if (minimum > variables.elem(i)) minimum = variables.elem(i);
  }
  return minimum;
}
