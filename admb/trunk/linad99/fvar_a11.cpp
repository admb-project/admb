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

  dvariable max(_CONST dvar_vector& t1)
  {
     dvariable tmp;
     int mmin=t1.indexmin();
     int mmax=t1.indexmax();
     tmp=t1.elem(mmin);
     for (int i=mmin+1; i<=mmax; i++)
     {
       if (tmp<t1.elem(i)) tmp=t1.elem(i);
     }
     return(tmp);
  }

  dvariable min(_CONST dvar_vector& t1)
  {
     dvariable tmp;
     int mmin=t1.indexmin();
     int mmax=t1.indexmax();
     tmp=t1.elem(mmin);
     for (int i=mmin+1; i<=mmax; i++)
     {
       if (tmp>t1.elem(i)) tmp=t1.elem(i);
     }
     return(tmp);
  }

#undef HOME_VERSION
