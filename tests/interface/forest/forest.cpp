#include "admb.h"
#include "adromb.cpp"

dvariable h(const double z, const dvariable& tau, const dvariable& nu, const dvariable& sigma, const dvariable& beta, const double ai)
{
  dvariable tmp;
  tmp = mfexp(-.5*z*z + tau*(-1.+mfexp(-nu*pow(ai,beta)*mfexp(sigma*z))));
  return tmp;
}
int main(int argc,char* argv[])
{
  // data_section
  int nsteps{8};
  int k{12};
  dvector a("{ 0.04, 0.1, 0.2, 0.4, 0.8, 1.6, 3.2, 6.4, 12.8, 25.6, 51.2, 102.4, 204.8 }");
  dvector freq("{ 167, 84, 61, 29, 19, 17, 4, 4, 1, 0, 1, 1 }");
  double sum_freq = sum(freq);

  minimizer m(argc, argv);

  // parameter_section(initial_value, minimimum_bounded_value, maximum_bounded_value, start_phase, name) 
  // parameter_section(initial_value, minimimum_bounded_value, maximum_bounded_value, name) -- uses 1 as default start phase
  param_init_bounded_number log_tau(0.0, -14, 15, 2, "log_tau");
  param_init_bounded_number log_nu(0.0, -15, 4, "log_nu");
  param_init_bounded_number beta(0.6666667, 0.1, 1.0, -1, "beta");
  param_init_bounded_number log_sigma(-2.0, -5, 3, "log_sigma");
  param_likeprof_number tau(25, "tau");
  param_stddev_number nu("nu");
  param_stddev_number sigma("sigma");
  objective_function_value f("f");

  dvar_vector S(1, k + 1);;
  S.initialize();

  // minimize procedure_section
  m.minimize([&]()
  {
    f = 0.0;
    cout << endl;
    cout << "ifn = " << m.ifn << endl;
    cout << "quit_flag = " << m.quit_flag << endl;
    cout << "ihflag = " << m.ihflag << endl;
    cout << "last_phase() " << m.last_phase() << endl;
    cout << "iexit = " << m.iexit << endl;
    tau=mfexp(log_tau);
    nu=mfexp(log_nu);
    sigma=mfexp(log_sigma);
    funnel_dvariable Integral;
    for (int i=1;i<=k+1;i++)
    {
      ad_begin_funnel();
      Integral=adromb(-3.0, 3.0, nsteps, &h, tau, nu, sigma, beta, a(i));
      S(i)=Integral;
    }
    for (int i=1;i<=k;i++)
    {
      dvariable ff=0.0;
      dvariable diff=posfun((S(i)-S(i+1))/S(i),.000001,ff);
      f-=freq(i)*log(1.e-50+S(i)*diff);
      f+=ff;
    }
    f+=sum_freq*log(1.e-50+S(1));
  });

  // report_section
  ofstream report(ad_comm::adprogram_name + ".rep");
  if (!report)
  {
    cerr << "error trying to open report file"  << ad_comm::adprogram_name << ".rep\n";
    return 0;
  }
  report << "report:" << endl;
  report << "ifn = " << m.ifn << endl;
  report << "quit_flag = " << m.quit_flag << endl;
  report << "ihflag = " << m.ihflag << endl;
  report << "last_phase() " << m.last_phase() << endl;
  report << "iexit = " << m.iexit << endl;
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
  report.close();

  // empty final_section

  return 0;
}
