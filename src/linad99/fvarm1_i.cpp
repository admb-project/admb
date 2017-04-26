/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
\file
i/o operations for class dvar_matrix
*/
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
  #include <iomanip.h>
  #include <fstream.h>
  #define __USE_IOSTREAM__
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
  #include <iomanip.hpp>
  #include <fstream.hpp>
  #define __USE_IOSTREAM__
#endif

// unformatted i/o

#ifdef __USE_IOSTREAM__
/**
Operator to read values to dvar_matrix form input stream istr.
\param istr output stream
\param _z dvar_matrix values
*/
uistream& operator>>(const uistream& istr, const dvar_matrix& _z)
{
  ADUNCONST(dvar_matrix,z)
  z.read_from(istr);
  return (uistream&)istr;
}
/**
Read values to dvar_matrix from input stream s.
\param s input stream
*/
void dvar_matrix::read_from(const uistream& s)
{
  if (allocated(*this))
  {
    //size = max - min + 1;
    int n = rowmax();
    for (int i = rowmin(); i <= n; ++i)
    {
      s >> (*this)[i];
      if (!s.good())
      {
        cerr << " Error: Unable to read dvar_matrix from uostream in "
             << __FILE__ << ':' << __LINE__ << '\n';
        ad_exit(1);
      }
    }
  }
}
/**
Operator to write values from dvar_matrix to output stream ostr.
\param ostr output stream
\param z dvar_matrix values
*/
uostream& operator<<(const uostream& ostr, const dvar_matrix& z)
{
  if (allocated(z))
    z.write_on(ostr);

  return (uostream&)ostr;
}
/**
Write values from dvar_matrix to output stream s.
\param s output stream
*/
void dvar_matrix::write_on(const uostream& s) const
{
  if (allocated(*this))
  {
    int n = rowmax();
    for (int i = rowmin(); i <= n; ++i)
    {
      s << (*this)[i];
      if (!s.good())
      {
        cerr << " Error: Unable to write dvar_matrix to uostream in "
             << __FILE__ << ':' << __LINE__ << '\n';
        ad_exit(1);
      }
    }
  }
}
#endif

