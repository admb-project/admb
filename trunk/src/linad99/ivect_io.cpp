/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

/**
\file
i/o operations for class ivector
*/

#include <string.h>
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
Insertion operator for ivector z.
*/
ostream& operator<<(const ostream& ostr, const ivector& z)
{
  z.write_on(ostr);
  return (ostream&) ostr;
}
/**
Writes all the elements to the ostream _s.
*/
void ivector::write_on(const ostream& _s) const
{
  ostream& s = (ostream&)_s;
#ifdef __USE_IOSTREAM__
  std::streamsize new_w = s.width();
  std::streamsize new_p = s.precision();
#if defined(GCC3)
  ios::fmtflags new_form = s.flags();
#else
  long new_form = s.flags();
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
    s.width(new_w);
    s.precision(new_p);
    s.flags(new_form);
    s.fill(new_fill);
    /*
    if (!s.good())
    {
      cerr << " Error in ivector write\n";
      ad_exit(1);
    }
    */
#else
    s << " " << (*this)[i];
#endif
  }
}
/**
Extraction operator for ivector _z.
*/
istream& operator>>(const istream& istr, const ivector& _z)
{
  ADUNCONST(ivector,z)
  z.read_from(istr);
  return (istream&)istr;
}
/**
Reads all the elements from istream _s.
*/
void ivector::read_from(const istream& _s)
{
  istream& s=(istream&)_s;
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin; i <= mmax; i++)
  {
    s >> (*this)[i];
  }
}
