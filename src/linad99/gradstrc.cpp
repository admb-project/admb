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

// *************************************************************
// *************************************************************
int ctlc_flag = 0;
int gradient_structure::Hybrid_bounded_flag=0;
//char gradient_structure::var_store_file_name[61];
unsigned int gradient_structure::NUM_RETURN_ARRAYS = 25;
double * gradient_structure::hessian_ptr=NULL;
int gradient_structure::NUM_DEPENDENT_VARIABLES = 2000;
#if (defined(NO_DERIVS))
  int gradient_structure::no_derivatives = 0;
#endif
unsigned long int gradient_structure::max_last_offset = 0;
long int gradient_structure::NVAR = 0;
long int gradient_structure::USE_FOR_HESSIAN = 0;
unsigned int gradient_structure::RETURN_ARRAYS_SIZE = 70;
int gradient_structure::instances = 0;
//int gradient_structure::RETURN_INDEX = 0;
//dvariable * gradient_structure::FRETURN = NULL;
#ifdef __BORLANDC__
long int gradient_structure::GRADSTACK_BUFFER_SIZE = 4000000L;
long int gradient_structure::CMPDIF_BUFFER_SIZE=140000000L;
#else
size_t gradient_structure::GRADSTACK_BUFFER_SIZE = 4000000L;
size_t gradient_structure::CMPDIF_BUFFER_SIZE=140000000L;
#endif

int gradient_structure::save_var_flag=0;
int gradient_structure::save_var_file_flag=0;

unsigned int gradient_structure::MAX_NVAR_OFFSET = 5000;
unsigned long gradient_structure::ARRAY_MEMBLOCK_SIZE = 0L; //js
__thread grad_stack* gradient_structure::GRAD_STACK1 = NULL;
unsigned int gradient_structure::MAX_DLINKS = 5000;

// note: ARRAY_MEMBLOCK stuff is set by tpl2cpp for historical reasons
//       those settings could be moved into this file in the future
//       - Ian Taylor 5/3/2012

#ifdef DIAG
long int farptr_tolong(void *) ;
#endif
void memory_allocate_error(const char * s, void * ptr);

/**
 * Description not yet available.
 * \param
 */
size_t gradient_structure::NUM_GRADSTACK_BYTES_WRITTEN(void)
{
  grad_stack* gstack = gradient_structure::GRAD_STACK1;

  if (!gstack) return 0;

  size_t tmp = gstack->TOTAL_BYTES - gstack->PREVIOUS_TOTAL_BYTES;
  gstack->PREVIOUS_TOTAL_BYTES = gstack->TOTAL_BYTES;

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
Returns total bytes used in current GRAD_STACK1.
*/
size_t gradient_structure::totalbytes(void)
{
  grad_stack* gs = gradient_structure::GRAD_STACK1;
  return gs ? gradient_structure::GRAD_STACK1->TOTAL_BYTES : 0;
}

/// Close gradient and variable files and free gradient structure memory.
void cleanup_temporary_files()
{
  if (gradient_structure::GRAD_STACK1)
  {
    if (gradient_structure::GRAD_STACK1->fp)
    {
      delete gradient_structure::GRAD_STACK1->fp;
      gradient_structure::GRAD_STACK1->fp = NULL;
    }
    if (gradient_structure::GRAD_STACK1->_GRADFILE_PTR1 != -1
        && close(gradient_structure::GRAD_STACK1->_GRADFILE_PTR1))
    {
      cerr << "Error closing file "
           << gradient_structure::GRAD_STACK1->gradfile_name1 << "\n";
    }
    gradient_structure::GRAD_STACK1->_GRADFILE_PTR1 = -1;
    if (gradient_structure::GRAD_STACK1->_GRADFILE_PTR2 != -1
        && close(gradient_structure::GRAD_STACK1->_GRADFILE_PTR2))
    {
      cerr << "Error closing file "
           << gradient_structure::GRAD_STACK1->gradfile_name2 << "\n";
    }
    gradient_structure::GRAD_STACK1->_GRADFILE_PTR2 = -1;
    if (gradient_structure::GRAD_STACK1->_VARSSAV_PTR != -1
        && close(gradient_structure::GRAD_STACK1->_VARSSAV_PTR))
    {
      cerr << "Error closing file "
           << gradient_structure::GRAD_STACK1->var_store_file_name << "\n";
    }
    gradient_structure::GRAD_STACK1->_VARSSAV_PTR = -1;
#if defined (_MSC_VER)
    remove(gradient_structure::GRAD_STACK1->gradfile_name1);
    remove(gradient_structure::GRAD_STACK1->gradfile_name2);
    remove(gradient_structure::GRAD_STACK1->var_store_file_name);
#else
    unlink(gradient_structure::GRAD_STACK1->gradfile_name1);
    unlink(gradient_structure::GRAD_STACK1->gradfile_name2);
    unlink(gradient_structure::GRAD_STACK1->var_store_file_name);
#endif
  }
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
    int& nlinks=(int&)gradient_structure::GRAD_STACK1->GRAD_LIST->nlinks;
    gradient_structure::GRAD_STACK1->GRAD_LIST->dlink_addresses[nlinks++]=dl;
    for (unsigned int i=1;i<=numlinks;i++)
    {
      dl=(dlink*)tmp1;
      dl->prev=prev;
      prev=dl;
      tmp1+=2*sizeof(double);

      gradient_structure::GRAD_STACK1->GRAD_LIST->dlink_addresses[nlinks++]=dl;
      // keep track of the links so you can zero them out
    }
    gradient_structure::GRAD_STACK1->GRAD_LIST->last=dl;
  }
}

