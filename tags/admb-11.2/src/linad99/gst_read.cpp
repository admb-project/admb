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

#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#if defined (__WAT32__)
#endif

#include <stdio.h>
#include <stdlib.h>

#ifdef __SUN__
  #include <iostream.h>
  #include <fcntl.h>
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

#ifdef _MSC_VER
  #ifdef _M_X64
  typedef __int64 ssize_t;
  #else
  typedef int ssize_t;
  #endif
  #define lseek _lseek
  #define read _read
  #define write _write
  #define open _open
  #define close _close
#else
  #include <iostream>
  using namespace std;
  #include <fcntl.h>
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

#if defined(__MINGW64__) || (defined(_WIN64) && defined(_MSC_VER))
  #include <cassert>
  #include <climits>
#endif

#if defined(__NDPX__ )
  extern "C" {
    int lseek(int, int, int);
    int read(int, char*, int);
  };
#endif

#include <math.h>

/**
 * Description not yet available.
 * \param
 */
int grad_stack::read_grad_stack_buffer(off_t& lpos)
  {
    // check to see if we are past the beginning of this file
    if (lpos < 0)
    {
      lpos = lseek(gradient_structure::GRAD_STACK1->_GRADFILE_PTR,
        0L,SEEK_SET);
      // get the previous file
      if (gradient_structure::GRAD_STACK1->decrement_current_gradfile_ptr()
                        < 0)
      {
        // there is no more file to read ... but perhaps the beginning of
        // the buffer has not been used
        if (ptr_first==true_ptr_first)
        {
          // break condition
          return 0;
        }
        else
        {
          ptr_first=true_ptr_first;
          length=true_length;
          return 1;
        }
      }
      else
      {
        // get the end of file for the first file
        end_pos = end_pos1;
        // repostion the first file to end of pointer
        lseek(_GRADFILE_PTR,end_pos,SEEK_SET);
      }
      // now back up the file one buffer size
      lpos = lseek(_GRADFILE_PTR,
         -((off_t)(sizeof(grad_stack_entry)*length)),SEEK_CUR);
      if (lpos == -1L)
      {
        cerr << "Error positioning temporary gradient file "
             << gradient_structure::GRAD_STACK1->get_gradfile_name()
             << " after open.\n";
        ad_exit(1);
      }
    }
#if defined(__MINGW64__) || (defined(_WIN64) && defined(_MSC_VER))
    size_t size = sizeof(grad_stack_entry) * length;
    assert(size <= UINT_MAX);
    ssize_t nread = read(_GRADFILE_PTR, ptr_first, (unsigned int)size);
#else
    ssize_t nread = read(_GRADFILE_PTR, ptr_first,
      sizeof(grad_stack_entry)*length);
#endif
    ptr = ptr_first + length-1;

    if (nread == -1 )
    {
      perror("IO error trying to read temporary gradient file\n");
    }
    if (nread <((int)(sizeof(grad_stack_entry)*length)) )
    {
     perror("End of file encountered trying to read temporary gradient file\n");
      cout << "Read " << nread << "bytes from temp. grad. file\n";
    }
    lpos = lseek(_GRADFILE_PTR,-((off_t)(sizeof(grad_stack_entry)*length)),
                                                           SEEK_CUR);
    // no break condition
    return 1;
  }
