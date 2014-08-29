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
// file: dmat_io.cpp

// i/o operations for class dmatrix
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
ostream& operator<<(const ostream& _s, const d3_array& z)
{
  ostream& s = (ostream&) _s;
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

  for (int i=z.slicemin();i<=z.slicemax();i++)
  {
  #ifdef __USE_IOSTREAM__
     s.width(new_w);
     s.precision(new_p);
     s.flags(new_form);
     s.fill(new_fill);
  #endif
    s << z[i];
    if (i<z.slicemax())
    {
      s << endl;
    }
  }
  return s;
}

/**
 * Description not yet available.
 * \param
 */
istream& operator>>(const istream& _istr, const d3_array& z)
{
  istream& istr = (istream&) _istr;
  for (int i=z.slicemin();i<=z.slicemax();i++)
  {
    istr >> z[i];
  }
  return istr;
}
