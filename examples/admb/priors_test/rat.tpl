// Author: Weihai Liu
// Copyright (c) 2009-2018 ADMB Foundation

GLOBALS_SECTION 
  #include "priors.cpp"
  // append to mcmc output file
  long mcmc_iter = 0; 
  adstring mcFileName="testmc.dat"; //put your mcmc saving file name




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
  //!! cout<<x<<endl<<endl<<y<<endl; exit(8);


PARAMETER_SECTION 
  //init_number tauc(3) //bounds is 0.00001,100
  init_bounded_number tauc(0.00001,100,3) //bounds is 0.00001,100

  init_number alphac    //mean for alpha

  //init_number alphatau(2) //bounds is 0.00001,100
  init_bounded_number alphatau(0.00001,100,2) //bounds is 0.00001,100

  init_number betac 

  //init_number betatau(2) //bounds is 0.00001,100
  init_bounded_number betatau(0.00001,100,2) //bounds is 0.00001,100

  init_vector alpha(1,N) //used to be random effect
  init_vector beta(1,N) //used to be random effect

  matrix mu(1,N,1,T) 
  sdreport_number alpha0   //user interest
  number like
  objective_function_value f 


INITIALIZATION_SECTION
  tauc  1 
  alphac  150
  alphatau  1
  betac  10
  betatau 1
  alpha  250
  beta  6


PRIORS_SECTION
  tauc     ~ nllGamma ( 0.001 , 0.001); 
  alphac   ~ nllNormal2 ( 0.0 ,  1.0e-6);  
  alphatau ~ nllGamma (0.001 , 0.001); 
  betac    ~ nllNormal2( 0.0,   1.0e-6); 
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
   //cout<<"1f ="<<prior_function_value<<"  "<< likelihood_function_value<<"  "<<f<<endl;


PROCEDURE_SECTION 
  like=0;

  //add nll for parm.
  //like=-N*0.5*log(alphatau)+0.5*alphatau*norm2(alpha-alphac); 
  //like+=-N*0.5*log(betatau)+0.5*betatau*norm2(beta-betac);
  
  for(int i=1;i<=N;i++) 
  { 
    //alpha(i) ~ dnorm(alphac,alphatau);
    //beta(i) ~ dnorm(betac,betatau);
    for(int j=1;j<=T;j++) 
    { 
       mu(i,j)=alpha(i) + beta(i) * (x(j) - xbar); 
       //like += -log_normal_density( y(i,j), mu(i,j), tauc);  //nll for obs.
       //y(i,j) ~ dnorm(mu(i,j), tauc);
    } 
  } 

  alpha0=alphac-xbar*betac;
  //f+=like;

  //add prior nll, will automatically added to obj. by priors_section
  /*
  f+=-log_gamma_density(tauc,0.001,0.001); 
  f+=0.5*1.0E-6*square(alphac-0.0); 
  f+=-log_gamma_density(alphatau,0.001,0.001); 
  f+=0.5*1.0E-6*square(betac-0.0); 
  f+=-log_gamma_density(betatau,0.001,0.001);
  */
  if (mceval_phase()) SaveMcmc(mcFileName);





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

