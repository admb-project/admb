

#define HOME_VERSION
//COPYRIGHT (c) 2005 OTTER RESEARCH LTD
#include "fvar.hpp"

void dvar_vector::fill_randnegbinomial(double lambda,double tau,
  const random_number_generator& rng)
{
  for (int i=indexmin(); i<=indexmax(); i++)
  {
    elem(i)=randnegbinomial(lambda,tau,rng);
  }
}

#undef HOME_VERSION


