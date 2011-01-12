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
#define HOME_VERSION
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
  df1b2variable gamma_density(const df1b2variable& _x,double r, double mu)
  {
    df1b2variable& x= (df1b2variable&)(_x);

    return exp(r*log(mu) + (r-1)*log(x)-mu*x-gammln(r));
  }
  
/**
 * Description not yet available.
 * \param
 */  
  df1b2variable gamma_density(const df1b2variable& _x,const df1b2variable& _r,
    const  df1b2variable& _mu)
  {
    df1b2variable& x= (df1b2variable&)(_x);
    df1b2variable& r= (df1b2variable&)(_r);
    df1b2variable& mu= (df1b2variable&)(_mu);
    return exp(r*log(mu) + (r-1)*log(x)-mu*x-gammln(r));
  }
    
/**
 * Description not yet available.
 * \param
 */
  df1b2variable log_gamma_density(const df1b2variable& _x,double r, double mu)
  {
    df1b2variable& x= (df1b2variable&)(_x);

    return r*log(mu) + (r-1)*log(x)-mu*x-gammln(r);
  }
    
/**
 * Description not yet available.
 * \param
 */
  df1b2variable log_gamma_density(const df1b2variable& _x,const df1b2variable& _r,
    const  df1b2variable& _mu)
  {
    df1b2variable& x= (df1b2variable&)(_x);
    df1b2variable& r= (df1b2variable&)(_r);
    df1b2variable& mu= (df1b2variable&)(_mu);
    return r*log(mu) + (r-1)*log(x)-mu*x-gammln(r);
  }
