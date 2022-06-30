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
#include "fvar.hpp"

/**
 * Divide elements of a vector by a constant  
 * \param x constant to divide vector by.
 */
dvector& dvector::operator/=(const double x)
{
  int min = indexmin();
  int max = indexmax();
  double* pvi = v + min;
  for (int i = min; i <= max; ++i)
  {
    *pvi /= x;
    ++pvi;
  }
  return *this;
}

/**
 * Multiply elements of a vector by a constant.
 * \param x constant for multiplication.
 */
dvector& dvector::operator*=(const double x)
{
  int min = indexmin();
  int max = indexmax();
  double* pvi = v + min;
  for (int i = min; i <= max; ++i)
  {
    *pvi *= x;
    ++pvi;
  }
  return *this;
}
