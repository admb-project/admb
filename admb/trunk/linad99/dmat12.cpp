/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>

dmatrix symmetrize(_CONST dmatrix& m)
{
  if (m.rowmin() != m.colmin() || m.rowmax() != m.colmax() )
  {
    cerr << " Non square matrix passed to dmatrix symmetrize\n";
    ad_exit(1);
  }
  int rmin=m.rowmin();
  int rmax=m.rowmax();

  dmatrix s(rmin,rmax,rmin,rmax);
  for (int i=rmin;i<=rmax;i++)
  {
    s(i,i)=m(i,i);
  
    for (int j=rmin;j<i;j++)
    {
      s(i,j)=(m(i,j)+m(j,i))/2.;
      s(j,i)=s(i,j);
    }
  }
  return s;
}




