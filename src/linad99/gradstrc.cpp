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
#ifndef _MSC_VER
  #include <unistd.h>
#endif
#include "fvar.hpp"

//#define THREAD_SAFE

#if defined(THREAD_SAFE)
  pthread_mutex_t mutex_return_arrays = PTHREAD_MUTEX_INITIALIZER;
#endif

void null_ptr_err_message(void);

#include <string.h>

#if defined(__TURBOC__)
  #pragma hdrstop
  #include <iostream.h>
  #include <alloc.h>
#endif

#include <stdlib.h>

#ifdef __ZTC__
  #include <iostream.hpp>
  int _cdecl farfree(void _far *ptr);
  void _far * _cdecl farmalloc(unsigned long size);
#endif

#ifndef OPT_LIB
  #include <cassert>
#endif

extern ofstream clogf;
#ifndef __SUNPRO_CC
typedef int (* fptr) (const char * format, ...) ;
#endif

//void adwait(double);
fptr ad_printf = printf;
extern "C"{
  exitptr ad_exit=&exit;

  void spdll_exit(int ierr)
  {
    if (ad_printf) (*ad_printf) (" Exception -- error code %d\n",ierr);
    if (ad_printf) (*ad_printf) (" Pause");
    //adwait(4.0);
#if defined(USE_EXCEPTIONS)
    throw spdll_exception(ierr);
#endif
  }
}

//char * MY_BUF=NULL;
// *************************************************************
// *************************************************************
int ctlc_flag = 0;
int gradient_structure::Hybrid_bounded_flag=0;
DF_FILE * gradient_structure::fp=NULL;
char gradient_structure::cmpdif_file_name[61];
//char gradient_structure::var_store_file_name[61];
int gradient_structure::NUM_RETURN_ARRAYS = 25;
double * gradient_structure::hessian_ptr=NULL;
int gradient_structure::NUM_DEPENDENT_VARIABLES = 2000;
#if (defined(NO_DERIVS))
  int gradient_structure::no_derivatives = 0;
#endif
unsigned long int gradient_structure::max_last_offset = 0;
long int gradient_structure::NVAR = 0;
size_t gradient_structure::TOTAL_BYTES = 0;
size_t gradient_structure::PREVIOUS_TOTAL_BYTES = 0;
long int gradient_structure::USE_FOR_HESSIAN = 0;
dvariable** gradient_structure::RETURN_ARRAYS = NULL;
int gradient_structure::RETURN_ARRAYS_PTR;
dvariable ** gradient_structure::RETURN_PTR_CONTAINER = NULL;
int gradient_structure::RETURN_ARRAYS_SIZE = 70;
int gradient_structure::instances = 0;
//int gradient_structure::RETURN_INDEX = 0;
//dvariable * gradient_structure::FRETURN = NULL;
dvariable * gradient_structure::MAX_RETURN = NULL;
dvariable * gradient_structure::MIN_RETURN = NULL;
dvariable * gradient_structure::RETURN_PTR = NULL;
#ifdef __BORLANDC__
long int gradient_structure::GRADSTACK_BUFFER_SIZE = 4000000L;
long int gradient_structure::CMPDIF_BUFFER_SIZE=140000000L;
#else
size_t gradient_structure::GRADSTACK_BUFFER_SIZE = 4000000L;
size_t gradient_structure::CMPDIF_BUFFER_SIZE=140000000L;
#endif

dependent_variables_information * gradient_structure::DEPVARS_INFO=NULL;

int gradient_structure::save_var_flag=0;
int gradient_structure::save_var_file_flag=0;

// should be int gradfile_handle;
//int gradient_structure::_GRADFILE_PTR = NULL;

// should be int gradfile_handle;
//int gradient_structure::_GRADFILE_PTR1 = NULL;

// should be int gradfile_handle;
//int gradient_structure::_GRADFILE_PTR2 = NULL;

// should be int gradfile_handle;
//int gradient_structure::_VARSSAV_PTR = 0;

