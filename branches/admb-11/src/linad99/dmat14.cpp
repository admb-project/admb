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
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
double trace(const dmatrix& M)
{
  double tmp;
  tmp=0.0;
  if (M.colmin()!=M.rowmin() || M.colmax()!=M.rowmax() )
  {
    cerr << " Matrix not square in trace\n";
    ad_exit(1);
  }
  for (int i=M.colmin();i<=M.colmax();i++)
  {
    tmp+=M.elem(i,i);
  }
  return tmp;
}
