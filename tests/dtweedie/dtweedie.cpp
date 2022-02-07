#include <vector>
#include <type_traits>
#include <fvar.hpp>

int imax2(int a, double v)
{
  int b = static_cast<int>(v);
  return a > b ? a : b;  
}
int imin2(int a, int b)
{
  return a < b ? a : b;  
}
int fmax2(double a, const dvariable& v)
{
  double b = value(v);
  return a > b ? a : b;  
}
double asDouble(const dvariable& v)
{
  return value(v);
}
dvariable lgamma(const prevariable& v)
{
  return gammln(v);  
}
#include "tweedie_logW.cpp"
/**
  \brief dtweedie function (same as dtweedie.series from R package
  'tweedie').

  Silently returns NaN if not within the valid parameter range:
  \f[ (0 \leq y) \land (0 < \mu) \land (0 < \phi) \land (1 < p) \land (p < 2) \f] .

  \note Parameter order differs from the R version.

  \warning The derivative wrt. the y argument is disabled
  (zero). Hence the tweedie distribution can only be used for *data*
  (not random effects).

  The dtweedie function was copied from TMB repository at
  https://github.com/kaskr/adcomp, then modified for ADMB
  data types.

  \ingroup R_style_distribution
*/
template<class Type>
Type dtweedie(double y, Type& mu, Type& phi, Type& p, int give_log = 0) {
  Type p1 = p - 1.0, p2 = 2.0 - p;
  Type ans = -pow(mu, p2) / (phi * p2); // log(prob(y=0))
  if (y > 0) {
    ans += tweedie_logW(y, phi, p);
    ans += -y / (phi * p1 * pow(mu, p1)) - log(y);
  }
  return ( give_log ? ans : exp(ans) );
}
