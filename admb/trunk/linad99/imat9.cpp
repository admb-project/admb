
#define HOME_VERSION
#include <fvar.hpp>

int max(const imatrix & M)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  int n1=max(M(mmin));
  for (int i=mmin+1;i<=mmax;i++)
  {
    int n=max(M(i));
    if (n1<n) n1=n;
  }
  return n1;
}
    

#undef HOME_VERSION

