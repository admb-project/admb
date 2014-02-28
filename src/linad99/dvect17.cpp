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
Extract the diagonal elements from a matrix and return the corresponding vector

\param m a dmatrix
\return a dvector correpsonding to the diagonal elements.
*/
dvector extract_diagonal(const dmatrix& m)
{
  if ( (m.rowmin()!=m.colmin()) || (m.rowmax()!=m.colmax()))
  {
    cerr << "Error in extract_diagonal function "
    "-- input matrix not square" <<endl;
    ad_exit(1);
  }

  dvector tmp(m.rowmin(),m.rowmax());
  for (int i=m.rowmin(); i<=m.rowmax(); i++)
  {
    tmp.elem(i)=m.elem(i,i);
  }

  return(tmp);
}
