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

#if (defined(__ZTC__) && !defined(DOS386))
  void _far * _cdecl _farptr_norm(void _far *);
  void _far * _cdecl _farptr_fromlong(unsigned long);
  long _cdecl _farptr_tolong(void _far *);
#endif

#include <math.h>

/**
 * Description not yet available.
 * \param
 */
void jacobcalc(int nvar,BOR_CONST dmatrix& jac)
{
  gradient_structure::jacobcalc(nvar,jac);
}

/**
 * Description not yet available.
 * \param
 */
void gradient_structure::jacobcalc(int nvar,BOR_CONST dmatrix& _jac)
{
  ADUNCONST(dmatrix,jac)

  unsigned int i;
  long int lpos;
  if(!instances)
  {
    jac.initialize();
    return;
  }
  if (jac.rowmin()!=1)
  {
    cerr << "Error in jacobcalc jacobian must have minimum valid"
            " index of 1" << endl;
    jac.initialize();
    return;
  }
  int depvar_count=DEPVARS_INFO->depvar_count;
  if (jac.rowmax()<depvar_count)
  {
    cerr << "Error in jacobcalc jacobian must have maximumvalid"
            " index >= the number of dependent variables " << endl
          << " which is " << depvar_count << endl;
    jac.initialize();
    return;
  }

  int& _GRADFILE_PTR=GRAD_STACK1->_GRADFILE_PTR;
  // check to see if anything has been written into the file
  long int last_gpos=lseek(_GRADFILE_PTR,0L,SEEK_CUR);

  //save current contents of the buffer so we can get them later
  if (last_gpos)
  {
    GRAD_STACK1->write_grad_stack_buffer();
  }

  // check to see if anything has been written into the file
  long int last_cpos=lseek(fp->file_ptr,0L,SEEK_CUR);

  //save current contents of the buffer so we can get them later
  if (last_cpos)
  {
    fp->write_cmpdif_stack_buffer();
  }
  grad_stack_entry * grad_ptr;

  for (i=jac.rowmin();i<=(unsigned int)jac.rowmax();i++)
  {
    if (jac(i).indexmin() !=1)
    {
      cerr  << "jacobian matrix minimum column index must equal 1"
               " for all rows" << endl;
      return;
    }
    if (jac(i).indexmax() < nvar)
    {
      cerr  << "jacobian matrix column size is less than the number of"
               " independent variables" << endl;
      return;
    }
  }
  // save variable values if desired
  if (save_var_flag)
  {
    save_arrays();
    save_variables();
  }
  // now evalueate the jacobian
  for (int ijac=1;ijac<=depvar_count;ijac++)
  {
    dvector& g=(dvector&)(jac(ijac));
    //max_num_dependent_variables=ndv;
    if (depvar_count>DEPVARS_INFO->max_num_dependent_variables)
    {
      cout << "maximum number of depdendent variables of "
         << DEPVARS_INFO->max_num_dependent_variables << " exceeded "
         << endl
         << "use gradient_structure::set_NUM_DEPENDENT_VARIABLES(int i);"
         << endl << "to increase the number of dependent variables"
         << endl;
      ad_exit(1);
    }

    fp->offset=DEPVARS_INFO->cmpdif_buffer_position(ijac);
    fp->toffset=fp->offset;
    _GRADFILE_PTR=DEPVARS_INFO->grad_file_count(ijac);
    fp->file_ptr=DEPVARS_INFO->cmpdif_file_count(ijac);
    lpos=DEPVARS_INFO->grad_file_position(ijac);
    // position the cmpdif file correctly;
    if (last_cpos)
    {
      long int cmp_lpos=DEPVARS_INFO->cmpdif_file_position(ijac);
      lseek(fp->file_ptr,cmp_lpos,SEEK_SET);
      #ifndef __MSC__
        fp->read_cmpdif_stack_buffer(cmp_lpos);
      #else
        fp->read_cmpdif_stack_buffer((long int&)cmp_lpos);
      #endif
    }
    GRAD_STACK1->_GRADFILE_PTR = GRAD_STACK1->gradfile_handle();

    if (last_gpos)
    {
      // just use the end of the buffer
      GRAD_STACK1->set_gbuffer_pointers();

      // check to sere if buffer was written into the beginning of
      // the next file
      if ( (GRAD_STACK1->_GRADFILE_PTR == GRAD_STACK1->_GRADFILE_PTR1)
         && (lpos == GRAD_STACK1->end_pos1) && (lpos>0) )
      {
        // get the next file
        GRAD_STACK1->increment_current_gradfile_ptr();
        lpos=0;
      }
      // and position the file to the begginig of the buffer image
      lseek(_GRADFILE_PTR,lpos,SEEK_SET);
      // now fill the buffer with the appropriate stuff
      GRAD_STACK1->read_grad_stack_buffer(lpos);
      // now reposition the grad_buffer pointer
    }
    GRAD_STACK1->ptr=
         (grad_stack_entry *)DEPVARS_INFO->grad_buffer_position(ijac);

    if(GRAD_STACK1->ptr <= GRAD_STACK1->ptr_first)
    {
      #ifdef SAFE_ARRAYS
        cerr << "warning -- calling gradcalc when no calculations generating"
         << endl << "derivative information have occurred" << endl;
      #endif
      g.initialize();
      return;
    }    // current is one past the end so -- it

    gradient_structure::GRAD_STACK1->ptr--;

    for (i=0; i< GRAD_LIST->nlinks; i++)
    {
      * (double*) (GRAD_LIST->dlink_addresses[i]) = 0;
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

    unsigned long int max_last_offset
               = gradient_structure::ARR_LIST1->get_max_last_offset();

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

    * gradient_structure::GRAD_STACK1->ptr->dep_addr  = 1;
    zptr = gradient_structure::GRAD_STACK1->ptr->dep_addr;

    //double z;
    int break_flag=1;

    do
    {
      gradient_structure::GRAD_STACK1->ptr++;
      #ifdef FAST_ASSEMBLER
        gradloop();
      #else
        //int counter=0;
      while (gradient_structure::GRAD_STACK1->ptr-- >
    		gradient_structure::GRAD_STACK1->ptr_first)
      {
        grad_ptr = gradient_structure::GRAD_STACK1->ptr;
        {
          (* gradient_structure::GRAD_STACK1->ptr->func)();
        }
      }
      #endif

  // back up the file one buffer size and read forward
      lpos = lseek(gradient_structure::GRAD_STACK1->_GRADFILE_PTR,
        -((long int)(sizeof(grad_stack_entry)*gradient_structure::
        GRAD_STACK1->length)),SEEK_CUR);

       break_flag=gradient_structure::
                  GRAD_STACK1->read_grad_stack_buffer(lpos);

    }  while (break_flag); // do

    int mindx = g.indexmin();
    dvector & gg=(dvector&)(g);
    for (i=0; i<(unsigned int)nvar; i++)
    {
      gg[i+mindx] =  * gradient_structure::INDVAR_LIST->get_address(i);
      //g[i+mindx] =  * gradient_structure::INDVAR_LIST->get_address(i);
    }
    gradient_structure::GRAD_STACK1->ptr =
         gradient_structure::GRAD_STACK1->ptr_first;

  }// loop over dep vars
  DEPVARS_INFO->depvar_count=0;
  if (gradient_structure::save_var_flag)
  {
    gradient_structure::restore_arrays();
    gradient_structure::restore_variables();
  }
}
