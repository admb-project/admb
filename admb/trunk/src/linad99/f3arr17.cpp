/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

 dvar3_array::dvar3_array(void)
 {
   allocate();
 }

 void dvar3_array::allocate(void)
 {
   shape=NULL;
   t = NULL;
 }


