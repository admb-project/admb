/*
 * $Id: sgradclc.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"
#if defined(USE_ADMPI)
  #include "admodel.h"
#endif

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

#if (defined(__ZTC__) && !defined(DOS386))
  void _far * _cdecl _farptr_norm(void _far *);
  void _far * _cdecl _farptr_fromlong(unsigned long);
  long _cdecl _farptr_tolong(void _far *);
#endif

//void KLUDGEX(void * p);

/**
 * Description not yet available.
 * \param
 */
void gradcalc(int nvar,BOR_CONST dvector& _g)
{
  if (nvar!=0)
  {
    if (nvar != gradient_structure::NVAR)
    {
      cerr << "nvar != gradient_structure::NVAR in gradcalc" << endl;
      cerr << "  nvar = " << nvar << endl;
      cerr << "  gradient_structure::NVAR = " << gradient_structure::NVAR 
           << endl;
      cerr << "  in " __FILE__ << endl;
      ad_exit(1);
    }
  }
  dvector& g= (dvector&) _g;
  gradient_structure::TOTAL_BYTES = 0;
  gradient_structure::PREVIOUS_TOTAL_BYTES=0;
  unsigned int i;
  long int lpos;
  if(!gradient_structure::instances)
  {
    g.initialize();
    return;
  }
  
  if (g.size() < nvar)
  {
    cerr  << "gradient vector size is less than the number of variables" << endl;
    ad_exit(1);
  }

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
    g.initialize();
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

    * gradient_structure::GRAD_STACK1->ptr->dep_addr  = 1;
    zptr = gradient_structure::GRAD_STACK1->ptr->dep_addr;

//double z;
int break_flag=1;
int icount=0;

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
      (*(gradient_structure::GRAD_STACK1->ptr->func))(); // sync ptr->ind_addr1?
      icount++;                                         // maybe below not need
      if (icount%1000==0)
      {
        //cout << "icount = " << icount << endl;
      }
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
   #ifdef GRAD_DIAG
  long int ttmp = 
   #endif
    lseek(gradient_structure::GRAD_STACK1->_GRADFILE_PTR, 0,SEEK_CUR);
   #ifdef GRAD_DIAG
      cout << "Offset in file at end of gradcalc is " << ttmp
				      << " bytes from the beginning\n";
   #endif
  }

#if defined(USE_ADMPI)
  if (ad_comm::mpi_manager)
  {
    if (ad_comm::mpi_manager->sync_gradient_flag)
    {
      dvector local_g(0,nvar);
      for (i=0; i < (unsigned int)nvar; i++)
      {
        local_g(i)=* gradient_structure::INDVAR_LIST->get_address(i);
      }

      if (ad_comm::mpi_manager->is_master())
      {
        // sync 
        for(int si=1;si<=ad_comm::mpi_manager->get_num_slaves();si++)
        {
          local_g+=ad_comm::mpi_manager->get_dvector_from_slave(si);
        }
        // send to slaves
        for(int si=1;si<=ad_comm::mpi_manager->get_num_slaves();si++)
        {
          ad_comm::mpi_manager->send_dvector_to_slave(local_g,si);
        }
      }
      else
      {
        // sync
        ad_comm::mpi_manager->send_dvector_to_master(local_g);
        // get from master
        local_g=ad_comm::mpi_manager->get_dvector_from_master();
      }

      for (i=0; i < (unsigned int)nvar; i++)
      {
        gradient_structure::INDVAR_LIST->put_value(i,local_g(i));
      }
    }
  }
#endif


  int mindx = g.indexmin();
  for (i=0; i < (unsigned int)nvar; i++)
  {
    g[i+mindx] =  * gradient_structure::INDVAR_LIST->get_address(i);
  }

  gradient_structure::GRAD_STACK1->ptr = gradient_structure::GRAD_STACK1->ptr_first;

  if (gradient_structure::save_var_flag)
  {
    gradient_structure::restore_arrays();
    gradient_structure::restore_variables();
  }
}

/**
 * Description not yet available.
 * \param
 */
