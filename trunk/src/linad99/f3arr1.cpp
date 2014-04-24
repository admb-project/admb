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
    prevariable dvar3_array::operator () (int k, int i, int j)
    {
      if (!allocated(*this))
      {
         cerr << "trying to access an unallocated object" << endl;
         ad_exit(21);
      }
      if (k < slicemin())
      {
         ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too low",
         "prevariable dvar3_array::operator () (int k, int i, int j)",
         slicemin(), slicemax(), k);
      }
      if (k > slicemax())
      {
         ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too high",
         "prevariable dvar3_array::operator () (int k, int i, int j)",
         slicemin(), slicemax(), k);
      }
      return (elem(k))(i,j);
    }

/**
 * Description not yet available.
 * \param
 */
    dvar_vector& dvar3_array::operator () (int k, int i)
    {
      if (k < slicemin())
      {
         ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too low",
         "dvar_vector& dvar3_array::operator () (int k, int i)",
         slicemin(), slicemax(), k);
      }
      if (k > slicemax())
      {
         ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too high",
         "dvar_vector& dvar3_array::operator () (int k, int i)",
         slicemin(), slicemax(), k);
      }
      return (elem(k))(i);
    }

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix& dvar3_array::operator[] (int i)
 {
   if (i < slicemin())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too low",
     "dvar_matrix& dvar3_array::operator [] (int i)",
     slicemin(), slicemax(), i);
   }
   if (i > slicemax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too high",
     "dvar_matrix& dvar3_array::operator [] (int i)",
     slicemin(), slicemax(), i);
   }
   return t[i];
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_matrix& dvar3_array::operator() (int i)
 {
   if (!allocated(*this))
   {
       cerr << "trying to access an unallocated object" << endl;
       ad_exit(21);
   }
   if (i < slicemin())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too low",
     "dvar_matrix& dvar3_array::operator () (int i)",
     slicemin(), slicemax(), i);
   }
   if (i > slicemax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("array bound exceeded -- slice index too high",
     "dvar_matrix& dvar3_array::operator () (int i)",
     slicemin(), slicemax(), i);
   }
   return t[i];
 }
#endif

/**
 * Description not yet available.
 * \param
 */
dvariable sum(const dvar3_array& m)
{
  RETURN_ARRAYS_INCREMENT();
  dvariable tmp=0.;
  for (int i=m.indexmin();i<=m.indexmax();i++)
  {
    tmp+=sum(m.elem(i));
  }
  RETURN_ARRAYS_DECREMENT();
  return tmp;
}
