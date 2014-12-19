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
  for (int i=indexmin(); i<=indexmax(); i++)
  {
    elem(i)/=x;
  }
  return(*this);
}

/**
 * Multiply elements of a vector by a constant.
 * \param x constant for multiplication.
 */
dvector& dvector::operator*=(const double x)
{
  for (int i=indexmin(); i<=indexmax(); i++)
  {
    elem(i)*=x;
  }
  return(*this);
}
