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
 * Saves size and address information for a dmatrix to adjoint data file.
 */
void dmatrix::save_dmatrix_position() const
{
  gradient_structure::fp->save_dmatrix_position(*this);
}
void DF_FILE::save_dmatrix_position(const dmatrix& m)
{
  dmatrix_position tmp(m);

  int min=m.rowmin();
  int max=m.rowmax();
  size_t size = static_cast<size_t>(max - min + 1);

  constexpr size_t wsize1=sizeof(void*);
  fwrite(&tmp.ptr.elem(min), wsize1 * size);

  constexpr size_t wsize = sizeof(int);
  fwrite(tmp.lb.get_v() + min, wsize * size);
  fwrite(tmp.ub.get_v() + min, wsize * size);

  fwrite(&(tmp.row_min), wsize);
  fwrite(&(tmp.row_max), wsize);
}

/**
 * Description not yet available.
 * \param
 */
void d3_array::save_d3_array_position() const
{
  gradient_structure::fp->save_d3_array_position(*this);
}
void DF_FILE::save_d3_array_position(const d3_array& a)
{
  // saves the size and address information for a dvar_vector
  int mmin=a.indexmin();
  int mmax=a.indexmax();
  constexpr size_t wsize = sizeof(int);
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
  fwrite(&(mmin),wsize);
  fwrite(&(mmax),wsize);
}

/**
 * Description not yet available.
 * \param
 */
d3_array_position restore_d3_array_position()
{
  return gradient_structure::fp->restore_d3_array_position();
}
d3_array_position DF_FILE::restore_d3_array_position()
{
  constexpr size_t wsize = sizeof(int);

  // saves the size and address information for a dvar_vector
  int mmin;
  int mmax;
  fread(&mmax,wsize);
  fread(&mmin,wsize);
  d3_array_position tmp(mmin,mmax);
  return tmp;
}

/**
 * Reads back the size and address information for a dvar_matrix,
 * restores the size, address, and value information for a dvar_vector
 */
