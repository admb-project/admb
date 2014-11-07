/*
 * $Id$
 *
 * Copyright (c) 2009-2012 ADMB Foundation
 */
/**
 * \file
 * Has routines for sorting a dvector
 */

#include <fvar.hpp>
#include "qsort.h"

/**
 * A subroutine used in Quicksort
 */
void double_qsort(double *arr, unsigned n)
{
  #define double_lt(a,b) ((*a)<(*b))
  QSORT(double, arr, n, double_lt);
}

/**
 * A subroutine used in Quicksort
 */
void double_qsort2(double *arr, int *arr2, unsigned n)
{
  #define double_lt(a,b) ((*a)<(*b))
  QSORT2(double, int, arr, arr2, n, double_lt);
}

/**
 * Quicksort.
 * \param v A dvector to be sorted.
 * \param NSTACK Not used.
 * \return dvector object containing the input vector sorted in ascending order.
 *
 * \n\n Adopted from the GNU C Library. http://www.corpit.ru/mjt/qsort.html
 */
dvector sort(const dvector & v, int NSTACK)
{
   int lb=v.indexmin();
   int size=v.size();

   double *doublearray = new double[size];
   for(int i=0;i<size;i++)
   {
      doublearray[i] = v(lb+i);
   }

   if (size > 0)
   {
     double_qsort(doublearray, (unsigned int)size);
   }

   int ub=v.indexmax();
   dvector arr(lb, ub);
   for(int i=0;i<size;i++) {
      arr(lb+i) = doublearray[i];
   }

   delete [] doublearray;
   doublearray = 0;

   return arr;
}

/**
 * Quicksort.
 * \param _v A dvector to be sorted.
 * \param _index ivector on return containing the input order of the original vector.
 * \param NSTACK Not used.
 * \return ivector object containing the input vector sorted in ascending order.
 *
 * \n\n Adopted from the GNU C Library. http://www.corpit.ru/mjt/qsort.html
 */
dvector sort(const dvector &_v, const ivector &_index, int NSTACK)
{
   ivector & index = (ivector &) _index;
   dvector & v = (dvector &) _v;

   if (v.size() != index.size())
   {
      cerr << " Incompatible array sizes in vector v and ivector index\n"
           << " in ivector sort(const ivector& v,const ivector& index)\n";
      ad_exit(1);
   }

   int lb=v.indexmin();
   int size=v.size();

   double *doublearray = new double[size];
   for(int i = 0;i < size; i++)
   {
      doublearray[i] = v(lb+i);
   }

   int *intarray = new int[size];
   for(int i=0;i<size;i++)
   {
      intarray[i] = lb + i;
   }

   if (size > 0)
   {
     double_qsort2(doublearray, intarray, (unsigned int)size);
   }

   int ub=v.indexmax();
   dvector arr(lb, ub);
   for(int i = 0;i < size; i++) {
      arr(lb+i) = doublearray[i];
   }

   for(int i = 0; i < size; i++) {
      index(index.indexmin()+i) = intarray[i];
   }

   delete[] doublearray;
   doublearray = 0;

   delete[] intarray;
   intarray = 0;

   return arr;
}
