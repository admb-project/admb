/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <admodel.h>

#if !defined(USE_ADPVM)
void function_minimizer::pvm_slave_mcmc_routine(void){}
#else
void function_minimizer::pvm_slave_mcmc_routine(void)
{
  int nvar=initial_params::nvarcalc();
  do
  {
    int iflag=get_int_from_master();
    if (!iflag) break;
    pvm_slave_get_monte_carlo_value(nvar); 
  }
  while(1);
}
#endif




