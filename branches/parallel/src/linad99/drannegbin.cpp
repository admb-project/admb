/*
 * $Id: drannegbin.cpp 946 2011-01-12 23:52:45Z johnoel $
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
void dvector::fill_randnegbinomial(double lambda,double tau,
  const random_number_generator& rng)
{
  for (int i=indexmin(); i<=indexmax(); i++)
  {
    elem(i)=randnegbinomial(lambda,tau,rng);
  }
}
