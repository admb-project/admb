/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
  #include <iomanip.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
  #include <iomanip.hpp>
#endif

/**
Exits if the dimensions of a and b dvector are not equal.

\param a dvector
\param b dvector
\param message to include with output
*/
void shape_check(
  const dvector& a,
  const dvector& b,
  const char* message)
{
  if (a.indexmin() != b.indexmin() || a.indexmax() != b.indexmax())
  {
    cerr << " Vector sizes do no match in" << message << "\n";
    ad_exit(1);
  }
}
