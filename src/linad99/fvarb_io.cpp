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
// file: fvara_io.cpp

// i/o operations for class fvar_arry

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


#ifdef __USE_IOSTREAM__

/**
 * Description not yet available.
 * \param
 */
uistream& operator>>(const uistream& istr, const dvar_vector& _z)
{
  ADUNCONST(dvar_vector,z)
  if (allocated(z))
    z.read_from(istr);
  return (uistream&) istr;
}

/**
 * Description not yet available.
 * \param
 */
void dvar_vector::read_from(const uistream& _s)
{
  if (allocated(*this))
  {
    uistream& s = (uistream&) _s;
    int n = indexmax() - indexmin() + 1;
    double_and_int * p = va + indexmin();

    for (int i=1; i <= n; i++)
    {
       s >> (p++)->x;
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
uostream& operator<<(const uostream& ostr, const dvar_vector& z)
{
  if (allocated(z))
    z.write_on(ostr);
  return (uostream&) ostr;
}

/**
 * Description not yet available.
 * \param
 */
void dvar_vector::write_on(const uostream& _s) const
{
  if (allocated(*this))
  {
    uostream& s = (uostream&) _s;
    int n = indexmax() - indexmin() + 1;
    double_and_int * p = va + indexmin();

    for (int i=1; i <= n; i++)
    {
       s << (p++)->x;
    }
  }
}
#endif
