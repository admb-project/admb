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
void dvector::save_dvector_position() const
{
  return gradient_structure::fp->save_dvector_position(*this);
}
void DF_FILE::save_dvector_position(const dvector& v)
{
  // saves the size and address information for a dvar_vector
  constexpr size_t wsize=sizeof(dvector_position);
  dvector_position tmp(v);
  //int num_rec;
  fwrite(&tmp, wsize);
}

/**
 * Description not yet available.
 * \param
 */
ivector_position restore_ivector_position()
{
  return gradient_structure::fp->restore_ivector_position();
}
ivector_position DF_FILE::restore_ivector_position()
{
  // reads back the size and address information for a ivector
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  constexpr size_t wsize = sizeof(dvector_position);
  ivector_position tmp;
  //int ierr;
  fread(&tmp, wsize);
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector_position restore_dvar_vector_position()
{
  return gradient_structure::fp->restore_dvar_vector_position();
}
dvar_vector_position DF_FILE::restore_dvar_vector_position()
{
  // reads back the size and address information for a dvar_vector
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  constexpr size_t wsize = sizeof(dvar_vector_position);
  dvar_vector_position tmp;
  fread(&tmp, wsize);
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector_position restore_dvector_position()
{
  return gradient_structure::fp->restore_dvector_position();
}
dvector_position DF_FILE::restore_dvector_position()
{
  // reads back the size and address information for a dvar_vector
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  constexpr size_t wsize = sizeof(dvector_position);
  dvector_position tmp;
  fread(&tmp, wsize);
  return tmp;
}

/**
Saves the size, address, and value information for a dvar_vector.
*/
void dvar_vector::save_dvar_vector_value() const
{
  return gradient_structure::fp->save_dvar_vector_value(*this);
}
void DF_FILE::save_dvar_vector_value(const dvar_vector& v)
{
  //int ierr=save_dvar_vector_position();
  //const unsigned wsize=sizeof(double);
  //int num_rec;
  int min=v.indexmin();
  int max=v.indexmax();
  const double_and_int* pvi = v.va + min;
  for (int i=min;i<=max;++i)
  {
    //double tmp=value((*this)(i));
    //gradient_structure::get_fp()->fwrite(&tmp,wsize);
    fwrite(pvi->x);
    ++pvi;
  }
}

/**
Saves the size, address, and value information for a dvector.
*/
void dvector::save_dvector_value() const
{
  return gradient_structure::fp->save_dvector_value(*this);
}
void DF_FILE::save_dvector_value(const dvector& v)
{
  int min = v.indexmin();
  int max = v.indexmax();
  fwrite(v.get_v() + min, sizeof(double) * (max - min + 1));
}

/**
Saves the size, address, and value information for a ivector.
*/
void ivector::save_ivector_value() const
{
  return gradient_structure::fp->save_ivector_value(*this);
}
void DF_FILE::save_ivector_value(const ivector& v)
{
  // int ierr=save_ivector_position();
  constexpr size_t wsize=sizeof(int);
  int min=v.indexmin();
  int max=v.indexmax();
  const int* pvi = v.get_v() + min;
  for (int i=min;i<=max;i++)
  {
    fwrite(pvi, wsize);
    ++pvi;
  }
}

/**
Restores the size, address, and value information for a dvector.
Back up the stream and read the number of bytes written in the
``write function'' corresponding to this ``read function''

\param tmp To get indexmin and indexmax
\return dvector 
*/
dvector restore_dvector_value(const dvector_position& tmp)
{
  return gradient_structure::fp->restore_dvector_value(tmp);
}
dvector DF_FILE::restore_dvector_value(const dvector_position& tmp)
{
  // restores the size, address, and value information for a dvar_vector
  int min = tmp.indexmin();
  int max = tmp.indexmax();
  dvector temp_vec(min, max);
  fread(temp_vec.get_v() + min, sizeof(double) * (max - min + 1));

  return temp_vec;
}

/**
 * Description not yet available.
 * \param
 */
ivector restore_ivector_value(const ivector_position& tmp)
{
  return gradient_structure::fp->restore_ivector_value(tmp);
}
ivector DF_FILE::restore_ivector_value(const ivector_position& tmp)
{
  // restores the size, address, and value information for a ivector
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  constexpr size_t sizeofint = sizeof(int);
  int min = tmp.indexmin();
  int max = tmp.indexmax();
  ivector temp_vec(min, max);
  int* ptemp_veci = temp_vec.get_v() + max;
  for (int i = max; i >= min; --i)
  {
    fread(ptemp_veci, sizeofint);
    --ptemp_veci;
  }
  return temp_vec;
  // Back up the stream again for the next function
}

/**
Restores the size, address, and value information for a dvar_vector.
Back up the stream and read the number of bytes written in the
``write function'' corresponding to this ``read function''
\param
*/
dvector restore_dvar_vector_value(const dvar_vector_position& tmp)
{
  return gradient_structure::fp->restore_dvar_vector_value(tmp);
}
dvector DF_FILE::restore_dvar_vector_value(const dvar_vector_position& tmp)
{
  int min = tmp.indexmin();
  int max = tmp.indexmax();
  dvector temp_vec(min, max);
  double* ptemp_veci = temp_vec.get_v() + max;
  for (int i = max; i >= min; --i)
  {
    //gradient_structure::get_fp()->fread(&ttmp,sizeof(double));
    fread(*ptemp_veci);
    --ptemp_veci;
  }
  return temp_vec;
}
/**
Saves the size, address, and value information for a dvar_matrix.
*/
void dvar_matrix::save_dvar_matrix_value() const
{
  gradient_structure::fp->save_dvar_matrix_value(*this);
}
void DF_FILE::save_dvar_matrix_value(const dvar_matrix& m)
{
  int min=m.rowmin();
  int max=m.rowmax();
  const dvar_vector* pmi = &m(min);
  for (int i=min;i<=max;++i)
  {
    save_dvar_vector_value(*pmi);
    save_dvar_vector_position(*pmi);
    ++pmi;
  }
}