void gradient_structure::save_arrays()
{
  void * temp_ptr;
  long bytes_needed=min(gradient_structure::ARR_LIST1->get_last_offset()+1,
    ARRAY_MEMBLOCK_SIZE);
  gradient_structure::save_var_file_flag=0;
  //#if DOS386==1
  #if defined(DOS386)
   if ( (temp_ptr = (void *) malloc(bytes_needed )) == 0)
  #else
#if !defined(__MSVC32__) && !defined (__WAT32__)
   if ( (temp_ptr = farmalloc(bytes_needed) ) == 0)
#else
   if ( (temp_ptr = malloc(bytes_needed) ) == 0)
#endif
  #define __USE_IOSTREAM__
  #endif
   {
     gradient_structure::save_var_file_flag=1;
     cerr << "insufficient memory to allocate space for ARRAY_MEMBLOCK"
	  << " save buffer " << endl;
   }
   if (gradient_structure::save_var_file_flag==0)
   {
     ARRAY_MEMBLOCK_SAVE = temp_ptr;
     #if defined(DOS386)
     //#if DOS386==1
       #ifndef USE_ASSEMBLER
         memcpy((char*)ARRAY_MEMBLOCK_SAVE,(char*)ARRAY_MEMBLOCK_BASE,
	   bytes_needed);
       #else
         dw_block_move((double*)ARRAY_MEMBLOCK_SAVE,
           (double*)ARRAY_MEMBLOCK_BASE,bytes_needed/8);
       #endif
     #else
     unsigned long int max_move=50000;
     unsigned long int left_to_move=bytes_needed;
     humungous_pointer dest = ARRAY_MEMBLOCK_SAVE;
     humungous_pointer src = ARRAY_MEMBLOCK_BASE;
     while(left_to_move > max_move)
     {
       memcpy((char*)dest,(char*)src,max_move);
       left_to_move-=max_move;
       src+=max_move;
       dest+=max_move;
     }
     memcpy((char*)dest,(char*)src,left_to_move);
    #endif
  }
  else
  {
     humungous_pointer src = ARRAY_MEMBLOCK_BASE;
     lseek(gradient_structure::GRAD_STACK1->_VARSSAV_PTR,0L,SEEK_SET);
     #if defined(DOS386)
     //#if DOS386==1
       write(gradient_structure::GRAD_STACK1->_VARSSAV_PTR,
         (char*)src,bytes_needed);
     #else
     unsigned long int max_move=500;
     unsigned long int left_to_move=bytes_needed;
     while(left_to_move > max_move)
     {
       write(_VARSSAV_PTR,(char*)src,max_move);
       left_to_move-=max_move;
       src+=max_move;
     }
     write(gradient_structure::GRAD_STACK1->_VARSSAV_PTR,(char*)src,
       left_to_move);
    #endif
  }
}

/**
 * Description not yet available.
 * \param
 */
void gradient_structure::restore_arrays()
{
  long bytes_needed=min(gradient_structure::ARR_LIST1->get_last_offset()+1,
    ARRAY_MEMBLOCK_SIZE);
  if (gradient_structure::save_var_file_flag==0)
  {
    #if defined(DOS386)
    //#if DOS386==1
      #ifndef USE_ASSEMBLER
        memcpy((char*)ARRAY_MEMBLOCK_BASE,(char*)ARRAY_MEMBLOCK_SAVE,
	  bytes_needed);
       #else
         dw_block_move((double*)ARRAY_MEMBLOCK_BASE,
           (double*)ARRAY_MEMBLOCK_SAVE,bytes_needed/8);
       #endif
     #else
     unsigned long max_move=50000;

     long int left_to_move=bytes_needed;
     humungous_pointer src = ARRAY_MEMBLOCK_SAVE;
     humungous_pointer dest = ARRAY_MEMBLOCK_BASE;
     while(left_to_move > max_move)
     {
       memcpy((char*)dest,(char*)src,max_move);
       left_to_move-=max_move;
       src+=max_move;
       dest+=max_move;
     }
     memcpy((char*)dest,(char*)src,left_to_move);
    #endif
    ARRAY_MEMBLOCK_SAVE.free();
  }
  else
  {
    humungous_pointer dest = ARRAY_MEMBLOCK_BASE;
    lseek(gradient_structure::GRAD_STACK1->_VARSSAV_PTR,0L,SEEK_SET);
    #if defined(DOS386)
    // #if DOS386==1
      read(gradient_structure::GRAD_STACK1->_VARSSAV_PTR,
       (char*)dest,bytes_needed);
    #else
     unsigned long int max_move=50000;

     long int left_to_move=bytes_needed;
     while(left_to_move > max_move)
     {
       read(gradient_structure::GRAD_STACK1->_VARSSAV_PTR,
         (char*)dest,max_move);
       left_to_move-=max_move;
       dest+=max_move;
     }
     read(gradient_structure::GRAD_STACK1->_VARSSAV_PTR,
       (char*)dest,left_to_move);
    #endif
  }
}

