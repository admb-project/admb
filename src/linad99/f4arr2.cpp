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
dvar4_array operator/(const d4_array& m, const prevariable& d)
   {
     gradient_structure* gs = gradient_structure::get();
     gs->RETURN_ARRAYS_INCREMENT();

     int min = m.indexmin();
     int max = m.indexmax();
     dvar4_array tmp;
     tmp.allocate(m);

     dvar3_array* ptmpi = &tmp(min);
     const d3_array* pmi = &m(min);
     for (int i = min; i <= max; ++i)
     {
       *ptmpi = *pmi / d;

       ++pmi;
       ++ptmpi;
     }
     gs->RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar4_array operator/(const dvar4_array& m, const double d)
   {
     gradient_structure* gs = gradient_structure::get();
     gs->RETURN_ARRAYS_INCREMENT();

     int min = m.indexmin();
     int max = m.indexmax();
     dvar4_array tmp;
     tmp.allocate(m);

     double invd = 1.0 / d;

     dvar3_array* ptmpi = &tmp(min);
     const dvar3_array* pmi = &m(min);
     for (int i = min; i <= max; ++i)
     {
       *ptmpi = *pmi * invd;

       ++pmi;
       ++ptmpi;
     }
     gs->RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
dvar4_array operator/(const dvar4_array& m, const prevariable& d)
   {
     gradient_structure* gs = gradient_structure::get();
     gs->RETURN_ARRAYS_INCREMENT();
     int min = m.indexmin();
     int max = m.indexmax();
     dvar4_array tmp;
     tmp.allocate(m);
     dvar3_array* ptmpi = &tmp(min);
     const dvar3_array* pmi = &m(min);
     for (int i = min; i <= max; ++i)
     {
       *ptmpi = *pmi / d;

       ++pmi;
       ++ptmpi;
     }
     gs->RETURN_ARRAYS_DECREMENT();
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
void dvar4_array::operator/=(const prevariable& d)
   {
     gradient_structure* gs = gradient_structure::get();
     gs->RETURN_ARRAYS_INCREMENT();
     int min = indexmin();
     int max = indexmax();
     dvar3_array* pti = t + min;
     for (int i = min; i <= max; ++i)
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
void dvar4_array::operator/=(const double& d)
   {
     gradient_structure* gs = gradient_structure::get();
     gs->RETURN_ARRAYS_INCREMENT();
     int min = indexmin();
     int max = indexmax();
     dvar3_array* pti = t + min;
     for (int i = min; i <= max; ++i)
     {
       *pti /= d;

       ++pti;
     }
     gs->RETURN_ARRAYS_DECREMENT();
   }
