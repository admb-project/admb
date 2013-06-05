#include <admodel.h>

#include <df1b2fun.h>

#include <adrndeff.h>

  extern "C"  {
    void ad_boundf(int i);
  }
#include <kidney.htp>

  df1b2_parameters * df1b2_parameters::df1b2_parameters_ptr=0;
  model_parameters * model_parameters::model_parameters_ptr=0;
model_data::model_data(int argc,char * argv[]) : ad_comm(argc,argv)
{
  n.allocate("n");
  age.allocate(1,n,1,2,"age");
  sex.allocate(1,n,"sex");
  disease.allocate(1,n,"disease");
  t.allocate(1,n,1,2,"t");
  logt.allocate(1,n,1,2);
  delta.allocate(1,n,1,2,"delta");
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 model_data(argc,argv) , function_minimizer(sz)
{
  model_parameters_ptr=this;
  initializationfunction();
  b0.allocate(-8,2,"b0");
  b_age.allocate(-.1,.1,"b_age");
  b_disease.allocate(1,3,-3,3,"b_disease");
  b_sex.allocate(-3,3,"b_sex");
  r.allocate(.5,2,"r");
  log_sigma.allocate(-6.0,1.0,"log_sigma");
  u.allocate(1,n,"u");
  g.allocate("g");  /* ADOBJECTIVEFUNCTION */
}
void model_parameters::userfunction(void)
{
  int i, j;
  dvariable sigma, eta, h0t, ht, Ht;                      // Local variables 
  sigma = exp(log_sigma);
  g = -n*log(sigma)-0.5*norm2(u/sigma); // log[h(u)]
  for(i=1;i<=n;i++)                     
  {
    for(j=1;j<=2;j++)                     
    {
      eta = b0 + b_age*age(i,j) + b_sex*sex(i) + u(i);
      if(disease(i)>1)
        eta += b_disease(disease(i)-1);
      h0t = r*exp(logt(i,j)*(r-1));     // Baseline hazard
      ht = h0t * mfexp(eta);            // Hazard function    
      Ht = ht*t(i,j)/r;                 // Cumulative hazard
 
      g += delta(i,j)*log(ht) - Ht;     // log[f(y|u)] 
    }
  }
  g *= -1;
}

void model_parameters::report()
{
 adstring ad_tmp=initial_params::get_reportfile_name();
  ofstream report((char*)(adprogram_name + ad_tmp));
  if (!report)
  {
    cerr << "error trying to open report file"  << adprogram_name << ".rep";
    return;
  }
}

void model_parameters::preliminary_calculations(void)
{

  admaster_slave_variable_interface(*this);
  cout << setprecision(4);
  logt = log(t);
}
  long int arrmblsize=0;

int main(int argc,char * argv[])
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;
  arrmblsize = 400000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(300000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(20000);
  gradient_structure::set_MAX_NVAR_OFFSET(2000);
    gradient_structure::set_NO_DERIVATIVES();
    gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
  #if defined(__GNUDOS__) || defined(DOS386) || defined(__DPMI32__)  || \
     defined(__MSVC32__)
      if (!arrmblsize) arrmblsize=150000;
  #else
      if (!arrmblsize) arrmblsize=25000;
  #endif
    df1b2variable::noallocate=1;
    df1b2_parameters mp(arrmblsize,argc,argv);
    mp.iprint=10;

    function_minimizer::random_effects_flag=1;
    df1b2variable::noallocate=0;
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

model_data::~model_data()
{}

model_parameters::~model_parameters()
{}

void model_parameters::final_calcs(void){}

void model_parameters::set_runtime(void){}

#ifdef _BORLANDC_
  extern unsigned _stklen=10000U;
#endif


#ifdef __ZTC__
  extern unsigned int _stack=10000U;
#endif


#define __DF1B2PART__
void df1b2_parameters::user_function(void)
{
  int i, j;
  df1b2variable sigma, eta, h0t, ht, Ht;                      // Local variables 
  sigma = exp(log_sigma);
  g = -n*log(sigma)-0.5*norm2(u/sigma); // log[h(u)]
  for(i=1;i<=n;i++)                     
  {
    for(j=1;j<=2;j++)                     
    {
      eta = b0 + b_age*age(i,j) + b_sex*sex(i) + u(i);
      if(disease(i)>1)
        eta += b_disease(disease(i)-1);
      h0t = r*exp(logt(i,j)*(r-1));     // Baseline hazard
      ht = h0t * mfexp(eta);            // Hazard function    
      Ht = ht*t(i,j)/r;                 // Cumulative hazard
 
      g += delta(i,j)*log(ht) - Ht;     // log[f(y|u)] 
    }
  }
  g *= -1;
}
   
void df1b2_pre_parameters::setup_quadprior_calcs(void) 
{ 
  df1b2_gradlist::set_no_derivatives(); 
  quadratic_prior::in_qp_calculations=1; 
}  
  
void df1b2_pre_parameters::begin_df1b2_funnel(void) 
{ 
  (*re_objective_function_value::pobjfun)=0; 
  other_separable_stuff_begin(); 
  f1b2gradlist->reset();  
  if (!quadratic_prior::in_qp_calculations) 
  { 
    df1b2_gradlist::set_yes_derivatives();  
  } 
  funnel_init_var::allocate_all();  
}  
 
void df1b2_pre_parameters::end_df1b2_funnel(void) 
{  
  lapprox->do_separable_stuff(); 
  other_separable_stuff_end(); 
} 
  
void model_parameters::begin_df1b2_funnel(void) 
{ 
  if (lapprox)  
  {  
    {  
      begin_funnel_stuff();  
    }  
  }  
}  
 
void model_parameters::end_df1b2_funnel(void) 
{  
  if (lapprox)  
  {  
    end_df1b2_funnel_stuff();  
  }  
} 

void df1b2_parameters::allocate(void) 
{
  b0.allocate(-8,2,"b0");
  b_age.allocate(-.1,.1,"b_age");
  b_disease.allocate(1,3,-3,3,"b_disease");
  b_sex.allocate(-3,3,"b_sex");
  r.allocate(.5,2,"r");
  log_sigma.allocate(-6.0,1.0,"log_sigma");
  u.allocate(1,n,"u");
  g.allocate("g");  /* ADOBJECTIVEFUNCTION */
}
