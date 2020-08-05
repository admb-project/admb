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
// file fvar_fn.cpp
// math.h functions involving prevariables
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
  #include <iomanip.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
  #include <iomanip.hpp>
#endif

#include <stdio.h>
#include <math.h>

//extern prevariable * FRETURN;
//extern int RETURN_INDEX;
//extern dlist * GRAD_LIST; //js

void shape_check(const dvar_vector& v1, const dvar_vector& v2,
  const char *function_name);
void shape_check(const dvector& v1, const dvar_vector& v2,
  const char *function_name);
void shape_check(const dvector& v1, const dvector& v2,
  const char *function_name);
void shape_check(const dvar_vector& v1, const dvector& v2,
  const char *function_name);

/**
 * Description not yet available.
 * \param
 */
 dvar_vector sinh(const dvar_vector& v1)// ***
 {
   RETURN_ARRAYS_INCREMENT();
   dvar_vector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=sinh(v1.elem(i));             // ***
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_vector cosh(const dvar_vector& v1)// ***
 {
   RETURN_ARRAYS_INCREMENT();
   dvar_vector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=cosh(v1.elem(i));             // ***
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_vector tanh(const dvar_vector& v1)// ***
 {
   RETURN_ARRAYS_INCREMENT();
   dvar_vector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=tanh(v1.elem(i));             // ***
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_vector pow(const dvar_vector& v1, const dvar_vector& v2)// ***
 {
   shape_check(v1,v2,
     "dvar_vector pow(const dvar_vector& v1,const dvar_vector& v2)");

   RETURN_ARRAYS_INCREMENT();
   dvar_vector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=pow(v1.elem(i),v2.elem(i));             // ***
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_vector pow(const prevariable& x, const dvar_vector& v2)// ***
 {
   RETURN_ARRAYS_INCREMENT();
   dvar_vector tmp(v2.indexmin(),v2.indexmax());
   for (int i=v2.indexmin();i<=v2.indexmax();i++)
   {
     tmp.elem(i)=pow(x,v2.elem(i));             // ***
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_vector asin(const dvar_vector& v1)// ***
 {
   RETURN_ARRAYS_INCREMENT();
   dvar_vector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=asin(v1.elem(i));             // ***
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_vector acos(const dvar_vector& v1)// ***
 {
   RETURN_ARRAYS_INCREMENT();
   dvar_vector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=acos(v1.elem(i));             // ***
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
 dvar_vector log10(const dvar_vector& v1)// ***
 {
   RETURN_ARRAYS_INCREMENT();
   dvar_vector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=log10(v1.elem(i));             // ***
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
 void shape_check(const dvar_vector& v1, const dvar_vector& v2,
   const char *function_name)
 {
   if (v1.indexmin() != v2.indexmin() || v1.indexmax() != v2.indexmax())
   {
     cerr << " Vector sizes do no match in" << function_name << "\n";
     ad_exit(1);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void shape_check(const dvector& v1, const dvar_vector& v2,
   const char *function_name)
 {
   if (v1.indexmin() != v2.indexmin() || v1.indexmax() != v2.indexmax())
   {
     cerr << " Vector sizes do no match in" << function_name << "\n";
     ad_exit(1);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 void shape_check(const dvar_vector& v1, const dvector& v2,
   const char *function_name)
 {
   if (v1.indexmin() != v2.indexmin() || v1.indexmax() != v2.indexmax())
   {
     cerr << " Vector sizes do no match in" << function_name << "\n";
     ad_exit(1);
   }
 }
