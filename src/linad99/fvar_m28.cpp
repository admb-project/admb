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
dvar_matrix& dvar_matrix::operator/=(const double x)
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();
  int min = index_min;
  int max = index_max;
  dvar_vector* pv = m + min;
  for (int i = min; i <= max; ++i)
  {
    *pv /= x;
    ++pv;
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return (*this);
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix& dvar_matrix::operator/=(const prevariable& x)
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();
  int min = index_min;
  int max = index_max;
  dvar_vector* pv = m + min;
  for (int i = min; i <= max; ++i)
  {
    *pv /= x;
    ++pv;
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return (*this);
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix& dvar_matrix::operator=(const double x)
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();
  int min = index_min;
  int max = index_max;
  dvar_vector* pv = m + min;
  for (int i = min; i <= max; ++i)
  {
    *pv = x;
    ++pv;
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return (*this);
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix& dvar_matrix::operator=(const prevariable& x)
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();
  int min = index_min;
  int max = index_max;
  dvar_vector* pv = m + min;
  for (int i = min; i <= max; ++i)
  {
    *pv = x;
    ++pv;
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return (*this);
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix& dvar_matrix::operator*=(const double x)
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();
  int min = index_min;
  int max = index_max;
  dvar_vector* pv = m + min;
  for (int i = min; i <= max; ++i)
  {
    *pv *= x;
    ++pv;
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return (*this);
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix& dvar_matrix::operator*=(const prevariable& x)
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();
  int min = index_min;
  int max = index_max;
  dvar_vector* pv = m + min;
  for (int i = min; i <= max; ++i)
  {
    *pv *= x;
    ++pv;
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return (*this);
}
