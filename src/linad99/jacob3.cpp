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

#include <stdio.h>
#include <stdlib.h>

#ifdef __SUN__
  #include <iostream.h>
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

#if !defined(_MSC_VER)
  #include <iostream>
  using namespace std;
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

#if defined(__NDPX__ )
  extern "C" {
    int LSEEK(int, int, int);
    int read(int, char*, int);
  };
#endif

#include <math.h>

/**
 * Description not yet available.
 * \param
 */
void jacobcalc(int nvar, const uostream& ofs)
{
  gradient_structure::jacobcalc(nvar,ofs);
}
void gradient_structure::jacobcalc(int nvar, const uostream& ofs)
{
  gradient_structure::GRAD_STACK1->jacobcalc(nvar,ofs);
}

/**
 * Description not yet available.
 * \param
 */
void grad_stack::jacobcalc(int nvar, const uostream& ofs)
{
  dvector jac(1,nvar);
  OFF_T lpos;
  int depvar_count = DEPVARS_INFO->depvar_count;

  // check to see if anything has been written into the file
  OFF_T last_gpos=LSEEK(_GRADFILE_PTR,0L,SEEK_CUR);

  //save current contents of the buffer so we can get them later
  if (last_gpos)
  {
    write_grad_stack_buffer();
  }

  // check to see if anything has been written into the file
  OFF_T last_cpos=LSEEK(fp->file_ptr,0L,SEEK_CUR);

  //save current contents of the buffer so we can get them later
  if (last_cpos)
  {
    fp->write_cmpdif_stack_buffer();
  }

  // save variable values if desired
  if (gradient_structure::save_var_flag)
  {
    save_arrays();
    GRAD_LIST->save_variables();
  }
  // now evalueate the jacobian
  for (int ijac=1;ijac<=depvar_count;ijac++)
  {
    dvector& g=jac;
    //max_num_dependent_variables=ndv;
    if (depvar_count > DEPVARS_INFO->max_num_dependent_variables)
    {
      cout << "maximum number of depdendent variables of "
         << DEPVARS_INFO->max_num_dependent_variables << " exceeded "
         << endl
         << "use gradient_structure::set_NUM_DEPENDENT_VARIABLES(int i);"
         << endl << "to increase the number of dependent variables"
         << endl;
      ad_exit(1);
    }

    fp->offset = DEPVARS_INFO->cmpdif_buffer_position(ijac);
    fp->toffset = fp->offset;
    _GRADFILE_PTR = DEPVARS_INFO->grad_file_count(ijac);
    fp->file_ptr = DEPVARS_INFO->cmpdif_file_count(ijac);
    lpos = DEPVARS_INFO->grad_file_position(ijac);
    // position the cmpdif file correctly;
    if (last_cpos)
    {
      OFF_T cmp_lpos = DEPVARS_INFO->cmpdif_file_position(ijac);
      LSEEK(fp->file_ptr, cmp_lpos, SEEK_SET);
      fp->read_cmpdif_stack_buffer(cmp_lpos);
    }
    _GRADFILE_PTR = gradfile_handle();

    if (last_gpos)
    {
      // just use the end of the buffer
      set_gbuffer_pointers();

      // check to sere if buffer was written into the beginning of
      // the next file
      if ( (_GRADFILE_PTR == _GRADFILE_PTR1)
         && (lpos == end_pos1) && (lpos>0) )
      {
        // get the next file
        increment_current_gradfile_ptr();
        lpos=0;
      }
      // and position the file to the begginig of the buffer image
      LSEEK(_GRADFILE_PTR,lpos,SEEK_SET);
      // now fill the buffer with the appropriate stuff
      read_grad_stack_buffer(lpos);
      // now reposition the grad_buffer pointer
    }
    ptr = (grad_stack_entry*)DEPVARS_INFO->grad_buffer_position(ijac);

    if(ptr <= ptr_first)
    {
#ifdef DEBUG
        cerr << "warning -- calling gradcalc when no calculations generating"
         << endl << "derivative information have occurred" << endl;
#endif
      g.initialize();
      return;
    }    // current is one past the end so -- it

    ptr--;

    GRAD_LIST->initialize();

    double_and_int* tmp = (double_and_int*)ARR_LIST1->ARRAY_MEMBLOCK_BASE;

    unsigned long int max_last_offset = ARR_LIST1->get_max_last_offset();

    size_t size = sizeof(double_and_int);

    for (unsigned int i = 0; i < (max_last_offset/size); i++)
    {
      tmp->x = 0;
#if defined (__ZTC__)
      tmp = (double_and_int*)_farptr_norm((void*)(++tmp));
#else
      tmp++;
#endif
    }

    *ptr->dep_addr  = 1;
    //double* zptr = gradient_structure::GRAD_STACK1->ptr->dep_addr;

    int break_flag=1;
    do
    {
      ptr++;
      #ifdef FAST_ASSEMBLER
        gradloop();
      #else
        //int counter=0;
      while (ptr-- > ptr_first)
      {
        //grad_stack_entry* grad_ptr =
        //gradient_structure::GRAD_STACK1->ptr;
        {
          (*ptr->func)();
        }
      }
      #endif

      // \todo Need test
      // back up the file one buffer size and read forward
      OFF_T offset = (OFF_T)(sizeof(grad_stack_entry) * length);
      lpos = LSEEK(_GRADFILE_PTR, -offset, SEEK_CUR);

       break_flag = read_grad_stack_buffer(lpos);
    }  while (break_flag); // do

    int mindx = g.indexmin();
    for (int i=0; i < nvar; i++)
    {
      g[i+mindx] =  *INDVAR_LIST->get_address(i);
    }
    ptr = ptr_first;
    //ofs << setprecision(10) << g << endl;
    ofs << g ;
  }// loop over dep vars
  DEPVARS_INFO->depvar_count=0;
  if (gradient_structure::save_var_flag)
  {
    restore_arrays();
    GRAD_LIST->restore_variables();
  }
}
