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
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
  dvector& dvector::operator /= ( CGNU_DOUBLE x)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)/=x;
    }
    return(*this);
  }

/**
 * Description not yet available.
 * \param
 */
  dvector& dvector::operator *= ( CGNU_DOUBLE x)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)*=x;
    }
    return(*this);
  }
