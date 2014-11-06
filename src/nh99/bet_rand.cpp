/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009-2012 ADMB foundation
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

/**
 * Description not yet available.
 * \param
 */
double better_rand(long int& idum)
{
#ifndef OPT_LIB
  assert(idum <= INT_MAX);  
#endif
  random_number_generator rng((int)idum);
  double rr = ((random_number_generator&) rng).better_rand();
  return rr;
}
