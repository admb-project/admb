/*
 * $Id: fvar_a49.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <math.h>

/**
 * Description not yet available.
 * \param
 */
  dvariable var(_CONST dvar_vector& v)
  {
    dvariable tmp;
    RETURN_ARRAYS_INCREMENT();
    tmp=norm(v)/sqrt(double(v.size()));
    dvariable tmp1;
    tmp1=mean(v);
    RETURN_ARRAYS_DECREMENT();
    return(tmp*tmp-tmp1*tmp1);
  }

/**
 * Description not yet available.
 * \param
 */
  dvariable std_dev(_CONST dvar_vector& v)
  {
    dvariable tmp;
    RETURN_ARRAYS_INCREMENT();
    tmp=norm(v)/sqrt(double(v.size()));
    dvariable tmp1;
    tmp1=mean(v);
    RETURN_ARRAYS_DECREMENT();
    return(sqrt(tmp*tmp-tmp1*tmp1));
  }

/**
 * Description not yet available.
 * \param
 */
  dvariable mean(_CONST dvar_vector& v)
  {
    dvariable tmp;
    RETURN_ARRAYS_INCREMENT();
    tmp=sum(v)/double(v.size());
    RETURN_ARRAYS_DECREMENT();
    return(tmp);
  }
