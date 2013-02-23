/*
 * $Id: bet_rand.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2009-2012 ADMB foundation
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
