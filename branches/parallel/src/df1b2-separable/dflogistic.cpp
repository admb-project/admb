/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
  df1b2variable logistic(double a,double b,const df1b2variable& x)
  {
    if (value(x)>-20.)
    {
      df1b2variable tmp=exp(-x);
      return a+(b-a)*1.0/(1.0+tmp);
    }
    else
    {
      df1b2variable tmp=exp(x);
      return a+(b-a)*tmp/(1.0+tmp);
    }
  }
  
/**
 * Description not yet available.
 * \param
 */
  df1b2variable log_der_logistic(double a,double b,const df1b2variable& x)
  {
    if (value(x)>-20.)
    {
      df1b2variable tmp=exp(-x);
      return log((b-a)*tmp/square(1.0+tmp));
    }
    else
    {
      df1b2variable tmp=exp(x);
      return log((b-a)*tmp/square(1.0+tmp));
    }
  }

/**
 * Description not yet available.
 * \param
 */
  df1b2variable dflogistic(double a,double b,const df1b2variable& x)
  {
    if (value(x)>-20.)
    {
      df1b2variable tmp=exp(-x);
      return (b-a)*tmp/square(1.0+tmp);
    }
    else
    {
      df1b2variable tmp=exp(x);
      return (b-a)*tmp/square(1.0+tmp);
    }
  }
