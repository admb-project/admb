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
#include <admodel.h>
#include "admb_messages.h"


#if !defined(OPT_LIB)

/**
 * Description not yet available.
 * \param
 */
   param_init_vector& param_init_vector_vector::operator [] (int i) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "param_init_vector& param_init_vector_vector::operator [] (int i)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "param_init_vector& param_init_vector_vector::operator [] (int i)", indexmin(), indexmax(), i);
     }
     return v[i];
   }

/**
 * Description not yet available.
 * \param
 */
   param_init_vector& param_init_vector_vector::operator () (int i) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "param_init_vector& param_init_vector_vector::operator () (int i)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "param_init_vector& param_init_vector_vector::operator () (int i)", indexmin(), indexmax(), i);
     }
     return v[i];
   }

/**
 * Description not yet available.
 * \param
 */
   prevariable param_init_vector_vector::operator () (int i,int j) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "prevariable param_init_vector_vector::operator () (int i, int j)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "prevariable param_init_vector_vector::operator () (int i, int j)", indexmin(), indexmax(), i);
     }
#if defined(__BORLANDC__)
#  if (__BORLANDC__  >= 0x0540) 
     return (prevariable&) (v[i][j]);
#  else
     return v[i][j];
#  endif
#else
#  if ( defined(linux) && __GNUC__ < 4)
     return (prevariable&) (v[i][j]);
#  else
     return v[i][j];
#  endif
#endif
   }

/**
 * Description not yet available.
 * \param
 */
   param_init_matrix& param_init_matrix_vector::operator [] (int i) 
   {
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "param_init_matrix& prevariable param_init_vector_vector::operator [] (int i)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "param_init_matrix& prevariable param_init_vector_vector::operator [] (int i)", indexmin(), indexmax(), i);
     }
     return v[i];
   }

/**
 * Description not yet available.
 * \param
 */
   param_init_matrix& param_init_matrix_vector::operator () (int i) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "param_init_matrix& param_init_matrix_vector::operator () (int i)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "param_init_matrix& param_init_matrix_vector::operator () (int i)", indexmin(), indexmax(), i);
     }
     return v[i];
   }

/**
 * Description not yet available.
 * \param
 */
   dvar_vector& param_init_matrix_vector::operator () (int i,int j) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "dvar_vector& param_init_matrix_vector::operator () (int i, int j)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "dvar_vector& param_init_matrix_vector::operator () (int i, int j)", indexmin(), indexmax(), i);
     }
     return v[i][j];
   }

/**
 * Description not yet available.
 * \param
 */
   prevariable param_init_matrix_vector::operator () (int i,int j,int k) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "prevariable param_init_matrix_vector::operator () (int i, int j, int k)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "prevariable param_init_matrix_vector::operator () (int i, int j, int k)", indexmin(), indexmax(), i);
     }
#if defined(__BORLANDC__)
#  if (__BORLANDC__  >= 0x0540) 
     return (prevariable&) (v[i](j,k));
#  else
     return v[i](j,k);
#  endif
#else
#  if ( defined(linux) && __GNUC__ < 4)
     return (prevariable&) v[i](j,k);
#  else
     return v[i](j,k);
#  endif
#endif
   }

/**
 * Description not yet available.
 * \param
 */
   param_init_bounded_vector& param_init_bounded_vector_vector::operator [] (int i) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "param_init_bounded_vector& param_init_bounded_vector_vector::operator [] (int i)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "param_init_bounded_vector& param_init_bounded_vector_vector::operator [] (int i)", indexmin(), indexmax(), i);
     }
     return v[i];
   }

/**
 * Description not yet available.
 * \param
 */
   param_init_bounded_vector& param_init_bounded_vector_vector::operator () (int i) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "param_init_bounded_vector& param_init_bounded_vector_vector::operator () (int i)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "param_init_bounded_vector& param_init_bounded_vector_vector::operator () (int i)", indexmin(), indexmax(), i);
     }
     return v[i];
   }

