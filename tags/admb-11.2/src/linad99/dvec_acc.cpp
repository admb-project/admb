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
#include "admb_messages.h"

#if !defined(OPT_LIB)
/**
Returns a reference to the element at index __i__ in the array.

\param __i__ index
*/
double& dvector::operator[](int i)
{
  if (i < index_min || index_max < i)
  {
  #if defined(USE_EXCEPTIONS)
    throw vector_range_exception(i,index_min,index_max);
  #else
    ADMB_ARRAY_BOUNDS_ERROR("invalid index for array",
    "double& dvector::operator[] (int i)", index_min, index_max, i);
  #endif
  }
  return *(v+i);
}
/**
Returns a reference to the element at index __i__ in the array.

\param __i__ index
*/
double& dvector::operator()(int i)
{
  if (i < index_min || index_max < i)
  {
  #if defined(USE_EXCEPTIONS)
    throw vector_range_exception(i,index_min,index_max);
  #else
    ADMB_ARRAY_BOUNDS_ERROR("invalid index for array",
    "double& dvector::operator[] (int i)", index_min, index_max, i);
  #endif
  }
  return *(v+i);
}
/**
Returns a reference to the element at index __i__ in the array.

\param __i__ index
*/
const double& dvector::operator[](int i) const
{
  if (i < index_min || index_max < i)
  {
  #if defined(USE_EXCEPTIONS)
    throw vector_range_exception(i,index_min,index_max);
  #else
    ADMB_ARRAY_BOUNDS_ERROR("invalid index for array",
    "double& dvector::operator[] (int i)", index_min, index_max, i);
  #endif
  }
  return *(v+i);
}
/**
Returns a reference to the element at index __i__ in the array.

\param __i__ index
*/
const double& dvector::operator()(int i) const
{
  if (i < index_min || index_max < i)
  {
  #if defined(USE_EXCEPTIONS)
    throw vector_range_exception(i,index_min,index_max);
  #else
    ADMB_ARRAY_BOUNDS_ERROR("invalid index for array",
    "double& dvector::operator[] (int i)", index_min, index_max, i);
  #endif
  }
  return *(v+i);
}
#endif
