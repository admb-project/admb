/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>

dmatrix dmatrix::operator() (_CONST ivector& t)
{
  dmatrix tmp(t.indexmin(), t.indexmax(), t.indexmin(), t.indexmax());

  for (int i=t.indexmin(); i <= t.indexmax(); i++)
  {
    tmp(i) = (*this)(t(i))(t);
  }
  return(tmp);
}
