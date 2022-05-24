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
void dvector::save_dvector_position(DF_FILE* fp) const
{
  // saves the size and address information for a dvar_vector
  size_t wsize=sizeof(dvector_position);
  dvector_position tmp(*this);
  //int num_rec;
  fp->fwrite(&tmp,wsize);
}

/**
 * Description not yet available.
 * \param
 */
ivector_position restore_ivector_position()
{
  return gradient_structure::get_fp()->restore_ivector_position();
}
ivector_position DF_FILE::restore_ivector_position()
{
  // reads back the size and address information for a ivector
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  ivector_position tmp;
  //int ierr;
  fread(&tmp,sizeof(ivector_position));
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector_position restore_dvar_vector_position()
{
  return gradient_structure::get_fp()->restore_dvar_vector_position();
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
  return gradient_structure::get_fp()->restore_dvector_position();
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
  return gradient_structure::get_fp()->save_dvar_vector_value(*this);
}
void DF_FILE::save_dvar_vector_value(const dvar_vector& v)
{
  //int ierr=save_dvar_vector_position();
  //const unsigned wsize=sizeof(double);
  //int num_rec;
  int min=v.indexmin();
  int max=v.indexmax();
  for (int i=min;i<=max;++i)
  {
    //double tmp=value((*this)(i));
    //gradient_structure::get_fp()->fwrite(&tmp,wsize);
    fwrite(v.elem_value(i));
  }
}

/**
Saves the size, address, and value information for a dvector.
*/
void dvector::save_dvector_value(DF_FILE* fp) const
{
  // int ierr=save_dvector_position();
  //int wsize=sizeof(double);
  //int num_rec;
  int min=indexmin();
  int max=indexmax();
  for (int i=min;i<=max;i++)
  {
    double tmp=(*this)(i);
    fp->fwrite(tmp);
  }
}

/**
Saves the size, address, and value information for a ivector.
*/
void ivector::save_ivector_value(DF_FILE* fp) const
{
  // int ierr=save_ivector_position();
  constexpr size_t wsize=sizeof(int);
  int min=indexmin();
  int max=indexmax();
  for (int i=min;i<=max;i++)
  {
    int tmp=(*this)(i);
    fp->fwrite(&tmp,size_t(wsize));
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
  return gradient_structure::get_fp()->restore_dvector_value(tmp);
}
dvector DF_FILE::restore_dvector_value(const dvector_position& tmp)
{
  // restores the size, address, and value information for a dvar_vector
  dvector temp_vec(tmp.indexmin(),tmp.indexmax());
  for (int i=tmp.indexmax();i>=tmp.indexmin();i--)
  {
    double ttmp = 0.0;
    fread(ttmp);
    temp_vec(i)=ttmp;
  }
  return temp_vec;
}

/**
 * Description not yet available.
 * \param
 */
ivector restore_ivector_value(const ivector_position& tmp)
{
  return gradient_structure::get_fp()->restore_ivector_value(tmp);
}
ivector DF_FILE::restore_ivector_value(const ivector_position& tmp)
{
  // restores the size, address, and value information for a ivector
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  ivector temp_vec(tmp.indexmin(),tmp.indexmax());
  for (int i=tmp.indexmax();i>=tmp.indexmin();i--)
  {
    int n = 0;
    fread(&n, sizeof(int));
    temp_vec(i) = n;
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
  return gradient_structure::get_fp()->restore_dvar_vector_value(tmp);
}
dvector DF_FILE::restore_dvar_vector_value(const dvar_vector_position& tmp)
{
  dvector temp_vec(tmp.indexmin(),tmp.indexmax());
  for (int i=tmp.indexmax();i>=tmp.indexmin();i--)
  {
    double ttmp = 0.0;
    //gradient_structure::get_fp()->fread(&ttmp,sizeof(double));
    fread(ttmp);
    temp_vec(i)=ttmp;
  }
  return temp_vec;
}
/**
Saves the size, address, and value information for a dvar_matrix.
*/
void dvar_matrix::save_dvar_matrix_value(DF_FILE* fp) const
{
  int min=rowmin();
  int max=rowmax();
  for (int i=min;i<=max;i++)
  {
    fp->save_dvar_vector_value(elem(i));
    fp->save_dvar_vector_position(elem(i));
  }
}
