  int NSLAVES = 7;
#include <admodel.h>
#include <contrib.h>

  extern "C"  {
    void ad_boundf(int i);
  }
#include <msimple1.htp>

model_data::model_data(int argc,char * argv[]) : ad_comm(argc,argv)
{
 ad_comm::change_datafile_name("msimple.dat");
  nobs.allocate("nobs");
 nslaves = NSLAVES;
  Y.allocate(1,nslaves,1,nobs);
  x.allocate(1,nslaves,1,nobs);
    double A = 2.0;
    double B = 4.0;
    random_number_generator rng(101);
    dvector err(1,nobs);
    for (int i = 1; i <= nslaves; i++)
    {
       x(i).fill_randu(rng);
       x(i) *= 100.0;
       Y(i) = A*x(i) + B;
       err.fill_randn(rng);
       Y(i) += 5.0*err;
    }
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 model_data(argc,argv) , function_minimizer(sz)
{
  initializationfunction();
  a.allocate("a");
  b.allocate("b");
  ff.allocate(1,nslaves,"ff");
  #ifndef NO_AD_INITIALIZE
    ff.initialize();
  #endif
  pred_Y.allocate(1,nslaves,1,nobs,"pred_Y");
  #ifndef NO_AD_INITIALIZE
    pred_Y.initialize();
  #endif
  f.allocate("f");
  prior_function_value.allocate("prior_function_value");
  likelihood_function_value.allocate("likelihood_function_value");
}

void model_parameters::preliminary_calculations(void)
{

  admaster_slave_variable_interface(*this);
  a = 1.0;
  b = 2.0;
}

void model_parameters::userfunction(void)
{
  f =0.0;
  for (int i=1;i<=nslaves;i++)
  {
      pred_Y(i) = a * x(i) +  b;
      ff(i) = norm2(pred_Y(i)-Y(i)); 
      ff(i) = nobs/2.*log(ff(i));    // make it a likelihood function so that
                                    // covariance matrix is correct
  }
  f = sum(ff);
}

model_data::~model_data()
{}

model_parameters::~model_parameters()
{}

void model_parameters::report(void){}

void model_parameters::final_calcs(void){}

void model_parameters::set_runtime(void){}

#ifdef _BORLANDC_
  extern unsigned _stklen=10000U;
#endif


#ifdef __ZTC__
  extern unsigned int _stack=10000U;
#endif

  long int arrmblsize=0;

int main(int argc,char * argv[])
{
    ad_set_new_handler();
  ad_exit=&ad_boundf;
    gradient_structure::set_NO_DERIVATIVES();
    gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
    if (!arrmblsize) arrmblsize=15000000;
    model_parameters mp(arrmblsize,argc,argv);
    mp.iprint=10;
    mp.preliminary_calculations();
    mp.computations(argc,argv);
    return 0;
}

extern "C"  {
  void ad_boundf(int i)
  {
    /* so we can stop here */
    exit(i);
  }
}
