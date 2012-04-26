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
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
 dvector& dvector::operator+= (_CONST dvector& v1)
 {
   if (indexmin() != v1.indexmin() || indexmax() != v1.indexmax())
   {
     cerr << " Incompatible array bounds in dvector& operator += (_CONST dvector&)\n";
     ad_exit(21);
   }

   {    
     for (int i=indexmin();i<=indexmax();i++)
     {
       elem(i) += v1.elem(i);
     }
   }
   return(*this);
 }

/**
 * Description not yet available.
 * \param
 */
 dvector& dvector::operator-= (_CONST dvector& v1)
 {
   if (indexmin() != v1.indexmin() || indexmax() != v1.indexmax())
   {
     cerr << " Incompatible array bounds in dvector& operator -= (_CONST dvector&)\n";
     ad_exit(21);
   }

   {    
     for (int i=indexmin();i<=indexmax();i++)
     {
       elem(i) -= v1.elem(i);
     }
   }
   return(*this);
 }

/**
 * Description not yet available.
 * \param
 */
 dvector& dvector::operator+= ( CGNU_DOUBLE d)
 {
   for (int i=indexmin();i<=indexmax();i++)
   {
     elem(i) += d;
   }
   return(*this);
 }

/**
 * Description not yet available.
 * \param
 */
 dvector& dvector::operator-= ( CGNU_DOUBLE d)
 {
   for (int i=indexmin();i<=indexmax();i++)
   {
     elem(i) -= d;
   }
   return(*this);
 }
