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
 * Sets all elements to zero.
 */
  void dvector::initialize(void)
  {
    if (!(!(*this)))  // only initialize allocated objects
    {
      for (int i=indexmin();i<=indexmax();i++)
      {
        elem(i)=0.0;
      }
    }
  }
