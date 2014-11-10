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
#  include <io.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
  #define lseek _lseek
  #define  read _read
  #define write _write
#else
  #include <iostream>
  using namespace std;
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
    int lseek(int, int, int);
    int read(int, char*, int);
  };
#endif

#include <math.h>

#ifndef OPT_LIB
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
void funnel_gradcalc(void)
{
#  ifdef NO_DERIVS
     if (gradient_structure::no_derivatives)
     {
       return;
     }
#  endif
  gradient_structure::TOTAL_BYTES = 0;
  gradient_structure::PREVIOUS_TOTAL_BYTES=0;
  if(!gradient_structure::instances)
  {
    return;
  }

   gradient_structure::GRAD_STACK1->_GRADFILE_PTR =
              gradient_structure::GRAD_STACK1->gradfile_handle();

  int& _GRADFILE_PTR=gradient_structure::GRAD_STACK1->_GRADFILE_PTR;

  off_t lpos = lseek(_GRADFILE_PTR,0L,SEEK_CUR);

  if(gradient_structure::GRAD_STACK1->ptr
       <= gradient_structure::GRAD_STACK1->ptr_first)
  {
#ifdef SAFE_ALL
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

  gradient_structure::GRAD_STACK1->ptr--;

  for (unsigned int i=0; i<gradient_structure::GRAD_LIST->nlinks; i++)
  {
    * (double*) (gradient_structure::GRAD_LIST->dlink_addresses[i]) = 0;
  }

  double_and_int* tmp =
    (double_and_int*)gradient_structure::ARRAY_MEMBLOCK_BASE;

     unsigned long int max_last_offset =
       gradient_structure::ARR_LIST1->get_max_last_offset();

     unsigned int size = sizeof(double_and_int );

  double * zptr;

   for (unsigned int i = 0; i < (max_last_offset/size); i++)
   {
     tmp->x = 0;
#if defined (__ZTC__)
     tmp = (double_and_int*)_farptr_norm((void*)(++tmp));
#else
     tmp++;
#endif
   }

    *gradient_structure::GRAD_STACK1->ptr->dep_addr = 1;
    zptr = gradient_structure::GRAD_STACK1->ptr->dep_addr;

int break_flag=1;
int funnel_flag=0;

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
      if (!gradient_structure::GRAD_STACK1->ptr->func)
      {
        funnel_flag=1;
        break;
      }
      else
        (*(gradient_structure::GRAD_STACK1->ptr->func))();
    }

  #endif
   if (funnel_flag) break;

  // back up the file one buffer size and read forward
  off_t offset = sizeof(grad_stack_entry)
    * gradient_structure::GRAD_STACK1->length;
  lpos = lseek(gradient_structure::GRAD_STACK1->_GRADFILE_PTR,
    -offset, SEEK_CUR);

  break_flag=gradient_structure::GRAD_STACK1->read_grad_stack_buffer(lpos);
}  while (break_flag); // do

 {
   if (lpos<0)
   {
     #ifdef GRAD_DIAG
      off_t ttmp =
     #endif
      lseek(gradient_structure::GRAD_STACK1->_GRADFILE_PTR, 0,SEEK_CUR);

     #ifdef GRAD_DIAG
      cout << "Offset in file at end of gradcalc is " << ttmp
           << " bytes from the beginning\n";
     #endif
   }
 }

  //if (gradient_structure::save_var_flag)
  {
    unsigned long bytes_needed = min(
      gradient_structure::ARR_LIST1->get_last_offset() + 1,
      gradient_structure::ARRAY_MEMBLOCK_SIZE);
    size_t _dsize = bytes_needed/sizeof(double);
#ifndef OPT_LIB
    assert(_dsize <= INT_MAX);
#endif
    int dsize = (int)_dsize;

    //dvector dtmp(0,dsize-1);
    //memcpy((char*)&(dtmp(0)),(char*)gradient_structure::ARRAY_MEMBLOCK_BASE,
      //dsize*sizeof(double));

    double* dptr=(double*) gradient_structure::ARRAY_MEMBLOCK_BASE;
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
      save_double_value(*dptr);
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
        save_double_value(*dptr);
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
    save_int_value(dcount);

    for (int i=0;i<ii;i++)
    {
      save_int_value(offset(i));
    }
    save_int_value(ii);

    unsigned int ssize=gradient_structure::GRAD_LIST->nlinks;
#ifndef OPT_LIB
    assert(ssize > 0);
    assert(ssize <= INT_MAX);
#endif
    dvector stmp(0,(int)(ssize-1));

    for (int i=0; i<gradient_structure::GRAD_LIST->nlinks; i++)
    {
      memcpy((char*)&(stmp(i)),
        gradient_structure::GRAD_LIST->dlink_addresses[i],sizeof(double));
    }
    //dtmp.save_dvector_value();
    //dtmp.save_dvector_position();
    stmp.save_dvector_value();
    stmp.save_dvector_position();

    // save the address of the dependent variable for the funnel
    int wsize=sizeof(double_and_int*);
    gradient_structure::get_fp()->fwrite(&zptr,size_t(wsize));
    save_identifier_string("ae");

    gradient_structure::GRAD_STACK1->set_gradient_stack(funnel_derivatives);
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
  verify_identifier_string("ae");
  prevariable_position deppos=restore_prevariable_position();
  dvector_position stmp_pos=restore_dvector_position();
  dvector stmp=restore_dvector_value(stmp_pos);
  //dvector_position dtmp_pos=restore_dvector_position();
  //dvector dtmp=restore_dvector_value(dtmp_pos);
  int ii=restore_int_value();
  int i;
  int ip=ii;
  if (!ip) ip=1;
  ivector offset(0,ip);
  offset(ip)=0;
  //ivector offset(0,ip-1);
  for (i=ii-1;i>=0;i--)
  {
    offset(i)=restore_int_value();
  }
  int dcount=restore_int_value();
  int dc=dcount;
  if (!dc) dc=1;
  dvector dx(0,dc-1);
  for (i=dcount-1;i>=0;i--)
  {
    dx(i)=restore_double_value();
  }

  verify_identifier_string("ue");

  double df = restore_prevariable_derivative(deppos);
  double * dptr= (double *) gradient_structure::ARRAY_MEMBLOCK_BASE;

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
  for (i=0;i<smax;i++)
  {
    if (!ISZERO(stmp(i)))
    {
      *(double*)(gradient_structure::GRAD_LIST->dlink_addresses[i])
        +=stmp(i)*df;
    }
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

