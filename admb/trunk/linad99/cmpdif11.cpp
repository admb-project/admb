/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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

void banded_symmetric_dvar_matrix::save_dvar_matrix_value(void) _CONST
{
  // saves the size, address, and value information for a dvar_matrix
  int min=d.rowmin();
  int max=d.rowmax();
  for (int i=min;i<=max;i++)
  {
    d(i).save_dvar_vector_value();
    d(i).save_dvar_vector_position();
  }
}

void banded_lower_triangular_dvar_matrix::save_dvar_matrix_value(void) _CONST
{
  // saves the size, address, and value information for a dvar_matrix
  int min=d.rowmin();
  int max=d.rowmax();
  for (int i=min;i<=max;i++)
  {
    d(i).save_dvar_vector_value();
    d(i).save_dvar_vector_position();
  }
}

void banded_symmetric_dmatrix::save_dmatrix_value(void) _CONST
{
  // saves the size, address, and value information for a dvar_matrix
  int min=d.rowmin();
  int max=d.rowmax();
  for (int i=min;i<=max;i++)
  {
    d(i).save_dvector_value();
    d(i).save_dvector_position();
  }
}



banded_symmetric_dmatrix restore_banded_symmetric_dvar_matrix_value(BOR_CONST dvar_matrix_position& mpos)
{
  // restores the size, address, and value information for a dvar_matrix
  banded_symmetric_dmatrix out((BOR_CONST dvar_matrix_position&)mpos);
  int ierr;
  int min=out.rowmin();
  int max=out.rowmax();
  for (int i=max;i>=min;i--)
  {
    dvar_vector_position vpos=restore_dvar_vector_position();
    out.d(i)=restore_dvar_vector_value(vpos);
  }
  return out;
}

banded_lower_triangular_dmatrix restore_banded_lower_triangular_dvar_matrix_value(BOR_CONST dvar_matrix_position& mpos)
{
  // restores the size, address, and value information for a dvar_matrix
  banded_lower_triangular_dmatrix out((BOR_CONST dvar_matrix_position&)mpos);
  int ierr;
  int min=out.rowmin();
  int max=out.rowmax();
  for (int i=max;i>=min;i--)
  {
    dvar_vector_position vpos=restore_dvar_vector_position();
    out.d(i)=restore_dvar_vector_value(vpos);
  }
  return out;
}

void banded_symmetric_dvar_matrix::save_dvar_matrix_position(void) _CONST
{
  // saves the size and address information for a dvar_vector
  dvar_matrix_position tmp((*this).d,1);
  const int wsize=sizeof(int);
  const int wsize1=sizeof(void*);

  int min=rowmin();
  int max=rowmax();
  for (int i=min;i<=max;i++)
  {
    gradient_structure::get_fp()->fwrite(&(tmp.lb(i)),wsize);
    gradient_structure::get_fp()->fwrite(&(tmp.ub(i)),wsize);
    gradient_structure::get_fp()->fwrite(&(tmp.ptr(i)),wsize1);
   }
  gradient_structure::get_fp()->fwrite(&(tmp.row_min),wsize);
  gradient_structure::get_fp()->fwrite(&(tmp.row_max),wsize);
}

void banded_lower_triangular_dvar_matrix::save_dvar_matrix_position(void) _CONST
{
  // saves the size and address information for a dvar_vector
  dvar_matrix_position tmp((*this).d,1);
  const int wsize=sizeof(int);
  const int wsize1=sizeof(void*);

  int min=rowmin();
  int max=rowmax();
  for (int i=min;i<=max;i++)
  {
    gradient_structure::get_fp()->fwrite(&(tmp.lb(i)),wsize);
    gradient_structure::get_fp()->fwrite(&(tmp.ub(i)),wsize);
    gradient_structure::get_fp()->fwrite(&(tmp.ptr(i)),wsize1);
   }
  gradient_structure::get_fp()->fwrite(&(tmp.row_min),wsize);
  gradient_structure::get_fp()->fwrite(&(tmp.row_max),wsize);
}

void banded_symmetric_dmatrix::save_dmatrix_derivatives(_CONST dvar_matrix_position& pos) _CONST
{
  // puts the derivative values in a dvector into a dvar_vector's guts
  int min=rowmin();
  int max=rowmax();
  if (min!=pos.row_min||max!=pos.row_max)
  {
    cerr << "Incompatible array sizes in " <<
     "void dmatrix::save_dmatrix__derivatives(BOR_CONST dvar_matrix_position& pos)" <<
     endl;
  }
  for (int i=min;i<=max;i++)
  {
#if defined(__MSVC32__)
     _CONST dvector& xx=(*this)(i);
#else
    const dvector& xx=(*this)(i);
#endif
    dvector& x=(dvector&) xx;
    dvar_matrix_position& pos1=(dvar_matrix_position&)pos;
#if defined(__MSVC32__)
    //((BOR_CONST dvector&)x).save_dvector_derivatives(pos1(i));
    x.save_dvector_derivatives((pos1(i)));
#else
    x.save_dvector_derivatives(pos1(i));
#endif
  }
}

void banded_lower_triangular_dmatrix::save_dmatrix_derivatives(_CONST dvar_matrix_position& pos) _CONST
{
  // puts the derivative values in a dvector into a dvar_vector's guts
  int min=rowmin();
  int max=rowmax();
  if (min!=pos.row_min||max!=pos.row_max)
  {
    cerr << "Incompatible array sizes in " <<
     "void dmatrix::save_dmatrix__derivatives(BOR_CONST dvar_matrix_position& pos)" <<
     endl;
  }
  for (int i=min;i<=max;i++)
  {
#if defined(__MSVC32__)
    dvector& x=(dvector&)(*this)(i);
#else
    const dvector& cx=(const dvector&)(*this)(i);
    dvector& x=(dvector&)(cx);
    //dvector& x=(dvector&)(*this)(i);
#endif
    dvar_matrix_position& pos1= (dvar_matrix_position&) pos;
#if defined(__MSVC32__)
    x.save_dvector_derivatives(pos1(i));
#else
    x.save_dvector_derivatives(pos1(i));
#endif
  }
}

banded_lower_triangular_dmatrix
  restore_banded_lower_triangular_dvar_matrix_derivatives
  (BOR_CONST dvar_matrix_position& _pos)
{
  dvar_matrix_position& pos= (dvar_matrix_position&) _pos; 
  banded_lower_triangular_dmatrix tmp(pos);
  for (int i=pos.row_max;i>=pos.row_min;i--)
  {
    tmp(i)=restore_dvar_vector_derivatives(pos(i));
  }
  return tmp;
}

banded_symmetric_dmatrix restore_bounded_symmetric_dvar_matrix_derivatives
  (BOR_CONST dvar_matrix_position& _pos)
{
  dvar_matrix_position& pos= (dvar_matrix_position&) _pos; 
  banded_symmetric_dmatrix tmp(pos);
  for (int i=pos.row_max;i>=pos.row_min;i--)
  {
    tmp(i)=restore_dvar_vector_derivatives(pos(i));
  }
  return tmp;
}

