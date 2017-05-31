/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

#include <adstring.hpp>

/**
Concatenate adstring u with unsigned char v.

\param u left hand side
\param v right hand side
*/
adstring operator+(const adstring& u, const unsigned char v)
{
  return (u + adstring(v));
}
/**
Concatenate adstring u with char v.

\param u left hand side
\param v right hand side
*/
adstring operator+(const adstring& u, const char v)
{
  return (u + adstring(v));
}
/**
Concatenate adstring u with unsigned char v.

\param u left hand side
\param v right hand side
*/
adstring operator+(const adstring& u, const unsigned char* v)
{
  return (u + adstring(v));
}
/**
Concatenate adstring u with char* v.

\param u left hand side
\param v right hand side
*/
adstring operator+(const adstring& u, const char* v)
{
  return (u + adstring(v));
}
/**
Concatenate unsigned char* v with adstring u.

\param u left hand side
\param v right hand side
*/
adstring operator+(const unsigned char* v, const adstring& u)
{
  return (adstring(v) + u);
}
/**
Concatenate char* v with adstring u.

\param u left hand side
\param v right hand side
*/
adstring operator+(const char* v, const adstring& u)
{
  adstring vv = v;
  return (vv+u);
}
/**
Concatenate unsigned char u with adstring v.

\param u left hand side
\param v right hand side
*/
adstring operator+(const unsigned char u, const adstring& v)
{
  adstring uu = u;
  return (uu + v);
}
