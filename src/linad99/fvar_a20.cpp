/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Assignment operators for dvar_vector for types dvar_vector, prevariable and double
*/
#include "fvar.hpp"
#if defined(__TURBOC__)
  #pragma hdrstop
   #include <alloc.h>
#endif

#include <stdlib.h>

void dv_assign(void);

#ifdef _MSC_VER
  #include <memory.h>
#endif

#ifdef DEBUG
  #include <cassert>
#endif

/**
Assign values from other t to dvar_vector.

@param t other dvar_vector
*/
dvar_vector& dvar_vector::operator=(const dvar_vector& t)
 {
   if (!(*this))
   {
     allocatec(t);
   }
#if defined (AD_FAST_ASSIGN)
   else if (!(shape->ncopies))
   {
     deallocate();
     allocatec(t);
   }
#endif
   else
   {
     int mmin=indexmin();
     int mmax=indexmax();
#ifdef DEBUG
     assert(mmax >= mmin);
#endif
     if (mmin != t.indexmin() || mmax != t.indexmax())
     {
       cerr << " Incompatible bounds in dvar_vector& dvar_vector::operator ="
         " (const dvar_vector& t)\n";
       ad_exit(21);
     }
     if (va != t.va)
     {
       constexpr size_t sizeofdouble = sizeof(double);
       size_t size = (size_t)(mmax - mmin + 1);
       memcpy(va + mmin, t.va + mmin, size * sizeofdouble);

       gradient_structure* gs = gradient_structure::get();
       DF_FILE* fp = gs->fp;

       // The derivative list considerations
       //save_identifier_string("bbbb");
       fp->save_dvar_vector_position(t);
       fp->save_dvar_vector_position(*this);
       //save_identifier_string("aaaa");
       gs->GRAD_STACK1->set_gradient_stack(dv_assign);
     }
   }
   return (*this);
 }

void dv_eqprev(void);

/**
Assigns all elements for dvar_vector with t. 

@param t prevariable
*/
dvar_vector& dvar_vector::operator=(const prevariable& t)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   for (int i=mmin; i<=mmax; i++)
   {
     va[i].x = value(t);
   }

   gradient_structure* gs = gradient_structure::get();
   DF_FILE* fp = gs->fp;

   // The derivative list considerations
   save_identifier_string("dddd");
   fp->save_prevariable_position(t);
   fp->save_dvar_vector_position(*this);
   save_identifier_string("ssss");
   gs->GRAD_STACK1->set_gradient_stack(dv_eqprev);
   return (*this);
 }

void dv_eqdoub(void);

/**
Assigns all elements for dvar_vector with t. 

@param t single value
*/
dvar_vector& dvar_vector::operator=(const double t)
 {
   int mmin=indexmin();
   int mmax=indexmax();
   for (int i=mmin; i<=mmax; i++)
   {
     va[i].x = t;
   }
   gradient_structure* gs = gradient_structure::get();
   DF_FILE* fp = gs->fp;

   // The derivative list considerations
   save_identifier_string("trut");
   fp->save_dvar_vector_position(*this);
   save_identifier_string("ssss");
   gs->GRAD_STACK1->set_gradient_stack(dv_eqdoub);
   return (*this);
 }
/**
Adjoint to compute gradient for dvar_vector::operator=(const double).
*/
void dv_eqdoub(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;
  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("ssss");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  verify_identifier_string("trut");
}
/**
Adjoint to compute gradient for dvar_vector::operator=(const prevariable&).
*/
void dv_eqprev(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  verify_identifier_string("ssss");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  prevariable_position t_pos=fp->restore_prevariable_position();
  verify_identifier_string("dddd");
  double dft=0.;
  for (int i=dftmp.indexmin();i<=dftmp.indexmax();i++)
  {
    //vtmp.elem(i)=t;
    dft+=dftmp.elem(i);
  }
  save_double_derivative(dft,t_pos);
}
/**
Adjoint to compute gradients for dvar_vector::operator=(const dvar_vector&)
*/
void dv_assign(void)
{
  gradient_structure* gs = gradient_structure::get();
  DF_FILE* fp = gs->fp;

  // int ierr=fsetpos(gradient_structure::get_fp(),&filepos);
  //verify_identifier_string("aaaa");
  dvar_vector_position tmp_pos=fp->restore_dvar_vector_position();
  dvector dftmp=restore_dvar_vector_derivatives(tmp_pos);
  dvar_vector_position t_pos=fp->restore_dvar_vector_position();
  //verify_identifier_string("bbbb");

  int mmin=dftmp.indexmin();
  int mmax=dftmp.indexmax();

#ifdef DEBUG
  assert(mmax >= mmin);
#endif

  dvector dft(mmin, mmax);

  constexpr size_t sizeofdouble = sizeof(double);
  size_t size = (size_t)(mmax - mmin + 1);
  memcpy(dft.get_v() + mmin, dftmp.get_v() + mmin, size * sizeofdouble);

  dft.save_dvector_derivatives(t_pos);
}
