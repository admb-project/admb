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
void imatrix::save_imatrix_value(DF_FILE* fp)
{
  for (int i=rowmin();i<=rowmax();i++)
  {
    ((*this)(i).save_ivector_value(fp));
    ((*this)(i).save_ivector_position(fp));
  }
}
/**
Saves the size and address information for a imatrix.
*/
void imatrix::save_imatrix_position(DF_FILE* fp)
{
  imatrix_position tmp(*this);
  constexpr size_t wsize=sizeof(int);
  constexpr size_t wsize1=sizeof(void*);

  //DF_FILE* fp = gradient_structure::get_fp();

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
Reads and restores back the size and address information for a imatrix.
*/
imatrix_position restore_imatrix_position(DF_FILE* fp)
{
  //DF_FILE* fp = gradient_structure::get_fp();

  constexpr size_t sizeofint = sizeof(int);
  constexpr size_t sizeofvoidp = sizeof(void*);
  int min;
  int max;
  fp->fread(&max, sizeofint);
  fp->fread(&min, sizeofint);
  imatrix_position tmp(min,max);
  for (int i=max;i>=min;i--)
  {
    fp->fread(&(tmp.ptr(i)), sizeofvoidp);
    fp->fread(&(tmp.ub(i)), sizeofint);
    fp->fread(&(tmp.lb(i)), sizeofint);
  }
  return tmp;
}
/**
 * Description not yet available.
 * \param
 */
imatrix restore_imatrix_value(const imatrix_position& mpos)
{
  DF_FILE* fp = gradient_structure::get_fp();
  // restores the size, address, and value information for a dvar_matrix
  //  the size, address, and value information for a dvar_matrix
  imatrix out(mpos);
  int min=out.rowmin();
  int max=out.rowmax();
  for (int i=max;i>=min;i--)
  {
    ivector_position vpos=restore_ivector_position(fp);
    out(i)=restore_ivector_value(vpos);
  }
  return out;
}
