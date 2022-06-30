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
#include <fvar.hpp>
  /**
  \ingroup matop
  Element-wise multiplication of two vectors; constant objects.
  Exits with error if bounds of the two arguments differ.
  \param t1 A vector, \f$u\f$ with valid subscripts in \f$[i_1,i_n]\f$
  \param t2 A vector, \f$v\f$ with valid subscripts in \f$[i_1,i_n]\f$
  \return A vector containing \f$z_i = u_i\times v_i; [i_1,i_n]\f$.
  */
dvector elem_prod(const dvector& t1, const dvector& t2)
  {
     int min = t1.indexmin();
     int max = t1.indexmax();
#ifndef OPT_LIB
     if (min != t2.indexmin() || max != t2.indexmax())
     {
       cerr << "Index bounds do not match in dvector "
       "elem_prod(const dvector&, const dvector&)\n";
       ad_exit(1);
     }
#endif

     dvector tmp(min, max);

     double* ptmp = tmp.get_v() + min;
     double* pt1 = t1.get_v() + min;
     double* pt2 = t2.get_v() + min;
     for (int i = min; i <= max; ++i)
     {
       //tmp[i]=t1[i]*t2[i];
       *ptmp = *pt1 * *pt2;
       ++ptmp;
       ++pt1;
       ++pt2;
     }

     return tmp;
  }

  /**
  \ingroup matop
  Element-wise division of two vectors; constant objects.
  Exits with error if bounds of the two arguments differ.
  \param t1 A vector, \f$u\f$ with valid subscripts in \f$[i_1,i_n]\f$
  \param t2 A vector, \f$v\f$ with valid subscripts in \f$[i_1,i_n]\f$
  \return A vector containing \f$z_i = u_i\div v_i; [i_1,i_n]\f$.
  */
dvector elem_div(const dvector& t1, const dvector& t2)
  {
     int min = t1.indexmin();
     int max = t1.indexmax();
#ifndef OPT_LIB
     if (min != t2.indexmin() || max != t2.indexmax())
     {
       cerr << "Index bounds do not match in "
       "dvector elem_div(const dvector&, const dvector&)\n";
       ad_exit(1);
     }
#endif

     dvector tmp(min, max);

     double* ptmp = tmp.get_v() + min;
     double* pt1 = t1.get_v() + min;
     double* pt2 = t2.get_v() + min;
     for (int i = min; i <= max; ++i)
     {
       //tmp[i]=t1[i]/t2[i];
       *ptmp = *pt1 / *pt2;
       ++ptmp;
       ++pt1;
       ++pt2;
     }

     return tmp;
  }
