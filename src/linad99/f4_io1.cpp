/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

// file: dmat_io.cpp

// i/o operations for class dmatrix

#include "fvar.hpp"
#include  "d4arr.hpp"

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

#ifdef __USE_IOSTREAM__


uostream& operator<<(BOR_CONST uostream& ostr,BOR_CONST dvar4_array & z)
{
  for (int i=z.hslicemin();i<=z.hslicemax();i++)
  {
    ostr << z[i];
  }
  return (uostream&) ostr;
}

uistream& operator>>(BOR_CONST uistream& istr,BOR_CONST  dvar4_array & z)
{
  for (int i=z.hslicemin();i<=z.hslicemax();i++)
  {
    istr >> z[i];
  }
  return (uistream&) istr;
}

#endif

