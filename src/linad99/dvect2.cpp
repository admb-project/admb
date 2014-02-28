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
     if (t1.indexmin() != t2.indexmin() ||  t1.indexmax() != t2.indexmax())
     {
       cerr << "Index bounds do not match in dvector "
       "elem_prod(const dvector&, const dvector&)\n";
       ad_exit(1);
     }
     dvector tmp(t1.indexmin(),t1.indexmax());

#ifndef USE_ASSEMBLER
     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp[i]=t1[i]*t2[i];
     }
#else
     int min=t1.indexmin();
     int n=t1.indexmax()-min+1;
     dp_vector_elem_prod(&(tmp(min)),&(t1(min)),&(t2(min)),n);
#endif

     return(tmp);
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
     if (t1.indexmin() != t2.indexmin() ||  t1.indexmax() != t2.indexmax())
     {
       cerr << "Index bounds do not match in "
       "dvector elem_div(const dvector&, const dvector&)\n";
       ad_exit(1);
     }
     dvector tmp(t1.indexmin(),t1.indexmax());

#ifndef USE_ASSEMBLER
     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp[i]=t1[i]/t2[i];
     }
#else
     int min=t1.indexmin();
     int n=t1.indexmax()-min+1;
     dp_vector_elem_prod(&(tmp(min)),&(t1(min)),&(t2(min)),n);
#endif

     return(tmp);
  }
