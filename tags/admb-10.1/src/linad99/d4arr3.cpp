/*
 * $Id: d4arr3.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"
#include <d4arr.hpp>

/**
 * Description not yet available.
 * \param
 */
d4_array::d4_array() 
{
  allocate();
}

/**
 * Description not yet available.
 * \param
 */
void d4_array::allocate(void)
{
  shape=NULL;
  t = NULL;
}
