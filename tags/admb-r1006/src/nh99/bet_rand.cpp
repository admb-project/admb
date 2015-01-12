/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009-2011 ADMB foundation
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>
 
/**
 * Description not yet available.
 * \param
 */
double better_rand(long int& idum)
{
  random_number_generator rng(idum);
  double rr = ((random_number_generator&) rng).better_rand();
  return rr;
}
