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
#endif

/**
Saves the size, address, and value information for a imatrix.
*/
void imatrix::save_imatrix_value(void)
{
  for (int i=rowmin();i<=rowmax();i++)
  {
    ((*this)(i).save_ivector_value());
    ((*this)(i).save_ivector_position());
  }
}
/**
Saves the size and address information for a imatrix.
*/
void imatrix::save_imatrix_position(void)
{
  imatrix_position tmp(*this);
  size_t wsize=sizeof(int);
  size_t wsize1=sizeof(void*);

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
/**
Reads and restores back the size and address information for a imatrix.
*/
imatrix_position restore_imatrix_position(void)
{
  int min;
  int max;
  gradient_structure::get_fp()->fread(&max,sizeof(int));
  gradient_structure::get_fp()->fread(&min,sizeof(int));
  imatrix_position tmp(min,max);
  for (int i=max;i>=min;i--)
  {
    gradient_structure::get_fp()->fread(&(tmp.ptr(i)),sizeof(void*));
    gradient_structure::get_fp()->fread(&(tmp.ub(i)),sizeof(int));
    gradient_structure::get_fp()->fread(&(tmp.lb(i)),sizeof(int));
  }
  return tmp;
}
/**
 * Description not yet available.
 * \param
 */
imatrix restore_imatrix_value(const imatrix_position& mpos)
{
  // restores the size, address, and value information for a dvar_matrix
  //  the size, address, and value information for a dvar_matrix
  imatrix out(mpos);
  int min=out.rowmin();
  int max=out.rowmax();
  for (int i=max;i>=min;i--)
  {
    ivector_position vpos=restore_ivector_position();
    out(i)=restore_ivector_value(vpos);
  }
  return out;
}
