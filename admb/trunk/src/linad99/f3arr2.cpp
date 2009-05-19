/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

    dvariable norm(_CONST dvar3_array& m)
    {
      RETURN_ARRAYS_INCREMENT();
      dvariable tmp=0.0;
      for (int k=m.slicemin();k<=m.slicemax();k++)
      {
	tmp+=norm2(m(k));
      }
      tmp=sqrt(tmp);
      RETURN_ARRAYS_DECREMENT();
      return tmp;
    }

    dvariable norm2(_CONST dvar3_array& m)
    {
      RETURN_ARRAYS_INCREMENT();
      dvariable tmp=0.0;
      for (int k=m.slicemin();k<=m.slicemax();k++)
      {
	tmp+=norm2(m(k));
      }
      RETURN_ARRAYS_DECREMENT();
      return tmp;
    }

   dvar3_array exp(_CONST dvar3_array& m)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=exp(m(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

   dvar3_array log(_CONST dvar3_array& m)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=log(m(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

   dvar3_array sin(_CONST dvar3_array& m)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=sin(m(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  


   dvar3_array cos(_CONST dvar3_array& m)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=cos(m(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array sqrt(_CONST dvar3_array& m)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=sqrt(m(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array sqr(_CONST dvar3_array& m)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=sqr(m(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

   dvar3_array tan(_CONST dvar3_array& m)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=tan(m(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   } 
 
   dvar3_array elem_prod(_CONST dvar3_array& m1,_CONST dvar3_array& m2)
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

   dvar3_array elem_div(_CONST dvar3_array& m1,_CONST dvar3_array& m2)
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

   dvar3_array operator + (_CONST dvar3_array& m1,_CONST dvar3_array& m2)
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

   dvar3_array operator - (_CONST dvar3_array& m1,_CONST dvar3_array& m2)
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

   dvar3_array elem_prod(_CONST d3_array& m1,_CONST dvar3_array& m2)
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

   dvar3_array elem_div(_CONST d3_array& m1,_CONST dvar3_array& m2)
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

   dvar3_array operator + (_CONST d3_array& m1,_CONST dvar3_array& m2)
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

   dvar3_array operator - (_CONST d3_array& m1,_CONST dvar3_array& m2)
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
