#include <fvar.hpp>
#include <string.h>
#include <stdlib.h>
#include <safe_mem.h>

adstring::adstring(int lb, int ub) : clist()
{
  if (lb != 1)
  {
    cerr << " Error in adstring::adstring(int lb,int ub) : clist()\n"
    " At present minimum index for adstring must equal 1\n";
    exit(1);
  }
  unsigned int sz = ub;
//  shape = new adstring_shape(sz);
//  s = new char[size_t(sz + 1)];
  allocate(sz);
  s--;
  for (int i = 1; i <= sz; i++)
  {
    s[i] = '\0'; //' ';
  }
  s[sz + 1] = '\0';
}

/*
adstring::adstring(const unsigned char ub) : clist()
{
  unsigned int sz = 1;
//  shape = new adstring_shape(sz);
//  s = new char[size_t(sz + 1)];
  allocate(sz);
  s--;
  s[1] = ub;
  s[2] = '\0';
}
*/

adstring::adstring(_CONST char ub) : clist()
{
  unsigned int sz = 1;
//  shape = new adstring_shape(sz);
//  s = new char[size_t(sz + 1)];
  allocate(sz);
  s--;
  s[1] = ub;
  s[2] = '\0';
}

adstring::adstring(_CONST adstring & v) : clist(v)
{
  shape = v.shape;
  s = v.s;
}
 
 
adstring operator + (_CONST adstring & u, _CONST adstring & v) 
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



