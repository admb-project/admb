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
void dmatrix::save_dmatrix_position(void) const
{
  // saves the size and address information for a dvar_vector
  dmatrix_position tmp(*this);
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
 * Description not yet available.
 * \param
 */
void d3_array::save_d3_array_position(void) const
{
  // saves the size and address information for a dvar_vector
  int mmin=indexmin();
  int mmax=indexmax();
  const int wsize=sizeof(int);
 /*
  dmatrix_position tmp(*this);
  const int wsize=sizeof(int);
  const int wsize1=sizeof(void*);

  for (int i=min;i<=max;i++)
  {
    gradient_structure::get_fp()->fwrite(&(tmp.lb(i)),wsize);
    gradient_structure::get_fp()->fwrite(&(tmp.ub(i)),wsize);
    gradient_structure::get_fp()->fwrite(&(tmp.ptr(i)),wsize1);
   }
 */
  gradient_structure::get_fp()->fwrite(&(mmin),wsize);
  gradient_structure::get_fp()->fwrite(&(mmax),wsize);
}

/**
 * Description not yet available.
 * \param
 */
d3_array_position restore_d3_array_position(void)
{
  // saves the size and address information for a dvar_vector
  int mmin;
  int mmax;
  gradient_structure::get_fp()->fread(&mmax,sizeof(int));
  gradient_structure::get_fp()->fread(&mmin,sizeof(int));
  d3_array_position tmp(mmin,mmax);
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix_position restore_dvar_matrix_position(void)
{
  // reads back the size and address information for a dvar_matrix
  // restores the size, address, and value information for a dvar_vector
  int min;
  int max;
  gradient_structure::get_fp()->fread(&max,sizeof(int));
  gradient_structure::get_fp()->fread(&min,sizeof(int));
  dvar_matrix_position tmp(min,max);
  // cout << "tmp.ptr= " << tmp.ptr ;
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
dmatrix_position restore_dmatrix_position(void)
{
  // reads back the size and address information for a dvar_matrix
  // restores the size, address, and value information for a dvar_vector
  int min;
  int max;
  gradient_structure::get_fp()->fread(&max,sizeof(int));
  gradient_structure::get_fp()->fread(&min,sizeof(int));
  dmatrix_position tmp(min,max);
  // cout << "tmp.ptr= " << tmp.ptr ;
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
dmatrix restore_dvar_matrix_derivatives(const dvar_matrix_position& _pos)
{
  dvar_matrix_position& pos= (dvar_matrix_position&) _pos;
  dmatrix tmp(pos);
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
dmatrix restore_dvar_matrix_der_nozero(const dvar_matrix_position& _pos)
{
  dvar_matrix_position& pos= (dvar_matrix_position&) _pos;
  dmatrix tmp(pos);
  for (int i=pos.row_max;i>=pos.row_min;i--)
  {
    tmp(i)=restore_dvar_vector_der_nozero(pos(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector restore_dvar_matrix_derivative_row(const dvar_matrix_position& _pos,
  const int& ii)
{
  dvar_matrix_position& pos= (dvar_matrix_position&) _pos;
  dvector tmp=restore_dvar_vector_derivatives(pos(ii));
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector restore_dvar_matrix_derivative_column(const dvar_matrix_position& _pos,
  const int& ii)
{
  dvar_matrix_position& pos= (dvar_matrix_position&) _pos;
  dvector tmpvec(pos.rowmin(),pos.rowmax());
  int min=tmpvec.indexmin();
  int max=tmpvec.indexmax();
  for (int i=min;i<=max;i++)
  {
    tmpvec(i)=((pos(i)).va)[ii].xvalue();
    ((pos(i)).va)[ii].xvalue()=0.;
  }
  return tmpvec;
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector nograd_assign(dvector tmp)
{
  kkludge_object kg;
  int min=tmp.indexmin();
  int max=tmp.indexmax();
  dvar_vector out(min,max,kg); // dvar_vector constructor that
                               // doesn't do any initialization
  for (int i=min;i<=max;i++)
  {
    value(out(i))=tmp(i);
  }
  return out;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix nograd_assign(const dmatrix& m)
{
  // cout << "Entering nograd assign"<<endl;
  //kkludge_object kg;
  int nrl=m.rowmin();
  int nrh=m.rowmax();
  ivector ncl(nrl,nrh);
  ivector nch(nrl,nrh);
  int i;
  for (i=nrl;i<=nrh;i++)
  {
    ncl(i)=m(i).indexmin();
    nch(i)=m(i).indexmax();
  }
  dvar_matrix out(nrl,nrh,ncl,nch); // dvar_matrix constructor that
                                       // doesn't do any initialization
  for (i=nrl;i<=nrh;i++)
  {
    for (int j=ncl(i);j<=nch(i);j++)
    {
      value(out(i,j))=m(i,j);
    }
    // out(i)=nograd_assign(m(i));
  }
  // cout << "Leaving nograd assign"<<endl;
  return out;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix nograd_assign_trans(const dmatrix& m)
{
  // cout << "Entering nograd assign"<<endl;
  //kkludge_object kg;
  int nrl=m.rowmin();
  int nrh=m.rowmax();
  ivector ncl(nrl,nrh);
  ivector nch(nrl,nrh);
  int i;
  for (i=nrl;i<=nrh;i++)
  {
    ncl(i)=m(i).indexmin();
    nch(i)=m(i).indexmax();
  }
  dvar_matrix out(nrl,nrh,ncl,nch); // dvar_matrix constructor that
                                       // doesn't do any initialization
  for (i=nrl;i<=nrh;i++)
  {
    for (int j=ncl(i);j<=nch(i);j++)
    {
      value(out(j,i))=m(i,j);
    }
    // out(i)=nograd_assign(m(i));
  }
  // cout << "Leaving nograd assign"<<endl;
  return out;
}

/**
 * Description not yet available.
 * \param
 */
void nograd_assign_column(const dvar_matrix& m, const dvector& v, const int& ii)
{
  // cout << "Entering nograd assign"<<endl;
  //kkludge_object kg;
  if (ii<m.colmin()||ii>m.colmax()  ||
   (v.indexmin()!=m.rowmin()) ||
   (v.indexmax()!=m.rowmax()) )
  {
    cerr << "Error -- Index out of bounds in\n"
      "void nograd_assign(const dvar_matrix& m,const dvector& v, const int& ii)"
      << endl;
    ad_exit(1);
  }
  int min=v.indexmin();
  int max=v.indexmax();
  for (int j=min;j<=max;j++)
  {
    value(m(j,ii))=v(j);
  }
    // out(i)=nograd_assign(m(i));
}

/**
 * Description not yet available.
 * \param
 */
  d3_array_position::d3_array_position(int mmin,int mmax) :
    min(mmin), max(mmax)
  {}
