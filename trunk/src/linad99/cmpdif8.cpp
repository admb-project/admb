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
prevariable_position restore_prevariable_position(void)
{
  double_and_int * tmp;
  gradient_structure::get_fp()->fread(&tmp,sizeof(double_and_int *));
  return prevariable_position(tmp);
}

/**
 * Description not yet available.
 * \param
 */
void prevariable::save_prevariable_position(void) const
{
  double_and_int * tmp=get_v();
  int wsize=sizeof(double_and_int*);
  gradient_structure::get_fp()->fwrite(&tmp,size_t(wsize));
}

/**
 * Description not yet available.
 * \param
 */
void prevariable::save_prevariable_value(void) const
{
  //double_and_int * tmp=get_v();
  //const unsigned wsize=sizeof(double_and_int*);
  //gradient_structure::get_fp()->fwrite(&tmp,wsize);
  double x=value(*this);
  //const unsigned dsize=sizeof(double);
  gradient_structure::get_fp()->fwrite(x);
}

/**
 * Description not yet available.
 * \param
 */
void save_double_value(const double x)
{
  //const unsigned wsize=sizeof(double);
  gradient_structure::get_fp()->fwrite(x);
}

/**
 * Description not yet available.
 * \param
 */
void save_int_value( int x)
{
  //const unsigned wsize=sizeof(double);
  gradient_structure::get_fp()->fwrite(x);
}

/**
 * Description not yet available.
 * \param
 */
void save_pointer_value(void *ptr)
{
  gradient_structure::get_fp()->fwrite(ptr);
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
double restore_prevariable_derivative(void)
{
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  double_and_int * tmp;
  gradient_structure::get_fp()->fread(&tmp,sizeof(double_and_int *));
  double tmpout=tmp->x;
  tmp->x=0.0;
  return tmpout;
}

/**
 * Description not yet available.
 * \param
 */
double restore_prevariable_value(void)
{
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  double tmpout = 0;
  gradient_structure::get_fp()->fread(&tmpout,sizeof(double));
  return tmpout;
}

/**
 * Description not yet available.
 * \param
 */
double restore_double_value(void)
{
  double tmpout = 0;
  gradient_structure::get_fp()->fread(tmpout);
  return tmpout;
}

/**
 * Description not yet available.
 * \param
 */
int restore_int_value(void)
{
  int tmpout = 0;
  gradient_structure::get_fp()->fread(tmpout);
  return tmpout;
}

/**
 * Description not yet available.
 * \param
 */
void* restore_pointer_value(void)
{
  void* tmpout = NULL;
  gradient_structure::get_fp()->fread(tmpout);
  return tmpout;
}
