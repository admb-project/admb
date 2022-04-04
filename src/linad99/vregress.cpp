/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function regression(const dvector&, const dvar_vector&)
*/

#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
dvariable regression(const dvector& obs, const dvar_vector& pred)
{
  double nobs=double(size_count(obs));
  dvariable vhat=norm2(obs-pred);
  vhat/=nobs;
  return (.5*nobs*log(vhat));
}
