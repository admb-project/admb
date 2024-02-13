/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "param_init_bounded_number_matrix.h"
#include "admb_messages.h"
#ifdef DEBUG
  #include <cassert>
#endif

/// Default constructor
param_init_bounded_number_matrix::param_init_bounded_number_matrix():
  v(NULL),
  index_min(0),
  index_max(-1)
{
}
/// Destructor
param_init_bounded_number_matrix::~param_init_bounded_number_matrix()
{
  deallocate();
}
/**
Allocate matrix of param_init_bounded numbers with dimension
[rowmin to rowmax] x [colmin to colmax] with bounded values
[bmin, bmax].

Note: default phase_start is 1.

\param rowmin matrix row minimum index
\param rowmax matrix row max index
\param colmin matrix column minimum index
\param colmax matrix column max index
\param bmin bounded lower values
\param bmax bounded upper values
\param s id
*/
void param_init_bounded_number_matrix::allocate(
  int rowmin, int rowmax,
  int colmin, int colmax,
  const dmatrix& bmin, const dmatrix& bmax,
  const char* s)
{
  imatrix phase_start(rowmin, rowmax, colmin, colmax);
  phase_start = 1;
  allocate(rowmin, rowmax, colmin, colmax, bmin, bmax, phase_start, s);
}
/**
Allocate matrix of param_init_bounded numbers with dimension
[rowmin to rowmax] x [colmin to colmax] with bounded values
[bmin, bmax].

Note: default phase_start is 1.

\param rowmin matrix row minimum index
\param rowmax matrix row max index
\param colmin matrix column minimum index
\param colmax matrix column max index
\param bmin bounded lower values
\param bmax bounded upper values
\param phase_start
\param s id
*/
void param_init_bounded_number_matrix::allocate(
  int rowmin, int rowmax,
  int colmin, int colmax,
  const dmatrix& bmin, const dmatrix& bmax,
  const imatrix& phase_start,
  const char* s)
{
#ifdef DEBUG
  assert(v == NULL);
#endif

  if (rowmax >= rowmin)
  {
    unsigned int size  = static_cast<unsigned int>(rowmax - rowmin + 1);
    v = new param_init_bounded_number_vector[size];
    if (!v)
    {
      cerr << " error trying to allocate memory in "
               "param_init_bounded_number_vector " << endl;
      ad_exit(1);
    }

    index_min = rowmin;
    index_max = rowmax;
    v -= index_min;

    for (int i = index_min; i <= index_max; ++i)
    {
      /*if (it) v[i].set_initial_value(it[i]);*/
      adstring a = s + adstring("[") + str(i) + adstring("]");
      v[i].allocate(colmin, colmax, bmin[i], bmax[i], phase_start[i],
       (char*)(a));
    }
  }
}
/**
Set scalefactor for each element of param_init_bounded_number_matrix.

\param scalefactor double
*/
void param_init_bounded_number_matrix::set_scalefactor(
  const double scalefactor)
{
#ifdef DEBUG
  assert(v != NULL);
#endif

  for (int i = index_min; i <= index_max; ++i)
  {
    v[i].set_scalefactor(scalefactor);
  }
}
/**
Set scalefactor for each element of param_init_bounded_number_matrix.
scalefactor should have the same dimension as param_init_bounded_number_matrix.

\param scalefactor dmatrix
*/
void param_init_bounded_number_matrix::set_scalefactor(
  const dmatrix& scalefactor)
{
#ifdef DEBUG
  assert(v != NULL);
#endif
  for (int i = index_min; i <= index_max; i++)
  {
    v[i].set_scalefactor(scalefactor(i));
  }
}
/**
Returns matrix with scalefactors for each element
in param_init_bounded_number_matrix.
*/
dmatrix param_init_bounded_number_matrix::get_scalefactor() const
{
  dmatrix scalefactor;
  if (index_min < index_max)
  {
    scalefactor.allocate(index_min, index_max);
    for (int i = index_min; i <= index_max; i++)
    {
      param_init_bounded_number_vector& vi = v[i];
      scalefactor(i).allocate(vi.indexmin(), vi .indexmax());
      scalefactor(i) = vi.get_scalefactor();
    }
  }
  return scalefactor;
}
/**
Free allocated memory.
*/
void param_init_bounded_number_matrix::deallocate()
{
  if (v)
  {
    for (int i = index_min; i <= index_max; i++)
    {
      v[i].deallocate();
    }
    v += index_min;
    delete [] v;
    v = NULL;
  }
}
/**
Returns param_init_bounded_vector for index i.
Bounds checking is performed.

\param i index
*/
param_init_bounded_number_vector&
param_init_bounded_number_matrix::operator[](const int i) const
{
#ifndef OPT_LIB
  if (i < index_min)
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too low",
    "param_init_bounded_number_matrix::operator[](const int i) const",
    index_min, index_max, i);
  }
  if (i > index_max)
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too high",
    "param_init_bounded_number_matrix::operator[](const int i) const",
    index_min, index_max, i);
  }
#endif
  return v[i];
}
/**
Returns param_init_bounded_vector for index i.
Bounds checking is performed.

\param i index
*/
param_init_bounded_number_vector&
param_init_bounded_number_matrix::operator()(const int i) const
{
#ifndef OPT_LIB
  if (i < index_min)
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too low",
    "param_init_bounded_number_matrix::operator[](const int i) const",
    index_min, index_max, i);
  }
  if (i > index_max)
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too high",
    "param_init_bounded_number_matrix::operator[](const int i) const",
    index_min, index_max, i);
  }
#endif
  return v[i];
}
/**
Returns param_init_bounded_number at index i and j.
Bounds checking is performed.

\param i row index
\param j column index
*/
param_init_bounded_number&
param_init_bounded_number_matrix::operator()(const int i, const int j) const
{
  return this->operator()(i)(j);
}
