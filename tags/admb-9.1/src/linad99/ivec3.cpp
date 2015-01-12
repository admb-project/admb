/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"

 ivector ivector::operator ()(_CONST ivector& u)
 {
   ivector tmp(u.indexmin(),u.indexmax());

   for ( int i=u.indexmin(); i<=u.indexmax(); i++)
   {
     tmp(i)=(*this)(u(i));
   }
   return tmp;
 }


 lvector lvector::operator ()(_CONST lvector& u)
 {
   lvector tmp(u.indexmin(),u.indexmax());

   for ( int i=u.indexmin(); i<=u.indexmax(); i++)
   {
     tmp(i)=(*this)(u(i));
   }
   return tmp;
 }

