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
#include <fvar.hpp>

  /**
  \ingroup PDF
  Log gamma probability density function; variable objects.
  \param _x dvariable argument
  \param r double argument
  \param mu double argument
  \returns \f$r\log{\mu} + (r-1)*\log{x}-\mu*x-\log{\Gamma(r)}\f$
  */
  dvariable log_gamma_density(const prevariable& _x,double r, double mu)
  {
    prevariable& x= (prevariable&)(_x);

    return r*log(mu) + (r-1)*log(x)-mu*x-gammln(r);
  }

  /**
  \ingroup PDF
  Log gamma probability density function; variable objects.
  \param _x dvariable argument
  \param _r dvariable argument
  \param _mu dvariable argument
  \returns \f$r\log{\mu} + (r-1)*\log{x}-\mu*x-\log{\Gamma(r)}\f$
  */
  dvariable log_gamma_density(const dvariable& _x,const dvariable& _r,
    const  dvariable& _mu)
  {
    prevariable& x= (prevariable&)(_x);
    prevariable& r= (prevariable&)(_r);
    prevariable& mu= (prevariable&)(_mu);
    return r*log(mu) + (r-1)*log(x)-mu*x-gammln(r);
  }
    
  /**
  \ingroup PDF
  Gamma probability density function; variable objects.
  \param _x double argument
  \param r double argument
  \param mu dvariable argument
  \returns Davariable containing \f$\exp\big(r\log{\mu} + (r-1)*\log{x}-\mu*x-\log{\Gamma(r)}\big)\f$
  */
  dvariable gamma_density(const prevariable& _x,double r, double mu)
  {
    prevariable& x= (prevariable&)(_x);

    return exp(r*log(mu) + (r-1)*log(x)-mu*x-gammln(r));
  }
  /**
  \ingroup PDF
  Gamma probability density function; variable objects.
  \param _x dvariable argument
  \param _r dvariable argument
  \param _mu dvariable argument
  \returns Davariable containing \f$\exp\big(r\log{\mu} + (r-1)*\log{x}-\mu*x-\log{\Gamma(r)}\big)\f$
  */  
  dvariable gamma_density(const dvariable& _x,const dvariable& _r,
    const  dvariable& _mu)
  {
    prevariable& x= (prevariable&)(_x);
    prevariable& r= (prevariable&)(_r);
    prevariable& mu= (prevariable&)(_mu);
    return exp(r*log(mu) + (r-1)*log(x)-mu*x-gammln(r));
  }
