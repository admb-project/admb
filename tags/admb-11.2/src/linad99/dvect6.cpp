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
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
#endif

#include <math.h>

void shape_check(const dvector& v1, const dvector& v2,
  const char *function_name);

/**
 * Description not yet available.
 * \param
 */
dvector sin(const dvector& v1)// ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=sin(v1.elem(i));             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector cos(const dvector& v1)// ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=cos(v1.elem(i));             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector tan(const dvector& v1)// ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=tan(v1.elem(i));             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector sinh(const dvector& v1)// ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=sinh(v1.elem(i));             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector cosh(const dvector& v1)// ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=cosh(v1.elem(i));             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector tanh(const dvector& v1)// ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=tanh(v1.elem(i));             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector pow(const dvector& v1, const double x)// ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=pow(v1.elem(i),x);             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector pow(const dvector& v1, int x)// ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=pow(v1.elem(i),x);             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector pow(const dvector& v1, const dvector& v2)// ***
 {
   shape_check(v1,v2,"dvector pow(const dvector& v1,constdvector& v2)");

   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=pow(v1.elem(i),v2.elem(i));             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector pow(const double x, const dvector& v2)// ***
 {
   dvector tmp(v2.indexmin(),v2.indexmax());
   for (int i=v2.indexmin();i<=v2.indexmax();i++)
   {
     tmp.elem(i)=pow(x,v2.elem(i));             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector asin(const dvector& v1)// ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=asin(v1.elem(i));             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector acos(const dvector& v1)// ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=acos(v1.elem(i));             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector atan(const dvector& v1)// ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=atan(v1.elem(i));             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector log10(const dvector& v1)// ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=log10(v1.elem(i));             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector sqrt(const dvector& v1)// ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=sqrt(v1.elem(i));             // ***
   }
   return(tmp);
 }

/**
 * Description not yet available.
 * \param
 */
dvector sqr(const dvector& v1)// ***
 {
   dvector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
     tmp.elem(i)=sqrt(v1.elem(i));             // ***
   }
   return(tmp);
 }
