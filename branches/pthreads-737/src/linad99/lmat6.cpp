/*
 * $Id: lmat6.cpp 542 2012-07-10 21:04:06Z johnoel $
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
void lmatrix::allocate(const lmatrix& dm)
{
  int nrl=dm.rowmin();
  int nrh=dm.rowmax();
  int ncl=dm.colmin();
  int nch=dm.colmax();

  if ( (shape = new mat_shape(nrl,nrh,ncl,nch))== 0)
  {
    cerr << " Error allocating memory in imatrix contructor" << endl;
    ad_exit(21);
  }

  int rs=rowsize();
  if ( (m = new lvector [rs]) == 0)
  {
    cerr << " Error allocating memory in imatrix contructor" << endl;
    ad_exit(21);
  }
  m -= rowmin();
  for (int i=rowmin(); i<=rowmax(); i++)
  {
    m[i].allocate(dm(i));
  }
}

