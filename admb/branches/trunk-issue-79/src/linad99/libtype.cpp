/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
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
