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

ostream& operator<<(BOR_CONST ostream& _ostr,_CONST dvar3_array& z)
{
  ostream& ostr= (ostream&) _ostr;
  for (int i=z.slicemin();i<=z.slicemax();i++)
  {
    ostr << z[i];
    if (i<z.slicemax())
    {
      ostr << endl;
    }
  }
  return ostr;
}

istream& operator>>(BOR_CONST istream& _istr,BOR_CONST dvar3_array& z)
{
  istream& istr= (istream&) _istr;
  for (int i=z.slicemin();i<=z.slicemax();i++)
  {
    istr >> z[i];
  }
  return istr;
}
