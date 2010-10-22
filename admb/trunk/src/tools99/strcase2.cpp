/*
 * $Id$
 *
 * Author: John Sibert
 * Copyright (c) 2010 ADMB Foundation
 */
#include "fvar.hpp"
#include "adstring.hpp"

void adstring_array::to_lower(void)
{
  int i1 = indexmin();
  int i2 = indexmax();
  for (int i=i1; i <= i2; i++)
  {
    (ptr[i])->adstring::to_lower(); 
    //(*this[i]).adstring::to_lower(); 
  }
}

void adstring_array::to_upper(void)
{
  int i1 = indexmin();
  int i2 = indexmax();
  for (int i=i1; i <= i2; i++)
  {
    (ptr[i])->adstring::to_upper(); 
  }
}

adstring_array to_lower(adstring_array& s)
{
  adstring_array t = s;
  t.to_lower();
  return(t);
}

adstring_array to_upper(adstring_array& s)
{
  adstring_array t = s;
  t.to_upper();
  return(t);
}
