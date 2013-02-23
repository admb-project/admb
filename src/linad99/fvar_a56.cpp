/*
 * $Id: fvar_a56.cpp 542 2012-07-10 21:04:06Z johnoel $
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
 * Description not yet available.
 * \param
 */
  dvar_vector& dvar_vector::operator *= ( CGNU_DOUBLE x)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)*=x;
    }
    return(*this);
  }

/**
 * Description not yet available.
 * \param
 */
dvar_vector& dvar_vector::operator*=(const prevariable& x)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)*=x;
    }
    return(*this);
  }
