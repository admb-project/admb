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

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(BOR_CONST ostream& ostr,_CONST ivector& z)
{
  z.write_on(ostr);
  return (ostream&) ostr;
}

/**
 * Description not yet available.
 * \param
 */
void ivector::write_on(BOR_CONST ostream& _s) _CONST
{
  ostream& s = (ostream&) _s;
#ifdef __USE_IOSTREAM__
  int new_w = s.width();
  int new_p = s.precision();
#if defined(GCC3)
  ios::fmtflags new_form = s.flags();
#else
  long new_form = s.flags();
#endif
  char new_fill = s.fill();
#endif
  for (int i=indexmin(); i <= indexmax(); i++)
  {
  #ifdef __USE_IOSTREAM__
     s.width(0);
     s << " ";
     s.width(new_w);
     s.precision(new_p);
     s.flags(new_form);
     s.fill(new_fill);
     s << (*this)[i];
     s.width(new_w);
     s.precision(new_p);
     s.flags(new_form);
     s.fill(new_fill);
     /*
     if (!s.good()) 
     {
       cerr << " Error in ivector write\n";
       ad_exit(1);
     }
     */
  #else
     s << " " << (*this)[i];
  #endif
  }
}

/**
 * Description not yet available.
 * \param
 */
istream& operator>>(BOR_CONST istream& istr,BOR_CONST ivector& _z)
{
  ADUNCONST(ivector,z)
  z.read_from(istr);

  return (istream&)istr;
}

/**
 * Description not yet available.
 * \param
 */
void ivector::read_from(BOR_CONST istream& _s)
{
  istream& s=(istream&) _s;
  int mmin=indexmin();
  int mmax=indexmax();

  for (int i=mmin; i <= mmax; i++)
  {
     s >> (*this)[i];
  }
}
