
DATA_SECTION
  init_int nobs
  init_int n0
  init_int n1
  init_int n2
  init_int n3
  init_int n4
  init_int n5
  init_matrix obs(1,nobs,1,7)

PARAMETER_SECTION
  init_vector a(1,n0)
  init_bounded_number log_sigma1(-3.0,3.0,3)
  init_bounded_number log_sigma2(-3.0,3.0,3)
  init_bounded_number log_sigma3(-3.0,3.0,3)
  init_bounded_number log_sigma4(-3.0,3.0,3)
  init_bounded_number log_sigma5(-3.0,3.0,3)
  sdreport_number sigma1
  sdreport_number sigma2
  sdreport_number sigma3
  sdreport_number sigma4
  sdreport_number sigma5
  random_effects_vector u1(1,n1,2)
  random_effects_vector u2(1,n2,2)
  random_effects_vector u3(1,n3,2)
  random_effects_vector u4(1,n4,2)
  random_effects_vector u5(1,n5,2)
  objective_function_value f;

PROCEDURE_SECTION

  f0(u1);
  f0(u2);
  f0(u3);
  f0(u4);
  f0(u5);
  for (int ii=1;ii<=nobs;ii++)
  {
    double y=obs(ii,1);
    dvector ind=obs(ii)(3,7).shift(1);
    f1(y,a(obs(ii,2)),u1(ind(1)),u2(ind(2)),u3(ind(3)),u4(ind(4)),u5(ind(5)),log_sigma1,log_sigma2,log_sigma3,log_sigma4,log_sigma5);
  }

  if (sd_phase())
  {
    sigma1=exp(log_sigma1);
    sigma2=exp(log_sigma2);
    sigma3=exp(log_sigma3);
    sigma4=exp(log_sigma4);
    sigma5=exp(log_sigma5);
  }

SEPARABLE_FUNCTION void f0(const dvar_vector& u)
  f+=0.5*norm2(u);
  
  
SEPARABLE_FUNCTION void f1(double y,const prevariable& a,const prevariable& u1,const prevariable& u2,const prevariable& u3,const prevariable& u4,const prevariable& u5,const prevariable ls1,const prevariable ls2,const prevariable ls3,const prevariable ls4,const prevariable ls5)
    dvariable logq=a+exp(ls1)*u1+exp(ls2)*u2+exp(ls3)*u3+exp(ls4)*u4+exp(ls5)*u5;
    dvariable q=exp(logq);
    // add minus thge log likelihood
    if(y==1)
      f+=log(1+q)-logq;
    else
      f+=log(1+q);


TOP_OF_MAIN_SECTION
  /*
  arrmblsize = 40000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(30000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(2000000);
  gradient_structure::set_MAX_NVAR_OFFSET(100000);
  */
