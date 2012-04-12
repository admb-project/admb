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
void dmatrix::allocate(_CONST dvar_matrix& dm)
{
  int nrl=dm.rowmin();
  int nrh=dm.rowmax();

  index_min=nrl;
  index_max=nrh;
  if ( (m = new dvector [rowsize()]) == 0)
  {
    cerr << " Error allocating memory in dmatrix contructor\n";
    ad_exit(21);
  }
  if ( (shape = new mat_shapex(m))== 0)
  {
    cerr << " Error allocating memory in dmatrix contructor\n";
    ad_exit(21);
  }

  m -= rowmin();
  for (int i=rowmin(); i<=rowmax(); i++)
  {
    m[i].allocate(dm(i));
  }
}
