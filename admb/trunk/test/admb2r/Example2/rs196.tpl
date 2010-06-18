//##--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
//##
//##  SEDAR15 Assessment: Red Snapper, October 2007
//##  NMFS Beaufort Lab
//##  Modified for use as example for ADMB2R and FishGraph
//##
//##--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>

DATA_SECTION
//Create ascii file for output
//!!CLASS ofstream report1("rsresults.rep",ios::out);  //create file for output

!!cout << "Starting Red Snapper Assessment Model" << endl;

// Starting and ending year of the model (year data starts)
init_int styr;
init_int endyr;

//Starting year to estimate recruitment deviation from S-R curve
init_int styr_rec_dev;

//3 periods: until '91 no size regs, 1992-98 12inch TL, 1999-04 14inch TL
init_int endyr_period1;
init_int endyr_period2;


//Total number of ages
init_int nages;

// Vector of ages for age bins
init_ivector agebins(1,nages);

//number assessment years
number nyrs;
number nyrs_rec;
//this section MUST BE INDENTED!!!
 LOCAL_CALCS
   nyrs=endyr-styr+1.;
   nyrs_rec=endyr-styr_rec_dev+1.;
 END_CALCS

//Total number of length bins for each matrix
init_int nlenbins;

// Vector of lengths for length bins (mm)(midpoint)
init_ivector lenbins(1,nlenbins);

//discard mortality constants
init_number set_Dmort_commHAL;
init_number set_Dmort_HB;
init_number set_Dmort_MRFSS;

//Total number of iterations for spr calcs
init_int n_iter_spr;
//Total number of iterations for msy calcs
init_int n_iter_msy;
//starting index of ages for exploitation rate: if model has age-0s, ages of E are (value-1) to oldest
init_int set_E_age_st;
//bias correction (set to 1.0 for no bias correction or 0.0 to compute from rec variance)
init_number set_BiasCor;
// Von Bert parameters
init_number set_Linf;
init_number set_K;
init_number set_t0;
//CV of length at age
init_number set_len_cv;

//length(mm)-weight(whole weigt in g) relationship: W=aL^b
init_number wgtpar_a;
init_number wgtpar_b;
//weight-weight relationship:whole weight to gutted weight -- gutted=a*whole
init_number wgtpar_whole2gutted

//Female maturity and proportion female at age
init_vector maturity_f_obs(1,nages);            //total maturity of females
init_vector prop_f_obs(1,nages);                //proportion female at age

//#############################################################################
//###################Commercial Hook and Line fishery #########################
//CPUE
init_int styr_HAL_cpue;
init_int endyr_HAL_cpue;
init_vector obs_HAL_cpue(styr_HAL_cpue,endyr_HAL_cpue);//Observed CPUE
init_vector HAL_cpue_cv(styr_HAL_cpue,endyr_HAL_cpue); //CV of cpue

// Landings - after WW II (1000 lb whole weight)
init_int styr_commHAL_L_2;
init_int endyr_commHAL_L_2;
init_vector obs_commHAL_L_2(styr_commHAL_L_2,endyr_commHAL_L_2); //vector of observed landings by year
init_vector commHAL_L_cv_2(styr_commHAL_L_2,endyr_commHAL_L_2);    //vector of CV of landings by year

// Discards (1000s)
init_int styr_commHAL_D;
init_int endyr_commHAL_D;
init_vector obs_commHAL_released(styr_commHAL_D,endyr_commHAL_D); //vector of observed releases by year, multiplied by discard mortality for fitting
init_vector commHAL_D_cv(styr_commHAL_D,endyr_commHAL_D);    //vector of CV of discards by year

// Length Compositions (30mm bins)
init_int styr_commHAL_lenc;
init_int endyr_commHAL_lenc;
init_vector nsamp_commHAL_lenc(styr_commHAL_lenc,endyr_commHAL_lenc);
init_matrix obs_commHAL_lenc(styr_commHAL_lenc,endyr_commHAL_lenc,1,nlenbins);
// Age Compositions
init_int nyr_commHAL_agec;
init_ivector yrs_commHAL_agec(1,nyr_commHAL_agec);
init_vector nsamp_commHAL_agec(1,nyr_commHAL_agec);
init_matrix obs_commHAL_agec(1,nyr_commHAL_agec,1,nages);

//#############################################################################
//##############################Commercial Diving fishery ########################
// Landings (1000 lb whole weight)
init_int styr_commDV_L;
init_int endyr_commDV_L;
init_vector obs_commDV_L(styr_commDV_L,endyr_commDV_L);
init_vector commDV_L_cv(styr_commDV_L,endyr_commDV_L);    //vector of CV of landings by year
// Length Compositions (30mm bins)
init_int nyr_commDV_lenc;
init_ivector yrs_commDV_lenc(1,nyr_commDV_lenc);
init_vector nsamp_commDV_lenc(1,nyr_commDV_lenc);
init_matrix obs_commDV_lenc(1,nyr_commDV_lenc,1,nlenbins);
// Age Compositions
init_int nyr_commDV_agec;
init_ivector yrs_commDV_agec(1,nyr_commDV_agec);
init_vector nsamp_commDV_agec(1,nyr_commDV_agec);
init_matrix obs_commDV_agec(1,nyr_commDV_agec,1,nages);

//#############################################################################
//################################Headboat fishery ########################################
//CPUE
init_int styr_HB_cpue;
init_int endyr_HB_cpue;
init_vector obs_HB_cpue(styr_HB_cpue,endyr_HB_cpue);//Observed CPUE
init_vector HB_cpue_cv(styr_HB_cpue,endyr_HB_cpue); //CV of cpue
// Landings (1000 lb whole weight)
init_int styr_HB_L;
init_int endyr_HB_L;
init_vector obs_HB_L(styr_HB_L,endyr_HB_L);
init_vector HB_L_cv(styr_HB_L,endyr_HB_L);
// Discards (1000s)
init_int styr_HB_D;
init_int endyr_HB_D;
init_vector obs_HB_released(styr_HB_D,endyr_HB_D); //vector of observed releases by year, multiplied by discard mortality for fitting
init_vector HB_D_cv(styr_HB_D,endyr_HB_D);    //vector of CV of discards by year
// Length Compositions (10mm bins)
init_int styr_HB_lenc;
init_int endyr_HB_lenc;
init_vector nsamp_HB_lenc(styr_HB_lenc,endyr_HB_lenc);
init_matrix obs_HB_lenc(styr_HB_lenc,endyr_HB_lenc,1,nlenbins);
// Age compositions
init_int nyr_HB_agec;
init_ivector yrs_HB_agec(1,nyr_HB_agec);
init_vector nsamp_HB_agec(1,nyr_HB_agec);
init_matrix obs_HB_agec(1,nyr_HB_agec,1,nages);

//#############################################################################
//############################MRFSS landings #################################
//CPUE
init_int styr_MRFSS_cpue;
init_int endyr_MRFSS_cpue;
init_vector obs_MRFSS_cpue(styr_MRFSS_cpue,endyr_MRFSS_cpue);//Observed CPUE
init_vector MRFSS_cpue_cv(styr_MRFSS_cpue,endyr_MRFSS_cpue); //CV of cpue
// Landings (1000 lb whole weight)
init_int styr_MRFSS_L;
init_int endyr_MRFSS_L;
init_vector obs_MRFSS_L(styr_MRFSS_L,endyr_MRFSS_L);
init_vector MRFSS_L_cv(styr_MRFSS_L,endyr_MRFSS_L);
// Discards (1000s)
init_int styr_MRFSS_D;
init_int endyr_MRFSS_D;
init_vector obs_MRFSS_released(styr_MRFSS_D,endyr_MRFSS_D); //vector of observed releases by year, multiplied by discard mortality for fitting
init_vector MRFSS_D_cv(styr_MRFSS_D,endyr_MRFSS_D);    //vector of CV of discards by year
// Length Compositions (30mm bins)
init_int nyr_MRFSS_lenc;
init_ivector yrs_MRFSS_lenc(1,nyr_MRFSS_lenc);
init_vector nsamp_MRFSS_lenc(1,nyr_MRFSS_lenc);
init_matrix obs_MRFSS_lenc(1,nyr_MRFSS_lenc,1,nlenbins);
// Age Compositions
init_int styr_MRFSS_agec;
init_int endyr_MRFSS_agec;
init_vector nsamp_MRFSS_agec(styr_MRFSS_agec,endyr_MRFSS_agec);
init_matrix obs_MRFSS_agec(styr_MRFSS_agec,endyr_MRFSS_agec,1,nages);

//#############################################################################
//##################Parameter values and initial guesses #################################
//--weights for likelihood components-------------------------------------------------------------------------------
init_number set_w_L;
init_number set_w_D;
init_number set_w_lc;
init_number set_w_ac;
init_number set_w_I_HAL;
init_number set_w_I_HB;
init_number set_w_I_MRFSS;
init_number set_w_R;
init_number set_w_R_init;
init_number set_w_R_end;
init_number set_w_F;
init_number set_w_B1dB0;         // weight on B1/B0
init_number set_w_fullF;         //penalty for any fullF>5
init_number set_w_cvlen_dev;         //penalty on cv deviations at age
init_number set_w_cvlen_diff;       //penalty on first difference of cv deviations at age

//Initial guess for commercial landings bias parameter
init_number set_L_early_bias;
//Initial guess for rate of increase on q
init_number set_q_rate;
//Initial guesses or fixed values
init_number set_steep;
//init_number set_M;
init_vector set_M(1,nages); //age-dependent: used in model
init_number set_M_constant; //age-independent: used only for MSST

//--index catchability------------------------------------------------------------------------------------------------------------
init_number set_logq_HAL;     //catchability coefficient (log) for commercial logbook CPUE index
init_number set_logq_HB;      //catchability coefficient (log) for the headboat index
init_number set_logq_MRFSS;   //catchability coefficient (log) for MRFSS CPUE index

//--F's--------------------------------
init_number set_log_avg_F_commHAL_2;
init_number set_log_avg_F_commDV;
init_number set_log_avg_F_HB;
init_number set_log_avg_F_MRFSS;

//--discard F's-----------------------
init_number set_log_avg_F_commHAL_D;
init_number set_log_avg_F_HB_D;
init_number set_log_avg_F_MRFSS_D;

//Set some more initial guesses of estimated parameters
init_number set_log_R0;
init_number set_R1_mult;
init_number set_B1dB0;
init_number set_R_autocorr;

//Initial guesses of estimated selectivity parameters
init_number set_selpar_L50_commHAL1;
init_number set_selpar_slope_commHAL1;
init_number set_selpar_L502_commHAL1;
init_number set_selpar_slope2_commHAL1;
init_number set_selpar_L50_commHAL2;
init_number set_selpar_slope_commHAL2;
init_number set_selpar_L502_commHAL2;
init_number set_selpar_slope2_commHAL2;
init_number set_selpar_L50_commHAL3;
init_number set_selpar_slope_commHAL3;
init_number set_selpar_L502_commHAL3;
init_number set_selpar_slope2_commHAL3;

init_number set_selpar_L50_commDV1;
init_number set_selpar_L502_commDV1;
init_number set_selpar_slope_commDV1;
init_number set_selpar_slope2_commDV1;
//init_number set_selpar_L50_commDV2;
//init_number set_selpar_L502_commDV2;
//init_number set_selpar_slope_commDV2;
//init_number set_selpar_slope2_commDV2;

init_number set_selpar_L50_HB1;
init_number set_selpar_slope_HB1;
init_number set_selpar_L502_HB1;
init_number set_selpar_slope2_HB1;
init_number set_selpar_L50_HB2;
init_number set_selpar_slope_HB2;
init_number set_selpar_L502_HB2;
init_number set_selpar_slope2_HB2;
init_number set_selpar_L50_HB3;
init_number set_selpar_slope_HB3;
init_number set_selpar_L502_HB3;
init_number set_selpar_slope2_HB3;

init_number set_selpar_L50_MRFSS1;
init_number set_selpar_slope_MRFSS1;
init_number set_selpar_L502_MRFSS1;
init_number set_selpar_slope2_MRFSS1;
init_number set_selpar_L50_MRFSS2;
init_number set_selpar_slope_MRFSS2;
init_number set_selpar_L502_MRFSS2;
init_number set_selpar_slope2_MRFSS2;
init_number set_selpar_L50_MRFSS3;
init_number set_selpar_slope_MRFSS3;
init_number set_selpar_L502_MRFSS3;
init_number set_selpar_slope2_MRFSS3;

init_number set_selpar_commHAL_D_age1;
init_number set_selpar_HB_D_age1;
init_number set_selpar_MRFSS_D_age1;

// #######Indices for year(iyear), age(iage),length(ilen) ###############
int iyear;
int iage;
int ilen;
int E_age_st;   //starting age for exploitation rate: (value-1) to oldest

init_number end_of_data_file;
//this section MUST BE INDENTED!!!
 LOCAL_CALCS
   if(end_of_data_file!=999)
   {
     for(iyear=1; iyear<=100; iyear++)
     {
       cout << "*** WARNING: Data File NOT READ CORRECTLY ****" << endl;
       cout << "" <<endl;
     }
   }
   else
   {
    cout << "Data File read correctly" << endl;
   }
 END_CALCS


//##--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
//##--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
PARAMETER_SECTION
//--------------Growth---------------------------------------------------------------------------

  //init_bounded_number Linf(600,1400,2);
  //init_bounded_number K(0.05,0.6,2);
  //init_bounded_number t0(-2.0,0.0,2);
  number Linf;
  number K;
  number t0;
  vector wgt_g(1,nages);        //whole wgt in g
  vector wgt_kg(1,nages);       //whole wgt in kg
  vector wgt(1,nages);          //whole wgt in mt
  vector wgt_klb(1,nages);      //whole wgt in 1000 lb
  vector meanlen(1,nages);        //mean length at age
  number sqrt2pi;
  number g2mt;                    //conversion of grams to metric tons
  number g2kg;                      //conversion of grams to kg
  number mt2klb;                  //conversion of metric tons to 1000 lb

  matrix lenprob(1,nages,1,nlenbins);           //distn of size at age (age-length key, 30 mm bins)
  init_bounded_number log_len_cv(-5,-0.3,3);
  //init_bounded_number log_len_cv(-4.6,-0.7,2) //cv expressed in log-space, bounds correspond to 0.01, 0.5
  //init_bounded_dev_vector log_len_cv_dev(1,nages,-2,2,3)
  vector len_cv(1,nages);

