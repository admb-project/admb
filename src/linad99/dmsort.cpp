/*
 * $Id$
 * Author: David Fournier
 *
 * Copyright (c) 2009-2011 ADMB Foundation
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
dmatrix sort(_CONST dmatrix& m,int column,int NSTACK)
{
  ivector ind(m.rowmin(),m.rowmax());
  ivector ind1(m.rowmin(),m.rowmax());
  ivector ind2(m.rowmin(),m.rowmax());
  int i;
  for (i=m.rowmin();i<=m.rowmax();i++)
  {
    ind1(i)=m(i).indexmin();
    ind2(i)=m(i).indexmax();
  }
  sort(extract_column(m,column),ind);
  dmatrix tmp(m.rowmin(),m.rowmax(),ind1,ind2);
  for (i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=m(ind(i));
  }
  return tmp;
}
