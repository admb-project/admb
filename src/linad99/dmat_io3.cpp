/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
  #include <iomanip.h>
  #include <fstream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
  #include <iomanip.hpp>
  #include <fstream.hpp>
#endif

/**
Read values from input.

\param input uistream
\param value dmatrix
*/
uistream& operator>>(const uistream& input, const dmatrix& values)
{
  return const_cast<dmatrix&>(values).read_from(input);
}
/**
Read dmatrix from input.

\param input uistream
*/
uistream& dmatrix::read_from(const uistream& input)
{
  uistream& uis = const_cast<uistream&>(input);
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    uis >> elem(i);
  }
  if (uis.bad() || uis.fail())
  {
    cerr << " Error in dmatrix::read_from.\n";
    ad_exit(1);
  }
  return uis;
}
/**
Write values to output.

\param output uostream
\param value dmatrix
*/
uostream& operator<<(const uostream& output, const dmatrix& values)
{
  return values.write_on(output);
}
/**
Write dmatrix to output.

\param output uostream
*/
uostream& dmatrix::write_on(const uostream& output) const
{
  uostream& uos = const_cast<uostream&>(output);
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
    uos << elem(i);
  }
  if (uos.bad() || uos.fail())
  {
    cerr << " Error in dmatrix::write_on\n";
    ad_exit(1);
  }
  return uos;
}
