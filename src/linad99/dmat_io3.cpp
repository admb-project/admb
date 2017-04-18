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
uistream& operator>>(const uistream& istr, const dmatrix& _z)
{
  ADUNCONST(dmatrix,z)
  z.read_from(istr);

  return (uistream&)istr;
}

/**
 * Description not yet available.
 * \param
 */
void dmatrix::read_from(const uistream& s)
{
  for (int i = rowmin(); i <= rowmax(); ++i)
  {
     s >> (*this)[i];
     if (!s.good())
     {
       cerr << " Error in dmatrix read\n";
       ad_exit(1);
     }
  }
}

/**
 * Description not yet available.
 * \param
 */
uostream& operator<<(const uostream& ostr, const dmatrix& z)
{
  z.write_on(ostr);

  return (uostream&) ostr;
}

/**
 * Description not yet available.
 * \param
 */
void dmatrix::write_on(const uostream& s) const
{
  for (int i=rowmin(); i <= rowmax(); i++)
  {
     s << (*this)[i];
     if (!s.good())
     {
       cerr << " Error in dmatrix write\n";
       ad_exit(1);
     }
  }
}
#endif
