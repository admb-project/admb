/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <admodel.h>

#ifdef __GNUDOS__
  #include <gccmanip.h>
#endif

/**
 * Description not yet available.
 * \param
 */
void function_minimizer::mcmc_eval(void)
{
  gradient_structure::set_NO_DERIVATIVES();
  initial_params::current_phase=initial_params::max_number_phases;
  uistream * pifs_psave = NULL;

#if defined(USE_LAPLACE)
#endif

#if defined(USE_LAPLACE)
    initial_params::set_active_random_effects();
    int nvar1=initial_params::nvarcalc(); 
#else
  int nvar1=initial_params::nvarcalc(); // get the number of active parameters
#endif
  int nvar;
  
  pifs_psave= new
    uistream((char*)(ad_comm::adprogram_name + adstring(".psv")));
  if (!pifs_psave || !(*pifs_psave))
  {
    cerr << "Error opening file "
            << (char*)(ad_comm::adprogram_name + adstring(".psv"))
       << endl;
    if (pifs_psave)
    {
      delete pifs_psave;
      pifs_psave=NULL;
      return;
    }
  }
  else
  {     
    (*pifs_psave) >> nvar;
    if (nvar!=nvar1)
    {
      cout << "Incorrect value for nvar in file "
           << "should be " << nvar1 << " but read " << nvar << endl;
      if (pifs_psave)
      {
        delete pifs_psave;
        pifs_psave=NULL;
      }
      return;
    }
  }
   
  independent_variables y(1,nvar);

  do
  {
    if (pifs_psave->eof())
    {
      break;
    }
    else
    {
      (*pifs_psave) >> y;
      if (pifs_psave->eof())
      {

        break;
      }
      int ii=1;
      initial_params::restore_all_values(y,ii);
      initial_params::xinit(y);   
      /*double ll=-*/get_monte_carlo_value(nvar,y);
    }
  }
  while(1);
  if (pifs_psave)
  {
    delete pifs_psave;
    pifs_psave=NULL;
  }
  return;
}
