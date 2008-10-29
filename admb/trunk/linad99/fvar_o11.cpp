

#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
// file: fvar_ops.cpp
// operators involving prevariables

#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <stdio.h>
#include <math.h>

  void df_minus_eq_pvpv(void);

    void prevariable::operator -=(_CONST prevariable& v1)
    {
      (*v).x-=(*v1.v).x;
      gradient_structure::GRAD_STACK1->set_gradient_stack(df_minus_eq_pvpv,&(v->x),
        &(v1.v->x));
    }

  void df_minus_eq_pvpv(void)
  {
    * gradient_structure::GRAD_STACK1->ptr->ind_addr1
               -= * gradient_structure::GRAD_STACK1->ptr->dep_addr;
  }

#undef HOME_VERSION