/**
 * Description not yet available.
 * \param
 */
   prevariable param_init_bounded_vector_vector::operator () (int i,int j) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "prevariable param_init_bounded_vector_vector::operator () (int i, int j)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "prevariable param_init_bounded_vector_vector::operator () (int i, int j)", indexmin(), indexmax(), i);
     }
#if defined(__BORLANDC__)
#  if (__BORLANDC__  >= 0x0540) 
     return (prevariable&) (v[i][j]);
#  else
     return v[i][j];
#  endif
#else
#  if ( defined(linux) && __GNUC__ < 4)
     return (prevariable&) (v[i][j]);
#  else
     return v[i][j];
#  endif
#endif
   }

/**
 * Description not yet available.
 * \param
 */
   param_init_bounded_matrix& param_init_bounded_matrix_vector::operator [] (int i) 
   {
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "param_init_bounded_matrix& param_init_bounded_matrix_vector::operator [] (int i)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "param_init_bounded_matrix& param_init_bounded_matrix_vector::operator [] (int i)", indexmin(), indexmax(), i);
     }
     return v[i];
   }

/**
 * Description not yet available.
 * \param
 */
   param_init_bounded_matrix& param_init_bounded_matrix_vector::operator () (int i) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "param_init_bounded_matrix& param_init_bounded_matrix_vector::operator () (int i)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "param_init_bounded_matrix& param_init_bounded_matrix_vector::operator () (int i)", indexmin(), indexmax(), i);
     }
     return v[i];
   }

/**
 * Description not yet available.
 * \param
 */
   dvar_vector& param_init_bounded_matrix_vector::operator () (int i,int j) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "dvar_vector& param_init_bounded_matrix_vector::operator () (int i, int j)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "dvar_vector& param_init_bounded_matrix_vector::operator () (int i, int j)", indexmin(), indexmax(), i);
     }
     return v[i][j];
   }

/**
 * Description not yet available.
 * \param
 */
   prevariable param_init_bounded_matrix_vector::operator () (int i,int j,int k) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "prevariable param_init_bounded_matrix_vector::operator () (int i, int j, int k)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "prevariable param_init_bounded_matrix_vector::operator () (int i, int j, int k)", indexmin(), indexmax(), i);
     }
#if defined(__BORLANDC__)
#  if (__BORLANDC__  >= 0x0540) 
     return (prevariable&) (v[i](j,k));
#  else
     return v[i](j,k);
#  endif
#else
#  if ( defined(linux) && __GNUC__ < 4)
     return (prevariable&) v[i](j,k);
#  else
     return v[i](j,k);
#  endif
#endif
   }

/**
 * Description not yet available.
 * \param
 */
   param_init_number& param_init_number_vector::operator [] (int i) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "param_init_number& param_init_number_vector::operator [] (int i)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "param_init_number& param_init_number_vector::operator [] (int i)", indexmin(), indexmax(), i);
     }
     return v[i];
   }

/**
 * Description not yet available.
 * \param
 */
   param_init_number& param_init_number_vector::operator () (int i) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "param_init_number& param_init_number_vector::operator () (int i)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "param_init_number& param_init_number_vector::operator () (int i)", indexmin(), indexmax(), i);
     }
     return v[i];
   }

/**
 * Description not yet available.
 * \param
 */
   param_init_bounded_number& param_init_bounded_number_vector::operator [] (int i) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "param_init_bounded_number& param_init_bounded_number_vector::operator [] (int i)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "param_init_bounded_number& param_init_bounded_number_vector::operator [] (int i)", indexmin(), indexmax(), i);
     }
     return v[i];
   }

/**
 * Description not yet available.
 * \param
 */
   param_init_bounded_number& param_init_bounded_number_vector::operator () (int i) 
   { 
     if (i<indexmin()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too low", "param_init_bounded_number& param_init_bounded_number_vector::operator () (int i)", indexmin(), indexmax(), i);
     }
     if (i>indexmax()) {
       ADMB_ARRAY_BOUNDS_ERROR("Index too high", "param_init_bounded_number& param_init_bounded_number_vector::operator () (int i)", indexmin(), indexmax(), i);
     }
     return v[i];
   }
#endif
