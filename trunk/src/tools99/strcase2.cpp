/*
 * $Id$
 *
 * Author: John Sibert
 * Copyright (c) 2010-2012 ADMB Foundation
 */
#include "adstring.hpp"

void adstring_array::to_lower(void)
{
  int i1 = indexmin();
  int i2 = indexmax();
  for (int i=i1; i <= i2; i++)
  {
    (ptr[i])->to_lower();
    //(*this[i]).adstring::to_lower();
  }
}

void adstring_array::to_upper(void)
{
  int i1 = indexmin();
  int i2 = indexmax();
  for (int i=i1; i <= i2; i++)
  {
    (ptr[i])->to_upper();
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