dvar_matrix_position restore_dvar_matrix_position()
{
  return gradient_structure::fp->restore_dvar_matrix_position();
}
dvar_matrix_position DF_FILE::restore_dvar_matrix_position()
{
  constexpr size_t wsize = sizeof(int);

  int min;
  int max;
  fread(&max, wsize);
  fread(&min, wsize);
  dvar_matrix_position tmp(min,max);

  size_t size = static_cast<size_t>(max - min + 1);

  fread(tmp.ub.get_v() + min, wsize * size);
  fread(tmp.lb.get_v() + min, wsize * size);

  constexpr size_t wsize2 = sizeof(void*);
  fread(&tmp.ptr.elem(min), wsize2 * size);

  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix_position restore_dmatrix_position()
{
  return gradient_structure::fp->restore_dmatrix_position();
}
dmatrix_position DF_FILE::restore_dmatrix_position()
{
  // reads back the size and address information for a dvar_matrix
  // restores the size, address, and value information for a dvar_vector
  constexpr size_t wsize = sizeof(int);
  int min;
  int max;
  fread(&max, wsize);
  fread(&min, wsize);

  dmatrix_position tmp(min,max);
  // cout << "tmp.ptr= " << tmp.ptr ;
  size_t size = static_cast<size_t>(max - min + 1);
  fread(tmp.ub.get_v() + min, wsize * size);
  fread(tmp.lb.get_v() + min, wsize * size);

  constexpr size_t wsize2 = sizeof(void*);
  fread(&tmp.ptr.elem(min), wsize2 * size);

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
  int min = pos.row_min;
  int max = pos.row_max;
  dvector* ptmpi = &tmp(max);
  for (int i = max; i >= min; --i)
  {
    *ptmpi = restore_dvar_vector_derivatives(pos(i));
    --ptmpi;
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
  int min = pos.row_min;
  int max = pos.row_max;
  dvector* ptmpi = &tmp(max);
  for (int i = max; i >= min; --i)
  {
    *ptmpi = restore_dvar_vector_der_nozero(pos(i));
    --ptmpi;
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
  dvar_matrix_position& pos =(dvar_matrix_position&)_pos;

  int min = pos.rowmin();
  int max = pos.rowmax();
  dvector tmpvec(min, max);

  double* ptmpveci = tmpvec.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    *ptmpveci = ((pos(i)).va)[ii].xvalue();
    ((pos(i)).va)[ii].xvalue() = 0.0;

    ++ptmpveci;
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

  int min = tmp.indexmin();
  int max = tmp.indexmax();

  // dvar_vector constructor that doesn't do any initialization
  dvar_vector out(min, max, kg);

  double_and_int* pouti = out.va + min;
  double* ptmpi = tmp.get_v() + min;
  for (int i = min; i <= max; ++i)
  {
    pouti->x = *ptmpi;

    ++pouti;
    ++ptmpi;
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
  int nrl = m.rowmin();
  int nrh = m.rowmax();
  ivector ncl(nrl, nrh);
  ivector nch(nrl, nrh);

  int* pncli = ncl.get_v() + nrl;
  int* pnchi = nch.get_v() + nrl;
  const dvector* pmi = &m(nrl);
  for (int i = nrl; i <= nrh; ++i)
  {
    *pncli = pmi->indexmin();
    *pnchi = pmi->indexmax();

    ++pncli;
    ++pnchi;
    ++pmi;
  }

  // dvar_matrix constructor that doesn't do any initialization
  dvar_matrix out(nrl,nrh,ncl,nch);

  pmi = &m(nrl);
  pncli = ncl.get_v() + nrl;
  pnchi = nch.get_v() + nrl;
  dvar_vector* pouti = &out(nrl);
  for (int i = nrl; i <= nrh; ++i)
  {
    int jmin = *pncli;
    int jmax = *pnchi;
    double* pmij = pmi->get_v() + jmin;
    double_and_int* poutij = pouti->va + jmin;
    for (int j = jmin; j <= jmax; ++j)
    {
      poutij->x = *pmij;

      ++pmij;
      ++poutij;
    }
    ++pmi;
    ++pncli;
    ++pnchi;
    ++pouti;
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

  int* pncli = ncl.get_v() + nrl;
  int* pnchi = nch.get_v() + nrl;
  const dvector* pmi = &m(nrl);
  for (int i = nrl; i <= nrh; ++i)
  {
    *pncli = pmi->indexmin();
    *pnchi = pmi->indexmax();

    ++pncli;
    ++pnchi;
    ++pmi;
  }

  // dvar_matrix constructor that doesn't do any initialization
  dvar_matrix out(nrl,nrh,ncl,nch);

  pncli = ncl.get_v() + nrl;
  pnchi = nch.get_v() + nrl;
  pmi = &m(nrl);
  for (int i = nrl; i <= nrh; ++i)
  {
    int jmin = *pncli;
    int jmax = *pnchi;
    double* pmij = pmi->get_v() + jmin;
    dvar_vector* poutj = &out(jmin);
    for (int j = jmin; j <= jmax; ++j)
    {
      (poutj->va + i)->x = *pmij;

      ++poutj;
      ++pmij;
    }

    ++pmi;
    ++pncli;
    ++pnchi;
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

#ifndef OPT_LIB
  if (ii < m.colmin() || ii > m.colmax()
      || (v.indexmin() != m.rowmin())
      || (v.indexmax() != m.rowmax()))
  {
    cerr << "Error -- Index out of bounds in\n"
      "void nograd_assign(const dvar_matrix& m,const dvector& v, const int& ii)"
      << endl;
    ad_exit(1);
  }
#endif

  int min = v.indexmin();
  int max = v.indexmax();
  double* pvj = v.get_v() + min;
  const dvar_vector* pmj = &m(min);
  for (int j = min; j <= max; ++j)
  {
    (pmj->va + ii)->x = *pvj;

    ++pvj;
    ++pmj;
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
