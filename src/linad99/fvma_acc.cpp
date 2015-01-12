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

#ifndef OPT_LIB

/**
 * Description not yet available.
 * \param
 */
    prevariable dvar_matrix::operator () (int i, int j)
    {
      #ifdef SAFE_ARRAYS
      if (i < rowmin())
      {
        ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too low", "prevariable dvar_matrix::operator () (int i, int j)", rowmin(), rowmax(), i);
      }
      if (i > rowmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too high", "prevariable dvar_matrix::operator () (int i, int j)", rowmin(), rowmax(), i);
      }
      if (j < elem(i).indexmin())
      {
        ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- second index too low", "prevariable dvar_matrix::operator () (int i, int j)", elem(i).indexmin(), elem(i).indexmax(), j);
      }
      if (j > elem(i).indexmax())
      {
        ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- second index too high", "prevariable dvar_matrix::operator () (int i, int j)", elem(i).indexmin(), elem(i).indexmax(), j);
      }
      #endif
      return ( m[i].va+j );
    }

/**
 * Description not yet available.
 * \param
 */
 dvar_vector& dvar_matrix::operator[] (int i)
 {
   #ifdef SAFE_ARRAYS
   if (i < rowmin())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too low", "prevariable dvar_matrix::operator () (int i, int j)", rowmin(), rowmax(), i);
   }
   if (i > rowsize() + rowmin() - 1)
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- index too high", "prevariable dvar_matrix::operator () (int i, int j)", rowmin(), rowmax(), i);
   }
   #endif
   return (m[i]);
 }

#ifdef USE_CONST

/**
 * Description not yet available.
 * \param
 */
    _CONST prevariable dvar_matrix::operator () (int i, int j) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<rowmin())
        {
          cerr << "array bound exceeded -- index too low in dvar_matrix::operator(int,int)"
               << " first argument was " << i << endl;
          ad_exit(21);
        }
        if (j<elem(i).indexmin())
        {
          cerr << "array bound exceeded -- index too low in dvar_matrix::operator(int,int)"
               << " first argument was " << i << endl;
          ad_exit(22);
        }
        if (i>rowmax())
        {
          cerr << "array bound exceeded -- index too high in dvar_matrix::operator(int,int)"
               << " second argument was " << j << endl;
          ad_exit(23);
        }
        if (j>elem(i).indexmax())
        {
          cerr << "array bound exceeded -- index too high in dvar_matrix::operator(int,int)"
               << " second argument was " << j << endl;
          ad_exit(24);
        }
      #endif
      return ( m[i].va+j );
    }

/**
 * Description not yet available.
 * \param
 */
  _CONST dvar_vector& dvar_matrix::operator[] (int i) _CONST
 {
   #ifdef SAFE_ARRAYS
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in dvar_matrix::operator[]"
             << "value was" << i;
       ad_exit(21);
     }
     if (i>rowsize()+rowmin()-1)
     {
       cerr << "matrix bound exceeded -- row index too high in dvar_matrix::operator[]"
             << "value was" << i;
       ad_exit(22);
     }
   #endif
   return (m[i]);
 }

#endif

#endif

