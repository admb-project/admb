/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

/**
\ingroup misc
Return maximum value variables.
\param variables dvar_vector
\returns the maximum of the vector
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
\ingroup misc
Return minimum value variables.
\param variables dvar_vector
\returns the minimum of the vector
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
