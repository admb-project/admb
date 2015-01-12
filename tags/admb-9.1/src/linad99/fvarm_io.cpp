/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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


ostream& operator<<(BOR_CONST ostream& _ostr,_CONST dvar_matrix& z)
{
  ostream& ostr= (ostream&) _ostr; 
  z.write_on(ostr);

  return ostr;
}


void dvar_matrix::write_on(BOR_CONST ostream& _s) _CONST
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
    if(i<rowmax())
    {
      s << endl;
    }
  }
}

istream& operator>>(BOR_CONST istream& _istr,BOR_CONST dvar_matrix& _z)
{
  dvar_matrix& z = (dvar_matrix&)_z;
  istream& istr= (istream&) _istr; 
  z.read_from(istr);

  return istr;
}

void dvar_matrix::read_from(BOR_CONST istream& s)
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

