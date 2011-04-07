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
double get_values(double x,double y,int print_switch);

#include "fvar.hpp"
  /**
  \ingroup PDF
  Gamma probability density function; constant objects.
  \param x
  \param r
  \param mu
  \returns \f$\exp\big(r\log{\mu} + (r-1)*\log{x}-\mu*x-\log{\Gamma(r)}\big)\f$
  */
  double gamma_density(double x,double r, double mu)
  {
    return exp(r*log(mu) + (r-1)*log(x)-mu*x-gammln(r));
  }
    
  /**
  \ingroup PDF
  Log gamma probability density function; constant objects.
  \param x
  \param r
  \param mu
  \returns \f$r\log{\mu} + (r-1)*\log{x}-\mu*x-\log{\Gamma(r)}\f$
  */
  double log_gamma_density(double x,double r, double mu)
  {
    return r*log(mu) + (r-1)*log(x)-mu*x-gammln(r);
  }
