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
Save iarr3 to output stream.

\param output ostream
\param iarr3 i3_array
*/
ostream& operator<<(const ostream& output, const i3_array& iarr3)
{
  ostream& ostr = const_cast<ostream&>(output);
  for (int i = iarr3.slicemin(); i <= iarr3.slicemax(); ++i)
  {
    if (allocated(iarr3[i]))
    {
      ostr << iarr3[i];
    }
    if (i < iarr3.slicemax())
    {
      ostr << endl;
    }
  }
  return ostr;
}
/**
Read to iarr3 from input stream.

\param input istream
\param iarr3 i3_array
*/
istream& operator>>(const istream& input, const i3_array& iarr3)
{
  istream& istr = const_cast<istream&>(input);
  for (int i = iarr3.slicemin(); i <= iarr3.slicemax(); ++i)
  {
    if (allocated(iarr3[i]))
    {
      istr >> iarr3[i];
    }
  }
  return istr;
}
