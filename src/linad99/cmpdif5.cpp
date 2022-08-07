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
#include <string.h>

#ifdef DEBUG
  #include <cassert>
#endif

/**
 * Description not yet available.
 * \param
 */
void dmatrix::save_dmatrix_value() const
{
  gradient_structure::fp->save_dmatrix_value(*this);
}
void DF_FILE::save_dmatrix_value(const dmatrix& m)
{
  // saves the size, address, and value information for a dvar_matrix
  //int ierr;
  int min = m.rowmin();
  int max = m.rowmax();
  const dvector* pmi = &m(min);
  for (int i = min; i <= max; ++i)
  {
    save_dvector_value(*pmi);
    save_dvector_position(*pmi);

    ++pmi;
  }
}

/**
 * Description not yet available.
 * \param
 */
void d3_array::save_d3_array_value() const
{
  gradient_structure::fp->save_d3_array_value(*this);
}
void DF_FILE::save_d3_array_value(const d3_array& a)
{
  // saves the size, address, and value information for a dvar_matrix
  //int ierr;
  int min = a.indexmin();
  int max = a.indexmax();
  const dmatrix* pai = &a(min);
  for (int i = min; i <= max; ++i)
  {
    save_dmatrix_value(*pai);
    save_dmatrix_position(*pai);

    ++pai;
  }
}

/**
 * Description not yet available.
 * \param
 */
dmatrix restore_dvar_matrix_value(const dvar_matrix_position& mpos)
{
  return gradient_structure::fp->restore_dvar_matrix_value(mpos);
}
dmatrix DF_FILE::restore_dvar_matrix_value(const dvar_matrix_position& mpos)
{
  // restores the size, address, and value information for a dvar_matrix
  dmatrix out((const dvar_matrix_position&)mpos);
  //int ierr;
  int min = out.rowmin();
  int max = out.rowmax();
  dvector* pouti = &out(max);
  for (int i = max;i >= min; --i)
  {
    dvar_vector_position vpos = restore_dvar_vector_position();
    *pouti = restore_dvar_vector_value(vpos);

    --pouti;
  }
  return out;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix restore_dmatrix_value(const dmatrix_position& mpos)
{
  return gradient_structure::fp->restore_dmatrix_value(mpos);
}
dmatrix DF_FILE::restore_dmatrix_value(const dmatrix_position& mpos)
{
  // restores the size, address, and value information for a dvar_matrix
  //  the size, address, and value information for a dvar_matrix
  dmatrix out((const dmatrix_position&)mpos);
  //int ierr;
  int min=out.rowmin();
  int max=out.rowmax();
  dvector* pouti = &out(max);
  for (int i = max; i >= min; --i)
  {
    dvector_position vpos = restore_dvector_position();
    *pouti = restore_dvector_value(vpos);

    --pouti;
  }
  return out;
}

/**
 * Description not yet available.
 * \param
 */
d3_array restore_d3_array_value(const d3_array_position& mpos)
{
  return gradient_structure::fp->restore_d3_array_value(mpos);
}
d3_array DF_FILE::restore_d3_array_value(const d3_array_position& mpos)
{
  // restores the size, address, and value information for a dvar_matrix
  //  the size, address, and value information for a dvar_matrix
  d3_array out((const d3_array_position&) mpos);
  //int ierr;
  int min = out.indexmin();
  int max = out.indexmax();
  dmatrix* pouti = &out(max);
  for (int i = max; i >= min; --i)
  {
    dmatrix_position vpos=restore_dmatrix_position();
    *pouti = restore_dmatrix_value(vpos);

    --pouti;
  }
  return out;
}

/**
 * Description not yet available.
 * \param
 */
dvector restore_dvar_vector_derivatives(const dvar_vector_position& tmp)
{
  int min = tmp.indexmin();
  int max = tmp.indexmax();

  // puts the derivative values from a dvar_vector's guts into a dvector
  dvector tempvec(min, max);
  double_and_int* va = tmp.va + min;

  double* ptmpvec = tempvec.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    //tempvec(i)=va[i].xvalue();
    //va[i].xvalue()=0.;
    *ptmpvec = va->x;
    va->x = 0.0;
    ++va;
    ++ptmpvec;
  }

//  _dp_vector_add
//  _dp_vector_elem_div
//  _dp_dotproduct
//  _dp_vector_elem_prod
//  _dp_scalar_product
//  _dp_vector_sub
//  _dw_block_move

  return tempvec;
}

/**
 * Description not yet available.
 * \param
 */
dvector restore_dvar_vector_der_nozero(const dvar_vector_position& tmp)
{
  // puts the derivative values from a dvar_vector's guts into a dvector
  int min = tmp.min;
  int max = tmp.max;
  dvector tempvec(min, max);
  double_and_int* va = tmp.va + min;

#ifdef USE_ASSEMBLER
  int min=tmp.indexmin();
  int n=tmp.indexmax()-min+1;
  dw_block_move(&(tempvec.elem(min)),&(va[min].xvalue()),n);
#else
  double* ptempvec = tempvec.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *ptempvec = va->x;
    ++va;
    ++ptempvec;
  }
