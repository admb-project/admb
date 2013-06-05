  #include <df1b2fun.h>
#include <admodel.h>

#include <df1b2fun.h>

#include <adrndeff.h>

  extern "C"  {
    void ad_boundf(int i);
  }
#include <nested4.htp>

  df1b2_parameters * df1b2_parameters::df1b2_parameters_ptr=0;
  model_parameters * model_parameters::model_parameters_ptr=0;
model_data::model_data(int argc,char * argv[]) : ad_comm(argc,argv)
{
  N.allocate("N");
  m.allocate(1,4,"m");
 mm = 1+m(2)*(1+m(3)*(1+m(4)));		// Total number of random effects under each top level
 m1 = m(1);		
 m2m3m4 = m(2)*m(3)*m(4);		
  y.allocate(1,m1,1,m2m3m4,"y");
  indI.allocate(1,3,"indI");
  I.allocate(1,m2m3m4,1,3,"I");
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 model_data(argc,argv) , function_minimizer(sz)
{
  model_parameters_ptr=this;
  initializationfunction();
  b.allocate(1,1,-10,10,1,"b");
  log_sigma.allocate(1,4,-6,5,2,"log_sigma");
  u.allocate(1,m1,1,mm,2,"u");
  g.allocate("g");  /* ADOBJECTIVEFUNCTION */
}
void model_parameters::userfunction(void)
{
  int i;
  g = 0.0;
  for(i=1;i<=m(1);i++)
    fit_group_i(b,log_sigma,u(i),i);
}

void SEPFUN1  model_parameters::fit_group_i(const dvar_vector& b, const dvar_vector& ls, const dvar_vector& U,const  int& i)
{
  begin_df1b2_funnel();
    int j;
    // Likelihood contribution from unscaled random effects
    g -= -0.5*norm2(U);
    dvar_vector sigma(1,4);
    sigma = exp(ls);
    // Scaling up the random effects by multiplication with SD
    dvar_vector uu(1,mm);		
    uu(1) = sigma(1)*U(1);
    for(j=2;j<=indI(1);j++)
      uu(j) = sigma(2)*U(j);
    for(j=indI(1)+1;j<=indI(2);j++)
      uu(j) = sigma(3)*U(j);
    for(j=indI(2)+1;j<=indI(3);j++)
      uu(j) = sigma(4)*U(j);
    dvariable eta;			// Linear predictor
    for(j=1;j<=m2m3m4;j++)
    {
      eta = b(1) + uu(1) + uu(I(j,1)) + uu(I(j,2)) + uu(I(j,3));  // That is: u_i + u_ij + u_ijk + u_ijkl
      g -= y(i,j)*eta - N*log(1+exp(eta));
    }
  end_df1b2_funnel();
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
  //report << "b =" << b << "sigma=" << sigma << endl;
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
  arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(200000);
  gradient_structure::set_MAX_NVAR_OFFSET(20000);
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
    initial_df1b2params::separable_flag=1;
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
  g = 0.0;
  for(i=1;i<=m(1);i++)
    fit_group_i(b,log_sigma,u(i),i);
}

void   df1b2_pre_parameters::fit_group_i(const funnel_init_df1b2vector& b, const funnel_init_df1b2vector& ls, const funnel_init_df1b2vector& U,const  int& i)
{
  begin_df1b2_funnel();
    int j;
    // Likelihood contribution from unscaled random effects
    g -= -0.5*norm2(U);
    df1b2vector sigma(1,4);
    sigma = exp(ls);
    // Scaling up the random effects by multiplication with SD
    df1b2vector uu(1,mm);		
    uu(1) = sigma(1)*U(1);
    for(j=2;j<=indI(1);j++)
      uu(j) = sigma(2)*U(j);
    for(j=indI(1)+1;j<=indI(2);j++)
      uu(j) = sigma(3)*U(j);
    for(j=indI(2)+1;j<=indI(3);j++)
      uu(j) = sigma(4)*U(j);
    df1b2variable eta;			// Linear predictor
    for(j=1;j<=m2m3m4;j++)
    {
      eta = b(1) + uu(1) + uu(I(j,1)) + uu(I(j,2)) + uu(I(j,3));  // That is: u_i + u_ij + u_ijk + u_ijkl
      g -= y(i,j)*eta - N*log(1+exp(eta));
    }
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
  b.allocate(1,1,-10,10,1,"b");
  log_sigma.allocate(1,4,-6,5,2,"log_sigma");
  u.allocate(1,m1,1,mm,2,"u");
  g.allocate("g");  /* ADOBJECTIVEFUNCTION */
}
