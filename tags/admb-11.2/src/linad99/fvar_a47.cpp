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
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
void dvar_vector::fill_multinomial(const int& seed,const dvector& p)
{
  dvector tmp(indexmin(),indexmax());
  tmp.fill_multinomial(seed,p);
  *(this)=tmp;
}
