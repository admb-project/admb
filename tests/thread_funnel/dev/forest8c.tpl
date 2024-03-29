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
  auto start = std::chrono::high_resolution_clock::now();
  S = funnel([](const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps)
  {
    dvariable Integral;
    Integral=adromb2(&h2,tau,nu,sigma,beta,ai,-3.0,3.0,nsteps);
    return Integral;
  }, tau, nu, sigma, beta, a, nsteps);
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  double count = elapsed.count();
  std::cout << "Funnel time: " << count <<  endl;
  total_funnel_time += count;

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
  auto start = std::chrono::high_resolution_clock::now();
  /*
  global_gs1 = new gradient_structure(10000, 1);
  global_gs2 = new gradient_structure(10000, 2);
  global_gs3 = new gradient_structure(10000, 3);
  global_gs4 = new gradient_structure(10000, 4);
  */
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  allocation_time = elapsed.count();
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
  cout << "Total Funnel time: " << total_funnel_time << endl;

  auto start = std::chrono::high_resolution_clock::now();
  delete global_gs1;
  global_gs1 = nullptr;
  delete global_gs2;
  global_gs2 = nullptr;
  delete global_gs3;
  global_gs3 = nullptr;
  delete global_gs4;
  global_gs4 = nullptr;

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  deallocation_time = elapsed.count();
  std::cout << "Resource time: " << (deallocation_time + allocation_time)  <<  endl;
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
  gradient_structure* global_gs1 = nullptr;
  gradient_structure* global_gs2 = nullptr;
  gradient_structure* global_gs3 = nullptr;
  gradient_structure* global_gs4 = nullptr;

  std::future<std::pair<double, dvector>> afunnel(
    dvariable (*func)(const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps),
    const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps, gradient_structure* gs)
  {
    return std::async(std::launch::async, [=]()->std::pair<double, dvector>
    {
      double v = 0;
      dvector g(1, 4);

      gradient_structure::_instance = gs;
      //gradient_structure::get()->GRAD_STACK1->allocate_RETURN_ARRAYS(25, 70);
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
      gradient_structure::_instance = nullptr;
      //gradient_structure::get()->GRAD_STACK1->deallocate_RETURN_ARRAYS();

      return std::make_pair(v, g);
    });
  }
  dvariable to_dvariable(
    gradient_structure* gs,
    std::pair<double, dvector>& p,
    const dvariable& x, const dvariable& y,
    const dvariable& u, const dvariable& v)
  {
    gradient_structure::_instance = gs;

    dvariable var(p.first);
    dvector g(p.second);

    grad_stack_entry* entry = gs->GRAD_STACK1->ptr;
    entry->func = NULL;
    entry->dep_addr = &((*var.v).x);
    entry->ind_addr1 = &((*x.v).x);
    entry->mult1 = g(1);
    entry->ind_addr2 = &((*y.v).x);
    entry->mult2 = g(2);
    gs->GRAD_STACK1->ptr++;
    grad_stack_entry* entry2 = gs->GRAD_STACK1->ptr;
    entry2->func = default_evaluation4ind;
    entry2->ind_addr1 = &((*u.v).x);
    entry2->mult1 = g(3);
    entry2->ind_addr2 = &((*v.v).x);
    entry2->mult2 = g(4);
    gs->GRAD_STACK1->ptr++;

    return var;
  }
  dvar_vector funnel(
    dvariable (*func)(const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps),
    const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const dvector& a, const int nsteps)
  {
    const int min = a.indexmin();
    const int max = a.indexmax();
    dvar_vector results(min, max);

    gradient_structure* gs = gradient_structure::get();

    global_gs1 = new gradient_structure(10000, min);
    global_gs2 = new gradient_structure(10000, min + 1);
    global_gs3 = new gradient_structure(10000, min + 2);
    global_gs4 = new gradient_structure(10000, min + 3);
    for (int i = min; i < max; i += 4)
    {
      std::future<std::pair<double, dvector>> f = 
        afunnel(func, tau, nu, sigma, beta, a(i), nsteps, global_gs1);
      std::future<std::pair<double, dvector>> f2 = 
        afunnel(func, tau, nu, sigma, beta, a(i + 1), nsteps, global_gs2);
      std::future<std::pair<double, dvector>> f3 = 
        afunnel(func, tau, nu, sigma, beta, a(i + 2), nsteps, global_gs3);
      std::future<std::pair<double, dvector>> f4 = 
        afunnel(func, tau, nu, sigma, beta, a(i + 3), nsteps, global_gs4);

      std::pair<double, dvector> p = f.get();
      std::pair<double, dvector> p2 = f2.get();
      std::pair<double, dvector> p3 = f3.get();
      std::pair<double, dvector> p4 = f4.get();

      results(i) = to_dvariable(gs, p, tau, nu, sigma, beta);
      results(i + 1) = to_dvariable(gs, p2, tau, nu, sigma, beta);
      results(i + 2) = to_dvariable(gs, p3, tau, nu, sigma, beta);
      results(i + 3) = to_dvariable(gs, p4, tau, nu, sigma, beta);
    }
    delete global_gs2;
    global_gs2 = nullptr;
    delete global_gs3;
    global_gs3 = nullptr;
    delete global_gs4;
    global_gs4 = nullptr;

    gradient_structure::_instance = global_gs1;
    {
      std::future<std::pair<double, dvector>> f = 
        afunnel(func, tau, nu, sigma, beta, a(max), nsteps, global_gs1);
      std::pair<double, dvector> p = f.get();

      results(max) = to_dvariable(gs, p, tau, nu, sigma, beta);
    }
    delete global_gs1;
    global_gs1 = nullptr;

    gradient_structure::_instance = gs;

    return results;
  }
  double total_funnel_time = 0;
  double allocation_time = 0;
  double deallocation_time = 0;
