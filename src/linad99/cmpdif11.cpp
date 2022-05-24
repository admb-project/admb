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
#include <fvar.hpp>

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <string.h>

/**
 * Description not yet available.
 * \param
 */
void banded_symmetric_dvar_matrix::save_dvar_matrix_value(DF_FILE* fp) const
{
  // saves the size, address, and value information for a dvar_matrix
  int min=d.rowmin();
  int max=d.rowmax();
  for (int i=min;i<=max;i++)
  {
    d(i).save_dvar_vector_value(fp);
    d(i).save_dvar_vector_position(fp);
  }
}

/**
 * Description not yet available.
 * \param
 */
void banded_lower_triangular_dvar_matrix::save_dvar_matrix_value(DF_FILE* fp) const
{
  // saves the size, address, and value information for a dvar_matrix
  int min=d.rowmin();
  int max=d.rowmax();
  for (int i=min;i<=max;i++)
  {
    d(i).save_dvar_vector_value(fp);
    d(i).save_dvar_vector_position(fp);
  }
}

/**
 * Description not yet available.
 * \param
 */
void banded_symmetric_dmatrix::save_dmatrix_value(DF_FILE* fp) const
{
  // saves the size, address, and value information for a dvar_matrix
  int min=d.rowmin();
  int max=d.rowmax();
  for (int i=min;i<=max;i++)
  {
    d(i).save_dvector_value(fp);
    d(i).save_dvector_position(fp);
  }
}

/**
 * Description not yet available.
 * \param
 */
banded_symmetric_dmatrix restore_banded_symmetric_dvar_matrix_value(
  const dvar_matrix_position& mpos)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  // restores the size, address, and value information for a dvar_matrix
  banded_symmetric_dmatrix out((const dvar_matrix_position&)mpos);
  //int ierr;
  int min=out.rowmin();
  int max=out.rowmax();
  for (int i=max;i>=min;i--)
  {
    dvar_vector_position vpos=fp->restore_dvar_vector_position();
    out.d(i)=restore_dvar_vector_value(vpos);
  }
  return out;
}

/**
 * Description not yet available.
 * \param
 */
banded_lower_triangular_dmatrix
restore_banded_lower_triangular_dvar_matrix_value(
  const dvar_matrix_position& mpos)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  // restores the size, address, and value information for a dvar_matrix
  banded_lower_triangular_dmatrix out((const dvar_matrix_position&)mpos);
  //int ierr;
  int min=out.rowmin();
  int max=out.rowmax();
  for (int i=max;i>=min;i--)
  {
    dvar_vector_position vpos=fp->restore_dvar_vector_position();
    out.d(i)=restore_dvar_vector_value(vpos);
  }
  return out;
}

/**
 * Description not yet available.
 * \param
 */
void banded_symmetric_dvar_matrix::save_dvar_matrix_position(DF_FILE* fp) const
{
  // saves the size and address information for a dvar_vector
  dvar_matrix_position tmp((*this).d,1);
  constexpr size_t wsize = sizeof(int);
  constexpr size_t wsize1 = sizeof(void*);

  int min=rowmin();
  int max=rowmax();
  for (int i=min;i<=max;i++)
  {
    fp->fwrite(&(tmp.lb(i)),wsize);
    fp->fwrite(&(tmp.ub(i)),wsize);
    fp->fwrite(&(tmp.ptr(i)),wsize1);
  }
  fp->fwrite(&(tmp.row_min),wsize);
  fp->fwrite(&(tmp.row_max),wsize);
}

/**
 * Description not yet available.
 * \param
 */
void banded_lower_triangular_dvar_matrix::save_dvar_matrix_position(DF_FILE* fp) const
{
  // saves the size and address information for a dvar_vector
  dvar_matrix_position tmp((*this).d,1);
  constexpr size_t wsize=sizeof(int);
  constexpr size_t wsize1=sizeof(void*);

  int min=rowmin();
  int max=rowmax();
  for (int i=min;i<=max;i++)
  {
    fp->fwrite(&(tmp.lb(i)),wsize);
    fp->fwrite(&(tmp.ub(i)),wsize);
    fp->fwrite(&(tmp.ptr(i)),wsize1);
  }
  fp->fwrite(&(tmp.row_min),wsize);
  fp->fwrite(&(tmp.row_max),wsize);
}

/**
 * Description not yet available.
 * \param
 */
void banded_symmetric_dmatrix::save_dmatrix_derivatives(
  const dvar_matrix_position& pos) const
{
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
    const dvector& xx=(*this)(i);
    dvector& x=(dvector&) xx;
    dvar_matrix_position& pos1=(dvar_matrix_position&)pos;
    //((const dvector&)x).save_dvector_derivatives(pos1(i));
    x.save_dvector_derivatives(pos1(i));
  }
}

/**
 * Description not yet available.
 * \param
 */
void banded_lower_triangular_dmatrix::save_dmatrix_derivatives(
  const dvar_matrix_position& pos) const
{
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
    dvector& x=(dvector&)d(i);
    dvar_matrix_position& pos1= (dvar_matrix_position&) pos;
    x.save_dvector_derivatives(pos1(i));
  }
}

/**
 * Description not yet available.
 * \param
 */
banded_lower_triangular_dmatrix
  restore_banded_lower_triangular_dvar_matrix_derivatives
  (const dvar_matrix_position& _pos)
{
  dvar_matrix_position& pos= (dvar_matrix_position&) _pos;
  banded_lower_triangular_dmatrix tmp(pos);
  for (int i=pos.row_max;i>=pos.row_min;i--)
  {
    tmp(i)=restore_dvar_vector_derivatives(pos(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
banded_symmetric_dmatrix restore_bounded_symmetric_dvar_matrix_derivatives
  (const dvar_matrix_position& _pos)
{
  dvar_matrix_position& pos= (dvar_matrix_position&) _pos;
  banded_symmetric_dmatrix tmp(pos);
  for (int i=pos.row_max;i>=pos.row_min;i--)
  {
    tmp(i)=restore_dvar_vector_derivatives(pos(i));
  }
  return tmp;
}
