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
//#include "i3_array.h"

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(const ostream& _ostr, const i3_array& z)
{
  ostream& ostr=(ostream&) _ostr;
  for (int i=z.slicemin();i<=z.slicemax();i++)
  {
    if (allocated(z[i]))
    {
      ostr << z[i];
    }
    if (i<z.slicemax())
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
istream& operator>>(const istream& istr,const i3_array& z)
{
  for (int i=z.slicemin();i<=z.slicemax();i++)
  {
    if (allocated(z[i]))
    {
      istr >> z[i];
    }
  }
  return (istream&) istr;
}
