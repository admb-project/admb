
#define HOME_VERSION
#include <fvar.hpp>

void ivector::initialize(void)
{
  for (int i=indexmin();i<=indexmax();i++)
  {
    elem(i)=0;
  }
}

#undef HOME_VERSION
