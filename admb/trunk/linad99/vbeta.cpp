
#include <fvar.hpp>

dvariable beta(const prevariable& a,const prevariable& b )
{
  return exp(gammln(a)+gammln(b)-gammln(a+b));
}
