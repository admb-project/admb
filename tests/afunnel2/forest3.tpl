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
   funnel_dvariable Integral;
   int i;
   for (i=1;i<=k+1;i++)
   {
     a_index=i;
     ad_begin_funnel();
     Integral=adromb2(&h2,tau,nu,sigma,beta,a(a_index),-3.0,3.0,nsteps);
     S(i)=Integral;
   }
   f=0.0;
   for (i=1;i<=k;i++)
   {
     dvariable ff=0.0;
     dvariable diff=posfun((S(i)-S(i+1))/S(i),.000001,ff);
     f-=freq(i)*log(1.e-50+S(i)*diff);
     f+=ff;
   }
   f+=sum_freq*log(1.e-50+S(1));
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
GLOBALS_SECTION
  #include <fvar.hpp>
  #include <admodel.h>

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