/**
 * Description not yet available.
 * \param
 */
void gradient_structure::save_variables()
{
  if ((variables_save = new double[gradient_structure::MAX_DLINKS])==NULL)
  {
    //_VARSSAV_PTR=open(var_store_file_name, O_RDWR | O_CREAT | O_TRUNC ,
    //		     S_IREAD | S_IWRITE);
    cerr << "insufficient memory to allocate space for dvariables"
	 << " save buffer " << endl;
    ad_exit(1);
  }
  for (unsigned int i=0; i<gradient_structure::GRAD_LIST->nlinks; i++)
  {
    //variables_save[i]= * (double*)
    //	  (gradient_structure::GRAD_LIST->dlink_addresses[i]);
    memcpy(&(variables_save[i]),
       gradient_structure::GRAD_LIST->dlink_addresses[i],sizeof(double));
  }
}

/**
 * Description not yet available.
 * \param
 */
void gradient_structure::restore_variables()
{
  for (unsigned int i=0; i<gradient_structure::GRAD_LIST->nlinks; i++)
  {
     //* (double*)(gradient_structure::GRAD_LIST->dlink_addresses[i])
     //	= variables_save[i];
    memcpy(gradient_structure::GRAD_LIST->dlink_addresses[i],
       &(variables_save[i]),sizeof(double));
  }
  delete [] variables_save;
}

void KLUDGEX(void * p){;}

/**
 * Description not yet available.
 * \param
 */
void reset_gradient_stack(void)
{
  gradient_structure::GRAD_STACK1->ptr = 
    gradient_structure::GRAD_STACK1->ptr_first;

  int& _GRADFILE_PTR=gradient_structure::GRAD_STACK1->_GRADFILE_PTR;

  lseek(_GRADFILE_PTR,0L,SEEK_SET);
}

static int inner_count=0;
//static grad_stack_entry * pgse = (grad_stack_entry*) (0x1498fffc);

/**
 * Description not yet available.
 * \param
 */
void grad_stack::set_gradient_stack1(void (* func)(void),
  double * dep_addr,double * ind_addr1)
{
#ifdef NO_DERIVS
  if (!gradient_structure::no_derivatives)
  {
#endif
    inner_count++;
    /*
    if (inner_count == 404849)
    {
       cout << ptr << endl;
       cout << ptr->func << endl;
       cout << ptr->dep_addr << endl;
       cout << (int)(ptr->dep_addr)%8 << endl;
    }
    */
    if (ptr > ptr_last)
    {
       // current buffer is full -- write it to disk and reset pointer
       // and counter
       this->write_grad_stack_buffer();
    }

    test_the_pointer();

    ptr->func = func;
    ptr->dep_addr = dep_addr;
    ptr->ind_addr1 = ind_addr1;
    ptr++;
#ifdef NO_DERIVS
  }
#endif
}

/**
 * Description not yet available.
 * \param
 */
void test_the_pointer(void)
{
 /*
  pgse->func = (void (*)())(100);
  pgse->dep_addr = (double*) 100;
  pgse->ind_addr1 = (double*) 100;
 */
}
