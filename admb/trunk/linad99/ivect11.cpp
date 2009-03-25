/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */




#include "fvar.hpp"

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


