/**
  * $Id$
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */

#define HOME_VERSION
#include "fvar.hpp"

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


 dvector& dvector::operator+= ( CGNU_DOUBLE d)
 {
   for (int i=indexmin();i<=indexmax();i++)
   {
     elem(i) += d;
   }
   return(*this);
 }

 dvector& dvector::operator-= ( CGNU_DOUBLE d)
 {
   for (int i=indexmin();i<=indexmax();i++)
   {
     elem(i) -= d;
   }
   return(*this);
 }

 #undef HOME_VERSION
