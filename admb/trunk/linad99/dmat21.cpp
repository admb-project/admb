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


double dmatrix::fill_seqadd( CGNU_DOUBLE x, CGNU_DOUBLE d)
{
  double x1=x;
  double d1=d;
  for (int i=rowmin();i<=rowmax();i++)
  {
    elem(i).fill_seqadd(x1,d1);
    x1+=elem(i).size()*d1;
  }
  return x1;
}
#undef HOME_VERSION
