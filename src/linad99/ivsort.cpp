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
ivector sort(const ivector& v, int NSTACK)
{
  int lb = v.indexmin();
  unsigned int size = v.size();
  int* intarray = new int[size];
  for(unsigned int i = 0; i < size; ++i)
  {
    intarray[i] = v(lb);
    ++lb;
  }
  if (size > 1)
  {
    int_qsort(intarray, size);
  }
  lb = v.indexmin();
  int ub = v.indexmax();
  ivector arr(lb, ub);
  for(unsigned int i = 0; i < size; ++i)
  {
    arr(lb) = intarray[i];
    ++lb;
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
ivector sort(const ivector& v, const ivector& _index, int NSTACK)
{
  ivector& index = (ivector&)_index;
  if (v.size() != index.size())
  {
    cerr << " Incompatible array sizes in vector v and ivector index\n"
         << " in ivector sort(const ivector& v, const ivector& index)\n";
    ad_exit(1);
  }
  int lb = v.indexmin();
  unsigned int size = v.size();
  int* intarray = new int[size];
  for (unsigned int i = 0; i < size; ++i)
  {
    intarray[i] = v(lb);
    ++lb;
  }
  lb = v.indexmin();
  int* intarray2 = new int[size];
  for (unsigned int i = 0; i < size; ++i)
  {
    intarray2[i] = lb;
    ++lb;
  }
  if (size > 1)
  {
    int_qsort2(intarray, intarray2, size);
  }
  lb = v.indexmin();
  int ub=v.indexmax();
  ivector arr(lb, ub);
  for (unsigned int i = 0; i < size; ++i)
  {
    arr(lb) = intarray[i];
    ++lb;
  }
  lb = index.indexmin();
  for (unsigned int i = 0; i < size; ++i)
  {
    index(lb) = intarray2[i];
    ++lb;
  }

  delete [] intarray;
  intarray = 0;

  delete [] intarray2;
  intarray2 = 0;

  return arr;
}
