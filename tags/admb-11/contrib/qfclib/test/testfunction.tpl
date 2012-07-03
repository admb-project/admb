GLOBALS_SECTION
  #include "qfclib.h"


DATA_SECTION
  

PARAMETER_SECTION
 init_vector junk(1,3)
 
 //random_effects_vector tmp(1,3)
 objective_function_value nll

PRELIMINARY_CALCS_SECTION

  //following are testing for functions defined in qfc_sim.cpp file
  //================================================================
  random_number_generator rnd(12345);
  dvector p(1,4); p.fill("{0.3,0.4,0.2,0.1}"); //for dirichlet
  for(int i=1;i<=2;i++){
    cout<<endl<<"runif = "<<runif(0.5,10.5,rnd)<<endl; //random number
    cout<<"rgamma = "<<round(rgamma(2.5,2.5,rnd),3)<<endl; //using round()
    cout<<"rdirichlet = "<<round(rdirichlet(p,rnd),2)<<endl;
    cout<<"rnorm = "<<rnorm(3,1.2,rnd)<<endl;
  }

  cout<<endl<<"found all values for mu parameter from std file"<<endl;
  //cout<<findValFromFile("test1.std","mu",2)<<endl;//change filename if needed
  
 
  dvector v(1,10); 
  v.fill("{6,2,2,4,4,5,4,12,8,6}");  
  cout<<endl<<"original values with replicate"<<endl<<v<<endl;
  cout<<"unique value"<<endl<<unique(v)<<endl<<endl;
  //cout<<"unique vlaues "<<endl<<v(unique(v))<<endl<<endl;


  cout<<"convert vector to matrix by row"<<endl<<vector2matrix(v,2,5)<<endl;  
  dmatrix m=vector2matrix(v,2,5);
  cout<<"convert matrix to vector by row"<<endl<< matrix2vector(m)<<endl<<endl;

  ivector idx=sample(v,5,1,rnd); //random sample size 5 from v with replacement
  cout<<"random sample index "<<endl<<idx<<endl;
  cout<<"actual random sample value"<<endl<<v(idx)<<endl<<endl;

  

PROCEDURE_SECTION
  //following are testing for functions defined in qfc_est.cpp file
  //================================================================
  junk.fill("{1.2, 3, 5}");
  //constrain p as sum=1 and each [0,1]
  dvar_vector dp=logitProp(junk);
  cout<<"constrain the p"<<dp<<endl;
  cout<<"convert back"<<endl<<invLogitProp(dp)<<endl<<endl; //convert them back

  dvariable fpen=0;
  dvar_vector dv(1,3); dv=junk;
  for(int i=1;i<=3;i++) 
    dv(i)=mf_upper_bound2(junk(i),2.,fpen);
  cout<<"old value "<<junk<<endl<<"new value "<<dv<<endl<<"penalty = "<<fpen<<endl;

  dvector obs(1,4); obs.fill("{12, 3, 5,20}");
  cout<<nllNegativeBinomial(junk(2),1.2,3)<<" "<<nllNegativeBinomial(3,junk(1),junk(2))<<endl;
  cout<<nllMultiNomial(obs,dp)<<endl;
  cout<<nllPoisson(obs(1),dp(1))<<endl;
  cout<<nllLognormal(obs,junk(1),junk(2))<<endl;
  cout<<nllGamma(obs,junk(1),junk(2))<<endl;

  exit(8);
