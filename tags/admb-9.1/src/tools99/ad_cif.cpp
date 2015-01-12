/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>
#include "cifstrem.h"

//VECTOR_OPERATOR_DEFINE(dvector)
//VECTOR_OPERATOR_DEFINE(ivector)
//VECTOR_OPERATOR_DEFINE(lvector)

//MATRIX_OPERATOR_DEFINE(dmatrix)
//MATRIX_OPERATOR_DEFINE(imatrix)
//MATRIX_OPERATOR_DEFINE(lmatrix)

cifstream& cifstream::operator>>(BOR_CONST ivector& z)
{
  if (allocated(z))
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  {
    *this >> z[i];
  } 
  return *this;
}

cifstream& operator>>(cifstream& istr,BOR_CONST prevariable& z)
{
  istr >> value(z);
  return istr;
}

cifstream& cifstream::operator>>(BOR_CONST lvector& z)
{
  if (allocated(z))
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  {
    *this >> z[i];
  } 
  return *this;
}


cifstream& operator>>(cifstream& istr,BOR_CONST imatrix& z)
{ 
  if (allocated(z))
  for (int i= z.rowmin(); i <= z.rowmax(); i++)
  { 
    istr >> z[i];
  }
  return istr;
}

cifstream& cifstream::operator>>(BOR_CONST dvector& z)
{
  if (allocated(z))
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  {
    *this >> z[i];
  } 
  return *this;
}

cifstream& operator>>(cifstream& istr,BOR_CONST  dmatrix& z)
{ 
  if (allocated(z))
  for (int i= z.rowmin(); i <= z.rowmax(); i++)
  { 
    istr >> z[i];
  }
  return istr;
}

cifstream& operator>>(cifstream& istr,BOR_CONST  d3_array& z)
{ 
  if (allocated(z))
  for (int i= z.slicemin(); i <= z.slicemax(); i++)
  { 
    istr >> z[i];
  }
  return istr;
}

cifstream& operator>>(cifstream& istr,BOR_CONST  d5_array& z)
{ 
  if (allocated(z))
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  { 
    istr >> z[i];
  }
  return istr;
}

cifstream& operator>>(cifstream& istr,BOR_CONST  i4_array& z)
{ 
  if (allocated(z))
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  { 
    istr >> z[i];
  }
  return istr;
}

cifstream& operator>>(cifstream& istr,BOR_CONST  i3_array& z)
{ 
  if (allocated(z))
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  { 
    istr >> z[i];
  }
  return istr;
}

cifstream& operator>>(cifstream& istr,BOR_CONST  d4_array& z)
{ 
  if (allocated(z))
  for (int i= z.hslicemin(); i <= z.hslicemax(); i++)
  { 
    istr >> z[i];
  }
  return istr;
}



