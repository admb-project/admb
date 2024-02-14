/*
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
#  include <io.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#ifndef _MSC_VER
  #include <iostream>
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

#ifdef __SUN__
  #include <iostream.h>
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

#ifdef DEBUG
  #include <cassert>
  #include <climits>
#endif

#ifdef ISZERO
  #undef ISZERO
#endif
#define ISZERO(d) ((d)==0.0)

void funnel_derivatives(void);

#if defined(__ZTC__)
  void _far * _cdecl _farptr_norm(void _far *);
  void _far * _cdecl _farptr_fromlong(unsigned long);
  long _cdecl _farptr_tolong(void _far *);
#endif

/**
 * Description not yet available.
 * \param
 */
void funnel_gradcalc()
{
  gradient_structure* gs = gradient_structure::_instance;
  if (!gs)
  {
    cerr << "Warning: No instance of gradient data structure.\n";
    return;
  }
  gs->funnel_gradcalc();
}
void gradient_structure::funnel_gradcalc()
{
#  ifdef NO_DERIVS
     if (gradient_structure::no_derivatives)
     {
       return;
     }
#  endif

  TOTAL_BYTES = 0;
  PREVIOUS_TOTAL_BYTES=0;

  GRAD_STACK1->_GRADFILE_PTR = GRAD_STACK1->gradfile_handle();

  int& _GRADFILE_PTR = GRAD_STACK1->_GRADFILE_PTR;

  OFF_T lpos = LSEEK(_GRADFILE_PTR,0L,SEEK_CUR);

  if (GRAD_STACK1->ptr <= GRAD_STACK1->ptr_first)
  {
#ifdef DIAG
      cerr <<
        "warning -- calling funnel_gradcalc when no calculations generating"
           << endl << "derivative information have occurred" << endl;
#endif
    return;
  }    // current is one past the end so -- it

  //if (gradient_structure::save_var_flag)
  {
    gradient_structure::save_arrays();
    gradient_structure::save_variables();
  }

  GRAD_STACK1->ptr--;

  GRAD_LIST->initialize();

  double_and_int* tmp = (double_and_int*)ARR_LIST1->ARRAY_MEMBLOCK_BASE;

  constexpr size_t size = sizeof(double_and_int);

  unsigned long int local_max_last_offset = ARR_LIST1->get_max_last_offset() / size;

   for (unsigned int i = 0; i < local_max_last_offset; i++)
   {
     tmp->x = 0;
#if defined (__ZTC__)
     tmp = (double_and_int*)_farptr_norm((void*)(++tmp));
#else
     tmp++;
#endif
   }

    *GRAD_STACK1->ptr->dep_addr = 1;
    double* zptr = GRAD_STACK1->ptr->dep_addr;

int break_flag=1;
int funnel_flag=0;

do
{
  GRAD_STACK1->ptr++;
  #ifdef FAST_ASSEMBLER
    gradloop();
  #else
    grad_stack_entry * grad_ptr_first = GRAD_STACK1->ptr_first;
    while (GRAD_STACK1->ptr-- > grad_ptr_first)
    {
      if (!GRAD_STACK1->ptr->func)
      {
        funnel_flag=1;
        break;
      }
      else
        (*(GRAD_STACK1->ptr->func))();
    }

  #endif
   if (funnel_flag) break;

  // back up the file one buffer size and read forward
  OFF_T offset = (OFF_T)(sizeof(grad_stack_entry) * GRAD_STACK1->length);
  lpos = LSEEK(GRAD_STACK1->_GRADFILE_PTR, -offset, SEEK_CUR);

  break_flag = GRAD_STACK1->read_grad_stack_buffer(lpos);
}  while (break_flag); // do

 {
   if (lpos<0)
   {
     #ifdef GRAD_DIAG
      OFF_T ttmp =
     #endif
      LSEEK(GRAD_STACK1->_GRADFILE_PTR, 0,SEEK_CUR);

     #ifdef GRAD_DIAG
      cout << "Offset in file at end of gradcalc is " << ttmp
           << " bytes from the beginning\n";
     #endif
   }
 }

  constexpr size_t sizeofdouble = sizeof(double);
  //if (gradient_structure::save_var_flag)
  {
    unsigned long bytes_needed = min(
      gradient_structure::ARR_LIST1->get_last_offset() + 1,
      gradient_structure::ARRAY_MEMBLOCK_SIZE);
    size_t _dsize = bytes_needed / sizeofdouble;
#ifdef DEBUG
    assert(_dsize <= INT_MAX);
#endif
    int dsize = (int)_dsize;

    //dvector dtmp(0,dsize-1);
    //memcpy((char*)&(dtmp(0)),(char*)ARR_LIST1->ARRAY_MEMBLOCK_BASE,
      //dsize*sizeof(double));

    double* dptr=(double*)ARR_LIST1->ARRAY_MEMBLOCK_BASE;
    dptr-=1;
    int ii=0;
    int nzero=0;
    int nnzero=0;
    int dcount=0;
    int zero_flag=0;
    ivector offset(0,dsize-1);
    save_identifier_string("ue");
    if (!ISZERO(*(++dptr)))
    {
      fp->save_double_value(*dptr);
      dcount++;
      zero_flag=0;
      offset(ii++)=0;
      nnzero++;
    }
    else
    {
      zero_flag=1;
      nzero++;
    }

    for (int i1=1;i1<dsize;i1++)
    {
      if (!ISZERO(*(++dptr)))
      {
        fp->save_double_value(*dptr);
        dcount++;
        nnzero++;
        if (zero_flag)
        {
          offset(ii++)=nzero;
          nzero=0;
          zero_flag=0;
        }
      }
      else
      {
        nzero++;
        if (!zero_flag)
        {
          offset(ii++)=nnzero;
          nnzero=0;
          zero_flag=1;
        }
      }
    }
    fp->save_int_value(dcount);

    for (int i=0;i<ii;i++)
    {
      fp->save_int_value(offset(i));
    }
    fp->save_int_value(ii);

    int nlinks = static_cast<int>(GRAD_LIST->nlinks);
#ifdef DEBUG
    assert(GRAD_LIST->nlinks <= INT_MAX);
    assert(nlinks > 0);
#endif
    dvector stmp(0, nlinks - 1);

    double* pstmpi = stmp.get_v();
    dlink** dlink_addresses = GRAD_LIST->dlink_addresses;
    for (int i=0; i < nlinks; ++i)
    {
      memcpy((char*)pstmpi, *dlink_addresses, sizeofdouble);

      ++pstmpi;
      ++dlink_addresses;
    }
    //dtmp.save_dvector_value();
    //dtmp.save_dvector_position();
    fp->save_dvector_value(stmp);
    fp->save_dvector_position(stmp);

    // save the address of the dependent variable for the funnel
    size_t wsize=sizeof(double_and_int*);
    fp->fwrite(&zptr, wsize);
    save_identifier_string("ae");

    GRAD_STACK1->set_gradient_stack(funnel_derivatives);
    gradient_structure::restore_arrays();
    gradient_structure::restore_variables();
  }
}

