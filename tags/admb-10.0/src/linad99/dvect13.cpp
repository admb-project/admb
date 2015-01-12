/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
dmatrix column_vector(_CONST dvector& v)
{
  int min=v.indexmin();
  int max=v.indexmax();
  dmatrix tmp(min,max,1,1);
  for (int i=min;i<=max;i++)
  {
    tmp.elem(i,1)=v.elem(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix row_vector(_CONST dvector& v)
{
  int min=v.indexmin();
  int max=v.indexmax();
  dmatrix tmp(1,1,min,max);
  for (int i=min;i<=max;i++)
  {
    tmp.elem(1,i)=v.elem(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix column_vector(_CONST dvar_vector& v)
{
  int min=v.indexmin();
  int max=v.indexmax();
  dvar_matrix tmp(min,max,1,1);
  for (int i=min;i<=max;i++)
  {
    tmp.elem(i,1)=v.elem(i);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
dvar_matrix row_vector(_CONST dvar_vector& v)
{
  int min=v.indexmin();
  int max=v.indexmax();
  dvar_matrix tmp(1,1,min,max);
  for (int i=min;i<=max;i++)
  {
    tmp.elem(1,i)=v.elem(i);
  }
  return tmp;
}