//----Predicted length and age compositions
  matrix pred_commHAL_lenc(styr_commHAL_lenc,endyr_commHAL_lenc,1,nlenbins);
  matrix pred_commDV_lenc(1,nyr_commDV_lenc,1,nlenbins);
  matrix pred_HB_lenc(styr_HB_lenc,endyr_HB_lenc,1,nlenbins);
  matrix pred_MRFSS_lenc(1,nyr_MRFSS_lenc,1,nlenbins);

  matrix pred_commHAL_agec(1,nyr_commHAL_agec,1,nages);
  matrix pred_commDV_agec(1,nyr_commDV_agec,1,nages);
  matrix pred_HB_agec(1,nyr_HB_agec,1,nages);
  matrix pred_MRFSS_agec(styr_MRFSS_agec,endyr_MRFSS_agec,1,nages);

  //nsamp_X_allyr vectors used only for R output of comps with nonconsecutive yrs
  vector nsamp_commDV_lenc_allyr(styr,endyr);
  vector nsamp_MRFSS_lenc_allyr(styr,endyr);
  vector nsamp_commHAL_agec_allyr(styr,endyr);
  vector nsamp_commDV_agec_allyr(styr,endyr);
  vector nsamp_HB_agec_allyr(styr,endyr);

//-----Population-----------------------------------------------------------------------------------
  matrix N(styr,endyr+1,1,nages);           //Population numbers by year and age at start of yr
  matrix N_mdyr(styr,endyr,1,nages);        //Population numbers by year and age at mdpt of yr: used for comps and SSB
  matrix B(styr,endyr+1,1,nages);           //Population biomass by year and age
  vector totB(styr,endyr+1);                //Total biomass by year
  //init_bounded_number log_R1(5,20,1);       //log(Recruits) in styr
  sdreport_vector SSB(styr,endyr);       //Spawning biomass by year
  sdreport_vector rec(styr,endyr+1);       //Recruits by year
  vector prop_f(1,nages);                   //Proportion female by age
  vector maturity_f(1,nages);               //Proportion of female mature at age
  vector reprod(1,nages);

//---Stock-Recruit Function (Beverton-Holt, steepness parameterization)----------
  init_bounded_number log_R0(5,20,1);       //log(virgin Recruitment)
  sdreport_number R0;
  init_bounded_number steep(0.25,0.95,3);     //steepness
  //number steep;  //uncomment to fix steepness, comment line directly above
  init_bounded_dev_vector log_dev_N_rec(styr_rec_dev,endyr,-3,3,2); //log recruitment deviations
  vector log_dev_R(styr,endyr+1);           //used in output. equals zero except for yrs in log_dev_N_rec
  number var_rec_dev;                       //variance of log recruitment deviations.
                                              //Estimate from yrs with unconstrainted S-R(XXXX-XXXX)
  number BiasCor;                           //Bias correction in equilibrium recruits
  init_bounded_number R_autocorr(0,1.0,3);  //autocorrelation in SR
  //number R_autocorr
  sdreport_number R_autocorr_sd;
  sdreport_number steep_sd;                 //steepness for stdev report
  number S0;                                //equal to spr_F0*R0 = virgin SSB
  number B0;                                //equal to bpr_F0*R0 = virgin B
  number B1dB0;                             //B1dB0 computed and used in constraint
  //init_bounded_number R1_mult(0.05,1.0,1);   //R(styr)=R1_mult*R0
  number R1_mult;                           //equals B1dB0 under assumption of virgin age structure
  number R1;                                //Recruits in styr

  sdreport_number S1S0;                     //SSB(styr) / virgin SSB
  sdreport_number popstatus;                //SSB(endyr) / virgin SSB

//---Selectivity-------------------------------------------------------------------------

  //Commercial hook and line
  matrix sel_commHAL(styr,endyr,1,nages);
  //init_bounded_number selpar_slope_commHAL1(0.5,12.0,1); //period 1
  //init_bounded_number selpar_L50_commHAL1(0.1,10.,1);
  //init_bounded_number selpar_slope2_commHAL1(0.0,12.0,3); //period 1
  //init_bounded_number selpar_L502_commHAL1(1.0,15.0,3);
  number selpar_slope_commHAL1; //period 1 is assumed same as HB and MRFSS
  number selpar_L50_commHAL1;
  number selpar_slope2_commHAL1; //period 1
  number selpar_L502_commHAL1;
  init_bounded_number selpar_slope_commHAL2(0.5,12.0,1); //period 2
  init_bounded_number selpar_L50_commHAL2(0.1,10.,1);
  //init_bounded_number selpar_slope2_commHAL2(0.0,12.0,3); //period 2
  //init_bounded_number selpar_L502_commHAL2(1.0,15.0,3);
  number selpar_slope2_commHAL2; //period 2
  number selpar_L502_commHAL2;
  init_bounded_number selpar_slope_commHAL3(0.5,12.0,1); //period 3
  init_bounded_number selpar_L50_commHAL3(0.1,10.,1);
  //init_bounded_number selpar_slope2_commHAL3(0.0,12.0,3); //period 3
  //init_bounded_number selpar_L502_commHAL3(1.0,15.0,3);
  number selpar_slope2_commHAL3; //period 3
  number selpar_L502_commHAL3;
  //init_bounded_dev_vector selpar_L50_commHAL_dev(styr_commHAL_lenc,endyr_period1,-5,5,3);
  vector sel_commHAL_1(1,nages); //sel in period 1
  vector sel_commHAL_2(1,nages); //sel in period 2
  vector sel_commHAL_3(1,nages); //sel in period 3


  //Commercial diving
  matrix sel_commDV(styr,endyr,1,nages);            //time invariant
  init_bounded_number selpar_slope_commDV1(0.5,12.0,1);
  init_bounded_number selpar_L50_commDV1(0.1,10.,1);
  init_bounded_number selpar_slope2_commDV1(0.1,12.0,3);
  init_bounded_number selpar_L502_commDV1(1.0,20.0,3);
  vector sel_commDV_vec(1,nages); //sel vector

  //Headboat: logistic, parameters allowed to vary with period defined by size restrictions
  matrix sel_HB(styr,endyr,1,nages);
  init_bounded_number selpar_slope_HB1(0.5,12.0,1); //period 1
  init_bounded_number selpar_L50_HB1(0.1,10.0,1);
  //init_bounded_number selpar_slope2_HB1(0.1,12.0,3); //period 1
  //init_bounded_number selpar_L502_HB1(1.0,20.0,3);
  number selpar_slope2_HB1;
  number selpar_L502_HB1;
  number selpar_slope_HB2;//period 2
  //init_bounded_number selpar_slope_HB2(0.5,12.0,1);
  init_bounded_number selpar_L50_HB2(0.1,10.,1);
  //init_bounded_number selpar_slope2_HB2(0.1,12.0,3); //period 2
  //init_bounded_number selpar_L502_HB2(1.0,20.0,3);
  number selpar_slope2_HB2;
  number selpar_L502_HB2;
  init_bounded_number selpar_slope_HB3(0.5,12.0,1); //period 3
  init_bounded_number selpar_L50_HB3(0.1,10.,1);
  //init_bounded_number selpar_slope2_HB3(0.1,12.0,3); //period 3
  //init_bounded_number selpar_L502_HB3(1.0,20.0,3);
  number selpar_slope2_HB3;
  number selpar_L502_HB3;
  //init_bounded_dev_vector selpar_L50_HB_dev(styr_HB_lenc,endyr_period1,-5,5,3);
  vector sel_HB_1(1,nages); //sel in period 1
  vector sel_HB_2(1,nages); //sel in period 2
  vector sel_HB_3(1,nages); //sel in period 3


  //MRFSS:
  matrix sel_MRFSS(styr,endyr,1,nages);
  //init_bounded_number selpar_slope_MRFSS1(0.5,9.0,1); //period 1
  //init_bounded_number selpar_L50_MRFSS1(0.1,10.0,1);
  //init_bounded_number selpar_slope2_MRFSS1(0.0,12.0,3); //period 1
  //init_bounded_number selpar_L502_MRFSS1(1.0,15.0,3);
  number selpar_slope_MRFSS1; //period 1 selectivity for MRFSS is same as HB
  number selpar_L50_MRFSS1;
  number selpar_slope2_MRFSS1;
  number selpar_L502_MRFSS1;
  number selpar_slope_MRFSS2; //period 2
  //init_bounded_number selpar_slope_MRFSS2(0.5,12.0,1); //period 2
  init_bounded_number selpar_L50_MRFSS2(0.1,10.,1);
  //init_bounded_number selpar_slope2_MRFSS2(0.1,12.0,3); //period 2
  //init_bounded_number selpar_L502_MRFSS2(1.0,20.0,3);
  number selpar_slope2_MRFSS2;
  number selpar_L502_MRFSS2;
  init_bounded_number selpar_slope_MRFSS3(0.5,12.0,1); //period 3
  init_bounded_number selpar_L50_MRFSS3(0.1,10.,1);
  //init_bounded_number selpar_slope2_MRFSS3(0.1,12.0,3); //period 3
  //init_bounded_number selpar_L502_MRFSS3(1.0,20.0,3);
  number selpar_slope2_MRFSS3;
  number selpar_L502_MRFSS3;
  //init_bounded_dev_vector selpar_L50_MRFSS_dev(1981,endyr_period1,-5,5,3);
  vector sel_MRFSS_2(1,nages); //sel in period 2; period 1 same as HB
  vector sel_MRFSS_3(1,nages); //sel in period 3


  //effort-weighted, recent selectivities
  vector sel_wgted_L(1,nages);  //toward landings
  vector sel_wgted_D(1,nages);  //toward discards
  vector sel_wgted_tot(1,nages);//toward Z, landings plus deads discards
  number max_sel_wgted_tot;

//-------CPUE Predictions--------------------------------
  vector pred_HAL_cpue(styr_HAL_cpue,endyr_HAL_cpue);          //predicted HAL U (pounds/hook-hour)
  matrix N_HAL(styr_HAL_cpue,endyr_HAL_cpue,1,nages);          //used to compute HAL index
  vector pred_HB_cpue(styr_HB_cpue,endyr_HB_cpue);             //predicted HB U (number/angler-day)
  matrix N_HB(styr_HB_cpue,endyr_HB_cpue,1,nages);             //used to compute HB index
  vector pred_MRFSS_cpue(styr_MRFSS_cpue,endyr_MRFSS_cpue);    //predicted MRFSS U (number/1000 hook-hours)
  matrix N_MRFSS(styr_MRFSS_cpue,endyr_MRFSS_cpue,1,nages);    //used to compute MRFSS index

//---Catchability (CPUE q's)----------------------------------------------------------
  init_bounded_number log_q_HAL(-20,-5,1);
  init_bounded_number log_q_HB(-20,-5,1);
  init_bounded_number log_q_MRFSS(-20,-5,1);
  //init_bounded_number q_rate(-0.1,0.1,-3);
  number q_rate;

//---Landings Bias------------------------------------------------------------------
  //init_bounded_number L_early_bias(0.1,10.0,3);
  number L_early_bias;
  number L_commHAL_bias;
//---C is landings in (numbers), L is landings in wgt (mt)--------------------------------------------------
  matrix C_commHAL(styr,endyr,1,nages);                 //landings (numbers) at age
  matrix L_commHAL(styr,endyr,1,nages);                 //landings (mt) at age
  matrix L_commHAL_klb(styr,endyr,1,nages);             //landings (1000 lb whole weight) at age
  vector pred_commHAL_L_2(styr_commHAL_L_2,endyr_commHAL_L_2); //post-WWII yearly landings summed over ages

  matrix C_commDV(styr,endyr,1,nages);                 //landings (numbers) at age
  matrix L_commDV(styr,endyr,1,nages);                 //landings (mt) at age
  matrix L_commDV_klb(styr,endyr,1,nages);             //landings (1000 lb whole weight) at age
  vector pred_commDV_L(styr_commDV_L,endyr_commDV_L);  //yearly landings (klb) summed over ages

  matrix C_HB(styr,endyr,1,nages);                     //landings (numbers) at age
  matrix L_HB(styr,endyr,1,nages);                     //landings (mt) at age
  matrix L_HB_klb(styr,endyr,1,nages);             //landings (1000 lb whole weight) at age
  vector pred_HB_L(styr_HB_L,endyr_HB_L);               //yearly landings (klb) summed over ages

  matrix C_MRFSS(styr,endyr,1,nages);                  //landings (numbers) at age
  matrix L_MRFSS(styr,endyr,1,nages);                  //landings (mt) at age
  matrix L_MRFSS_klb(styr,endyr,1,nages);              //landings (1000 lb whole weight) at age
  vector pred_MRFSS_L(styr_MRFSS_L,endyr_MRFSS_L);     //yearly landings (klb) summed over ages

  matrix C_total(styr,endyr,1,nages);                  //catch in number
  matrix L_total(styr,endyr,1,nages);                  //landings in mt
  vector L_total_yr(styr,endyr);                       //total landings (mt) by yr summed over ages

//---Discards (number dead fish) --------------------------------------------------
  matrix C_commHAL_D(styr_commHAL_D,endyr_commHAL_D,1,nages);//discards (numbers) at age
  vector pred_commHAL_D(styr_commHAL_D,endyr_commHAL_D);     //yearly discards summed over ages
  vector obs_commHAL_D(styr_commHAL_D,endyr_commHAL_D);      //observed releases multiplied by discard mortality
  matrix early_C_commHAL_D(styr,styr_commHAL_D-1,1,nages);//discards (numbers) at age pre-data
  vector early_pred_commHAL_D(styr,styr_commHAL_D-1);     //yearly discards summed over ages pre-data


  matrix C_HB_D(styr_HB_D,endyr_HB_D,1,nages);           //discards (numbers) at age
  vector pred_HB_D(styr_HB_D,endyr_HB_D);                //yearly discards summed over ages
  vector obs_HB_D(styr_HB_D,endyr_HB_D);                 //observed releases multiplied by discard mortality
  matrix early_C_HB_D(styr,styr_HB_D-1,1,nages);//discards (numbers) at age pre-data
  vector early_pred_HB_D(styr,styr_HB_D-1);     //yearly discards summed over ages pre-data

  matrix C_MRFSS_D(styr_HB_D,endyr_MRFSS_D,1,nages);     //discards (numbers) at age
  vector pred_MRFSS_D(styr_MRFSS_D,endyr_MRFSS_D);          //yearly discards summed over ages
  vector obs_MRFSS_D(styr_MRFSS_D,endyr_MRFSS_D);        //observed releases multiplied by discard mortality
  matrix early_C_MRFSS_D(styr,styr_MRFSS_D-1,1,nages);//discards (numbers) at age pre-data
  vector early_pred_MRFSS_D(styr,styr_MRFSS_D-1);     //yearly discards summed over ages pre-data