/**
 * Description not yet available.
 * \param
 */
void funnel_derivatives(void)
{
  gradient_structure* gs = gradient_structure::_instance;
  DF_FILE* fp = gradient_structure::fp;

  verify_identifier_string("ae");
  prevariable_position deppos=fp->restore_prevariable_position();
  dvector_position stmp_pos=fp->restore_dvector_position();
  dvector stmp=fp->restore_dvector_value(stmp_pos);
  //dvector_position dtmp_pos=fp->restore_dvector_position();
  //dvector dtmp=restore_dvector_value(dtmp_pos);
  int ii=fp->restore_int_value();
  int i;
  int ip=ii;
  if (!ip) ip=1;
  ivector offset(0,ip);
  offset(ip)=0;
  //ivector offset(0,ip-1);
  for (i=ii-1;i>=0;i--)
  {
    offset(i)=fp->restore_int_value();
  }
  int dcount=fp->restore_int_value();
  int dc=dcount;
  if (!dc) dc=1;
  dvector dx(0,dc-1);
  for (i=dcount-1;i>=0;i--)
  {
    dx(i)=fp->restore_double_value();
  }

  verify_identifier_string("ue");

  double df = restore_prevariable_derivative(deppos);
  double* dptr = (double*)(gs->ARR_LIST1->ARRAY_MEMBLOCK_BASE);

  //double * dd = &(dx(1));
  ii=0;
  int ic=0;
  dptr+=offset(ii++);
  for (i=0;i<dcount;i++)
  {
    *(dptr++)+=dx(i)*df;
    if (++ic==offset(ii))
    {
      if (i==dcount-1)
      {
        break;
      }
      dptr+=offset(ii+1);
      ii+=2;
      ic=0;
    }
  }

  int smax=stmp.indexmax();
  double* pstmpi = stmp.get_v();
  dlink** dlink_addresses = gs->GRAD_LIST->dlink_addresses;
  for (i=0;i<smax;i++)
  {
    if (!ISZERO(*pstmpi))
    {
      *((double*)(*dlink_addresses)) += *pstmpi * df;
    }
    ++pstmpi;
    ++dlink_addresses;
  }
}

/**
 * Description not yet available.
 * \param
 */
dvariable& funnel_dvariable::operator=(const prevariable& t)
{
  dvariable::operator = (t);
  funnel_gradcalc();
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
void ad_begin_funnel(void)
{
  gradient_structure::GRAD_STACK1->set_gradient_stack(NULL);
}

