/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
//#include <adstring.hpp>
#include <fvar.hpp>
#include <string.h>
#include <stdlib.h>

adstring operator+(const adstring& u, const unsigned char v)
    { return (u + adstring(  v)); }
adstring operator+(const adstring& u, const signed char v)
    { return (u + adstring(v)); }
adstring operator+(const adstring& u, const unsigned char* v)
    { return (u + adstring( (const char *) v)); }
adstring operator+(const adstring& u, const signed char* v)
    { return (u + adstring((const char *) v)); }

adstring operator+(const unsigned char* v, const adstring& u)
    { return (adstring( (const char *) v)+u); }

adstring operator+(const char* v, const adstring& u)
  {
      adstring vv=v;
      return (vv+u);
  }

adstring operator+(const unsigned char u, const adstring& v)
  {
    adstring uu=u;
    return (uu + v);
  }
