/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#include "cifstrem.h"

cifstream& cifstream::operator>>(const dvariable& z)
{
  *this >> value(z);
  return *this;
}

/*
cifstream& cifstream::operator>>(const prevariable& z)
{
  *this >> value(z);
  return *this;
}
*/


cifstream& cifstream::operator>>(const dvar_vector& z)
{
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  {
    *this >> z[i];
  }
  return *this;
}

cifstream& operator>>(cifstream& istr, const dvar_matrix& z)
{
  for (int i= z.rowmin(); i <= z.rowmax(); i++)
  {
    if (allocated(z[i]))
    {
      istr >> z[i];
    }
  }
  return istr;
}

cifstream& operator>>(cifstream& istr, const dvar3_array& z)
{
  for (int i= z.slicemin(); i <= z.slicemax(); i++)
  {
    istr >> z[i];
  }
  return istr;
}

cifstream& operator>>(cifstream& istr, const dvar4_array& z)
{
  for (int i= z.hslicemin(); i <= z.hslicemax(); i++)
  {
    istr >> z[i];
  }
  return istr;
}

cifstream& operator>>(cifstream& istr, const dvar5_array& z)
{
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  {
    istr >> z(i);
  }
  return istr;
}
