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

/**
 * Description not yet available.
 * \param
 */
dmatrix outer_prod(const dvector& v1, const dvector& v2)
{
  dmatrix tmp(v1.indexmin(),v1.indexmax(), v2.indexmin(), v2.indexmax() );

  for (int i=v1.indexmin(); i<=v1.indexmax(); i++)
  {
    for (int j=v2.indexmin(); j<=v2.indexmax(); j++)
    {
      tmp.elem(i,j)=v1.elem(i)*v2.elem(j);
    }
  }
  return(tmp);
}
