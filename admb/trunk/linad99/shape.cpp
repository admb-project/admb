/**
  * $Id:   $
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
 /*
  void vector_shapex::operator delete(void * ptr,size_t n) 
  {  
    xpool->free(ptr); 
  }
 */

  void vector_shape::shift(int min)
  {
    index_max=index_max-index_min+min;
    index_min=min;
  }

  void vector_shapex::shift(int min)
  {
    index_max=index_max-index_min+min;
    index_min=min;
  }

#undef HOME_VERSION
