/*
 * $Id: dvect26.cpp 946 2011-01-12 23:52:45Z johnoel $
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
  void dvector::reallocate(double s)
  {
    if (::allocated(*this))
    {
      dvector tmp(indexmin(),indexmax());
      tmp=(*this);
      deallocate();
      allocate(indexmin(),int(s*indexmax()));
      *this=tmp;
    }
    else
    {
      dvector tmp(1,s);
    }
  }
