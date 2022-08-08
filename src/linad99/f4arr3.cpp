/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

/// Default Constructor
dvar4_array::dvar4_array()
{
  allocate();
}

/// Initializes to NULL
void dvar4_array::allocate(void)
{
  shape=NULL;
  t = NULL;
}
