/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008 Regents of the University of California 
 */

#include "fvar.hpp"

dvar_vector diagonal(const dvar_matrix& m)
{
  if (m.indexmin() != m.colmin() || m.indexmax() != m.colmax())
  {
    cerr << "Error matrix not square in function diagonal" << endl;
    exit(21);
  }
  int mmin=m.indexmin();
  int mmax=m.indexmax();
  dvar_vector tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
    tmp(i)=m(i,i);
  return tmp;
} 


