// Author: Wiehai Liu
// Copyright (c) 2009-2018 ADMB Foundation

GLOBALS_SECTION
  #include "priors.cpp" 
  // append to mcmc output file
  long mcmc_iter = 0; 
  adstring mcFileName="admb1.mc.dat"; //put your mcmc saving file name
  
  //*** if your admb not build from the latest trunk, you need uncomment out following functions ***
  //df1b2variable operator -(double x, const df1b2variable& y) {return x+(-1.0*y);}
  //df1b2variable operator -(const df1b2variable& x,double y) {return (-1.0*y)+x;}


TOP_OF_MAIN_SECTION
  arrmblsize = 90000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(3000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(2000000);
  gradient_structure::set_MAX_NVAR_OFFSET(8000);


DATA_SECTION 
  !!ad_comm::change_datafile_name("rat.dat");
  init_int N 
  init_int T 
  init_number xbar 
  init_vector x(1,T) 
  init_matrix y(1,N,1,T)
  //!! cout<<" ** x"<<endl<<x<<endl<<endl<<" ** y"<<endl<<y<<endl;// exit(8);

INITIALIZATION_SECTION
  tauc  1 
  alphac  150
  alphatau  1
  betac  10
  betatau 1

PARAMETER_SECTION 
  init_bounded_number tauc(0.00001,100,3) 
  init_number alphac    
  init_bounded_number alphatau(0.00001,100,2) 
  init_number betac 
  init_bounded_number betatau(0.00001,100,2) 
  random_effects_vector alpha(1,N) 
  random_effects_vector beta(1,N) 
  matrix mu(1,N,1,T) 
  sdreport_number alpha0   //user interest
  objective_function_value f 

PRIORS_SECTION
  tauc     ~ nllGamma ( 0.001 , 0.001); 
  alphac   ~ nllNormal2 ( 0.0 ,  0.000001);  
  alphatau ~ nllGamma (0.001 , 0.001); 
  betac    ~ nllNormal2( 0.0,   0.000001); 
  betatau  ~ nllGamma(0.001, 0.001); 
  //cout<<"1f ="<<prior_function_value<<"  "<< likelihood_function_value<<"  "<<f<<endl;

LIKELIHOOD_SECTION
  for(int i=1;i<=N;i++){ 
    alpha(i) ~ nllNormal2(alphac,alphatau);
    beta(i) ~ nllNormal2(betac,betatau);
    for(int j=1;j<=T;j++) 
    { 
      y(i,j) ~ nllNormal2(mu(i,j), tauc);
    }
  }
  //cout<<"2f ="<<prior_function_value<<"  "<< likelihood_function_value<<"  "<<f<<endl;
  //exit(8);

PRELIMINARY_CALCS_SECTION
  //cout<<T<<endl;

PROCEDURE_SECTION 
  //cout<<"alphac, betac = "<<alphac<<" "<<betac<<endl; //exit(8);
  for(int i=1;i<=N;i++) 
  { 
    for(int j=1;j<=T;j++) 
    { 
       mu(i,j)=alpha(i) + beta(i) * (x(j) - xbar); 
       //f+=-0.5*log(tauc)+0.5*tauc*square((y(i,j)-mu(i,j))); 
    } 
  } 
  //cout<<"mu"<<endl<<mu<<endl<<endl;
  alpha0=alphac-xbar*betac;
  //add re
  //f+=-N*0.5*log(alphatau)+0.5*alphatau*norm2(alpha-alphac); 
  //f+=-N*0.5*log(betatau)+0.5*betatau*norm2(beta-betac);

  //add prior nll
  /*
  f+=-log_gamma_density(tauc,0.001,0.001); 
  f+=0.5*1.0E-6*square(alphac-0.0); 
  f+=-log_gamma_density(alphatau,0.001,0.001); 
  f+=0.5*1.0E-6*square(betac-0.0); 
  f+=-log_gamma_density(betatau,0.001,0.001);
  */
  if (mceval_phase()) SaveMcmc(mcFileName);

  //cout<<"f ="<<prior_function_value<<"  "<< likelihood_function_value<<"  "<<f<<endl;
  

//=============================================================
//save mcmc data file, filename is defined on the top of this program
//had been formated as can be read into R by using our admb2List R function
//how to run mcmc in admb, two steps: 
//mixBayes -mcmc 1000 -mcsave 20
//mixBayes -mceval
//when you run -mceval, no need to provide the runtime output filename
FUNCTION int SaveMcmc(adstring mcFileName)
  mcmc_iter++;
  if(mcmc_iter == 1){ //add the top lines for variable names read into R
    ofstream mcmc_report(mcFileName);//create file
    mcmc_report<<"# mcnames"<<endl; //being recoginzed if using our admbPlot.r program to plot mcmc
    //make up strings for variable names    
    mcmc_report<<"tauc\t alphac\t alphatau\t betac\t betatau\t alpha0"<<endl;//provide variable names here
    mcmc_report<<"# mcdata"<<endl;
  }

  ofstream mcmc_report(mcFileName,ios::app);//append data
  mcmc_report<<tauc<<" "<<alphac<<" "<<alphatau<<" "<< betac<<" "<<betatau<<" "<<alpha0<<endl;//corresponding to above variable names
  mcmc_report.close();
  return 0;
 
REPORT_SECTION
  report<<"Parameters est.  "<<endl;
  report<<tauc <<" "<< alphac<<" "<<alphatau<<" "<< betac<<" "<<betatau<<endl;
  report<<"alpha"<<endl<<alpha<<endl;
  report<<"beta"<<endl<<beta<<endl;
  report<<"prior_function_value: "<<prior_function_value<<endl;
  report<<"likelihood objective value: "<<likelihood_function_value<<endl;
  report<<"total objective value: "<<f<<endl;

RUNTIME_SECTION
  convergence_criteria 1.0e-6,1.0e-8,1.0e-10
  maximum_function_evaluations 100,500,1000
