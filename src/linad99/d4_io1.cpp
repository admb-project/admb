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
Write values to output.

\param output uostream
\param values d4_array
*/
uostream& operator<<(const uostream& output, const d4_array& values)
{
  uostream& ostr = const_cast<uostream&>(output);
  for (int i = values.hslicemin(); i <= values.hslicemax(); ++i)
  {
    ostr << values[i];
  }
  return ostr;
}
/**
Read from input to values.

\param input uistream
\param values d4_array
*/
uistream& operator>>(const uistream& input, const d4_array& values)
{
  uistream& istr = const_cast<uistream&>(input);
  for (int i = values.hslicemin(); i <= values.hslicemax(); ++i)
  {
    istr >> values[i];
  }
  return istr;
}
