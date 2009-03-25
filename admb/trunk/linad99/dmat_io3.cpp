/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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
uistream& operator>>(BOR_CONST uistream& istr,BOR_CONST dmatrix& _z)
{
  ADUNCONST(dmatrix,z)
  z.read_from(istr);

  return (uistream&)istr;
}

void dmatrix::read_from(BOR_CONST uistream& s)
{
  int n = rowmin() + rowsize() - 1;

  for (int i=rowmin(); i <= n; i++)
  {
     s >> (*this)[i];
     if (!s.good()) 
     {
       cerr << " Error in dmatrix read\n";
       ad_exit(1);
     }
  }
}

uostream& operator<<(BOR_CONST uostream& ostr,_CONST dmatrix& z)
{
  z.write_on(ostr);

  return (uostream&) ostr;
}

void dmatrix::write_on(BOR_CONST uostream& s) _CONST
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

