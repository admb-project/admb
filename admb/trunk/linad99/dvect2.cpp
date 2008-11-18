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
#include <fvar.hpp>

  dvector elem_prod(_CONST dvector& t1,_CONST dvector& t2)
  {
     if (t1.indexmin() != t2.indexmin() ||  t1.indexmax() != t2.indexmax())  
     {
       cerr << "Index bounds do not match in dvector elem_prod(_CONST dvector&,_CONST dvector&)\n";
       ad_exit(1);
     }
     dvector tmp(t1.indexmin(),t1.indexmax());

#ifndef USE_ASSEMBLER
     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp[i]=t1[i]*t2[i];
     }
#else
     int min=t1.indexmin();
     int n=t1.indexmax()-min+1;
     dp_vector_elem_prod(&(tmp(min)),&(t1(min)),&(t2(min)),n);
#endif
     
     return(tmp);
  }

  dvector elem_div(_CONST dvector& t1,_CONST dvector& t2)
  {
     if (t1.indexmin() != t2.indexmin() ||  t1.indexmax() != t2.indexmax())  
     {
       cerr << "Index bounds do not match in dvector elem_div(_CONST dvector&,_CONST dvector&)\n";
       ad_exit(1);
     }
     dvector tmp(t1.indexmin(),t1.indexmax());

#ifndef USE_ASSEMBLER
     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp[i]=t1[i]/t2[i];
     }
#else
     int min=t1.indexmin();
     int n=t1.indexmax()-min+1;
     dp_vector_elem_prod(&(tmp(min)),&(t1(min)),&(t2(min)),n);
#endif
     
     return(tmp);
  }

#undef HOME_VERSION
