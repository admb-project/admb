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
//#include <d4arr.hpp>

/**
 * Description not yet available.
 * \param
 */
d6_array::d6_array() 
{
  allocate();
}

/**
 * Description not yet available.
 * \param
 */
void d6_array::allocate(void)
{
  shape=NULL;
  t = NULL;
}
