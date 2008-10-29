
#define HOME_VERSION
#include "fvar.hpp"

void banded_symmetric_dmatrix::initialize(void)
{
  for (int i=rowmin();i<=rowmax();i++)
  {
    (*this)(i).initialize();
  }
}

void banded_lower_triangular_dmatrix::initialize(void)
{
  for (int i=rowmin();i<=rowmax();i++)
  {
    (*this)(i).initialize();
  }
}
#undef HOME_VERSION
