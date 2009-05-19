/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>
  dvector operator & (_CONST dvector& t1,_CONST dvector& t2)
  {
    int size =t1.size()+t2.size();
    dvector tmp(1,size);
    int min=t1.indexmin();
    int max=t1.indexmax();
    int ii=0;
    int i;
    for (i=min;i<=max;i++)
    {
      tmp(++ii)=t1(i);
    }
    min=t2.indexmin();
    max=t2.indexmax();
    for (i=min;i<=max;i++)
    {
      tmp(++ii)=t2(i);
    }
    return tmp;
  }


  dvar_vector operator & (_CONST dvar_vector& t1,_CONST dvar_vector& t2)
  {
    int size =t1.size()+t2.size();
    dvar_vector tmp(1,size);
    int min=t1.indexmin();
    int max=t1.indexmax();
    int ii=0;
    int i;
    for (i=min;i<=max;i++)
    {
      tmp(++ii)=t1(i);
    }
    min=t2.indexmin();
    max=t2.indexmax();
    for (i=min;i<=max;i++)
    {
      tmp(++ii)=t2(i);
    }
    return tmp;
  }