unsigned int gradient_structure::MAX_NVAR_OFFSET = 5000;
unsigned long gradient_structure::ARRAY_MEMBLOCK_SIZE = 0L; //js
dlist * gradient_structure::GRAD_LIST;
grad_stack * gradient_structure::GRAD_STACK1;
indvar_offset_list * gradient_structure::INDVAR_LIST = NULL;
arr_list * gradient_structure::ARR_LIST1 = NULL;
arr_list * gradient_structure::ARR_FREE_LIST1 = NULL;
unsigned int gradient_structure::MAX_DLINKS = 5000;

// note: ARRAY_MEMBLOCK stuff is set by tpl2cpp for historical reasons
//       those settings could be moved into this file in the future
//       - Ian Taylor 5/3/2012

//unsigned long int gradient_structure::ARRAY_MEMBLOCK_BASE = 0L;
humungous_pointer gradient_structure::ARRAY_MEMBLOCK_BASE;
humungous_pointer gradient_structure::ARRAY_MEMBLOCK_BASEA;
humungous_pointer gradient_structure::ARRAY_MEMBLOCK_SAVE;
double * gradient_structure::variables_save=NULL;
void * farptr_norm(void *);
long int farptr_tolong(void *) ;
void memory_allocate_error(const char * s, void * ptr);

/**
 * Description not yet available.
 * \param
 */
