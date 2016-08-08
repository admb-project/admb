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
  char tmp[301];
  tmp[0]='\0';
  GetCurrentDirectory(300,tmp);
  s=tmp;
#else
  char tmp[301];
  tmp[0]='\0';
  #ifdef __GNUC__
  char* ret = getcwd(tmp,300);
  assert(ret != 0);
  #else
  getcwd(tmp,300);
  #endif
  s=adstring(tmp);
#endif
}

/**
Make directory s.

\return 1 if successful, 0 otherwise.
*/
int ad_mkdir(const char* s)
{
#if defined(_WIN32)
  return CreateDirectory(s, NULL) != 0;
#else
  return mkdir(s,S_IREAD | S_IWRITE) == 0;
#endif
}
/**
Create a sub directory s.

\return 1 if successful, 0 otherwise.
*/
int make_sub_directory(const char* s)
{
  adstring currdir;
  adstring currdir1;
  ad_getcd(currdir);
#if defined(_WIN32)
  int ierr = SetCurrentDirectory(s);
  if (!ierr) // zero means failed
#else
  DIR* dirp = opendir(s);
  if (!dirp) // NULL means failed
#endif
  {
    ad_getcd(currdir);
    return ad_mkdir(s);
  }
  else
  {
    ad_getcd(currdir1);
    ad_chdir(currdir);
    ad_getcd(currdir1);
  }
#if defined(_WIN32)
  return ierr != 0;
#else
  return closedir(dirp) != -1;
#endif
}
