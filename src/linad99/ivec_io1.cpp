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

// i/o ooperations for class ivector


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

#ifdef __USE_IOSTREAM__

/**
 * Description not yet available.
 * \param
 */
uistream& operator>>(const uistream& _istr, const ivector& _z)
{
  ivector& z=(ivector& )_z;
  uistream& istr= (uistream&) _istr;
  z.read_from(istr);
  return istr;
}

/**
 * Description not yet available.
 * \param
 */
void ivector::read_from(const uistream& _s)
{
  ADUNCONST(uistream,s);
#ifndef OPT_LIB
  assert(indexmax() >= indexmin());
#endif
  unsigned int n = indexmax() - indexmin() + 1;
  char* p = (char*)(v + indexmin());

  s.read(p, n*sizeof(int) );
}

/**
 * Description not yet available.
 * \param
 */
uostream& operator<<(const uostream& _ostr, const ivector& z)
{
  uostream & ostr = (uostream&) _ostr;
  z.write_on(ostr);

  return ostr;
}

/**
 * Description not yet available.
 * \param
 */
void ivector::write_on(const uostream& _s) const
{
  ADUNCONST(uostream,s)
#ifndef OPT_LIB
  assert(indexmax() >= indexmin());
#endif
  unsigned int n = indexmax() - indexmin() + 1;
  char* p = (char*)(v + indexmin());

  s.write(p, n*sizeof(int) );
}
#endif
