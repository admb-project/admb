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
// file: dvect_io.cpp

// i/o ooperations for class dvector
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

#include <string.h>

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(const ostream& _ostr,const dvector& z)
{
  ostream& ostr=(ostream&) _ostr;
  z.write_on(ostr);

  return ostr;
}

/**
 * Description not yet available.
 * \param
 */
void dvector::write_on(const ostream& _s) const
{
  ostream& s=(ostream&) _s;
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
  for (int i=indexmin(); i <= indexmax(); i++)
  {
  #ifdef __USE_IOSTREAM__
     s.width(0);
     s << " ";
     s.width(new_w);
     s.precision(new_p);
     s.flags(new_form);
     s.fill(new_fill);
     s << (*this)[i];
  #else
     s << " " << (*this)[i];
  #endif
  }
}

/**
 * Description not yet available.
 * \param
 */
istream& operator>>(const istream& _istr, const dvector& _z)
{
  dvector& z = (dvector&)_z;
  istream& istr= (istream&) _istr;
  z.read_from(istr);

  return istr;
}

/**
 * Description not yet available.
 * \param
 */
void dvector::read_from(const istream& _s)
{
  istream& s= (istream&) _s;
  for (int i=indexmin(); i <= indexmax(); i++)
  {
     s >> elem(i);
  }
}