std::mutex m;

/**
Constructor
*/
gradient_structure::gradient_structure(long int _size):
  x(0)
{
#ifndef OPT_LIB
  assert(_size > 0);
#endif
  gradient_structure::NVAR=0;
  atexit(cleanup_temporary_files);

  m.lock();
  instances++;
  m.unlock();

  //Should be a multiple of sizeof(double_and_int)
  const long int remainder = _size % sizeof(double_and_int);
  gradient_structure::ARRAY_MEMBLOCK_SIZE =
    static_cast<unsigned long int>(_size - remainder);

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
          cerr << "Usage -ndv option needs positive integer -- ignored"
               << endl;
        }
        else
        {
          NUM_DEPENDENT_VARIABLES=jj;
        }
      }
    }
  }
  // double_and_int * tmp;
#ifdef DIAG
  cerr <<" In gradient_structure::gradient_structure()\n";
  cerr <<"  ARRAY_MEMBLOCK_SIZE = " << ARRAY_MEMBLOCK_SIZE << "\n";
#endif

   {
     int on,nopt = 0;
     if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mdl",nopt))>-1)
     {
       if (nopt == 1)
       {
         int i = atoi(ad_comm::argv[on+1]);
         if (i > 0)
           gradient_structure::MAX_DLINKS = (unsigned int)i;
       }
       else
       {
         cerr << "Wrong number of options to -mdl -- must be 1"
           " you have " << nopt << endl;
         ad_exit(1);
       }
     }
   }
   {
 // ****************************************************************
 // ****************************************************************
      int nopt=0;
      int on=0;

      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mno",nopt))>-1)
      {
        if (nopt ==1)
        {
          const int i = atoi(ad_comm::argv[on+1]);
          MAX_NVAR_OFFSET = static_cast<unsigned int>(i);
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
   }

   if (GRAD_STACK1 != NULL)
   {
     cerr << "Trying to allocate to a non NULL pointer\n";
   }
   else
   {
     GRAD_STACK1 = new grad_stack(_size, instances - 1);
     memory_allocate_error("GRAD_STACK1",GRAD_STACK1);
     gradient_structure::hessian_ptr= (double*) GRAD_STACK1->true_ptr_first;
     GRAD_STACK1->allocate_RETURN_ARRAYS(NUM_RETURN_ARRAYS, RETURN_ARRAYS_SIZE);
   }
#ifdef DIAG
   cout << "GRAD_STACK1= "<< farptr_tolong(GRAD_STACK1)<<"\n";
#endif
   //allocate_dvariable_space();
}
void grad_stack::allocate_RETURN_ARRAYS(
  unsigned int _NUM_RETURN_ARRAYS,
  unsigned int _RETURN_ARRAYS_SIZE)
{
  if (RETURN_ARRAYS != NULL)
  {
cerr << "Trying to allocate to a non NULL pointer in gradient structure \n";
    ad_exit(1);
  }

  NUM_RETURN_ARRAYS = _NUM_RETURN_ARRAYS;
  RETURN_ARRAYS_SIZE = _RETURN_ARRAYS_SIZE;

  RETURN_ARRAYS = new dvariable*[NUM_RETURN_ARRAYS];
  memory_allocate_error("RETURN_ARRAYS",RETURN_ARRAYS);

  //allocate_dvariable_space();
  for (unsigned int i = 0; i < NUM_RETURN_ARRAYS; ++i)
  {
    RETURN_ARRAYS[i]  = new dvariable[RETURN_ARRAYS_SIZE];
    memory_allocate_error("RETURN_ARRAYS[i]", RETURN_ARRAYS[i]);
  }

  RETURN_ARRAYS_PTR = 0;
  MIN_RETURN = RETURN_ARRAYS[RETURN_ARRAYS_PTR];
  MAX_RETURN = RETURN_ARRAYS[RETURN_ARRAYS_PTR]+RETURN_ARRAYS_SIZE-1;
  RETURN_PTR = MIN_RETURN;
  //RETURN_INDEX = 0;

  RETURN_PTR_CONTAINER = new dvariable*[NUM_RETURN_ARRAYS];
  memory_allocate_error("RETURN_INDICES_CONTAINER",RETURN_PTR_CONTAINER);

  for (unsigned int i = 0; i < NUM_RETURN_ARRAYS; ++i)
  {
    RETURN_PTR_CONTAINER[i] = 0;
  }
}

/**
Increments gradient_structure::RETURN_ARRAYS_PTR.
Must be called on entry to any function that returns a variable object.
Calls must balance calls to void RETURN_ARRAYS_DECREMENT(void).
\ingroup RA
*/
void RETURN_ARRAYS_INCREMENT()
{
#if defined(THREAD_SAFE)
  pthread_mutex_lock(&mutex_return_arrays);
#endif

  gradient_structure::GRAD_STACK1->RETURN_ARRAYS_INCREMENT();

#if defined(THREAD_SAFE)
  pthread_mutex_unlock(&mutex_return_arrays);
#endif
}
void grad_stack::RETURN_ARRAYS_INCREMENT()
{
  RETURN_PTR_CONTAINER[RETURN_ARRAYS_PTR] = RETURN_PTR;

  if (++RETURN_ARRAYS_PTR == NUM_RETURN_ARRAYS)
  {
    cerr << " Overflow in RETURN_ARRAYS stack -- Increase NUM_RETURN_ARRAYS\n";
    cerr << " There may be a RETURN_ARRAYS_INCREMENT()\n";
    cerr << " which is not matched by a RETURN_ARRAYS_DECREMENT()\n";
    ad_exit(24);
  }
  MIN_RETURN = RETURN_ARRAYS[RETURN_ARRAYS_PTR];
  MAX_RETURN = RETURN_ARRAYS[RETURN_ARRAYS_PTR] + RETURN_ARRAYS_SIZE - 1;
  RETURN_PTR = MIN_RETURN;
}

/**
Decrements gradient_structure::RETURN_ARRAYS_PTR.
Must be called prior to exit from any functiton that returns a variable object.
Calls must balance calls to void RETURN_ARRAYS_INCREMENT(void).
\ingroup RA
*/
void RETURN_ARRAYS_DECREMENT()
{
#if defined(THREAD_SAFE)
  pthread_mutex_lock(&mutex_return_arrays);
#endif

  gradient_structure::GRAD_STACK1->RETURN_ARRAYS_DECREMENT();

#if defined(THREAD_SAFE)
  pthread_mutex_unlock(&mutex_return_arrays);
#endif
}

void grad_stack::RETURN_ARRAYS_DECREMENT()
{
  if (RETURN_ARRAYS_PTR == 0)
  {
    cerr << " Error -- RETURN_ARRAYS_PTR is 0  \n";
    cerr << " There must be a RETURN_ARRAYS_DECREMENT()\n";
    cerr << " which is not matched by a RETURN_ARRAYS_INCREMENT()\n";
    ad_exit(24);
  }

  --RETURN_ARRAYS_PTR;

  MIN_RETURN = RETURN_ARRAYS[RETURN_ARRAYS_PTR];
  MAX_RETURN = RETURN_ARRAYS[RETURN_ARRAYS_PTR] + RETURN_ARRAYS_SIZE - 1;
  RETURN_PTR = RETURN_PTR_CONTAINER[RETURN_ARRAYS_PTR];
}
/**
Destructor
*/
gradient_structure::~gradient_structure()
{
  gradient_structure::NVAR=0;
  if (GRAD_STACK1 == NULL)
  {
    null_ptr_err_message();
    ad_exit(1);
  }
  else
  {
    GRAD_STACK1->deallocate_RETURN_ARRAYS();

    delete GRAD_STACK1;
    GRAD_STACK1 = NULL;
  }
  --instances;
}

/**
Outputs null error message.
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

/** Disable accumulation of derivative information. 
    Used internally by ADMB to avoid computation of derivatives.
    Also useful for running simulations using variable objects when
    function minimization is not required. 
   \ingroup BAD
 */
    void gradient_structure::set_NO_DERIVATIVES(void)
    {
      no_derivatives=1;
    }

/** Enable accumulation of derivative information. 
    Used internally by ADMB to restart computation of derivatives.
   \ingroup BAD
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
