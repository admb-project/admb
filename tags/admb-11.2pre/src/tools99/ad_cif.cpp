/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#include "cifstrem.h"
/** \file ad_cif.cpp
Overloaded cifstream operators for autodif classes.
*/

//VECTOR_OPERATOR_DEFINE(dvector)
//VECTOR_OPERATOR_DEFINE(ivector)
//VECTOR_OPERATOR_DEFINE(lvector)

//MATRIX_OPERATOR_DEFINE(dmatrix)
//MATRIX_OPERATOR_DEFINE(imatrix)
//MATRIX_OPERATOR_DEFINE(lmatrix)

cifstream& cifstream::operator>>(const ivector& z)
{
  if (allocated(z))
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  {
    *this >> z[i];
  }
  return *this;
}

cifstream& operator>>(cifstream& istr, const prevariable& z)
{
  istr >> value(z);
  return istr;
}

cifstream& cifstream::operator>>(const lvector& z)
{
  if (allocated(z))
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  {
    *this >> z[i];
  }
  return *this;
}

cifstream& operator>>(cifstream& istr, const imatrix& z)
{
  if (allocated(z))
  for (int i= z.rowmin(); i <= z.rowmax(); i++)
  {
    istr >> z[i];
  }
  return istr;
}

cifstream& cifstream::operator>>(const dvector& z)
{
  if (allocated(z))
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  {
    *this >> z[i];
  }
  return *this;
}

cifstream& operator>>(cifstream& istr, const dmatrix& z)
{
  if (allocated(z))
  for (int i= z.rowmin(); i <= z.rowmax(); i++)
  {
    istr >> z[i];
  }
  return istr;
}

cifstream& operator>>(cifstream& istr, const d3_array& z)
{
  if (allocated(z))
  for (int i= z.slicemin(); i <= z.slicemax(); i++)
  {
    istr >> z[i];
  }
  return istr;
}

cifstream& operator>>(cifstream& istr, const d5_array& z)
{
  if (allocated(z))
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  {
    istr >> z[i];
  }
  return istr;
}

cifstream& operator>>(cifstream& istr, const i4_array& z)
{
  if (allocated(z))
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  {
    istr >> z[i];
  }
  return istr;
}

cifstream& operator>>(cifstream& istr, const i3_array& z)
{
  if (allocated(z))
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  {
    istr >> z[i];
  }
  return istr;
}

cifstream& operator>>(cifstream& istr, const d4_array& z)
{
  if (allocated(z))
  for (int i= z.hslicemin(); i <= z.hslicemax(); i++)
  {
    istr >> z[i];
  }
  return istr;
}
