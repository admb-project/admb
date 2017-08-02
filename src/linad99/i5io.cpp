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
Write iarray to output stream.

\param output ostream
\param iarray i5_array
*/
ostream& operator<<(const ostream& output, const i5_array& iarray)
{
  ostream& ostr = const_cast<ostream&>(output);
  for (int i = iarray.indexmin(); i <= iarray.indexmax(); ++i)
  {
    if (allocated(iarray(i)))
    {
      ostr << iarray(i);
    }
    if (i < iarray.indexmax())
    {
      ostr << '\n';
    }
  }
  return ostr;
}
/**
Read iarray from input stream.

\param input istream
\param iarray i5_array
*/
istream& operator>>(const istream& input, const i5_array& iarray)
{
  for (int i = iarray.indexmin(); i <= iarray.indexmax(); ++i)
  {
    if (allocated(iarray(i)))
    {
      input >> iarray(i);
    }
  }
  return const_cast<istream&>(input);
}
