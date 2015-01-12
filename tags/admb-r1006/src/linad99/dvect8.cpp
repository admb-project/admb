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
 dvector::dvector(_CONST ivector& u)
 {
   allocate(u.indexmin(),u.indexmax());
   for ( int i=indexmin(); i<=indexmax(); i++)
   {
     elem(i)=u.elem(i);
   }
 }    

/**
 * Description not yet available.
 * \param
 */
 dvector::dvector(_CONST lvector& u)
 {
   allocate(u.indexmin(),u.indexmax());
   for ( int i=indexmin(); i<=indexmax(); i++)
   {
     elem(i)=u.elem(i);
   }
 }

/**
 * Description not yet available.
 * \param
 */
 dvector dvector::operator ()(_CONST ivector& u)
 {
   dvector tmp(u.indexmin(),u.indexmax());

   for ( int i=u.indexmin(); i<=u.indexmax(); i++)
   {
     tmp(i)=(*this)(u(i));
   }
   return tmp;
 }

/**
 * Description not yet available.
 * \param
 */
 dvector dvector::operator ()(_CONST lvector& u)
 {
   dvector tmp(u.indexmin(),u.indexmax());

   for ( int i=u.indexmin(); i<=u.indexmax(); i++)
   {
     tmp(i)=(*this)(u(i));
   }
   return tmp;
 }
