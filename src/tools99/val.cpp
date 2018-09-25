/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#include <stdio.h>

void val(const adstring& s, int& v, int& code)
{
  int z;
  if ( (s.size() > 2) && (s(1,2) == adstring("0x") ))
    z = sscanf((const char*)s, "%i", &v);
  else
    z = sscanf((const char*)s, "%d", &v);

  if (z != 1)
    code = 1;
  else
    code = 0;
}

int val(const adstring& s)
{
  int v;
  int code;

  val(s, v, code);

  return v;
}
