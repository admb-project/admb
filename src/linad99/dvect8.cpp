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

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

/**
 * Description not yet available.
 * \param
 */
dvector::dvector(const ivector& u)
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
dvector::dvector(const lvector& u)
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
dvector dvector::operator ()(const ivector& u)
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
dvector dvector::operator ()(const lvector& u)
 {
   dvector tmp(u.indexmin(),u.indexmax());

   for ( int i=u.indexmin(); i<=u.indexmax(); i++)
   {
#ifdef OPT_LIB
     tmp(i)=(*this)((int)u(i));
#else
     const long ui = u(i);
     assert(ui <= INT_MAX);
     tmp(i)=(*this)((int)ui);
#endif
   }
   return tmp;
 }
