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
#include <fvar.hpp>
#include <adstring.hpp>
//#include <fstream.h>
#include <stdlib.h>
#if !defined(_MSC_VER)
  #include <dirent.h>
  #include <sys/stat.h>
#endif
#if defined(__BORLANDC__)
#  include <dir.h>
#endif
#if defined(_WIN32)
#  include <windows.h>
#else
#  include <unistd.h>
#endif

#if !defined(_MSC_VER)
#include <iostream>
using namespace std;
#include <memory.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#include <cassert>

/**
 * Description not yet available.
 * \param
 */
int ad_chdir(const char * s)
{
#if defined(_WIN32)
  return SetCurrentDirectory(s);
#else
  return chdir(s);
#endif
}

/**
 * Description not yet available.
 * \param
 */
void ad_getcd(const adstring& _s)
{
  adstring& s=(adstring&) (_s);
#if defined(_WIN32)
  char tmp[101];
  tmp[0]='\0';
  GetCurrentDirectory(100,tmp);
  s=tmp;
#else
  char tmp[101];
  tmp[0]='\0';
  #ifndef __SUNPRO_CC
  char* ret = getcwd(tmp,100);
  assert(ret != 0);
  #else
  getcwd(tmp,100);
  #endif
  s=adstring(tmp);
#endif
}

/**
 * Description not yet available.
 * \param
 */
int ad_mkdir(const char * s)
{
#if defined(_WIN32)
  return CreateDirectory(s,NULL);
#else
  return mkdir(s,S_IREAD | S_IWRITE);
#endif
}

/**
 * Description not yet available.
 * \param
 */
int make_sub_directory(const char * s)
{
  adstring currdir;
  adstring currdir1;
  ad_getcd(currdir);
  //const int len=100;
  //char dirname[len+1];
#if defined(_WIN32)
  int ierr=SetCurrentDirectory(s);
#else
  DIR * ierr=opendir(s);
#endif
  if (!ierr) // NULL means failed
  {
    ad_getcd(currdir);
    return ad_mkdir(s);
  }
  else
  {
    ad_getcd(currdir1);
    ad_chdir(currdir);
    ad_getcd(currdir1);
    return 1;
  }
}

