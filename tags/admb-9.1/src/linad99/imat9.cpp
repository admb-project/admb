/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <fvar.hpp>

int max(const imatrix & M)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  int n1=max(M(mmin));
  for (int i=mmin+1;i<=mmax;i++)
  {
    int n=max(M(i));
    if (n1<n) n1=n;
  }
  return n1;
}
    


