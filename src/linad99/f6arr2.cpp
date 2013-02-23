/*
 * $Id: f6arr2.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
dvar6_array::dvar6_array() 
{
  allocate();
}

/**
 * Description not yet available.
 * \param
 */
void dvar6_array::allocate(void)
{
  shape=NULL;
  t = NULL;
}
