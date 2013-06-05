  #include <fvar.hpp>
  #include <dbgprint.cpp>
  
#include <admodel.h>

#include <df1b2fun.h>

#include <adrndeff.h>

  extern "C"  {
    void ad_boundf(int i);
  }
#include <spatial.htp>

  df1b2_parameters * df1b2_parameters::df1b2_parameters_ptr=0;
  model_parameters * model_parameters::model_parameters_ptr=0;
model_data::model_data(int argc,char * argv[]) : ad_comm(argc,argv)
{
  n.allocate("n");
  y.allocate(1,n,"y");
  p.allocate("p");
  X.allocate(1,n,1,p,"X");
  Z.allocate(1,n,1,2,"Z");
  dd.allocate(1,n,1,n);
  int i, j;
  // make the columns of X orthonormal
  dmatrix tX=trans(X);
  ncol1=norm(tX(1));
  tX(1)/=ncol1; 
  tX(2)-= tX(1)*tX(2)*tX(1);
  cout << tX(1)*tX(2) << endl;
  ncol2=norm(tX(2));
  tX(2)/=ncol2; 
  X=trans(tX);
  cout << norm(column(X,1)) << endl;
  cout << norm(column(X,2)) << endl;
  cout << column(X,1)*column(X,2) << endl;
  dd.initialize();
  for(i=1;i<=n;i++)
  {
    for ( j=1;j<i;j++)
    {
      dd(i,j)=sqrt(square(Z(i,1)-Z(j,1))+square(Z(i,2)-Z(j,2)));
      dd(j,i)=dd(i,j);
    }
  }
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 model_data(argc,argv) , function_minimizer(sz)
{
  model_parameters_ptr=this;
  initializationfunction();
  b.allocate(1,p,-100,100,"b");
  a.allocate(0.01,3.0,2,"a");
  log_sigma.allocate(-3.0,3.0,2,"log_sigma");
  u.allocate(1,n,2,"u");
  M.allocate(u,"M");
  l.allocate("l");  /* ADOBJECTIVEFUNCTION */
}
void model_parameters::userfunction(void)
{
  int i;
  //get_M(a);						// Calculate covariate matrix
  for (i=1;i<=n;i++)
    pois_loglik(i,u(i),b,log_sigma);			// Likelilhood contribution from i'th point
}

void SEPFUN1  model_parameters::pois_loglik(int i,const dvariable& ui,const dvar_vector& _b,const dvariable& _log_sigma)
{
  begin_df1b2_funnel();
    dvariable eta = X(i)*_b + exp(_log_sigma)*ui;	// Linear predictor
    dvariable lambda = mfexp(eta);			// Mean in Poisson distribution
    l += lambda-y(i)*eta;
  end_df1b2_funnel();
}

void SEPFUN1  model_parameters::get_M(const dvariable& _a)
{
  begin_df1b2_funnel();
  if (inner_opt_flag==0)
  {
      int i,j;
      dvar_matrix tmpM(1,n,1,n);
      for (i=1;i<=n;i++)
      {
        tmpM(i,i)=1.0;
        for ( j=1;j<i;j++)
        {
          tmpM(i,j)=exp(-_a*dd(i,j));			// Exponentially decaying correlation
          tmpM(j,i)=tmpM(i,j);
        }
      }
      //M=tmpM;
      if (M.dfpMinv){
        delete M.dfpMinv;
        M.dfpMinv=0;
      }
      M.dfpMinv=new dvar_matrix(inv(tmpM)); /* df1b2 Deletion Tag */
    if (quadratic_prior::matrix_mult_flag){
      M=tmpM;
  }
/* XXXX */ 
  }else{
/*CUTSNIP-BEGIN*/
    if (quadratic_prior::calc_matrix_flag){
    int i,j;
    dmatrix tmpM(1,n,1,n);
    for (i=1;i<=n;i++)
    {
      tmpM(i,i)=1.0;
      for ( j=1;j<i;j++)
      {
        tmpM(i,j)=exp(-value(_a)*dd(i,j));			// Exponentially decaying correlation
        tmpM(j,i)=tmpM(i,j);
      }
    }
    //M=tmpM;
      if (M.CM){
        delete M.CM;
        M.CM=0;
      }
      M.CM=new dmatrix(tmpM);
      if (M.SCM){
        delete M.SCM;
        M.SCM=0;
      }
    }
    if (quadratic_prior::matrix_mult_flag){
      M=*(M.CM);
  }
/*CUTSNIP-END*/ 
  } 
  end_df1b2_funnel();
}

void model_parameters::evaluate_M(void)
{
  get_M(a);
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
  cout << "b =" << b << "sigma=" << exp(log_sigma) << endl;
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
  gradient_structure::set_MAX_NVAR_OFFSET(460404);
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

void df1b2_normal_prior_M::get_cM(void)
{
  df1b2_parameters * mp=
    df1b2_parameters::get_df1b2_parameters_ptr();
  mp->evaluate_M();
}

void df1b2_normal_prior_M::get_Lxu(dmatrix& LXU)
{
  df1b2_parameters * mp=
    df1b2_parameters::get_df1b2_parameters_ptr();
  mp->evaluate_M();
  int rmin=Lxu->indexmin();
  int rmax=Lxu->indexmax();
  int cmin=1;
  int cmax=(*Lxu)(rmin).indexmax();
  if (cmax != LXU.indexmax())
  {
    cerr << "Shape error in get_Lxu" << endl;
    ad_exit(1);
  }
  
  for (int i=rmin;i<=rmax;i++)
  {
    int row = (int)((*Lxu)(i,0));
    for (int j=cmin;j<=cmax;j++)
    {
      LXU(j,row)+=(*Lxu)(i,j);
    }
  }
}

void df_normal_prior_M::get_cM(void)
{
  model_parameters * mp=
    model_parameters::get_model_parameters_ptr();
  mp->evaluate_M();
}
void df1b2_parameters::user_function(void)
{
  int i;
  //get_M(a);						// Calculate covariate matrix
  for (i=1;i<=n;i++)
    pois_loglik(i,u(i),b,log_sigma);			// Likelilhood contribution from i'th point
}

void   df1b2_pre_parameters::pois_loglik(int i,const funnel_init_df1b2variable& ui,const funnel_init_df1b2vector& _b,const funnel_init_df1b2variable& _log_sigma)
{
  begin_df1b2_funnel();
    df1b2variable eta = X(i)*_b + exp(_log_sigma)*ui;	// Linear predictor
    df1b2variable lambda = mfexp(eta);			// Mean in Poisson distribution
    l += lambda-y(i)*eta;
  end_df1b2_funnel();
}

void   df1b2_pre_parameters::get_M(const funnel_init_df1b2variable& _a)
{
  begin_df1b2_funnel();
  if (inner_opt_flag==0)
  {
      int i,j;
      df1b2matrix tmpM(1,n,1,n);
      for (i=1;i<=n;i++)
      {
        tmpM(i,i)=1.0;
        for ( j=1;j<i;j++)
        {
          tmpM(i,j)=exp(-_a*dd(i,j));			// Exponentially decaying correlation
          tmpM(j,i)=tmpM(i,j);
        }
      }
      //M=tmpM;
      if (M.dfpMinv){
        delete M.dfpMinv;
        M.dfpMinv=0;
      }
    if (quadratic_prior::matrix_mult_flag){
      M=tmpM;
  }
/* XXXX */ 
  }else{
/*CUTSNIP-BEGIN*/
    if (quadratic_prior::calc_matrix_flag){
    int i,j;
    dmatrix tmpM(1,n,1,n);
    for (i=1;i<=n;i++)
    {
      tmpM(i,i)=1.0;
      for ( j=1;j<i;j++)
      {
        tmpM(i,j)=exp(-value(_a)*dd(i,j));			// Exponentially decaying correlation
        tmpM(j,i)=tmpM(i,j);
      }
    }
    //M=tmpM;
      if (M.CM){
        delete M.CM;
        M.CM=0;
      }
      M.CM=new dmatrix(tmpM);
      if (M.SCM){
        delete M.SCM;
        M.SCM=0;
      }
    }
    if (quadratic_prior::matrix_mult_flag){
      M=*(M.CM);
  }
/*CUTSNIP-END*/ 
  } 
  end_df1b2_funnel();
}

void df1b2_parameters::evaluate_M(void)
{
  get_M(a);
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
  b.allocate(1,p,-100,100,"b");
  a.allocate(0.01,3.0,2,"a");
  log_sigma.allocate(-3.0,3.0,2,"log_sigma");
  u.allocate(1,n,2,"u");
  M.allocate(u,"M");
  l.allocate("l");  /* ADOBJECTIVEFUNCTION */
}
