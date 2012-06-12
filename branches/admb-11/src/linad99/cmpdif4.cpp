/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
void dvector::save_dvector_position(void) const
{
  // saves the size and address information for a dvar_vector
  const unsigned wsize=sizeof(dvector_position);
  dvector_position tmp(*this);
  //int num_rec;
  gradient_structure::get_fp()->fwrite(&tmp,wsize);
}

/**
 * Description not yet available.
 * \param
 */
ivector_position restore_ivector_position(void)
{
  // reads back the size and address information for a ivector
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  ivector_position tmp;
  //int ierr;
  gradient_structure::get_fp()->fread(&tmp,sizeof(ivector_position));
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_vector_position restore_dvar_vector_position(void)
{
  // reads back the size and address information for a dvar_vector
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  dvar_vector_position tmp;
  gradient_structure::get_fp()->fread(&tmp,sizeof(dvar_vector_position));
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvector_position restore_dvector_position(void)
{
  // reads back the size and address information for a dvar_vector
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  dvector_position tmp;
  gradient_structure::get_fp()->fread(&tmp,sizeof(dvector_position));
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void dvar_vector::save_dvar_vector_value(void) const
{
  //int ierr=save_dvar_vector_position();
  // saves the size, address, and value information for a dvar_vector
  //const unsigned wsize=sizeof(double);
  //int num_rec;
  int min=indexmin();
  int max=indexmax();
  for (int i=min;i<=max;i++)
  {
    //double tmp=value((*this)(i));
    //gradient_structure::get_fp()->fwrite(&tmp,wsize);
    gradient_structure::get_fp()->fwrite(this->elem_value(i));
  }
}

/**
 * Description not yet available.
 * \param
 */
void dvector::save_dvector_value(void) const
{
  // saves the size, address, and value information for a dvar_vector
  // int ierr=save_dvector_position();
  //int wsize=sizeof(double);
  //int num_rec;
  int min=indexmin();
  int max=indexmax();
  for (int i=min;i<=max;i++)
  {
    double tmp=(*this)(i);
    gradient_structure::get_fp()->fwrite(tmp);
  }
}

/**
 * Description not yet available.
 * \param
 */
void ivector::save_ivector_value(void) const
{
  // saves the size, address, and value information for a ivector
  // int ierr=save_ivector_position();
  const unsigned wsize=sizeof(int);
  int min=indexmin();
  int max=indexmax();
  for (int i=min;i<=max;i++)
  {
    int tmp=(*this)(i);
    gradient_structure::get_fp()->fwrite(&tmp,size_t(wsize));
  }
}

/**
 * Description not yet available.
 * \param
 */
dvector restore_dvector_value(const dvector_position& tmp)
{
  // restores the size, address, and value information for a dvar_vector
  // restores the size, address, and value information for a ivector
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  dvector temp_vec(tmp.indexmin(),tmp.indexmax());
  for (int i=tmp.indexmax();i>=tmp.indexmin();i--)
  {
    double ttmp;
    gradient_structure::get_fp()->fread(ttmp);
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
  // restores the size, address, and value information for a ivector
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  ivector temp_vec(tmp.indexmin(),tmp.indexmax());
  for (int i=tmp.indexmax();i>=tmp.indexmin();i--)
  {
    int tmp;
    gradient_structure::get_fp()->fread(&tmp,sizeof(int));
    temp_vec(i)=tmp;
  }
  return temp_vec;
  // Back up the stream again for the next function
}

/**
 * Description not yet available.
 * \param
 */
dvector restore_dvar_vector_value(const dvar_vector_position& tmp)
{
  // restores the size, address, and value information for a dvar_vector
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''

  dvector temp_vec(tmp.indexmin(),tmp.indexmax());
  for (int i=tmp.indexmax();i>=tmp.indexmin();i--)
  {
    double ttmp;
    //gradient_structure::get_fp()->fread(&ttmp,sizeof(double));
    gradient_structure::get_fp()->fread(ttmp);
    temp_vec(i)=ttmp;
  }
  return temp_vec;
}

/**
 * Description not yet available.
 * \param
 */
void dvar_matrix::save_dvar_matrix_value(void) const
{
  // saves the size, address, and value information for a dvar_matrix
  int min=rowmin();
  int max=rowmax();
  for (int i=min;i<=max;i++)
  {
    ((*this)(i).save_dvar_vector_value());
    ((*this)(i).save_dvar_vector_position());
  }
}
