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
  gradient_structure::get_fp()->save_dmatrix_value(*this);
}
void DF_FILE::save_dmatrix_value(const dmatrix& m)
{
  // saves the size, address, and value information for a dvar_matrix
  //int ierr;
  for (int i=m.rowmin();i<=m.rowmax();i++)
  {
    save_dvector_value(m(i));
    save_dvector_position(m(i));
  }
}

/**
 * Description not yet available.
 * \param
 */
void d3_array::save_d3_array_value() const
{
  gradient_structure::get_fp()->save_d3_array_value(*this);
}
void DF_FILE::save_d3_array_value(const d3_array& a)
{
  // saves the size, address, and value information for a dvar_matrix
  //int ierr;
  for (int i=a.indexmin();i<=a.indexmax();i++)
  {
    save_dmatrix_value(a(i));
    save_dmatrix_position(a(i));
  }
}

/**
 * Description not yet available.
 * \param
 */
dmatrix restore_dvar_matrix_value(const dvar_matrix_position& mpos)
{
  return gradient_structure::get_fp()->restore_dvar_matrix_value(mpos);
}
dmatrix DF_FILE::restore_dvar_matrix_value(const dvar_matrix_position& mpos)
{
  // restores the size, address, and value information for a dvar_matrix
  dmatrix out((const dvar_matrix_position&)mpos);
  //int ierr;
  int min=out.rowmin();
  int max=out.rowmax();
  for (int i=max;i>=min;i--)
  {
    dvar_vector_position vpos=restore_dvar_vector_position();
    out(i)=restore_dvar_vector_value(vpos);
  }
  return out;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix restore_dmatrix_value(const dmatrix_position& mpos)
{
  return gradient_structure::get_fp()->restore_dmatrix_value(mpos);
}
dmatrix DF_FILE::restore_dmatrix_value(const dmatrix_position& mpos)
{
  // restores the size, address, and value information for a dvar_matrix
  //  the size, address, and value information for a dvar_matrix
  dmatrix out((const dmatrix_position&) mpos);
  //int ierr;
  int min=out.rowmin();
  int max=out.rowmax();
  for (int i=max;i>=min;i--)
  {
    dvector_position vpos=restore_dvector_position();
    out(i)=restore_dvector_value(vpos);
  }
  return out;
}

/**
 * Description not yet available.
 * \param
 */
d3_array restore_d3_array_value(const d3_array_position& mpos)
{
  return gradient_structure::get_fp()->restore_d3_array_value(mpos);
}
d3_array DF_FILE::restore_d3_array_value(const d3_array_position& mpos)
{
  // restores the size, address, and value information for a dvar_matrix
  //  the size, address, and value information for a dvar_matrix
  d3_array out((const d3_array_position&) mpos);
  //int ierr;
  int min=out.indexmin();
  int max=out.indexmax();
  for (int i=max;i>=min;i--)
  {
    dmatrix_position vpos=restore_dmatrix_position();
    out(i)=restore_dmatrix_value(vpos);
  }
  return out;
}

/**
 * Description not yet available.
 * \param
 */
dvector restore_dvar_vector_derivatives(const dvar_vector_position& tmp)
{
  // puts the derivative values from a dvar_vector's guts into a dvector
  dvector tempvec(tmp.indexmin(),tmp.indexmax());
  double_and_int * va=tmp.va;

#ifndef USE_ASSEMBLER
  for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
  {
    tempvec(i)=va[i].xvalue();
    va[i].xvalue()=0.;
  }
#else
     int min=tmp.indexmin();
     int n=tmp.max-min+1;
     dw_block_move(&(tempvec.elem(min)),&(va[min].xvalue()),n);
     dp_block_initialize(&(va[min].xvalue()),n);
#endif

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
  dvector tempvec(tmp.min,tmp.max);
  double_and_int * va=tmp.va;

  #ifndef USE_ASSEMBLER
    for (int i=tmp.indexmin();i<=tmp.indexmax();i++)
    {
      tempvec(i)=va[i].xvalue();
    }
  #else
     int min=tmp.indexmin();
     int n=tmp.indexmax()-min+1;
     dw_block_move(&(tempvec.elem(min)),&(va[min].xvalue()),n);
  #endif
  return tempvec;
}

/**
Puts the derivative values in a dvector into a dvar_vector's guts.
*/
void dvector::save_dvector_derivatives(const dvar_vector_position& pos) const
{
  const int min = indexmin();
  const int max = indexmax();

#ifdef DEBUG
  //Check for incompatible array sizes
  assert(min == pos.indexmin() && max == pos.indexmax());
#endif

#ifdef USE_ASSEMBLER
  double_and_int* ptr = pos.va;
  int n=max-min+1;
  dp_vector_add(&(ptr[min].xvalue()), &(ptr[min].xvalue()),
    &(this->elem(min)), n);
#else
  double_and_int* dest = &pos.va[min];
  double* source = &v[min];
  for (int i = min; i <= max; ++i)
  {
    dest->x += *source;
    ++source;
    ++dest;
  }
#endif
}

/**
 * Description not yet available.
 * \param
 */
void dvector::save_dvector_derivatives_na(const dvar_vector_position& pos) const
{
  // puts the derivative values in a dvector into a dvar_vector's guts
  int min=indexmin();
  int max=indexmax();
  if (min!=pos.indexmin() || max!=pos.indexmax())
  {
    cerr << "Incompatible array sizes in " <<
    "void dvector::save_dvector_derivatives_na(const dvar_vector_position& pos)"
    << endl;
  }
  double_and_int * ptr=pos.va;

#ifndef USE_ASSEMBLER
  for (int i=min;i<=max;i++)
  {
    ptr[i].xvalue()=(*this)(i);
  }
#else
     int n=max-min+1;
     dw_block_move(&(ptr[min].xvalue()),&(this->elem(min)),n);
#endif
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
  if (min!=pos.row_min||max!=pos.row_max)
  {
    cerr << "Incompatible array sizes in " <<
    "void dmatrix::save_dmatrix__derivatives(const dvar_matrix_position& pos)"
    << endl;
  }
  for (int i=min;i<=max;i++)
  {
    if (allocated((*this)(i)))
      (*this)(i).save_dvector_derivatives(pos(i));
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
  if (min!=pos.row_min||max!=pos.row_max)
  {
    cerr << "Incompatible array sizes in " <<
    "void dmatrix::save_dmatrix__derivatives(const dvar_matrix_position& pos)"
    << endl;
  }
  for (int i=min;i<=max;i++)
  {
    if (allocated((*this)(i)))
      (*this)(i).save_dvector_derivatives_na(pos(i));
  }
}

/**
 * Description not yet available.
 * \param
 */
void dvar_matrix::save_dvar_matrix_position() const
{
  gradient_structure::get_fp()->save_dvar_matrix_position(*this);
}
void DF_FILE::save_dvar_matrix_position(const dvar_matrix& m)
{
  // saves the size and address information for a dvar_vector
  dvar_matrix_position tmp(m,1);
  constexpr size_t wsize=sizeof(int);
  constexpr size_t wsize1=sizeof(void*);

  int min=m.rowmin();
  int max=m.rowmax();
  for (int i=min;i<=max;++i)
  {
    fwrite(&(tmp.lb(i)),wsize);
    fwrite(&(tmp.ub(i)),wsize);
    fwrite(&(tmp.ptr(i)),wsize1);
  }
  fwrite(&(tmp.row_min),wsize);
  fwrite(&(tmp.row_max),wsize);
}
