#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include <fvar.hpp>

double dvar3_array::fill_seqadd(double i1,double i2)
{
  int mmin=indexmin();
  int mmax=indexmax();
  double inp = i1;
  for (int i=mmin;i<=mmax;i++)
  {
    double tmp=(*this)(i).fill_seqadd(inp,i2);
    inp=tmp;
  }
  return inp;
}
#undef HOME_VERSION
