#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

void dvar_matrix::rowshift(int min )
{
  m = m + rowmin() - min;
  index_max+=min-index_min;
  index_min=min;
}


 void dvar_matrix::colshift( int min)
 {
   for (int i=rowmin(); i<=rowmax(); i++)
   {
     this->elem(i).shift(min);
   }
   //shape->colshift(min);
 }

#undef HOME_VERSION
