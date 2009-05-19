/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

   dvar3_array elem_prod(_CONST dvar3_array& m1,_CONST d3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=elem_prod(m1(i),m2(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array elem_div(_CONST dvar3_array& m1,_CONST d3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=elem_div(m1(i),m2(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array operator + (_CONST dvar3_array& m1,_CONST d3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)+m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array operator - (_CONST dvar3_array& m1,_CONST d3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)-m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array operator + (_CONST dvariable& d,_CONST d3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d+m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array operator - (_CONST dvariable& d,_CONST d3_array& m2)
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

   dvar3_array operator * (_CONST dvariable& d,_CONST d3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d*m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array operator * (_CONST dvariable& d,_CONST dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d*m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array operator * (double d,_CONST dvar3_array& m2)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d*m2(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array operator - (_CONST dvar3_array& m1,_CONST dvariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)-d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array operator + (_CONST dvar3_array& m1,_CONST dvariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)+d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array operator + ( double d,_CONST dvar3_array& m1)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d+m1(i);
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array operator * (_CONST dvar3_array& m1,_CONST dvariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)*d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array operator + (_CONST dvariable& d1, _CONST dvar3_array& m1)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m1);

     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)+d1;
     }

     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

