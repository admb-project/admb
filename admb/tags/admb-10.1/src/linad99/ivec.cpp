/*
 * $Id$
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
ivector& ivector::shift(int min)
{
  v += indexmin()-min;
  index_max=index_max+min-index_min;
  index_min=min;
  shape->shift(min);
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
void lvector::shift(int min)
{
  v += indexmin()-min;
  shape->shift(min);
}
