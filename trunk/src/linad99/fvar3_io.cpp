/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * i/o operations for class dmatrix.
 */
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
ostream& operator<<(const ostream& _ostr, const dvar3_array& z)
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

/**
 * Description not yet available.
 * \param
 */
istream& operator>>(const istream& _istr,const dvar3_array& z)
{
  istream& istr= (istream&) _istr;
  for (int i=z.slicemin();i<=z.slicemax();i++)
  {
    istr >> z[i];
  }
  return istr;
}
