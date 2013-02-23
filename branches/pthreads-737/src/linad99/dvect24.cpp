/*
 * $Id: dvect24.cpp 542 2012-07-10 21:04:06Z johnoel $
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
ivector sgn(const dvector& v)
  {
    int mmin=v.indexmin();
    int mmax=v.indexmax();
    ivector tmp(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      if(v(i)>0.0) 
        tmp(i)=1;
      else
        tmp(i)=-1;
    }
    return tmp;
  }
