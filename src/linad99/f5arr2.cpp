/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
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
dvar5_array operator/(const d5_array& m, const prevariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar5_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
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
dvar5_array operator/(const dvar5_array& m, const double d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar5_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
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
dvar5_array operator/(const dvar5_array& m, const prevariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar5_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
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
void dvar5_array::operator/=(const prevariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)(i)/=d;
     }
     RETURN_ARRAYS_DECREMENT();
   }

/**
 * Description not yet available.
 * \param
 */
void dvar5_array::operator/=(const double& d)
   {
     RETURN_ARRAYS_INCREMENT();
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)(i)/=d;
     }
     RETURN_ARRAYS_DECREMENT();
   }
