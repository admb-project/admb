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
void save_double_derivative(const double x, const prevariable_position& _pos)
{
  prevariable_position& pos= (prevariable_position&) _pos;
  // adds the derivative value in a double to a prevariables' guts
  pos.xval()+=x;
}

/**
 * Description not yet available.
 * \param
 */
prevariable_position restore_prevariable_position(DF_FILE* fp)
{
  constexpr size_t wsize = sizeof(double_and_int*);

  double_and_int* tmp;
  fp->fread(&tmp, wsize);
  return prevariable_position(tmp);
}

/**
 * Description not yet available.
 * \param
 */
void prevariable::save_prevariable_position(DF_FILE* fp) const
{
  constexpr size_t wsize = sizeof(double_and_int*);

  double_and_int* tmp = get_v();
  fp->fwrite(&tmp, wsize);
}

/**
 * Description not yet available.
 * \param
 */
void prevariable::save_prevariable_value(DF_FILE* fp) const
{
  //double_and_int * tmp=get_v();
  //const unsigned wsize=sizeof(double_and_int*);
  //gradient_structure::get_fp()->fwrite(&tmp,wsize);
  double x=value(*this);
  //const unsigned dsize=sizeof(double);
  fp->fwrite(x);
}

/**
 * Description not yet available.
 * \param
 */
void save_double_value(const double x)
{
  gradient_structure::get_fp()->save_double_value(x);
}
void DF_FILE::save_double_value(const double x)
{
  //const unsigned wsize=sizeof(double);
  fwrite(x);
}

/**
 * Description not yet available.
 * \param
 */
void save_int_value(int x)
{
  gradient_structure::get_fp()->save_int_value(x);
}
void DF_FILE::save_int_value(int x)
{
  //const unsigned wsize=sizeof(double);
  fwrite(x);
}

/**
 * Description not yet available.
 * \param
 */
void save_pointer_value(void *ptr)
{
  gradient_structure::get_fp()->save_pointer_value(ptr);
}
void DF_FILE::save_pointer_value(void *ptr)
{
  fwrite(ptr);
}

/**
 * Description not yet available.
 * \param
 */
double restore_prevariable_derivative(const prevariable_position& _pos)
{
  prevariable_position& pos= (prevariable_position&) _pos;
  double tmpout=pos.xval();
  pos.xval()=0.0;
  return tmpout;
}

/**
 * Description not yet available.
 * \param
 */
double restore_prevariable_derivative(DF_FILE* fp)
{
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  constexpr size_t wsize = sizeof(double_and_int*);

  double_and_int* tmp;
  fp->fread(&tmp, wsize);
  double tmpout=tmp->x;
  tmp->x=0.0;
  return tmpout;
}

/**
 * Description not yet available.
 * \param
 */
double restore_prevariable_value()
{
  return gradient_structure::get_fp()->restore_prevariable_value();
}
double DF_FILE::restore_prevariable_value()
{
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  constexpr size_t wsize = sizeof(double);
  double tmpout = 0;
  fread(&tmpout, wsize);
  return tmpout;
}

/**
 * Description not yet available.
 * \param
 */
double restore_double_value()
{
  return gradient_structure::get_fp()->restore_double_value();
}
double DF_FILE::restore_double_value()
{
  double tmpout = 0;
  fread(tmpout);
  return tmpout;
}

/**
 * Description not yet available.
 * \param
 */
int restore_int_value(void)
{
  return gradient_structure::get_fp()->restore_int_value();
}
int DF_FILE::restore_int_value()
{
  int tmpout = 0;
  fread(tmpout);
  return tmpout;
}

/**
 * Description not yet available.
 * \param
 */
void* restore_pointer_value()
{
  return gradient_structure::get_fp()->restore_pointer_value();
}
void* DF_FILE::restore_pointer_value()
{
  void* tmpout = NULL;
  fread(tmpout);
  return tmpout;
}