//---MSY calcs----------------------------------------------------------------------------

  number F_commHAL_prop;  //proportion of F_full attributable to hal, last three yrs
  number F_commDV_prop;   //proportion of F_full attributable to diving, last three yrs
  number F_HB_prop;       //proportion of F_full attributable to headboat, last three yrs
  number F_MRFSS_prop;    //proportion of F_full attributable to MRFSS, last three yrs
  number F_commHAL_D_prop;//proportion of F_full attributable to hal discards, last three yrs
  number F_HB_D_prop;     //proportion of F_full attributable to headboat discards, last three yrs
  number F_MRFSS_D_prop;  //proportion of F_full attributable to MRFSS discards, last three yrs
  number F_temp_sum;      //sum of geom mean full Fs in last yrs, used to compute F_fishery_prop

  number SSB_msy_out;           //SSB at msy
  number F_msy_out;             //F at msy
  number msy_out;               //max sustainable yield
  number B_msy_out;             //total biomass at MSY
  number E_msy_out;             //exploitation rate at MSY (ages E_age_st plus)
  number R_msy_out;             //equilibrium recruitment at F=Fmsy
  number D_msy_out;             //equilibrium dead discards at F=Fmsy
  number spr_msy_out;           //spr at F=Fmsy

  vector N_age_msy(1,nages);         //numbers at age for MSY calculations: beginning of yr
  vector N_age_msy_mdyr(1,nages);    //numbers at age for MSY calculations: mdpt of yr
  vector C_age_msy(1,nages);         //catch at age for MSY calculations
  vector Z_age_msy(1,nages);         //total mortality at age for MSY calculations
  vector D_age_msy(1,nages);         //discard mortality (dead discards) at age for MSY calculations
  vector F_L_age_msy(1,nages);       //fishing mortality (landings, not discards) at age for MSY calculations
  vector F_D_age_msy(1,nages);
  vector F_msy(1,n_iter_msy);        //values of full F to be used in per-recruit and equilibrium calculations
  vector spr_msy(1,n_iter_msy);      //reproductive capacity-per-recruit values corresponding to F values in F_msy
  vector R_eq(1,n_iter_msy);     //equilibrium recruitment values corresponding to F values in F_msy
  vector L_eq(1,n_iter_msy);     //equilibrium landings(mt) values corresponding to F values in F_msy
  vector SSB_eq(1,n_iter_msy);   //equilibrium reproductive capacity values corresponding to F values in F_msy
  vector B_eq(1,n_iter_msy);     //equilibrium biomass values corresponding to F values in F_msy
  vector E_eq(1,n_iter_msy);     //equilibrium exploitation rates corresponding to F values in F_msy
  vector D_eq(1,n_iter_msy);     //equilibrium discards (1000s) corresponding to F values in F_msy

  vector FdF_msy(styr,endyr);
  vector EdE_msy(styr,endyr);
  vector SdSSB_msy(styr,endyr);
  number SdSSB_msy_end;
  number FdF_msy_end;
  number EdE_msy_end;

//--------Mortality------------------------------------------------------------------
  vector M(1,nages);                         //age-dependent natural mortality
  number M_constant;                         //age-indpendent: used only for MSST
  matrix F(styr,endyr,1,nages);
  vector fullF(styr,endyr);                   //Fishing mortality rate by year
  vector E(styr,endyr);                       //Exploitation rate by year
  sdreport_vector fullF_sd(styr,endyr);
  sdreport_vector E_sd(styr,endyr);
  matrix Z(styr,endyr,1,nages);

  init_bounded_number log_avg_F_commHAL_2(-10,0,1); //post-WW2
  init_bounded_dev_vector log_F_dev_commHAL_2(styr_commHAL_L_2,endyr_commHAL_L_2,-10,5,1);
  matrix F_commHAL(styr,endyr,1,nages);
  vector F_commHAL_out(styr,endyr_commHAL_L_2); //used for intermediate calculations in fcn get_mortality
  //number log_F_init_commHAL;

  init_bounded_number log_avg_F_commDV(-10,0,1);
  init_bounded_dev_vector log_F_dev_commDV(styr_commDV_L,endyr_commDV_L,-10,5,2);
  matrix F_commDV(styr,endyr,1,nages);
  vector F_commDV_out(styr,endyr_commDV_L); //used for intermediate calculations in fcn get_mortality
  //number log_F_init_commDV;

  init_bounded_number log_avg_F_HB(-10,0,1);
  init_bounded_dev_vector log_F_dev_HB(styr_HB_L,endyr_HB_L,-10,5,2);
  matrix F_HB(styr,endyr,1,nages);
  vector F_HB_out(styr,endyr_HB_L);        //used for intermediate calculations in fcn get_mortality
  //number log_F_init_HB;

  init_bounded_number log_avg_F_MRFSS(-10,0,1);
  init_bounded_dev_vector log_F_dev_MRFSS(styr_MRFSS_L,endyr_MRFSS_L,-10,5,2);
  matrix F_MRFSS(styr,endyr,1,nages);
  vector F_MRFSS_out(styr,endyr_MRFSS_L); //used for intermediate calculations in fcn get_mortality
  //number log_F_init_MRFSS;

//--Discard mortality stuff------------------------------------------------------------------------------
  init_bounded_number log_avg_F_commHAL_D(-10,0,1);
  init_bounded_dev_vector log_F_dev_commHAL_D(styr_commHAL_D,endyr_commHAL_D,-10,5,2);
  matrix F_commHAL_D(styr,endyr,1,nages);
  vector F_commHAL_D_out(styr,endyr); //used for intermediate calculations in fcn get_mortality
  number F_commHAL_D_ratio;  //ratio of average discard F to fishery F, for projection discards back before data
  matrix sel_commHAL_D(styr,endyr,1,nages);
  vector sel_commHAL_D_dum(1,nages); //logistic version of sel for computing discard sel
  number selpar_commHAL_D_age1;      //discard selectivity of age

  init_bounded_number log_avg_F_HB_D(-10,0,1);
  init_bounded_dev_vector log_F_dev_HB_D(styr_HB_D,endyr_HB_D,-10,5,2);
  matrix F_HB_D(styr,endyr,1,nages);
  vector F_HB_D_out(styr,endyr); //used for intermediate calculations in fcn get_mortality
  number F_HB_D_ratio;  //ratio of average discard F to fishery F, for projection discards back before data
  matrix sel_HB_D(styr,endyr,1,nages);
  vector sel_HB_D_dum(1,nages); //logistic version of sel for computing discard sel
  number selpar_HB_D_age1;      //discard selectivity of age 1

  init_bounded_number log_avg_F_MRFSS_D(-10,0,1);
  init_bounded_dev_vector log_F_dev_MRFSS_D(styr_MRFSS_D,endyr_MRFSS_D,-10,5,2);
  matrix F_MRFSS_D(styr,endyr,1,nages);
  vector F_MRFSS_D_out(styr,endyr); //used for intermediate calculations in fcn get_mortality
  number F_MRFSS_D_ratio;  //ratio of average discard F to fishery F, for projection discards back before data
  matrix sel_MRFSS_D(styr,endyr,1,nages);
  vector sel_MRFSS_D_dum(1,nages); //logistic version of sel for computing discard sel
  number selpar_MRFSS_D_age1;      //discard selectivity of age 1

  number selpar_L50_D_2; //age at 50% discard sel assumed equal to age at size limit (12in=304.8mm)
  number selpar_L50_D_3; //age at 50% discard sel assumed equal to age at size limit (20in=508mm)


  number Dmort_commHAL;
  number Dmort_HB;
  number Dmort_MRFSS;

////---Per-recruit stuff----------------------------------------------------------------------------------
  vector N_age_spr(1,nages);         //numbers at age for SPR calculations: beginning of year
  vector N_age_spr_mdyr(1,nages);    //numbers at age for SPR calculations: midyear
  vector C_age_spr(1,nages);         //catch at age for SPR calculations
  vector Z_age_spr(1,nages);         //total mortality at age for SPR calculations
  vector spr_static(styr,endyr);    //vector of static SPR values by year
  vector F_L_age_spr(1,nages);       //fishing mortality (landings, not discards) at age for SPR calculations
  vector F_spr(1,n_iter_spr);        //values of full F to be used in per-recruit and equilibrium calculations
  vector spr_spr(1,n_iter_spr);      //reporductive capacity-per-recruit values corresponding to F values in F_spr
  vector L_spr(1,n_iter_spr);        //landings(mt)-per-recruit values corresponding to F values in F_spr
  vector E_spr(1,n_iter_spr);        //exploitation rate values corresponding to F values in F_spr

  vector N_spr_F0(1,nages);          //Used to compute spr at F=0: midpt of year
  vector N_bpr_F0(1,nages);          //Used to compute bpr at F=0: start of year
  number spr_F0;                     //Spawning biomass per recruit at F=0
  number bpr_F0;                     //Biomass per recruit at F=0

//-------Objective function components-----------------------------------------------------------------------------
  number w_L;
  number w_D;
  number w_lc;
  number w_ac;
  number w_I_HAL;
  number w_I_HB;
  number w_I_MRFSS;
  number w_R;
  number w_R_init;
  number w_R_end;
  number w_F;
  number w_B1dB0;
  number w_fullF;
  number w_cvlen_dev;
  number w_cvlen_diff;

  number f_HAL_cpue;
  number f_HB_cpue;
  number f_MRFSS_cpue;

  number f_commHAL_L_2;
  number f_commDV_L;
  number f_HB_L;
  number f_MRFSS_L;

  number f_commHAL_D;
  number f_HB_D;
  number f_MRFSS_D;

  number f_commHAL_lenc;
  number f_commDV_lenc;
  number f_HB_lenc;
  number f_MRFSS_lenc;

  number f_commHAL_agec;
  number f_commDV_agec;
  number f_HB_agec;
  number f_MRFSS_agec;

  number f_N_dev;               //weight on recruitment deviations to fit S-R curve
  number f_N_dev_early;         //extra weight against deviations before styr
  number f_N_dev_end;         //extra constraint on last 3 years of recruitment variability
  number f_Fend_constraint;     //penalty for F deviation in last 5 years
  number f_B1dB0_constraint;    //penalty to fix B(styr)/K
  number f_fullF_constraint;    //penalty for fullF>5
  number f_cvlen_dev_constraint; //deviation penalty on cv's of length at age
  number f_cvlen_diff_constraint;//first diff penalty on cv's of length at age

  objective_function_value fval;
  number fval_unwgt;


//--Dummy arrays for output convenience  --------------------------
  vector xdum(styr,endyr);
  vector xdum2(styr,endyr+1);
//--Other dummy variables ----
  number sel_diff_dum;
  number zero_dum;
  number dzero_dum;

  //init_number x_dum; //used only during model development. can be removed.

//##--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
//##--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
INITIALIZATION_SECTION


//##--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
//##--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
GLOBALS_SECTION
  #include "admodel.h"          // Include AD class definitions
  #include "admb2r.cpp"         // Include R-compatible output functions (needs preceding)

//##--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
RUNTIME_SECTION
 maximum_function_evaluations 500, 2000, 10000;
 convergence_criteria 1e-1, 1e-2, 1e-4;

//##--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
//##--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
PRELIMINARY_CALCS_SECTION

// Set values of fixed parameters or set initial guess of estimated parameters
  Dmort_commHAL=set_Dmort_commHAL;
  Dmort_HB=set_Dmort_HB;
  Dmort_MRFSS=set_Dmort_MRFSS;

  obs_commHAL_D=Dmort_commHAL*obs_commHAL_released;
  obs_HB_D=Dmort_HB*obs_HB_released;
  obs_MRFSS_D=Dmort_MRFSS*obs_MRFSS_released;

  E_age_st=set_E_age_st;   //E computed over ages E_age_st +   [E_age_st-1+ if model starts with age 0]

  Linf=set_Linf;
  K=set_K;
  t0=set_t0;

  selpar_L50_D_2=t0-log(1.0-304.8/Linf)/K; //age at size limit: 304.8 = limit in mm
  selpar_L50_D_3=t0-log(1.0-508./Linf)/K;  //age at size limit: 508 = limit in mm

  M=set_M;
  M_constant=set_M_constant;
  steep=set_steep;
  log_dev_N_rec=0.0;
  R_autocorr=set_R_autocorr;

  log_q_HAL=set_logq_HAL;
  log_q_HB=set_logq_HB;
  log_q_MRFSS=set_logq_MRFSS;
  q_rate=set_q_rate;

  L_early_bias=set_L_early_bias;
  L_commHAL_bias=1.0;

  w_L=set_w_L;
  w_D=set_w_D;
  w_lc=set_w_lc;
  w_ac=set_w_ac;
  w_I_HAL=set_w_I_HAL;
  w_I_HB=set_w_I_HB;
  w_I_MRFSS=set_w_I_MRFSS;
  w_R=set_w_R;
  w_R_init=set_w_R_init;
  w_R_end=set_w_R_end;
  w_F=set_w_F;
  w_B1dB0=set_w_B1dB0;
  w_fullF=set_w_fullF;
  w_cvlen_dev=set_w_cvlen_dev;
  w_cvlen_diff=set_w_cvlen_diff;

  log_avg_F_commHAL_2=set_log_avg_F_commHAL_2;
  log_avg_F_commDV=set_log_avg_F_commDV;
  log_avg_F_HB=set_log_avg_F_HB;
  log_avg_F_MRFSS=set_log_avg_F_MRFSS;

  log_avg_F_commHAL_D=set_log_avg_F_commHAL_D;
  log_avg_F_HB_D=set_log_avg_F_HB_D;
  log_avg_F_MRFSS_D=set_log_avg_F_MRFSS_D;

  log_len_cv=log(set_len_cv);
  log_R0=set_log_R0;
  R1_mult=set_R1_mult;
  B1dB0=set_B1dB0;

  selpar_L50_commHAL1=set_selpar_L50_commHAL1;
  selpar_slope_commHAL1=set_selpar_slope_commHAL1;
  selpar_L502_commHAL1=set_selpar_L502_commHAL1;
  selpar_slope2_commHAL1=set_selpar_slope2_commHAL1;
  selpar_L50_commHAL2=set_selpar_L50_commHAL2;
  selpar_slope_commHAL2=set_selpar_slope_commHAL2;
  selpar_L502_commHAL2=set_selpar_L502_commHAL2;
  selpar_slope2_commHAL2=set_selpar_slope2_commHAL2;
  selpar_L50_commHAL3=set_selpar_L50_commHAL3;
  selpar_slope_commHAL3=set_selpar_slope_commHAL3;
  selpar_L502_commHAL3=set_selpar_L502_commHAL3;
  selpar_slope2_commHAL3=set_selpar_slope2_commHAL3;

  selpar_L50_commDV1=set_selpar_L50_commDV1;
  selpar_L502_commDV1=set_selpar_L502_commDV1;
  selpar_slope_commDV1=set_selpar_slope_commDV1;
  selpar_slope2_commDV1=set_selpar_slope2_commDV1;
  //selpar_L50_commDV2=set_selpar_L50_commDV2;
  //selpar_L502_commDV2=set_selpar_L502_commDV2;
  //selpar_slope_commDV2=set_selpar_slope_commDV2;
  //selpar_slope2_commDV2=set_selpar_slope2_commDV2;

  selpar_L50_HB1=set_selpar_L50_HB1;
  selpar_slope_HB1=set_selpar_slope_HB1;
  selpar_L502_HB1=set_selpar_L502_HB1;
  selpar_slope2_HB1=set_selpar_slope2_HB1;
  selpar_L50_HB2=set_selpar_L50_HB2;
  selpar_slope_HB2=set_selpar_slope_HB2;
  selpar_L502_HB2=set_selpar_L502_HB2;
  selpar_slope2_HB2=set_selpar_slope2_HB2;
  selpar_L50_HB3=set_selpar_L50_HB3;
  selpar_slope_HB3=set_selpar_slope_HB3;
  selpar_L502_HB3=set_selpar_L502_HB3;
  selpar_slope2_HB3=set_selpar_slope2_HB3;

  selpar_L50_MRFSS1=set_selpar_L50_MRFSS1;
  selpar_slope_MRFSS1=set_selpar_slope_MRFSS1;
  selpar_L502_MRFSS1=set_selpar_L502_MRFSS1;
  selpar_slope2_MRFSS1=set_selpar_slope2_MRFSS1;
  selpar_L50_MRFSS2=set_selpar_L50_MRFSS2;
  selpar_slope_MRFSS2=set_selpar_slope_MRFSS2;
  selpar_L502_MRFSS2=set_selpar_L502_MRFSS2;
  selpar_slope2_MRFSS2=set_selpar_slope2_MRFSS2;
  selpar_L50_MRFSS3=set_selpar_L50_MRFSS3;
  selpar_slope_MRFSS3=set_selpar_slope_MRFSS3;
  selpar_L502_MRFSS3=set_selpar_L502_MRFSS3;
  selpar_slope2_MRFSS3=set_selpar_slope2_MRFSS3;

  selpar_commHAL_D_age1=set_selpar_commHAL_D_age1;
  selpar_HB_D_age1=set_selpar_HB_D_age1;
  selpar_MRFSS_D_age1=set_selpar_MRFSS_D_age1;

 sqrt2pi=sqrt(2.*3.14159265);
 g2mt=0.000001;         //conversion of grams to metric tons
 g2kg=0.001;         //conversion of grams to kg
 mt2klb=2.20462;        //converstion of metric tons to 1000 lb
 //df=0.001; //difference for msy derivative approximations
 zero_dum=0.0;

 //additive constant to prevent division by zero
 dzero_dum=0.00001;

 SSB_msy_out=0.0;

 maturity_f=maturity_f_obs;
 prop_f=prop_f_obs;

