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
void dvar_matrix::rowshift(int min )
{
  m = m + rowmin() - min;
  index_max+=min-index_min;
  index_min=min;
}

/**
 * Description not yet available.
 * \param
 */
 void dvar_matrix::colshift( int min)
 {
   int rmin = rowmin();
   int rmax = rowmax();
   dvar_vector* pmi = m + rmin;
   for (int i = rmin; i <= rmax; ++i)
   {
     pmi->shift(min);
     ++pmi;
   }
   //shape->colshift(min);
 }
