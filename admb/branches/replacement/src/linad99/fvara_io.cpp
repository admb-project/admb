/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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


ostream& operator<<(BOR_CONST ostream& ostr,_CONST dvar_vector& z)
{
  if (allocated(z))  
    z.write_on(ostr);

  return (ostream&) ostr;
}

void dvar_vector::write_on(BOR_CONST ostream& _s) _CONST
{
  ostream& s =(ostream&) _s;
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

istream& operator>>(BOR_CONST istream& istr,BOR_CONST dvar_vector& _z)
{
  ADUNCONST(dvar_vector,z)
  if (allocated(z))
    z.read_from(istr);
  return (istream&)istr;
}

void dvar_vector::read_from(BOR_CONST istream& s)
{
  if (allocated(*this))
    for (int i=indexmin(); i <= indexmax(); i++)
    {
       s >> elem(i); 
    }
}

