#include <fvar.hpp>
#include <admodel.h>
#include <future>

extern grad_stack* global_grad_stack1;
extern grad_stack* global_grad_stack2;
extern grad_stack* global_grad_stack3;
extern grad_stack* global_grad_stack4;

typedef std::function<dvariable(const dvariable&, const dvariable&, const dvariable&, const dvariable&, const dvariable&, const double)> _func2;

dvariable h2(const dvariable& z, const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double aa_index)
{
  dvariable tmp;
  tmp=mfexp(-.5*z*z + tau*(-1.+mfexp(-nu*pow(aa_index,beta)*mfexp(sigma*z))) );  
  return tmp;
}
dvariable trapzd(_func2 func, const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double aa_index, double a, double b, int n, int& interval, dvariable& s)
{
  double x,num_interval,hn;
  dvariable sum;
  int j;
  if (n == 1) {
    interval=1;
    return (s=0.5*(b-a)*(func(a, tau, nu, sigma, beta, aa_index)+func(b, tau, nu, sigma, beta, aa_index)));
  } else {
    num_interval=interval;
    hn=(b-a)/num_interval;
    x=a+0.5*hn;
    for (sum=0.0,j=1;j<=interval;j++,x+=hn) sum += func(x, tau, nu, sigma, beta, aa_index);
    interval *= 2;
    s=0.5*(s+(b-a)*sum/num_interval);
    return s;
  }
}
dvariable adromb2(_func2 func, const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double aa_index, double a, double b, int ns)
{
  const int JMAX = 50;
  const double base = 4;
  int MAXN = min(JMAX, ns);
  dvar_vector s(1,MAXN+1);

  int interval = 0;
  dvariable s2;
  for(int j=1; j<=MAXN+1; j++)
  {
    s[j] = trapzd(func,tau,nu,sigma,beta,aa_index,a,b,j,interval,s2);
  }

  for(int iter=1; iter<=MAXN+1; iter++)
  {
    for(int j=1; j<=MAXN+1-iter; j++)
    {
      s[j] = (pow(base,iter)*s[j+1]-s[j])/(pow(base,iter)-1);
    }
  }
  return s[1];
}

#include "compute-gradients-v2.h"

dvar_vector funnel(
  dvariable (*func)(const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps),
  const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const dvector& a, const int nsteps)
{
  const int min = a.indexmin();
  const int max = a.indexmax();
  dvar_vector results(min, max);

  for (int i = min; i <= max; ++i)
  {
    auto f = compute_gradients(func, tau, nu, sigma, beta, a(i), nsteps);
    results(i) = to_dvariable(f.get());
  }
  //ad_exit(1);

  return results;
}