#endif
  return tempvec;
}

/**
Puts the derivative values in a dvector into a dvar_vector's guts.
*/
void dvector::save_dvector_derivatives(const dvar_vector_position& pos) const
{
  const int min = pos.indexmin();
  const int max = pos.indexmax();

#ifdef DEBUG
  //Check for incompatible array sizes
  assert(min == indexmin() && max == indexmax());
#endif

  double_and_int* dest = pos.va + min;
  double* source = v + min;
  for (int i = min; i <= max; ++i)
  {
    dest->x += *source;
    ++source;
    ++dest;
  }
}

/**
 * Description not yet available.
 * \param
 */
void dvector::save_dvector_derivatives_na(const dvar_vector_position& pos) const
{
  // puts the derivative values in a dvector into a dvar_vector's guts
  int min = pos.indexmin();
  int max = pos.indexmax();

#ifndef OPT_LIB
  if (min != indexmin() || max != indexmax())
  {
    cerr << "Incompatible array sizes in " <<
    "void dvector::save_dvector_derivatives_na(const dvar_vector_position& pos)"
    << endl;
  }
#endif

  double_and_int* dest = pos.va + min;
  double* source = v + min;
  for (int i = min; i <= max; ++i)
  {
    dest->x = *source;
    ++dest;
    ++source;
  }
}

/**
 * Description not yet available.
 * \param
 */
void save_dmatrix_derivatives(const dvar_matrix_position& _pos, const double x,
  const int& i, int& j)
{
  dvar_matrix_position& pos= (dvar_matrix_position&) _pos;
  if ( i<pos.rowmin()||i>pos.rowmax() ||
     j<(pos.colmin())(i) || j>(pos.colmax())(i) )
  {
    cerr << "Error -- Index out of bounds in routine\n"
    " void save_dmatrix_derivatives(const dvar_matrix_position& pos"
    "  , const double& x, const int& i, const int& j)" << endl;
    ad_exit(1);
  }
  // puts the derivative values in a dvector into a dvar_vector's guts
  pos(i)(j)+=x;
}

/**
 * Description not yet available.
 * \param
 */
void dmatrix::save_dmatrix_derivatives(const dvar_matrix_position& _pos) const
{
  dvar_matrix_position& pos=(dvar_matrix_position&) _pos;
  // puts the derivative values in a dvector into a dvar_vector's guts
  int min=rowmin();
  int max=rowmax();
#ifndef OPT_LIB
  if (min != pos.row_min || max != pos.row_max)
  {
    cerr << "Incompatible array sizes in " <<
    "void dmatrix::save_dmatrix__derivatives(const dvar_matrix_position& pos)"
    << endl;
  }
#endif
  dvector* pmi = m + min;
  for (int i=min;i<=max;i++)
  {
    if (allocated(*pmi))
      pmi->save_dvector_derivatives(pos(i));
    ++pmi;
  }
}

/**
 * Description not yet available.
 * \param
 */
void dmatrix::save_dmatrix_derivatives_na(const dvar_matrix_position& _pos)
  const
{
  dvar_matrix_position& pos=(dvar_matrix_position&) _pos;
  // puts the derivative values in a dvector into a dvar_vector's guts
  int min=rowmin();
  int max=rowmax();
#ifndef OPT_LIB
  if (min!=pos.row_min||max!=pos.row_max)
  {
    cerr << "Incompatible array sizes in " <<
    "void dmatrix::save_dmatrix__derivatives(const dvar_matrix_position& pos)"
    << endl;
  }
#endif

  dvector* pmi = m + min;
  for (int i = min; i <= max; ++i)
  {
    if (allocated(*pmi))
      pmi->save_dvector_derivatives_na(pos(i));
    ++pmi;
  }
}

/**
 * Description not yet available.
 * \param
 */
void dvar_matrix::save_dvar_matrix_position() const
{
  gradient_structure::fp->save_dvar_matrix_position(*this);
}
void DF_FILE::save_dvar_matrix_position(const dvar_matrix& m)
{
  // saves the size and address information for a dvar_vector
  dvar_matrix_position tmp(m,1);
  constexpr size_t wsize=sizeof(int);
  constexpr size_t wsize1=sizeof(void*);

  int min=m.rowmin();
  int max=m.rowmax();
  int* ptmplbi = tmp.lb.get_v() + min;
  int* ptmpubi = tmp.ub.get_v() + min;
  for (int i=min;i<=max;++i)
  {
    fwrite(ptmplbi, wsize);
    fwrite(ptmpubi, wsize);
    fwrite(&(tmp.ptr(i)), wsize1);

    ++ptmplbi;
    ++ptmpubi;
  }
  fwrite(&(tmp.row_min), wsize);
  fwrite(&(tmp.row_max), wsize);
}
