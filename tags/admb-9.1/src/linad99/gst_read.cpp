/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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
  #ifndef __MSVC32__
    #include <unistd.h>
  #endif
  #ifdef __MSVC32__
    #define lseek _lseek
    #define  read _read
    #define write _write 
    #define open _open
    #define close _close 
  #endif
#endif

#ifdef __GNU__
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

#if defined(__NDPX__ )
  extern "C" {
    int lseek(int, int, int);
    int read(int, char*, int);
  };
#endif

#include <math.h>

#     if defined(__GNU__)
  int  grad_stack::read_grad_stack_buffer(my_off_t& lpos)
#     else
  int  grad_stack::read_grad_stack_buffer(long int& lpos)
#     endif
  {
    // check to see if we are past the beginning of this file
    if (lpos < 0)
    {
      lpos = lseek(gradient_structure::
        GRAD_STACK1->_GRADFILE_PTR,0L,SEEK_SET);
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
         -((long int)(sizeof(grad_stack_entry)*length)),SEEK_CUR);
      if (lpos == -1L)
      {
        cerr << "Error positioning temporary gradient file "
           << gradient_structure::GRAD_STACK1->get_gradfile_name() << " after open.\n";
        ad_exit(1);
      }
    }
    #if !defined( __NDPX__) && !defined( __SUN__)
      unsigned int nread = read(_GRADFILE_PTR,ptr_first,
        ((long int)(sizeof(grad_stack_entry)*length)) );
    #else
      unsigned int nread = read(_GRADFILE_PTR,
        (char*)ptr_first,((long int)(sizeof(grad_stack_entry)*length)) );
    #endif
    ptr = ptr_first + length-1;

    if (nread == -1 )
    {
      perror("IO error trying to read temporary gradient file\n");
    }
    if (nread <((long int)(sizeof(grad_stack_entry)*length)) )
    {
      perror("End of file encountered trying to read temporary gradient file\n");
      cout << "Read " << nread << "bytes from temp. grad. file\n";
    }
    lpos = lseek(_GRADFILE_PTR,-((long int)(sizeof(grad_stack_entry)*length)),
                                                           SEEK_CUR);
    // no break condition
    return 1;
  }

