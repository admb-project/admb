  #include <df1b2fun.h>
#include <admodel.h>

#include <df1b2fun.h>

#include <adrndeff.h>

  extern "C"  {
    void ad_boundf(int i);
  }
#include <orange2.htp>

  df1b2_parameters * df1b2_parameters::df1b2_parameters_ptr=0;
  model_parameters * model_parameters::model_parameters_ptr=0;
model_data::model_data(int argc,char * argv[]) : ad_comm(argc,argv)
{
  n.allocate("n");
  y.allocate(1,n,"y");
  t.allocate(1,n,"t");
  M.allocate("M");
  ngroup.allocate(1,M,"ngroup");
  m.allocate("m");
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 model_data(argc,argv) , function_minimizer(sz)
{
  model_parameters_ptr=this;
  initializationfunction();
  beta.allocate(1,3,-50,200,1,"beta");
  log_sigma.allocate(-5.0,5.0,1,"log_sigma");
  log_sigma_u.allocate(-5,5,2,"log_sigma_u");
  log_sigma_v.allocate(-5,5,2,"log_sigma_v");
  u.allocate(1,M,2,"u");
  v.allocate(1,7,2,"v");
  g.allocate("g");  /* ADOBJECTIVEFUNCTION */
}
void model_parameters::userfunction(void)
{
  int i,ii,j;
  dvar_vector a(1,3);		  		// Basic model function parameters
  dvariable tmp, f;
  dvariable sigma = mfexp(log_sigma);
  a(1) = 192.0 + beta(1);			
  a(2) = 726.0 + beta(2);
  a(3) = 356.0 + beta(3);
  g = 0.0;
  ii=0;
  for(i=1;i<=(int) M;i++)
  {
    for(j=1;j<=ngroup(i);j++)
    {
      ii++;
      g -= -log_sigma;
      f = (a(1)+u(i)+v(j))/(1+mfexp(-(t(ii)-a(2))/a(3)));
      tmp = y(ii) - f;
      tmp /= sigma;
      g -= -0.5*tmp*tmp;
    }
  }
  for(i=1;i<=M;i++)
  {    
    g -= -(log_sigma_u);
    g -= -.5*(square(u(i)/mfexp(log_sigma_u)));
  }
  for(j=1;j<=7;j++)
  {
    g -= -(log_sigma_v);
    g -= -.5*(square(v(j)/mfexp(log_sigma_v)));
  }
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
  //report << beta0+beta << endl;
  report << exp(log_sigma) << endl;
  report << exp(log_sigma_u) << endl;
  report << exp(log_sigma_v) << endl;
}

void model_parameters::preliminary_calculations(void)
{

  admaster_slave_variable_interface(*this);
  cout << setprecision(4);
}
  long int arrmblsize=0;

int main(int argc,char * argv[])
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;
  arrmblsize = 40000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(200000);
  gradient_structure::set_MAX_NVAR_OFFSET(10000);
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
  int i,ii,j;
  df1b2vector a(1,3);		  		// Basic model function parameters
  df1b2variable tmp, f;
  df1b2variable sigma = mfexp(log_sigma);
  a(1) = 192.0 + beta(1);			
  a(2) = 726.0 + beta(2);
  a(3) = 356.0 + beta(3);
  g = 0.0;
  ii=0;
  for(i=1;i<=(int) M;i++)
  {
    for(j=1;j<=ngroup(i);j++)
    {
      ii++;
      g -= -log_sigma;
      f = (a(1)+u(i)+v(j))/(1+mfexp(-(t(ii)-a(2))/a(3)));
      tmp = y(ii) - f;
      tmp /= sigma;
      g -= -0.5*tmp*tmp;
    }
  }
  for(i=1;i<=M;i++)
  {    
    g -= -(log_sigma_u);
    g -= -.5*(square(u(i)/mfexp(log_sigma_u)));
  }
  for(j=1;j<=7;j++)
  {
    g -= -(log_sigma_v);
    g -= -.5*(square(v(j)/mfexp(log_sigma_v)));
  }
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
  beta.allocate(1,3,-50,200,1,"beta");
  log_sigma.allocate(-5.0,5.0,1,"log_sigma");
  log_sigma_u.allocate(-5,5,2,"log_sigma_u");
  log_sigma_v.allocate(-5,5,2,"log_sigma_v");
  u.allocate(1,M,2,"u");
  v.allocate(1,7,2,"v");
  g.allocate("g");  /* ADOBJECTIVEFUNCTION */
}