size_t gradient_structure::NUM_GRADSTACK_BYTES_WRITTEN(void)
{
  size_t tmp = TOTAL_BYTES - PREVIOUS_TOTAL_BYTES;
  PREVIOUS_TOTAL_BYTES = TOTAL_BYTES;
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
char lastchar(char* s)
{
  size_t k = strlen(s);
  return s[k - 1];
}

/**
 * Description not yet available.
 * \param
 */
size_t gradient_structure::totalbytes(void)
{
  return TOTAL_BYTES;
}

 void fill_ad_random_part(void);
 extern char ad_random_part[6];

/**
Close gradient and variable files.  Free gradient structure memory.
*/
void cleanup_temporary_files()
{
   if (gradient_structure::fp)
   {
     delete gradient_structure::fp;
     gradient_structure::fp=NULL;
   }
   if (gradient_structure::GRAD_STACK1)
   {
     if (close(gradient_structure::GRAD_STACK1->_GRADFILE_PTR1))
     {
       cerr << "Error closing file "
       << gradient_structure::GRAD_STACK1->gradfile_name1 << "\n";
     }
     if (close(gradient_structure::GRAD_STACK1->_GRADFILE_PTR2))
     {
       cerr << "Error closing file "
       << gradient_structure::GRAD_STACK1->gradfile_name2 << "\n";
     }
     if (close( gradient_structure::GRAD_STACK1->_VARSSAV_PTR))
     {
       cerr << "Error closing file "
       << gradient_structure::GRAD_STACK1->var_store_file_name << "\n";
     }
   }
#if !defined (_MSC_VER)
   if (gradient_structure::GRAD_STACK1)
   {
     unlink(gradient_structure::GRAD_STACK1->gradfile_name1);
     unlink(gradient_structure::GRAD_STACK1->gradfile_name2);
     unlink(gradient_structure::GRAD_STACK1->var_store_file_name);
     //unlink(gradient_structure::cmpdif_file_name);
   }
#else
   if (gradient_structure::GRAD_STACK1)
   {
     remove(gradient_structure::GRAD_STACK1->gradfile_name1);
     remove(gradient_structure::GRAD_STACK1->gradfile_name2);
     remove(gradient_structure::GRAD_STACK1->var_store_file_name);
     //cout << remove(gradient_structure::cmpdif_file_name);
   }
#endif
}

/**
 * Description not yet available.
 * \param
 */
void allocate_dvariable_space()
{
  int on,nopt = 0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mdl",nopt))>-1)
  {
    if (nopt ==1)
    {
      const int i = atoi(ad_comm::argv[on+1]);
      if (i > 0)
      {
        gradient_structure::MAX_DLINKS = (unsigned int)i;
      }
    }
    else
    {
      cerr << "Wrong number of options to -mdl -- must be 1"
        " you have " << nopt << endl;
      ad_exit(1);
    }
  }
  unsigned int numlinks=gradient_structure::MAX_DLINKS;
  //cout << sizeof(dlink) << endl;

#ifndef OPT_LIB
  //cerr << "sizeof(char) is not equal 1) --"
  // " need to modify allocate_dvariable_space in gradstrc.cpp" << endl;
  assert(sizeof(char) == 1);

  //cerr << "sizeof(dlink) is greater than 2*sizeof(double) --"
  // " need to modify allocate_dvariable_space in gradstrc.cpp" << endl;
  assert(sizeof(dlink) == 2 * sizeof(double));
#endif
  const size_t size = 2 * sizeof(double) * (numlinks + 1);
  char* tmp1 = (char*)malloc(size * sizeof(char));
  if (!tmp1)
  {
    cerr << "Error[" << __FILE__ << ":" << __LINE__
         << "]: unable to allocate memory.\n";
    ad_exit(1);
  }
  else
  {
    dlink * dl=(dlink*)tmp1;
    tmp1+=2*sizeof(double);
    dl->prev=NULL;
    dlink * prev=dl;
    int& nlinks=(int&)gradient_structure::GRAD_LIST->nlinks;
    gradient_structure::GRAD_LIST->dlink_addresses[nlinks++]=dl;
    for (unsigned int i=1;i<=numlinks;i++)
    {
      dl=(dlink*)tmp1;
      dl->prev=prev;
      prev=dl;
      tmp1+=2*sizeof(double);

      gradient_structure::GRAD_LIST->dlink_addresses[nlinks++]=dl;
      // keep track of the links so you can zero them out
    }
    gradient_structure::GRAD_LIST->last=dl;
  }
}

/**
 * Description not yet available.
 * \param
 */
 gradient_structure::gradient_structure(long int _size)
 {
#ifndef OPT_LIB
  assert(_size > 0);
#endif
   gradient_structure::NVAR=0;
   atexit(cleanup_temporary_files);
   fill_ad_random_part();

   const unsigned long int size = (unsigned long int)_size;

   if (instances++ > 0)
   {
     cerr << "More than one gradient_structure object has been declared.\n"
          << "  Only one gradient_structure object can exist. Check the scope\n"
          << "  of the objects declared.\n";
     ad_exit(1);
   }
   gradient_structure::ARRAY_MEMBLOCK_SIZE=size; //js

   char * path = getenv("ADTMP1"); // NULL if not defined
   if (path != NULL)
   {
     #ifdef __SUN__
     sprintf(&cmpdif_file_name[0],"%s/cmpdiff.%s", path,
          ad_random_part);
     #else
        if (lastchar(path)!='\\')
        {
          sprintf(&cmpdif_file_name[0],"%s\\cmpdiff.%s", path,
            ad_random_part);
        }
        else
        {
          sprintf(&cmpdif_file_name[0],"%scmpdiff.%s", path,
            ad_random_part);
        }
     #endif
   }
   else
   {
      sprintf(&cmpdif_file_name[0],"cmpdiff.%s",ad_random_part);
   }

   if (DEPVARS_INFO!= NULL)
   {
      cerr << "  0 Trying to allocate to a non NULL pointer in gradient"
              "_structure" << endl;
   }
   else
   {
     int on,nopt = 0;
     if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-ndv",nopt))>-1)
     {
       if (!nopt)
       {
         cerr << "Usage -ndv option needs integer  -- ignored" << endl;
       }
       else
       {
         int jj=atoi(ad_comm::argv[on+1]);
         if (jj<=0)
         {
           cerr << "Usage -ndv option needs positive integer"
              "  -- ignored" << endl;
         }
         else
         {
           NUM_DEPENDENT_VARIABLES=jj;
         }
       }
     }
     DEPVARS_INFO=new dependent_variables_information(NUM_DEPENDENT_VARIABLES);
     memory_allocate_error("DEPVARS_INFO", (void *) DEPVARS_INFO);
   }

   if (fp!= NULL)
   {
      cerr << "  0 Trying to allocate to a non NULL pointer in gradient"
              "_structure" << endl;
   }
   else
   {
     fp=new DF_FILE(CMPDIF_BUFFER_SIZE);
     memory_allocate_error("fp", (void *) fp);
   }

   void * temp_ptr;
  // double_and_int * tmp;
   #ifdef DIAG
     cerr <<" In gradient_structure::gradient_structure()\n";
     cerr <<"  ARRAY_MEMBLOCK_SIZE = " << ARRAY_MEMBLOCK_SIZE << "\n";
   #endif

   if ( GRAD_LIST!= NULL)
   {
    cerr << "Trying to allocate to a non NULL pointer in gradient structure\n";
   }
   else
   {
      GRAD_LIST = new dlist;
      memory_allocate_error("GRAD_LIST", (void *) GRAD_LIST);
   }

   if ( ARR_LIST1!= NULL)
   {
     cerr << "Trying to allocate to a non NULL pointer in gradient structure\n";
   }
   else
   {
      ARR_LIST1 = new arr_list;
      memory_allocate_error("ARR_LIST1", (void *) ARR_LIST1);
   }

 /*
   if ( ARR_FREE_LIST1!= NULL)
   {
cerr << "  2 Trying to allocate to a non NULL pointer in gradient structure \n";
   }
   else
   {
      ARR_FREE_LIST1 = new arr_list;
      memory_allocate_error("ARR_FREE_LIST1", (void *) ARR_FREE_LIST1);
   }
 */

#ifdef __ZTC__
   if ((temp_ptr = farmalloc(ARRAY_MEMBLOCK_SIZE)) == 0)
#else
   if ((temp_ptr = (void*)malloc(ARRAY_MEMBLOCK_SIZE)) == 0)
#endif
   {
     cerr << "insufficient memory to allocate space for ARRAY_MEMBLOCKa\n";
     ad_exit(1);
   }

  /*
   if (ARRAY_MEMBLOCK_BASE != NULL)
   {
cerr << "Trying to allocate to a non NULL pointer in gradient structure \n";
   }
 */

   ARRAY_MEMBLOCK_BASE = temp_ptr;

   const size_t adjustment = (8 -((size_t)ARRAY_MEMBLOCK_BASE.ptr) % 8) % 8;
   ARRAY_MEMBLOCK_BASE.adjust(adjustment);

   if (GRAD_STACK1 != NULL)
   {
      cerr << "Trying to allocate to a non NULL pointer\n";
   }
   else
   {
     GRAD_STACK1 = new grad_stack;
     memory_allocate_error("GRAD_STACK1",GRAD_STACK1);
     gradient_structure::hessian_ptr= (double*) GRAD_STACK1->true_ptr_first;
   }
    #ifdef DIAG
        cout << "GRAD_STACK1= "<< farptr_tolong(GRAD_STACK1)<<"\n";
    #endif

   if ( INDVAR_LIST!= NULL)
   {
      cerr <<
        "Trying to allocate to a non NULL pointer in gradient structure \n";
      ad_exit(1);
   }
   else
   {
     INDVAR_LIST = new indvar_offset_list;
     memory_allocate_error("INDVAR_LIST",INDVAR_LIST);
 // ****************************************************************
 // ****************************************************************
      int nopt=0;
      int on=0;

      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mno",nopt))>-1)
      {
        if (nopt ==1)
        {
          const int i = atoi(ad_comm::argv[on+1]);
          MAX_NVAR_OFFSET = (unsigned int)i;
        }
        else
        {
          cerr << "Wrong number of options to -mno -- must be 1"
            " you have " << nopt << endl;
          ad_exit(1);
        }
      }

 // ****************************************************************
 // ****************************************************************

     INDVAR_LIST->address = new double * [ (size_t) MAX_NVAR_OFFSET];
     memory_allocate_error("INDVAR_LIST->address",INDVAR_LIST->address);
   }

   //allocate_dvariable_space();

   if ( RETURN_ARRAYS!= NULL)
   {
cerr << "Trying to allocate to a non NULL pointer in gradient structure \n";
      ad_exit(1);
   }
   else
   {
      RETURN_ARRAYS = new dvariable*[NUM_RETURN_ARRAYS];
      memory_allocate_error("RETURN_ARRAYS",RETURN_ARRAYS);

      //allocate_dvariable_space();
      for (int i=0; i< NUM_RETURN_ARRAYS; i++)
      {
        RETURN_ARRAYS[i]=new dvariable[RETURN_ARRAYS_SIZE];
        memory_allocate_error("RETURN_ARRAYS[i]",RETURN_ARRAYS[i]);
      }
      RETURN_ARRAYS_PTR=0;
      MIN_RETURN = RETURN_ARRAYS[RETURN_ARRAYS_PTR];
      MAX_RETURN = RETURN_ARRAYS[RETURN_ARRAYS_PTR]+RETURN_ARRAYS_SIZE-1;
      RETURN_PTR = MIN_RETURN;
   }
   //RETURN_INDEX = 0;

   RETURN_PTR_CONTAINER=new dvariable*[NUM_RETURN_ARRAYS];
   memory_allocate_error("RETURN_INDICES_CONTAINER",RETURN_PTR_CONTAINER);

   for (int i=0; i< NUM_RETURN_ARRAYS; i++)
   {
     RETURN_PTR_CONTAINER[i]=0;
   }
 }

/**
Increments gradient_structure::RETURN_ARRAYS_PTR.
Must be called on entry to any function that returns a variable object.
Calls must balance calls to void RETURN_ARRAYS_DECREMENT(void).
\ingroup RA
*/
void RETURN_ARRAYS_INCREMENT(void)
{
#if defined(THREAD_SAFE)
  pthread_mutex_lock(&mutex_return_arrays);
#endif
  gradient_structure::RETURN_PTR_CONTAINER[
    gradient_structure::RETURN_ARRAYS_PTR]=gradient_structure::RETURN_PTR;
  if (++gradient_structure::RETURN_ARRAYS_PTR ==
    gradient_structure::NUM_RETURN_ARRAYS)
  {
    cerr << " Overflow in RETURN_ARRAYS stack -- Increase NUM_RETURN_ARRAYS\n";
    cerr << " There may be a RETURN_ARRAYS_INCREMENT()\n";
    cerr << " which is not matched by a RETURN_ARRAYS_DECREMENT()\n";
    ad_exit(24);
  }
  gradient_structure::MIN_RETURN =
    gradient_structure::RETURN_ARRAYS[gradient_structure::RETURN_ARRAYS_PTR];
  gradient_structure::MAX_RETURN =
    gradient_structure::RETURN_ARRAYS[gradient_structure::RETURN_ARRAYS_PTR]+
    gradient_structure::RETURN_ARRAYS_SIZE-1;
  gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
#if defined(THREAD_SAFE)
  pthread_mutex_unlock(&mutex_return_arrays);
#endif
}

/**
Decrements gradient_structure::RETURN_ARRAYS_PTR.
Must be called prior to exit from any functiton that returns a variable object.
Calls must balance calls to void RETURN_ARRAYS_INCREMENT(void).
\ingroup RA
*/
void RETURN_ARRAYS_DECREMENT(void)
{
#if defined(THREAD_SAFE)
  pthread_mutex_lock(&mutex_return_arrays);
#endif
  if (--gradient_structure::RETURN_ARRAYS_PTR< 0)
  {
    cerr << " Error -- RETURN_ARRAYS_PTR < 0  \n";
    cerr << " There must be a RETURN_ARRAYS_DECREMENT()\n";
    cerr << " which is not matched by a RETURN_ARRAYS_INCREMENT()\n";
    ad_exit(24);
  }
  gradient_structure::MIN_RETURN =
    gradient_structure::RETURN_ARRAYS[gradient_structure::RETURN_ARRAYS_PTR];
  gradient_structure::MAX_RETURN =
    gradient_structure::RETURN_ARRAYS[gradient_structure::RETURN_ARRAYS_PTR]+
    gradient_structure::RETURN_ARRAYS_SIZE-1;
  gradient_structure::RETURN_PTR =
    gradient_structure::RETURN_PTR_CONTAINER[
      gradient_structure::RETURN_ARRAYS_PTR];
#if defined(THREAD_SAFE)
  pthread_mutex_unlock(&mutex_return_arrays);
#endif
}

/**
 * Description not yet available.
 * \param
 */
gradient_structure::~gradient_structure()
{
   gradient_structure::NVAR=0;
   if (RETURN_ARRAYS == NULL)
   {
     null_ptr_err_message();
     ad_exit(1);
   }
   else
   {
     for (int i=0; i< NUM_RETURN_ARRAYS; i++)
     {
       delete [] RETURN_ARRAYS[i];
       RETURN_ARRAYS[i]=NULL;
     }
     delete [] RETURN_ARRAYS;
     RETURN_ARRAYS = NULL;
     delete [] RETURN_PTR_CONTAINER;
     RETURN_PTR_CONTAINER = NULL;
   }
   if (INDVAR_LIST == NULL)
   {
     null_ptr_err_message();
     ad_exit(1);
   }
   else
   {
     delete [] INDVAR_LIST->address;
     delete INDVAR_LIST;
     INDVAR_LIST = NULL;
   }

   if (GRAD_STACK1 == NULL)
   {
     null_ptr_err_message();
     ad_exit(1);
   }
   else
   {
     delete GRAD_STACK1;
     GRAD_STACK1 = NULL;
   }

   if (ARRAY_MEMBLOCK_BASE == NULL)
   {
     cerr << "Trying to farfree a NULL pointer in ~gradient_structure\n";
     ad_exit(1);
   }
   else
   {
     ARRAY_MEMBLOCK_BASE.free();
   }

   if (ARR_LIST1 == NULL)
   {
     null_ptr_err_message();
     ad_exit(1);
   }
   else
   {
      delete ARR_LIST1;
      ARR_LIST1 = NULL;
   }

   if (GRAD_LIST == NULL)
   {
     null_ptr_err_message();
     ad_exit(1);
   }
   else
   {
      delete GRAD_LIST;
      GRAD_LIST = NULL;
   }

   instances--;

   if (DEPVARS_INFO==NULL)
   {
     null_ptr_err_message();
     ad_exit(1);
   }
   delete DEPVARS_INFO;
   DEPVARS_INFO=NULL;

   if (fp == NULL)
   {
     cerr << "Trying to close stream referenced by a NULL pointer\n"
       " in ~gradient_structure\n";
     ad_exit(1);
   }
   delete fp;
   fp = NULL;
}

/**
 * Description not yet available.
 * \param
 */
void null_ptr_err_message(void)
{
   cerr << "Trying to delete a NULL pointer in ~gradient_structure" << endl;
}

/**
 * Description not yet available.
 * \param
 */
void memory_allocate_error(const char * s, void * ptr)
{
  if (ptr == NULL)
  {
    cerr << " Error trying to allocate " << s << "\n";
    ad_exit(21);
  }
}

 #if defined(NO_DERIVS)

/**
 * Description not yet available.
 * \param
 */
    void gradient_structure::set_NO_DERIVATIVES(void)
    {
      no_derivatives=1;
    }

/**
 * Description not yet available.
 * \param
 */
    void gradient_structure::set_YES_DERIVATIVES(void)
    {
      no_derivatives=0;
    }
 #endif

/**
 * Description not yet available.
 * \param
 */
    void  gradient_structure::set_YES_SAVE_VARIABLES_VALUES(void)
    {
      save_var_flag=1;
    }

/**
 * Description not yet available.
 * \param
 */
    void  gradient_structure::set_NO_SAVE_VARIABLES_VALUES(void)
    {
      save_var_flag=0;
    }

/**
 * Description not yet available.
 * \param
 */
    void gradient_structure::set_NUM_DEPENDENT_VARIABLES(int i)
    {
      if (i<1)
      {
        cerr << " Error in "
                "gradient_structure::set_NUM_DEPENDENT_VARIABLES(int i)"
             << endl << " value of i must be >= 1" << endl;
        i=1;
      }
      NUM_DEPENDENT_VARIABLES=i;
    }
