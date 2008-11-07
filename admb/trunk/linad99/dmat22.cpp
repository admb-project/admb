/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */



#define HOME_VERSION
// file fvar.cpp
// constructors, destructors and misc functions involving class dvariable 

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

dmatrix& dmatrix::operator = ( CGNU_DOUBLE x)
{
  for (int i=rowmin();i<=rowmax();i++)
  {
    elem(i)=x;
  }
  return (*this);
}

dmatrix& dmatrix::operator /= ( CGNU_DOUBLE x)
{
  for (int i=rowmin();i<=rowmax();i++)
  {
    elem(i)/=x;
  }
  return (*this);
}

dmatrix& dmatrix::operator *= ( CGNU_DOUBLE x)
{
  for (int i=rowmin();i<=rowmax();i++)
  {
    elem(i)*=x;
  }
  return (*this);
}

#undef HOME_VERSION
