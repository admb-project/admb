/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <fvar.hpp>

#ifdef __TURBOC__
  #pragma hdrstop
#endif

void imatrix::save_imatrix_value(void)
{
  // saves the size, address, and value information for a imatrix
  int ierr;
  for (int i=rowmin();i<=rowmax();i++)
  {
    ((*this)(i).save_ivector_value());
    ((*this)(i).save_ivector_position());
  }
}


void imatrix::save_imatrix_position(void)
{
  // saves the size and address information for a ivector
  imatrix_position tmp(*this);
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

imatrix_position restore_imatrix_position(void)
{
  // reads back the size and address information for a imatrix
  // restores the size, address, and value information for a ivector
  int min;
  int max;
  gradient_structure::get_fp()->fread(&max,sizeof(int));
  gradient_structure::get_fp()->fread(&min,sizeof(int));
  imatrix_position tmp(min,max);
  // cout << "tmp.ptr= " << tmp.ptr ;
  for (int i=max;i>=min;i--)
  {
    gradient_structure::get_fp()->fread(&(tmp.ptr(i)),sizeof(void*));
    gradient_structure::get_fp()->fread(&(tmp.ub(i)),sizeof(int));
    gradient_structure::get_fp()->fread(&(tmp.lb(i)),sizeof(int));
  }
  return tmp;
}

imatrix restore_imatrix_value(BOR_CONST imatrix_position& mpos)
{
  // restores the size, address, and value information for a dvar_matrix
  //  the size, address, and value information for a dvar_matrix
  imatrix out(mpos);
  int ierr;
  int min=out.rowmin();
  int max=out.rowmax();
  for (int i=max;i>=min;i--)
  {
    ivector_position vpos=restore_ivector_position();
    out(i)=restore_ivector_value(vpos);
  }
  return out;
}

