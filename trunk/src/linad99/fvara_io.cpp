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
// file: fvara_io.cpp
// i/o operations for class fvar_arry

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
ostream& operator<<(const ostream& ostr, const dvar_vector& z)
{
  if (allocated(z))
    z.write_on(ostr);

  return (ostream&) ostr;
}

/**
 * Description not yet available.
 * \param
 */
void dvar_vector::write_on(const ostream& _s) const
{
  ostream& s =(ostream&) _s;
#ifdef __USE_IOSTREAM__
  std::streamsize new_w = s.width();
  std::streamsize new_p = s.precision();
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
istream& operator>>(const istream& istr, const dvar_vector& _z)
{
  ADUNCONST(dvar_vector,z)
  if (allocated(z))
    z.read_from(istr);
  return (istream&)istr;
}

/**
 * Description not yet available.
 * \param
 */
void dvar_vector::read_from(const istream& s)
{
  if (allocated(*this))
    for (int i=indexmin(); i <= indexmax(); i++)
    {
       s >> elem(i);
    }
}
