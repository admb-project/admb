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

#include <cassert>

/**
Concatenate adstring u with unsigned char v.
*/
adstring operator+(const adstring& u, const unsigned char v)
{
  return (u + adstring(v));
}
/**
Concatenate adstring u with char v.
*/
adstring operator+(const adstring& u, const char v)
{
  return (u + adstring(v));
}
adstring operator+(const adstring& u, const unsigned char* v)
{
  return (u + adstring(v));
}
adstring operator+(const adstring& u, const char* v)
{
  return (u + adstring(v));
}
adstring operator+(const unsigned char* v, const adstring& u)
{
  return (adstring(v) + u);
}
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
