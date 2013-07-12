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

#ifdef __USE_IOSTREAM__

/**
 * Description not yet available.
 * \param
 */
uostream& operator<<(const uostream& _ostr, const d3_array& z)
{
  uostream & ostr = (uostream&) _ostr;
  for (int i=z.slicemin();i<=z.slicemax();i++)
  {
    ostr << z[i];
  }
  return ostr;
}

/**
 * Description not yet available.
 * \param
 */
uistream& operator>>(const uistream& _istr, const d3_array& z)
{
  uistream & istr = (uistream&) _istr;
  for (int i=z.slicemin();i<=z.slicemax();i++)
  {
    istr >> z[i];
  }
  return istr;
}

/**
 * Description not yet available.
 * \param
 */
uostream& operator<<(const uostream& _ostr, const dvar3_array& z)
{
  uostream & ostr = (uostream&) _ostr;
  for (int i=z.slicemin();i<=z.slicemax();i++)
  {
    ostr << z[i];
  }
  return ostr;
}

/**
 * Description not yet available.
 * \param
 */
uistream& operator>>(const uistream& _istr, const dvar3_array& z)
{
  uistream & istr = (uistream&) _istr;
  for (int i=z.slicemin();i<=z.slicemax();i++)
  {
    istr >> z[i];
  }
  return istr;
}

#endif
