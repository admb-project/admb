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
dvar6_array operator/(const d6_array& m, const prevariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar6_array tmp;
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
dvar6_array operator/(const dvar6_array& m, const double d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar6_array tmp;
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
dvar6_array operator/(const dvar6_array& m, const prevariable& d)
   {
     RETURN_ARRAYS_INCREMENT();
     dvar6_array tmp;
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
void dvar6_array::operator/=(const prevariable& d)
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
void dvar6_array::operator/=(const double& d)
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
dvariable sum(const dvar6_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvariable tmp=0.;
  for (int i=m.indexmin();i<=m.indexmax();i++)
  {
    tmp+=sum(m.elem(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}
