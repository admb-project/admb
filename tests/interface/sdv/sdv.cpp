#ifdef DEBUG
  #ifndef __SUNPRO_C
    #include <cfenv>
    #include <cstdlib>
  #endif
#endif
  //#include <df1b2fun.h>
#ifdef DEBUG
  #include <chrono>
#endif
#include <admodel.h>
#ifdef USE_ADMB_CONTRIBS
#include <contrib.h>
#endif
#include <df1b2fun.h>
#include <adrndeff.h>

class model_data : public ad_comm{
  public:
  data_int  n;
  data_vector y;
  ~model_data();
  model_data(int argc,char * argv[]);
  friend class model_parameters;
};

class model_parameters : public model_data ,
  public function_minimizer
{
public:
  friend class df1b2_pre_parameters;
  friend class df1b2_parameters;
  static model_parameters * model_parameters_ptr;
  static model_parameters * get_model_parameters_ptr(void)
  {
    return model_parameters_ptr;
  }
  ~model_parameters();
  void preliminary_calculations(void);
  void set_runtime(void);
  static int mc_phase(void)
  {
    return initial_params::mc_phase;
  }
  static int mceval_phase(void)
  {
    return initial_params::mceval_phase;
  }
  static int hessian_phase(void)
  {
    return initial_params::in_hessian_phase;
  }
  static int sd_phase(void)
  {
    return initial_params::sd_phase;
  }
  static int current_phase(void)
  {
    return initial_params::current_phase;
  }
  static int last_phase(void)
  {
    return (initial_params::current_phase
      >=initial_params::max_number_phases);
  }
  static prevariable current_feval(void)
  {
    return *objective_function_value::pobjfun;
  }
private:
  ivector integer_control_flags;
  void begin_df1b2_funnel(void);
  void end_df1b2_funnel(void);
  dvector double_control_flags;
  param_init_bounded_number b;
  param_init_bounded_number log_sigma;
  param_init_bounded_number mu;
  param_init_bounded_number mu_x;
  random_effects_vector x;
  param_number prior_function_value;
  param_number likelihood_function_value;
  objective_function_value  g;
public:
  virtual void userfunction(void);
  virtual void report(const dvector& gradients);
  virtual void final_calcs(void);
  model_parameters(int sz,int argc, char * argv[]);
  virtual void initializationfunction(void){}
  virtual void AD_uf_inner(void){pre_userfunction();}
  virtual void AD_uf_outer(void){pre_userfunction();}
  virtual void user_function(void){;}
  virtual void allocate(void){;}
  void sf1(const dvariable& ls,const dvariable& bb,const dvariable& x_1);
  void sf2(const dvariable& ls,const dvariable& bb,const dvariable& x_i,const dvariable& x_i1);
  void sf3(const dvariable& x_i ,const dvariable& mu ,const dvariable& mu_x ,int i);
};
  
class df1b2_pre_parameters : public model_parameters
{ 
public: 
  df1b2_pre_parameters(int sz,int argc, char * argv[]) : 
    model_parameters(sz,argc,argv){;}
  re_objective_function_value  g;
  void begin_df1b2_funnel(void); 
  void setup_quadprior_calcs(void); 
  void end_df1b2_funnel(void);
 void sf1(const funnel_init_df1b2variable& ls,const funnel_init_df1b2variable& bb,const funnel_init_df1b2variable& x_1);
 void sf2(const funnel_init_df1b2variable& ls,const funnel_init_df1b2variable& bb,const funnel_init_df1b2variable& x_i,const funnel_init_df1b2variable& x_i1);
 void sf3(const funnel_init_df1b2variable& x_i ,const funnel_init_df1b2variable& mu ,const funnel_init_df1b2variable& mu_x ,int i);
}; 
 
