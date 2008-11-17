#include <admodel.h>

#include <vonb.htp>

model_data::model_data()
{
  nobs.allocate("nobs");
  data.allocate(1,nobs,1,2,"data");
  age.allocate(1,nobs);
  size.allocate(1,nobs);
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 ad_comm(argc,argv), model_data() , function_minimizer(sz)
{
  initializationfunction();
  linf.allocate("linf");
  K.allocate("K");
  t0.allocate("t0");
  pred_size.allocate(1,nobs,"pred_size");
  #ifndef NO_AD_INITIALIZE
    pred_size.initialize();
  #endif
  f.allocate("f");
}

void model_parameters::preliminary_calculations(void)
{
  // get the data out of the columns of the data matrix 
  age=column(data,1);
  size=column(data,2);
  linf=1.1*max(size);  // set linf to 1.1 times the longest observed length
}

void model_parameters::userfunction(void)
{
  // like pred_size(i)=linf*(1-exp(-K*(age(i)-t0))) without loops
  pred_size=linf*(1.-exp(-K*(age-t0)));
  f=regression(size,pred_size);
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