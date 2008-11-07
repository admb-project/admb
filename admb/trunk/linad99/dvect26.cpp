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


#undef HOME_VERSION
