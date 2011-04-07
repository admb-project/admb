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
#include "d4arr.hpp"

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
ostream& operator<<(BOR_CONST ostream& _ostr,BOR_CONST  dvar4_array & z)
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
istream& operator>>(BOR_CONST istream& istr,BOR_CONST  dvar4_array & z)
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
ostream& operator<<(BOR_CONST ostream& ostr,BOR_CONST  dvar5_array & z)
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
istream& operator>>(BOR_CONST istream& istr,BOR_CONST  dvar5_array & z)
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
ostream& operator<<(BOR_CONST ostream& ostr,BOR_CONST  dvar6_array & z)
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
istream& operator>>(BOR_CONST istream& istr,BOR_CONST  dvar6_array & z)
{
  for (int i=z.indexmin();i<=z.indexmax();i++)
  {
    istr >> z[i];
  }
  return (istream&) istr;
}
