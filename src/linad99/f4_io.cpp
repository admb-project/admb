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

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(const ostream& _ostr, const dvar4_array &z)
{
  ostream& ostr= (ostream&) _ostr;
  for (int i=z.hslicemin();i<=z.hslicemax();i++)
  {
    ostr << z[i];
    if (i<z.hslicemax()) ostr << endl;
  }
  return (ostream&) ostr;
}

/**
 * Description not yet available.
 * \param
 */
istream& operator>>(const istream& istr, const dvar4_array &z)
{
  for (int i=z.hslicemin();i<=z.hslicemax();i++)
  {
    istr >> z[i];
  }
  return (istream&) istr;
}

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(const ostream& ostr, const dvar5_array &z)
{
  for (int i=z.indexmin();i<=z.indexmax();i++)
  {
    ostr << z[i];
  }
  return (ostream&) ostr;
}

/**
 * Description not yet available.
 * \param
 */
istream& operator>>(const istream& istr, const dvar5_array &z)
{
  for (int i=z.indexmin();i<=z.indexmax();i++)
  {
    istr >> z[i];
  }
  return (istream&) istr;
}

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(const ostream& ostr, const dvar6_array &z)
{
  for (int i=z.indexmin();i<=z.indexmax();i++)
  {
    ostr << z[i];
  }
  return (ostream&) ostr;
}

/**
 * Description not yet available.
 * \param
 */
istream& operator>>(const istream& istr, const dvar6_array &z)
{
  for (int i=z.indexmin();i<=z.indexmax();i++)
  {
    istr >> z[i];
  }
  return (istream&) istr;
}
