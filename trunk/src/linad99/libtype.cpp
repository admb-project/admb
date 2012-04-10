/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"
#if defined SAFE_ALLOCATE && defined SAFE_INITIALIZE
void safe_library() { ; }
#else
void optimized_library() { ; }
#endif
/** Get ADMB library mode.
\ingroup misc
\return char containing 'o' if compiled with the OPT_LIB macro;
contains 's' otherwise.
*/
char which_library()
{
//#if defined SAFE_ALLOCATE && defined SAFE_INITIALIZE
#ifndef OPT_LIB
  return 's';
#else
  return 'o';
#endif
}
