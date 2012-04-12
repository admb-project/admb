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
   dvar3_array operator / (_CONST d3_array& m,_CONST prevariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m(i)/d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   dvar3_array operator / (_CONST dvar3_array& m, CGNU_DOUBLE d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m(i)/d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   dvar3_array operator / (_CONST dvar3_array& m,_CONST prevariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m(i)/d;
     }
     RETURN_ARRAYS_DECREMENT();
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   void dvar3_array::operator /=(_CONST prevariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     for (int i=slicemin();i<=slicemax();i++)
     {
       (*this)(i)/=d;
     }
     RETURN_ARRAYS_DECREMENT();
   }  

/**
 * Description not yet available.
 * \param
 */
   void dvar3_array::operator /=(CGNU_DOUBLE d)
   {
     RETURN_ARRAYS_INCREMENT();
     for (int i=slicemin();i<=slicemax();i++)
     {
       (*this)(i)/=d;
     }
     RETURN_ARRAYS_DECREMENT();
   }  
