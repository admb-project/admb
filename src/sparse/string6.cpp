/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
//#include <adstring.hpp>
#include <fvar.hpp>
#include <string.h>
#include <stdlib.h>

  adstring operator + (_CONST adstring & u, _CONST unsigned char v)
    { return (u + adstring(  v)); }
  adstring operator + (_CONST adstring & u, _CONST signed char v)
    { return (u + adstring(v)); }
  adstring operator + (_CONST adstring & u, _CONST unsigned char * v)
    { return (u + adstring( (_CONST char *) v)); }
  adstring operator + (_CONST adstring & u, _CONST signed char * v)
    { return (u + adstring((_CONST char *) v)); }

  adstring operator + (_CONST unsigned char * v,_CONST adstring& u)
    { return (adstring( (_CONST char *) v)+u); }

  adstring operator + (_CONST char * v,_CONST adstring & u)
  {
      adstring vv=v;
      return (vv+u);
  }

  adstring operator + (_CONST unsigned char u,_CONST  adstring & v)
  {
    adstring uu=u;
    return (uu + v);
  }

