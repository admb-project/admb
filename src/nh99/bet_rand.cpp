/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 ADMB Foundation

@brief Function better_rand
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
