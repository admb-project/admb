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
     gradient_structure* gs = gradient_structure::_instance;
     gs->RETURN_ARRAYS_INCREMENT();

     dvar6_array tmp;
     tmp.allocate(m);
     int min = tmp.indexmin();
     int max = tmp.indexmax();
     dvar5_array* ptmpi = &tmp(min);
     const d5_array* pmi = &m(min);
     for (int i=min;i<=max;++i)
     {
       *ptmpi = *pmi / d;
       ++ptmpi;
       ++pmi;
     }
     gs->RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar6_array operator/(const dvar6_array& m, const double d)
   {
     gradient_structure* gs = gradient_structure::_instance;
     gs->RETURN_ARRAYS_INCREMENT();
     dvar6_array tmp;
     tmp.allocate(m);
     int min = tmp.indexmin();
     int max = tmp.indexmax();
     dvar5_array* ptmpi = &tmp(min);
     const dvar5_array* pmi = &m(min);
     for (int i=min;i<=max;++i)
     {
       *ptmpi = *pmi / d;
       ++ptmpi;
       ++pmi;
     }
     gs->RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar6_array operator/(const dvar6_array& m, const prevariable& d)
   {
     gradient_structure* gs = gradient_structure::_instance;
     gs->RETURN_ARRAYS_INCREMENT();
     dvar6_array tmp;
     tmp.allocate(m);
     int min = tmp.indexmin();
     int max = tmp.indexmax();
     dvar5_array* ptmpi = &tmp(min);
     const dvar5_array* pmi = &m(min);
     for (int i=min;i<=max;++i)
     {
       *ptmpi = *pmi / d;
       ++ptmpi;
       ++pmi;
     }
     gs->RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
void dvar6_array::operator/=(const prevariable& d)
   {
     gradient_structure* gs = gradient_structure::_instance;
     gs->RETURN_ARRAYS_INCREMENT();
     int min = indexmin();
     int max = indexmax();
     dvar5_array* pti = t + min;
     for (int i=min;i<=max;++i)
     {
       *pti /= d;
       ++pti;
     }
     gs->RETURN_ARRAYS_DECREMENT();
   }

/**
 * Description not yet available.
 * \param
 */
void dvar6_array::operator/=(const double& d)
   {
     gradient_structure* gs = gradient_structure::_instance;
     gs->RETURN_ARRAYS_INCREMENT();
     int min = indexmin();
     int max = indexmax();
     dvar5_array* pti = t + min;
     for (int i=min;i<=max;++i)
     {
       *pti /= d;
       ++pti;
     }
     gs->RETURN_ARRAYS_DECREMENT();
   }

/**
 * Description not yet available.
 * \param
 */
dvariable sum(const dvar6_array& m)
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();
  dvariable tmp=0.;
  int min = m.indexmin();
  int max = m.indexmax();
  const dvar5_array* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    tmp+=sum(*pmi);

    ++pmi;
  }
  gs->RETURN_ARRAYS_DECREMENT();
  return tmp;
}
