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
#  include <io.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#ifdef __MSVC32__
  #define lseek _lseek
  #define  read _read
  #define write _write 
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

#if defined(__GNU__) || defined(UNIXKLUDGE)
  //#include <iostream.h>
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

#if (defined(__ZTC__) && !defined(DOS386))
  void _far * _cdecl _farptr_norm(void _far *);
  void _far * _cdecl _farptr_fromlong(unsigned long);
  long _cdecl _farptr_tolong(void _far *);
#endif

//void KLUDGEX(void * p);

void slave_gradcalc(void)
{
  if (gradient_structure::no_derivatives)
  {
    reset_gradient_stack();
  }
  else
  {
    gradient_structure::TOTAL_BYTES = 0;
    gradient_structure::PREVIOUS_TOTAL_BYTES=0;
    int i;
    my_off_t lpos;
  
     gradient_structure::GRAD_STACK1->_GRADFILE_PTR =
                gradient_structure::GRAD_STACK1->gradfile_handle();
  
    int& _GRADFILE_PTR=gradient_structure::GRAD_STACK1->_GRADFILE_PTR;
  
    lpos = lseek(_GRADFILE_PTR,0L,SEEK_CUR);
  
    if(gradient_structure::GRAD_STACK1->ptr
         <= gradient_structure::GRAD_STACK1->ptr_first)
    {
     /*
      #ifdef SAFE_ARRAYS
        cerr << "warning -- calling gradcalc when no calculations generating"
  	 << endl << "derivative information have occurred" << endl;
      #endif
     */
      return;
    }    // current is one past the end so -- it
  
    if (gradient_structure::save_var_flag)
    {
      gradient_structure::save_arrays();
      gradient_structure::save_variables();
    }
  
    gradient_structure::GRAD_STACK1->ptr--;
  
    for (i=0; i<gradient_structure::GRAD_LIST->nlinks; i++)
    {
      * (double*) (gradient_structure::GRAD_LIST->dlink_addresses[i]) = 0;
    }
  
    #if defined (__BORLANDC__) && !defined(DOS386)
      double_and_int huge * tmp;
    #else
      double_and_int * tmp;
    #endif
  
    #if defined (__BORLANDC__) && !defined(DOS386)
       tmp = (double_and_int huge *) gradient_structure::ARRAY_MEMBLOCK_BASE;
    #else
       tmp = (double_and_int *) gradient_structure::ARRAY_MEMBLOCK_BASE;
    #endif
  
    unsigned long int max_last_offset = gradient_structure::ARR_LIST1->get_max_last_offset();
  
    unsigned int size = sizeof(double_and_int );
  
    double * zptr;
  
    for (i=0 ; i< (max_last_offset/size) ; i++ )
    {
      tmp->x = 0;
      #if defined (__ZTC__)
        #if defined(DOS386)
        tmp++;
         #else
          tmp = (double_and_int  *) _farptr_norm( (void*) (++tmp)  );
         #endif
       #endif
       #if defined (__BORLANDC__)
          tmp++;
       #endif
       #if (!defined (__ZTC__) && !defined (__BORLANDC__))
         tmp++;
       #endif
    }
  
    //* gradient_structure::GRAD_STACK1->ptr->dep_addr  = 1;
    zptr = gradient_structure::GRAD_STACK1->ptr->dep_addr;
  
    double z;
    int break_flag=1;
    
    do
    {
      gradient_structure::GRAD_STACK1->ptr++;
      #ifdef FAST_ASSEMBLER
        gradloop();
      #else
        grad_stack_entry * grad_ptr_first=
          gradient_structure::GRAD_STACK1->ptr_first;
        while (gradient_structure::GRAD_STACK1->ptr-- >
    		grad_ptr_first)
        {
          //KLUDGEX(gradient_structure::GRAD_STACK1->ptr);
          (*(gradient_structure::GRAD_STACK1->ptr->func))();
        }
    
      #endif
    
      // back up the file one buffer size and read forward
      //KLUDGEX(gradient_structure::GRAD_STACK1->ptr);
      lpos = lseek(gradient_structure::GRAD_STACK1->_GRADFILE_PTR,
          -((long int)(sizeof(grad_stack_entry)*gradient_structure::
            GRAD_STACK1->length)),SEEK_CUR);
      //KLUDGEX(gradient_structure::GRAD_STACK1->ptr);
    
      break_flag=gradient_structure::GRAD_STACK1->read_grad_stack_buffer(lpos);
    
    }  while (break_flag); // do
  
    {
      my_off_t ttmp = 
        lseek(gradient_structure::GRAD_STACK1->_GRADFILE_PTR, 0,SEEK_CUR);
     #ifdef GRAD_DIAG
        cout << "Offset in file at end of gradcalc is " << ttmp
  				      << " bytes from the beginning\n";
     #endif
    }
  
  
    gradient_structure::GRAD_STACK1->ptr = gradient_structure::GRAD_STACK1->ptr_first;
  
    if (gradient_structure::save_var_flag)
    {
      gradient_structure::restore_arrays();
      gradient_structure::restore_variables();
    }
  }
}


