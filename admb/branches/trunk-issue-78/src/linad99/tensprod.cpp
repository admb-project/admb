/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>
  dvar_matrix tensor_prod(const dvar_matrix& a,const dvar_matrix & b)
  {
    int lba=a.indexmin();
    int lbb=b.indexmin();
    int uba=a.indexmax();
    int ubb=b.indexmax();
    dvar_matrix ta=trans(a);
    dvar_matrix tb=trans(b);
    dvar_matrix c(lba,uba,lbb,ubb);
    for (int i=lba;i<=lbb;i++)
      for (int j=lbb;j<=ubb;j++)
        c(i,j)=ta(i)*tb(j);
    return c;
  }



