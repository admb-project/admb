/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
// i/o operations for class dmatrix

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
Save values from arr3 to output stream.

\param output uostream
\param arr3 d3_array
*/
uostream& operator<<(const uostream& output, const d3_array& arr3)
{
  uostream& uos = const_cast<uostream&>(output);
  for (int i = arr3.slicemin(); i <= arr3.slicemax(); ++i)
  {
    uos << arr3[i];
  }
  return uos;
}
/**
Read values from input stream to arr3.

\param input uistream
\param arr3 d3_array
*/
uistream& operator>>(const uistream& input, const d3_array& arr3)
{
  uistream& uis = const_cast<uistream&>(input);
  for (int i = arr3.slicemin(); i <= arr3.slicemax(); ++i)
  {
    uis >> arr3[i];
  }
  return uis;
}
/**
Save values from varr3 to output stream.

\param output uostream
\param varr3 dvar3_array
*/
uostream& operator<<(const uostream& output, const dvar3_array& varr3)
{
  uostream& uos = const_cast<uostream&>(output);
  for (int i = varr3.slicemin(); i <= varr3.slicemax(); ++i)
  {
    uos << varr3[i];
  }
  return uos;
}
/**
Read values from input stream to varr3.

\param input uistream
\param varr3 dvar3_array
*/
uistream& operator>>(const uistream& input, const dvar3_array& varr3)
{
  uistream& uis = const_cast<uistream&>(input);
  for (int i = varr3.slicemin(); i <= varr3.slicemax(); ++i)
  {
    uis >> varr3[i];
  }
  return uis;
}
