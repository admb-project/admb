GLOBALS_SECTION
  #include "qfclib.h"
 
  


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
  cout<<ad_comm::adprogram_name<<endl;
  cout<<M_PI<<endl;

  dvector tmp1(1,4);
  tmp1.fill_randu(rnd);
  tmp2=3;
  cout<<tmp1<<endl<<tmp<<endl<<tmp2<<endl<<endl;

  dvector obs(1,4); obs.fill("{12, 33, 15,20}");

  cout<<nllNegativeBinomial(junk,1.2,3)<<endl;
  cout<<nllNegativeBinomial(3,tmp2(1),tmp2(2))<<endl;

  cout<<nllMultiNomial(obs,tmp1)<<endl;

  cout<<nllGamma(obs,tmp2(1),tmp2(2))<<endl;

  cout<<nllInverseGamma(tmp2,2.2,2.2)<<endl;
  cout<<nllInverseGamma(tmp2,junk,junk)<<endl;

  cout<<nllPoisson(junk,junk)<<endl;
  cout<<nllPoisson(junk,tmp1(1))<<endl;

  cout<<nllLognormal2(tmp2,junk,tmp1(3))<<endl;
  cout<<nllLognormal(tmp2,junk,junk)<<endl;

  cout<<nllBinomial(junk,obs(1),tmp1(4))<<endl;
  cout<<nllBinomial(tmp2,obs(1,3),tmp1(1))<<endl;

  exit(88);
 

