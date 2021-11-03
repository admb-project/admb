#include "model_parameters.h"

class forest: public model_parameters
{
  data_int nsteps;
  data_int k;
  data_vector a;
  data_vector freq;
  int a_index;
  double sum_freq;
  param_init_bounded_number log_tau;
  param_init_bounded_number log_nu;
  param_init_bounded_number beta;
  param_init_bounded_number log_sigma;
  param_likeprof_number tau;
  param_stddev_number nu;
  param_stddev_number sigma;
  param_vector S;
  param_number prior_function_value;
  param_number likelihood_function_value;
  objective_function_value f;
public:
  forest(int sz,int argc, char * argv[]);
  virtual ~forest() {}
  void userfunction(void);
  void report(const dvector& gradients);
  void final_calcs(void) {}
  void initializationfunction(void);
  dvariable h(const dvariable& z);
};

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

forest::forest(int sz,int argc,char * argv[]): 
  model_parameters::model_parameters(sz, argc, argv) 
{
  nsteps.allocate("nsteps");
  k.allocate("k");
  a.allocate(1,k+1,"a");
  freq.allocate(1,k,"freq");
 sum_freq=sum(freq);
  initializationfunction();
  log_tau.allocate(-14,15,2,"log_tau");
  log_nu.allocate(-15,4,"log_nu");
  beta.allocate(.1,1.0,-1,"beta");
  log_sigma.allocate(-5,3,"log_sigma");
  tau.allocate("tau");
 tau.set_stepnumber(25);
  nu.allocate("nu");
  sigma.allocate("sigma");
  S.allocate(1,k+1,"S");
  #ifndef NO_AD_INITIALIZE
    S.initialize();
  #endif
  f.allocate("f");
  prior_function_value.allocate("prior_function_value");
  likelihood_function_value.allocate("likelihood_function_value");
}

void forest::initializationfunction(void)
{
  log_tau.set_initial_value(0);
  beta.set_initial_value(0.6666667);
  log_nu.set_initial_value(0);
  log_sigma.set_initial_value(-2);
}

void forest::userfunction(void)
{
  f =0.0;
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
     Integral=adromb2(&h2,tau, nu, sigma, beta, a(i), -3.0,3.0,nsteps);
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
}

dvariable forest::h(const dvariable& z)
{
  dvariable tmp;
  tmp=mfexp(-.5*z*z + tau*(-1.+mfexp(-nu*pow(a(a_index),beta)*mfexp(sigma*z))) );  
  return tmp;
}

void forest::report(const dvector& gradients)
{
 adstring ad_tmp=initial_params::get_reportfile_name();
  ofstream report((char*)(adprogram_name + ad_tmp));
  if (!report)
  {
    cerr << "error trying to open report file"  << adprogram_name << ".rep";
    return;
  }
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
}

long int arrmblsize=0;

int main(int argc,char * argv[])
{
    ad_set_new_handler();
  ad_exit=&ad_boundf;
    gradient_structure::set_NO_DERIVATIVES();
#ifdef DEBUG
  #ifndef __SUNPRO_C
std::feclearexcept(FE_ALL_EXCEPT);
  #endif
  auto start = std::chrono::high_resolution_clock::now();
#endif
    gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
    if (!arrmblsize) arrmblsize=15000000;
    forest mp(arrmblsize,argc,argv);
    mp.iprint=10;
    mp.preliminary_calculations();
    mp.computations(argc,argv);
#ifdef DEBUG
  std::cout << endl << argv[0] << " elapsed time is " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() << " microseconds." << endl;
  #ifndef __SUNPRO_C
bool failedtest = false;
if (std::fetestexcept(FE_DIVBYZERO))
  { cerr << "Error: Detected division by zero." << endl; failedtest = true; }
if (std::fetestexcept(FE_INVALID))
  { cerr << "Error: Detected invalid argument." << endl; failedtest = true; }
if (std::fetestexcept(FE_OVERFLOW))
  { cerr << "Error: Detected overflow." << endl; failedtest = true; }
if (std::fetestexcept(FE_UNDERFLOW))
  { cerr << "Error: Detected underflow." << endl; }
if (failedtest) { std::abort(); } 
  #endif
#endif
    return 0;
}
