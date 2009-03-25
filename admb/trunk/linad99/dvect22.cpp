/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>

dvector dvector::operator - (void)
{
  int mmin=indexmin();
  int mmax=indexmax();
  dvector tmp(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=-elem(i);  
  }
  return tmp;
}
