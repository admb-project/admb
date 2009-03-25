/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>

double randnegbinomial(double mu,double tau,
  const random_number_generator& rng)
{
  if (tau<=1.0)
  {
    cerr << "Error in randnegbinomial overdispersion must be >=1" << endl;
    ad_exit(1);
  }
  double r=mu/(tau-1);
  double c=r/mu;
  double z=sgamma(r,rng);
  double lambda=z/c;
  return randpoisson(lambda,rng); 
}
