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
// file: dvect_io.cpp
#include "fvar.hpp"

// i/o ooperations for class lvector

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
#ifndef OPT_LIB
  #include <cassert>
#endif

// unformatted

#ifdef __USE_IOSTREAM__

/**
 * Description not yet available.
 * \param
 */
uistream& operator>>(const uistream& _istr, const lvector& _z)
{
  ADUNCONST(lvector,z)
  uistream & istr = (uistream&) _istr;
  z.read_from(istr);

  return istr;
}

/**
 * Description not yet available.
 * \param
 */
void lvector::read_from(const uistream& _s)
{
  ADUNCONST(uistream,s)
  char* p = (char*)(v + indexmin());
#ifndef OPT_LIB
  assert(indexmax() >= indexmin());
#endif
  int n = indexmax() - indexmin() + 1;
  n *= sizeof(int);
  s.read(p, n);
}

/**
 * Description not yet available.
 * \param
 */
uostream& operator<<(const uostream& _ostr, const lvector& z)
{
  uostream & ostr = (uostream&) _ostr;
  z.write_on(ostr);

  return ostr;
}

/**
 * Description not yet available.
 * \param
 */
void lvector::write_on(const uostream& _s) const
{
  ADUNCONST (uostream,s)
  char* p = (char*)(v + indexmin());
#ifndef OPT_LIB
  assert(indexmax() >= indexmin());
#endif
  int n = indexmax() - indexmin() + 1;
  n *= sizeof(int);
  s.write(p, n);
}
#endif

