  #include <fvar.hpp>
  #include <dbgprint.cpp>
  
#include <admodel.h>

#include <df1b2fun.h>

#include <adrndeff.h>

  extern "C"  {
    void ad_boundf(int i);
  }
#include <small.htp>

  df1b2_parameters * df1b2_parameters::df1b2_parameters_ptr=0;
  model_parameters * model_parameters::model_parameters_ptr=0;
model_data::model_data(int argc,char * argv[]) : ad_comm(argc,argv)
{
 n=10;
  obs.allocate(1,n);
 obs.fill_seqadd(1.0,1.0);
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 model_data(argc,argv) , function_minimizer(sz)
{
  model_parameters_ptr=this;
  initializationfunction();
  x.allocate("x");
 int n1=n*(n-1)/2;
  v.allocate(1,n1,-10.8,10.,"v");
  u.allocate(1,n,"u");
  M.allocate(1,n,1,n,"M");
  #ifndef NO_AD_INITIALIZE
    M.initialize();
  #endif
  f.allocate("f");  /* ADOBJECTIVEFUNCTION */
}
void model_parameters::userfunction(void)
{
   int offset=1;
   M.initialize();
   for (int i=1;i<=n;i++)
   {
     M(i,i)=1.0;
     if (i>1)
     {
       M(i,i-1)=v(offset);
       offset+=1;
       M(i)/=norm(M(i));
     }
   }
   M=M*trans(M);
   dvar_matrix N=inv(M);
   f=norm2(obs-x-N*u);
   f+=0.5*norm2(u);
   f+=0.5*norm2(v);
       
}
  long int arrmblsize=0;

int main(int argc,char * argv[])
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;
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


#define __DF1B2PART__
void df1b2_parameters::user_function(void)
{
   int offset=1;
   M.initialize();
   for (int i=1;i<=n;i++)
   {
     M(i,i)=1.0;
     if (i>1)
     {
       M(i,i-1)=v(offset);
       offset+=1;
       M(i)/=norm(M(i));
     }
   }
   M=M*trans(M);
   df1b2matrix N=inv(M);
   f=norm2(obs-x-N*u);
   f+=0.5*norm2(u);
   f+=0.5*norm2(v);
       
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
  x.allocate("x");
 int n1=n*(n-1)/2;
  v.allocate(1,n1,-10.8,10.,"v");
  u.allocate(1,n,"u");
  M.allocate(1,n,1,n,"M");
  #ifndef NO_AD_INITIALIZE
    M.initialize();
  #endif
  f.allocate("f");  /* ADOBJECTIVEFUNCTION */
}
