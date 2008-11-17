#include <admodel.h>

#include <finance.htp>

model_data::model_data()
{
  T.allocate("T");
  r.allocate(0,T,"r");
  sub_r.allocate(1,T);
}

void model_parameters::initializationfunction(void)
{
  a0.set_initial_value(.1);
  a1.set_initial_value(.1);
  a2.set_initial_value(.1);
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 ad_comm(argc,argv), model_data() , function_minimizer(sz)
{
  initializationfunction();
  a0.allocate(0.0,1.0,"a0");
  a1.allocate(0.0,1.0,2,"a1");
  a2.allocate(0.0,1.0,3,"a2");
  Mean.allocate("Mean");
  eps2.allocate(1,T,"eps2");
  #ifndef NO_AD_INITIALIZE
    eps2.initialize();
  #endif
  h.allocate(1,T,"h");
  #ifndef NO_AD_INITIALIZE
    h.initialize();
  #endif
  log_likelihood.allocate("log_likelihood");
}

void model_parameters::preliminary_calculations(void)
{
  h0=square(std_dev(r));   // square forms the element-wise square 
  sub_r=r(1,T);    // form a subvector so we can use vector operations
  Mean=mean(r);    // calculate the mean of the vector r 
}

void model_parameters::userfunction(void)
{
  eps2=square(sub_r-Mean);   
  h(1)=a0+a2*h0;
  for (int t=2;t<=T;t++)
  {
    h(t)=a0+a1*eps2(t-1)+a2*h(t-1);
  }
  // calculate minus the log-likelihood function and assign it to
  // the object of type objective_function_value
  log_likelihood=.5*sum(log(h)+elem_div(eps2,h));  // elem_div performs  
          // element-wise division of vectors
}

  model_data::~model_data(){}

void model_parameters::report(void){}

void function_minimizer::set_runtime(void){}

#ifdef _BORLANDC_
  extern unsigned _stklen=10000U;
#endif


#ifdef __ZTC__
  extern unsigned int _stack=10000U;
#endif

  long int arrmblsize=0;

int main(int argc,char * argv[])
{
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
  #if defined(__GNUDOS__) || defined(DOS386) || defined(__DPMI32__)  || \
     defined(__MSVC32__)
    if (!arrmblsize) arrmblsize=150000;
  #else
    if (!arrmblsize) arrmblsize=25000;
  #endif
  model_parameters mp(arrmblsize,argc,argv);
  mp.iprint=10;
  mp.preliminary_calculations();
  mp.computations(argc,argv);
  return 0;
}
