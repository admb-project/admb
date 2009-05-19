#include <fvar.hpp>
#include <string.h>
#include <stdlib.h>
#include <safe_mem.h>

adstring adstring::operator()(int i, int j)
{
  if (i < 1 || i > (int) shape->size())
  {
    cerr << "First index out of bounds in adstring::operator () (int,int)\n"
    << "Index value was " << i << " The size of this adstring is "
    << shape->size() << "\n";
    exit(1);
  }
  if (j < 1 || j > (int) shape->size())
  {
    cerr << "Second index out of bounds in adstring::operator () (int,int)\n"
    << "Index value was " << j << " The size of this adstring is "
    << shape->size() << "\n";
    exit(1);
  }

  if (i > j)
  {
    cerr << "First index must be less than or equal to second index in"
    " adstring::operator () (int,int)\n"
    << "Index value was " << i << " The size of this adstring is "
    << shape->size() << "\n";
    exit(1);
  }
 
  adstring tmp(1, size_t(j - i + 1));
  for (int ii = i; ii <= j; ii++)
  {
    tmp(ii - i + 1) = (* this) (ii);
  }
  return (tmp);
}

#if defined (USE_CONST)
adstring adstring::operator()(int i, int j) _CONST
{
  if (i < 1 || i > (int) shape->size())
  {
    cerr << "First index out of bounds in adstring::operator () (int,int)\n"
    << "Index value was " << i << " The size of this adstring is "
    << shape->size() << "\n";
    exit(1);
  }
  if (j < 1 || j > (int) shape->size())
  {
    cerr << "Second index out of bounds in adstring::operator () (int,int)\n"
    << "Index value was " << j << " The size of this adstring is "
    << shape->size() << "\n";
    exit(1);
  }

  if (i > j)
  {
    cerr << "First index must be less than or equal to second index in"
    " adstring::operator () (int,int)\n"
    << "Index value was " << i << " The size of this adstring is "
    << shape->size() << "\n";
    exit(1);
  }
 
  adstring tmp(1, size_t(j - i + 1));
  for (int ii = i; ii <= j; ii++)
  {
    tmp(ii - i + 1) = (* this) (ii);
  }
  return (tmp);
}
#endif
 
adstring & adstring::operator = (_CONST adstring & t)
{
  if (s != t.s)
  {
    int sz = t.size ();
    shape->size() = t.size();
    mem_free(++s);
  #if (defined __ZTC__) || (defined __NDPX__)
    s =  (char*)mem_malloc(sz+1);
  #else
    s =  (unsigned char*)mem_malloc(sz+1);
  #endif
    s--;
    for (int i = 1; i <= t.size(); i++)
    {
      s[i] = t[i];
    }
    s[sz + 1] = '\0';
    adstring * tmp = (adstring *) this->next;
    while (tmp != this)
    {
      tmp->shape = shape;
      tmp->s = s;
      tmp = (adstring *) tmp->next;
    }
  }
  return (* this);
}

void adstring::realloc(const char * t)
{
  int sz = strlen(t);
  shape->size() = strlen(t);
  mem_free(++s);
  s =  (unsigned char*)mem_malloc(sz+1);
  strcpy((char*)(s),t);
  s--;
  adstring * tmp = (adstring *) this->next;
  while (tmp != this)
  {
    tmp->shape = shape;
    tmp->s = s;
    tmp = (adstring *) tmp->next;
  }
}

adstring::~adstring()
{
  if (next==this)
  {
    mem_free(shape);
    mem_free(++s);
  }
};
 
unsigned char & adstring::operator()(_CONST int i)
{
  if (i < 1 || i > (int) shape->size())
  {
    cerr << "Index out of bounds in adstring::operator () (const int)\n"
    << "Index value was " << i << " The size of this adstring is "
    << shape->size() << "\n";
    exit(1);
  }
  return ( ((unsigned char *)s)[i]);
}
 
#ifdef USE_CONST
_CONST unsigned char & adstring::operator()(_CONST int i) _CONST
{
  if (i < 1 || i > (int) shape->size())
  {
    cerr << "Index out of bounds in adstring::operator () (const int)\n"
    << "Index value was " << i << " The size of this adstring is "
    << shape->size() << "\n";
    exit(1);
  }
  return (s[i]);
}

_CONST unsigned char & adstring::operator[] (_CONST int i) _CONST 
{
  if (i < 1 || i > (int) shape->size())
  {
    cerr << "Index out of bounds in adstring::operator () (const int)\n"
    << "Index value was " << i << " The size of this adstring is "
    << shape->size() << "\n";
  }
  return (s[i]);
}
#endif
 
#ifdef USE_CONST
int adstring::operator == (_CONST adstring & v) _CONST
{
  int tmp = strcmp (* this, v);
  return (tmp == 0);
}
#endif
 
int adstring::operator == (_CONST adstring & v)
{
  int tmp = strcmp (* this, v);
  return (tmp == 0);
}

int adstring::operator != (_CONST adstring & v)
{
  int tmp = strcmp (* this, v);
  return (tmp != 0);
}


adstring & adstring::operator += (_CONST adstring & v)
{
  int us = size ();
  int vs = v.size ();
  int bs = buff_size();
  if (bs > us + vs)
  {
    for (int i = 1; i <= vs; i++)
    {
      s[i + us] = v(i);
    }
  }
  else
  {
    adstring tmp(1, us + vs);
    int i;
    for (i = 1; i <= us; i++)
    {
      tmp(i) = s[i];
    }
    for (i = 1; i <= vs; i++)
    {
      tmp(i + us) = v(i);
    }
    * this = tmp;
  }
  return (* this);
}
 

unsigned char & adstring::operator[] (_CONST int i)
{
  if (i < 1 || i > (int) shape->size())
  {
    cerr << "Index out of bounds in adstring::operator () (const int)\n"
    << "Index value was " << i << " The size of this adstring is "
    << shape->size() << "\n";
  }
 // return (s[i]);
  return ( ((unsigned char *)s)[i]);
}
 
int length(_CONST adstring& t)
{
  return (int(t.size()));
}
