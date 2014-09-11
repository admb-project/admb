/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#include <string.h>
#include <stdlib.h>

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

adstring::adstring(const char* t): clist()
{
  unsigned int sz = 0;
  if (t)
  {
#ifdef OPT_LIB
    sz = (unsigned int)strlen(t);
#else
    size_t len = strlen(t);
    assert(len <= (size_t)UINT_MAX);
    sz = (unsigned int)len;
#endif
  }
  allocate(sz);
  for (unsigned int i = 1; i <= sz; i++)
  {
    s[i] = t[i - 1];
  }
  s[sz + 1] = '\0';
}

adstring::adstring(void): clist()
{
  unsigned int sz = 0;
  allocate(sz);
  s[sz + 1] = '\0';
}

int adstring::pos(const adstring& substr) const
{
#if (defined __ZTC__) || (defined __NDPX__)
  char* ptr = strstr(*this, substr);
#else
  const char* ptr = strstr((const char*)(*this), (const char*)(substr));
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
