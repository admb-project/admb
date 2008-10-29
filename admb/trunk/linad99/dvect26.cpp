


#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD

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
