/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <fvar.hpp>
#include <string.h>
#include <stdlib.h>
#include <safe_mem.h>

adstring::adstring(const char * t) : clist()
{
  unsigned int sz = 0;
  if (t)
  {
    sz = strlen (t);
  }
//  shape = new adstring_shape(sz);
//  s = new char[size_t(sz + 1)];
  allocate(sz);
  s--;
  for (unsigned int i = 1; i <= sz; i++)
  {
    s[i] = t[i - 1];
  }
  s[sz + 1] = '\0';
}

//js
adstring::adstring(void) : clist()
{
  unsigned int sz = 0;
//  shape = new adstring_shape(sz);
//  s = new char[size_t(sz + 1)];
  allocate(sz);
  s--;
  s[sz + 1] = '\0';
}

int adstring::pos(const adstring& substr) const
{
#if (defined __ZTC__) || (defined __NDPX__)
  char* ptr = strstr(*this, substr);
#else
  const char * ptr = strstr((const char *)(*this), (const char *)(substr));
#endif
  unsigned int i = 0;

  if (ptr != NULL)
  {
    while ( (ptr != (char*)(s+i)) && (i < size()) ) i++;
  }
  return i;
}

int pos(const adstring& substr, const adstring& s)
{
  return(s.pos(substr));
}
