/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"


  dvar_vector fabs(_CONST dvar_vector& t1)
  {
     RETURN_ARRAYS_INCREMENT();

     dvar_vector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=fabs(t1.elem(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return(tmp);
  }

  dvector value(_CONST dvar_vector& t1)
  {
     RETURN_ARRAYS_INCREMENT();

     dvector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=value(t1.elem(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return(tmp);
  }

  dvariable norm(_CONST dvar_vector& t1)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable tmp;
    tmp=t1*t1;
    if (value(tmp)>0.0)
    {
     tmp=pow(tmp,.5);
    }
    RETURN_ARRAYS_DECREMENT();
    return(tmp);
  }

  dvariable norm2(_CONST dvar_vector& t1)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable tmp;
    tmp=t1*t1;
    RETURN_ARRAYS_DECREMENT();
    return(tmp);
  }


  dvar_vector sfabs(_CONST dvar_vector& t1)
  {
     RETURN_ARRAYS_INCREMENT();

     dvar_vector tmp(t1.indexmin(),t1.indexmax());

     for (int i=t1.indexmin(); i<=t1.indexmax(); i++)
     {
       tmp.elem(i)=sfabs(t1.elem(i));
     }
     RETURN_ARRAYS_DECREMENT();
     return(tmp);
  }
