/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include "fvar.hpp"

dvar5_array::dvar5_array() 
{
  allocate();
}

void dvar5_array::allocate(void)
 {
   shape=NULL;
   t = NULL;
 }

