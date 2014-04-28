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
#include <stdio.h>

/**
 * Description not yet available.
 * \param
 */
double sfabs(const double v1)
 {
   #define cutoff 0.001
   #define cutoff2 0.000001
   double a = 2./cutoff;
   double b = 1./cutoff2;

   double return_value;
   double tmp1 = v1;
   double tmp = ::fabs(tmp1);
   if (tmp > cutoff)
   {
        return_value=tmp;
   }
   else
   {
     double t2 = tmp * tmp;

     if (tmp1 >=0)
     {
       return_value=t2*(a-b*tmp1);
     }
     else
     {
       return_value=t2*(a+b*tmp1);
     }
   }
   return(return_value);
 }

/**
 * Description not yet available.
 * \param
 */
dvector sfabs(const dvector& t1)
  {
     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=sfabs(t1.elem(i));
     }
     return(tmp);
  }
