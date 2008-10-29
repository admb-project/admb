#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

void ivector::fill(const char * s)
{
  dvector tmp(*this);
  tmp.fill(s);
  *this=ivector(tmp);
}

void lvector::fill(const char * s)
{
  dvector tmp(*this);
  tmp.fill(s);
  *this=lvector(tmp);
}
#undef HOME_VERSION
