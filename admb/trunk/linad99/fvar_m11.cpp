
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

 dvar_matrix& dvar_matrix::operator+= (_CONST dvar_matrix& m1)
 {
   if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() )
   {
     cerr << " Incompatible array bounds in dvar_matrix& operator += (_CONST dvar_vector&)\n";
     ad_exit(21);
   }

   for (int i=rowmin();i<=rowmax();i++)
   {
     elem(i) += m1.elem(i);
   }
   return(*this);
 }

 dvar_matrix& dvar_matrix::operator+= (_CONST dmatrix& m1)
 {
   if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() )
   {
     cerr << " Incompatible array bounds in dvar_matrix& operator += (_CONST dvar_vector&)\n";
     ad_exit(21);
   }

   for (int i=rowmin();i<=rowmax();i++)
   {
     elem(i) += m1.elem(i);
   }
   return(*this);
 }


 dvar_matrix& dvar_matrix::operator-= (_CONST dvar_matrix& m1)
 {
   if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() )
   {
     cerr << " Incompatible array bounds in dvar_matrix& operator -= (_CONST dvar_vector&)\n";
     ad_exit(21);
   }

   for (int i=rowmin();i<=rowmax();i++)
   {
     elem(i) -= m1.elem(i);
   }
   return(*this);
 }

 dvar_matrix& dvar_matrix::operator-= (_CONST dmatrix& m1)
 {
   if (rowmin() != m1.rowmin() || rowmax() != m1.rowmax() )
   {
     cerr << " Incompatible array bounds in dvar_matrix& operator -= (_CONST dvar_vector&)\n";
     ad_exit(21);
   }

   for (int i=rowmin();i<=rowmax();i++)
   {
     elem(i) -= m1.elem(i);
   }
   return(*this);
 }


 #undef HOME_VERSION
