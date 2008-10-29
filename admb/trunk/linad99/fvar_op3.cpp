
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

#include <math.h>
#include <stdio.h>


void gradfree(dlink *);


    int prevariable::operator ==( CGNU_DOUBLE v1) _CONST
    {
      return(v->x==v1);
    }

    int prevariable::operator <=( CGNU_DOUBLE v1) _CONST
    {
      return(v->x<=v1);
    }

    int prevariable::operator <( CGNU_DOUBLE v1) _CONST
    {
      return(v->x<v1);
    }

    int prevariable::operator >( CGNU_DOUBLE v1) _CONST
    {
      return(v->x>v1);
    }

    int prevariable::operator >=( CGNU_DOUBLE v1) _CONST
    {
      return(v->x >=v1);
    }

    int prevariable::operator !=( CGNU_DOUBLE v1) _CONST
    {
      return(v->x!=v1);
    }

#undef HOME_VERSION
