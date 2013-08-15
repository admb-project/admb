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
 /*
  void vector_shapex::operator delete(void * ptr,size_t n)
  {
    xpool->free(ptr);
  }
 */

/**
 * Description not yet available.
 * \param
 */
void vector_shape::shift(int min)
{
  index_max=index_max-index_min+min;
  index_min=min;
}

/**
 * Description not yet available.
 * \param
 */
void vector_shapex::shift(int min)
{
  index_max=index_max-index_min+min;
  index_min=min;
}
