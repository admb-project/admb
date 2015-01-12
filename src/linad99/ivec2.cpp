/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <fvar.hpp>

void ivector::initialize(void)
{
  for (int i=indexmin();i<=indexmax();i++)
  {
    elem(i)=0;
  }
}

