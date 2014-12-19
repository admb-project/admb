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
#include "admb_messages.h"
#ifdef __TURBOC__
  #pragma hdrstop
#endif

#ifndef OPT_LIB

/**
 * Description not yet available.
 * \param
 */
 ivector& imatrix::operator[] (int i)
 {
   if (i < rowmin())
   {
     ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low",
     "ivector& imatrix::operator[] (int i)", rowmin(), rowmax(), i);
   }
   if (i > rowsize() + rowmin() - 1)
   {
     ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high",
     "ivector& imatrix::operator[] (int i)", rowmin(), rowmax(), i);
   }
   return m[i];
 }

/**
 * Description not yet available.
 * \param
 */
const ivector& imatrix::operator[](int i) const
 {
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in "
       "imatrix::operator[]" << "value was" << i;
       ad_exit(21);
     }
     if (i>rowsize()+rowmin()-1)
     {
       cerr << "matrix bound exceeded -- row index too high in "
       "imatrix::operator[]" << "value was" << i;
       ad_exit(22);
     }
   return m[i];
 }
#endif
