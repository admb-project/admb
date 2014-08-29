/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
// file: fvarm_io.cpp

//////// i/o operations for class dvar_matrix

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

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(const ostream& _ostr, const dvar_matrix& z)
{
  ostream& ostr= (ostream&) _ostr;
  z.write_on(ostr);

  return ostr;
}

/**
 * Description not yet available.
 * \param
 */
void dvar_matrix::write_on(const ostream& _s) const
{
  ostream& s = (ostream&)_s;
#ifdef __USE_IOSTREAM__
  using std::streamsize;
  streamsize new_w = s.width();
  streamsize new_p = s.precision();
#if !defined(__cplusplus)
  long new_form = s.flags();
#else
  ios::fmtflags new_form = s.flags();
#endif
  char new_fill = s.fill();
#endif

  for (int i=rowmin(); i <= rowmax(); i++)
  {
  #ifdef __USE_IOSTREAM__
    s.width(new_w);
    s.precision(new_p);
    s.flags(new_form);
    s.fill(new_fill);
  #endif
    s << (*this)[i];
    if(i<rowmax())
    {
      s << endl;
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
istream& operator>>(const istream& _istr, const dvar_matrix& _z)
{
  dvar_matrix& z = (dvar_matrix&)_z;
  istream& istr= (istream&) _istr;
  z.read_from(istr);

  return istr;
}

/**
 * Description not yet available.
 * \param
 */
void dvar_matrix::read_from(const istream& s)
{
  int n = rowmin() + rowsize() - 1;

  for (int i=rowmin(); i <= n; i++)
  {
    s >> (*this)[i];
    /*
    if (!s.good())
    {
      cerr << " Error in dvar_matrix read\n";
      ad_exit(1);
    }
    */
  }
}
