#include <admodel.h>

#include <df1b2fun.h>

#include <adrndeff.h>

  extern "C"  {
    void ad_boundf(int i);
  }
#include <bcb.htp>

  df1b2_parameters * df1b2_parameters::df1b2_parameters_ptr=0;
  model_parameters * model_parameters::model_parameters_ptr=0;
model_data::model_data(int argc,char * argv[]) : ad_comm(argc,argv)
{
  n.allocate("n");
  D.allocate(1,n,1,7,"D");
  cv_N4.allocate(1,n);
  cv_P4.allocate(1,n);
  indN4.allocate(1,n);
  indP4.allocate(1,n);
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 model_data(argc,argv) , function_minimizer(sz)
{
  model_parameters_ptr=this;
  initializationfunction();
  log_s_eta.allocate(-10,10,"log_s_eta");
  log_p.allocate(1,n,"log_p");
  #ifndef NO_AD_INITIALIZE
    log_p.initialize();
  #endif
  Py.allocate(1,n,"Py");
  log_pi.allocate(1,1,"log_pi");
  a.allocate(0,1,"a");
  eta.allocate(1,n,"eta");
  g.allocate("g");  /* ADOBJECTIVEFUNCTION */
}
void model_parameters::userfunction(void)
{
  int i;
  // Contribution from random effects distribution
  g = -n*log_s_eta - .5*norm2(eta)/mfexp(2*log_s_eta);
  log_p  = log_pi(1) + eta;
  for(i=1;i<=n;i++)
  {
    if(indN4(i))
      g += -0.5*square((log(D(i,2)) - log_p(i) - a(0) - a(1)*(D(i,1)-1980))/cv_N4(i));		// Rate of increase verison
    if(indP4(i))
      g += -0.5*square((log(D(i,5))-log_p(i))/cv_P4(i));
  }
  g *= -1.0;				// ADMB does minimization !!!
  Py = exp(a(0) + a(1)*(column(D,1)-1980.0));
      
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
  report << "s_eta = " << exp(log_s_eta) << endl;
  report << "pi = " << exp(log_pi) << endl;
  report << "Py(1978-1983,1985-1988,1993,2001) = " << Py << endl;
  
     
}

void model_parameters::preliminary_calculations(void)
{

  admaster_slave_variable_interface(*this);
  cout << setprecision(4);
  // Punt's cv's
  cv_N4 = sqrt(log(square(elem_div(column(D,3),column(D,2)))+1.0));
  cv_P4 = sqrt(log(square(elem_div(column(D,6),column(D,5)))+1.0));
  indN4 = (ivector) column(D,4);
  indP4 = (ivector) column(D,7);
}
  long int arrmblsize=0;

int main(int argc,char * argv[])
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(300000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(20000);
  gradient_structure::set_MAX_NVAR_OFFSET(50850);
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
  int i;
  // Contribution from random effects distribution
  g = -n*log_s_eta - .5*norm2(eta)/mfexp(2*log_s_eta);
  log_p  = log_pi(1) + eta;
  for(i=1;i<=n;i++)
  {
    if(indN4(i))
      g += -0.5*square((log(D(i,2)) - log_p(i) - a(0) - a(1)*(D(i,1)-1980))/cv_N4(i));		// Rate of increase verison
    if(indP4(i))
      g += -0.5*square((log(D(i,5))-log_p(i))/cv_P4(i));
  }
  g *= -1.0;				// ADMB does minimization !!!
  Py = exp(a(0) + a(1)*(column(D,1)-1980.0));
      
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
  log_s_eta.allocate(-10,10,"log_s_eta");
  log_p.allocate(1,n,"log_p");
  #ifndef NO_AD_INITIALIZE
    log_p.initialize();
  #endif
  Py.allocate(1,n,"Py");
  log_pi.allocate(1,1,"log_pi");
  a.allocate(0,1,"a");
  eta.allocate(1,n,"eta");
  g.allocate("g");  /* ADOBJECTIVEFUNCTION */
}
