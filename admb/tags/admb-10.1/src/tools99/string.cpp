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

void adstring::allocate(int sz)
{
  shape = (adstring_shape*)mem_malloc(sizeof(adstring_shape));
  shape->sz = sz;
#if (defined __ZTC__) || (defined __NDPX__)
  s =  (char*)mem_malloc(sz+1);
#else
  s =  (unsigned char*)mem_malloc(sz+1);
#endif
  if (!s) {
    cerr << "Error allocating memory for adstring" << endl;
    exit(1);
  }
}

adstring::operator unsigned char * ()
{
  return (unsigned char*)s + 1;
}

adstring::operator char * ()
{
  return (char*)(s + 1);
}

#ifdef USE_CONST
adstring::operator _CONST unsigned char * () _CONST
{
  return (_CONST unsigned char*)s + 1;
}

adstring::operator _CONST char * () _CONST
{
  return (_CONST char*)(s + 1);
}
#endif

  unsigned int adstring::size(void) _CONST
  {
    if (!s) return 0;
    return (strlen((char*)(s+1)));
  }

  unsigned int adstring::buff_size(void)
  {
    return (shape->size());
  }

ostream & operator << (ostream & c, _CONST adstring & t)
{
  for (unsigned int i = 1; i <= t.size(); i++)
  {
  #if (defined __ZTC__) || (defined __NDPX__)
    c << (char)(t.s)[i];
  #else
    c << (t.s)[i];
  #endif
  }
  return (c);
}

adstring & adstring::operator = (_CONST char t)
{ 
  return (*this = adstring(t)); 
}
