/**
\file
Author: David Fournier
Copyright (c) 2008-2015 Regents of the University of California
*/
#include "fvar.hpp"

/**
Default constructor
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
  shape = NULL;
  t = NULL;
}
