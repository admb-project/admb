DATA_SECTION
  init_int nplates;
  init_vector r(1,nplates);
  init_vector n(1,nplates);
  init_vector x1(1,nplates);
  init_vector x2(1,nplates);

PARAMETER_SECTION
  init_number logalpha
  init_vector beta(1,4);
  random_effects_vector b(1,nplates);
  vector eta(1,nplates);
  vector p(1,nplates);
  sdreport_vector u(1,nplates);
  vector v(1,nplates);
  objective_function_value nll;

PROCEDURE_SECTION
  for (int i=1; i<=nplates; ++i){
    seeds_betabin(i,b(i),logalpha,beta);
  }

  // assign fitted u
  if (sd_phase){
    dvariable alpha=mfexp(logalpha);
    for (int i=1; i<=nplates; ++i){
      u(i)=beta_deviate(alpha,alpha,b(i),0.0000001);
    }
  }

SEPARABLE_FUNCTION void seeds_betabin(int& i, const dvariable& bi, const dvariable& logalpha, const dvar_vector& beta)
  dvariable alpha=mfexp(logalpha);
  // RANDOM EFFECTS PART
  nll+=0.5*(log(2.0*M_PI)+square(bi));

  // beta via PIT
  dvariable ui= beta_deviate(alpha,alpha,bi,0.0000001);

  // on linear predictor scale
  dvariable vi= log(ui/(1-ui));

  // LINEAR PREDICTOR
  dvariable etai=beta(1)+beta(2)*x1(i)+beta(3)*x2(i)+beta(4)*x1(i)*x2(i)+vi;
  //
  dvariable pi=1.0/(1.0+mfexp(-etai));
  // DATA
  nll-=log_comb(n(i),r(i))+r(i)*log(pi)+(n(i)-r(i))*log(1.0-pi);

GLOBALS_SECTION
  // Note need to have code Dave sent here
  /*
  #include <df12fun.cpp>
  #include <betai.cpp>
  #include <dfbetai.cpp>
  #include <df1b2invcumdbeta.cpp>
  */
