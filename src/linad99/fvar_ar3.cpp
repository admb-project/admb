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

/**
 * Description not yet available.
 * \param
 */
dvar_vector fabs(const dvar_vector& t1)
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

/**
 * Description not yet available.
 * \param
 */
dvector value(const dvar_vector& t1)
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

/**
 * Description not yet available.
 * \param
 */
dvariable norm(const dvar_vector& t1)
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

/**
 * Description not yet available.
 * \param
 */
dvariable norm2(const dvar_vector& t1)
  {
    RETURN_ARRAYS_INCREMENT();
    dvariable tmp;
    tmp=t1*t1;
    RETURN_ARRAYS_DECREMENT();
    return(tmp);
  }
dvariable sumsq(const dvar_vector& t1) {return(norm2(t1));}

/**
 * Description not yet available.
 * \param
 */
dvar_vector sfabs(const dvar_vector& t1)
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
