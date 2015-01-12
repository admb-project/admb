/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

void uistream::sss(void){}
void uostream::sss(void){}

#define INSERT_IMPLEMENT(TYPE) \
uostream& uostream::operator<< (TYPE x) \
{ \
  write((char*)&x, sizeof(TYPE)); \
  return *this; \
}

#define EXTRACT_IMPLEMENT(TYPE) \
uistream& uistream::operator>> (BOR_CONST TYPE& x) \
{ \
  read((char*)&x, sizeof(TYPE)); \
  return *this; \
}

#if defined(__GNUDOS__) || defined(__MSVC32__) || defined (__WAT32__)
#  define __BINFILE__ ios::binary
#elif defined(__TURBOC__) 
#  define __BINFILE__ ios::binary
#else
#  define __BINFILE__ 0
#endif

#if defined(__TURBOC__) || defined(__GNUDOS__) || defined(__MSVC32__) || defined (__WAT32__)
uostream::uostream(const char* name, int  m, int prot)
#  if defined(__GNU_NEWER__)
    :ofstream(name, std::ios::binary | std::_Ios_Openmode(m)) 
#  elif defined(__MSC_NEWER__) || (__BORLANDC__  > 0x0550) 
    :ofstream(name, std::ios::binary | m) 
#  else
    :ofstream(name, m | __BINFILE__, prot) 
#  endif
{ }

/**
 * Description not yet available.
 * \param
 */
void uistream::open(const char* name, int m, int prot)
{
#if defined(__TURBOC__) && (__BORLANDC__  <= 0x0520) 
  fstreambase::open(name, m, prot);
#endif
#ifdef __ZTC__
  fstream_common::open(name, m, prot);
#endif
#ifdef __NDPX__
  ifstream::open(name, m, prot);
#endif
#ifdef __SUN__
  ifstream::open(name, m, prot);
#endif
}

/**
 * Description not yet available.
 * \param
 */
void uostream::open(const char* name, int m, int prot)
{
#if defined (__TURBOC__) &&   (__BORLANDC__  <= 0x0520) 
  fstreambase::open(name, m, prot);
#endif
#if (__BORLANDC__  >= 0x0540 && __BORLANDC__  <= 0x0550) 
  ofstream::open(name, m, prot);
#else
#  if defined(linux)
#    if (__GNUC__  >= 3) 
       ofstream::open(name, std::_Ios_Openmode(m));
#    else
       ofstream::open(name, m);
#    endif     
#  else
     ofstream::open(name, m);
#  endif
#endif

#ifdef __MSVC32__
#  if (__MSVC32__>=8)
  ofstream::open(name, m);
#  else
  //fstreambase::open(name, m, prot);
  ofstream::open(name, m, prot);
#  endif
#endif
#ifdef __ZTC__
  fstream_common::open(name, m, prot);
#endif
#ifdef __NDPX__
  ofstream::open(name, m, prot);
#endif
#ifdef __SUN__
  ofstream::open(name, m, prot);
#endif
}

/**
 * Description not yet available.
 * \param
 */
uistream::uistream(const char* name, int m, int prot)
#  if (__BORLANDC__  > 0x0520  && __BORLANDC__  < 0x0560) 
  :ifstream(name, m | __BINFILE__ , prot) { }
#  else
#  if ( defined(__GNU_NEWER__) || defined(__MSC_NEWER__)  || __BORLANDC__  > 0x0550) 
       :ifstream(name, std::ios::binary ) { }
#    else
       :ifstream(name, m | ios::nocreate | __BINFILE__ , prot) { }
#    endif
#  endif
#endif

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
//#  if (__BORLANDC__  > 0x0520 || defined(linux)) 
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
 // EXTRACT_IMPLEMENT(BOR_CONST signed char)
 // EXTRACT_IMPLEMENT(BOR_CONST unsigned char)
 // EXTRACT_IMPLEMENT(BOR_CONST char)
 // EXTRACT_IMPLEMENT(BOR_CONST short)
 // EXTRACT_IMPLEMENT(BOR_CONST int)
 // EXTRACT_IMPLEMENT(BOR_CONST long)
 // EXTRACT_IMPLEMENT(BOR_CONST unsigned short)
 // EXTRACT_IMPLEMENT(BOR_CONST unsigned long)
 // EXTRACT_IMPLEMENT(BOR_CONST float)
 // EXTRACT_IMPLEMENT(BOR_CONST double)
 // #  endif
#endif

#ifdef __TURBOC__
#  if (__BORLANDC__  > 0x0520) 
EXTRACT_IMPLEMENT(long double)
#  else
EXTRACT_IMPLEMENT(BOR_CONST long double)
#endif
#endif

