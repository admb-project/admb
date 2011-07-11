/*
 * $Id: dmat0.cpp 946 2011-01-12 23:52:45Z johnoel $
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
void dmatrix::allocate(void)  //default constructor
{
  index_min=1;
  index_max=0;
  m=NULL;
  shape=NULL;
} 

/**
 * Description not yet available.
 * \param
 */
dmatrix::dmatrix()  //default constructor 
{
  allocate();
} 
