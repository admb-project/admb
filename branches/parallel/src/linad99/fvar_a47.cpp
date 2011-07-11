/*
 * $Id: fvar_a47.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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
  void dvar_vector::fill_multinomial(BOR_CONST int& seed,_CONST dvector& p)
  {
    dvector tmp(indexmin(),indexmax());
    tmp.fill_multinomial(seed,p);
    *(this)=tmp;
  }
