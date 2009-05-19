/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
// file: dvect_io.cpp

// i/o ooperations for class dvector
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
uistream& operator>>(BOR_CONST uistream& istr,BOR_CONST dvector& _z)
{
  ADUNCONST(dvector,z)
  z.read_from(istr);
  return (uistream&)istr;
}

uostream& operator<<(BOR_CONST uostream& ostr,const dvector& z)
{
  z.write_on(ostr);

  return (uostream&)ostr;
}

void dvector::write_on(BOR_CONST uostream& _s) _CONST
{
  ADUNCONST(uostream,s)
  int mmin = indexmin();
  int mmax = indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    s.write((char*)&((*this)[i]), sizeof(double) );
  }
}
void dvector::read_from(BOR_CONST uistream& _s) 
{
  ADUNCONST(uistream,s) 
  int mmin = indexmin();
  int mmax = indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    s.read((char*)&((*this)[i]), sizeof(double) );
  }
}
#endif


