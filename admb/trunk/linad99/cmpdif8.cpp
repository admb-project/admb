/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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

void save_double_derivative( CGNU_DOUBLE x, BOR_CONST prevariable_position& _pos)
{
  prevariable_position& pos= (prevariable_position&) _pos; 
  // adds the derivative value in a double to a prevariables' guts
  pos.xval()+=x;
}

prevariable_position restore_prevariable_position(void)
{
  double_and_int * tmp;
  gradient_structure::get_fp()->fread(&tmp,sizeof(double_and_int *));
  return prevariable_position(tmp);
}

void prevariable::save_prevariable_position(void) _CONST
{
  double_and_int * tmp=get_v();
  int wsize=sizeof(double_and_int*);
  gradient_structure::get_fp()->fwrite(&tmp,size_t(wsize));
}

void prevariable::save_prevariable_value(void) _CONST
{
  //double_and_int * tmp=get_v();
  //const unsigned wsize=sizeof(double_and_int*);
  //gradient_structure::get_fp()->fwrite(&tmp,wsize);
  double x=value(*this);
  //const unsigned dsize=sizeof(double);
  gradient_structure::get_fp()->fwrite(x);
}

void save_double_value( CGNU_DOUBLE x)
{
  //const unsigned wsize=sizeof(double);
  gradient_structure::get_fp()->fwrite(x);
}

void save_int_value( int x)
{
  //const unsigned wsize=sizeof(double);
  gradient_structure::get_fp()->fwrite(x);
}

double restore_prevariable_derivative(BOR_CONST prevariable_position& _pos)
{
  prevariable_position& pos= (prevariable_position&) _pos; 
  double tmpout=pos.xval();
  pos.xval()=0.0;
  return tmpout;
}

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

double restore_prevariable_value(void)
{
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  double tmpout;
  gradient_structure::get_fp()->fread(&tmpout,sizeof(double));
  return tmpout;
}

double restore_double_value(void)
{
  double tmpout;
  gradient_structure::get_fp()->fread(tmpout);
  return tmpout;
}

int restore_int_value(void)
{
  int tmpout;
  gradient_structure::get_fp()->fread(tmpout);
  return tmpout;
}
