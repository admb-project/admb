/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
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
double randcau(const random_number_generator& rng)
{
  double u=inv_cumd_cauchy(((random_number_generator&) rng).better_rand());
  return(u);
}

/**
 * Description not yet available.
 * \param
 */
void dvector::fill_randcau(const random_number_generator& rng)
{
  for (int i=indexmin(); i<=indexmax(); i++)
  {
    (*this)(i)=randcau(rng);
  }
}

/**
 * Description not yet available.
 * \param
 */
void dmatrix::fill_randcau(const random_number_generator& rng)
{
  for (int i=rowmin(); i<=rowmax(); i++)
  {
    elem(i).fill_randcau(rng);
  }
}

/**
 * Description not yet available.
 * \param
 */
void d3_array::fill_randcau(const random_number_generator& rng)
{
  for (int i=slicemin(); i<=slicemax(); i++)
  {
    elem(i).fill_randcau(rng);
  }
}
