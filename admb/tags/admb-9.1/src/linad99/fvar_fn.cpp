/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
// file fvar_fn.cpp
// math.h functions involving prevariables
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


void gradfree(dlink *);

    prevariable& pow(_CONST prevariable& v1, CGNU_DOUBLE u)
    {
      #ifdef SAFE_ARRAYS
        if (v1.v->x == 0)
        {
          cerr << "Error -- base = 0 in function"
            " prevariable& pow(_CONST prevariable& v1, CGNU_DOUBLE u)" << endl;
        }
      #endif
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
	gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      double x,y;
      x=::pow(v1.v->x,u-1);
      y=x* v1.v->x;
      gradient_structure::RETURN_PTR->v->x=y;
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
		       &(v1.v->x), u * x );
      return(*gradient_structure::RETURN_PTR);
    }


 void prevariable::initialize(void)
 {
   *this = 0.0;
 }


 prevariable& sin(_CONST prevariable& v1)
 {
   if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
     gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=::sin(v1.v->x);
   gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x), &(v1.v->x),
			     ::cos(v1.v->x) );
   return(*gradient_structure::RETURN_PTR);
 }

 prevariable& sigmoid(_CONST prevariable& v1)
 {
   if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
     gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
   double tmp=v1.v->x;

   //gradient_structure::RETURN_PTR->v->x=atan(tmp)/1.5708;
      gradient_structure::RETURN_PTR->v->x=::atan(tmp)/2.8;

   gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x), &(v1.v->x),
 //                1./((1.+tmp*tmp)*1.5708));
		   1./((1.+tmp*tmp)*2.8));
   return(*gradient_structure::RETURN_PTR);
 }


    /** \ingroup misc
    Absolute value. Simple overload of standard C library function. 
    Not differentiable and should not be used in cases where an
    independent variable is expected to change sign. 
    Use \ref sfabs in such cases.
    \param v1 Indpendent variable \f$x\f$
    \return \f$|x|\f$
    */
    prevariable& fabs(_CONST prevariable& v1)
    {
      double tmp;

     if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
       gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      tmp=v1.v->x;
      (gradient_structure::RETURN_PTR->v)->x=fabs(tmp);
      if (tmp >=0)
      {
	gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
					    &(v1.v->x),1);
      }
      else
      {
	gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
					    &(v1.v->x),-1);
      }
      return(*gradient_structure::RETURN_PTR);
    }

    /** \ingroup misc
    Smooth absolute value. 
    Uses thrid order polynomial to interpolate between += 0.001.
    Derivatives correct for all values of indpendent variable != 0.
    \param v1 Indpendent variable \f$x\f$
    \return \f$|x|\f$
    */
    prevariable& sfabs(_CONST prevariable& v1)
    {
      #define cutoff 0.001 //  h
      #define cutoff2 0.000001
      double a = 2./cutoff; // 2.0/h
      double b = 1./cutoff2; // 1.0/(h*h)

      double tmp,tmp1,t2;

      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
	gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;

      tmp1=v1.v->x;
      tmp=::fabs(tmp1);
      if (tmp > cutoff)
      {
	gradient_structure::RETURN_PTR->v->x=tmp;
	if (tmp1 >=0)
	{
	  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
					    &(v1.v->x),1);
	}
	else
	{
	  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
					    &(v1.v->x),-1);
	}
      }
      else
      {
	t2=tmp*tmp;

	if (tmp1 >=0)
	{
	  gradient_structure::RETURN_PTR->v->x=t2*(a-b*tmp1);
	  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
			 &(v1.v->x),tmp*(2*a-3*b*tmp1) );
	}
	else
	{
	  gradient_structure::RETURN_PTR->v->x=t2*(a+b*tmp1);
	  gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
			&(v1.v->x),tmp1*(2*a+3*b*tmp1) );
	}
      }
      return(*gradient_structure::RETURN_PTR);
    }



    prevariable& cos(_CONST prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
	gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=::cos(v1.v->x);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
				    &(v1.v->x),-::sin(v1.v->x) );
      return(*gradient_structure::RETURN_PTR);
    }

    prevariable& log(_CONST prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
	gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=::log(v1.v->x);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,&(gradient_structure::RETURN_PTR->v->x),
				    &(v1.v->x),1./(v1.v->x) );
      return(*gradient_structure::RETURN_PTR);
    }

    prevariable& log10(_CONST prevariable& v1)
    {
      if (++gradient_structure::RETURN_PTR > gradient_structure::MAX_RETURN)
	gradient_structure::RETURN_PTR = gradient_structure::MIN_RETURN;
      gradient_structure::RETURN_PTR->v->x=::log10(v1.v->x);
      gradient_structure::GRAD_STACK1->set_gradient_stack(default_evaluation,
        &(gradient_structure::RETURN_PTR->v->x),&(v1.v->x),1./(v1.v->x)/2.3025851 );
      return(*gradient_structure::RETURN_PTR);
    }

