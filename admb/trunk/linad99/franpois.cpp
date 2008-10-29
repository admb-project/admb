#define HOME_VERSION
//COPYRIGHT (c) 1998 OTTER RESEARCH LTD
#include "fvar.hpp"


  void dvar_vector::fill_randpoisson( double lambda,
    BOR_CONST random_number_generator& rng)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=randpoisson(lambda,rng);
    }
  }


#undef HOME_VERSION


