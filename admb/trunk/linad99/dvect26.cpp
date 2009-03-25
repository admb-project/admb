/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */




#include "fvar.hpp"

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


