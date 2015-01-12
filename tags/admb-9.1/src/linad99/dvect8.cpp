/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"

 dvector::dvector(_CONST ivector& u)
 {
   allocate(u.indexmin(),u.indexmax());
   for ( int i=indexmin(); i<=indexmax(); i++)
   {
     elem(i)=u.elem(i);
   }
 }    

 dvector::dvector(_CONST lvector& u)
 {
   allocate(u.indexmin(),u.indexmax());
   for ( int i=indexmin(); i<=indexmax(); i++)
   {
     elem(i)=u.elem(i);
   }
 }

 dvector dvector::operator ()(_CONST ivector& u)
 {
   dvector tmp(u.indexmin(),u.indexmax());

   for ( int i=u.indexmin(); i<=u.indexmax(); i++)
   {
     tmp(i)=(*this)(u(i));
   }
   return tmp;
 }


 dvector dvector::operator ()(_CONST lvector& u)
 {
   dvector tmp(u.indexmin(),u.indexmax());

   for ( int i=u.indexmin(); i<=u.indexmax(); i++)
   {
     tmp(i)=(*this)(u(i));
   }
   return tmp;
 }
