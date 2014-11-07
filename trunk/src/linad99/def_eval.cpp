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

#include <stdio.h>
#include <stdlib.h>

#ifdef __SUN__
  #include <iostream.h>
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

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

#if defined (__WAT32__)
  #include <io.h>
#endif

#include <math.h>

#ifdef ISZERO
  #undef ISZERO
#endif
#define ISZERO(d) ((d)==0.0)
//#define XXX 3.70255042e-17

  //ofstream gradlog("grad.log");

/**
 * Description not yet available.
 * \param
 */
  void default_evaluation(void)
  {
    // checks to see how many independent variables there are
    grad_stack_entry * grad_ptr = gradient_structure::GRAD_STACK1->ptr;
    double * zptr = grad_ptr->dep_addr;
    double z = *zptr;
    *zptr = 0;
    // Check to see if first independent variable is a NULL adress
    if  ( grad_ptr->ind_addr1 )
    {
      * grad_ptr->ind_addr1 += z * grad_ptr->mult1 ;
        //gradlog <<  setprecision(13) << * grad_ptr->ind_addr1  << endl;
        //if (fabs(* grad_ptr->ind_addr1+XXX)<1.e-16)
         // cout <<  setprecision(13) << * grad_ptr->ind_addr1  << endl;
#if defined(USE_DDOUBLE)
      if  ( grad_ptr->mult2 !=0)
#else
      if  (!ISZERO(grad_ptr->mult2))
#endif
      {
        * grad_ptr->ind_addr2 += z * grad_ptr->mult2 ;
        //gradlog <<  setprecision(13) << * grad_ptr->ind_addr2  << endl;
        //if (fabs(* grad_ptr->ind_addr2+XXX)<1.e-16)
         // cout <<  setprecision(13) << * grad_ptr->ind_addr2  << endl;
      }
    }
  }

/**
 * Description not yet available.
 * \param
 */
  void default_evaluation1(void)
  {
    // there is one independent variable
    grad_stack_entry * grad_ptr = gradient_structure::GRAD_STACK1->ptr;
    double z = * grad_ptr->dep_addr;
    * grad_ptr->dep_addr=0.;
    * grad_ptr->ind_addr1 += z;
    //gradlog <<  setprecision(13) << * grad_ptr->ind_addr1  << endl;
    //if (fabs(* grad_ptr->ind_addr1+XXX)<1.e-16)
    //cout << setscientific() <<  setprecision(13) << * grad_ptr->ind_addr1
    //<< endl;
  }

/**
 * Description not yet available.
 * \param
 */
  void default_evaluation1m(void)
  {
    // there is one independent variable
    grad_stack_entry * grad_ptr = gradient_structure::GRAD_STACK1->ptr;
    double z = * grad_ptr->dep_addr;
    * grad_ptr->dep_addr=0.;
    * grad_ptr->ind_addr1 -= z;
    //gradlog <<  setprecision(13) << * grad_ptr->ind_addr1  << endl;
     //   if (fabs(* grad_ptr->ind_addr1+XXX)<1.e-16)
      //    cout <<  setprecision(13) << * grad_ptr->ind_addr1  << endl;
  }

/**
 * Description not yet available.
 * \param
 */
  void default_evaluation0(void)
  {
    // there is one independent variable
    * gradient_structure::GRAD_STACK1->ptr->dep_addr=0.;
  }

/**
 * Description not yet available.
 * \param
 */
  void default_evaluation2(void)
  {
    //char ch;
    // there is one independent variable
    grad_stack_entry * grad_ptr = gradient_structure::GRAD_STACK1->ptr;
    //cout << setprecision(16) << *grad_ptr->dep_addr << endl;
    //cout << setprecision(16) << *grad_ptr->ind_addr1 << endl;
    //cout << setprecision(16) << grad_ptr->mult1 << endl;
    //cin >> ch;
    double z = * grad_ptr->dep_addr;
    * grad_ptr->dep_addr=0.;
    * grad_ptr->ind_addr1 += z * grad_ptr->mult1 ;
    //gradlog <<  setprecision(13) << * grad_ptr->ind_addr1  << endl;
     //   if (fabs(* grad_ptr->ind_addr1+XXX)<1.e-16)
      //    cout <<  setprecision(13) << * grad_ptr->ind_addr1  << endl;
  }

/**
 * Description not yet available.
 * \param
 */
  void default_evaluation3(void)
  {
    // there are two independent variables
    grad_stack_entry * grad_ptr = gradient_structure::GRAD_STACK1->ptr;
    double z = * grad_ptr->dep_addr;
    * grad_ptr->dep_addr=0.;
    * grad_ptr->ind_addr1 += z * grad_ptr->mult1 ;
    * grad_ptr->ind_addr2 += z * grad_ptr->mult2 ;
    //gradlog <<  setprecision(13) << * grad_ptr->ind_addr1  << endl;
     //   if (fabs(* grad_ptr->ind_addr1+XXX)<1.e-16)
      //    cout <<  setprecision(13) << * grad_ptr->ind_addr1  << endl;
  }

