/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function dvar_vector::fill_randnegbinomial
*/

#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
void dvar_vector::fill_randnegbinomial(double lambda,double tau,
  const random_number_generator& rng)
{
  for (int i=indexmin(); i<=indexmax(); i++)
  {
    elem(i)=randnegbinomial(lambda,tau,rng);
  }
}
