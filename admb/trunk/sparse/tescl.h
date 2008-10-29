
#ifndef CLIST_H
#define CLIST_H
class clist
{
public :
  int length(const int & max = 1000);
protected :
  clist * next;
  virtual here()=0;
  clist() { next = here(); }
  clist(const clist & pt);
  clist * prev(void);
public:
  ~clist();
};


clist * clist::prev(void)
{
  clist * tmp = this->next;
  while (tmp->next != this) tmp = tmp->next;
  return (tmp);
}
 
int  clist::length(const int & max)
{
  int num = 1;
  clist * tmp = this;
  while (tmp->next != this)
  {
    tmp = tmp->next;
    if (++num > max)
    {
      return (-1);
    }
  }
  return (num);
}

clist::clist(const clist & t)
{
  clist& tmp=t.here(); 
  next = t.next;
  tmp.next = this;
}
 
 
clist::~clist()
{
  if (next == here())
  {
    next = 0;
  }
  else
  {
    prev()->next = next;
  }
}

class mmm : public clist
{
  virtual mmm * here(){return this;}
}


#include <adstring.hpp>
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
  for (int i = 1; i <= us; i++)
  {
    tmp(i) = u(i);
  }
  for (i = 1; i <= vs; i++)
  {
    tmp(i + us) = v(i);
  }
  return (tmp);
}

#endif
