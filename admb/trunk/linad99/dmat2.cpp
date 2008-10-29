#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"


 dmatrix trans(_CONST dmatrix& m1)
 {
   dmatrix tmp(m1.colmin(),m1.colmax(),m1.rowmin(),m1.rowmax());

   for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
   {
     for (int j=m1.colmin(); j<=m1.colmax(); j++)
     {
       tmp[j][i]=m1[i][j];
     }
   }
   return (tmp);
 }


    double norm(_CONST dmatrix& m1)
    {
      double tmp;
      double tmp1;
      tmp=0;
      for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
      {
        tmp+=norm2(m1.elem(i));
      }
      return(sqrt(tmp));
    }

    double norm2(_CONST dmatrix& m1)
    {
      double tmp;
      double tmp1;
      tmp=0;
      for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
      {
        tmp+=norm2(m1.elem(i));
      }
      return(tmp);
    }
#undef HOME_VERSION
