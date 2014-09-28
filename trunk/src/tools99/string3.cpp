/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#include <string.h>
#include <stdlib.h>

adstring::adstring(const char* t): clist()
{
  size_t sz = 0;
  if (t)
  {
    sz = strlen(t);
  }
  allocate(sz);
  for (size_t i = 1; i <= sz; i++)
  {
    s[i] = t[i - 1];
  }
  s[sz + 1] = '\0';
}

adstring::adstring(void): clist()
{
  size_t sz = 0;
  allocate(sz);
  s[sz + 1] = '\0';
}

size_t adstring::pos(const adstring& substr) const
{
#if (defined __ZTC__) || (defined __NDPX__)
  char* ptr = strstr(*this, substr);
#else
  const char* ptr = strstr((const char*)(*this), (const char*)(substr));
#endif
  size_t i = 0;

  if (ptr != NULL)
  {
    while ( (ptr != (char*)(s+i)) && (i < size()) ) i++;
  }
  return i;
}

size_t pos(const adstring& substr, const adstring& s)
{
  return s.pos(substr);
}
