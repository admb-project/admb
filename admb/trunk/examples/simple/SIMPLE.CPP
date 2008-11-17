#include <admodel.h>

#include <simple.htp>

model_data::model_data()
{
  nobs.allocate("nobs");
  Y.allocate(1,nobs,"Y");
  x.allocate(1,nobs,"x");
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 ad_comm(argc,argv), model_data() , function_minimizer(sz)
{
  initializationfunction();
  a.allocate("a");
  b.allocate("b");
  pred_Y.allocate(1,nobs,"pred_Y");
  #ifndef NO_AD_INITIALIZE
    pred_Y.initialize();
  #endif
  f.allocate("f");
}

void model_parameters::userfunction(void)
{
  pred_Y=a*x+b;
  f=(norm2(pred_Y-Y)); 
  f=nobs/2.*log(f);    // make it a likelihood function so that
                       // covariance matrix is correct
}

void model_parameters::preliminary_calculations(void){}

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