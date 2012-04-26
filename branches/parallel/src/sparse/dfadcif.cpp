/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#define HOME_VERSION
#include <fvar.hpp>
#include "cifstrem.h"



cifstream& cifstream::operator>>(BOR_CONST dvariable& z)
{
  *this >> value(z);
  return *this;
}

/*
cifstream& cifstream::operator>>(BOR_CONST prevariable& z)
{
  *this >> value(z);
  return *this;
}
*/


cifstream& cifstream::operator>>(BOR_CONST dvar_vector& z)
{
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  {
    *this >> z[i];
  } 
  return *this;
}

cifstream& operator>>(cifstream& istr,BOR_CONST dvar_matrix& z)
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

cifstream& operator>>(cifstream& istr,BOR_CONST dvar3_array& z)
{ 
  for (int i= z.slicemin(); i <= z.slicemax(); i++)
  { 
    istr >> z[i];
  }
  return istr;
}

cifstream& operator>>(cifstream& istr,BOR_CONST dvar4_array& z)
{ 
  for (int i= z.hslicemin(); i <= z.hslicemax(); i++)
  { 
    istr >> z[i];
  }
  return istr;
}

cifstream& operator>>(cifstream& istr,BOR_CONST dvar5_array& z)
{ 
  for (int i= z.indexmin(); i <= z.indexmax(); i++)
  { 
    istr >> z(i);
  }
  return istr;
}

