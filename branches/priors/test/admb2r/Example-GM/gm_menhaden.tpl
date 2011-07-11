//--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
//
//  Gulf Menhaden Assessment Model, Sept 2003
//  Sustainable Fisheries Branch, NMFS, Beaufort Lab
//  Updated: 6/15/05
//
//--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>--><>
DATA_SECTION
// Starting and ending year of the model
init_int styr;
init_int endyr;
// Number of ages
init_int nages;
// Vector of ages for age bins
init_ivector agebins(1,nages);

//starting year for recruitment estimation (not being read in)
int styrR;
//this section MUST BE INDENTED!!!
 LOCAL_CALCS
   styrR=styr-(nages-1);
 END_CALCS

// Natural mortality vector
init_vector M_vec(1,nages);

// Stock-recruit function (1=Bev-Holt,2=Ricker)
init_number SRswitch;

//--><>--Biologicals--><>--><>--><>--><>--><>--><>--><>--><>--><>--
//weight-at-age in the fishery (g)
init_matrix wgt_fish(styr,endyr,1,nages);
init_vector wgt_fish_mean(1,nages);
//weight-at-age for the spawning population (g)
init_matrix wgt_spawn(styr,endyr,1,nages);
init_vector wgt_spawn_mean(1,nages);
//maturity of females (%)
init_vector mat_f(1,nages);

//fecundity at age (eggs/female)
init_matrix fec_f(styr,endyr,1,nages);
init_vector fec_f_mean(1,nages);

//--><>--Recruitment Index--><>--><>--><>--><>--><>--><>--
init_int U_age0_styr;
init_int U_age0_endyr;
init_vector U_age0_obs(U_age0_styr,U_age0_endyr);
init_vector U_age0_cv(U_age0_styr,U_age0_endyr);

//--><>--Reduction Fishery--><>--><>--><>--><>--><>--><>--><>--><
// Landings (1000mt)
init_int L_reduction_styr;
init_int L_reduction_endyr;
init_vector L_reduction_obs(L_reduction_styr,L_reduction_endyr);
// Age Compositions
init_int agec_reduction_styr;
init_int agec_reduction_endyr;
init_vector agec_reduction_nsamp(agec_reduction_styr,agec_reduction_endyr);
init_matrix agec_reduction_obs(agec_reduction_styr,agec_reduction_endyr,1,nages);

// Indices for year(y) and age(a)
int y;
int a;

PARAMETER_SECTION

matrix M(styrR,endyr,1,nages);

//Population Numbers
init_bounded_number R1_log(1.0,15.0,1); //log(Recruits) in styrR and first age
number R1_log_constraint;               //constraint for first recruitment estimate
number R1;                              //Recruits in styrR and first age
init_bounded_dev_vector R_log_dev(styrR+1,endyr,-5.0,5.0,2);//recruitment deviations from SR curve
matrix N(styrR,endyr,1,nages);          //Population numbers by year and age: each N represents 1e9 indivs
                                        //landings in 1000mt and fish weight in grams
matrix B(styrR,endyr,1,nages);          //Population biomass by year and age
sdreport_vector R_age0(styrR,endyr);    //Recruits at age 0 by year
sdreport_vector R_age1(styrR,endyr);    //Recruits at age 1 by year
vector R_pred(styrR,endyr);             //S-R curve predicted R's used only in report output
vector R_rep(styrR,endyr);              //replacement R's used only in report output
vector B_sum(styrR,endyr);              //Total biomass by year
sdreport_vector SSB(styrR,endyr);       //Spawning biomass by year
sdreport_vector FEC(styrR,endyr);       //Fecundity by year

//---Stock-Recruit Function (Beverton-Holt, steepness parameterization)----------
init_bounded_number R0_log(1.0,15.0,1); //log(virgin Recruitment)
init_bounded_number steep(0.21,0.99,1); //steepness
sdreport_number steep_sd;
sdreport_number R0;
number S0;          //equal to spr*R0 = virgin SSB
number S1S0;        //SSB(styr) / virgin SSB
number SendS0;      //SSB(endyr) / virgin SSB
number FEC0;        //equal to fpr*R0 = virgin FEC
number FEC1FEC0;    //FEC(styr) / virgin FEC
number FECendFEC0;  //FEC(endyr) / virgin FEC

//Catchability (CPUE q's)----------------------------------------------------
init_bounded_number q_log_U_age0(-12.0,0.0,1);
//Survey and Index Predictions
vector U_age0_pred(U_age0_styr,U_age0_endyr);

//Landings (numbers and weight(1000mt))
matrix L_reduction_num(styrR,endyr,1,nages);
matrix L_total_num(styrR,endyr,1,nages);
matrix L_reduction_wgt(styrR,endyr,1,nages);
matrix L_total_wgt(styrR,endyr,1,nages);

//predicted age comps and landings
matrix agec_reduction_pred(agec_reduction_styr,agec_reduction_endyr,1,nages);
vector L_reduction_pred(L_reduction_styr,L_reduction_endyr);
number L_reduction_cv;

//---Selectivity-------------------------------------------------------------------
//---logistic --------------------------------------------
init_bounded_number selpar_s_reduction_st1(0.1,10.0,1);  //for stanza1
init_bounded_number selpar_A50_reduction_st1(1.0,3.0,1); //for stanza1
init_bounded_number selpar_s_reduction_st2(0.1,10.0,1);  //for stanza2
init_bounded_number selpar_A50_reduction_st2(1.0,3.0,1); //for stanza2

matrix sel_reduction(styr,endyr,1,nages);


