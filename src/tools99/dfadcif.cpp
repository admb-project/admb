/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include <fvar.hpp>
#include "cifstrem.h"

/*
cifstream& cifstream::operator>>(const prevariable& z)
{
  *this >> value(z);
  return *this;
}
*/

/**
Reads input into var from comment formatted input file. 

\param var dvariable
*/
cifstream& cifstream::operator>>(const dvariable& var)
{
  *this >> value(var);
  return *this;
}
/**
Reads input into var from comment formatted input file. 

\param var dvar_vector
*/
cifstream& cifstream::operator>>(const dvar_vector& varvec)
{
  for (int i = varvec.indexmin(); i <= varvec.indexmax(); ++i)
  {
    *this >> varvec[i];
  }
  return *this;
}

/**
Reads input into var from comment formatted input file. 

\param var dvar_matrix
*/
cifstream& operator>>(cifstream& istr, const dvar_matrix& varmat)
{
  for (int i = varmat.rowmin(); i <= varmat.rowmax(); ++i)
  {
    if (allocated(varmat[i]))
    {
      istr >> varmat[i];
    }
  }
  return istr;
}
/**
Reads input into var from comment formatted input file. 

\param var dvar3_array
*/
cifstream& operator>>(cifstream& istr, const dvar3_array& vararr3)
{
  for (int i = vararr3.slicemin(); i <= vararr3.slicemax(); ++i)
  {
    istr >> vararr3[i];
  }
  return istr;
}
/**
Reads input into var from comment formatted input file. 

\param var dvar4_array
*/
cifstream& operator>>(cifstream& istr, const dvar4_array& vararr4)
{
  for (int i = vararr4.hslicemin(); i <= vararr4.hslicemax(); ++i)
  {
    istr >> vararr4[i];
  }
  return istr;
}
/**
Reads input into var from comment formatted input file. 

\param var dvar5_array
*/
cifstream& operator>>(cifstream& istr, const dvar5_array& vararr5)
{
  for (int i = vararr5.indexmin(); i <= vararr5.indexmax(); ++i)
  {
    istr >> vararr5(i);
  }
  return istr;
}
