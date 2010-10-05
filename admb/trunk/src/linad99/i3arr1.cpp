/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California 
 */
#include "fvar.hpp"
#include "admb_messages.h"
//#include "i3_array.h"

#ifndef OPT_LIB
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