////Fill in maturity matrix for calculations for styr to styr
//    for(iyear=styr; iyear<=styr-1; iyear++)
//      {
//         maturity_f(iyear)=maturity_f_obs;
//         maturity_m(iyear)=maturity_m_obs;
//         prop_m(iyear)=prop_m_obs(styr);
//         prop_f(iyear)=1.0-prop_m_obs(styr);
//      }
//    for (iyear=styr;iyear<=endyr;iyear++)
//      {
//         maturity_f(iyear)=maturity_f_obs;
//         maturity_m(iyear)=maturity_m_obs;
//         prop_m(iyear)=prop_m_obs(iyear);
//         prop_f(iyear)=1.0-prop_m_obs(iyear);
//      }

//Fill in sample sizes of comps sampled in nonconsec yrs.
//Used only for output in R object
      nsamp_commDV_lenc_allyr=missing; //"missing" defined in admb2r.cpp
      nsamp_MRFSS_lenc_allyr=missing;
      nsamp_commHAL_agec_allyr=missing;
      nsamp_commDV_agec_allyr=missing;
      nsamp_HB_agec_allyr=missing;
      for (iyear=1; iyear<=nyr_commDV_lenc; iyear++)
         {
           nsamp_commDV_lenc_allyr(yrs_commDV_lenc(iyear))=nsamp_commDV_lenc(iyear);
         }
      for (iyear=1; iyear<=nyr_MRFSS_lenc; iyear++)
         {
           nsamp_MRFSS_lenc_allyr(yrs_MRFSS_lenc(iyear))=nsamp_MRFSS_lenc(iyear);
         }
      for (iyear=1; iyear<=nyr_commHAL_agec; iyear++)
         {
           nsamp_commHAL_agec_allyr(yrs_commHAL_agec(iyear))=nsamp_commHAL_agec(iyear);
         }
      for (iyear=1; iyear<=nyr_commDV_agec; iyear++)
         {
           nsamp_commDV_agec_allyr(yrs_commDV_agec(iyear))=nsamp_commDV_agec(iyear);
         }
      for (iyear=1; iyear<=nyr_HB_agec; iyear++)
         {
           nsamp_HB_agec_allyr(yrs_HB_agec(iyear))=nsamp_HB_agec(iyear);
         }



//fill in F's, Catch matrices, and log rec dev with zero's
  F_commHAL.initialize();
  C_commHAL.initialize();
  F_commDV.initialize();
  C_commDV.initialize();
  F_HB.initialize();
  C_HB.initialize();
  F_MRFSS.initialize();
  C_MRFSS.initialize();

  F_commHAL_D.initialize();
  F_HB_D.initialize();
  F_MRFSS_D.initialize();

  sel_commHAL_D.initialize();
  sel_HB_D.initialize();
  sel_MRFSS_D.initialize();

  log_dev_R.initialize();

