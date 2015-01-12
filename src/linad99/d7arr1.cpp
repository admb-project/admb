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
   d7_array operator / (_CONST d7_array& m, CGNU_DOUBLE d)
   {
     d7_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   void d7_array::operator /= ( CGNU_DOUBLE d)
   {
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)(i)/=d;
     }
   }  

/**
 * Description not yet available.
 * \param
 */
  double sum(_CONST d7_array& m)
  {
    RETURN_ARRAYS_INCREMENT();
    double tmp=0.;
    for (int i=m.indexmin();i<=m.indexmax();i++)
    {
      tmp+=sum(m.elem(i));
    }
    RETURN_ARRAYS_DECREMENT();
    return tmp;
  }
