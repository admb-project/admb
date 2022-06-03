/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 \file
 Overloads of math library functions for variable arguments.
 */
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
  #include <iomanip.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
  #include <iomanip.hpp>
#endif

#include <stdio.h>
#include <math.h>

/**
 * Description not yet available.
 * \param
 */
prevariable& pow(const prevariable& v1, const double u)
    {
#ifndef OPT_LIB
        if (v1.v->x == 0)
        {
          cerr << "Error -- base = 0 in function"
            " prevariable& pow(const prevariable& v1, const double u)" << endl;
        }
#endif
      gradient_structure* gs = gradient_structure::get();
      dvariable* RETURN_PTR = gs->RETURN_PTR == gs->MAX_RETURN ? gs->RETURN_PTR = gs->MIN_RETURN : ++gs->RETURN_PTR;

      double x=::pow(v1.v->x,u-1);
      double y=x* v1.v->x;
      RETURN_PTR->v->x=y;
      gs->GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(RETURN_PTR->v->x), &(v1.v->x), u * x );

      return *RETURN_PTR;
    }

/**
 * Description not yet available.
 * \param
 */
 void prevariable::initialize(void)
 {
   *this = 0.0;
 }

/**
 * Description not yet available.
 * \param
 */
 prevariable& sin(const prevariable& v1)
 {
   gradient_structure* gs = gradient_structure::get();
   dvariable* RETURN_PTR = gs->RETURN_PTR == gs->MAX_RETURN ? gs->RETURN_PTR = gs->MIN_RETURN : ++gs->RETURN_PTR;

   RETURN_PTR->v->x=::sin(v1.v->x);
   gs->GRAD_STACK1->set_gradient_stack(default_evaluation,
     &(RETURN_PTR->v->x), &(v1.v->x), ::cos(v1.v->x) );

   return *RETURN_PTR;
 }

/**
 * Description not yet available.
 * \param
 */
prevariable& sigmoid(const prevariable& v1)
 {
   gradient_structure* gs = gradient_structure::get();
   dvariable* RETURN_PTR = gs->RETURN_PTR == gs->MAX_RETURN ? gs->RETURN_PTR = gs->MIN_RETURN : ++gs->RETURN_PTR;

   double tmp=v1.v->x;

   //gradient_structure::RETURN_PTR->v->x=atan(tmp)/1.5708;
   RETURN_PTR->v->x=::atan(tmp)/2.8;

   gs->GRAD_STACK1->set_gradient_stack(default_evaluation,
     &(RETURN_PTR->v->x), &(v1.v->x),
 //                1./((1.+tmp*tmp)*1.5708));
                   1./((1.+tmp*tmp)*2.8));
   return *RETURN_PTR;
 }


    /** \ingroup misc
    Absolute value. Simple overload of standard C library function.
    Not differentiable and should not be used in cases where an
    independent variable is expected to change sign.
    Use \ref sfabs in such cases.
    \param v1 Indpendent variable \f$x\f$
    \return \f$|x|\f$
    */
prevariable& fabs(const prevariable& v1)
    {
      gradient_structure* gs = gradient_structure::get();
      dvariable* RETURN_PTR = gs->RETURN_PTR == gs->MAX_RETURN ? gs->RETURN_PTR = gs->MIN_RETURN : ++gs->RETURN_PTR;

      double tmp=v1.v->x;
      RETURN_PTR->v->x=fabs(tmp);
      gs->GRAD_STACK1->set_gradient_stack(
        default_evaluation,&(RETURN_PTR->v->x),
        &(v1.v->x), tmp >= 0.0 ? 1.0 : -1.0);

      return *RETURN_PTR;
    }

    /** \ingroup misc
    Smooth absolute value.
    Uses thrid order polynomial to interpolate between += 0.001.
    Derivatives correct for all values of indpendent variable != 0.
    \param v1 Indpendent variable \f$x\f$
    \return \f$|x|\f$
    */
prevariable& sfabs(const prevariable& v1)
    {
      #define cutoff 0.001 //  h
      #define cutoff2 0.000001
      double a = 2./cutoff; // 2.0/h
      double b = 1./cutoff2; // 1.0/(h*h)

      gradient_structure* gs = gradient_structure::get();
      dvariable* RETURN_PTR = gs->RETURN_PTR == gs->MAX_RETURN ? gs->RETURN_PTR = gs->MIN_RETURN : ++gs->RETURN_PTR;

      double tmp1=v1.v->x;
      double tmp=::fabs(tmp1);

      if (tmp > cutoff)
      {
        RETURN_PTR->v->x=tmp;
        if (tmp1 >=0)
        {
          gs->GRAD_STACK1->set_gradient_stack(
            default_evaluation,&(RETURN_PTR->v->x),
            &(v1.v->x),1);
        }
        else
        {
          gs->GRAD_STACK1->set_gradient_stack(
            default_evaluation,&(RETURN_PTR->v->x),
            &(v1.v->x),-1);
        }
      }
      else
      {
        double t2 = tmp * tmp;
        if (tmp1 >=0)
        {
          RETURN_PTR->v->x=t2*(a-b*tmp1);
          gs->GRAD_STACK1->set_gradient_stack(
            default_evaluation,&(RETURN_PTR->v->x),
            &(v1.v->x),tmp*(2*a-3*b*tmp1) );
        }
        else
        {
          RETURN_PTR->v->x=t2*(a+b*tmp1);
          gs->GRAD_STACK1->set_gradient_stack(
            default_evaluation,&(RETURN_PTR->v->x),
            &(v1.v->x),tmp1*(2*a+3*b*tmp1));
        }
      }
      return *RETURN_PTR;
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& cos(const prevariable& v1)
    {
      gradient_structure* gs = gradient_structure::get();
      dvariable* RETURN_PTR = gs->RETURN_PTR == gs->MAX_RETURN ? gs->RETURN_PTR = gs->MIN_RETURN : ++gs->RETURN_PTR;

      RETURN_PTR->v->x=::cos(v1.v->x);
      gs->GRAD_STACK1->set_gradient_stack(
        default_evaluation,&(RETURN_PTR->v->x),
        &(v1.v->x),-::sin(v1.v->x) );

      return *RETURN_PTR;
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& log(const prevariable& v1)
    {
      gradient_structure* gs = gradient_structure::get();
      dvariable* RETURN_PTR = gs->RETURN_PTR == gs->MAX_RETURN ? gs->RETURN_PTR = gs->MIN_RETURN : ++gs->RETURN_PTR;

      RETURN_PTR->v->x=::log(v1.v->x);
      gs->GRAD_STACK1->set_gradient_stack(
        default_evaluation,&(RETURN_PTR->v->x),
        &(v1.v->x),1./(v1.v->x) );

      return *RETURN_PTR;
    }

/**
 * Description not yet available.
 * \param
 */
prevariable& log10(const prevariable& v1)
    {
      gradient_structure* gs = gradient_structure::get();
      dvariable* RETURN_PTR = gs->RETURN_PTR == gs->MAX_RETURN ? gs->RETURN_PTR = gs->MIN_RETURN : ++gs->RETURN_PTR;

      RETURN_PTR->v->x=::log10(v1.v->x);
      gs->GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(gs->RETURN_PTR->v->x),&(v1.v->x),
        1./(v1.v->x)/2.3025851);

      return *RETURN_PTR;
    }
