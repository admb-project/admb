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

ostream& operator<<(BOR_CONST ostream& _ostr,_CONST dmatrix& z)
{
  ostream& ostr = (ostream&) _ostr;
  z.write_on(ostr);
  return ostr;
}

void dmatrix::write_on(BOR_CONST ostream& _s) _CONST 
{
 ostream& s=(ostream&) _s;
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

  for (int i=rowmin(); i <= rowmax(); i++)
  {
  #ifdef __USE_IOSTREAM__
     s.width(new_w);
     s.precision(new_p);
     s.flags(new_form);
     s.fill(new_fill);
  #endif
     s << (*this)[i];
     if (i<rowmax())
     {
//#  if ( defined(__BORLANDC__) &&  __BORLANDC__  > 0x0520) 
      
//#  endif
       s << endl;
     }
  }
}

istream& operator>>(BOR_CONST istream& _istr,BOR_CONST dmatrix& _z)
{
  dmatrix& z= (dmatrix&) _z; 
  istream& istr = (istream&) _istr;
  z.read_from(istr);

  return istr;
}

void dmatrix::read_from(BOR_CONST istream& s)
{
  for (int i=rowmin();i <= rowmax();i++)
  {
     s >> (*this)[i];
  }
}

