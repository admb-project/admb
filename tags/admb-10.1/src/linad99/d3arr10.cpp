/*
 * $Id: d3arr10.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
