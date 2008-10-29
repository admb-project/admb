#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
// file fvar.cpp
// constructors, destructors and misc functions involving class prevariable 

#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif


#include <stdio.h>
#ifndef __SUN__
#endif
#include <math.h>
dvar_matrix& dvar_matrix::operator /= ( CGNU_DOUBLE x)
{
  RETURN_ARRAYS_INCREMENT();
  for (int i=rowmin();i<=rowmax();i++)
  {
    elem(i)/=x;
  }
  RETURN_ARRAYS_DECREMENT();
  return (*this);
}

dvar_matrix& dvar_matrix::operator /= ( _CONST prevariable& x)
{
  RETURN_ARRAYS_INCREMENT();
  for (int i=rowmin();i<=rowmax();i++)
  {
    elem(i)/=x;
  }
  RETURN_ARRAYS_DECREMENT();
  return (*this);
}

dvar_matrix& dvar_matrix::operator = ( CGNU_DOUBLE x)
{
  RETURN_ARRAYS_INCREMENT();
  for (int i=rowmin();i<=rowmax();i++)
  {
    elem(i)=x;
  }
  RETURN_ARRAYS_DECREMENT();
  return (*this);
}

dvar_matrix& dvar_matrix::operator = (_CONST prevariable& x)
{
  RETURN_ARRAYS_INCREMENT();
  for (int i=rowmin();i<=rowmax();i++)
  {
    elem(i)=x;
  }
  RETURN_ARRAYS_DECREMENT();
  return (*this);
}

dvar_matrix& dvar_matrix::operator *= ( CGNU_DOUBLE x)
{
  RETURN_ARRAYS_INCREMENT();
  for (int i=rowmin();i<=rowmax();i++)
  {
    elem(i)*=x;
  }
  RETURN_ARRAYS_DECREMENT();
  return (*this);
}

dvar_matrix& dvar_matrix::operator *= ( _CONST prevariable& x)
{
  RETURN_ARRAYS_INCREMENT();
  for (int i=rowmin();i<=rowmax();i++)
  {
    elem(i)*=x;
  }
  RETURN_ARRAYS_DECREMENT();
  return (*this);
}

#undef HOME_VERSION
