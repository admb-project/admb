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
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
dmatrix dmatrix::operator()(const ivector& t)
{
  dmatrix tmp(t.indexmin(), t.indexmax(), t.indexmin(), t.indexmax());

  for (int i=t.indexmin(); i <= t.indexmax(); i++)
  {
    tmp(i) = (*this)(t(i))(t);
  }
  return(tmp);
}
