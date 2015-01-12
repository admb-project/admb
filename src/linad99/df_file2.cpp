/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


// file fvar.cpp
// constructors, destructors and misc functions involving class prevariable

#include "fvar.hpp"

#if defined (__WAT32__)
  #include <fcntl.h>
#endif

#ifdef __MSVC32__
  #define lseek _lseek
  #define  read _read
  #define write _write 
#endif

#if defined(__TURBOC__) && !defined(__linux__)
#pragma hdrstop
#include <iostream.h>
#include <iomanip.h>
#include <sys\stat.h>
#include <fcntl.h>
#endif

#ifdef __ZTC__
#include <iostream.hpp>
#define S_IREAD 0000400
#define S_IWRITE 0000200
#endif

#ifdef __NDPX__
#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2
  extern "C"
  {
    int lseek(int, int, int);
    int open(const char*, int);
    int creat(const char*, int);
    int close(int);
    int write(int, char*, int);
    int read(int, char*, int);
  };
#endif

#if  defined(__GNU__) || defined(__linux__)
  #if (__GNUC__ >3)
     #include <iostream>
     using namespace std;
  #else   
    #include <iostream.h>
  #endif
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#ifdef __SUN__
#include <iostream.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifndef __MSVC32__
#include <unistd.h>
#endif
#endif


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void DF_FILE::fread(BOR_CONST double& _x)
{
  double& x = (double&) _x;
  const unsigned num_bytes=sizeof(double);
  if (toffset < num_bytes)
  {
    my_off_t lpos = lseek(file_ptr,-((long int) buff_size),SEEK_CUR);
    //cout << "In fread filepos = " << lpos << endl;
    read_cmpdif_stack_buffer(lpos);
    offset -= num_bytes;
    toffset = offset;
  }
  else
  {
    toffset-=num_bytes; //decrement the temporary offset count
  }
  memcpy(&x, buff+toffset, sizeof(double));
  offset=toffset;
}

void DF_FILE::fread(BOR_CONST int& _x)
{
  int& x = (int&) _x;
  const unsigned num_bytes=sizeof(int);
  if (toffset < num_bytes)
  {
     my_off_t lpos = lseek(file_ptr,-((long int) buff_size),SEEK_CUR);
    //cout << "In fread filepos = " << lpos << endl;
    read_cmpdif_stack_buffer(lpos);
    offset -= num_bytes;
    toffset = offset;
  }
  else
  {
    toffset-=num_bytes; //decrement the temporary offset count
  }
  memcpy(&x, buff+toffset, sizeof(int));
  offset=toffset;
}

void DF_FILE::fwrite( CGNU_DOUBLE x)
{
  #ifdef NO_DERIVS
    if (gradient_structure::no_derivatives)
    {
      return;
    }
  #endif
  const unsigned num_bytes=sizeof(double);
  toffset+=num_bytes; //increment the temporary offset count
  if (toffset>buff_end)
  {
    write_cmpdif_stack_buffer();
    toffset=num_bytes;
    offset=0;
  }
  memcpy(buff+offset, &x, sizeof(double));
  offset=toffset;
}

void DF_FILE::fwrite(const int& x)
{
  #ifdef NO_DERIVS
    if (gradient_structure::no_derivatives)
    {
      return;
    }
  #endif
  const unsigned num_bytes=sizeof(int);
  toffset+=num_bytes; //increment the temporary offset count
  if (toffset>buff_end)
  {
    write_cmpdif_stack_buffer();
    toffset=num_bytes;
    offset=0;
  }
  memcpy(buff+offset, &x, sizeof(int));
  offset=toffset;
}

