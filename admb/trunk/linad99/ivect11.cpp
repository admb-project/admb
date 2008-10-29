


#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD

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


#undef HOME_VERSION
