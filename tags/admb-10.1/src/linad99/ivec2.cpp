/*
 * $Id: ivec2.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
void ivector::initialize(void)
{
  for (int i=indexmin();i<=indexmax();i++)
  {
    elem(i)=0;
  }
}
