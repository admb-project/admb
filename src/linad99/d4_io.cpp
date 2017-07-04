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
ostream& operator<<(const ostream& output, const d4_array& values)
{
  ostream& ostr = const_cast<ostream&>(output);
  for (int i = values.hslicemin(); i <= values.hslicemax(); ++i)
  {
    ostr << values[i] << endl;
  }
  return ostr;
}
/**
Read from input to values.

\param input uistream
\param values d4_array
*/
istream& operator>>(const istream& input, const d4_array& values)
{
  istream& istr = const_cast<istream&>(input);
  for (int i = values.hslicemin(); i <= values.hslicemax(); ++i)
  {
    istr >> values[i];
  }
  return istr;
}
/**
Write values to output.

\param output uostream
\param values d5_array
*/
ostream& operator<<(const ostream& output, const d5_array& values)
{
  ostream& ostr = const_cast<ostream&>(output);
  for (int i = values.indexmin(); i <= values.indexmax(); ++i)
  {
    ostr << values[i] << endl;
  }
  return ostr;
}
/**
Read from input to values.

\param input uistream
\param values d4_array
*/
istream& operator>>(const istream& input, const d5_array& values)
{
  istream& istr = const_cast<istream&>(input);
  for (int i = values.indexmin(); i <= values.indexmax(); ++i)
  {
    istr >> values[i];
  }
  return istr;
}

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(const ostream& _ostr, const d6_array &z)
{
  uostream & ostr = (uostream&) _ostr;
  for (int i=z.indexmin();i<=z.indexmax();i++)
  {
    ostr << z[i] << endl;
  }
  return ostr;
}

/**
 * Description not yet available.
 * \param
 */
istream& operator>>(const istream& _istr, const d6_array &z)
{
  uistream & istr = (uistream&) _istr;
  for (int i=z.indexmin();i<=z.indexmax();i++)
  {
    istr >> z[i];
  }
  return istr;
}
