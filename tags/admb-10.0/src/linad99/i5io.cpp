/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
//#include "i3_array.h"

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
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
