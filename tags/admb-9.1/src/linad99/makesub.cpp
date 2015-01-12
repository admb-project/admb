/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>
#include <adstring.hpp>
//#include <fstream.h>
#include <stdlib.h>
#if (defined(__GNUDOS__) || defined(unix) || defined(__BORLANDC__))
#  include <dirent.h>
#endif
#if defined(__BORLANDC__) 
#  include <dir.h>
#endif
#if (defined(__GNUDOS__) || defined(unix))
#  include <sys/stat.h>
#endif
#if defined(_WIN32)
#  include <windows.h>
#else
#  include <unistd.h>
#endif

#if  defined(__GNU__) || defined(__linux__)
  #if (__GNUC__ >3)
     #include <iostream>
     using namespace std;
  #else   
    #include <iostream.h>
  #endif
#include <memory.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

int ad_chdir(const char * s)
{
#if defined(_WIN32) 
  return SetCurrentDirectory(s);
#elif (defined(__GNUDOS__) || defined(unix) || defined(__linux__) )
    return chdir(s);
#else
  xxx
  // not defined for this compiler
#endif
}

void ad_getcd(const adstring& _s)
{
  adstring& s=(adstring&) (_s);
#if defined(_WIN32) 
  char tmp[101];
  tmp[100]=0;
  GetCurrentDirectory(100,tmp);
  s=tmp;
#elif (defined(__GNUDOS__) || defined(unix) || defined(__linux__) )
  char tmp[101];
  tmp[100]=0;
  getcwd(tmp,100);
  s=adstring(tmp);
#else
  xxx
  // not defined for this compiler
#endif
}


int ad_mkdir(const char * s)
{
#if defined(_WIN32) 
  return CreateDirectory(s,NULL);
#elif (defined(__GNUDOS__) || defined(unix) || defined(__linux__) )
    return mkdir(s,S_IREAD | S_IWRITE);
#else
  xxxx
  cerr << "ad_mkdir not defined for this compiler" << endl;
#endif
}

int make_sub_directory(const char * s)
{
  adstring currdir;
  adstring currdir1;
  ad_getcd(currdir);
  const int len=100;
  char dirname[len+1];
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

