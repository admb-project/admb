/*
 * $Id: ivect11.cpp 542 2012-07-10 21:04:06Z johnoel $
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
  void ivector::reallocate(double s)
  {
    int oldmin=indexmin();
    int oldmax=indexmax();
    if (::allocated(*this))
    {
      ivector tmp(indexmin(),indexmax());
      tmp=(*this);
      deallocate();
      allocate(indexmin(),int(s*indexmax()));
      (*this)(oldmin,oldmax)=tmp;
    }
    else
    {
      ivector tmp(1,s);
    }
  }
