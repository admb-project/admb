/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


#include <fvar.hpp>


  void dvar_vector::fill_multinomial(BOR_CONST int& seed,_CONST dvector& p)
  {
    dvector tmp(indexmin(),indexmax());
    tmp.fill_multinomial(seed,p);
    *(this)=tmp;
  }
