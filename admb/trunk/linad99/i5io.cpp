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
//#include "i3_array.h"

ostream& operator<<(BOR_CONST ostream& _ostr, _CONST i5_array& z)
{
  ostream& ostr=(ostream&) _ostr;
  for (int i=z.indexmin();i<=z.indexmax();i++)
  {
    if (allocated(z[i]))
    {
      ostr << z[i];
    }
    if (i<z.indexmax())
    {
      ostr << endl;
    }
  }
  return (ostream&) ostr;
}

istream& operator>>(BOR_CONST istream& istr,BOR_CONST i5_array& z)
{
  for (int i=z.indexmin();i<=z.indexmax();i++)
  {
    if (allocated(z[i]))
    {
      istr >> z[i];
    }
  }
  return (istream&) istr;
}

