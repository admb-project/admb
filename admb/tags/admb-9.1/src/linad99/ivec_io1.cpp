/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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


#ifdef __USE_IOSTREAM__
uistream& operator>>(BOR_CONST uistream& _istr,BOR_CONST ivector& _z)
{
  ivector& z=(ivector& )_z;
  uistream& istr= (uistream&) _istr;
  z.read_from(istr);
  return istr;
}

void ivector::read_from(BOR_CONST uistream& _s)
{
  ADUNCONST(uistream,s);
  int n = indexmax() - indexmin() + 1;
  char* p = (char*)(v + indexmin());

  s.read(p, n*sizeof(int) );
}

uostream& operator<<(BOR_CONST uostream& _ostr,_CONST ivector& z)
{
  uostream & ostr = (uostream&) _ostr;
  z.write_on(ostr);

  return ostr;
}

void ivector::write_on(BOR_CONST uostream& _s) _CONST
{
  ADUNCONST(uostream,s)
  int n = indexmax() - indexmin() + 1;
  char* p = (char*)(v + indexmin());

  s.write(p, n*sizeof(int) );
}
#endif

