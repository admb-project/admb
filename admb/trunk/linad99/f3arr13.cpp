/**
  * $Id$
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

 dvar3_array& dvar3_array::operator= (_CONST d3_array& m1)
 {
   if (slicemin() != m1.slicemin() || slicemax() != m1.slicemax())
   {
     cerr << " Incompatible array bounds in dvar_matrix& operator = (_CONST dvar_vector&)\n";
     ad_exit(21);
   }

   for (int i=slicemin();i<=slicemax();i++)
   {
     elem(i)=m1.elem(i);
   }
   return(*this);
 }

 dvar3_array& dvar3_array::operator= (double x)
 {
   for (int i=slicemin();i<=slicemax();i++)
   {
     elem(i)=x;
   }
   return(*this);
 }


#undef HOME_VERSION

