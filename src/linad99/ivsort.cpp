/*
 * $Id$
 *
 * Copyright (c) 2009-2012 ADMB Foundation
 */
/**
 * \file
 * Has routines for sorting an ivector
 */

#include <fvar.hpp>
#include "qsort.h"

/**
 * A subroutine used in Quicksort
 */
void int_qsort(int *arr, unsigned n)
{
  #define int_lt(a,b) ((*a)<(*b))
  QSORT(int, arr, n, int_lt);
}

/**
 * A subroutine used in Quicksort
 */
void int_qsort2(int *arr, int *arr2, unsigned n)
{
  #define int_lt(a,b) ((*a)<(*b))
  QSORT2(int, int, arr, arr2, n, int_lt);
}

/**
 * Quicksort.
 * \param v Vector of integers to be sorted
 * \param NSTACK Not used.
 * \return ivector object containing the input vector sorted in ascending order.
 *
 * \n\n Adopted from the GNU C Library. http://www.corpit.ru/mjt/qsort.html
 */
ivector sort(const ivector &v, int NSTACK)
{
   int lb=v.indexmin();
   int size=v.size();

   ivector intarray(0,size-1);
   for(int i=0;i<size;i++)
   {
      intarray[i] = v(lb+i);
   }

   if (size > 1)
   {
     int_qsort(&(intarray(0)), (unsigned int)size);
   }

   int ub=v.indexmax();
   ivector arr(lb, ub);
   for(int i=0;i<size;i++) {
      arr(lb+i) = intarray[i];
   }

   return arr;
}

/**
 * Quicksort.
 * \param _v Vector of integers to be sorted
 * \param _index ivector on return containing the input order of the original vector.
 * \param NSTACK Not used.
 * \return ivector object containing the input vector sorted in ascending order.
 *
 * \n\n Adopted from the GNU C Library. http://www.corpit.ru/mjt/qsort.html
 */
ivector sort(const ivector &_v, const ivector &_index, int NSTACK)
{
   ivector & index = (ivector &) _index;
   ivector & v = (ivector &) _v;

   if (v.size() != index.size())
   {
      cerr << " Incompatible array sizes in vector v and ivector index\n"
           << " in ivector sort(const ivector& v, const ivector& index)\n";
      ad_exit(1);
   }

   int lb=v.indexmin();
   int size=v.size();

   ivector intarray(0,size-1);
   for(int i=0;i<size;i++)
   {
      intarray[i] = v(lb+i);
   }

   ivector intarray2(0,size-1);
   for(int i=0;i<size;i++)
   {
      intarray2[i] = lb+i;
   }

   if (size > 1)
   {
     int_qsort2(&(intarray[0]),&(intarray2[0]), (unsigned int)size);
   }

   int ub=v.indexmax();
   ivector arr(lb, ub);
   for(int i=0;i<size;i++) {
      arr(lb+i) = intarray[i];
   }

   for(int i=0;i<size;i++) {
      index(index.indexmin()+i) = intarray2[i];
   }

   return arr;
}
