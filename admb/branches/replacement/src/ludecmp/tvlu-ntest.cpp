  #include "ntest.cpp"
#include <admodel.h>

  extern "C"  {
    void ad_boundf(int i);
  }
#include <tvlu-ntest.htp>

model_data::model_data(int argc,char * argv[]) : ad_comm(argc,argv)
{
 n=25;
  C.allocate(1,n,1,n);
  Id.allocate(1,n,1,n);
  random_number_generator rng(873);
  C.fill_randn(rng);
  Id.initialize();
  for (int i=1;i<=n;i++)
    Id(i,i)=1.0;
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 model_data(argc,argv) , function_minimizer(sz)
{
  initializationfunction();
  A.allocate(1,n,1,n,"A");
  f.allocate("f");
}

void model_parameters::userfunction(void)
{
  cout << norm2(inv(A+C)*(A+C)-Id)<< endl;
  f=norm2(inv(A+C));
}

void model_parameters::preliminary_calculations(void){
  admaster_slave_variable_interface(*this);
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
  gradient_structure::set_MAX_NVAR_OFFSET(625);
    gradient_structure::set_NO_DERIVATIVES();
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

extern "C"  {
  void ad_boundf(int i)
  {
    /* so we can stop here */
    exit(i);
  }
}
