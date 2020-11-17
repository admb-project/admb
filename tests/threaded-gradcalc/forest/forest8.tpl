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
  global_grad_stack1 = new grad_stack(10000, 10);
  global_grad_stack2 = new grad_stack(10000, 10);
  global_grad_stack3 = new grad_stack(10000, 10);
  global_grad_stack4 = new grad_stack(10000, 10);
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
  delete global_grad_stack1;
  global_grad_stack1 = nullptr;
  delete global_grad_stack2;
  global_grad_stack2 = nullptr;
  delete global_grad_stack3;
  global_grad_stack3 = nullptr;
  delete global_grad_stack4;
  global_grad_stack4 = nullptr;
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  deallocation_time = elapsed.count();
  std::cout << "Resource time: " << (deallocation_time + allocation_time)  <<  endl;
GLOBALS_SECTION
  #include <fvar.hpp>

  grad_stack* global_grad_stack1 = nullptr;
  grad_stack* global_grad_stack2 = nullptr;
  grad_stack* global_grad_stack3 = nullptr;
  grad_stack* global_grad_stack4 = nullptr;

  double total_funnel_time = 0;
  double allocation_time = 0;
  double deallocation_time = 0;

  dvar_vector funnel(
    dvariable (*func)(const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps),
    const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const dvector& a, const int nsteps);

  dvariable h2(const dvariable& z, const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double aa_index);

  typedef std::function<dvariable(const dvariable&, const dvariable&, const dvariable&, const dvariable&, const dvariable&, const double)> _func2;

  dvariable adromb2(_func2 func, const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double aa_index, double a, double b, int ns);

