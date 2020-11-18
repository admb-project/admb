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

std::future<std::pair<double, dvector>> afunnel(
  dvariable (*func)(const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps),
  const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps, grad_stack* gstack)
{
  return std::async(std::launch::async, [=]()->std::pair<double, dvector>
  {
    double v = 0;
    dvector g(1, 4);

    gradient_structure::GRAD_STACK1 = gstack;
    gradient_structure::GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
    {
      independent_variables scoped_independents(1, 4);
      scoped_independents(1) = value(tau);
      scoped_independents(2) = value(nu);
      scoped_independents(3) = value(sigma);
      scoped_independents(4) = value(beta);

      // Set gradient_structure::NVAR
      dvar_vector scoped_variables(scoped_independents);

      dvariable f(0);

      dvariable _tau = scoped_variables(1);
      dvariable _nu = scoped_variables(2);
      dvariable _sigma = scoped_variables(3);
      dvariable _beta = scoped_variables(4);

      f = func(_tau, _nu, _sigma, _beta, ai, nsteps);

      v = value(f);

      gradcalc(4, g);
    }
    gradient_structure::GRAD_STACK1->deallocate_RETURN_ARRAYS();
    gradient_structure::GRAD_STACK1 = nullptr;

    return std::make_pair(v, g);
  });
}
dvariable to_dvariable(
  std::pair<double, dvector>& p,
  const dvariable& x, const dvariable& y,
  const dvariable& u, const dvariable& v)
{
  dvariable var(p.first);
  dvector g(p.second);

  grad_stack_entry* entry = gradient_structure::GRAD_STACK1->ptr;
  entry->func = NULL;
  entry->dep_addr = &((*var.v).x);
  entry->ind_addr1 = &((*x.v).x);
  entry->mult1 = g(1);
  entry->ind_addr2 = &((*y.v).x);
  entry->mult2 = g(2);
  gradient_structure::GRAD_STACK1->ptr++;
  grad_stack_entry* entry2 = gradient_structure::GRAD_STACK1->ptr;
  entry2->func = default_evaluation4ind;
  entry2->ind_addr1 = &((*u.v).x);
  entry2->mult1 = g(3);
  entry2->ind_addr2 = &((*v.v).x);
  entry2->mult2 = g(4);
  gradient_structure::GRAD_STACK1->ptr++;

  return var;
}
dvar_vector funnel(
  dvariable (*func)(const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps),
  const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const dvector& a, const int nsteps)
{
  const int min = a.indexmin();
  const int max = a.indexmax();
  dvar_vector results(min, max);

  for (int i = min; i < max; i += 4)
  {
    std::future<std::pair<double, dvector>> f1 = 
      afunnel(func, tau, nu, sigma, beta, a(i    ), nsteps, global_grad_stack1);
    std::future<std::pair<double, dvector>> f2 = 
      afunnel(func, tau, nu, sigma, beta, a(i + 1), nsteps, global_grad_stack2);
    std::future<std::pair<double, dvector>> f3 = 
      afunnel(func, tau, nu, sigma, beta, a(i + 2), nsteps, global_grad_stack3);
    std::future<std::pair<double, dvector>> f4 = 
      afunnel(func, tau, nu, sigma, beta, a(i + 3), nsteps, global_grad_stack4);

    std::pair<double, dvector> p1 = f1.get();
    std::pair<double, dvector> p2 = f2.get();
    std::pair<double, dvector> p3 = f3.get();
    std::pair<double, dvector> p4 = f4.get();

    results(i    ) = to_dvariable(p1, tau, nu, sigma, beta);
    results(i + 1) = to_dvariable(p2, tau, nu, sigma, beta);
    results(i + 2) = to_dvariable(p3, tau, nu, sigma, beta);
    results(i + 3) = to_dvariable(p4, tau, nu, sigma, beta);
  }
  {
    std::future<std::pair<double, dvector>> f = 
      afunnel(func, tau, nu, sigma, beta, a(max), nsteps, global_grad_stack1);
    std::pair<double, dvector> p = f.get();
    results(max) = to_dvariable(p, tau, nu, sigma, beta);
  }

  return results;
}

