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
#include <fcntl.h>

#ifdef _MSC_VER
  #define LSEEK _lseek
  #define  read _read
  #define write _write
#else
  #include <iostream>
  using namespace std;
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

#if defined(__TURBOC__)
#pragma hdrstop
#include <iostream.h>
#include <iomanip.h>
#include <sys\stat.h>
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
    int LSEEK(int, int, int);
    int open(const char*, int);
    int creat(const char*, int);
    int close(int);
    int write(int, char*, int);
    int read(int, char*, int);
  };
#endif

#ifdef __SUN__
#include <iostream.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Description not yet available.
 * \param
 */
void DF_FILE::fread(const double& _x)
{
  double& x = (double&)_x;
  const size_t num_bytes = sizeof(double);
  if (toffset < num_bytes)
  {
    OFF_T lpos = LSEEK(file_ptr,-((OFF_T)buff_size),SEEK_CUR);
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

/**
 * Description not yet available.
 * \param
 */
void DF_FILE::fread(void* &x)
{
  const size_t num_bytes = sizeof(void*);
  if (toffset < num_bytes)
  {
     OFF_T lpos = LSEEK(file_ptr,-((OFF_T)buff_size),SEEK_CUR);
    //cout << "In fread filepos = " << lpos << endl;
    read_cmpdif_stack_buffer(lpos);
    offset -= num_bytes;
    toffset = offset;
  }
  else
  {
    toffset-=num_bytes; //decrement the temporary offset count
  }
  memcpy(&x, buff+toffset, sizeof(void*));
  offset=toffset;
}

/**
 * Description not yet available.
 * \param
 */
void DF_FILE::fwrite(const double x)
{
#ifdef NO_DERIVS
  if (gradient_structure::no_derivatives)
  {
    return;
  }
#endif
  const size_t num_bytes = sizeof(double);
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
/**
Read _x from buffer.

\param x int to read.
*/
void DF_FILE::fread(const int& _x)
{
  int& x = (int&)_x;
  const size_t num_bytes = sizeof(int);
  if (toffset < num_bytes)
  {
    OFF_T lpos = LSEEK(file_ptr, -((OFF_T)buff_size), SEEK_CUR);
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
/**
Write _x to buffer.

\param x int to write.
*/
void DF_FILE::fwrite(const int& x)
{
  #ifdef NO_DERIVS
    if (gradient_structure::no_derivatives)
    {
      return;
    }
  #endif
  const size_t num_bytes = sizeof(int);
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

/**
 * Description not yet available.
 * \param
 */
void DF_FILE::fwrite(void * ptr)
{
  #ifdef NO_DERIVS
    if (gradient_structure::no_derivatives)
    {
      return;
    }
  #endif
  const size_t num_bytes = sizeof(void*);
  toffset+=num_bytes; //increment the temporary offset count
  if (toffset>buff_end)
  {
    write_cmpdif_stack_buffer();
    toffset=num_bytes;
    offset=0;
  }
  memcpy(buff+offset, &ptr, sizeof(void*));
  offset=toffset;
}
