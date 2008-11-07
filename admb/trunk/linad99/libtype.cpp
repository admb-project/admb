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
#if defined SAFE_ALLOCATE && defined SAFE_INITIALIZE
void safe_library() { ; }
#else
void optimized_library() { ; }
#endif
char which_library()
{
#if defined SAFE_ALLOCATE && defined SAFE_INITIALIZE
  return 's';
#else
  return 'o';
#endif
}
#undef HOME_VERSION
