/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"

   dvar3_array operator - ( CGNU_DOUBLE d,_CONST dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d-m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvariable mean(_CONST dvar3_array& m)
   {
     dvariable tmp;
     tmp=sum(m)/double(size_count(m));
     return tmp;
   }