/**
 * Description not yet available.
 * \param
 */
  void default_evaluation3ind(void)
  {
    // there are three independent variables
    grad_stack_entry *  grad_ptr = gradient_structure::GRAD_STACK1->ptr;

    double mult3=grad_ptr->mult1 ;
    double * ind_addr3=grad_ptr->ind_addr1;
    if (gradient_structure::GRAD_STACK1->ptr-- ==
      gradient_structure::GRAD_STACK1->ptr_first)
    {
      // \todo Need test
      // back up the file one buffer size and read forward
      off_t offset = sizeof(grad_stack_entry)
        * gradient_structure::GRAD_STACK1->length;
      off_t lpos=lseek(gradient_structure::GRAD_STACK1->_GRADFILE_PTR,
        -offset, SEEK_CUR);

      gradient_structure::GRAD_STACK1->read_grad_stack_buffer(lpos);
      //gradient_structure::GRAD_STACK1->ptr++;
    }

    grad_ptr = gradient_structure::GRAD_STACK1->ptr;
    double z = * grad_ptr->dep_addr;
    * grad_ptr->dep_addr=0.;
    * grad_ptr->ind_addr1 += z * grad_ptr->mult1 ;
    * grad_ptr->ind_addr2 += z * grad_ptr->mult2 ;
    * ind_addr3 += z * mult3 ;
  }

/**
 * Description not yet available.
 * \param
 */
  void default_evaluation4ind(void)
  {
    // there are three independent variables
    grad_stack_entry *  grad_ptr = gradient_structure::GRAD_STACK1->ptr;

    double * ind_addr3=grad_ptr->ind_addr1;
    double mult3=grad_ptr->mult1 ;
    double * ind_addr4=grad_ptr->ind_addr2;
    double mult4=grad_ptr->mult2 ;
    if (gradient_structure::GRAD_STACK1->ptr-- ==
      gradient_structure::GRAD_STACK1->ptr_first)
    {
      // \todo Need test
      // back up the file one buffer size and read forward
      off_t offset = sizeof(grad_stack_entry)
        * gradient_structure::GRAD_STACK1->length;
      off_t lpos=lseek(gradient_structure::GRAD_STACK1->_GRADFILE_PTR,
        -offset, SEEK_CUR);

      gradient_structure::GRAD_STACK1->read_grad_stack_buffer(lpos);
      //gradient_structure::GRAD_STACK1->ptr++;
    }

    grad_ptr = gradient_structure::GRAD_STACK1->ptr;
    double z = * grad_ptr->dep_addr;
    * grad_ptr->dep_addr=0.;
    * grad_ptr->ind_addr1 += z * grad_ptr->mult1 ;
    * grad_ptr->ind_addr2 += z * grad_ptr->mult2 ;
    * ind_addr3 += z * mult3 ;
    * ind_addr4 += z * mult4 ;
    //gradlog <<  setprecision(13) << * grad_ptr->ind_addr1  << endl;
     //   if (fabs(* grad_ptr->ind_addr1+XXX)<1.e-16)
      //    cout <<  setprecision(13) << * grad_ptr->ind_addr1  << endl;
    //gradlog <<  setprecision(13) << * grad_ptr->ind_addr2  << endl;
     //   if (fabs(* grad_ptr->ind_addr2+XXX)<1.e-16)
      //    cout <<  setprecision(13) << * grad_ptr->ind_addr2  << endl;
    //gradlog <<  setprecision(13) << * ind_addr3  << endl;
     //   if (fabs(* ind_addr3+XXX)<1.e-16)
      //    cout <<  setprecision(13) << * ind_addr3  << endl;
    //gradlog <<  setprecision(13) << * ind_addr4  << endl;
     //   if (fabs(* ind_addr4+XXX)<1.e-16)
      //    cout <<  setprecision(13) << * ind_addr4  << endl;
  }

/**
 * Description not yet available.
 * \param
 */
  void default_evaluation4(void)
  {
    // there are two independent variables
    grad_stack_entry * grad_ptr = gradient_structure::GRAD_STACK1->ptr;
    double z = * grad_ptr->dep_addr;
    * grad_ptr->dep_addr=0.;
    * grad_ptr->ind_addr1 += z;
    * grad_ptr->ind_addr2 += z;
  }

/**
 * Description not yet available.
 * \param
 */
  void default_evaluation4m(void)
  {
    // there are two independent variables
    grad_stack_entry * grad_ptr = gradient_structure::GRAD_STACK1->ptr;
    double z = * grad_ptr->dep_addr;
    * grad_ptr->dep_addr=0.;
    * grad_ptr->ind_addr1 += z;
    * grad_ptr->ind_addr2 -= z;
  }
