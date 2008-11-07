/**
  * $Id:   $
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

double d3_array::fill_seqadd(double i1,double i2)
{
  int mmin=indexmin();
  int mmax=indexmax();
  double inp = i1;
  for (int i=mmin;i<=mmax;i++)
  {
    double tmp=(*this)(i).fill_seqadd(inp,i2);
    inp=tmp;
  }
  return inp;
}
#undef HOME_VERSION
