/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Function which_library()
*/

#include "fvar.hpp"
/** Get ADMB library mode.
\ingroup misc
\return char containing 'o' if compiled with the OPT_LIB macro;
contains 's' otherwise.
*/
char which_library()
{
#ifndef OPT_LIB
  return 's';
#else
  return 'o';
#endif
}
