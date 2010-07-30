/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <admodel.h>
#include "admb_messages.h"


#if !defined(OPT_LIB)
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
