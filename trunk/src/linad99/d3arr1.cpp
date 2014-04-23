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

#ifndef OPT_LIB
/**
 * Description not yet available.
 * \param
 */
    double& d3_array::operator () (int k, int i, int j)
    {
        if (k<slicemin())
        {
         ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too low",
         "dmatrix& d3_array::operator() (int k, int i, int j)",
         slicemin(), slicemax(), k);
        }
        if (k>slicemax())
        {
        ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too high",
        "dmatrix& d3_array::operator() (int k, int i, int j)",
        slicemin(), slicemax(), k);
        }
      return ( (elem(k))(i,j) );
    }

/**
 * Description not yet available.
 * \param
 */
    dvector& d3_array::operator () (int k, int i)
    {
        if (k<slicemin())
        {
         ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too low",
         "dmatrix& d3_array::operator() (int k, int i)",
         slicemin(), slicemax(), k);
        }
        if (k>slicemax())
        {
         ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too high",
         "dmatrix& d3_array::operator() (int k, int i)",
         slicemin(), slicemax(), k);
        }
      return ( (elem(k))(i) );
    }

/**
 * Description not yet available.
 * \param
 */
 dmatrix& d3_array::operator[] (int i)
 {
     if (i<slicemin())
     {
       ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low",
       "dmatrix& d3_array::operator[] (int i)", indexmin(), indexmax(), i);
     }
     if (i>slicemax())
     {
       ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high",
       "dmatrix& d3_array::operator[] (int i)", indexmin(), indexmax(), i);
     }
   return(t[i]);
 }

/**
 * Description not yet available.
 * \param
 */
 dmatrix& d3_array::operator() (int i)
 {
     if (i<slicemin())
     {
       ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low",
       "dmatrix& d3_array::operator() (int i)", indexmin(), indexmax(), i);
     }
     if (i>slicemax())
     {
       ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high",
       "dmatrix& d3_array::operator() (int i)", indexmin(), indexmax(), i);
     }
   return(t[i]);
 }
#endif
