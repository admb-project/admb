/*
 * $Id$
 * Author: David Fournier
 * Copyright (c) 2008 Regents of the University of California 
 */

#include "fvar.hpp"
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
