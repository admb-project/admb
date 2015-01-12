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
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
  void dvar_vector::fill_randpoisson( double lambda,
    BOR_CONST random_number_generator& rng)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=randpoisson(lambda,rng);
    }
  }
