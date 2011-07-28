// testing for neg. log. likelihood functions defined in qfc_est.cpp file
GLOBALS_SECTION
  #include "qfc_sim.cpp"
  #include "qfc_est.cpp"
  


DATA_SECTION
  
INITIALIZATION_SECTION
 junk 2.2
 tmp 9.

PARAMETER_SECTION
 init_number junk
 random_effects_vector tmp(1,3,1)
 objective_function_value nll
 vector tmp2(1,3)


PRELIMINARY_CALCS_SECTION


PROCEDURE_SECTION
  random_number_generator rnd(12345);

  dvector tmp1(1,4);
  tmp1.fill_randu(rnd);
  tmp2=9;
  cout<<tmp1<<endl;
  cout<<tmp<<endl; //don't know why the random effect variable not being initialized here ???
  cout<<tmp2<<endl<<endl;

  dvector obs(1,4); obs.fill("{12, 3, 5,20}");

  cout<<nllNegativeBinomial(1.2,3,junk)<<endl;
  cout<<nllNegativeBinomial(tmp2(1),tmp2(2),3)<<endl;

  cout<<nllMultiNomial(tmp1,obs)<<endl;

  cout<<nllGamma(tmp2(1),tmp2(2),obs)<<endl;

  cout<<nllInverseGamma(2.2,2.2,tmp2)<<endl;
  cout<<nllInverseGamma(junk,junk,tmp2)<<endl;

  cout<<nllPoisson(junk,junk)<<endl;
  cout<<nllPoisson(tmp1(1),junk)<<endl;

  cout<<nllLognormal2(junk,junk,tmp2)<<endl;
  cout<<nllLognormal(junk,junk,tmp2)<<endl;

  cout<<nllBinomial(tmp2(1),tmp1(4),junk)<<endl;
  cout<<nllBinomial(tmp2,tmp1(3),tmp2)<<endl;

  exit(88);
 

