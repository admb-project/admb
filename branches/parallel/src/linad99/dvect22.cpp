/*
 * $Id: dvect22.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
