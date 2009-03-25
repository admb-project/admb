/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */



#include "fvar.hpp"

   dvar3_array operator / (_CONST prevariable& d,_CONST dvar3_array& m)
   {
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d/m(i);
     }
     return tmp;
   }  

   dvar3_array operator / (_CONST prevariable& d,_CONST d3_array& m)
   {
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d/m(i);
     }
     return tmp;
   }  

   dvar3_array operator / ( CGNU_DOUBLE d,_CONST dvar3_array& m)
   {
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d/m(i);
     }
     return tmp;
   }  

