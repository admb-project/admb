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
dvar7_array operator/(const d7_array& m, const prevariable& d)
   {
     gradient_structure* gs = gradient_structure::_instance;
     gs->RETURN_ARRAYS_INCREMENT();

     dvar7_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     gs->RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar7_array operator/(const dvar7_array& m, const double d)
   {
     gradient_structure* gs = gradient_structure::_instance;
     gs->RETURN_ARRAYS_INCREMENT();
     dvar7_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     gs->RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar7_array operator/(const dvar7_array& m, const prevariable& d)
   {
     gradient_structure* gs = gradient_structure::_instance;
     gs->RETURN_ARRAYS_INCREMENT();
     dvar7_array tmp;
     tmp.allocate(m);
     for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
     {
       tmp(i)=m(i)/d;
     }
     gs->RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
void dvar7_array::operator/=(const prevariable& d)
   {
     gradient_structure* gs = gradient_structure::_instance;
     gs->RETURN_ARRAYS_INCREMENT();
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)(i)/=d;
     }
     gs->RETURN_ARRAYS_DECREMENT();
   }

/**
 * Description not yet available.
 * \param
 */
void dvar7_array::operator/=(const double& d)
   {
     gradient_structure* gs = gradient_structure::_instance;
     gs->RETURN_ARRAYS_INCREMENT();
     for (int i=indexmin();i<=indexmax();i++)
     {
       (*this)(i)/=d;
     }
     gs->RETURN_ARRAYS_DECREMENT();
   }

/**
 * Description not yet available.
 * \param
 */
dvariable sum(const dvar7_array& m)
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();
  dvariable tmp=0.;
  int min = m.indexmin();
  int max = m.indexmax();
  const dvar6_array* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    tmp += sum(*pmi);

    ++pmi;
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}
