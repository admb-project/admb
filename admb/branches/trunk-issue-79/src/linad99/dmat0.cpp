/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"

void dmatrix::allocate(void)  //default constructor
{
  index_min=1;
  index_max=0;
  m=NULL;
  shape=NULL;
} 

dmatrix::dmatrix()  //default constructor 
{
  allocate();
} 
