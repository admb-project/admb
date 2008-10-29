
#define HOME_VERSION
//COPYRIGHT (c) 1998 OTTER RESEARCH LTD
#include "fvar.hpp"

          
double randcau( BOR_CONST random_number_generator& rng)
{
  double u=inv_cumd_cauchy(((random_number_generator&) rng).better_rand());
  return(u);
}
  
void dvector::fill_randcau( BOR_CONST random_number_generator& rng)
{
  for (int i=indexmin(); i<=indexmax(); i++)
  {
    (*this)(i)=randcau(rng);
  }
}

void dmatrix::fill_randcau( BOR_CONST random_number_generator& rng)
{
  for (int i=rowmin(); i<=rowmax(); i++)
  {
    elem(i).fill_randcau(rng);
  }
}

void d3_array::fill_randcau( BOR_CONST random_number_generator& rng)
{
  for (int i=slicemin(); i<=slicemax(); i++)
  {
    elem(i).fill_randcau(rng);
  }
}

#undef HOME_VERSION


