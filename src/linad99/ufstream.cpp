/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

#define INSERT_IMPLEMENT(TYPE) \
uostream& uostream::operator<< (TYPE x) \
{ \
  write((char*)&x, sizeof(TYPE)); \
  return *this; \
}

#define EXTRACT_IMPLEMENT(TYPE) \
uistream& uistream::operator>> (const TYPE& x) \
{ \
  read((char*)&x, sizeof(TYPE)); \
  return *this; \
}

uostream::uostream(const char* name, int  m, int prot)
  :ofstream(name, std::ios::binary | std::ios::openmode(m))
{
}

/**
 * Description not yet available.
 * \param
 */
void uistream::open(const char* name, int m, int prot)
{
  ifstream::open(name, std::ios::binary | std::ios::openmode(m));
}

/**
 * Description not yet available.
 * \param
 */
void uostream::open(const char* name, int m, int prot)
{
  ofstream::open(name, std::ios::binary | std::ios::openmode(m));
}

/**
 * Description not yet available.
 * \param
 */
uistream::uistream(const char* name, int m, int prot)
  :ifstream(name, std::ios::binary | std::ios::openmode(m))
{
}

uistream& uistream::operator>>(int& x)
{
  read((char*)&x, sizeof(int));
  return *this;
}

#ifdef __ZTC__
uostream::uostream(const char* name, int  m, int prot)
:ios(&buffer), ofstream(name, m, prot) { }

uistream::uistream(const char* name, int m, int prot)
:ios(&buffer), ifstream(name, m| ios::nocreate , prot) { }
#endif

// implement insertion operators for various types in class uostream
#ifndef __SUN__
INSERT_IMPLEMENT(signed char)
#endif
INSERT_IMPLEMENT(unsigned char)
INSERT_IMPLEMENT(short)
INSERT_IMPLEMENT(int)
INSERT_IMPLEMENT(long)
INSERT_IMPLEMENT(unsigned short)
INSERT_IMPLEMENT(unsigned long)
INSERT_IMPLEMENT(float)
INSERT_IMPLEMENT(double)

#ifdef __TURBOC__
INSERT_IMPLEMENT(long double)
#endif

// implement extraction operators for various types in class uistream
#ifndef __SUN__
//#  if (__BORLANDC__  > 0x0520 || defined(__linux__))
EXTRACT_IMPLEMENT(signed char)
EXTRACT_IMPLEMENT(unsigned char)
EXTRACT_IMPLEMENT(char)
EXTRACT_IMPLEMENT(short)
EXTRACT_IMPLEMENT(int)
EXTRACT_IMPLEMENT(long)
EXTRACT_IMPLEMENT(unsigned short)
EXTRACT_IMPLEMENT(unsigned long)
EXTRACT_IMPLEMENT(float)
EXTRACT_IMPLEMENT(double)
 // #  else
 // EXTRACT_IMPLEMENT(const signed char)
 // EXTRACT_IMPLEMENT(const unsigned char)
 // EXTRACT_IMPLEMENT(const char)
 // EXTRACT_IMPLEMENT(const short)
 // EXTRACT_IMPLEMENT(const int)
 // EXTRACT_IMPLEMENT(const long)
 // EXTRACT_IMPLEMENT(const unsigned short)
 // EXTRACT_IMPLEMENT(const unsigned long)
 // EXTRACT_IMPLEMENT(const float)
 // EXTRACT_IMPLEMENT(const double)
 // #  endif
#endif

#ifdef __TURBOC__
#  if (__BORLANDC__  > 0x0520)
EXTRACT_IMPLEMENT(long double)
#  else
EXTRACT_IMPLEMENT(const long double)
#endif
#endif

