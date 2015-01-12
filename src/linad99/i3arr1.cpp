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
#include "admb_messages.h"
//#include "i3_array.h"

#ifndef OPT_LIB

/**
 * Description not yet available.
 * \param
 */
    int& i3_array::operator () (int k, int i, int j)
    {
      #ifdef SAFE_ARRAYS
      if (k < slicemin())
      {
        ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low", "ivector& i3_array::operator() (int k, int i, int j)", slicemin(), slicemax(), k);
      }
      if (k > slicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low", "ivector& i3_array::operator() (int k, int i, int j)", slicemin(), slicemax(), k);
      }
      #endif
      return ( (elem(k))(i,j) );
    }

/**
 * Description not yet available.
 * \param
 */
    ivector& i3_array::operator () (int k, int i)
    {
      #ifdef SAFE_ARRAYS
      if (k < slicemin())
      {
        ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low", "ivector& i3_array::operator() (int k, int i)", slicemin(), slicemax(), k);
      }
      if (k > slicemax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high", "ivector& i3_array::operator() (int k, int i)", slicemin(), slicemax(), k);
      }
      #endif
      return ( (elem(k))(i) );
    }

/**
 * Description not yet available.
 * \param
 */
 imatrix& i3_array::operator[] (int i)
 {
   #ifdef SAFE_ARRAYS
   if (i < slicemin())
   {
     ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low", "imatrix& i3_array::operator[] (int i)", slicemin(), slicemax(), i);
   }
   if (i > slicemax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high", "imatrix& i3_array::operator[] (int i)", slicemin(), slicemax(), i);
   }
   #endif
   return(t[i]);
 }

/**
 * Description not yet available.
 * \param
 */
 imatrix& i3_array::operator() (int i)
 {
   #ifdef SAFE_ARRAYS
   if (i < slicemin())
   {
     ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low", "imatrix& i3_array::operator() (int i)", slicemin(), slicemax(), i);
   }
   if (i > slicemax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high", "imatrix& i3_array::operator() (int i)", slicemin(), slicemax(), i);
   }
   #endif
   return(t[i]);
 }
#endif
