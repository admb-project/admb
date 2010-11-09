/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California 
 */
#include "fvar.hpp"
#include "admb_messages.h"

#ifndef OPT_LIB
    double& d3_array::operator () (int k, int i, int j)
    {
      #ifdef SAFE_ARRAYS
        if (k<slicemin())
        {
          ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too low", "dmatrix& d3_array::operator() (int k, int i, int j)", slicemin(), slicemax(), k);
        }
        if (k>slicemax())
        {
          ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too high", "dmatrix& d3_array::operator() (int k, int i, int j)", slicemin(), slicemax(), k);
        }
      #endif
      return ( (elem(k))(i,j) );
    }


    dvector& d3_array::operator () (int k, int i)
    {
      #ifdef SAFE_ARRAYS
        if (k<slicemin())
        {
          ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too low", "dmatrix& d3_array::operator() (int k, int i)", slicemin(), slicemax(), k);
        }
        if (k>slicemax())
        {
          ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too high", "dmatrix& d3_array::operator() (int k, int i)", slicemin(), slicemax(), k);
        }
      #endif
      return ( (elem(k))(i) );
    }




 dmatrix& d3_array::operator[] (int i)
 {
   #ifdef SAFE_ARRAYS
     if (i<slicemin())
     {
       ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low", "dmatrix& d3_array::operator[] (int i)", indexmin(), indexmax(), i);
     }
     if (i>slicemax())
     {
       ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high", "dmatrix& d3_array::operator[] (int i)", indexmin(), indexmax(), i);
     }
   #endif
   return(t[i]);
 }

 dmatrix& d3_array::operator() (int i)
 {
   #ifdef SAFE_ARRAYS
     if (i<slicemin())
     {
       ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low", "dmatrix& d3_array::operator() (int i)", indexmin(), indexmax(), i);
     }
     if (i>slicemax())
     {
       ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high", "dmatrix& d3_array::operator() (int i)", indexmin(), indexmax(), i);
     }
   #endif
   return(t[i]);
 }
#endif

void ee51qo(void){ /*int i=1;*/}
