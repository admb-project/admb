#include <fvar.hpp>
#if defined(__cpluscplus)
extern "C" {
#endif

void exit_handler(int k)
{
  exit(1);
}

#if defined(__cpluscplus)
}
#endif