class df1b2_parameters : public df1b2_pre_parameters 
{ 
public: 
  static df1b2_parameters * df1b2_parameters_ptr;
  static df1b2_parameters * get_df1b2_parameters_ptr(void) 
  { 
    return df1b2_parameters_ptr; 
  } 
  void deallocate(); 
  df1b2_parameters(int sz,int argc, char * argv[]) : 
    df1b2_pre_parameters(sz,argc,argv) 
  { 
    df1b2_parameters_ptr=this;
  }
  df1b2_init_bounded_number b;
  df1b2_init_bounded_number log_sigma;
  df1b2_init_bounded_number mu;
  df1b2_init_bounded_number mu_x;
  df1b2_init_vector x;
  df1b2variable prior_function_value;
  df1b2variable likelihood_function_value;
   // re_objective_function_value  g;
  virtual void user_function(void); 
  virtual void allocate(void); 
 // void begin_df1b2_funnel(void); 
 // void setup_quadprior_calcs(void); 
 // void end_df1b2_funnel(void);

};

  extern "C"  {
    void ad_boundf(int i);
  }

  df1b2_parameters * df1b2_parameters::df1b2_parameters_ptr=0;
  model_parameters * model_parameters::model_parameters_ptr=0;
model_data::model_data(int argc,char * argv[]) : ad_comm(argc,argv)
{
  adstring tmpstring;
  tmpstring=adprogram_name + adstring(".dat");
  if (argc > 1)
  {
    int on=0;
    if ( (on=option_match(argc,argv,"-ind"))>-1)
    {
      if (on>argc-2 || argv[on+1][0] == '-')
      {
        cerr << "Invalid input data command line option"
                " -- ignored" << endl;
      }
      else
      {
        tmpstring = adstring(argv[on+1]);
      }
    }
  }
  global_datafile = new cifstream(tmpstring);
  if (!global_datafile)
  {
    cerr << "Error: Unable to allocate global_datafile in model_data constructor.";
    ad_exit(1);
  }
  if (!(*global_datafile))
  {
    delete global_datafile;
    global_datafile=NULL;
  }
  n.allocate("n");
  y.allocate(1,n,"y");
  if (global_datafile)
  {
    delete global_datafile;
    global_datafile = NULL;
  }
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 model_data(argc,argv) , function_minimizer(sz)
{
  model_parameters_ptr=this;
  initializationfunction();
  b.allocate(-.9999,.9999,2,"b");
  log_sigma.allocate(-3.0,3.0,2,"log_sigma");
  mu.allocate(-10,10,-1,"mu");
  mu_x.allocate(-10,3,1,"mu_x");
  x.allocate(1,n,2,"x");
  prior_function_value.allocate("prior_function_value");
  likelihood_function_value.allocate("likelihood_function_value");
  g.allocate("g");  /* ADOBJECTIVEFUNCTION */
}
void model_parameters::userfunction(void)
{
  g =0.0;
  int i;	
  sf1(log_sigma,b,x(1));
  for (i=2;i<=n;i++)
  {
    sf2(log_sigma,b,x(i),x(i-1));
  }
  for (i=1;i<=n;i++)
  {
    sf3(x(i),mu,mu_x,i);
  }
}

void model_parameters::sf1(const dvariable& ls,const dvariable& bb,const dvariable& x_1)
{
  begin_df1b2_funnel();
  g -= -ls + 0.5*log(1-square(bb))  - 0.5*square(x_1/mfexp(ls))*(1-square(bb));
  end_df1b2_funnel();
}

void model_parameters::sf2(const dvariable& ls,const dvariable& bb,const dvariable& x_i,const dvariable& x_i1)
{
  begin_df1b2_funnel();
  g -= -ls - .5*square((x_i-bb*x_i1)/mfexp(ls));
  end_df1b2_funnel();
}

void model_parameters::sf3(const dvariable& x_i ,const dvariable& mu ,const dvariable& mu_x ,int i)
{
  begin_df1b2_funnel();
  dvariable log_sigma_y = 0.5*(mu_x + x_i);
  dvariable sigma_y = mfexp(log_sigma_y);
  g -= -log_sigma_y - .5*square((y(i)-mu)/sigma_y);
  end_df1b2_funnel();
}

void model_parameters::report(const dvector& gradients)
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

  #if defined(USE_ADPVM)

  admaster_slave_variable_interface(*this);

  #endif
  cout << setprecision(4);
}
  long int arrmblsize=0;

