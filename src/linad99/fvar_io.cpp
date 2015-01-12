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
// file: fvar_io.cpp

// i/o operations for class prevariable

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

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(BOR_CONST ostream& _ostr,_CONST prevariable& f)
{
  ostream& ostr=(ostream&) _ostr;
  ostr << value(f);
  return ostr;
}

/**
 * Description not yet available.
 * \param
 */
istream& operator>>(BOR_CONST istream& _istr,BOR_CONST prevariable& _f)
{
  prevariable& f = (prevariable&)_f;
  istream& istr=(istream&) _istr;
  double tmp;
  istr >> tmp;
  f=tmp;
  return istr;
}


#ifdef __USE_IOSTREAM__
/**
 * Description not yet available.
 * \param
 */
uostream& operator<<(BOR_CONST uostream& _ostr,_CONST prevariable& f)
{
  uostream& ostr=(uostream&) _ostr;
  ostr << value(f);
  return ostr;
}

/**
 * Description not yet available.
 * \param
 */
uistream& operator>>(BOR_CONST uistream& _istr,BOR_CONST prevariable& _f)
{
  prevariable& f = (prevariable&)_f;
  uistream& istr=(uistream&) _istr;
  double tmp;
  istr >> tmp;
  f=tmp;
  return istr;
}
#endif
