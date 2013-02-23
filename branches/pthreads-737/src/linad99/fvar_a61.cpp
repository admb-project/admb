/*
 * $Id: fvar_a61.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <admodel.h>

/**
 * Description not yet available.
 * \param
 */
 dvar_vector::dvar_vector(const param_init_number_vector& _t)
 {
   param_init_number_vector& t=(param_init_number_vector&) (_t);
   int i;
   va=NULL;
   allocate(t.indexmin(),t.indexmax());
   initialize();
   for ( i=indexmin(); i<=indexmax(); i++)
   {
     (*this)(i)=t(i);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_vector::dvar_vector(const param_init_bounded_number_vector& _t)
 {
   param_init_bounded_number_vector& t=(param_init_bounded_number_vector&) (_t);
   int i;
   va=NULL;
   allocate(t.indexmin(),t.indexmax());
   initialize();
   for ( i=indexmin(); i<=indexmax(); i++)
   {
     (*this)(i)=t(i);
   }
 }
