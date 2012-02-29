/*
 * $Id: ivsort.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Copyright (c) 2009-2011 ADMB Foundation
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
ivector sort(_CONST ivector & v, int NSTACK)
{
   int lb=v.indexmin();
   int ub=v.indexmax();
   int size=v.size();

   ivector intarray(0,size-1);
   int i;
   for(i=0;i<size;i++)
   {
      intarray[i] = v(lb+i);
   }

   int_qsort(&(intarray(0)),size);

   ivector arr(lb, ub);
   for(i=0;i<size;i++) {
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
ivector sort(_CONST ivector & _v, BOR_CONST ivector & _index, int NSTACK)
{
   ivector & index = (ivector &) _index;
   ivector & v = (ivector &) _v;

   if (v.size() != index.size())
   {
      cerr << " Incompatible array sizes in vector v and ivector index\n"
	 << " in ivector sort(_CONST ivector& v,_CONST ivector& index)\n";
      ad_exit(1);
   }

   int lb=v.indexmin();
   int ub=v.indexmax();
   int size=v.size();

   ivector intarray(0,size-1);
   int i;
   for(i=0;i<size;i++)
   {
      intarray[i] = v(lb+i);
   }

   ivector intarray2(0,size-1);
   for(i=0;i<size;i++)
   {
      intarray2[i] = lb+i;
   }

   int_qsort2(&(intarray[0]),&(intarray2[0]),size);

   ivector arr(lb, ub);
   for(i=0;i<size;i++) {
      arr(lb+i) = intarray[i];
   }

   for(i=0;i<size;i++) {
      index(index.indexmin()+i) = intarray2[i];
   }

   return arr;
}