int main(int argc,char * argv[])
{
#ifdef DEBUG
  auto start = std::chrono::high_resolution_clock::now();
  #ifndef __SUNPRO_C
std::feclearexcept(FE_ALL_EXCEPT);
  #endif
#endif
  ad_set_new_handler();
  ad_exit=&ad_boundf;
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(300000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(20000);
  gradient_structure::set_MAX_NVAR_OFFSET(50850);
    gradient_structure::set_NO_DERIVATIVES();
    gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      if (!arrmblsize) arrmblsize=150000;
    df1b2variable::noallocate=1;
df1b2variable::pool = new adpool();
initial_df1b2params::varsptr = new P_INITIAL_DF1B2PARAMS[1000];
{
    df1b2_parameters mp(arrmblsize,argc,argv);
    mp.iprint=10;

    function_minimizer::random_effects_flag=1;
    df1b2variable::noallocate=0;
    mp.preliminary_calculations();
    initial_df1b2params::separable_flag=1;
    mp.computations(argc,argv);
}
delete [] init_df1b2variable::list;
init_df1b2variable::list = NULL;
delete [] initial_df1b2params::varsptr;
initial_df1b2params::varsptr = NULL;
delete df1b2variable::pool;
df1b2variable::pool = NULL;
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

void df1b2_parameters::user_function(void)
{
  g =0.0;
  int i;	
  sf1(log_sigma,b,x(1));
  for (i=2;i<=n;i++)
  {
    sf2(log_sigma,b,x(i),x(i-1));
  }
  for (i=1;i<=n;i++)
  {
    sf3(x(i),mu,mu_x,i);
  }
}

void   df1b2_pre_parameters::sf1(const funnel_init_df1b2variable& ls,const funnel_init_df1b2variable& bb,const funnel_init_df1b2variable& x_1)
{
  begin_df1b2_funnel();
  g -= -ls + 0.5*log(1-square(bb))  - 0.5*square(x_1/mfexp(ls))*(1-square(bb));
  end_df1b2_funnel();
}

void   df1b2_pre_parameters::sf2(const funnel_init_df1b2variable& ls,const funnel_init_df1b2variable& bb,const funnel_init_df1b2variable& x_i,const funnel_init_df1b2variable& x_i1)
{
  begin_df1b2_funnel();
  g -= -ls - .5*square((x_i-bb*x_i1)/mfexp(ls));
  end_df1b2_funnel();
}

void   df1b2_pre_parameters::sf3(const funnel_init_df1b2variable& x_i ,const funnel_init_df1b2variable& mu ,const funnel_init_df1b2variable& mu_x ,int i)
{
  begin_df1b2_funnel();
  df1b2variable log_sigma_y = 0.5*(mu_x + x_i);
  df1b2variable sigma_y = mfexp(log_sigma_y);
  g -= -log_sigma_y - .5*square((y(i)-mu)/sigma_y);
  end_df1b2_funnel();
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
  funnel_init_var::deallocate_all(); 
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

void df1b2_parameters::deallocate() 
{
  b.deallocate();
  log_sigma.deallocate();
  mu.deallocate();
  mu_x.deallocate();
  x.deallocate();
  prior_function_value.deallocate();
  likelihood_function_value.deallocate();
  g.deallocate();
} 
void df1b2_parameters::allocate(void) 
{
  b.allocate(-.9999,.9999,2,"b");
  log_sigma.allocate(-3.0,3.0,2,"log_sigma");
  mu.allocate(-10,10,-1,"mu");
  mu_x.allocate(-10,3,1,"mu_x");
  x.allocate(1,n,2,"x");
  prior_function_value.allocate("prior_function_value");
  likelihood_function_value.allocate("likelihood_function_value");
  g.allocate("g");  /* ADOBJECTIVEFUNCTION */
}
