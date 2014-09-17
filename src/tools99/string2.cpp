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
#endif

adstring::adstring(int lb, int ub) : clist()
{
  if (lb != 1)
  {
    cerr << " Error in adstring::adstring(int lb,int ub) : clist()\n"
    " At present minimum index for adstring must equal 1\n";
    exit(1);
  }
  unsigned int sz = ub;
  allocate(sz);
  for (unsigned int i = 1; i <= sz; i++)
  {
    s[i] = '\0'; //' ';
  }
  s[sz + 1] = '\0';
}

adstring::adstring(const char ub) : clist()
{
  unsigned int sz = 1;
  allocate(sz);

#ifndef OPT_LIB
  assert(ub >= 0);
#endif

  s[1] = (unsigned char)ub;
  s[2] = '\0';
}

adstring::adstring(const adstring & v) : clist(v)
{
  shape = v.shape;
  s = v.s;
}

adstring operator+(const adstring& u, const adstring& v)
{
  int us = u.size ();
  int vs = v.size ();
  adstring tmp(1, us + vs);
  int i;
  for (i = 1; i <= us; i++)
  {
    tmp(i) = u(i);
  }
  for (i = 1; i <= vs; i++)
  {
    tmp(i + us) = v(i);
  }
  return (tmp);
}

adstring itoa(int n,int r)
{
  char buf[50];
  int ii=0;
  do
  {
    buf[ii++]=n%r;
  } while (n/=r);

  adstring s(1,ii);
  for (int i=0;i<ii;i++)
  {
    s[ii-i]=buf[i]+48;
  }
  return s;
}
