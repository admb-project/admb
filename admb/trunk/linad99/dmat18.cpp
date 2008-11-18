/**
  * $Id$
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#define HOME_VERSION
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
#undef HOME_VERSION
