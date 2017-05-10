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
dvector sort(const dvector& v, int NSTACK)
{
  int lb = v.indexmin();
  unsigned int size = v.size();

  double* doublearray = new double[size];
  for (unsigned int i = 0; i < size; ++i)
  {
    doublearray[i] = v(lb);
    ++lb;
  }
  if (size > 1)
  {
    double_qsort(doublearray, size);
  }
  lb = v.indexmin();
  int ub = v.indexmax();
  dvector arr(lb, ub);
  for(unsigned int i = 0; i < size; ++i)
  {
    arr(lb) = doublearray[i];
    ++lb;
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
dvector sort(const dvector& v, const ivector& _index, int NSTACK)
{
  ivector& index = (ivector&) _index;
  if (v.size() != index.size())
  {
    cerr << " Incompatible array sizes in vector v and ivector index\n"
         << " in ivector sort(const ivector& v, const ivector& index)\n";
    ad_exit(1);
  }
  int lb = v.indexmin();
  unsigned int size = v.size();
  double* doublearray = new double[size];
  for (unsigned int i = 0; i < size; ++i)
  {
    doublearray[i] = v(lb);
    ++lb;
  }
  lb = v.indexmin();
  int* intarray = new int[size];
  for (unsigned int i = 0; i < size; ++i)
  {
    intarray[i] = lb;
    ++lb;
  }
  if (size > 1)
  {
    double_qsort2(doublearray, intarray, size);
  }
  lb = v.indexmin();
  int ub = v.indexmax();
  dvector arr(lb, ub);
  for (unsigned int i = 0; i < size; ++i)
  {
    arr(lb) = doublearray[i];
    ++lb;
  }
  lb = index.indexmin();
  for (unsigned int i = 0; i < size; ++i)
  {
    index(lb) = intarray[i];
    ++lb;
  }

  delete[] doublearray;
  doublearray = 0;

  delete[] intarray;
  intarray = 0;

  return arr;
}
