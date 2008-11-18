/**
  * $Id$
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#define HOME_VERSION
#include "fvar.hpp"


  void dvar_vector::fill_randpoisson( double lambda,
    BOR_CONST random_number_generator& rng)
  {
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=randpoisson(lambda,rng);
    }
  }


#undef HOME_VERSION