//Mortality---------------------------------------------------------------------
init_bounded_number F_log_avg_reduction(-4.0,1.0,1);
init_bounded_dev_vector F_log_dev_reduction(L_reduction_styr,L_reduction_endyr,-5.0,5.0,2);
matrix F_reduction(styrR,endyr,1,nages);

matrix F_total(styrR,endyr,1,nages);//F_total=F_reduction because only one fishery modeled
matrix F_DSV(styrR,endyr,1,nages);  //Popn weighted F of ages 2+
sdreport_vector F_DSV_vec(styrR,endyr);
sdreport_vector E(styrR,endyr);     //exploitation rate
sdreport_vector F_full(styrR,endyr);
matrix Z(styrR,endyr,1,nages);

//---MSY stuff------------------------------------------------------------
//vector of catches for last 3 years
vector C_last3(1,6);
matrix sel_last3(1,6,1,nages);
matrix sel_msy(styrR,endyr,1,nages); //assumed selectivity for msy calcs
//Newton-Raphson stuff
matrix N_msy(1,3,1,nages);
vector SSB_msy(1,3);
vector FEC_msy(1,3);
vector EdE_msy(styrR,endyr);
vector FdF_msy(styrR,endyr);
vector SdSSB_msy(styrR,endyr);
vector SSB_msy_out(styrR,endyr);
number SdSSB_msy_end;
vector FECdFEC_msy(styrR,endyr);
vector FEC_msy_out(styrR,endyr);
number FECdFEC_msy_end;
vector F_msy_out(styrR,endyr);
vector F_DSV_msy_out(styrR,endyr);
number FdF_msy_end;
vector msy_out(styrR,endyr);
vector E_msy_out(styrR,endyr);
vector msy_outx(1,400);
vector xx(1,400);
vector F_msy(1,3);
matrix Z_msy(1,3,1,nages);
vector L_msy(1,3);
vector C_msy(1,nages);
vector spr_msy(1,3);
vector fpr_msy(1,3);
vector R_eq(1,3);
number df;
vector dmsy(styrR,endyr);
number ddmsy;

//Per-recruit stuff
matrix N_spr_F0(styrR,endyr,1,nages);
vector N_spr(1,nages);
vector Z_spr(1,nages);
vector sel_spr(1,nages);
vector spr_F0(styrR,endyr);
number spr_F0_mean;     //spr_F0 based on mean weight
vector spr_static(styr,endyr);
vector fpr_F0(styrR,endyr);
number fpr_F0_mean;     //fpr_F0 based on mean fecundity
vector fpr_static(styr,endyr);
vector F_pr(1,211);     //fishing mortality vector for per-recruit curve output
vector F_DSV_pr(1,211);
vector SSB_pr(1,211);   //spawning biomass per-recruit output
vector FEC_pr(1,211);   //fecundity per-recruit output
vector Y_pr(1,211);     //yield per-recruit output
//Equilibrium stuff for per-recruit analyses
vector Z_eq(1,nages);
vector N_eq(1,nages);
number spr_eq;
number fpr_eq;
number C_eq;
vector SSB_eq(1,211);
vector FEC_eq(1,211);
vector Y_eq(1,211);

//Likelihood weights and components
vector lambda(1,6);
number f_U_age0;
number f_agec_reduction1;
number f_agec_reduction2;
number f_L_reduction;
number f_R_dev;
number f_R1_dev;
objective_function_value fval;

INITIALIZATION_SECTION
//population numbers
R1_log 6;
R0_log 6;
steep 0.7;

//selectivity parameters
selpar_s_reduction_st1 2.0;
selpar_A50_reduction_st1 1.0;
selpar_s_reduction_st2 2.0;
selpar_A50_reduction_st2 1.0;

q_log_U_age0 -5.0;

F_log_avg_reduction 0.0;


GLOBALS_SECTION
  // Include AD class definitions (required for ADMB2R):
  #include <admodel.h>
  // Include ADMB2R file, which must be in current or $ADMB_HOME/include directory:
  #include "admb2r.cpp"

RUNTIME_SECTION
maximum_function_evaluations 5000, 10000;
convergence_criteria 1e-8, 1e-8;

PRELIMINARY_CALCS_SECTION

  F_DSV.initialize();
  F_reduction.initialize();
  L_reduction_num.initialize();

  //Weights for likelihood components
  lambda(1)=1.0;    //CPUE age0 index
  lambda(2)=1.0;    //Reduction fishery age comps sample size 1964-1975
  lambda(3)=1.0;    //Reduction fishery age comps sample size 1976-2002
  lambda(4)=1.0;    //Reduction fishery landings
  lambda(5)=1.0;    //Recruitment deviations
  lambda(6)=1000.0; //constraint on R1 to follow S-R curve

  //re-weight landings cv's
  L_reduction_cv=0.04;

  //Fixed or starting values for some parameters
  R_log_dev=0.0;

  //difference for msy derivative approximations
  df=0.001;

  //fill in F's for per-recruit stuff
  F_pr.fill_seqadd(0,.015);

