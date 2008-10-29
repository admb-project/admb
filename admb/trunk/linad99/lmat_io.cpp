
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
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

ostream& operator<<(BOR_CONST ostream& ostr,_CONST lmatrix& z)
{
  int min=z.rowmin();
  int max=z.rowmax();
  int i;
  for (i=min;i<=max-1;i++)
  {
     ostr << z[i] << endl;
  }
  ostr << z[i];
  return (ostream&)ostr;
}

istream& operator>>(BOR_CONST istream& istr,BOR_CONST lmatrix& z)
{
  int min=z.rowmin();
  int max=z.rowmax();
  for (int i=min;i<=max;i++)
  {
     istr >> z[i];
  }
  return (istream&)istr;
}

#undef HOME_VERSION
