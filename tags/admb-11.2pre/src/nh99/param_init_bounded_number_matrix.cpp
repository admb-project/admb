/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "param_init_bounded_number_matrix.h"
#include "admb_messages.h"
#ifndef OPT_LIB
  #include <cassert>
#endif

param_init_bounded_number_matrix::param_init_bounded_number_matrix(): v(NULL),
  index_min(0), index_max(0)
{
}
void param_init_bounded_number_matrix::allocate(int rowmin, int rowmax,
  int colmin, int colmax,
  const dmatrix& bmin, const dmatrix& bmax,
  const char* s)
{
  imatrix phase_start(rowmin, rowmax, colmin, colmax);
  phase_start = 1;
  allocate(rowmin, rowmax, colmin, colmax, bmin, bmax, phase_start, s);
}
void param_init_bounded_number_matrix::allocate(int rowmin, int rowmax,
  int colmin, int colmax,
  const dmatrix& bmin, const dmatrix& bmax,
  const imatrix& phase_start,
  const char* s)
{
#ifndef OPT_LIB
  assert(v == NULL);
#endif

  int size  = rowmax - rowmin + 1;
  if (size > 0)
  {
    index_min = rowmin;
    index_max = rowmax;
    v = new param_init_bounded_number_vector[size];
    if (!v)
    {
      cerr << " error trying to allocate memory in "
               "param_init_bounded_number_vector " << endl;
      ad_exit(1);
    }
    v -= index_min;

    for (int i = index_min; i <= index_max; i++)
    {
      /*if (it) v[i].set_initial_value(it[i]);*/
      adstring a = s + adstring("[") + str(i) + adstring("]");
      v[i].allocate(colmin, colmax, bmin[i], bmax[i], phase_start[i],
       (char*)(a));
    }
  }
}
void param_init_bounded_number_matrix::set_scalefactor(const double scalefactor)
{
  for (int i = index_min; i <= index_max; i++)
  {
    v[i].set_scalefactor(scalefactor);
  }
}
void param_init_bounded_number_matrix::set_scalefactor(
  const dmatrix& scalefactor)
{
  for (int i = index_min; i <= index_max; i++)
  {
    const dvector& dv = scalefactor(i);
    v[i].set_scalefactor(dv);
  }
}
dmatrix param_init_bounded_number_matrix::get_scalefactor() const
{
  dmatrix scalefactor;
  if (index_min < index_max)
  {
    scalefactor.allocate(index_min, index_max);
    for (int i = index_min; i <= index_max; i++)
    {
      param_init_bounded_number_vector& pibv = v[i];
      dvector dv = pibv.get_scalefactor();
      int indexmin = pibv.indexmin();
      int indexmax = pibv.indexmax();
      scalefactor.allocate(indexmin, indexmax);
      scalefactor(i) = dv;
    }
  }
  return scalefactor;
}
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
param_init_bounded_number_vector& param_init_bounded_number_matrix::operator[](
  const int i) const
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
param_init_bounded_number_vector& param_init_bounded_number_matrix::operator()(
  const int i) const
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
param_init_bounded_number& param_init_bounded_number_matrix::operator()(
  const int i, const int j) const
{
  return this->operator()(i)(j);
}
