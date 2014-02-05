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
#include <fvar.hpp>

/**
 * The tensor product of two dvar_matrixes
 * \param a first dvar_matrix
 * \param b second dvar_matrix
 * \return c a dvar_matrix of the tensor product.
 * 
 * Calcuates the tensor product of a and b.
 * \f$
 *  C = A \otimes B
 * \f$
 */
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
