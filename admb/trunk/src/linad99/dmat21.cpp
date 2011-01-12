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

/**
 * Description not yet available.
 * \param
 */
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
