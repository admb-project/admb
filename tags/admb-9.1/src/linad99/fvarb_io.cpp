/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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
uistream& operator>>(BOR_CONST uistream& istr,BOR_CONST dvar_vector& _z)
{
  ADUNCONST(dvar_vector,z)
  if (allocated(z))
    z.read_from(istr);
  return (uistream&) istr;
}

void dvar_vector::read_from(BOR_CONST uistream& _s)
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

uostream& operator<<(BOR_CONST uostream& ostr,_CONST dvar_vector& z)
{
  if (allocated(z))
    z.write_on(ostr);
  return (uostream&) ostr;
}

void dvar_vector::write_on(BOR_CONST uostream& _s) _CONST
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
