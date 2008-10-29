
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

  dvar3_array& dvar3_array::operator= (_CONST dvar3_array& m1)  
 {
   if (slicemin() != m1.slicemin() || slicemax() != m1.slicemax())
   {
     cerr << " Incompatible array bounds in dvar_matrix& operator = (_CONST dvar_vector&)\n";
     ad_exit(21);
   }

   if (t != m1.t)            // check for condition that both matrices
   {                         // don't point to the same object
     for (int i=slicemin();i<=slicemax();i++)
     {
       elem(i)=m1.elem(i);
     }
   }
   return(*this);
 }

#undef HOME_VERSION

