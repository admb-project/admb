/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Member function for class adstring.
*/
#include <fvar.hpp>
#include <string.h>
#include <stdlib.h>

#ifndef OPT_LIB
  #include <cassert>
#endif

adstring::adstring(const size_t lb, const size_t ub) : clist()
{
  if (lb != 1)
  {
    cerr << " Error in adstring::adstring(int lb,int ub) : clist()\n"
    " At present minimum index for adstring must equal 1\n";
    ad_exit(1);
  }
  size_t sz = ub;
  allocate(sz);
  for (size_t i = 1; i <= sz; i++)
  {
    s[i] = '\0'; //' ';
  }
  s[sz + 1] = '\0';
}
adstring::adstring(const int sz) : clist()
{
  if (sz < 1)
  {
    cerr << " Error in adstring::adstring(const size_t size) : clist()\n"
    " At present size must be greater than zero.\n";
    ad_exit(1);
  }
  size_t size = sz > 0 ? (size_t)sz : 0;
  allocate(size);
  for (size_t i = 1; i <= size; i++)
  {
    s[i] = '\0'; //' ';
  }
  s[size + 1] = '\0';
}

adstring::adstring(const char ub) : clist()
{
  size_t sz = 1;
  allocate(sz);

  s[1] = (unsigned char)ub;
  s[2] = '\0';
}

adstring::adstring(const unsigned char ub) : clist()
{
  size_t sz = 1;
  allocate(sz);

  s[1] = ub;
  s[2] = '\0';
}

adstring::adstring(const adstring & v) : clist(v)
{
  shape = v.shape;
  s = v.s;
}

adstring operator+(const adstring& u, const adstring& v)
{
  size_t us = u.size();
  size_t vs = v.size();
  adstring tmp(1, us + vs);
  for (size_t i = 1; i <= us; i++)
  {
    tmp(i) = u(i);
  }
  for (size_t i = 1; i <= vs; i++)
  {
    tmp(i + us) = v(i);
  }
  return tmp;
}

adstring itoa(int n, int r)
{
#ifndef OPT_LIB
  assert(r != 0);
  assert(r != 1);
#endif

  bool sign = n < 0 ? true : false;
  if (sign) n *= -1;
  unsigned char buf[50];
  memset(&buf[0], ' ', 50);
  size_t ii=0;
  do
  {
    int nr = n % r;
    if (nr < 0) nr *= -1;
    buf[ii++] = (unsigned char)nr;
  } while (n /= r);
  if (sign)
  {
    ii++;
  }
  adstring s(1, ii);
  for (size_t i=0;i<ii;i++)
  {
    s[ii-i]=(unsigned char)(buf[i]+48);
  }
  if (sign)
  {
    s(1) = '-';
  }
  return s;
}