TOP_OF_MAIN_SECTION
  arrmblsize=2000000;
  gradient_structure::set_MAX_NVAR_OFFSET(1600);
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(15000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(100000000);
  gradient_structure::set_NUM_DEPENDENT_VARIABLES(1000);

PROCEDURE_SECTION
  steep_sd=steep;
  get_selectivity();
  get_mortality();
  get_spr_F0();
  get_numbers_at_age();
  get_catch_at_age();
  get_biomasses();
  get_pred_agecomps();
  evaluate_the_objective_function();

  //Compute the exploitation rate for ages 1+ and pop wgtd F for ages 2+
  for(y=styrR; y<=endyr; y++)
  {
    E(y)=sum(L_total_num(y)(2,nages))/sum(N(y)(2,nages));
    F_DSV_vec(y)=((F_reduction(y)(3,nages))*N(y)(3,nages))/sum(N(y)(3,nages));
  }

FUNCTION get_selectivity
//stanza 1 1964-1975
  for (y=styr; y<=1975; y++)
  {
    for (a=1; a<=nages; a++)
    {sel_reduction(y,a)=1./(1.+mfexp(-1.*selpar_s_reduction_st1*(double(agebins(a))-
                        selpar_A50_reduction_st1)));
    }
  }

//stanza 2 1976-2002
  for (y=1976; y<=endyr; y++)
  {
    for (a=1; a<=nages; a++)
    {
      //---logistic-----------------------------------------------------------------
      sel_reduction(y,a)=1./(1.+mfexp(-1.*selpar_s_reduction_st2*(double(agebins(a))-
                         selpar_A50_reduction_st2)));
    }
  }


FUNCTION get_mortality
  F_full=0.0;
  for (y=styr; y<=endyr; y++)
  {
    M(y)=M_vec;
    if(y>=L_reduction_styr)
    {
      F_reduction(y)=sel_reduction(y)*mfexp(F_log_avg_reduction+F_log_dev_reduction(y));
      F_full(y)+=mfexp(F_log_avg_reduction+F_log_dev_reduction(y));
    }

    F_total(y)=F_reduction(y);
    Z(y)=F_total(y)+M(y);
  }
  for(y=styrR; y<styr; y++)
  {
    M(y)=M(styr);
    Z(y)=Z(styr);
    F_reduction(y)=F_reduction(styr);
    F_full(y)=F_full(styr);
    F_total(y)=F_total(styr);
  }

FUNCTION get_spr_F0
  for(y=styrR; y<=endyr; y++)
  {
    N_spr_F0(y,1)=1.0;
    for(a=2; a<=nages; a++)
    {
      N_spr_F0(y,a)=N_spr_F0(y,a-1)*mfexp(-1.*M(y,a-1));
    }
    N_spr_F0(y,nages)=N_spr_F0(y,nages-1)*mfexp(-1.*M(y,nages-1))/(1-mfexp(-1.*M(y,nages)));//plus group


    if(y<styr)
    {
      spr_F0(y)=sum(elem_prod(elem_prod(N_spr_F0(y),wgt_spawn(styr)),mat_f))*0.5;
      fpr_F0(y)=sum(elem_prod(elem_prod(N_spr_F0(y),mat_f),fec_f(styr)))*0.5;
    }
    if(y>=styr)
    {
      spr_F0(y)=sum(elem_prod(elem_prod(N_spr_F0(y),wgt_spawn(y)),mat_f))*0.5;
      fpr_F0(y)=sum(elem_prod(elem_prod(N_spr_F0(y),mat_f),fec_f(y)))*0.5;
    }
  }
  spr_F0_mean=sum(elem_prod(elem_prod(N_spr_F0(endyr),wgt_spawn_mean),mat_f))*0.5;
  fpr_F0_mean=sum(elem_prod(elem_prod(N_spr_F0(endyr),mat_f),fec_f_mean))*0.5;


FUNCTION get_numbers_at_age
  R0=mfexp(R0_log);
//Initial age
  N(styrR,1)=mfexp(R1_log);
  for (a=2; a<=nages; a++)
  {
    N(styrR,a)=N(styrR,a-1)*mfexp(-1.*Z(styrR,a-1));
  }
//plus group calculation
  N(styrR,nages)=N(styrR,nages-1)*mfexp(-1.*Z(styrR,nages-1))/(1.-mfexp(-1.*Z(styrR,nages)));

//Biomass calcs
  SSB(styrR)=sum(elem_prod(elem_prod(N(styrR),wgt_spawn(styr)),mat_f))*0.5;
  FEC(styrR)=sum(elem_prod(elem_prod(N(styrR),mat_f),fec_f(styr)))*0.5;
  B(styrR)=elem_prod(N(styrR),wgt_fish(styr));
  B_sum(styrR)=sum(B(styrR));

//Constraint for first recruitment to follow S-R curve
  if(SRswitch<2)//Beverton-Holt stock-recruit function
     {R1_log_constraint=log(((0.8*R0*steep*FEC(styrR))/
         (0.2*R0*fpr_F0(styrR)*(1-steep)+(steep-0.2)*FEC(styrR)))+0.00001);}
  if(SRswitch>1)//Ricker stock-recruit function
    {R1_log_constraint=log((FEC(styrR)/fpr_F0(styrR))*mfexp(log((steep*4.0)/
         (1-steep))*(1-FEC(styrR)/(R0*fpr_F0(styrR))))+0.00001);}

//Rest of years ages
  for (y=styrR; y<endyr; y++)

  {
    if(SRswitch<2)//Beverton-Holt stock-recruit function

    {
      N(y+1,1)=mfexp(log(((0.8*R0*steep*FEC(y))/
              (0.2*R0*fpr_F0(y)*(1.0-steep)+(steep-0.2)*FEC(y)))+0.00001)+R_log_dev(y+1));
    }
    if(SRswitch>1)//Ricker stock-recruit function
    {
      N(y+1,1)=mfexp(log((FEC(y)/fpr_F0(y))*mfexp(log((steep*4.0)/
               (1-steep))*(1.0-FEC(y)/(R0*fpr_F0(y))))+0.00001)+R_log_dev(y+1));
    }
    N(y+1)(2,nages)=++elem_prod(N(y)(1,nages-1),(mfexp(-1.*Z(y)(1,nages-1))));
    N(y+1,nages)+=N(y,nages)*mfexp(-1.*Z(y,nages));//plus group
    if(y<styr)
    {
      SSB(y+1)=sum(elem_prod(elem_prod(N(y+1),wgt_spawn(styr)),mat_f))*0.5;
      FEC(y+1)=sum(elem_prod(elem_prod(N(y+1),mat_f),fec_f(styr)))*0.5;
      B(y+1)=elem_prod(N(y+1),wgt_fish(styr));
    }
    if(y>=styr)
    {
      SSB(y+1)=sum(elem_prod(elem_prod(N(y+1),wgt_spawn(y)),mat_f))*0.5;
      FEC(y+1)=sum(elem_prod(elem_prod(N(y+1),mat_f),fec_f(y)))*0.5;
      B(y+1)=elem_prod(N(y+1),wgt_fish(y));
    }
    B_sum(y+1)=sum(B(y+1));
  }

//Recruitment time series
  R_age0=column(N,1);
  R_age1=column(N,2);
  R1=mfexp(R1_log);

//Benchmark parameters
  S0=spr_F0(endyr)*R0;
  S1S0=SSB(styr)/S0;
  SendS0=SSB(endyr)/S0;
  FEC0=fpr_F0(endyr)*R0;
  FEC1FEC0=FEC(styr)/FEC0;
  FECendFEC0=FEC(endyr)/FEC0;

FUNCTION get_catch_at_age
  for (y=styrR; y<=endyr; y++)
  {
    for(a=1; a<=nages; a++)
    {
      L_reduction_num(y,a)=N(y,a)*F_reduction(y,a)*(1.-mfexp(-1.*Z(y,a)))/Z(y,a);
      L_total_num(y,a)=N(y,a)*F_total(y,a)*(1.-mfexp(-1.*Z(y,a)))/Z(y,a);
    }
  }

FUNCTION get_biomasses
  for (y=styrR; y<=endyr; y++)
  {
    if(y<styr)
    {
      L_reduction_wgt(y)=elem_prod(L_reduction_num(y),wgt_fish(styr));
      B(y)=elem_prod(N(y),wgt_fish(styr));
    }
    if(y>=styr)
    {
      L_reduction_wgt(y)=elem_prod(L_reduction_num(y),wgt_fish(y));
      B(y)=elem_prod(N(y),wgt_fish(y));
    }
    L_total_wgt(y)=L_reduction_wgt(y);
    B_sum(y)=sum(B(y));
  }

//predicted landings
  for (y=L_reduction_styr; y<=L_reduction_endyr; y++)
  {
    L_reduction_pred(y)=sum(L_reduction_wgt(y));
  }


//Predicted CPUE age0 index
  for (y=U_age0_styr; y<=U_age0_endyr; y++)
  {
    U_age0_pred(y)=mfexp(q_log_U_age0)*N(y,1);
  }

FUNCTION get_pred_agecomps
  //compute age comps by year
  for (y=agec_reduction_styr;y<=agec_reduction_endyr;y++)
  {
    agec_reduction_pred(y)=L_reduction_num(y)/sum(L_reduction_num(y));
  }


FUNCTION get_msy
  for(y=styrR; y<=endyr; y++)
  {

  if(y>=styr)
  {
      sel_msy(y)=sel_reduction(y);
  }
  if(y<styr)
  {
    sel_msy(y)=sel_reduction(styr);
  }

  //use Newton's method to get Fmsy, MSY, and Smsy
  F_msy(1)=0.2;
  for (int i=1; i<=10; i++){
    F_msy(2)=F_msy(1)-df;
    F_msy(3)=F_msy(1)+df;
    L_msy=0.0;

    Z_msy(1)=sel_msy(y)*F_msy(1)+M(endyr);
    Z_msy(2)=sel_msy(y)*F_msy(2)+M(endyr);
    Z_msy(3)=sel_msy(y)*F_msy(3)+M(endyr);
    //Initial age
    N_msy(1,1)=1.0;
    N_msy(2,1)=1.0;
    N_msy(3,1)=1.0;
    for (a=2; a<=nages; a++)
    {
      N_msy(1,a)=N_msy(1,a-1)*mfexp(-1.*Z_msy(1,a-1));
      N_msy(2,a)=N_msy(2,a-1)*mfexp(-1.*Z_msy(2,a-1));
      N_msy(3,a)=N_msy(3,a-1)*mfexp(-1.*Z_msy(3,a-1));
    }
    //last age is pooled
    N_msy(1,nages)=N_msy(1,nages-1)*mfexp(-1.*Z_msy(1,nages-1))/(1.-mfexp(-1.*Z_msy(1,nages)));
    N_msy(2,nages)=N_msy(2,nages-1)*mfexp(-1.*Z_msy(2,nages-1))/(1.-mfexp(-1.*Z_msy(2,nages)));
    N_msy(3,nages)=N_msy(3,nages-1)*mfexp(-1.*Z_msy(3,nages-1))/(1.-mfexp(-1.*Z_msy(3,nages)));
    spr_msy(1)=sum(elem_prod(elem_prod(N_msy(1),wgt_spawn_mean),mat_f))*0.5;
    spr_msy(2)=sum(elem_prod(elem_prod(N_msy(2),wgt_spawn_mean),mat_f))*0.5;
    spr_msy(3)=sum(elem_prod(elem_prod(N_msy(3),wgt_spawn_mean),mat_f))*0.5;
    fpr_msy(1)=sum(elem_prod(elem_prod(N_msy(1),mat_f),fec_f_mean))*0.5;
    fpr_msy(2)=sum(elem_prod(elem_prod(N_msy(2),mat_f),fec_f_mean))*0.5;
    fpr_msy(3)=sum(elem_prod(elem_prod(N_msy(3),mat_f),fec_f_mean))*0.5;
    if(SRswitch<2) //Beverton-Holt
    {
      R_eq(1)=(R0/((5*steep-1)*fpr_msy(1)))*(4*steep*fpr_msy(1)-fpr_F0_mean*(1-steep));
      R_eq(2)=(R0/((5*steep-1)*fpr_msy(2)))*(4*steep*fpr_msy(2)-fpr_F0_mean*(1-steep));
      R_eq(3)=(R0/((5*steep-1)*fpr_msy(3)))*(4*steep*fpr_msy(3)-fpr_F0_mean*(1-steep));
    }
    if(SRswitch>1) //Ricker
    {
      R_eq(1)=(R0/(fpr_msy(1)/fpr_F0_mean))*(1+log(fpr_msy(1)/fpr_F0_mean)/log((steep*4)/(1-steep)));
      R_eq(2)=(R0/(fpr_msy(2)/fpr_F0_mean))*(1+log(fpr_msy(2)/fpr_F0_mean)/log((steep*4)/(1-steep)));
      R_eq(3)=(R0/(fpr_msy(3)/fpr_F0_mean))*(1+log(fpr_msy(3)/fpr_F0_mean)/log((steep*4)/(1-steep)));
    }
    //Initial age
    N_msy(1)=R_eq(1);
    N_msy(2)=R_eq(2);
    N_msy(3)=R_eq(3);
    for (a=2; a<=nages; a++)
    {
      N_msy(1,a)=N_msy(1,a-1)*mfexp(-1.*Z_msy(1,a-1));
      N_msy(2,a)=N_msy(2,a-1)*mfexp(-1.*Z_msy(2,a-1));
      N_msy(3,a)=N_msy(3,a-1)*mfexp(-1.*Z_msy(3,a-1));
    }
    //last age is pooled
    N_msy(1,nages)=N_msy(1,nages-1)*mfexp(-1.*Z_msy(1,nages-1))/(1.-mfexp(-1.*Z_msy(1,nages)));
    N_msy(2,nages)=N_msy(2,nages-1)*mfexp(-1.*Z_msy(2,nages-1))/(1.-mfexp(-1.*Z_msy(2,nages)));
    N_msy(3,nages)=N_msy(3,nages-1)*mfexp(-1.*Z_msy(3,nages-1))/(1.-mfexp(-1.*Z_msy(3,nages)));
    SSB_msy(1)=sum(elem_prod(elem_prod(N_msy(1),wgt_spawn_mean),mat_f))*0.5;
    SSB_msy(2)=sum(elem_prod(elem_prod(N_msy(2),wgt_spawn_mean),mat_f))*0.5;
    SSB_msy(3)=sum(elem_prod(elem_prod(N_msy(3),wgt_spawn_mean),mat_f))*0.5;
    FEC_msy(1)=sum(elem_prod(elem_prod(N_msy(1),mat_f),fec_f_mean))*0.5;
    FEC_msy(2)=sum(elem_prod(elem_prod(N_msy(2),mat_f),fec_f_mean))*0.5;
    FEC_msy(3)=sum(elem_prod(elem_prod(N_msy(3),mat_f),fec_f_mean))*0.5;
    C_msy=0.0;
    for(a=1; a<=nages; a++){
      C_msy(a)=N_msy(1,a)*((Z_msy(1,a)-M(endyr,a))/Z_msy(1,a))*(1.-mfexp(-1.*Z_msy(1,a)));
      L_msy(1)+=N_msy(1,a)*((Z_msy(1,a)-M(endyr,a))/Z_msy(1,a))*(1.-mfexp(-1.*Z_msy(1,a)))*wgt_fish_mean(a);
      L_msy(2)+=N_msy(2,a)*((Z_msy(2,a)-M(endyr,a))/Z_msy(2,a))*(1.-mfexp(-1.*Z_msy(2,a)))*wgt_fish_mean(a);
      L_msy(3)+=N_msy(3,a)*((Z_msy(3,a)-M(endyr,a))/Z_msy(3,a))*(1.-mfexp(-1.*Z_msy(3,a)))*wgt_fish_mean(a);
    }
    dmsy(y)=(L_msy(3)-L_msy(2))/(2.*df);
    ddmsy=(L_msy(3)-2.*L_msy(1)+L_msy(2))/square(df);
    if(square(ddmsy)>1e-12){
      F_msy(1)-=(dmsy(y)/ddmsy);
    }
    if(F_msy(1)<=df){
      F_msy(1)=df;
    }
  }
  msy_out(y)=L_msy(1);
  E_msy_out(y)=sum(C_msy(2,nages))/sum(N_msy(1)(2,nages));
  F_msy_out(y)=F_msy(1);
  F_DSV_msy_out(y)=((Z_msy(1)-M(endyr))(3,nages)*N_msy(1)(3,nages))/sum(N_msy(1)(3,nages));
  SSB_msy_out(y)=SSB_msy(1);
  FEC_msy_out(y)=FEC_msy(1);
  }

  FdF_msy=elem_div(F_full,F_msy_out);
  SdSSB_msy=elem_div(SSB,SSB_msy_out);
  FECdFEC_msy=elem_div(FEC,FEC_msy_out);
  EdE_msy=elem_div(E,E_msy_out);
  SdSSB_msy_end=SdSSB_msy(endyr);
  FECdFEC_msy_end=FECdFEC_msy(endyr);
  FdF_msy_end=FdF_msy(endyr);

FUNCTION get_per_recruit_stuff

  //static spr
  for(y=styr; y<=endyr; y++)
  {
    N_spr(1)=1.0;
    for(a=2; a<=nages; a++)
    {
      N_spr(a)=N_spr(a-1)*mfexp(-1.*Z(y,a-1));
    }
    N_spr(nages)+=N_spr(nages)*mfexp(-1.*Z(y,nages));//plus group
    spr_static(y)=(sum(elem_prod(elem_prod(N_spr,wgt_spawn(y)),mat_f))*0.5)/spr_F0(y);
    fpr_static(y)=(sum(elem_prod(elem_prod(N_spr,mat_f),fec_f(y)))*0.5)/fpr_F0(y);
  }

  //compute SSB/R and YPR as functions of F, based on mean weights and fecundity
  sel_spr=sel_reduction(endyr);

  for(int f=1; f<=211; f++)
  {
    N_spr(1)=1.0;
    Z_spr=sel_spr*F_pr(f)+M(endyr);
    for (a=2; a<=nages; a++)
    {
      N_spr(a)=N_spr(a-1)*mfexp(-1.*Z_spr(a-1));
    }
    N_spr(nages)=N_spr(nages-1)*mfexp(-1.*Z_spr(nages-1))/(1-mfexp(-1.*Z_spr(nages)));//plus group

    SSB_pr(f)=sum(elem_prod(elem_prod(N_spr,wgt_spawn_mean),mat_f))*0.5;
    FEC_pr(f)=sum(elem_prod(elem_prod(N_spr,mat_f),fec_f_mean))*0.5;


    Y_pr(f)=0.0;
    for (a=1; a<=nages; a++)
    {
      Y_pr(f)+=N_spr(a)*((Z_spr(a)-M(endyr,a))/Z_spr(a))*(1.-mfexp(-1.*Z_spr(a)))*wgt_fish_mean(a);
    }
    F_DSV_pr(f)=((Z_spr(3,nages)-M(endyr)(3,nages))*N_spr(3,nages))/sum(N_spr(3,nages));

    //Compute equilibrium values of SSB and Yield at each F
    //based on stock-recruit curve estimated above
    Z_eq=sel_spr*F_pr(f)+M(endyr);
    N_eq(1)=1.0;
    for (a=2; a<=nages; a++)
    {
      N_eq(a)=N_eq(a-1)*mfexp(-1.*Z_eq(a-1));
    }
    //last age is pooled
    N_eq(nages)=N_eq(nages-1)*mfexp(-1.*Z_eq(nages-1))/(1.-mfexp(-1.*Z_eq(nages)));
    spr_eq=sum(elem_prod(elem_prod(N_eq,wgt_spawn_mean),mat_f))*0.5;
    fpr_eq=sum(elem_prod(elem_prod(N_eq,mat_f),fec_f_mean))*0.5;
    if(SRswitch<2) //Beverton-Holt
    {
      R_eq(1)=(R0/((5.0*steep-1.0)*fpr_eq))*(4.0*steep*fpr_eq-fpr_F0_mean*(1.0-steep));
    }
    if(SRswitch>1) //Ricker
    {
      R_eq(1)=(R0/(fpr_eq/fpr_F0_mean))*(1.0+log(fpr_eq/fpr_F0_mean)/
              log((steep*4.0)/(1.0-steep)));
    }
    //Initial age
    N_eq(1)=R_eq(1);
    for (a=2; a<=nages; a++)
    {
      N_eq(a)=N_eq(a-1)*mfexp(-1.*Z_eq(a-1));
    }
    //last age is pooled
    N_eq(nages)=N_eq(nages-1)*mfexp(-1.*Z_eq(nages-1))/(1.-mfexp(-1.*Z_eq(nages)));
    SSB_eq(f)=sum(elem_prod(elem_prod(N_eq,wgt_spawn_mean),mat_f))*0.5;
    FEC_eq(f)=sum(elem_prod(elem_prod(N_eq,mat_f),fec_f_mean))*0.5;
    C_eq=0.0;
    Y_eq(f)=0.0;
    for(a=1; a<=nages; a++)
    {
      C_eq+=N_eq(a)*((Z_eq(a)-M(endyr,a))/Z_eq(a))*(1.-mfexp(-1.*Z_eq(a)));
      Y_eq(f)+=N_eq(a)*((Z_eq(a)-M(endyr,a))/Z_eq(a))*(1.-mfexp(-1.*Z_eq(a)))*wgt_fish_mean(a);
    }
  }

  SSB_pr=SSB_pr/spr_F0_mean;
  FEC_pr=FEC_pr/fpr_F0_mean;

FUNCTION evaluate_the_objective_function
  fval=0.;

  f_U_age0=0.;
  for (y=U_age0_styr; y<=U_age0_endyr; y++)
  {
    f_U_age0+=square(log(U_age0_obs(y)+.001)-log(U_age0_pred(y)+.001))/(2.0*square(U_age0_cv(y)));
  }
  fval+=lambda(1)*f_U_age0;

  f_agec_reduction1=0.;
    for (y=agec_reduction_styr; y<=1975; y++)
    {
    f_agec_reduction1-=lambda(2)*agec_reduction_nsamp(y)*sum(elem_prod((agec_reduction_obs(y)+.001),log(agec_reduction_pred(y)+.001))-elem_prod((agec_reduction_obs(y)+.001),log(agec_reduction_obs(y)+.001)));
    }
  f_agec_reduction2=0.;
    for (y=1976; y<=agec_reduction_endyr; y++)
    {
    f_agec_reduction2-=lambda(3)*agec_reduction_nsamp(y)*sum(elem_prod((agec_reduction_obs(y)+.001),log(agec_reduction_pred(y)+.001))-elem_prod((agec_reduction_obs(y)+.001),log(agec_reduction_obs(y)+.001)));
    }
  fval+=f_agec_reduction1+f_agec_reduction2;

  f_L_reduction=0.;
  for (y=L_reduction_styr; y<=L_reduction_endyr; y++)
  {
    f_L_reduction+=square(log(L_reduction_obs(y)+.001)-log(L_reduction_pred(y)+.001))/(2.0*square(L_reduction_cv));
  }
  fval+=lambda(4)*f_L_reduction;

  f_R_dev=0.0;
  f_R_dev+=norm2(R_log_dev);
  fval+=lambda(5)*f_R_dev;

  f_R1_dev=0.0;
  f_R1_dev=square(R1_log-R1_log_constraint);
  fval+=lambda(6)*f_R1_dev;

REPORT_SECTION
  get_msy();
  get_per_recruit_stuff();
  cout << "Total Likelihood " << fval << endl;

  report << "Likelihood " << "Value " << "Weight" << endl;
  report << "age0_index " << f_U_age0 << " " << lambda(1) << endl;
  report << "reduction_agec 1964-1975 " << f_agec_reduction1 << " " << lambda(2) << endl;
  report << "reduction_agec 1976-2002 " << f_agec_reduction2 << " " << lambda(3) << endl;
  report << "L_reduction_wgt " << f_L_reduction << " " << lambda(4) << endl;
  report << "R_dev " << f_R_dev << " " << lambda(5) << endl;

  report << "TotalLikelihood " << fval << endl;

  report << "Error levels in model" << endl;
  report << "U_age0_cv " << U_age0_cv << endl;
  report << "L_reduction_cv " << L_reduction_cv << endl;

  report << "NaturalMortality in last year " << endl;
  report << "Age " << agebins << endl;
  report << "M " << M(endyr) << endl;

  report << "VirginSSB " << S0 << endl;
  report << "SSB1/VirginSSB " << S1S0 << endl;
  report << "SSB(end)/VirginSSB " << SendS0 << endl;
  report << "VirginFEC " << FEC0 << endl;
  report << "FEC1/VirginFEC " << FEC1FEC0 << endl;
  report << "FEC(end)/VirginSSB " << FECendFEC0 << endl;

  report << "SSB/R_F0" << endl;
  report << "Year";
  for(y=styrR; y<=endyr; y++)
  {
    report << " " << y;
  }
  report << endl;
  report << "SSB/R_F0 " << spr_F0 << endl;
  report << "FEC/R_F0 " << fpr_F0 << endl;
  report << "Steepness " << steep << endl;
  report << "R0 " << R0 << endl;
  if(SRswitch<2)
  {
    report << "S-R_curve Beverton-Holt" << endl;
  }
  if(SRswitch>1)
  {
    report << "S-R_curve Ricker" << endl;
  }

  report << "MSYstuff" << endl;
  report << "N-R_convergence " << dmsy << endl;
  report << "Emsy " << E_msy_out << endl;
  report << "Fmsy " << F_msy_out << endl;
  report << "Fmsy_DSV " << F_DSV_msy_out << endl;
  report << "SSBmsy " << SSB_msy_out << endl;
  report << "FECmsy " << FEC_msy_out << endl;
  report << "MSY " << msy_out << endl;
  report << "SSB2004/SSBmsy " << SdSSB_msy_end << endl;
  report << "FEC2004/FECmsy " << FECdFEC_msy_end << endl;
  report << "F2004/Fmsy " << FdF_msy_end << endl;
  report << "F_DSV(2004)/Fmsy_DSV " << F_DSV_vec(endyr)/F_DSV_msy_out(endyr) << endl;

  report << "Year";
  for(y=styrR; y<=endyr; y++)
  {
    report << " " << y;
  }
  report << endl;
  report << "E/Emsy " << EdE_msy << endl;
  report << "F/Fmsy " << FdF_msy << endl;
  report << "F_DSV/Fmsy_DSV " << elem_div(F_DSV_vec,F_DSV_msy_out) << endl;
  report << "SSB/SSBmsy " << SdSSB_msy << endl;
  report << "FEC/FECmsy " << FECdFEC_msy << endl;

  report << "Recruits" << endl;
  report << "Year";
  for(y=styrR; y<=endyr; y++)
  {
    report << " " << y;
  }
  report << endl;
  report << "Age-0_recruits " << R_age0 << endl;
  report << "Age-1_recruits " << R_age1 << endl;
  report << "SSB" << endl;
  report << "Year";
  for(y=styrR; y<=endyr; y++)
  {
    report << " " << y;
  }
  report << endl;
  report << "SSB " << SSB << endl;
  report << "FEC " << FEC << endl;
  report << "Lagged_R " << R_age0(styrR+1,endyr) << endl;

  for(y=styrR; y<=endyr; y++)
  {
      if(y<styrR+1)
      {
        if(SRswitch<2)
        {
          R_pred(y)=(0.8*R0*steep*FEC(y))/(0.2*fpr_F0(y)*R0*(1-steep)+(steep-0.2)*FEC(y));
        }
        if(SRswitch>1)
        {
          R_pred(y)=(FEC(y)/fpr_F0(y))*mfexp(log((steep*4)/(1-steep))*(1-FEC(y)/(R0*fpr_F0(y))));
        }
      }
      else
      {
        if(SRswitch<2)
        {
          R_pred(y)=(0.8*R0*steep*FEC(y-1))/(0.2*fpr_F0(y-1)*R0*(1-steep)+(steep-0.2)*FEC(y-1));
        }
        if(SRswitch>1)
        {
          R_pred(y)=(FEC(y-1)/fpr_F0(y-1))*mfexp(log((steep*4)/(1-steep))*(1-FEC(y-1)/(R0*fpr_F0(y-1))));
        }
      }

      R_rep(y)=FEC(y)/fpr_F0(y);
  }
  report << "S-R_R " << R_pred << endl;
  report << "Replacement " << R_rep << endl;


  report << "Reduction fishery selectivity A50 parameters" << endl;
  report << "Year";
  for(y=agec_reduction_styr; y<=endyr; y++)
  {
    report << " " << y;
  }
  report << endl;
  report << "Reduction fishery selectivity" << endl;
  report << "Year/Age " << agebins << endl;
  for(y=agec_reduction_styr; y<=endyr; y++)
  {
    report << y << sel_reduction(y) << endl;
  }

  report << "Full F reduction fishery" << endl;
  report << "Year";
  for(y=L_reduction_styr; y<=endyr; y++)
  {
    report << " " << y;
  }
  report << endl;
  report << "FullF_reduction " << mfexp(F_log_avg_reduction+F_log_dev_reduction) << endl;
  report << "Year";

  report << "Year";
  for(y=styrR; y<=endyr; y++)
  {
    report << " " << y;
  }
  report << endl;
  report << "FullF_total " << F_full << endl;
  report << "Doug's_F " << F_DSV_vec << endl;
  report << "Exploitation_rate " << E << endl;

  report << "CPUE_age0_index" << endl;
  report << "age0_index_q " << mfexp(q_log_U_age0) << endl;
  report << "Year";

  for(y=U_age0_styr; y<=endyr; y++)
  {
    report << " " << y;
  }
  report << endl;
  report << "Observed " << U_age0_obs << endl;

  report << "Predicted " << U_age0_pred << endl;

  report << "reduction landings (1000mt)" << endl;
  report << "Year";
  for(y=L_reduction_styr; y<=endyr; y++)
  {
    report << " " << y;
  }
  report << endl;
  report << "Observed " << L_reduction_obs << endl;
  report << "Predicted " << L_reduction_pred << endl;


  report << "NaturalMortality " << endl;
  report << "Year/Age " << agebins << endl;
  for(y=styrR; y<=endyr; y++)
  {
    report << y << M(y) << endl;
  }
  report << "N (billions)" << endl;
  report << "Year/Age " << agebins << endl;
  for(y=styrR; y<=endyr; y++)
  {
    report << y << N(y) << endl;
  }
  report << "B (1000mt)" << endl;
  report << "Year/Age " << agebins << endl;
  for(y=styrR; y<=endyr; y++)
  {
    report << y << B(y) << endl;
  }

  report << "Catch reduction (billions)" << endl;
  report << "Year/Age " << agebins << endl;
  for(y=styrR; y<=endyr; y++)
  {
    report << y << L_reduction_num(y) << endl;
  }

  for (y=agec_reduction_styr; y<=agec_reduction_endyr; y++){
    report << "Reduction Age Composition " << y << endl;
    report << "Age " << agebins << endl;
    report << "Observed" << agec_reduction_obs(y) << endl;
    report << "Predicted" << agec_reduction_pred(y) << endl;

  }


  report << "Reduction age comp residuals" << endl;
  report << "Year " << "Age " << "Residual " << endl;
  for (y=agec_reduction_styr; y<=agec_reduction_endyr; y++){
    for(a=1; a<=nages; a++){
      report << y << " " << agebins(a) << " " << agec_reduction_obs(y,a)-agec_reduction_pred(y,a) << endl;
    }
  }
  report << " " << endl;



  report << "Static SPR" << endl;
  report << "Year";
  for(y=styr; y<=endyr; y++)
  {
    report << " " << y;
  }
  report << endl;
  report << "static_SPR " << spr_static << endl;
  report << "static_FPR " << fpr_static << endl;


  report << "F F_DSV SPR YPR SSB_eq Y_eq" << endl;
  for(a=1; a<=201; a++)
  {

    report << F_pr(a) << " " << F_DSV_pr(a) << " " << SSB_pr(a) << " " << Y_pr(a) << " " << SSB_eq(a) << " " << Y_eq(a) << endl;
  }

  report << "F F_DSV FPR YPR FEC_eq Y_eq" << endl;
  for(a=1; a<=211; a++)
  {

    report << F_pr(a) << " " << F_DSV_pr(a) << " " << FEC_pr(a) << " " << Y_pr(a) << " " << FEC_eq(a) << " " << Y_eq(a) << endl;
  }

  report << "selectivity (catch-weighted)" << endl;
  report << "Year/Age " << agebins << endl;
  for(y=styrR; y<=endyr; y++)
  {
    report << y << sel_msy(y) << endl;
  }

  #include "GM_make_Robject.cxx"   // ADMB code to write the S-compatible report

