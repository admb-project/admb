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
#ifdef USE_THREAD
  #include <mutex>
#endif
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

#ifdef DEBUG
  #include <cassert>
#endif

#ifndef __SUNPRO_CC
typedef int (* fptr) (const char * format, ...) ;
#endif

//void adwait(double);
extern "C"{
  exitptr ad_exit=&exit;

  void spdll_exit(int ierr)
  {
    ad_printf(" Exception -- error code %d\n",ierr);
    ad_printf(" Pause");
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
unsigned int gradient_structure::NUM_RETURN_ARRAYS = 25;
int gradient_structure::NUM_DEPENDENT_VARIABLES = 2000;
#if (defined(NO_DERIVS))
  int gradient_structure::no_derivatives = 0;
#endif
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

unsigned int gradient_structure::MAX_NVAR_OFFSET = 5000;
unsigned long gradient_structure::ARRAY_MEMBLOCK_SIZE = 0L; //js
//arr_list * gradient_structure::ARR_FREE_LIST1 = NULL;
unsigned int gradient_structure::MAX_DLINKS = 5000;

// note: ARRAY_MEMBLOCK stuff is set by tpl2cpp for historical reasons
//       those settings could be moved into this file in the future
//       - Ian Taylor 5/3/2012

//unsigned long int gradient_structure::ARRAY_MEMBLOCK_BASE = 0L;
#ifdef DIAG
long int _farptr_tolong(void *) ;
#endif
void memory_allocate_error(const char * s, void * ptr);

/// Allocate array of gradient_structure instances with size elements.
void gradient_structure::create(const unsigned int size)
{
  if (size > 0)
  {
    gradients_size = size;
    gradients = new gradient_structure*[gradients_size];
    gradients[0] = gradient_structure::get();
    for (unsigned int id = 1; id < gradients_size; ++id)
    {
      gradients[id] = new gradient_structure(10000L, id);
    }
    gradient_structure::reset(gradients[0]);
  }
}
gradient_structure* gradient_structure::reset(gradient_structure* instance)
{
  _instance = instance;
  return _instance;
}
/// Set _instance of gradient_structure from instances with id.
gradient_structure* gradient_structure::set(const unsigned int id)
{
#ifdef DEBUG
  assert(id < gradients_size);
#endif
  _instance = gradients[id];
  return _instance;
}
/// Delete gradient_structure instances.
void gradient_structure::clean()
{
  if (gradients_size > 0)
  {
    gradients[0] = nullptr;

    for (unsigned int id = 1; id < gradients_size; ++id)
    {
      if (gradients[id] != nullptr)
      {
        delete gradients[id];
        gradients[id] = nullptr;
      }
    }

    delete [] gradients;
    gradients = nullptr;

    gradients_size = 0;
  }
  _instance = this;
}

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

/// Close gradient and variable files and free gradient structure memory.
void cleanup_temporary_files()
{
#if defined(USE_VECTOR_SHAPE_POOL)
  void cleanup_xpools();
  cleanup_xpools();
#endif
  gradient_structure* gs = gradient_structure::get();
  if (gs)
  {
    delete gs;
    gs = nullptr;
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

#ifdef DEBUG
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
    int& nlinks=(int&)gradient_structure::get()->GRAD_LIST->nlinks;
    gradient_structure::get()->GRAD_LIST->dlink_addresses[nlinks++]=dl;
    for (unsigned int i=1;i<=numlinks;i++)
    {
      dl=(dlink*)tmp1;
      dl->prev=prev;
      prev=dl;
      tmp1+=2*sizeof(double);

      gradient_structure::get()->GRAD_LIST->dlink_addresses[nlinks++]=dl;
      // keep track of the links so you can zero them out
    }
    gradient_structure::get()->GRAD_LIST->last=dl;
  }
}

#ifdef USE_THREAD
std::mutex gsm;
#endif

/**
Constructor
*/
gradient_structure::gradient_structure(const long int _size, const unsigned int id):
  NVAR(0),
  x(id),
  hessian_ptr(NULL),
  max_last_offset(0)
{
#ifdef DEBUG
  assert(_size > 0);
#endif
  fill_ad_random_part();

  gradients = nullptr;
  gradients_size = 0;

  TOTAL_BYTES = 0;
  PREVIOUS_TOTAL_BYTES = 0;

  save_var_file_flag = 0;

#ifdef USE_THREAD
  gsm.lock();
#endif
  ++instances;
#ifdef USE_THREAD
  gsm.unlock();
#endif

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
    DEPVARS_INFO=new dependent_variables_information(NUM_DEPENDENT_VARIABLES);
    memory_allocate_error("DEPVARS_INFO", (void *) DEPVARS_INFO);
  }

  if (x > 0)
    _fp = new DF_FILE(CMPDIF_BUFFER_SIZE, x);
  else
    _fp = new DF_FILE(CMPDIF_BUFFER_SIZE);

  memory_allocate_error("_fp", (void*)_fp);

  gradient_structure::fp = _fp;

#ifdef DIAG
  cerr <<" In gradient_structure::gradient_structure()\n";
  cerr <<"  ARRAY_MEMBLOCK_SIZE = " << ARRAY_MEMBLOCK_SIZE << "\n";
#endif

  {
    GRAD_LIST = new dlist;
    memory_allocate_error("GRAD_LIST", (void *) GRAD_LIST);
  }
  {
    ARR_LIST1 = new arr_list;
    memory_allocate_error("ARR_LIST1", (void *) ARR_LIST1);
  }

   void* temp_ptr = NULL;
#ifdef __ZTC__
   if ((temp_ptr = farmalloc(ARRAY_MEMBLOCK_SIZE)) == 0)
#else
   if ((temp_ptr = (void*)malloc(ARRAY_MEMBLOCK_SIZE)) == 0)
#endif
   {
     cerr << "insufficient memory to allocate space for ARRAY_MEMBLOCKa\n";
     ad_exit(1);
   }

   ARR_LIST1->ARRAY_MEMBLOCK_BASE = temp_ptr;

   const size_t adjustment = (8 -((size_t)ARR_LIST1->ARRAY_MEMBLOCK_BASE.ptr) % 8) % 8;
   ARR_LIST1->ARRAY_MEMBLOCK_BASE.adjust(adjustment);

  if (x > 0)
    _GRAD_STACK1 = new grad_stack(gradient_structure::GRADSTACK_BUFFER_SIZE, x);
  else
    _GRAD_STACK1 = new grad_stack();
  memory_allocate_error("_GRAD_STACK1", _GRAD_STACK1);
  hessian_ptr = (double*)_GRAD_STACK1->true_ptr_first;
  gradient_structure::GRAD_STACK1 = _GRAD_STACK1;

#ifdef DIAG
   cout << "_GRAD_STACK1= "<< _farptr_tolong(_GRAD_STACK1)<<"\n";
#endif

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

     INDVAR_LIST->address = new double * [ (size_t) MAX_NVAR_OFFSET];
     memory_allocate_error("INDVAR_LIST->address",INDVAR_LIST->address);
   }

  _instance = this;

  //allocate_dvariable_space();
  if (true)
  {
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
  else
  {
    RETURN_ARRAYS = nullptr;
    RETURN_ARRAYS_PTR = 0;
    MIN_RETURN = nullptr;
    MAX_RETURN = nullptr;
    RETURN_PTR = nullptr;
    RETURN_PTR_CONTAINER = nullptr;
  }
}
dvariable* gradient_structure::next_RETURN_PTR()
{
  /*
  if (++_instance->RETURN_PTR > _instance->MAX_RETURN)
    _instance->RETURN_PTR = _instance->MIN_RETURN;

  return _instance->RETURN_PTR;
  */
  return _instance->RETURN_PTR == _instance->MAX_RETURN ? _instance->RETURN_PTR = _instance->MIN_RETURN : ++_instance->RETURN_PTR;
}

/**
Increments gradient_structure::RETURN_ARRAYS_PTR.
Must be called on entry to any function that returns a variable object.
Calls must balance calls to void RETURN_ARRAYS_DECREMENT(void).
\ingroup RA
*/
void RETURN_ARRAYS_INCREMENT()
{
  gradient_structure::get()->RETURN_ARRAYS_INCREMENT();
}
void gradient_structure::RETURN_ARRAYS_INCREMENT(void)
{
#if defined(THREAD_SAFE)
  pthread_mutex_lock(&mutex_return_arrays);
#endif
  RETURN_PTR_CONTAINER[RETURN_ARRAYS_PTR] = RETURN_PTR;
  if (++gradient_structure::RETURN_ARRAYS_PTR ==
    gradient_structure::NUM_RETURN_ARRAYS)
  {
    cerr << " Overflow in RETURN_ARRAYS stack -- Increase NUM_RETURN_ARRAYS\n";
    cerr << " There may be a RETURN_ARRAYS_INCREMENT()\n";
    cerr << " which is not matched by a RETURN_ARRAYS_DECREMENT()\n";
    ad_exit(24);
  }
  MIN_RETURN = RETURN_ARRAYS[RETURN_ARRAYS_PTR];
  MAX_RETURN = RETURN_ARRAYS[RETURN_ARRAYS_PTR]+
    gradient_structure::RETURN_ARRAYS_SIZE-1;
  RETURN_PTR = MIN_RETURN;
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
void RETURN_ARRAYS_DECREMENT()
{
  gradient_structure::get()->RETURN_ARRAYS_DECREMENT();
}
void gradient_structure::RETURN_ARRAYS_DECREMENT()
{
#if defined(THREAD_SAFE)
  pthread_mutex_lock(&mutex_return_arrays);
#endif
  if (RETURN_ARRAYS_PTR == 0)
  {
    cerr << " Error -- RETURN_ARRAYS_PTR is 0  \n";
    cerr << " There must be a RETURN_ARRAYS_DECREMENT()\n";
    cerr << " which is not matched by a RETURN_ARRAYS_INCREMENT()\n";
    ad_exit(24);
  }
  --RETURN_ARRAYS_PTR;

  MIN_RETURN = RETURN_ARRAYS[RETURN_ARRAYS_PTR];
  MAX_RETURN = RETURN_ARRAYS[RETURN_ARRAYS_PTR]+
    gradient_structure::RETURN_ARRAYS_SIZE-1;
  RETURN_PTR = RETURN_PTR_CONTAINER[RETURN_ARRAYS_PTR];

#if defined(THREAD_SAFE)
  pthread_mutex_unlock(&mutex_return_arrays);
#endif
}
/**
Destructor
*/
gradient_structure::~gradient_structure()
{
  _instance = this;

  NVAR = 0;
  if (RETURN_ARRAYS != NULL)
  {
     for (unsigned int i = 0; i < NUM_RETURN_ARRAYS; ++i)
     {
       delete [] RETURN_ARRAYS[i];
       RETURN_ARRAYS[i] = NULL;
     }
     delete [] RETURN_ARRAYS;
     RETURN_ARRAYS = NULL;
     delete [] RETURN_PTR_CONTAINER;
     RETURN_PTR_CONTAINER = NULL;
  }
  if (INDVAR_LIST != NULL)
  {
     delete [] INDVAR_LIST->address;
     delete INDVAR_LIST;
     INDVAR_LIST = NULL;
  }
  if (_GRAD_STACK1 != NULL)
  {
    delete _GRAD_STACK1;
    _GRAD_STACK1 = NULL;
  }
  gradient_structure::GRAD_STACK1 = nullptr;

  if (ARR_LIST1 != NULL)
  {
    delete ARR_LIST1;
    ARR_LIST1 = NULL;
  }
  if (GRAD_LIST != NULL)
  {
    delete GRAD_LIST;
    GRAD_LIST = NULL;
  }

#ifdef USE_THREAD
  gsm.lock();
#endif
  --instances;
#ifdef USE_THREAD
  gsm.unlock();
#endif

  if (DEPVARS_INFO==NULL)
  {
    null_ptr_err_message();
    ad_exit(1);
  }

  delete DEPVARS_INFO;
  DEPVARS_INFO=NULL;

  if (_fp == NULL)
  {
    cerr << "Trying to close stream referenced by a NULL pointer\n"
            " in ~gradient_structure\n";
    ad_exit(1);
  }

  delete _fp;
  _fp = NULL;

  gradient_structure::fp = nullptr;

  _instance = nullptr;

  cleanup_temporary_files();
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
