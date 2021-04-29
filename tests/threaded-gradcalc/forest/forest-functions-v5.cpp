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

#include "compute-gradients-v4.h"

dvar_vector funnel(
  dvariable (*func)(const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps),
  const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const dvector& a, const int nsteps)
{
  const int min = a.indexmin();
  const int max = a.indexmax();
  dvar_vector results(min, max);
#ifdef DEV

/*
  for (int i = min; i <= max; ++i)
  {
    auto f = compute_gradients(func, tau, nu, sigma, beta, a(i), nsteps);
    auto t = f.get();
    results(i) = to_dvariable(t);
  }
*/
  {
    auto f = compute_gradients(global_grad_stack1, func, tau, nu, sigma, beta, a(1), nsteps);
    auto t = f.get();
    results(1) = to_dvariable(t);
  }
  
  for (int i = 2; i <= max; i += 4)
  {
    auto f1 = compute_gradients(global_grad_stack1, func, tau, nu, sigma, beta, a(i), nsteps);
    auto f2 = compute_gradients(global_grad_stack2, func, tau, nu, sigma, beta, a(i + 1), nsteps);
    auto f3 = compute_gradients(global_grad_stack3, func, tau, nu, sigma, beta, a(i + 2), nsteps);
    auto f4 = compute_gradients(global_grad_stack4, func, tau, nu, sigma, beta, a(i + 3), nsteps);

    auto t1 = f1.get();
    results(i) = to_dvariable(t1);
    auto t2 = f2.get();
    results(i + 1) = to_dvariable(t2);
    auto t3 = f3.get();
    results(i + 2) = to_dvariable(t3);
    auto t4 = f4.get();
    results(i + 3) = to_dvariable(t4);
  }

/*
  auto f1 = compute_gradients(func, tau, nu, sigma, beta, a(1), nsteps);
  results(1) = to_dvariable(f1.get());
  auto f2 = compute_gradients(func, tau, nu, sigma, beta, a(2), nsteps);
  results(2) = to_dvariable(f2.get());
  auto f3 = compute_gradients(func, tau, nu, sigma, beta, a(3), nsteps);
  results(3) = to_dvariable(f3.get());
  auto f4 = compute_gradients(func, tau, nu, sigma, beta, a(4), nsteps);
  results(4) = to_dvariable(f4.get());
  auto f5 = compute_gradients(func, tau, nu, sigma, beta, a(5), nsteps);
  results(5) = to_dvariable(f5.get());
  auto f6 = compute_gradients(func, tau, nu, sigma, beta, a(6), nsteps);
  results(6) = to_dvariable(f6.get());
  auto f7 = compute_gradients(func, tau, nu, sigma, beta, a(7), nsteps);
  results(7) = to_dvariable(f7.get());
  auto f8 = compute_gradients(func, tau, nu, sigma, beta, a(8), nsteps);
  results(8) = to_dvariable(f8.get());
  auto f9 = compute_gradients(func, tau, nu, sigma, beta, a(9), nsteps);
  results(9) = to_dvariable(f9.get());
  auto f10 = compute_gradients(func, tau, nu, sigma, beta, a(10), nsteps);
  results(10) = to_dvariable(f10.get());
  auto f11 = compute_gradients(func, tau, nu, sigma, beta, a(11), nsteps);
  results(11) = to_dvariable(f11.get());
  auto f12 = compute_gradients(func, tau, nu, sigma, beta, a(12), nsteps);
  results(12) = to_dvariable(f12.get());
  auto f13 = compute_gradients(func, tau, nu, sigma, beta, a(13), nsteps);
  results(13) = to_dvariable(f13.get());
*/
#else
  auto f1 = compute_gradients(global_grad_stack1, func, tau, nu, sigma, beta, a(1), nsteps);
  auto f2 = compute_gradients(global_grad_stack2, func, tau, nu, sigma, beta, a(2), nsteps);
  auto f3 = compute_gradients(global_grad_stack3, func, tau, nu, sigma, beta, a(3), nsteps);
  auto f4 = compute_gradients(global_grad_stack4, func, tau, nu, sigma, beta, a(4), nsteps);
  results(1) = to_dvariable(f1);
  results(2) = to_dvariable(f2);
  results(3) = to_dvariable(f3);
  results(4) = to_dvariable(f4);
  auto f5 = compute_gradients(global_grad_stack1, func, tau, nu, sigma, beta, a(5), nsteps);
  auto f6 = compute_gradients(global_grad_stack2, func, tau, nu, sigma, beta, a(6), nsteps);
  auto f7 = compute_gradients(global_grad_stack3, func, tau, nu, sigma, beta, a(7), nsteps);
  auto f8 = compute_gradients(global_grad_stack4, func, tau, nu, sigma, beta, a(8), nsteps);
  results(5) = to_dvariable(f5);
  results(6) = to_dvariable(f6);
  results(7) = to_dvariable(f7);
  results(8) = to_dvariable(f8);
  auto f9 = compute_gradients(global_grad_stack1, func, tau, nu, sigma, beta, a(9), nsteps);
  auto f10 = compute_gradients(global_grad_stack2, func, tau, nu, sigma, beta, a(10), nsteps);
  auto f11 = compute_gradients(global_grad_stack3, func, tau, nu, sigma, beta, a(11), nsteps);
  auto f12 = compute_gradients(global_grad_stack4, func, tau, nu, sigma, beta, a(12), nsteps);
  results(9) = to_dvariable(f9);
  results(10) = to_dvariable(f10);
  results(11) = to_dvariable(f11);
  results(12) = to_dvariable(f12);
  auto f13 = compute_gradients(global_grad_stack1, func, tau, nu, sigma, beta, a(13), nsteps);
  results(13) = to_dvariable(f13);
#endif

  return results;
}
