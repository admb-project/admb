/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"


//#undef TRACE
//#define TRACE

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <string.h>

void dmatrix::save_dmatrix_value(void) _CONST
{
  // saves the size, address, and value information for a dvar_matrix
  int ierr;
  for (int i=rowmin();i<=rowmax();i++)
  {
    ((*this)(i).save_dvector_value());
    ((*this)(i).save_dvector_position());
  }
}




void d3_array::save_d3_array_value(void) const
{
  // saves the size, address, and value information for a dvar_matrix
  int ierr;
  for (int i=indexmin();i<=indexmax();i++)
  {
    ((*this)(i).save_dmatrix_value());
    ((*this)(i).save_dmatrix_position());
  }
}

dmatrix restore_dvar_matrix_value(BOR_CONST dvar_matrix_position& mpos)
{
  // restores the size, address, and value information for a dvar_matrix
  dmatrix out((BOR_CONST dvar_matrix_position&)mpos);
  int ierr;
  int min=out.rowmin();
  int max=out.rowmax();
  for (int i=max;i>=min;i--)
  {
    dvar_vector_position vpos=restore_dvar_vector_position();
    out(i)=restore_dvar_vector_value(vpos);
  }
  return out;
}

dmatrix restore_dmatrix_value(BOR_CONST dmatrix_position& mpos)
{
  // restores the size, address, and value information for a dvar_matrix
  //  the size, address, and value information for a dvar_matrix
  dmatrix out((BOR_CONST dmatrix_position&) mpos);
  int ierr;
  int min=out.rowmin();
  int max=out.rowmax();
  for (int i=max;i>=min;i--)
  {
    dvector_position vpos=restore_dvector_position();
    out(i)=restore_dvector_value(vpos);
  }
  return out;
}

d3_array restore_d3_array_value(const d3_array_position& mpos)
{
  // restores the size, address, and value information for a dvar_matrix
  //  the size, address, and value information for a dvar_matrix
  d3_array out((const d3_array_position&) mpos);
  int ierr;
  int min=out.indexmin();
  int max=out.indexmax();
  for (int i=max;i>=min;i--)
  {
    dmatrix_position vpos=restore_dmatrix_position();
    out(i)=restore_dmatrix_value(vpos);
  }
  return out;
}

dvector restore_dvar_vector_derivatives(BOR_CONST dvar_vector_position& tmp)
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

dvector restore_dvar_vector_der_nozero(BOR_CONST dvar_vector_position& tmp)
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

void dvector::save_dvector_derivatives(BOR_CONST dvar_vector_position& pos) _CONST
{
  // puts the derivative values in a dvector into a dvar_vector's guts
  int min=indexmin();
  int max=indexmax();
  if (min!=pos.indexmin() || max!=pos.indexmax())
  {
    cerr << "Incompatible array sizes in " <<
     "void dvector::save_dvector_derivatives(BOR_CONST dvar_vector_position& pos)" <<
     endl;
  }
  double_and_int * ptr=pos.va;

  #ifndef USE_ASSEMBLER
    for (int i=min;i<=max;i++)
    {
      ptr[i].xvalue()+=(*this)(i);
    }
  #else
    int n=max-min+1;
    dp_vector_add(&(ptr[min].xvalue()),&(ptr[min].xvalue()),
      &(this->elem(min)),n);
  #endif
}

void dvector::save_dvector_derivatives_na(BOR_CONST dvar_vector_position& pos) _CONST
{
  // puts the derivative values in a dvector into a dvar_vector's guts
  int min=indexmin();
  int max=indexmax();
  if (min!=pos.indexmin() || max!=pos.indexmax())
  {
    cerr << "Incompatible array sizes in " <<
     "void dvector::save_dvector_derivatives_na(BOR_CONST dvar_vector_position& pos)" <<
     endl;
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

void save_dmatrix_derivatives(BOR_CONST dvar_matrix_position& _pos, CGNU_DOUBLE x,BOR_CONST int& i,
  int& j)
{
  dvar_matrix_position& pos= (dvar_matrix_position&) _pos; 
  if ( i<pos.rowmin()||i>pos.rowmax() ||
     j<(pos.colmin())(i) || j>(pos.colmax())(i) )
  {
    cerr << "Error -- Index out of bounds in routine\n"
    " void save_dmatrix_derivatives(BOR_CONST dvar_matrix_position& pos"
    "  ,_CONST double& x,BOR_CONST int& i,BOR_CONST int& j)" << endl;
    ad_exit(1);
  }
  // puts the derivative values in a dvector into a dvar_vector's guts
  pos(i)(j)+=x;
}



void dmatrix::save_dmatrix_derivatives(BOR_CONST dvar_matrix_position& _pos) _CONST
{
  dvar_matrix_position& pos=(dvar_matrix_position&) _pos;
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
    if (allocated((*this)(i)))
      (*this)(i).save_dvector_derivatives(pos(i));
  }
}

void dmatrix::save_dmatrix_derivatives_na(BOR_CONST dvar_matrix_position& _pos) _CONST
{
  dvar_matrix_position& pos=(dvar_matrix_position&) _pos;
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
    if (allocated((*this)(i)))
      (*this)(i).save_dvector_derivatives_na(pos(i));
  }
}

void dvar_matrix::save_dvar_matrix_position(void) _CONST
{
  // saves the size and address information for a dvar_vector
  dvar_matrix_position tmp(*this,1);
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
