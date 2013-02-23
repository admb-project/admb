/*
 * $Id: d7arr2.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"
//#include <d5arr.hpp>

/**
 * Description not yet available.
 * \param
 */
 d7_array::d7_array() 
 {
   allocate();
 }

/**
 * Description not yet available.
 * \param
 */
void d7_array::allocate(void)
 {
   shape=NULL;
   t = NULL;
 }
