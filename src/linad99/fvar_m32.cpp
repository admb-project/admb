/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
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

/**
 * Description not yet available.
 * \param
 */
dvar_matrix mfexp(const dvar_matrix& m)
{
  dvar_matrix tmp;
  tmp.allocate(m.indexmin(),m.indexmax());
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=mfexp(m(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix mfexp(const dvar_matrix& m, const double d)
{
  dvar_matrix tmp;
  tmp.allocate(m.indexmin(),m.indexmax());
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=mfexp(m(i),d);
  }
  return tmp;
}
