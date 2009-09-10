/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include "fvar.hpp"

void dvector::fill_randnegbinomial(double lambda,double tau,
  const random_number_generator& rng)
{
  for (int i=indexmin(); i<=indexmax(); i++)
  {
    elem(i)=randnegbinomial(lambda,tau,rng);
  }
}



