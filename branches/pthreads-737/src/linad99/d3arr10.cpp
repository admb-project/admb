/*
 * $Id: d3arr10.cpp 542 2012-07-10 21:04:06Z johnoel $
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
void d3_array::allocate(void)
{
  shape=NULL;
  t = NULL;
}

/**
 * Description not yet available.
 * \param
 */
d3_array::d3_array(void)
{
  allocate();
}
