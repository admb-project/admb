/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"
//#include <d4arr.hpp>


 d5_array::d5_array() 
 {
   allocate();
 }

void d5_array::allocate(void)
 {
   shape=NULL;
   t = NULL;
 }


