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

  S = funnels([](const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps)
  {
    dvariable Integral;
    Integral = ::adromb(-3.0, 3.0, nsteps, &h, tau, nu, sigma, beta, ai);
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
  void allocate_gradients();
  allocate_gradients();
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
  void deallocate_gradients();
  deallocate_gradients();
GLOBALS_SECTION
  #include <fvar.hpp>
  #include <admodel.h>
  #include "adromb.cpp"
  #include "thread_funnel5.h"

  dvariable h(const double z, const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai)
  {
    dvariable tmp;
    tmp = mfexp(-.5*z*z + tau*(-1.+mfexp(-nu*pow(ai,beta)*mfexp(sigma*z))));
    return tmp;
  }

  extern double total_funnel_time;
  dvar_vector funnels(
    dvariable (*func)(const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai, const int nsteps),
    const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const dvector& a, const int nsteps)
  {
    auto start = std::chrono::high_resolution_clock::now();

    const int min = a.indexmin();
    const int max = a.indexmax();
    dvar_vector results(min, max);

    for (int i = min; i <= max; ++i)
    {
      funnel(func, tau, nu, sigma, beta, a(i), nsteps);
    }
    get_results(results);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    double count = elapsed.count();
    std::cout << "Funnel time: " << count <<  endl;
    total_funnel_time += count;

    return results;
  }
