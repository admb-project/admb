/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */

#define HOME_VERSION
#include <fvar.hpp>
  int sum(_CONST ivector&v)
  {
    int tmp=0;
    for (int i=v.indexmin(); i<=v.indexmax(); i++)
    {
      tmp+=v.elem(i);
    }
    return tmp;
  }

 ivector pow(const ivector& v1, int x)  
 {
   ivector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
#if (__MSVC32__>=8)
     tmp.elem(i)=pow(double(v1.elem(i)),x);           
#else
     tmp.elem(i)=pow(v1.elem(i),x);           
#endif
   }
   return(tmp);
 }

 ivector pow(int x,const ivector& v1)  
 {
   ivector tmp(v1.indexmin(),v1.indexmax());
   for (int i=v1.indexmin();i<=v1.indexmax();i++)
   {
#if (__MSVC32__>=8)
     tmp.elem(i)=pow(double(x),v1.elem(i));           
#else
     tmp.elem(i)=pow(x,v1.elem(i));           
#endif
   }
   return(tmp);
 }

#undef HOME_VERSION
