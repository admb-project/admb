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
Write value from varr4 to output stream.

\param output uostream
\param varr4 dvar4_array
*/
uostream& operator<<(const uostream& output, const dvar4_array& varr4)
{
  uostream& ostr = const_cast<uostream&>(output);
  for (int i = varr4.hslicemin(); i <= varr4.hslicemax(); ++i)
  {
    ostr << varr4[i];
  }
  return ostr;
}
/**
Read values to varr4 from input stream.

\param input uistream
\param varr4 dvar4_array
*/
uistream& operator>>(const uistream& input,const dvar4_array &varr4)
{
  uistream& istr = const_cast<uistream&>(input);
  for (int i = varr4.hslicemin(); i <= varr4.hslicemax(); ++i)
  {
    istr >> varr4[i];
  }
  return istr;
}
