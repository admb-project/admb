#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
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
