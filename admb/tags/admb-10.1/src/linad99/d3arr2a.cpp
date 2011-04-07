/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
   d3_array log(_CONST d3_array& m)
   {
     d3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=log(m(i));
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   d3_array exp(_CONST d3_array& m)
   {
     d3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=exp(m(i));
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   d3_array sin(_CONST d3_array& m)
   {
     d3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=sin(m(i));
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   d3_array cos(_CONST d3_array& m)
   {
     d3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=cos(m(i));
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   d3_array tan(_CONST d3_array& m)
   {
     d3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=tan(m(i));
     }
     return tmp;
   } 
 
/**
 * Description not yet available.
 * \param
 */
   d3_array elem_prod(_CONST d3_array& m1,_CONST d3_array& m2)
   {
     d3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=elem_prod(m1(i),m2(i));
     }
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
   d3_array elem_div(_CONST d3_array& m1,_CONST d3_array& m2)
   {
     d3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=elem_div(m1(i),m2(i));
     }
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
   d3_array operator + (_CONST d3_array& m1,_CONST d3_array& m2)
   {
     d3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)+m2(i);
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   d3_array operator - (_CONST d3_array& m1,_CONST d3_array& m2)
   {
     d3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)-m2(i);
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
    double norm(_CONST d3_array& m)
    {
      double tmp=0.0;
      for (int k=m.slicemin();k<=m.slicemax();k++)
      {
	tmp+=norm2(m(k));
      }
      tmp=sqrt(tmp);
      return tmp;
    }

/**
 * Description not yet available.
 * \param
 */
    double norm2(_CONST d3_array& m)
    {
      double tmp=0.0;
      for (int k=m.slicemin();k<=m.slicemax();k++)
      {
	tmp+=norm2(m(k));
      }
      return tmp;
    }

/**
 * Description not yet available.
 * \param
 */
   d3_array operator + ( double d,_CONST d3_array& m2)
   {
     d3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d+m2(i);
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   d3_array operator - ( double d,_CONST d3_array& m2)
   {
     d3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d-m2(i);
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   d3_array operator + (_CONST d3_array& m1, double d)
   {
     d3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)+d;
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   d3_array operator - (_CONST d3_array& m1, double d)
   {
     d3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)-d;
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   d3_array operator * (_CONST d3_array& m1, double d)
   {
     d3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)*d;
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   d3_array operator * ( double d,_CONST d3_array& m2)
   {
     d3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d*m2(i);
     }
     return tmp;
   }
