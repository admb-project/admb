// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

DATA_SECTION
 init_int nsteps 
 init_int k
 init_vector a(1,k+1)
 init_vector freq(1,k)
 int a_index;
 number sum_freq
!! sum_freq=sum(freq);
PARAMETER_SECTION
  init_bounded_number log_tau(-14,15,2)
  init_bounded_number log_nu(-15,4)
  init_bounded_number beta(.1,1.0,-1)
  init_bounded_number log_sigma(-5,3)
  likeprof_number tau
 !! tau.set_stepnumber(25);
  sdreport_number nu
  sdreport_number sigma
  vector S(1,k+1)
  objective_function_value f
INITIALIZATION_SECTION
  log_tau 0  
  beta 0.6666667 
  log_nu 0  
  log_sigma -2
PROCEDURE_SECTION
  cout << endl;
  cout << "ifn = " << ifn << endl;
  cout << "quit_flag = " << quit_flag << endl;
  cout << "ihflag = " << ihflag << endl;
  cout << "last_phase() " << last_phase() << endl; 
  cout << "iexit = " << iexit << endl;
  tau=mfexp(log_tau);
  nu=mfexp(log_nu);
  sigma=mfexp(log_sigma);
  S = funnel([](const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps)
  {
    dvariable Integral;
    Integral=adromb2(&h2,tau,nu,sigma,beta,ai,-3.0,3.0,nsteps);
    return Integral;
  }, tau, nu, sigma, beta, a, nsteps);
   f=0.0;
   for (int i=1;i<=k;i++)
   {
     dvariable ff=0.0;
     dvariable diff=posfun((S(i)-S(i+1))/S(i),.000001,ff);
     f-=freq(i)*log(1.e-50+S(i)*diff);
     f+=ff;
   }
   f+=sum_freq*log(1.e-50+S(1));
PRELIMINARY_CALCS_SECTION
  global_grad_stack = new grad_stack(10000, 10);
  global_grad_stack2 = new grad_stack(10000, 10);
FUNCTION dvariable h(const dvariable& z)
  dvariable tmp;
  tmp=mfexp(-.5*z*z + tau*(-1.+mfexp(-nu*pow(a(a_index),beta)*mfexp(sigma*z))) );  
  return tmp;
REPORT_SECTION
  report << "report:" << endl;
  report << "ifn = " << ifn << endl;
  report << "quit_flag = " << quit_flag << endl;
  report << "ihflag = " << ihflag << endl;
  report << "last_phase() " << last_phase() << endl; 
  report << "iexit = " << iexit << endl;
  tau=mfexp(log_tau);
  report << "nsteps = " << std::setprecision(10) <<  nsteps << endl;
  report << "f = " << std::setprecision(10) <<  f << endl;
  report << "a" << endl << a << endl;
  report << "freq" << endl << freq << endl;
  report << "S" << endl << S << endl;
  report << "S/S(1)" << endl << std::ios::fixed << std::setprecision(6) << S/S(1) << endl;
  report << "tau "  << tau << endl; 
  report << "nu "  << nu << endl; 
  report << "beta "  << beta << endl; 
  report << "sigma "  << sigma << endl; 
FINAL_SECTION
  delete global_grad_stack;
  global_grad_stack = nullptr;
  delete global_grad_stack2;
  global_grad_stack2 = nullptr;
GLOBALS_SECTION
  #include <fvar.hpp>
  #include <admodel.h>
  #include <future>

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
  grad_stack* global_grad_stack = nullptr;
  grad_stack* global_grad_stack2 = nullptr;

  std::future<std::vector<std::pair<double, dvector>>> afunnel(
    dvariable (*func)(const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps),
    const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const dvector& a, const int min, const int max, const int nsteps, grad_stack* gstack)
  {
    return std::async(std::launch::async, [=]()->std::vector<std::pair<double, dvector>>
    {
      std::vector<std::pair<double, dvector>> pairs;

      gradient_structure::GRAD_STACK1 = gstack;
      gradient_structure::GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
      for (int i = min; i <= max; ++i)
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

        f = func(_tau, _nu, _sigma, _beta, a(i), nsteps);

        double v = 0;
        v = value(f);

        dvector g(1, 4);
        gradcalc(4, g);

        pairs.push_back(std::make_pair(v, g));
      }
      gradient_structure::GRAD_STACK1->deallocate_RETURN_ARRAYS();
      gradient_structure::GRAD_STACK1 = nullptr;

      return pairs;
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

    std::future<std::vector<std::pair<double, dvector>>> f = 
      afunnel(func, tau, nu, sigma, beta, a, 1, 6, nsteps, global_grad_stack);
    std::future<std::vector<std::pair<double, dvector>>> f2 = 
      afunnel(func, tau, nu, sigma, beta, a, 7, 13, nsteps, global_grad_stack2);

    std::vector<std::pair<double, dvector>> pairs = f.get();
    std::vector<std::pair<double, dvector>> pairs2 = f2.get();
  
    for (int i = 1; i <= 6; ++i)
    {
      results(i) = to_dvariable(pairs[i - 1], tau, nu, sigma, beta);
    }
    int index = 0;
    for (int i = 7; i <= 13; ++i)
    {
      results(i) = to_dvariable(pairs2[index], tau, nu, sigma, beta);
      ++index;
    }

    return results;
  }
