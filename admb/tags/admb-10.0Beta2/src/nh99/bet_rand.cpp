/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009, 2010 ADMB Foundation
 */
#include <fvar.hpp>
 
double better_rand(long int& idum)
{
  random_number_generator rng(idum);
  double rr = ((random_number_generator&) rng).better_rand();
  return rr;
}
