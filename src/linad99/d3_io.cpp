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
Saves values from arr3 to output stream.
\param output ostream
\param arr3 d3_array
*/
ostream& operator<<(const ostream& output, const d3_array& arr3)
{
  ostream& ostr = const_cast<ostream&>(output);

  std::streamsize new_w = ostr.width();
  std::streamsize new_p = ostr.precision();
#if !defined(__cplusplus)
  long new_form = ostr.flags();
#else
  ios::fmtflags new_form = ostr.flags();
#endif
  char new_fill = ostr.fill();

  ostr.width(new_w);
  ostr.precision(new_p);
  ostr.flags(new_form);
  ostr.fill(new_fill);

  for (int i = arr3.slicemin(); i <= arr3.slicemax(); ++i)
  {
    ostr << arr3[i];
    if (i < arr3.slicemax())
    {
      ostr << endl;
    }
  }
  return ostr;
}
/**
Read values from input stream into arr3.

\param input istream
\param arr3 d3_array
*/
istream& operator>>(const istream& input, const d3_array& arr3)
{
  istream& istr = const_cast<istream&>(input);
  for (int i = arr3.slicemin(); i <= arr3.slicemax(); ++i)
  {
    istr >> arr3[i];
  }
  return istr;
}
