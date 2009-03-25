/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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

ostream& operator<<(BOR_CONST ostream& _s,_CONST d3_array& z)
{
  ostream& s = (ostream&) _s;
#ifdef __USE_IOSTREAM__
  int new_w = s.width();
  int new_p = s.precision();
#if defined(GCC3)
  ios::fmtflags new_form = s.flags();
#else
  long new_form = s.flags();
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

istream& operator>>(BOR_CONST istream& _istr,BOR_CONST d3_array& z)
{
  istream& istr = (istream&) _istr;
  for (int i=z.slicemin();i<=z.slicemax();i++)
  {
    istr >> z[i];
  }
  return istr;
}

