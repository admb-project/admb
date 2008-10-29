

#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD

#include "fvar.hpp"
  int Max(_CONST ivector& t1)
  {
    return max(t1);
  }

  int max(_CONST ivector& t1)
  {
     int tmp;
     int mmin=t1.indexmin();
     int mmax=t1.indexmax();
     tmp=t1.elem(mmin);
     for (int i=mmin+1; i<=mmax; i++)
     {
       if (tmp<t1.elem(i)) tmp=t1.elem(i);
     }
     return(tmp);
  }

  int min(_CONST ivector& t1)
  {
     int tmp;
     int mmin=t1.indexmin();
     int mmax=t1.indexmax();
     tmp=t1.elem(mmin);
     for (int i=mmin+1; i<=mmax; i++)
     {
       if (tmp>t1.elem(i)) tmp=t1.elem(i);
     }
     return(tmp);
  }


#undef HOME_VERSION
