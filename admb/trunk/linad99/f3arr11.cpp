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

   dvar3_array mfexp(_CONST dvar3_array& m)
   {
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=mfexp(m(i));
     }
     return tmp;
   }  

   dvar3_array mfexp(_CONST dvar3_array& m, CGNU_DOUBLE d)
   {
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=mfexp(m(i),d);
     }
     return tmp;
   }  

#undef HOME_VERSION

