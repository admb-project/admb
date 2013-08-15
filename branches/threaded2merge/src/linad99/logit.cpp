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
  dvariable logistic(double a,double b,const prevariable& x)
  {
    if (value(x)>-20.)
    {
      dvariable tmp=exp(-x);
      return a+(b-a)*1.0/(1.0+tmp);
    }
    else
    {
      dvariable tmp=exp(x);
      return a+(b-a)*tmp/(1.0+tmp);
    }
  }

/**
 * Description not yet available.
 * \param
 */
  dvariable log_der_logistic(double a,double b,const prevariable& x)
  {
    if (value(x)>-20.)
    {
      dvariable tmp=exp(-x);
      return log((b-a)*tmp/square(1.0+tmp));
    }
    else
    {
      dvariable tmp=exp(x);
      return log((b-a)*tmp/square(1.0+tmp));
    }
  }

/**
 * Description not yet available.
 * \param
 */
  dvariable dflogistic(double a,double b,const prevariable& x)
  {
    if (value(x)>-20.)
    {
      dvariable tmp=exp(-x);
      return (b-a)*tmp/square(1.0+tmp);
    }
    else
    {
      dvariable tmp=exp(x);
      return (b-a)*tmp/square(1.0+tmp);
    }
  }
