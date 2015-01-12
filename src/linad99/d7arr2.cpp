/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"
//#include <d5arr.hpp>

 d7_array::d7_array() 
 {
   allocate();
 }

void d7_array::allocate(void)
 {
   shape=NULL;
   t = NULL;
 }


