/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <admodel.h>

#if defined(USE_LAPLACE)
#  include <df1b2fun.h>
#  include <adrndeff.h>
#endif

#if defined(USE_LAPLACE)
dvariable function_minimizer::do_gauss_hermite_integration(void)
{
  if (lapprox->gh->mi)
  {
    return do_gauss_hermite_integration_multi();
  }
  else
  {
    dvariable fun=0.0;
    int nsc=lapprox->num_separable_calls;
    dvector& w=lapprox->gh->w;
    for (int is=1;is<=nsc;is++)
    {
      fun-=log(1.e-50+exp(-lapprox->gh->gauss_hermite_values(is))*w);
    }
    return fun;
  }
}

dvariable function_minimizer::do_gauss_hermite_integration_multi(void)
{
  multi_index mi=*(lapprox->gh->mi);
  dvariable fun=0.0;
  int nsc=lapprox->num_separable_calls;
  dvector& w=lapprox->gh->w;
  ivector& lrea = *(lapprox->num_local_re_array);
  for (int isc=1;isc<=nsc;isc++)
  {
    dvariable ftmp=0.0;
    int lus=lrea(isc);
    mi.initialize();
    double ww;
    do
    {
      ww=1.0;
      for (int iu=1;iu<=lus;iu++)
      {
        ww*= w(mi()(iu));
      }
      int is=mi.get_offset()+1;
      ftmp+=exp(-lapprox->gh->gauss_hermite_values(isc,is))*ww;
      ++mi;
    }
    while(mi.get_depth()<=lus);
    fun-=log(ftmp);
  }
  return fun;
}
#endif // #if defined(USE_LAPLACE)

