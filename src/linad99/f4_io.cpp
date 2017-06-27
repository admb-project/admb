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
Write values from varr4 to output stream.

\param output ostream
\param varr4 dvar4_array
*/
ostream& operator<<(const ostream& output, const dvar4_array& varr4)
{
  ostream& ostr = const_cast<ostream&>(output);
  for (int i = varr4.hslicemin(); i <= varr4.hslicemax(); ++i)
  {
    ostr << varr4[i];
    if (i < varr4.hslicemax())
    {
      ostr << endl;
    }
  }
  return ostr;
}
/**
Read values to varr4 from input stream.

\param input istream
\param varr4 dvar4_array
*/
istream& operator>>(const istream& input, const dvar4_array& varr4)
{
  istream& istr = const_cast<istream&>(input);
  for (int i = varr4.hslicemin(); i <= varr4.hslicemax(); ++i)
  {
    istr >> varr4[i];
  }
  return istr;
}
/**
Outputs dvar5_array z.
*/
ostream& operator<<(ostream& ostr, const dvar5_array& z)
{
  for (int i = z.indexmin(); i <= z.indexmax(); i++)
  {
    ostr << z[i];
    if (i < z.indexmax())
    {
      ostr << '\n';
    }
  }
  return ostr;
}
/**
Outputs dvar5_array z.
*/
ostream& operator<<(const ostream& ostr, const dvar5_array& z)
{
  return operator<<((ostream&)ostr, z);
}

/**
 * Description not yet available.
 * \param
 */
istream& operator>>(const istream& istr, const dvar5_array &z)
{
  for (int i=z.indexmin();i<=z.indexmax();i++)
  {
    istr >> z[i];
  }
  return (istream&) istr;
}

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(const ostream& ostr, const dvar6_array &z)
{
  for (int i=z.indexmin();i<=z.indexmax();i++)
  {
    ostr << z[i];
  }
  return (ostream&) ostr;
}

/**
 * Description not yet available.
 * \param
 */
istream& operator>>(const istream& istr, const dvar6_array &z)
{
  for (int i=z.indexmin();i<=z.indexmax();i++)
  {
    istr >> z[i];
  }
  return (istream&) istr;
}