//##--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
//##--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
TOP_OF_MAIN_SECTION
  arrmblsize=20000000;
  gradient_structure::set_MAX_NVAR_OFFSET(1600);
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(2000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(2000000);
  gradient_structure::set_NUM_DEPENDENT_VARIABLES(500);


//>--><>--><>--><>--><>
//##--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
PROCEDURE_SECTION

 R0=mfexp(log_R0);

 //cout<<"start"<<endl;
 get_length_and_weight_at_age();
 //cout << "got length and weight transitions" <<endl;
 get_reprod();
 get_length_at_age_dist();
 //cout<< "got predicted length at age distribution"<<endl;
 get_spr_F0();
 //cout << "got F0 spr" << endl;
 get_selectivity();
 //cout << "got selectivity" << endl;
 get_mortality();
 //cout << "got mortalities" << endl;
 get_bias_corr();
 //cout<< "got recruitment bias correction" << endl;
 get_numbers_at_age();
 //cout << "got numbers at age" << endl;
 get_landings_numbers();
 //cout << "got catch at age" << endl;
 get_landings_wgt();
 //cout << "got landings" << endl;
 get_dead_discards();
 //cout << "got discards" << endl;
 get_indices();
 //cout << "got indices" << endl;
 get_length_comps();
 //cout<< "got length comps"<< endl;
 get_age_comps();
 //cout<< "got age comps"<< endl;

 evaluate_objective_function();
 //cout << "objective function calculations complete" << endl;

FUNCTION get_length_and_weight_at_age
  //compute mean length (mm) and weight (whole and gutted) at age
    meanlen=Linf*(1.0-mfexp(-K*(agebins-t0)));   //length in mm
    wgt_g=wgtpar_a*pow(meanlen,wgtpar_b);        //wgt in grams
    wgt_kg=g2kg*wgt_g;                           //wgt in grams
    wgt=g2mt*wgt_g;     //mt of whole wgt: g2mt converts g to mt
    wgt_klb=mt2klb*wgt;                          //1000 lb of whole wgt


FUNCTION get_reprod

   //product of stuff going into reproductive capacity calcs
   reprod=elem_prod(elem_prod(prop_f,maturity_f),wgt);

FUNCTION get_length_at_age_dist
  //compute matrix of length at age, based on the normal distribution
  for (iage=1;iage<=nages;iage++)
  {
    //len_cv(iage)=mfexp(log_len_cv+log_len_cv_dev(iage));
    len_cv(iage)=mfexp(log_len_cv);
    for (ilen=1;ilen<=nlenbins;ilen++)
    {
      lenprob(iage,ilen)=(mfexp(-(square(lenbins(ilen)-meanlen(iage))/
      (2.*square(len_cv(iage)*meanlen(iage)))))/(sqrt2pi*len_cv(iage)*meanlen(iage)));
    }
    lenprob(iage)/=sum(lenprob(iage)); //standardize to account for truncated normal (i.e., no sizes<0)

  }

FUNCTION get_spr_F0
  //at mdyr, apply half this yr's mortality, half next yr's
  N_spr_F0(1)=1.0*mfexp(-1.0*M(1)/2.0);//at start of yr
  N_bpr_F0(1)=1.0;
  for (iage=2; iage<=nages; iage++)
  {
    //N_spr_F0(iage)=N_spr_F0(iage-1)*mfexp(-1.0*(M(iage-1));
    N_spr_F0(iage)=N_spr_F0(iage-1)*mfexp(-1.0*(M(iage-1)/2.0 + M(iage)/2.0));
    N_bpr_F0(iage)=N_bpr_F0(iage-1)*mfexp(-1.0*(M(iage-1)));
  }
  N_spr_F0(nages)=N_spr_F0(nages)/(1.0-mfexp(-1.0*M(nages))); //plus group (sum of geometric series)
  N_bpr_F0(nages)=N_bpr_F0(nages)/(1.0-mfexp(-1.0*M(nages)));

  spr_F0=sum(elem_prod(N_spr_F0,reprod));
  bpr_F0=sum(elem_prod(N_bpr_F0,wgt));


FUNCTION get_selectivity

// ------- compute landings selectivities by period
  selpar_L50_commHAL1=selpar_L50_HB1;
  selpar_slope_commHAL1=selpar_slope_HB1;

  for (iage=1; iage<=nages; iage++)
  {
     //sel_commHAL_1(iage)=1./(1.+mfexp(-1.*selpar_slope_commHAL1*(double(agebins(iage))-selpar_L50_commHAL1))); //logistic
     sel_commHAL_1(iage)=(1./(1.+mfexp(-1.*selpar_slope_commHAL1*(double(agebins(iage))-
                       selpar_L50_commHAL1))))*(1-(1./(1.+mfexp(-1.*selpar_slope2_commHAL1*
                       (double(agebins(iage))-(selpar_L50_commHAL1+selpar_L502_commHAL1)))))); //double logistic

     //sel_commHAL_2(iage)=1./(1.+mfexp(-1.*selpar_slope_commHAL2*(double(agebins(iage))-selpar_L50_commHAL2))); //logistic
     sel_commHAL_2(iage)=(1./(1.+mfexp(-1.*selpar_slope_commHAL2*(double(agebins(iage))-
                       selpar_L50_commHAL2))))*(1-(1./(1.+mfexp(-1.*selpar_slope2_commHAL2*
                       (double(agebins(iage))-(selpar_L50_commHAL2+selpar_L502_commHAL2)))))); //double logistic

     //sel_commHAL_3(iage)=1./(1.+mfexp(-1.*selpar_slope_commHAL3*(double(agebins(iage))-selpar_L50_commHAL3))); //logistic
     sel_commHAL_3(iage)=(1./(1.+mfexp(-1.*selpar_slope_commHAL3*(double(agebins(iage))-
                       selpar_L50_commHAL3))))*(1-(1./(1.+mfexp(-1.*selpar_slope2_commHAL3*
                       (double(agebins(iage))-(selpar_L50_commHAL3+selpar_L502_commHAL3)))))); //double logistic

     sel_commDV_vec(iage)=(1./(1.+mfexp(-1.*selpar_slope_commDV1*(double(agebins(iage))-
                       selpar_L50_commDV1))))*(1-(1./(1.+mfexp(-1.*selpar_slope2_commDV1*
                       (double(agebins(iage))-(selpar_L50_commDV1+selpar_L502_commDV1)))))); //double logistic

     //sel_HB_1(iage)=1./(1.+mfexp(-1.*selpar_slope_HB1*(double(agebins(iage))-selpar_L50_HB1))); //logistic
     sel_HB_1(iage)=(1./(1.+mfexp(-1.*selpar_slope_HB1*(double(agebins(iage))-
                       selpar_L50_HB1))))*(1-(1./(1.+mfexp(-1.*selpar_slope2_HB1*
                       (double(agebins(iage))-(selpar_L50_HB1+selpar_L502_HB1)))))); //double logistic
     //sel_HB_2(iage)=1./(1.+mfexp(-1.*selpar_slope_HB2*(double(agebins(iage))-selpar_L50_HB2))); //logistic
     sel_HB_2(iage)=(1./(1.+mfexp(-1.*selpar_slope_HB2*(double(agebins(iage))-
                       selpar_L50_HB2))))*(1-(1./(1.+mfexp(-1.*selpar_slope2_HB2*
                       (double(agebins(iage))-(selpar_L50_HB2+selpar_L502_HB2)))))); //double logistic
     //sel_HB_3(iage)=1./(1.+mfexp(-1.*selpar_slope_HB3*(double(agebins(iage))-selpar_L50_HB3))); //logistic
     sel_HB_3(iage)=(1./(1.+mfexp(-1.*selpar_slope_HB3*(double(agebins(iage))-
                       selpar_L50_HB3))))*(1-(1./(1.+mfexp(-1.*selpar_slope2_HB3*
                       (double(agebins(iage))-(selpar_L50_HB3+selpar_L502_HB3)))))); //double logistic
     //sel_MRFSS_2(iage)=1./(1.+mfexp(-1.*selpar_slope_MRFSS2*(double(agebins(iage))-selpar_L50_MRFSS2))); //logistic
     sel_MRFSS_2(iage)=(1./(1.+mfexp(-1.*selpar_slope_MRFSS2*(double(agebins(iage))-
                       selpar_L50_MRFSS2))))*(1-(1./(1.+mfexp(-1.*selpar_slope2_MRFSS2*
                       (double(agebins(iage))-(selpar_L50_MRFSS2+selpar_L502_MRFSS2)))))); //double logistic
     //sel_MRFSS_3(iage)=1./(1.+mfexp(-1.*selpar_slope_MRFSS3*(double(agebins(iage))-selpar_L50_MRFSS3))); //logistic
     sel_MRFSS_3(iage)=(1./(1.+mfexp(-1.*selpar_slope_MRFSS3*(double(agebins(iage))-
                       selpar_L50_MRFSS3))))*(1-(1./(1.+mfexp(-1.*selpar_slope2_MRFSS3*
                       (double(agebins(iage))-(selpar_L50_MRFSS3+selpar_L502_MRFSS3)))))); //double logistic

  }
  sel_commHAL_1=sel_commHAL_1/max(sel_commHAL_1); //re-normalize double logistic
  sel_commHAL_2=sel_commHAL_2/max(sel_commHAL_2); //re-normalize double logistic
  sel_commHAL_3=sel_commHAL_3/max(sel_commHAL_3); //re-normalize double logistic
  sel_commDV_vec=sel_commDV_vec/max(sel_commDV_vec); //re-normalize double logistic
  sel_HB_1=sel_HB_1/max(sel_HB_1); //re-normalize double logistic
  sel_HB_2=sel_HB_2/max(sel_HB_2); //re-normalize double logistic
  sel_HB_3=sel_HB_3/max(sel_HB_3); //re-normalize double logistic
  sel_MRFSS_2=sel_MRFSS_2/max(sel_MRFSS_2); //re-normalize double logistic
  sel_MRFSS_3=sel_MRFSS_3/max(sel_MRFSS_3); //re-normalize double logistic

//-----------fill in years--------------------------------------------

  for (iyear=styr; iyear<=endyr_period1; iyear++)
  //period1 HAL sel assumes HB sel but shifted by that difference in L50 from period2
  {
     sel_commHAL(iyear)=sel_commHAL_1;
     sel_commDV(iyear)=sel_commDV_vec;
     sel_HB(iyear)=sel_HB_1;
     sel_MRFSS(iyear)=sel_HB(iyear); //early period MRFSS same as HB

//     if (iyear>=styr_HB_lenc)  //selectivity in some early HB years varies
//     {
//       for (iage=1; iage<=nages; iage++)
//       {
//         //sel_HB(iyear,iage)=1./(1.+mfexp(-1.*selpar_slope_HB1*(double(agebins(iage))
//         //     -(selpar_L50_HB1+selpar_L50_HB_dev(iyear))))); //logistic
//         sel_HB(iyear,iage)=(1./(1.+mfexp(-1.*selpar_slope_HB1*(double(agebins(iage))-
//                       (selpar_L50_HB1+selpar_L50_HB_dev(iyear))))))*(1-(1./(1.+mfexp(-1.*selpar_slope2_HB1*
//                       (double(agebins(iage))-(selpar_L50_HB1+selpar_L502_HB1)))))); //double logistic
//       }
//       sel_HB(iyear)=sel_HB(iyear)/max(sel_HB(iyear)); //re-normalize double logistic
//     }
//     sel_MRFSS(iyear)=sel_HB(iyear); //early period MRFSS same as HB
  }


  for (iyear=endyr_period1+1; iyear<=endyr_period2; iyear++)
  {
     sel_commHAL(iyear)=sel_commHAL_2;
     sel_commDV(iyear)=sel_commDV_vec;
     sel_HB(iyear)=sel_HB_2;
     sel_MRFSS(iyear)=sel_MRFSS_2;
  }

  for (iyear=endyr_period2+1; iyear<=endyr; iyear++)
  {
     sel_commHAL(iyear)=sel_commHAL_3;
     sel_commDV(iyear)=sel_commDV_vec;
     sel_HB(iyear)=sel_HB_3;
     sel_MRFSS(iyear)=sel_MRFSS_3;
  }


//---Discard selectivities---------------------------------
//---------------------------------------------------------

//period 1 (pre data)
//  for (iage=1; iage<=nages; iage++)
//  {
//   sel_commHAL_D_dum(iage)=1./(1.+mfexp(-1.*selpar_slope_commHAL1*
//                     (double(agebins(iage))-selpar_L50_commHAL1)));
//   sel_HB_D_dum(iage)=1./(1.+mfexp(-1.*selpar_slope_HB1*
//                     (double(agebins(iage))-selpar_L50_HB1)));
//   sel_MRFSS_D_dum(iage)=1./(1.+mfexp(-1.*selpar_slope_MRFSS1*
//                     (double(agebins(iage))-selpar_L50_MRFSS1)));
//   }
//
//  for (iyear=styr;iyear<styr_commHAL_D;iyear++)
//    {
//     sel_commHAL_D(iyear)=1.0-sel_commHAL_D_dum;
//     sel_commHAL_D(iyear)=(sel_commHAL_D(iyear))/(max(sel_commHAL_D(iyear)));
//     sel_commHAL_D(iyear,1)=selpar_commHAL_D_age1;
//     sel_commHAL_D(iyear)=(sel_commHAL_D(iyear))/(max(sel_commHAL_D(iyear)));
//    }
//
//  for (iyear=styr;iyear<styr_HB_D;iyear++)
//    {
//     sel_HB_D(iyear)=1.0-sel_HB_D_dum;
//     sel_HB_D(iyear)=(sel_HB_D(iyear))/(max(sel_HB_D(iyear)));
//     sel_HB_D(iyear,1)=selpar_HB_D_age1;
//     sel_HB_D(iyear)=(sel_HB_D(iyear))/(max(sel_HB_D(iyear)));
//    }
//  for (iyear=styr;iyear<styr_MRFSS_D;iyear++)
//    {
//     sel_MRFSS_D(iyear)=1.0-sel_MRFSS_D_dum;
//     sel_MRFSS_D(iyear)=(sel_MRFSS_D(iyear))/(max(sel_MRFSS_D(iyear)));
//     sel_MRFSS_D(iyear,1)=selpar_MRFSS_D_age1;
//     sel_MRFSS_D(iyear)=(sel_MRFSS_D(iyear))/(max(sel_MRFSS_D(iyear)));
//    }

//period 2
  for (iage=1; iage<=nages; iage++)
  {
   sel_commHAL_D_dum(iage)=1./(1.+mfexp(-1.*selpar_slope_commHAL2*
                     (double(agebins(iage))-selpar_L50_D_2)));
   sel_HB_D_dum(iage)=1./(1.+mfexp(-1.*selpar_slope_HB2*
                     (double(agebins(iage))-selpar_L50_D_2)));
   sel_MRFSS_D_dum(iage)=1./(1.+mfexp(-1.*selpar_slope_MRFSS2*
                     (double(agebins(iage))-selpar_L50_D_2)));
   }

  for (iyear=styr_commHAL_D;iyear<=endyr_period2;iyear++)
    {
     sel_commHAL_D(iyear)=1.0-sel_commHAL_D_dum;
     sel_commHAL_D(iyear)(2,nages)=(sel_commHAL_D(iyear)(2,nages))/(max(sel_commHAL_D(iyear)(2,nages)));
     sel_commHAL_D(iyear,1)=selpar_commHAL_D_age1;
     //sel_commHAL_D(iyear)=(sel_commHAL_D(iyear))/(max(sel_commHAL_D(iyear)));
    }

  for (iyear=styr_HB_D;iyear<=endyr_period2;iyear++)
    {
     sel_HB_D(iyear)=1.0-sel_HB_D_dum;
     sel_HB_D(iyear)(2,nages)=(sel_HB_D(iyear)(2,nages))/(max(sel_HB_D(iyear)(2,nages)));
     sel_HB_D(iyear,1)=selpar_HB_D_age1;
     //sel_HB_D(iyear)=(sel_HB_D(iyear))/(max(sel_HB_D(iyear)));
    }
  for (iyear=styr_MRFSS_D;iyear<=endyr_period2;iyear++)
    {
     sel_MRFSS_D(iyear)=1.0-sel_MRFSS_D_dum;
     sel_MRFSS_D(iyear)(2,nages)=(sel_MRFSS_D(iyear)(2,nages))/(max(sel_MRFSS_D(iyear)(2,nages)));
     sel_MRFSS_D(iyear,1)=selpar_MRFSS_D_age1;
     //sel_MRFSS_D(iyear)=(sel_MRFSS_D(iyear))/(max(sel_MRFSS_D(iyear)));
    }

//period 3
  for (iage=1; iage<=nages; iage++)
  {
   sel_commHAL_D_dum(iage)=1./(1.+mfexp(-1.*selpar_slope_commHAL3*
                     (double(agebins(iage))-selpar_L50_D_3)));
   sel_HB_D_dum(iage)=1./(1.+mfexp(-1.*selpar_slope_HB3*
                     (double(agebins(iage))-selpar_L50_D_3)));
   sel_MRFSS_D_dum(iage)=1./(1.+mfexp(-1.*selpar_slope_MRFSS3*
                     (double(agebins(iage))-selpar_L50_D_3)));
   }
  for (iyear=endyr_period2+1;iyear<=endyr_commHAL_D;iyear++)
    {
     sel_commHAL_D(iyear)=1.0-sel_commHAL_D_dum;
     sel_commHAL_D(iyear)(2,nages)=(sel_commHAL_D(iyear)(2,nages))/(max(sel_commHAL_D(iyear)(2,nages)));
     sel_commHAL_D(iyear,1)=selpar_commHAL_D_age1;
     //sel_commHAL_D(iyear)=(sel_commHAL_D(iyear))/(max(sel_commHAL_D(iyear)));
    }
  for (iyear=endyr_period2+1;iyear<=endyr_HB_D;iyear++)
    {
     sel_HB_D(iyear)=1.0-sel_HB_D_dum;
     sel_HB_D(iyear)(2,nages)=(sel_HB_D(iyear)(2,nages))/(max(sel_HB_D(iyear)(2,nages)));
     sel_HB_D(iyear,1)=selpar_HB_D_age1;
     //sel_HB_D(iyear)=(sel_HB_D(iyear))/(max(sel_HB_D(iyear)));
    }
  for (iyear=endyr_period2+1;iyear<=endyr_MRFSS_D;iyear++)
    {
     sel_MRFSS_D(iyear)=1.0-sel_MRFSS_D_dum;
     sel_MRFSS_D(iyear)(2,nages)=(sel_MRFSS_D(iyear)(2,nages))/(max(sel_MRFSS_D(iyear)(2,nages)));
     sel_MRFSS_D(iyear,1)=selpar_MRFSS_D_age1;
     //sel_MRFSS_D(iyear)=(sel_MRFSS_D(iyear))/(max(sel_MRFSS_D(iyear)));

    }




FUNCTION get_mortality
  fullF=0.0;
  ////initialization F is avg of first 3 yrs of observed landings
  //log_F_init_commHAL=sum(log_F_dev_commHAL(styr_commHAL_L,(styr_commHAL_L+2)))/3.0;
  //log_F_init_commDV=sum(log_F_dev_commDV(styr_commDV_L,(styr_commDV_L+2)))/3.0;
  //log_F_init_HB=sum(log_F_dev_HB(styr_HB_L,(styr_HB_L+2)))/3.0;
  //log_F_init_MRFSS=sum(log_F_dev_MRFSS(styr_MRFSS_L,(styr_MRFSS_L+2)))/3.0;

//  F_commHAL_D_ratio=(sum(mfexp(log_avg_F_commHAL_D+log_F_dev_commHAL_D(styr_commHAL_D,(styr_commHAL_D+7))))/8.0)/
//            (sum(mfexp(log_avg_F_commHAL_2+log_F_dev_commHAL_2(styr_commHAL_D,(styr_commHAL_D+7))))/8.0);
//  F_HB_D_ratio=(sum(mfexp(log_avg_F_HB_D+log_F_dev_HB_D(styr_HB_D,(styr_HB_D+7))))/8.0)/
//            (sum(mfexp(log_avg_F_HB+log_F_dev_HB(styr_HB_D,(styr_HB_D+7))))/8.0);
//  F_MRFSS_D_ratio=(sum(mfexp(log_avg_F_MRFSS_D+log_F_dev_MRFSS_D(styr_MRFSS_D,(styr_MRFSS_D+7))))/8.0)/
//            (sum(mfexp(log_avg_F_MRFSS+log_F_dev_MRFSS(styr_MRFSS_D,(styr_MRFSS_D+7))))/8.0);


  for (iyear=styr; iyear<=endyr; iyear++)
  {
    if(iyear<styr_commHAL_L_2)
    {
      F_commHAL_out(iyear)=0.0;//mfexp(log_avg_F_commHAL+log_F_init_commHAL);
    }
    else
    {
      F_commHAL_out(iyear)=mfexp(log_avg_F_commHAL_2+log_F_dev_commHAL_2(iyear));
    }
    F_commHAL(iyear)=sel_commHAL(iyear)*F_commHAL_out(iyear);

    fullF(iyear)+=F_commHAL_out(iyear);

    if(iyear<styr_commDV_L)
    {
      F_commDV_out(iyear)=0.0;//mfexp(log_avg_F_commDV+log_F_init_commDV);
    }
    else
    {
      F_commDV_out(iyear)=mfexp(log_avg_F_commDV+log_F_dev_commDV(iyear));
    }
    F_commDV(iyear)=sel_commDV(iyear)*F_commDV_out(iyear);
    fullF(iyear)+=F_commDV_out(iyear);

    if(iyear<styr_HB_L)
    {
      F_HB_out(iyear)=0.0;//mfexp(log_avg_F_HB+log_F_init_HB);
    }
    else
    {
      F_HB_out(iyear)=mfexp(log_avg_F_HB+log_F_dev_HB(iyear));
    }
    F_HB(iyear)=sel_HB(iyear)*F_HB_out(iyear);

    fullF(iyear)+=F_HB_out(iyear);

    if(iyear<styr_MRFSS_L)
    {
      F_MRFSS_out(iyear)=0.0;//mfexp(log_avg_F_MRFSS+log_F_init_MRFSS);
    }
    else
    {
      F_MRFSS_out(iyear)=mfexp(log_avg_F_MRFSS+log_F_dev_MRFSS(iyear));
    }
    F_MRFSS(iyear)=sel_MRFSS(iyear)*F_MRFSS_out(iyear);

    fullF(iyear)+=F_MRFSS_out(iyear);



    //discards
    if(iyear>=styr_commHAL_D)
    {
      F_commHAL_D_out(iyear)=mfexp(log_avg_F_commHAL_D+log_F_dev_commHAL_D(iyear));
      F_commHAL_D(iyear)=sel_commHAL_D(iyear)*F_commHAL_D_out(iyear);
      fullF(iyear)+=F_commHAL_D_out(iyear);
    }
//    else
//    {
//      F_commHAL_D_out(iyear)=F_commHAL_D_ratio*F_commHAL_out(iyear);
//      F_commHAL_D(iyear)=sel_commHAL_D(iyear)*F_commHAL_D_out(iyear);
//      fullF(iyear)+=F_commHAL_D_out(iyear);
//    }

    if(iyear>=styr_HB_D)
    {
      F_HB_D_out(iyear)=mfexp(log_avg_F_HB_D+log_F_dev_HB_D(iyear));
      F_HB_D(iyear)=sel_HB_D(iyear)*F_HB_D_out(iyear);
      fullF(iyear)+=F_HB_D_out(iyear);
    }
//    else
//    {
//      F_HB_D_out(iyear)=F_HB_D_ratio*F_HB_out(iyear);
//      F_HB_D(iyear)=sel_HB_D(iyear)*F_HB_D_out(iyear);
//      fullF(iyear)+=F_HB_D_out(iyear);
//    }

    if(iyear>=styr_MRFSS_D)
    {
      F_MRFSS_D_out(iyear)=mfexp(log_avg_F_MRFSS_D+log_F_dev_MRFSS_D(iyear));
      F_MRFSS_D(iyear)=sel_MRFSS_D(iyear)*F_MRFSS_D_out(iyear);
      fullF(iyear)+=F_MRFSS_D_out(iyear);
    }

//    else
//    {
//      F_MRFSS_D_out(iyear)=F_MRFSS_D_ratio*F_MRFSS_out(iyear);
//      F_MRFSS_D(iyear)=sel_MRFSS_D(iyear)*F_MRFSS_D_out(iyear);
//      fullF(iyear)+=F_MRFSS_D_out(iyear);
//    }

    F(iyear)=F_commHAL(iyear); //first in additive series (NO +=)
    F(iyear)+=F_commDV(iyear);
    F(iyear)+=F_HB(iyear);
    F(iyear)+=F_MRFSS(iyear);

    F(iyear)+=F_commHAL_D(iyear);
    F(iyear)+=F_HB_D(iyear);
    F(iyear)+=F_MRFSS_D(iyear);

    Z(iyear)=M+F(iyear);
  }

FUNCTION get_bias_corr
  var_rec_dev=norm2(log_dev_N_rec(styr_rec_dev,(endyr-2))-sum(log_dev_N_rec(styr_rec_dev,(endyr-2)))
              /(nyrs_rec-2.0))/(nyrs_rec-3.0); //sample variance from yrs styr_rec_dev-2004
  if (set_BiasCor <= 0.0) {BiasCor=mfexp(var_rec_dev/2.0);}   //bias correction
  else {BiasCor=set_BiasCor;}


FUNCTION get_numbers_at_age
//Initial age
  S0=spr_F0*R0;
  B0=bpr_F0*R0;
  R1_mult=B1dB0;
  R1=R1_mult*mfexp(log(((0.8*R0*steep*S0)/
     (0.2*R0*spr_F0*(1.0-steep)+(steep-0.2)*S0))+dzero_dum));

  //Assume equilibrium age structure for first year
  N(styr,1)=R1;
  N_mdyr(styr,1)=N(styr,1)*mfexp(-1.*M(1)/2.0);
  for (iage=2; iage<=nages; iage++)
  {
    N(styr,iage)=N(styr,iage-1)*mfexp(-1.*M(iage-1));
    N_mdyr(styr,iage)=N(styr,iage)*mfexp(-1.*M(iage)/2.0);
  }
  //plus group calculation
  N(styr,nages)=N(styr,nages)/(1.-mfexp(-1.*M(nages)));
  N_mdyr(styr,nages)=N_mdyr(styr,nages)/(1.-mfexp(-1.*M(nages)));

  SSB(styr)=sum(elem_prod(N_mdyr(styr),reprod));
  B(styr)=elem_prod(N(styr),wgt);
  totB(styr)=sum(B(styr));

//Rest of years
  for (iyear=styr; iyear<endyr; iyear++)
  {
    if(iyear<(styr_rec_dev-1)) //recruitment follows S-R curve exactly
    {
        //add 0.00001 to avoid log(zero)
        N(iyear+1,1)=BiasCor*mfexp(log(((0.8*R0*steep*SSB(iyear))/(0.2*R0*spr_F0*
            (1.0-steep)+(steep-0.2)*SSB(iyear)))+dzero_dum));
        N(iyear+1)(2,nages)=++elem_prod(N(iyear)(1,nages-1),(mfexp(-1.*Z(iyear)(1,nages-1))));
        N(iyear+1,nages)+=N(iyear,nages)*mfexp(-1.*Z(iyear,nages));//plus group
        N_mdyr(iyear+1)(1,nages)=elem_prod(N(iyear+1)(1,nages),(mfexp(-1.*(Z(iyear+1)(1,nages))/2.0))); //mdyr
        SSB(iyear+1)=sum(elem_prod(N_mdyr(iyear+1),reprod));
        B(iyear+1)=elem_prod(N(iyear+1),wgt);
        totB(iyear+1)=sum(B(iyear+1));
    }
    else   //recruitment follows S-R curve with lognormal deviation
    {
        //add 0.00001 to avoid log(zero)
        N(iyear+1,1)=mfexp(log(((0.8*R0*steep*SSB(iyear))/(0.2*R0*spr_F0*
            (1.0-steep)+(steep-0.2)*SSB(iyear)))+dzero_dum)+log_dev_N_rec(iyear+1));
        N(iyear+1)(2,nages)=++elem_prod(N(iyear)(1,nages-1),(mfexp(-1.*Z(iyear)(1,nages-1))));
        N(iyear+1,nages)+=N(iyear,nages)*mfexp(-1.*Z(iyear,nages));//plus group
        N_mdyr(iyear+1)(1,nages)=elem_prod(N(iyear+1)(1,nages),(mfexp(-1.*(Z(iyear+1)(1,nages))/2.0))); //mdyr
        SSB(iyear+1)=sum(elem_prod(N_mdyr(iyear+1),reprod));
        B(iyear+1)=elem_prod(N(iyear+1),wgt);
        totB(iyear+1)=sum(B(iyear+1));
    }
  }


    //last year (projection) has no recruitment variability
    N(endyr+1,1)=mfexp(log(((0.8*R0*steep*SSB(endyr))/(0.2*R0*spr_F0*
                 (1.0-steep)+(steep-0.2)*SSB(endyr)))+dzero_dum));
    N(endyr+1)(2,nages)=++elem_prod(N(endyr)(1,nages-1),(mfexp(-1.*Z(endyr)(1,nages-1))));
    N(endyr+1,nages)+=N(endyr,nages)*mfexp(-1.*Z(endyr,nages));//plus group
    //SSB(endyr+1)=sum(elem_prod(N(endyr+1),reprod));
    B(endyr+1)=elem_prod(N(endyr+1),wgt);
    totB(endyr+1)=sum(B(endyr+1));

//Recruitment time series
  rec=column(N,1);

//Benchmark parameters
  S1S0=SSB(styr)/S0;
  popstatus=SSB(endyr)/S0;


FUNCTION get_landings_numbers //Baranov catch eqn
  for (iyear=styr; iyear<=endyr; iyear++)
  {
    for (iage=1; iage<=nages; iage++)
    {
      C_commHAL(iyear,iage)=N(iyear,iage)*F_commHAL(iyear,iage)*
        (1.-mfexp(-1.*Z(iyear,iage)))/Z(iyear,iage);
      C_commDV(iyear,iage)=N(iyear,iage)*F_commDV(iyear,iage)*
        (1.-mfexp(-1.*Z(iyear,iage)))/Z(iyear,iage);
      C_HB(iyear,iage)=N(iyear,iage)*F_HB(iyear,iage)*
        (1.-mfexp(-1.*Z(iyear,iage)))/Z(iyear,iage);
      C_MRFSS(iyear,iage)=N(iyear,iage)*F_MRFSS(iyear,iage)*
        (1.-mfexp(-1.*Z(iyear,iage)))/Z(iyear,iage);
    }
  }


FUNCTION get_landings_wgt

//---Predicted landings------------------------
  for (iyear=styr; iyear<=endyr; iyear++)
  {
    L_commHAL(iyear)=elem_prod(C_commHAL(iyear),wgt); //in mt
    L_commDV(iyear)=elem_prod(C_commDV(iyear),wgt);   //in mt
    L_HB(iyear)=elem_prod(C_HB(iyear),wgt);           //in mt
    L_MRFSS(iyear)=elem_prod(C_MRFSS(iyear),wgt);     //in mt

    L_commHAL_klb(iyear)=elem_prod(C_commHAL(iyear),wgt_klb); //in 1000 lb
    L_commDV_klb(iyear)=elem_prod(C_commDV(iyear),wgt_klb);   //in 1000 lb
    L_HB_klb(iyear)=elem_prod(C_HB(iyear),wgt_klb);           //in 1000 lb
    L_MRFSS_klb(iyear)=elem_prod(C_MRFSS(iyear),wgt_klb);     //in 1000 lb
  }


  for (iyear=styr_commHAL_L_2; iyear<=endyr_commHAL_L_2; iyear++)
    {
     pred_commHAL_L_2(iyear)=sum(L_commHAL_klb(iyear));
    }
  for (iyear=styr_commDV_L; iyear<=endyr_commDV_L; iyear++)
    {
     pred_commDV_L(iyear)=sum(L_commDV_klb(iyear));
    }
  for (iyear=styr_HB_L; iyear<=endyr_HB_L; iyear++)
    {
     pred_HB_L(iyear)=sum(L_HB_klb(iyear));
    }
  for (iyear=styr_MRFSS_L; iyear<=endyr_MRFSS_L; iyear++)
    {
     pred_MRFSS_L(iyear)=sum(L_MRFSS_klb(iyear));
    }

FUNCTION get_dead_discards //Baranov catch eqn
  //dead discards at age (number fish)
//  for (iyear=styr; iyear<styr_commHAL_D; iyear++)
//  {
//    for (iage=1; iage<=nages; iage++)
//    {
//      early_C_commHAL_D(iyear,iage)=N(iyear,iage)*F_commHAL_D(iyear,iage)*
//        (1.-mfexp(-1.*Z(iyear,iage)))/Z(iyear,iage);
//    }
//    early_pred_commHAL_D(iyear)=sum(early_C_commHAL_D(iyear))/1000.0; //pred annual dead discards in 1000s
//  }
  for (iyear=styr_commHAL_D; iyear<=endyr_commHAL_D; iyear++)
  {
    for (iage=1; iage<=nages; iage++)
    {
      C_commHAL_D(iyear,iage)=N(iyear,iage)*F_commHAL_D(iyear,iage)*
        (1.-mfexp(-1.*Z(iyear,iage)))/Z(iyear,iage);
    }
    pred_commHAL_D(iyear)=sum(C_commHAL_D(iyear))/1000.0; //pred annual dead discards in 1000s
  }

//  for (iyear=styr; iyear<styr_HB_D; iyear++)
//  {
//    for (iage=1; iage<=nages; iage++)
//    {
//      early_C_HB_D(iyear,iage)=N(iyear,iage)*F_HB_D(iyear,iage)*
//        (1.-mfexp(-1.*Z(iyear,iage)))/Z(iyear,iage);
//    }
//    early_pred_HB_D(iyear)=sum(early_C_HB_D(iyear))/1000.0; //pred annual dead discards in 1000s
//  }
  for (iyear=styr_HB_D; iyear<=endyr_HB_D; iyear++)
  {
    for (iage=1; iage<=nages; iage++)
    {
      C_HB_D(iyear,iage)=N(iyear,iage)*F_HB_D(iyear,iage)*
        (1.-mfexp(-1.*Z(iyear,iage)))/Z(iyear,iage);
    }
    pred_HB_D(iyear)=sum(C_HB_D(iyear))/1000.0; //pred annual dead discards in 1000s
  }

//  for (iyear=styr; iyear<styr_MRFSS_D; iyear++)
//  {
//    for (iage=1; iage<=nages; iage++)
//    {
//      early_C_MRFSS_D(iyear,iage)=N(iyear,iage)*F_MRFSS_D(iyear,iage)*
//        (1.-mfexp(-1.*Z(iyear,iage)))/Z(iyear,iage);
//    }
//    early_pred_MRFSS_D(iyear)=sum(early_C_MRFSS_D(iyear))/1000.0; //pred annual dead discards in 1000s
//  }
  for (iyear=styr_MRFSS_D; iyear<=endyr_MRFSS_D; iyear++)
  {
    for (iage=1; iage<=nages; iage++)
    {
      C_MRFSS_D(iyear,iage)=N(iyear,iage)*F_MRFSS_D(iyear,iage)*
        (1.-mfexp(-1.*Z(iyear,iage)))/Z(iyear,iage);
    }
    pred_MRFSS_D(iyear)=sum(C_MRFSS_D(iyear))/1000.0; //pred annual dead discards in 1000s
  }



FUNCTION get_indices
//---Predicted CPUEs------------------------
 //Hook and line Logbook cpue
  for (iyear=styr_HAL_cpue; iyear<=endyr_HAL_cpue; iyear++)
  {   //index in whole wgt (lb) units, wgt_klb in 1000 lb, but the multiplier (1000) is absorbed by q
      N_HAL(iyear)=elem_prod(elem_prod(N_mdyr(iyear),sel_commHAL(iyear)),wgt_klb);
      pred_HAL_cpue(iyear)=mfexp(log_q_HAL)*(1+(iyear-styr_HAL_cpue)*q_rate)*sum(N_HAL(iyear));
      //pred_HAL_cpue(iyear)=mfexp(log_q_HAL)*sum(N_HAL(iyear));
  }
 //Headboat cpue
  for (iyear=styr_HB_cpue; iyear<=endyr_HB_cpue; iyear++)
  {   //index in number units
      N_HB(iyear)=elem_prod(N_mdyr(iyear),sel_HB(iyear));
      pred_HB_cpue(iyear)=mfexp(log_q_HB)*(1+(iyear-styr_HB_cpue)*q_rate)*sum(N_HB(iyear));
      //pred_HB_cpue(iyear)=mfexp(log_q_HB)*sum(N_HB(iyear));
  }
  //MRFSS cpue
  for (iyear=styr_MRFSS_cpue; iyear<=endyr_MRFSS_cpue; iyear++)
  {   //index in number units
      N_MRFSS(iyear)=elem_prod(N_mdyr(iyear),sel_MRFSS(iyear));
      pred_MRFSS_cpue(iyear)=mfexp(log_q_MRFSS)*(1+(iyear-styr_MRFSS_cpue)*q_rate)*sum(N_MRFSS(iyear));
      //pred_MRFSS_cpue(iyear)=mfexp(log_q_MRFSS)*sum(N_MRFSS(iyear));
  }


FUNCTION get_length_comps
 //Commercial
  for (iyear=styr_commHAL_lenc;iyear<=endyr_commHAL_lenc;iyear++)
  {
    pred_commHAL_lenc(iyear)=(C_commHAL(iyear)*lenprob)/sum(C_commHAL(iyear));
  }
  for (iyear=1;iyear<=nyr_commDV_lenc;iyear++)
  {
    pred_commDV_lenc(iyear)=(C_commDV(yrs_commDV_lenc(iyear))*lenprob)
                              /sum(C_commDV(yrs_commDV_lenc(iyear)));
  }
 //Headboat
  for (iyear=styr_HB_lenc;iyear<=endyr_HB_lenc;iyear++)
  {
    pred_HB_lenc(iyear)=(C_HB(iyear)*lenprob)/sum(C_HB(iyear));
  }
 //MRFSS
  for (iyear=1;iyear<=nyr_MRFSS_lenc;iyear++)
  {
    pred_MRFSS_lenc(iyear)=(C_MRFSS(yrs_MRFSS_lenc(iyear))*lenprob)
                              /sum(C_MRFSS(yrs_MRFSS_lenc(iyear)));
  }

FUNCTION get_age_comps
 //Commercial
  for (iyear=1;iyear<=nyr_commHAL_agec;iyear++)
  {
    pred_commHAL_agec(iyear)=C_commHAL(yrs_commHAL_agec(iyear))/
                             sum(C_commHAL(yrs_commHAL_agec(iyear)));
  }
  for (iyear=1;iyear<=nyr_commDV_agec;iyear++)
  {
    pred_commDV_agec(iyear)=C_commDV(yrs_commDV_agec(iyear))/
                             sum(C_commDV(yrs_commDV_agec(iyear)));
  }
 //Headboat
  for (iyear=1;iyear<=nyr_HB_agec;iyear++)
  {
    pred_HB_agec(iyear)=C_HB(yrs_HB_agec(iyear))/
                             sum(C_HB(yrs_HB_agec(iyear)));
  }
 //MRFSS
  for (iyear=styr_MRFSS_agec;iyear<=endyr_MRFSS_agec;iyear++)
  {
    pred_MRFSS_agec(iyear)=C_MRFSS(iyear)/sum(C_MRFSS(iyear));
  }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FUNCTION get_sel_weighted_current
  F_temp_sum=0.0;
  F_temp_sum+=mfexp((3.0*log_avg_F_commHAL_2+sum(log_F_dev_commHAL_2(endyr-2,endyr)))/3.0);
  F_temp_sum+=mfexp((3.0*log_avg_F_commDV+sum(log_F_dev_commDV(endyr-2,endyr)))/3.0);
  F_temp_sum+=mfexp((3.0*log_avg_F_HB+sum(log_F_dev_HB(endyr-2,endyr)))/3.0);
  F_temp_sum+=mfexp((3.0*log_avg_F_MRFSS+sum(log_F_dev_MRFSS(endyr-2,endyr)))/3.0);
  F_temp_sum+=mfexp((3.0*log_avg_F_commHAL_D+sum(log_F_dev_commHAL_D(endyr-2,endyr)))/3.0);
  F_temp_sum+=mfexp((3.0*log_avg_F_HB_D+sum(log_F_dev_HB_D(endyr-2,endyr)))/3.0);
  F_temp_sum+=mfexp((3.0*log_avg_F_MRFSS_D+sum(log_F_dev_MRFSS_D(endyr-2,endyr)))/3.0);

  F_commHAL_prop=mfexp((3.0*log_avg_F_commHAL_2+sum(log_F_dev_commHAL_2(endyr-2,endyr)))/3.0)/F_temp_sum;
  F_commDV_prop=mfexp((3.0*log_avg_F_commDV+sum(log_F_dev_commDV(endyr-2,endyr)))/3.0)/F_temp_sum;
  F_HB_prop=mfexp((3.0*log_avg_F_HB+sum(log_F_dev_HB(endyr-2,endyr)))/3.0)/F_temp_sum;
  F_MRFSS_prop=mfexp((3.0*log_avg_F_MRFSS+sum(log_F_dev_MRFSS(endyr-2,endyr)))/3.0)/F_temp_sum;
  F_commHAL_D_prop=mfexp((3.0*log_avg_F_commHAL_D+sum(log_F_dev_commHAL_D(endyr-2,endyr)))/3.0)/F_temp_sum;
  F_HB_D_prop=mfexp((3.0*log_avg_F_HB_D+sum(log_F_dev_HB_D(endyr-2,endyr)))/3.0)/F_temp_sum;
  F_MRFSS_D_prop=mfexp((3.0*log_avg_F_MRFSS_D+sum(log_F_dev_MRFSS_D(endyr-2,endyr)))/3.0)/F_temp_sum;

  sel_wgted_L=F_commHAL_prop*sel_commHAL(endyr)+
              F_commDV_prop*sel_commDV(endyr)+
              F_HB_prop*sel_HB(endyr)+
              F_MRFSS_prop*sel_MRFSS(endyr);

  sel_wgted_D=F_commHAL_D_prop*sel_commHAL_D(endyr)+
                F_HB_D_prop*sel_HB_D(endyr)+
                F_MRFSS_D_prop*sel_MRFSS_D(endyr);

  sel_wgted_tot=sel_wgted_L+sel_wgted_D;

  max_sel_wgted_tot=max(sel_wgted_tot);
  sel_wgted_tot/=max_sel_wgted_tot;
  sel_wgted_L/=max_sel_wgted_tot; //landings sel bumped up by same amount as total sel
  sel_wgted_D/=max_sel_wgted_tot;



FUNCTION get_msy

  //fill in Fs for per-recruit stuff
  F_msy.fill_seqadd(0,.001);


  //compute values as functions of F
  for(int ff=1; ff<=n_iter_msy; ff++)
  {
    //uses fishery-weighted F's
    Z_age_msy=0.0;
    F_L_age_msy=0.0;
    F_D_age_msy=0.0;

    F_L_age_msy=F_msy(ff)*sel_wgted_L;
    F_D_age_msy=F_msy(ff)*sel_wgted_D;
    Z_age_msy=M+F_L_age_msy+F_D_age_msy;

    N_age_msy(1)=1.0;
    for (iage=2; iage<=nages; iage++)
    {
      N_age_msy(iage)=N_age_msy(iage-1)*mfexp(-1.*Z_age_msy(iage-1));
    }
    N_age_msy(nages)=N_age_msy(nages)/(1.0-mfexp(-1.*Z_age_msy(nages)));
    N_age_msy_mdyr(1,(nages-1))=elem_prod(N_age_msy(1,(nages-1)),
                                   mfexp((-1.*Z_age_msy(1,(nages-1)))/2.0));
    N_age_msy_mdyr(nages)=(N_age_msy_mdyr(nages-1)*
                          (mfexp(-1.*(Z_age_msy(nages-1)/2 + Z_age_msy(nages)/2) )))
                          /(1.0-mfexp(-1.*Z_age_msy(nages)));

    spr_msy(ff)=sum(elem_prod(N_age_msy_mdyr,reprod));


    //Compute equilibrium values of R (including bias correction), SSB and Yield at each F
    R_eq(ff)=(R0/((5.0*steep-1.0)*spr_msy(ff)))*
                 (BiasCor*4.0*steep*spr_msy(ff)-spr_F0*(1.0-steep));
    if (R_eq(ff)<dzero_dum) {R_eq(ff)=dzero_dum;}
    N_age_msy*=R_eq(ff);
    N_age_msy_mdyr*=R_eq(ff);

    for (iage=1; iage<=nages; iage++)
    {
      C_age_msy(iage)=N_age_msy(iage)*(F_L_age_msy(iage)/Z_age_msy(iage))*
                      (1.-mfexp(-1.*Z_age_msy(iage)));
      D_age_msy(iage)=N_age_msy(iage)*(F_D_age_msy(iage)/Z_age_msy(iage))*
                      (1.-mfexp(-1.0*Z_age_msy(iage)));
    }


    SSB_eq(ff)=sum(elem_prod(N_age_msy_mdyr,reprod));
    B_eq(ff)=sum(elem_prod(N_age_msy,wgt));
    L_eq(ff)=sum(elem_prod(C_age_msy,wgt));
    E_eq(ff)=sum(C_age_msy(E_age_st,nages))/sum(N_age_msy(E_age_st,nages));
    D_eq(ff)=sum(D_age_msy)/1000.0;
  }

  msy_out=max(L_eq);

  for(int ff=1; ff<=n_iter_msy; ff++)
  {
   if(L_eq(ff) == msy_out)
      {
        SSB_msy_out=SSB_eq(ff);
        B_msy_out=B_eq(ff);
        R_msy_out=R_eq(ff);
        D_msy_out=D_eq(ff);
        E_msy_out=E_eq(ff);
        F_msy_out=F_msy(ff);
        spr_msy_out=spr_msy(ff);
      }
  }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FUNCTION get_miscellaneous_stuff

  //compute total catch-at-age and landings
  C_total=(C_HB+C_MRFSS+C_commHAL+C_commDV); //catch in number fish
  L_total=L_HB+L_MRFSS+L_commHAL+L_commDV;   //landings in mt whole weight

  //compute exploitation rate of age E_age_st +
  for(iyear=styr; iyear<=endyr; iyear++)
  {
    E(iyear)=(sum(C_total(iyear)(E_age_st,nages)))/sum(N(iyear)(E_age_st,nages)); //catch in 1000s
    L_total_yr(iyear)=sum(L_total(iyear));
  }

  steep_sd=steep;
  fullF_sd=fullF;
  E_sd=E;

  if(E_msy_out>0)
    {
      EdE_msy=E/E_msy_out;
      EdE_msy_end=EdE_msy(endyr);
    }
  if(F_msy_out>0)
    {
      FdF_msy=fullF/F_msy_out;
      FdF_msy_end=FdF_msy(endyr);
    }
  if(SSB_msy_out>0)
    {
      SdSSB_msy=SSB/SSB_msy_out;
      SdSSB_msy_end=SdSSB_msy(endyr);
    }

   //fill in log recruitment deviations for yrs they are nonzero
   for(iyear=styr_rec_dev; iyear<=endyr; iyear++)
   {
    log_dev_R(iyear)=log_dev_N_rec(iyear);
   }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
FUNCTION get_per_recruit_stuff

  //static per-recruit stuff

  for(iyear=styr; iyear<=endyr; iyear++)
  {
    N_age_spr(1)=1.0;
    for(iage=2; iage<=nages; iage++)
    {
      N_age_spr(iage)=N_age_spr(iage-1)*mfexp(-1.*Z(iyear,iage-1));
    }
    N_age_spr(nages)=N_age_spr(nages)/(1.0-mfexp(-1.*Z(iyear,nages)));
    N_age_spr_mdyr(1,(nages-1))=elem_prod(N_age_spr(1,(nages-1)),
                                mfexp(-1.*Z(iyear)(1,(nages-1))/2.0));
    N_age_spr_mdyr(nages)=(N_age_spr_mdyr(nages-1)*
                          (mfexp(-1.*(Z(iyear)(nages-1)/2.0 + Z(iyear)(nages)/2.0) )))
                          /(1.0-mfexp(-1.*Z_age_msy(nages)));
    spr_static(iyear)=sum(elem_prod(N_age_spr_mdyr,reprod))/spr_F0;
  }

  //fill in Fs for per-recruit stuff
  F_spr.fill_seqadd(0,.01);
  //compute SSB/R and YPR as functions of F
  for(int ff=1; ff<=n_iter_spr; ff++)
  {
    //uses fishery-weighted F's, same as in MSY calculations
    Z_age_spr=0.0;
    F_L_age_spr=0.0;

    F_L_age_spr=F_spr(ff)*sel_wgted_L;

    Z_age_spr=M+F_L_age_spr+F_spr(ff)*sel_wgted_D;

    N_age_spr(1)=1.0;
    for (iage=2; iage<=nages; iage++)
    {
      N_age_spr(iage)=N_age_spr(iage-1)*mfexp(-1.*Z_age_spr(iage-1));
    }
    N_age_spr(nages)=N_age_spr(nages)/(1-mfexp(-1.*Z_age_spr(nages)));
    N_age_spr_mdyr(1,(nages-1))=elem_prod(N_age_spr(1,(nages-1)),
                                   mfexp((-1.*Z_age_spr(1,(nages-1)))/2.0));
    N_age_spr_mdyr(nages)=(N_age_spr_mdyr(nages-1)*
                          (mfexp(-1.*(Z_age_spr(nages-1)/2 + Z_age_spr(nages)/2) )))
                          /(1.0-mfexp(-1.*Z_age_spr(nages)));

    spr_spr(ff)=sum(elem_prod(N_age_spr_mdyr,reprod));
    L_spr(ff)=0.0;
    for (iage=1; iage<=nages; iage++)
    {
      C_age_spr(iage)=N_age_spr(iage)*(F_L_age_spr(iage)/Z_age_spr(iage))*
                      (1.-mfexp(-1.*Z_age_spr(iage)));
      L_spr(ff)+=C_age_spr(iage)*wgt(iage);
    }
    E_spr(ff)=sum(C_age_spr(E_age_st,nages))/sum(N_age_spr(E_age_st,nages));

  }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


FUNCTION evaluate_objective_function
  fval=0.0;
  fval_unwgt=0.0;

//---likelihoods---------------------------
  //fval=square(x_dum-3.0);

//---Indices-------------------------------
  f_HAL_cpue=0.0;
  for (iyear=styr_HAL_cpue; iyear<=endyr_HAL_cpue; iyear++)
  {
    f_HAL_cpue+=square(log((pred_HAL_cpue(iyear)+dzero_dum)/
        (obs_HAL_cpue(iyear)+dzero_dum)))/(2.0*square(HAL_cpue_cv(iyear)));
  }
  fval+=w_I_HAL*f_HAL_cpue;
  fval_unwgt+=f_HAL_cpue;

  f_HB_cpue=0.0;
  for (iyear=styr_HB_cpue; iyear<=endyr_HB_cpue; iyear++)
  {
    f_HB_cpue+=square(log((pred_HB_cpue(iyear)+dzero_dum)/
        (obs_HB_cpue(iyear)+dzero_dum)))/(2.0*square(HB_cpue_cv(iyear)));
  }
  fval+=w_I_HB*f_HB_cpue;
  fval_unwgt+=f_HB_cpue;

  f_MRFSS_cpue=0.0;
  for (iyear=styr_MRFSS_cpue; iyear<=endyr_MRFSS_cpue; iyear++)
  {
    f_MRFSS_cpue+=square(log((pred_MRFSS_cpue(iyear)+dzero_dum)/
        (obs_MRFSS_cpue(iyear)+dzero_dum)))/(2.0*square(MRFSS_cpue_cv(iyear)));
  }
  fval+=w_I_MRFSS*f_MRFSS_cpue;
  fval_unwgt+=f_MRFSS_cpue;


//---Landings-------------------------------

  f_commHAL_L_2=0.0; //in 1000s gutted pounds
  for (iyear=styr_commHAL_L_2; iyear<=endyr_commHAL_L_2; iyear++)
  {
      f_commHAL_L_2+=square(log((pred_commHAL_L_2(iyear)+dzero_dum)/
        (obs_commHAL_L_2(iyear)+dzero_dum)))/(2.0*square(commHAL_L_cv_2(iyear)));
  }
  fval+=w_L*f_commHAL_L_2;
  fval_unwgt+=f_commHAL_L_2;

  f_commDV_L=0.0; //in 1000s gutted pounds
  for (iyear=styr_commDV_L; iyear<=endyr_commDV_L; iyear++)
  {
    f_commDV_L+=square(log((pred_commDV_L(iyear)+dzero_dum)/
        (obs_commDV_L(iyear)+dzero_dum)))/(2.0*square(commDV_L_cv(iyear)));
  }
  fval+=w_L*f_commDV_L;
  fval_unwgt+=f_commDV_L;

  f_HB_L=0.0; //in 1000s
  for (iyear=styr_HB_L; iyear<=endyr_HB_L; iyear++)
  {
    f_HB_L+=square(log((pred_HB_L(iyear)+dzero_dum)/
        (obs_HB_L(iyear)+dzero_dum)))/(2.0*square(HB_L_cv(iyear)));
  }
  fval+=w_L*f_HB_L;
  fval_unwgt+=f_HB_L;

  f_MRFSS_L=0.0; //in 1000s
  for (iyear=styr_MRFSS_L; iyear<=1980; iyear++)
  {
    f_MRFSS_L+=square(log((pred_MRFSS_L(iyear)+dzero_dum)/
        (L_early_bias*obs_MRFSS_L(iyear)+dzero_dum)))/(2.0*square(MRFSS_L_cv(iyear)));
  }
  for (iyear=1981; iyear<=endyr_MRFSS_L; iyear++)
  {
    f_MRFSS_L+=square(log((pred_MRFSS_L(iyear)+dzero_dum)/
        (obs_MRFSS_L(iyear)+dzero_dum)))/(2.0*square(MRFSS_L_cv(iyear)));
  }
  fval+=w_L*f_MRFSS_L;
  fval_unwgt+=f_MRFSS_L;


//---Discards-------------------------------
  f_commHAL_D=0.0; //in 1000s
  for (iyear=styr_commHAL_D; iyear<=endyr_commHAL_D; iyear++)
  {
    f_commHAL_D+=square(log((pred_commHAL_D(iyear)+dzero_dum)/
        (obs_commHAL_D(iyear)+dzero_dum)))/(2.0*square(commHAL_D_cv(iyear)));
  }
  fval+=w_D*f_commHAL_D;
  fval_unwgt+=f_commHAL_D;


  f_HB_D=0.0; //in 1000s
  for (iyear=styr_HB_D; iyear<=endyr_HB_D; iyear++)
  {
    f_HB_D+=square(log((pred_HB_D(iyear)+dzero_dum)/
        (obs_HB_D(iyear)+dzero_dum)))/(2.0*square(HB_D_cv(iyear)));
  }
  fval+=w_D*f_HB_D;
  fval_unwgt+=f_HB_D;

  f_MRFSS_D=0.0; //in 1000s
  for (iyear=styr_MRFSS_D; iyear<=endyr_MRFSS_D; iyear++)
  {
    f_MRFSS_D+=square(log((pred_MRFSS_D(iyear)+dzero_dum)/
        (obs_MRFSS_D(iyear)+dzero_dum)))/(2.0*square(MRFSS_D_cv(iyear)));
  }
  fval+=w_D*f_MRFSS_D;
  fval_unwgt+=f_MRFSS_D;


//---Length comps-------------------------------
  f_commHAL_lenc=0.0;
  for (iyear=styr_commHAL_lenc; iyear<=endyr_commHAL_lenc; iyear++)
  {
    f_commHAL_lenc-=nsamp_commHAL_lenc(iyear)*
        sum( elem_prod((obs_commHAL_lenc(iyear)+dzero_dum),
            log(elem_div((pred_commHAL_lenc(iyear)+dzero_dum),
               (obs_commHAL_lenc(iyear)+dzero_dum)))));
  }
  fval+=w_lc*f_commHAL_lenc;
  fval_unwgt+=f_commHAL_lenc;

  f_commDV_lenc=0.;
  for (iyear=1; iyear<=nyr_commDV_lenc; iyear++)
  {
    f_commDV_lenc-=nsamp_commDV_lenc(iyear)*
         sum(elem_prod((obs_commDV_lenc(iyear)+dzero_dum),
             log(elem_div((pred_commDV_lenc(iyear)+dzero_dum),
                (obs_commDV_lenc(iyear)+dzero_dum)))));
  }
  fval+=w_lc*f_commDV_lenc;
  fval_unwgt+=f_commDV_lenc;

  f_HB_lenc=0.0;
  for (iyear=styr_HB_lenc; iyear<=endyr_HB_lenc; iyear++)
  {
    f_HB_lenc-=nsamp_HB_lenc(iyear)*
        sum( elem_prod((obs_HB_lenc(iyear)+dzero_dum),
            log(elem_div((pred_HB_lenc(iyear)+dzero_dum),
               (obs_HB_lenc(iyear)+dzero_dum)))));
  }
  fval+=w_lc*f_HB_lenc;
  fval_unwgt+=f_HB_lenc;

  f_MRFSS_lenc=0.;
  for (iyear=1; iyear<=nyr_MRFSS_lenc; iyear++)
  {
    f_MRFSS_lenc-=nsamp_MRFSS_lenc(iyear)*
         sum(elem_prod((obs_MRFSS_lenc(iyear)+dzero_dum),
             log(elem_div((pred_MRFSS_lenc(iyear)+dzero_dum),
                (obs_MRFSS_lenc(iyear)+dzero_dum)))));
  }
  fval+=w_lc*f_MRFSS_lenc;
  fval_unwgt+=f_MRFSS_lenc;


//---Age comps-------------------------------
  f_commHAL_agec=0.0;
  for (iyear=1; iyear<=nyr_commHAL_agec; iyear++)
  {
    f_commHAL_agec-=nsamp_commHAL_agec(iyear)*
            sum(elem_prod((obs_commHAL_agec(iyear)+dzero_dum),
               log(elem_div((pred_commHAL_agec(iyear)+dzero_dum),
                  (obs_commHAL_agec(iyear)+dzero_dum)))));
  }
  fval+=w_ac*f_commHAL_agec;
  fval_unwgt+=f_commHAL_agec;

  f_commDV_agec=0.0;
  for (iyear=1; iyear<=nyr_commDV_agec; iyear++)
  {
    f_commDV_agec-=nsamp_commDV_agec(iyear)*
            sum(elem_prod((obs_commDV_agec(iyear)+dzero_dum),
                log(elem_div((pred_commDV_agec(iyear)+dzero_dum),
                   (obs_commDV_agec(iyear)+dzero_dum)))));
  }
  fval+=w_ac*f_commDV_agec;
  fval_unwgt+=f_commDV_agec;

  f_HB_agec=0.0;
  for (iyear=1; iyear<=nyr_HB_agec; iyear++)
  {
    f_HB_agec-=nsamp_HB_agec(iyear)*
            sum(elem_prod((obs_HB_agec(iyear)+dzero_dum),
                log(elem_div((pred_HB_agec(iyear)+dzero_dum),
                   (obs_HB_agec(iyear)+dzero_dum)))));
  }
  fval+=w_ac*f_HB_agec;
  fval_unwgt+=f_HB_agec;

  f_MRFSS_agec=0.0;
  for (iyear=styr_MRFSS_agec; iyear<=endyr_MRFSS_agec; iyear++)
  {
    f_MRFSS_agec-=nsamp_MRFSS_agec(iyear)*
        sum(elem_prod((obs_MRFSS_agec(iyear)+dzero_dum),
            log(elem_div((pred_MRFSS_agec(iyear)+dzero_dum),
                (obs_MRFSS_agec(iyear)+dzero_dum)))));
  }
  fval+=w_ac*f_MRFSS_agec;
  fval_unwgt+=f_MRFSS_agec;


//-----------Constraints and penalties--------------------------------
  f_N_dev=0.0;
  //f_N_dev=norm2(log_dev_N_rec);
  f_N_dev=pow(log_dev_N_rec(styr_rec_dev),2);
  for(iyear=(styr_rec_dev+1); iyear<=endyr; iyear++)
  {
    f_N_dev+=pow(log_dev_N_rec(iyear)-R_autocorr*log_dev_N_rec(iyear-1),2);
  }
  fval+=w_R*f_N_dev;

//  f_N_dev_early=0.0;
//  f_N_dev_early=norm2(log_dev_N_rec(styr_rec_dev,(styr_rec_dev+5)));
//  fval+=w_R_init*f_N_dev_early;

  f_N_dev_end=0.0; //last 3 yrs
    f_N_dev_end=norm2(log_dev_N_rec(endyr-2,endyr));
  fval+=w_R_end*f_N_dev_end;

//  f_B1dB0_constraint=0.0;
//    f_B1dB0_constraint=square(totB(styr)/B0-B1dB0);
//  fval+=w_B1dB0*f_B1dB0_constraint;

  f_Fend_constraint=0.0; //last 3 yrs
  f_Fend_constraint=norm2(first_difference(fullF(endyr-2,endyr)));
  fval+=w_F*f_Fend_constraint;

  f_fullF_constraint=0.0;
  for (iyear=styr; iyear<=endyr; iyear++)
    {
     if (fullF(iyear)>3.0)
     {
     f_fullF_constraint+=square(fullF(iyear)-3.0);
     }
    }
  fval+=w_fullF*f_fullF_constraint;

//  f_cvlen_diff_constraint=0.0;
//    f_cvlen_diff_constraint=norm2(first_difference(log_len_cv_dev));
//  fval+=w_cvlen_diff*f_cvlen_diff_constraint;
//
//  f_cvlen_dev_constraint=0.0;
//    f_cvlen_dev_constraint=norm2(log_len_cv_dev);
//  fval+=w_cvlen_dev*f_cvlen_dev_constraint;

  //cout << "fval = " << fval << "  fval_unwgt = " << fval_unwgt << endl;


REPORT_SECTION
  //cout<<"start report"<<endl;
  get_sel_weighted_current();
  //cout<<"got sel weighted"<<endl;
  get_msy();
  //cout<<"got msy"<<endl;
  get_miscellaneous_stuff();
  //cout<<"got misc stuff"<<endl;
  get_per_recruit_stuff();
  //cout<<"got per recruit"<<endl;
  cout << "BC Fmsy=" << F_msy_out<< "   BC SSBmsy=" << SSB_msy_out <<endl;
  cout<<"Pop status="<<SSB(endyr)/SSB_msy_out<<endl;
  cout << "var_rec_resid="<<var_rec_dev<<endl;
  //cout << "x_dum="<<x_dum<<endl;

  report << "TotalLikelihood " << fval << endl;
  report<<" "<<endl;

  report << "Bias-corrected (BC) MSY stuff" << endl;
  report << "BC Fmsy " << F_msy_out << endl;
  report << "BC Emsy " << E_msy_out << endl;
  report << "BC SSBmsy " << SSB_msy_out << endl;
  report << "BC Rmsy " << R_msy_out << endl;
  report << "BC Bmsy " << B_msy_out << endl;
  report << "BC MSY " << msy_out << endl;
  report << "BC F/Fmsy " << fullF/F_msy_out << endl;
  report << "BC E/Emsy " << E/E_msy_out << endl;
  report << "BC SSB/SSBmsy " << SSB/SSB_msy_out << endl;
  report << "BC B/Bmsy " << totB/B_msy_out << endl;
  report << "BC Yield/MSY " << L_total_yr/msy_out <<endl;
  report << "BC F(2006)/Fmsy " << fullF(endyr)/F_msy_out << endl;
  report << "BC E(2006)/Emsy " << E(endyr)/E_msy_out << endl;
  report << "BC SSB(2006)/SSBmsy " << SSB(endyr)/SSB_msy_out << endl;
  report << "BC Predicted Landings(2006)/MSY " << L_total_yr(endyr)/msy_out <<endl;
  report  << " "<<endl;

  report << "Mortality and growth" << endl;
  report << "M "<<M<<endl;
  report << "Linf="<<Linf << "   K=" <<K<<"   t0="<< t0<<endl;
  report << "mean length " << meanlen << endl;
    report << "cv length " << len_cv << endl;
  report << "wgt " << wgt << endl;
  report<<" "<<endl;

  report << "Stock-Recruit " << endl;
  report << "R0= " << R0 << endl;
  report << "Steepness= " << steep << endl;
  report << "spr_F0= " << spr_F0 << endl;
  report << "Recruits(R) " << rec << endl;
  report << "VirginSSB " << S0 << endl;
  report << "SSB(styr)/VirginSSB " << S1S0 << endl;
  report << "SSB(2006)/VirginSSB " << popstatus << endl;
  report << "SSB " << SSB << endl;
  report << "Biomass " << totB << endl;
  report << "log recruit deviations (styr_rec_dev-2003)   " << log_dev_N_rec(styr_rec_dev,2003) <<endl;
  report << "variance of log rec dev (select yrs)  "<<var_rec_dev<<endl;
  report<<" "<<endl;

  report << "Exploitation rate (1901-2006)" << endl;
 report << E << endl;
 report << "Fully-selected F (1901-2006)" << endl;
 report << fullF << endl;
 report << "Headboat F" << endl;
 report << F_HB_out << endl;
 report << "MRFSS F" << endl;
 report << F_MRFSS_out << endl;
 report << "commHAL F" << endl;
 report << F_commHAL_out << endl;
 report << "commDV F" << endl;
 report << F_commDV_out << endl;
  report<<" "<<endl;
 report << "Headboat selectivity" << endl;
 report << sel_HB << endl;
 report << "Headboat DISCARD selectivity" << endl;
 report << sel_HB_D << endl;
 report << "MRFSS selectivity" << endl;
 report << sel_MRFSS << endl;
 report << "MRFSS DISCARD selectivity" << endl;
 report << sel_MRFSS_D << endl;
 report << "commHAL selectivity" << endl;
 report << sel_commHAL << endl;
 report << "commHAL DISCARD selectivity" << endl;
 report << sel_commHAL_D << endl;
 report << "commDV selectivity" << endl;
 report << sel_commDV << endl;

 report << "log_q_HAL "<<log_q_HAL<<endl;
 report << "Obs  HAL U"<<obs_HAL_cpue << endl;
 report << "pred HAL U"<<pred_HAL_cpue << endl;
 report << "log_q_HB "<<log_q_HB<<endl;
 report << "Obs  HB U"<<obs_HB_cpue << endl;
 report << "pred HB U"<<pred_HB_cpue << endl;
 report << "log_q_MRFSS "<<log_q_MRFSS<<endl;
 report << "Obs  MRFSS U"<<obs_MRFSS_cpue << endl;
 report << "pred MRFSS U"<<pred_MRFSS_cpue << endl;

 report << "Obs  HB landings (1000s)"<<obs_HB_L << endl;
 report << "pred HB landings (1000s)"<<pred_HB_L << endl;
 report << "Obs  MRFSS landings (1000s)"<<obs_MRFSS_L << endl;
 report << "pred MRFSS landings (1000s)"<<pred_MRFSS_L << endl;
 report << "Obs  commHAL landings--postWWII (1000 lb)"<<obs_commHAL_L_2 << endl;
 report << "pred commHAL landings--postWWII (1000 lb)"<<pred_commHAL_L_2 << endl;
 report << "Obs  commDV landings (1000 lb)"<<obs_commDV_L << endl;
 report << "pred commDV landings (1000 lb)"<<pred_commDV_L << endl;

 #include "rs_make_Robject6.cxx"   // write the S-compatible report

