// SS3
// Developed by Richard Methot, NOAA Fisheries

//  TAG_0000_#  DATA_SECTION
DATA_SECTION

  !!version_info+="SS-V3.02C_SAFE;_01/29/09;_Stock_Synthesis_by_Richard_Methot_(NOAA);_using_Otter_Research_ADMB_7.0.1";

//*********COUNTERS*************************// ProgLabel_030
  int z // counters for size (length)
  int z1  // min for z counter
  int z2  // max for z counter
  int  L1  //  reserve for future use in selecting sex specific length data
  int  L2  //  used for l+nlength to get length bin for males
  int  A2  //  used for a+nages+1 to get true age bin for males
  int a1  // use to track a subset of ages
  int f // counter for fleets and surveys
  int g // counter for gmorph
  int gg  // counter for gender
  int a // counter for ages
  int b // counter for age bins
  int p // counter for area
  int p1
  int p2 // counter for destination area in migration
  int i // counter for observations
  int y // counter for year
  int yz // year, but not allowed to extend past endyr
  int s // counter for seasons
  int s2  // destination season
  int smid  // = s+nseas
  int t // counter for time, combining year and season
  int j
  int j1
  int j2
  int k
  int s_off  // offset for male section of vectors
  int Fishon  // whether or not to do fishery catch in equil_calc
  int NP  // number of parameters
  int Ip  // parameter counter
  int firstseas   // used to start season loops at the birthseason
  int t_base;    //
  int niter  // iteration count
  int loop
  int TG_t;  // time counter (in seasons) for tag groups
  int Fore_catch_start
  int ParCount;
  int N_SC;
  int N_DC;
  int N_CC;
  int N_FC;

//  ProgLabel_0005   create prefixes for parameter labels
 LOCAL_CALCS
  adstring_array NumLbl;
  adstring_array GenderLbl;   // gender label
  adstring_array CRLF;   // blank to terminate lines

  CRLF+="";
  GenderLbl+="Fem";
  GenderLbl+="Mal";
  onenum="    ";
  for (i=1;i<=199;i++)
  {
//  _itoa( i, onenum, 10 );
  sprintf(onenum, "%d", i);
  NumLbl+=onenum+CRLF(1);
  }
 END_CALCS

//  TAG_0001    read the STARTER.SS file
 LOCAL_CALCS
  ad_comm::change_datafile_name("starter.SS");       //  get filenames
  cout<<" reading from STARTER.SS"<<endl;
  adstring checkchar;
  line_adstring readline;
  checkchar="";
  ifstream Starter_Stream("starter.SS");
   //  this opens a different logical file with a separate pointer from the pointer that ADMB uses when reading using init command to read from global_datafile
  k=1;
  N_SC=0;
  while(k!=0)
  {
//    *(ad_comm::global_datafile) >> readline   //  this reads the whole file, not a single line so cannot be used here
    Starter_Stream >>  readline;          // reads a single line from input stream
    if(length(readline)>2)
    {
      checkchar=readline(1);
      k=strcmp(checkchar,"#");
      checkchar=readline(1,2);
      j=strcmp(checkchar,"#C");
      if(j==0) {N_SC++; Starter_Comments+=readline;}
    }
  }
 END_CALCS

  init_adstring datfilename
  !!echoinput<<datfilename<<"  datfilename"<<endl;
  init_adstring ctlfilename
  !!echoinput<<ctlfilename<<"  ctlfilename"<<endl;
  init_int readparfile
  !!echoinput<<readparfile<<"  readparfile"<<endl;
  init_int rundetail
  !!echoinput<<rundetail<<"  rundetail"<<endl;
 init_int reportdetail
   !!echoinput<<reportdetail<<"  reportdetail"<<endl;
  init_int docheckup           // flag for ending dump to "checkup.SS"
   !!echoinput<<docheckup<<"  docheckup"<<endl;
  init_int Do_ParmTrace
   !!echoinput<<Do_ParmTrace<<"  Do_ParmTrace"<<endl;
  init_int Do_CumReport
   !!echoinput<<Do_CumReport<<"  Do_CumReport"<<endl;
  init_int Do_all_priors
   !!echoinput<<Do_all_priors<<"  Do_all_priors"<<endl;
  init_int SoftBound
   !!echoinput<<SoftBound<<"  SoftBound"<<endl;
  init_int N_nudata
   !!echoinput<<N_nudata<<"  N_nudata"<<endl;
  init_int Turn_off_phase
   !!echoinput<<Turn_off_phase<<"  Turn_off_phase"<<endl;

// read in burn and thinning intervals
  init_int burn_intvl
   !!echoinput<<burn_intvl<<"  MCMC burn_intvl"<<endl;
  init_int thin_intvl
   !!echoinput<<thin_intvl<<"  MCMC thin_intvl"<<endl;

  init_number jitter
   !!echoinput<<jitter<<"  jitter fraction for initial parm values"<<endl;

  init_int STD_Yr_min  // min yr for sdreport
   !!echoinput<<STD_Yr_min<<"  STD_Yr_min"<<endl;
  init_int STD_Yr_max  // max yr for sdreport
   !!echoinput<<STD_Yr_max<<"  STD_Yr_max"<<endl;
  init_int N_STD_Yr_RD  // N extra years to read
   !!echoinput<<N_STD_Yr_RD<<"  N extra STD years to read"<<endl;
  int N_STD_Yr
  init_ivector STD_Yr_RD(1,N_STD_Yr_RD)
   !!if(N_STD_Yr_RD>0) echoinput<<STD_Yr_RD<<"  vector of extra STD years"<<endl;
  // wait to process the above until after styr, endyr, N-forecast_yrs are read in data and forecast sections below

  int save_for_report;
  int save_gparm;
  int save_gparm_print;
  int N_warn;
  !! save_for_report=0;
  !! save_gparm=0;
  !! N_warn=0;

// set up the mcmc chain counter
  int mccounter;
  !! mccounter = 1;
  int done_run;
  !! done_run=0;

// set up the convergence criteria
  vector func_eval(1,50);
  vector func_conv(1,50);
//  number final_conv;
  init_number final_conv;
   !!echoinput<<final_conv<<"  final_conv"<<endl;

  !! func_eval.fill_seqadd(100,0);
  !! func_conv.fill_seqadd(1,0);
  !! func_conv(1)=10.;
  !! func_conv(2)=10.;

  init_int retro_yr;             //  introduce year for retrospective analysis
   !!echoinput<<retro_yr<<"  retro_yr"<<endl;
  int fishery_on_off;
  !! fishery_on_off=1;

  init_int Smry_Age
   !!echoinput<<Smry_Age<<"  Smry_Age"<<endl;

  init_int depletion_basis   // 0=skip; 1=fraction of B0; 2=fraction of Bmsy where fraction is depletion_level 3=rel to styr
   !!echoinput<<depletion_basis<<"  depletion_basis"<<endl;
  init_number depletion_level
   !!echoinput<<depletion_level<<"  depletion_level"<<endl;
  init_int SPR_reporting  // 0=skip; 1=SPR; 2=SPR_MSY; 3=SPR_Btarget; 4=(1-SPR)
   !!echoinput<<SPR_reporting<<"  SPR_reporting"<<endl;
  init_int F_reporting  // 0=skip; 1=exploit(Bio); 2=exploit(Num); 3=sum(frates)
   !!echoinput<<F_reporting<<"  F_reporting"<<endl;
  init_int F_report_basis // 0=raw; 1=rel Fspr; 2=rel Fmsy ; 3=rel Fbtgt
   !!echoinput<<F_report_basis<<"  F_report_basis"<<endl;
  init_int finish_starter

 LOCAL_CALCS
   if(finish_starter!=999) {cout<<" error reading starter file "<<finish_starter<<endl; exit(1);}
   echoinput<<"  finish reading starter.ss"<<endl<<endl;
 END_CALCS

  //  end reading  from Starter file

  number pi
  !!  pi=3.14159265358979;

  number neglog19
  !!  neglog19 = -log(19.);

  number NilNumbers           //  used as the minimum for posfun and similar checks
//  !! NilNumbers = 0.0000001;
  !! NilNumbers = 0.000;

//  TAG_0002  Set up a dummy datum for use when max phase = 0
  number dummy_datum
  int dummy_phase
  !! dummy_datum=1.;
  !! if(Turn_off_phase<=0) {dummy_phase=0;} else {dummy_phase=-6;}

  int runnumber
  int N_prof_var;
  int prof_var_cnt

 LOCAL_CALCS
   //  TAG_0003   Read runnumber.ss
   ifstream fin1("runnumber.SS", ios::in);
    if (fin1)
    {
      fin1>>runnumber;
      runnumber++;
      fin1.close();
    }
    else
    {
      runnumber=1;
    }
    ofstream fin2("runnumber.SS", ios::out);
    fin2 << runnumber;
    fin2.close();

   //  TAG_0004   Read Profile values file
   ifstream fin3("profilevalues.SS", ios::in);
   if (fin3) {fin3>>N_prof_var;}  else {N_prof_var=0;}
   fin3.close();
   if(N_prof_var>0)  {ad_comm::change_datafile_name("profilevalues.SS");}

 END_CALCS
   init_vector prof_var(1,runnumber*N_prof_var);


//****************************************************************
//  ProgLabel_1000  READ DATA FILE

 LOCAL_CALCS
  ad_comm::change_datafile_name(datfilename);
  cout<<" reading from data file"<<endl;
  ifstream Data_Stream(datfilename);   //  even if the global_datafile name is used, there still is a different logical device created
  k=1;
  N_DC=0;
  while(k!=0)
  {
    Data_Stream >>  readline;          // reads the line from input stream
    if(length(readline)>2)
    {
      checkchar=readline(1);
      k=strcmp(checkchar,"#");
      checkchar=readline(1,2);
      j=strcmp(checkchar,"#C");
      if(j==0) {N_DC++; Data_Comments+=readline;}
    }
  }
 END_CALCS

//MODEL DIMENSIONS
  init_int styr  //start year of the model
 !!echoinput<<styr<<" start year "<<endl;

  init_int endyr // end year of the model
 !!echoinput<<endyr<<" end year "<<endl;

  init_int nseas  //  number of seasons
 !!echoinput<<nseas<<" N seasons "<<endl;

  init_vector seasdur(1,nseas) //  number of months in each season
 !!echoinput<<seasdur<<" months/seas "<<endl;

  int TimeMax
//  int TimeMax_Fore
  int TimeMax_Fore_std
  int YrMax;

  int eq_yr;
  int bio_yr;
  number sumseas;

//  ProgLabel_1002  Set up seasons
  vector seasdur2(1,nseas)
 LOCAL_CALCS
   cout<<" Read DATA File "<<endl;
  sumseas=sum(seasdur);
  if(sumseas>=11.9)
    {seasdur /=sumseas;}
  else
    {seasdur /=12.;}
  seasdur2 = seasdur*0.5;   // half a season
  TimeMax = styr+(endyr-styr)*nseas+nseas-1;
  retro_yr=endyr+retro_yr;
 END_CALCS
 !!echoinput<<seasdur<<" processed season duration "<<endl;

   init_int spawn_seas    //  spawning occurs at beginning of this season
 !!echoinput<<spawn_seas<<" spawn_seas "<<endl;

//  ProgLabel_1004  Define fleets and surveys
  init_int Nfleet // number of fleets (each one with a different selectivity function)
 !!echoinput<<Nfleet<<" Nfleet "<<endl;

  init_int Nsurvey
  !!echoinput<<Nsurvey<<" Nsurvey "<<endl;

 int      Ntypes
  !! Ntypes=Nfleet+Nsurvey;
  init_int pop   // number of areas (populations)
  !!echoinput<<pop<<" N_areas "<<endl;

  imatrix pfleetname(1,Ntypes,1,2)
  init_adstring fleetnameread;

 LOCAL_CALCS
  if(pop>1 && F_reporting==3)
  {N_warn++; warning<<" F-reporting=3 (sum of full Fs) not advised in multiple area models "<<endl;}
  for(f=1;f<=Ntypes;f++) {pfleetname(f,1)=1; pfleetname(f,2)=1;}    // set whole array to equal 1 in case not enough names are read
  f=1;
  for(i=1;i<=strlen(fleetnameread);i++)
  if(adstring(fleetnameread(i))==adstring("%"))
   {pfleetname(f,2)=i-1; f+=1;  pfleetname(f,1)=i+1;}
  pfleetname(Ntypes,2)=strlen(fleetnameread);
  for(f=1;f<=Ntypes;f++)
  {
    fleetname+=fleetnameread(pfleetname(f,1),pfleetname(f,2))+CRLF(1);
  }
  echoinput<<fleetname<<endl;
 END_CALCS

  init_vector surveytime(1,Ntypes)   // fraction of season (not year) in which survey occurs
  !!echoinput<<surveytime<<" surveytime(fishery+surveys) "<<endl;

  init_ivector fleet_area(1,Ntypes)    // areas in which each fleet/survey operates
  !!echoinput<<fleet_area<<" fleet_area(fishery+surveys) "<<endl;

  init_vector catchunits(1,Nfleet)  // 1=biomass; 2=numbers
  !!echoinput<<catchunits<<" catchunits "<<endl;

  init_vector catch_se_rd(1,Nfleet)  // units are se of log(catch); SS2 default = 0.01
  !!echoinput<<catch_se_rd<<" catch_se "<<endl;

  matrix catch_se(styr-1,TimeMax,1,Nfleet);

//  ProgLabel_1006  define ages and years
  init_int    gender  //  number of sexes in the model
  !!echoinput<<gender<<" N genders "<<endl;

  init_int    nages // Number of ages
  !!echoinput<<nages<<" nages "<<endl;

  ivector     age_vector(0,nages)
  vector      r_ages(0,nages)
  ivector     years(styr,endyr) // vector of the years of the model

 LOCAL_CALCS
  for (a=0;a<=nages;a++) age_vector(a) = a; //age vector
  for (a=0;a<=nages;a++) r_ages(a) = double(a); //age vector
  for (y=styr;y<=endyr;y++) years(y)=y;     //year vector
 END_CALCS


//  ProgLabel_1010  Read CATCH amount by fleet
  init_vector obs_equ_catch(1,Nfleet)    //  initial, equilibrium catch.  Annual.
  !!echoinput<<obs_equ_catch<<" obs_equ_catch "<<endl;

  init_int N_ReadCatch;
  !!echoinput<<N_ReadCatch<<" N_ReadCatch "<<endl;

  init_matrix catch_bioT(1,N_ReadCatch,1,Nfleet+2)
  !!echoinput<<" catch as read "<<endl<<catch_bioT<<endl;

  matrix catch_ret_obs(1,Nfleet,styr-nseas,TimeMax+nseas)
  !! k=Nfleet*(TimeMax-styr+1);
  ivector have_catch(1,k);
  3darray catch_seas_area(styr,TimeMax,1,pop,0,Nfleet)
  matrix totcatch_byarea(styr,TimeMax,1,pop)
  vector totcat(styr-1,endyr)
  int first_catch_yr

 LOCAL_CALCS
    catch_ret_obs.initialize();
    t=styr-nseas;
    for(f=1;f<=Nfleet;f++)
      {catch_ret_obs(f,t) = obs_equ_catch(f);}    //  put all init equil catch in first period
  for(k=1;k<=N_ReadCatch;k++)
  {
    y=catch_bioT(k,Nfleet+1); s=catch_bioT(k,Nfleet+2);
    if(y>=styr && y<=endyr)
    {
      if(s>nseas) s=nseas;   // allows for collapsing multiple season catch data down into fewer seasons
                             //  typically to collapse to annual because accumulation will all be in the index "nseas"
      t=styr+(y-styr)*nseas+s-1;
      for(f=1;f<=Nfleet;f++) catch_ret_obs(f,t) += catch_bioT(k,f);
    }
  }
  echoinput<<" processed catch "<<endl<<trans(catch_ret_obs)<<endl;


  for(t=styr-1;t<=TimeMax;t++) {catch_se(t)=catch_se_rd;}

//  calc total catch by year so can calculate the first year with catch and to omit zero catch years from sdreport
  totcat.initialize();
  catch_seas_area.initialize();
  totcatch_byarea.initialize();
  totcat(styr-1)=sum(obs_equ_catch);
  first_catch_yr=0;
  if(totcat(styr-1)>0.0) first_catch_yr=styr-1;
  for(y=styr; y<=endyr; y++)
  {
    for(s=1;s<=nseas;s++)
    {
      t=styr+(y-styr)*nseas+s-1;
      for(p=1;p<=pop;p++)
      for(f=1;f<=Nfleet;f++)
      if(fleet_area(f)==p && catch_ret_obs(f,t) > 0.0)
      {
        totcat(y) += catch_ret_obs(f,t);
        catch_seas_area(t,p,f)=1;
        catch_seas_area(t,p,0)=1;
        totcatch_byarea(t,p)+=catch_ret_obs(f,t);
      }
    }
    if(totcat(y)>0.0 && first_catch_yr==0) first_catch_yr=y;
  }

 END_CALCS


  matrix yr_cr2(1,Ntypes,styr,TimeMax)    // reverse pointers to data occurrence
  matrix yr_disc2(1,Ntypes,styr,TimeMax)
  3darray yr_mnwt2(1,Ntypes,styr,TimeMax,0,2)  // last dimension here is for total, discard, retain
  3darray yr_l2(1,2,1,Ntypes,styr,TimeMax)
  3darray yr_a2(1,2,1,Ntypes,styr,TimeMax)
  3darray yr_ms2(1,2,1,Ntypes,styr,TimeMax)
  matrix have_data(1,Ntypes,styr,TimeMax)
  !! have_data.initialize();


//  ProgLabel_1020 Catch rate or Survey index
   init_int nobs_rd
   int nobs
  !!echoinput<<nobs_rd<<" nobs_survey "<<endl;
   init_matrix indexdata(1,nobs_rd,1,5)
  !!if(nobs_rd>0) echoinput<<" indexdata "<<endl<<indexdata<<endl;
   ivector nyr_cr(1,Ntypes)

 LOCAL_CALCS
    nyr_cr=0;
    if(nobs_rd>0)
    for(i=1;i<=nobs_rd;i++)
    {
    y=indexdata(i,1);
    f=indexdata(i,3);
    if(y>=styr && y<=retro_yr) nyr_cr(f)++;
    }
    nobs=sum(nyr_cr);
 END_CALCS

  imatrix yr_cr(1,Ntypes,1,nyr_cr)
  imatrix yr_cr_y(1,Ntypes,1,nyr_cr)
  matrix  obs_cr(1,Ntypes,1,nyr_cr)
  matrix  Ln_obs_cr(1,Ntypes,1,nyr_cr)
  matrix  cv_cr(1,Ntypes,1,nyr_cr)
  matrix vul_bio(1,Ntypes,1,nyr_cr);        // Vulnerable biomass
// arrays for Super-years
  ivector N_supyr_cr(1,Ntypes)      // N super_yrs per obs
  imatrix supyr_cr1(1,Ntypes,1,20)  //  max of 20 superyear obs are allowed per type
  imatrix supyr_cr2(1,Ntypes,1,20)  //  max of 20 superyear obs are allowed per type

 LOCAL_CALCS
//  ProgLabel_1022  process survey observations
    N_supyr_cr=0;
    nyr_cr=0;
    if(nobs>0)  // proceed if any data in yr range
    {
      for(i=1;i<=nobs_rd;i++)  // loop all, including those out of yr range
      {
        y=indexdata(i,1);
        if(y>=styr && y<=retro_yr)
        {
          s=indexdata(i,2);
          t=styr+(y-styr)*nseas+s-1;
          f=indexdata(i,3);
          nyr_cr(f)+=1;
          j=nyr_cr(f);
          yr_cr(f,j)=t;
          yr_cr_y(f,j)=y;

          obs_cr(f,j)=indexdata(i,4);
          if(obs_cr(f,j)>0) Ln_obs_cr(f,j)=log(obs_cr(f,j));
          cv_cr(f,j)=indexdata(i,5);
          //  create super_year indexes
          if(cv_cr(f,j)==-9999)  // start a super-year  ALL observations must be continguous in the file
           {N_supyr_cr(f)+=1; supyr_cr1(f,N_supyr_cr(f))=j;}
          if(cv_cr(f,j)==-9998)  // end a super-year
           {supyr_cr2(f,N_supyr_cr(f))=j;}
        }
      }
      echoinput<<" processed survey data "<<endl<<obs_cr<<endl;
    }

    cout<<" successful read of index data; N= "<<nobs << endl;
 END_CALCS

//  ProgLabel_1030  read Discard data
   init_int disc_type
  !!echoinput<<disc_type<<" disc_type "<<endl;
   init_int nobs_disc_rd
   int nobs_disc
  !!echoinput<<nobs_disc_rd<<" nobs_disc "<<endl;
   init_matrix discdata(1,nobs_disc_rd,1,5)
  !! if(nobs_disc_rd>0) echoinput<<" discarddata "<<endl<<discdata<<endl;
   ivector nyr_disc(1,Ntypes)

 LOCAL_CALCS
    nyr_disc=0;
    if(nobs_disc_rd>0)
      {
      for(i=1;i<=nobs_disc_rd;i++)
        {
         y=discdata(i,1);
         if(y>=styr && y<=retro_yr)
         {
          f=discdata(i,3);
          nyr_disc(f)++;
         }
        }
      }
    nobs_disc=sum(nyr_disc);
 END_CALCS

  imatrix yr_disc(1,Ntypes,1,nyr_disc)
  imatrix yr_disc_y(1,Ntypes,1,nyr_disc)
  matrix  obs_disc(1,Ntypes,1,nyr_disc)
  matrix  cv_disc(1,Ntypes,1,nyr_disc)
  matrix  sd_disc(1,Ntypes,1,nyr_disc)
// arrays for Super-years
  ivector N_supyr_disc(1,Ntypes)      // N super_yrs per obs
  imatrix supyr_disc1(1,Ntypes,1,20)  //  max of 20 superyear obs are allowed per type
  imatrix supyr_disc2(1,Ntypes,1,20)  //  max of 20 superyear obs are allowed per type

 LOCAL_CALCS
//  ProgLabel_1032  create discard super years
    N_supyr_disc=0;
    if(nobs_disc>0)
      {
      nyr_disc=0;                        // redo the counter to provide pointer for below
      for(i=1;i<=nobs_disc_rd;i++)
        {
        y=discdata(i,1);
         if(y>=styr && y<=retro_yr)
         {
          s=discdata(i,2);
          t=styr+(y-styr)*nseas+s-1;
          f=discdata(i,3);
          nyr_disc(f)++;
          j=nyr_disc(f);
          yr_disc(f,j)=t;
          yr_disc_y(f,j)=y;
          obs_disc(f,j)=discdata(i,4);
          if(catch_ret_obs(f,t)<=0.0)
          {
            N_warn++; warning<<" discard observation but no corresponding catch, yr, seas, fleet "<<y<<" "<<s<<" "<<f<<endl;
            obs_disc(f,j)=-fabs(obs_disc(f,j))-0.00001;
          }
        cv_disc(f,j)=discdata(i,5);
//        sd_disc(f,j)=cv_disc(f,j)*obs_disc(f,j);

                                   //  create super_year indexes
        if(cv_disc(f,j)==-9999)  // start a super-year  ALL observations must be continguous in the file
          {N_supyr_disc(f)+=1; supyr_disc1(f,N_supyr_disc(f))=j;}
        if(cv_disc(f,j)==-9998)  // end a super-year
          {supyr_disc2(f,N_supyr_disc(f))=j;}
        }
      }
      }
    cout<<" successful read of discard data, N= "<< nobs_disc << endl;
 END_CALCS


//  ProgLabel_1040  read Mean Body Weight data
   init_int nobs_mnwt_rd
   int nobs_mnwt
  !!echoinput<<nobs_mnwt_rd<<" nobs_mnwt "<<endl;
   init_matrix mnwtdata1(1,nobs_mnwt_rd,1,6)
 LOCAL_CALCS
  nobs_mnwt=0;
  if(nobs_mnwt_rd>0) echoinput<<" meanbodywt_data "<<endl<<mnwtdata1<<endl;
  for(i=1;i<=nobs_mnwt_rd;i++)
  {
    y=mnwtdata1(i,1);
    if(y>=styr && y<=retro_yr) nobs_mnwt++;
  }
 END_CALCS
  matrix mnwtdata(1,9,1,nobs_mnwt)
//    yr, seas, type, mkt, obs, CV

 LOCAL_CALCS
  yr_mnwt2=0;
  if(nobs_mnwt>0)
  j=0;
  for(i=1;i<=nobs_mnwt_rd;i++)
  {
    y=mnwtdata1(i,1);
    if(y>=styr && y<=retro_yr)
    {
      j++;
      s=mnwtdata1(i,2); t=styr+(y-styr)*nseas+s-1;
      f=mnwtdata1(i,3); z=mnwtdata1(i,4);  // z is partition (0, 1, 2)
      yr_mnwt2(f,t,z)=j;
      have_data(f,t)=1;
      for(k=1;k<=6;k++) mnwtdata(k,j)=mnwtdata1(i,k);
    }
  }
  cout<<" successful read of mean-body-wt data, N= "<< nobs_mnwt <<endl;
 END_CALCS


// **************************************
//  ProgLabel_1050  Length bin set-up
  number binwidth2  //  width of length bins in population
  number minLread  // input minimum size in population; this is used as the mean size at age 0.00
  number maxLread  //  input maximum size to be considered; should be divisible by binwidth2
  int nlen_bin2  //number of length bins in length comp data doubled for males
  int nlen_binP   //number of length bins in length comp data +1 as needed
  number minL               // minL and maxL store ends of the sizevector and are used as bounds later
  number minL_m  // mean size in first pop bin
  number maxL  // set to the midsize of last population bin for selex calc
  int nlength  // N pop lenbins
  int nlength1  //  +1 as needed
  int nlength2  // doubled for males
  number startbin  // population length bin that matches first data length bin

  init_int LenBin_option  // 1=set to data bins; 2 generate uniform; 3 = read custom
  !!echoinput<<LenBin_option<<" LenBin_option "<<endl;
 LOCAL_CALCS
   if(LenBin_option==1)
   {k=0;}
   else if(LenBin_option==2)
   {k=3;}
   else if(LenBin_option==3)
   {k=1;}
   else
   {N_warn++; warning<<" LenBin_option must be 1, 2 or 3"<<LenBin_option<<endl;}
 END_CALCS

  init_vector PopBin_Read(1,k);
  !!if( k>0) echoinput<<PopBin_Read<<" input for setup of pop length bins "<<endl;
 LOCAL_CALCS
   nlength=0;  // later will be read or calculated
   if(LenBin_option==2)
   {binwidth2=PopBin_Read(1); minLread=PopBin_Read(2); maxLread=PopBin_Read(3);}
   else if(LenBin_option==3)
   {nlength=PopBin_Read(1);}  // number of bins to read
 END_CALCS
  init_vector len_bins_rd(1,nlength)
  !!if(nlength>0) echoinput<<len_bins_rd<<" pop length bins as read "<<endl;

  init_number min_tail  //min_proportion_for_compressing_tails_of_observed_composition
  !!echoinput<<min_tail<<" min tail for comps "<<endl;
  init_number min_comp  //  small value added to each composition bins
  !!echoinput<<min_comp<<" value added to comps "<<endl;
  init_int CombGender_l  //  combine genders through this length bin
  !!echoinput<<CombGender_l<<" CombGender_lengths "<<endl;
  init_int nlen_bin //number of length bins in length comp data
  !!echoinput<<nlen_bin<<" nlen_bin_for_data "<<endl;

 !! nlen_binP=nlen_bin+1;
 !! nlen_bin2=gender*nlen_bin;

  init_vector len_bins_dat(1,nlen_bin) // length bin lower boundaries
  !!echoinput<<" len_bins_dat "<<endl<<len_bins_dat<<endl;
  vector len_bins_dat2(1,nlen_bin2)  //; doubled for males; for output only
  vector len_bins_dat_m(1,nlen_bin)  //; midbin; for output only

 LOCAL_CALCS
   if(LenBin_option==1)
   {
     nlength = nlen_bin;  // set N pop bins same as data bins
   }
   else if(LenBin_option==2)
   {
     nlength = (maxLread-minLread)/binwidth2+1;   // number of population length bins
   }
   else if(LenBin_option==3)
   {
    // nlength was read
   }
   nlength1 = nlength+1;          //  +1 when needed
   nlength2 = gender*nlength;    // doubled for males
 END_CALCS

  vector len_bins(1,nlength)  //vector with lower edge of population length bins
  vector len_bins2(1,nlength2)  //vector with lower edge of population length bins
  vector binwidth(1,nlength2)  //ve
  vector len_bins_m(1,nlength)  //vector with mean size in bin
  vector len_bins_m2(1,nlength2)  //vector with all length bins; doubled for males
  vector len_bins_sq(1,nlength2)  //vector with all length bins; doubled for males
  vector male_offset(1,nlength2)  // used to calculate retained@length as population quantity

 LOCAL_CALCS
  male_offset.initialize();  //  initialize
   if(LenBin_option==1)
   {len_bins=len_bins_dat;}
   else if(LenBin_option==2)
   {
     len_bins(1)=minLread;
     for (z=2;z<=nlength;z++)  {len_bins(z)=len_bins(z-1)+binwidth2;}
   }
   else
   {len_bins=len_bins_rd;}

  if(len_bins(1)==0.0) len_bins(1)=0.001;
  echoinput<<endl<<"Processed Population length bin info "<<endl;
  for (z=1;z<=nlength;z++)
  {
    len_bins2(z)=len_bins(z);
    if(z<nlength)
    {
      len_bins_m(z) = (len_bins(z+1)+len_bins(z))/2.;
      binwidth(z)=len_bins(z+1)-len_bins(z);
    }
    else
    {
      len_bins_m(z) = len_bins(z)+binwidth(z-1)/2.;
      binwidth(z)=binwidth(z-1);
    }

    len_bins_m2(z) = len_bins_m(z);     // for use in calc mean size at binned age
    len_bins_sq(z) = len_bins_m2(z)*len_bins_m2(z);        //  for use in calc std dev of size at binned age
    if(gender==2)
    {
      len_bins2(z+nlength)=len_bins(z);
      male_offset(z+nlength)=1.;
      binwidth(z+nlength)=binwidth(z);
      len_bins_m2(z+nlength)=len_bins_m2(z);
      len_bins_sq(z+nlength)=len_bins_sq(z);
    }
    echoinput<<z<<" "<<len_bins(z)<<" "<<len_bins_m(z)<<" "<<binwidth(z)<<endl;
  }
  maxL=len_bins_m(nlength);
  minL=len_bins(1);
  minL_m=len_bins_m(1);
  if(LenBin_option!=2) binwidth2=binwidth(nlength/2);  // set a reasonable value in case LenBin_option !=2

  startbin=1;
  while(len_bins(startbin)<len_bins_dat(1))
  {startbin++;}

  if(gender==1)
    {
    len_bins_dat2=len_bins_dat;        //  check this; it may fill it twice if gender ==2 anyway
    }
  else
    {
    for (z=1;z<=nlen_bin;z++)
      {
      len_bins_dat2(z) = len_bins_dat(z);
      len_bins_dat2(z+nlen_bin)=len_bins_dat(z);
      if(z<nlen_bin)
      {
        len_bins_dat_m(z)=0.5*(len_bins_dat(z)+len_bins_dat(z+1));
      }
      else
      {
        len_bins_dat_m(z)=len_bins_dat_m(z-1)+ (len_bins_dat(z)-len_bins_dat(z-1));
      }
      }
    }
 END_CALCS


//  ProgLabel_1054  create conversion of pop length bins to data length bins
  matrix make_len_bin(1,nlen_bin2,1,nlength2);

 LOCAL_CALCS

//  make_len_bin.initialize();
//  for(j=1;j<=nlen_bin;j++)
//  {
//    k=0;
//    for(z=1;z<=nlength;z++)
//    {
//      if(len_bins(z)==len_bins_dat(j))   //  this is erroneous   Jan 14, 2009
//      {
//        k=1;
//        make_len_bin(j,z)=1.;
//        if(gender==2) make_len_bin(j+nlen_bin,z+nlength) = 1.;
//      }
//    }
//    if(k==0)
//    {N_warn++;
//      cout<<" fatal error:  see warning.sso "<<endl;
//      warning<<" No pop len bin corresponds to data length bin: "<<j<<" len: "<<len_bins_dat(j)<<endl; exit(1);}
//  }

 END_CALCS

  int ibin;
  int ibinsave;
  int fini;
  number topbin;
  number botbin;

 LOCAL_CALCS
  make_len_bin.initialize();
  ibin=0;
  topbin=0.;
  botbin=0.;
  for(z=1;z<=nlength;z++)
  {
    if(ibin==nlen_bin)
    {  //checkup<<" got to last ibin, so put rest of popbins here"<<endl;
      make_len_bin(ibin,z)=1.;
    }
    else
    {
      if(len_bins(z)>=topbin) {ibin++; }  //checkup<<" incr ibin ";

//      checkup<<z<<" "<<ibin<<" "<<len_bins(z)<<" "<<len_bins_dat(ibin);
      if(ibin>1)  {botbin=len_bins_dat(ibin);}
      if(ibin<nlen_bin) {topbin=len_bins_dat(ibin+1);} else {topbin=99999.;}

      if(ibin==nlen_bin)  // checkup<<" got to last ibin, so put rest of popbins here"<<endl;
      {make_len_bin(ibin,z)=1.;}
      else if(len_bins(z)>=botbin && len_bins(z+1)<=topbin )  //checkup<<" pop inside dat, put here"<<endl;
      {make_len_bin(ibin,z)=1.;}
      else       // checkup<<" overlap"<<endl;
      {
      make_len_bin(ibin+1,z)=(len_bins(z+1)-topbin)/(len_bins(z+1)-len_bins(z));
      if(ibin!=1) make_len_bin(ibin,z)=1.-make_len_bin(ibin+1,z);
      }
    }
  }
  if(gender==2)
  {
    for (i=1;i<=nlen_bin;i++)
    for(j=1;j<=nlength;j++)
    make_len_bin(i+nlen_bin,j+nlength)=make_len_bin(i,j);
  }
   if(docheckup==1)
   {
    checkup<<"make_len_bin "<<len_bins<<endl;
    for(ibin=1;ibin<=nlen_bin;ibin++) checkup<<len_bins_dat(ibin)<<make_len_bin(ibin)(1,nlength)<<endl;
   }
 END_CALCS


//  ProgLabel_1060 read Length frequencies
   init_int nobsl_rd
   int nobsl
   !!echoinput<<nobsl_rd<<" N length comp obs "<<endl;
   init_matrix lendata(1,nobsl_rd,1,6+nlen_bin2)
   !!if(nobsl_rd>0) echoinput<<" first lencomp obs "<<endl<<lendata(1)<<endl<<" last obs"<<endl<<lendata(nobsl_rd)<<endl;;

  ivector nyr_l(1,Ntypes)
   number temp;

 LOCAL_CALCS
    nyr_l=0;                       //  number of observations from each fleet/survey
    if(nobsl_rd>0)
    for(i=1;i<=nobsl_rd;i++)
    {
      y=lendata(i,1);
      if(y>=styr && y<=retro_yr)
      {
      f=lendata(i,3);
      nyr_l(f)++;
      }
    }
    nobsl=sum(nyr_l);
 END_CALCS

  imatrix yr_l(1,Ntypes,1,nyr_l)
  imatrix yr_l_y(1,Ntypes,1,nyr_l)
  3darray obs_l(1,Ntypes,1,nyr_l,1,nlen_bin2)
  matrix  nsamp_l(1,Ntypes,1,nyr_l)
  matrix  nsamp_l_read(1,Ntypes,1,nyr_l)
  imatrix  gen_l(1,Ntypes,1,nyr_l)
  imatrix  mkt_l(1,Ntypes,1,nyr_l)
  3darray header_l(1,Ntypes,1,nyr_l,1,3)   //
  3darray tails_l(1,Ntypes,1,nyr_l,1,4)   // min-max bin for females; min-max bin for males
  ivector tails_w(1,4)

// arrays for Super-years
  ivector N_supyr_l(1,Ntypes)      // N super_yrs per obs
  imatrix supyr_l1(1,Ntypes,1,20)  //  max of 20 superyear obs are allowed per type
  imatrix supyr_l2(1,Ntypes,1,20)  //  max of 20 superyear obs are allowed per type
  int floop
  int tloop

//  ProgLabel_1052  pre-process length comps, compress tails, etc.
 LOCAL_CALCS
  N_supyr_l=0;
  nyr_l=0;
  if(nobsl>0)
    {
    for(floop=1;floop<=Ntypes;floop++)
    for(tloop=styr;tloop<=(styr+(endyr+1-styr)*nseas);tloop++)
    for(i=1;i<=nobsl_rd;i++)
      {
       y=lendata(i,1);
       if(y>=styr && y<=retro_yr)
       {
       s=lendata(i,2);
       t=styr+(y-styr)*nseas+s-1;
       f=lendata(i,3);
       if(f==floop && t==tloop)
         {
       nyr_l(f)+=1;
       j=nyr_l(f);

       header_l(f,j,1) = y;
       header_l(f,j,2) = s;
       header_l(f,j,3) = f;
       yr_l_y(f,j)=y;                   // year
       yr_l(f,j)=t;                     // sequential time = year+season
       gen_l(f,j)=lendata(i,4);         // gender 0=combined, 1=female, 2=male, 3=both
       mkt_l(f,j)=lendata(i,5);         // partition: 0=all, 1=discard, 2=retained
       nsamp_l_read(f,j)=lendata(i,6);  // assigned sample size for observation
       nsamp_l(f,j)=nsamp_l_read(f,j);
       for(z=1;z<=nlen_bin2;z++)   // get the composition vector
        {obs_l(f,j,z)=lendata(i,6+z);}

       if(sum(obs_l(f,j))<=0.0) {N_warn++; warning<<" zero fish in size comp (fleet, year) "<<f<<" "<<y<<endl; cout<<" exit - see warning "<<endl;  exit(1);}
       tails_l(f,j,1)=1;
       tails_l(f,j,2)=nlen_bin;
       tails_l(f,j,3)=nlen_binP;
       tails_l(f,j,4)=nlen_bin2;
       if(gen_l(f,j)==3 && CombGender_l>0)
       {
        for(z=1;z<=CombGender_l;z++)
        {
          obs_l(f,j,z)+=obs_l(f,j,z+nlen_bin);  obs_l(f,j,z+nlen_bin)=0.0;
        }
        tails_l(f,j,3)=nlen_binP+CombGender_l;
      }
       if(gen_l(f,j)==2) obs_l(f,j)(1,nlen_bin) = 0.;   //  zero out females for male-only obs
       if(gen_l(f,j)<=1 && gender==2) obs_l(f,j)(nlen_binP,nlen_bin2) = 0.;   //  zero out males for female-only or combined gender obs
       obs_l(f,j) /= sum(obs_l(f,j));                  // make sum to 1.00

       if(gen_l(f,j)!=2)                      // do females, unless Male-only observation
         {
         k=0;
         temp=sum(obs_l(f,j)(1,nlen_bin));
         for(z=1;z<=nlen_bin;z++)
         if(obs_l(f,j,z)>0.)
           {k++;}
         if(temp>0.0 && k>1)     // only compress tail if obs exist for this gender and there is more than 1 bin with data
           {
           k=0;
           for(z=1;z<=nlen_bin-1;z++)             // compress Female lower tail until exceeds min_tail
             {
             if(obs_l(f,j,z)<=min_tail && k==0)
               {
               obs_l(f,j,z+1)+=obs_l(f,j,z);
               obs_l(f,j,z)=0.00;
               tails_l(f,j,1)=z+1;
               }
             else
               {k=1;}
             }

           k=0;
           for(z=nlen_bin;z>=tails_l(f,j,1);z--)  // compress Female upper tail until exceeds min_tail
             {
             if(obs_l(f,j,z)<=min_tail && k==0)
               {
               obs_l(f,j,z-1)+=obs_l(f,j,z);
               obs_l(f,j,z)=0.00;
               tails_l(f,j,2)=z-1;
               }
             else
               {k=1;}
             }
           }
         obs_l(f,j)(tails_l(f,j,1),tails_l(f,j,2)) += min_comp;    // add min_comp to bins in range
         }


       if(gen_l(f,j)>=2) // process males
         {
         k=0;
         temp=sum(obs_l(f,j)(nlen_binP,nlen_bin2));
         for(z=nlen_binP;z<=nlen_bin2;z++)
         if(obs_l(f,j,z)>0.)
           {k++;}
         if(temp>0.0 && k>1)     // only compress tail if obs exist for this gender and there is more than 1 bin with data
           {

           k=0;
           k1=tails_l(f,j,3);
           for(z=k1;z<=nlen_bin2-1;z++)
             {
             if(obs_l(f,j,z)<=min_tail && k==0)
               {
               obs_l(f,j,z+1)+=obs_l(f,j,z);
               obs_l(f,j,z)=0.00;
               tails_l(f,j,3)=z+1;
               }
             else
               {k=1;}
             }

           k=0;
           for(z=nlen_bin2;z>=tails_l(f,j,3);z--)  // compress Male upper tail until exceeds min_tail
             {
             if(obs_l(f,j,z)<=min_tail && k==0)
               {
               obs_l(f,j,z-1)+=obs_l(f,j,z);
               obs_l(f,j,z)=0.00;
               tails_l(f,j,4)=z-1;
               }
             else
               {k=1;}
             }
           }
           obs_l(f,j)(tails_l(f,j,3),tails_l(f,j,4)) += min_comp;  // add min_comp to bins in range
         }   // end doing males
       obs_l(f,j) /= sum(obs_l(f,j));                  // make sum to 1.00 again after adding min_comp
//  ProgLabel_1056  create super year indexes for length compositions
       if(nsamp_l(f,j)==-9999)  // start a super-year  ALL observations must be continguous in the file
         {N_supyr_l(f)+=1; supyr_l1(f,N_supyr_l(f))=j;}
       if(nsamp_l(f,j)==-9998)  // end a super-year
         {supyr_l2(f,N_supyr_l(f))=j;}
       }
       }
      }
     }
    cout<<"  successful read of length data"<<endl;
 END_CALCS


//  ProgLabel_1060  Read Age frequencies
  init_int n_abins // age classes for data
   !!echoinput<<n_abins<<" N age bins "<<endl;
  int n_abins1;
  int n_abins2;
 LOCAL_CALCS
  n_abins1=n_abins+1;
  n_abins2=gender*n_abins;
 END_CALCS

   init_vector age_bins1(1,n_abins) // age classes for data
  !!echoinput << age_bins1<< " agebins "  << endl;
  init_int N_ageerr   // number of ageing error matrices to be calculated
   !!echoinput<<N_ageerr<<" N age error defs "<<endl;
  init_3darray age_err(1,N_ageerr,1,2,0,nages) // ageing imprecision as stddev for each age
  !!if(N_ageerr>0) echoinput <<" ageerr " << endl<<age_err << endl;

  3darray age_age(1,N_ageerr,1,n_abins2,0,gender*nages+gender-1)
  vector age_bins(1,n_abins2) // age classes for data

  init_int nobsa_rd
  int nobsa
  !!echoinput << nobsa_rd<< " N ageobs"  << endl;

  init_int Lbin_method  //#_Lbin_method: 1=poplenbins; 2=datalenbins; 3=lengths
  !!echoinput << Lbin_method<< " Lbin method for defined size ranges "  << endl;

  init_int CombGender_a  //  combine genders through this age bin
  !!echoinput << CombGender_a<< " merge males&females through this bin number "  << endl;

 LOCAL_CALCS
  if(nobsa_rd>0 && N_ageerr==0)
  {N_warn++; cout<<" exit - see warning "<<endl;
  warning<<" must define ageerror vectors because age data exist"<<endl; exit(1);}
 END_CALCS
  init_matrix agedata(1,nobsa_rd,1,9+n_abins2)
   !!if(nobsa_rd>0) echoinput<<" first agecomp obs "<<endl<<agedata(1)<<endl<<" last obs"<<endl<<agedata(nobsa_rd)<<endl;;
  ivector nyr_a(1,Ntypes)
  number age

 LOCAL_CALCS
  for (b=1;b<=n_abins;b++)
  {
   age_bins(b) = age_bins1(b);
   if(gender==2) age_bins(b+n_abins)=age_bins1(b);
  }
  nyr_a=0;
  for(i=1;i<=nobsa_rd;i++)
  {
    y=agedata(i,1);
    if(y>=styr && y<=endyr)
    {
     f=agedata(i,3);
     nyr_a(f)++;
    }
  }
  nobsa=sum(nyr_a);

  for(f=1;f<=Ntypes;f++)
      {if(nyr_a(f)==0) nyr_a(f)=1;}
 END_CALCS

  imatrix yr_a(1,Ntypes,1,nyr_a)
  imatrix yr_a_y(1,Ntypes,1,nyr_a)
  3darray obs_a(1,Ntypes,1,nyr_a,1,gender*n_abins)
  matrix  nsamp_a(1,Ntypes,1,nyr_a)
  matrix  nsamp_a_read(1,Ntypes,1,nyr_a)
  imatrix  ageerr_type_a(1,Ntypes,1,nyr_a)
  imatrix  gen_a(1,Ntypes,1,nyr_a)
  imatrix  mkt_a(1,Ntypes,1,nyr_a)
  3darray  Lbin_filter(1,Ntypes,1,nyr_a,1,nlength2)
  imatrix  use_Lbin_filter(1,Ntypes,1,nyr_a)
  imatrix  Lbin_lo(1,Ntypes,1,nyr_a)
  imatrix  Lbin_hi(1,Ntypes,1,nyr_a)
  3darray tails_a(1,Ntypes,1,nyr_a,1,4)   // min-max bin for females; min-max bin for males
  3darray header_a(1,Ntypes,1,nyr_a,1,9)

// arrays for Super-years
  ivector N_supyr_a(1,Ntypes)      // N super_yrs per obs
  imatrix supyr_a1(1,Ntypes,1,20)  //  max of 20 superyear obs are allowed per type
  imatrix supyr_a2(1,Ntypes,1,20)  //  max of 20 superyear obs are allowed per type

//  ProgLabel_1062  pre-process age comps, compress tails, define length bin filters
 LOCAL_CALCS
   Lbin_filter=1.;
   use_Lbin_filter.initialize();     // have to use initialize; imatrix cannot be set to a constant
   N_supyr_a=0;
   nyr_a=0;
   if(nobsa>0)
   {
    for(floop=1;floop<=Ntypes;floop++)
    for(tloop=styr;tloop<=(styr+(endyr+1-styr)*nseas);tloop++)
    for(i=1;i<=nobsa;i++)
    {
     y=agedata(i,1);
     if(y>=styr && y<=retro_yr)
     {
     s=agedata(i,2);
     t=styr+(y-styr)*nseas+s-1;
     f=agedata(i,3);
     if(f==floop && t==tloop)
     {
       nyr_a(f)++;
       j=nyr_a(f);
       header_a(f,j)(1,9)=agedata(i)(1,9);
       yr_a(f,j)=t;
       yr_a_y(f,j)=y;
       gen_a(f,j)=agedata(i,4);
       mkt_a(f,j)=agedata(i,5);
       if(agedata(i,6)==0 || agedata(i,6)>N_ageerr)
       {
          N_warn++; cout<<" exit - see warning "<<endl;
          warning<<" ageerror type must be >0 and <= "<<N_ageerr<<endl; exit(1);
       }
       ageerr_type_a(f,j)=agedata(i,6);

       Lbin_lo(f,j)=agedata(i,7);
       Lbin_hi(f,j)=agedata(i,8);
       switch (Lbin_method)
       {
         case 1:  // values are population length bin numbers
         {
           if(Lbin_lo(f,j)<=0) Lbin_lo(f,j)=1;
           if(Lbin_hi(f,j)<=0 || Lbin_hi(f,j)>nlength) Lbin_hi(f,j)=nlength;
           if(Lbin_lo(f,j)==1 && Lbin_hi(f,j)==nlength) {use_Lbin_filter(f,j)=0;} else {use_Lbin_filter(f,j)=1;}
           break;
         }
         case 2:  // values are data length bin numbers
         {
           if(Lbin_lo(f,j)<=0) Lbin_lo(f,j)=1;
           s=0;
           for(k=1;k<=nlength;k++)
           {
             if( len_bins(k)==len_bins_dat(Lbin_lo(f,j)) ) s=k;
           }
           if(s==0)
           {
             N_warn++; cout<<" exit - see warning "<<endl; warning<<" L_bin_lo mismatch in age comp (fleet, year) "<<f<<" "<<y<<endl;  exit(1);
           }
           Lbin_lo(f,j)=s;

           if(Lbin_hi(f,j)<=0 || Lbin_hi(f,j)>nlen_bin) Lbin_hi(f,j)=nlen_bin;
           s=0;
           for(k=1;k<=nlength;k++)
           {
             if( len_bins(k)==len_bins_dat(Lbin_hi(f,j)) ) s=k;
           }
           if(s==0)
           {N_warn++; cout<<" exit - see warning "<<endl; warning<<" L_bin_hi mismatch in age comp (fleet, year) "<<f<<" "<<y<<endl;  exit(1);}
           Lbin_hi(f,j)=s;
           if(Lbin_lo(f,j)==1 && Lbin_hi(f,j)==nlen_bin) {use_Lbin_filter(f,j)=0;} else {use_Lbin_filter(f,j)=1;}
           break;
         }
         case 3:   // values are lengths
         {
           if(Lbin_lo(f,j)<=0) Lbin_lo(f,j)=len_bins(1);
           s=0;
           for(k=1;k<=nlength;k++)
           {
             if( len_bins(k)==Lbin_lo(f,j) ) s=k;
           }
           if(s==0)
           {N_warn++; cout<<" exit - see warning "<<endl; warning<<" L_bin_lo mismatch in age comp (fleet, year) "<<f<<" "<<y<<endl;  exit(1);}
           Lbin_lo(f,j)=s;

           if(Lbin_hi(f,j)<=0 || Lbin_hi(f,j)>len_bins(nlength)) Lbin_hi(f,j)=len_bins(nlength);
           s=0;
           for(k=1;k<=nlength;k++)
           {
             if( len_bins(k)==Lbin_hi(f,j) ) s=k;
           }
           if(s==0)
           {N_warn++; cout<<" exit - see warning "<<endl; warning<<" L_bin_hi mismatch in age comp (fleet, year) "<<f<<" "<<y<<endl;  exit(1);}
           Lbin_hi(f,j)=s;
           if(Lbin_lo(f,j)==len_bins(1) && Lbin_hi(f,j)==len_bins(nlength)) {use_Lbin_filter(f,j)=0;} else {use_Lbin_filter(f,j)=1;}
           break;
         }
       }
       if(use_Lbin_filter(f,j)==1)
       {                                                   // use Lbin_filter for this obs
         Lbin_filter(f,j)=0;
         Lbin_filter(f,j)(Lbin_lo(f,j),Lbin_hi(f,j)) = 1;
         if(gender==2)
         {
          k=int(Lbin_lo(f,j))+nlength; z=int(Lbin_hi(f,j))+nlength;
          Lbin_filter(f,j)(k,z) = 1.;
         }
       }
       nsamp_a_read(f,j)=agedata(i,9);
       if(y>retro_yr) nsamp_a_read(f,j) = -fabs(nsamp_a_read(f,j));
       nsamp_a(f,j)=nsamp_a_read(f,j);

       for(b=1;b<=gender*n_abins;b++)   // get the composition vector
       {obs_a(f,j,b)=agedata(i,9+b);}

       if(sum(obs_a(f,j))<=0.0)
       {N_warn++; cout<<" exit - see warning "<<endl; warning<<" zero fish in age comp (fleet, year) "<<f<<" "<<y<<endl;  exit(1);}

       if(gen_a(f,j)==2) obs_a(f,j)(1,n_abins) = 0.;   //  zero out females for male-only obs
       if(gen_a(f,j)<=1&&gender==2) obs_a(f,j)(n_abins1,gender*n_abins) = 0.;   //  zero out males for female-only or combined gender obs
       tails_a(f,j,1)=1;
       tails_a(f,j,2)=n_abins;
       tails_a(f,j,3)=1+(gender-1)*n_abins;
       tails_a(f,j,4)=gender*n_abins;
       if(gender==2)
       {
           if(gen_a(f,j)==3 && CombGender_a>0)
           {
            for(z=1;z<=CombGender_a;z++)
            {
              obs_a(f,j,z)+=obs_a(f,j,z+n_abins);  obs_a(f,j,z+n_abins)=0.0;
            }
            tails_a(f,j,3)=n_abins+1+CombGender_a;
           }
       }

       obs_a(f,j) /= sum(obs_a(f,j));

       if(gen_a(f,j)!=2)                     // do females, unless Male-only observation
       {
       k=0;
       temp=sum(obs_a(f,j)(1,n_abins));
       for(z=1;z<=n_abins;z++)
         if(obs_a(f,j,z)>0.)
           {k++;}
       if(temp>0.0 && k>1)     // only compress tail if obs exist for this gender and there is more than 1 bin with data
         {
         k=0;
         for(z=1;z<=n_abins-1;z++)             // compress Female lower tail until exceeds min_tail
           {
           if(obs_a(f,j,z)<=min_tail && k==0)
             {
             obs_a(f,j,z+1)+=obs_a(f,j,z);
             obs_a(f,j,z)=0.00;
             tails_a(f,j,1)=z+1;
             }
           else
             {k=1;}
           }

         k=0;
         for(z=n_abins;z>=tails_a(f,j,1);z--)  // compress Female upper tail until exceeds min_tail
           {
           if(obs_a(f,j,z)<=min_tail && k==0)
             {
             obs_a(f,j,z-1)+=obs_a(f,j,z);
             obs_a(f,j,z)=0.00;
             tails_a(f,j,2)=z-1;
             }
           else
             {k=1;}
           }
         }
       obs_a(f,j)(tails_a(f,j,1),tails_a(f,j,2)) += min_comp;    // add min_comp to bins in range
       }                            // done with females

       if(gen_a(f,j)>=2) // compress Male lower tail until exceeds min_tail
       {
        k=0;
        temp=sum(obs_a(f,j)(n_abins1,n_abins2));
        for(z=n_abins1;z<=n_abins2;z++)
        if(obs_a(f,j,z)>0.)
          {k++;}
        if(temp>0.0 && k>1)     // only compress tail if obs exist for this gender and there is more than 1 bin with data
          {
          k=0;

          for(z=n_abins1;z<=n_abins2-1;z++)
            {
            if(obs_a(f,j,z)<=min_tail && k==0)
              {
              obs_a(f,j,z+1)+=obs_a(f,j,z);
              obs_a(f,j,z)=0.00;
              tails_a(f,j,3)=z+1;
              }
            else
              {k=1;}
            }

          k=0;
          for(z=n_abins2;z>=tails_a(f,j,3);z--)  // compress Male upper tail until exceeds min_tail
            {
            if(obs_a(f,j,z)<=min_tail && k==0)
              {
              obs_a(f,j,z-1)+=obs_a(f,j,z);
              obs_a(f,j,z)=0.00;
              tails_a(f,j,4)=z-1;
              }
            else
              {k=1;}
            }
          }
        obs_a(f,j)(tails_a(f,j,3),tails_a(f,j,4)) += min_comp;  // add min_comp to bins in range
       }

       if(sum(obs_a(f,j))>0.) obs_a(f,j) /= sum(obs_a(f,j));                  // make sum to 1.00 again after adding min_comp

  //  ProgLabel_1064  create super_year indexes for age compositions
       if(nsamp_a(f,j)==-9999)  // start a super-year  ALL observations must be continguous in the file
       {N_supyr_a(f)+=1; supyr_a1(f,N_supyr_a(f))=j;}
       if(nsamp_a(f,j)==-9998)  // end a super-year
       {supyr_a2(f,N_supyr_a(f))=j;}
     }
     }
    }
   }
 END_CALCS

// ***********************************************************************
//  ProgLabel_1070  read mean Size_at_Age data

  init_int nobs_ms_rd
  int nobs_ms
  !!echoinput<<nobs_ms_rd<<" N mean size-at-age obs "<<endl;
  init_matrix sizeagedata(1,nobs_ms_rd,1,7+2*n_abins2)
   !!if(nobs_ms_rd>0) echoinput<<" first meansize obs "<<endl<<sizeagedata(1)<<endl<<" last obs"<<endl<<sizeagedata(nobs_ms_rd)<<endl;;
  ivector nyr_ms(1,Ntypes)

 LOCAL_CALCS
  nyr_ms=0;
  if(nobs_ms_rd>0)
  for(i=1;i<=nobs_ms_rd;i++)
  {
    y=sizeagedata(i,1);
    if(y>=styr && y<=retro_yr)
    {
   f=sizeagedata(i,3);
   nyr_ms(f)++;
    }
  }
  nobs_ms=sum(nyr_ms);
 END_CALCS

  imatrix yr_ms(1,Ntypes,1,nyr_ms)
  imatrix yr_ms_y(1,Ntypes,1,nyr_ms)
  3darray obs_ms(1,Ntypes,1,nyr_ms,1,n_abins2)
  3darray obs_ms_n(1,Ntypes,1,nyr_ms,1,n_abins2)
  3darray obs_ms_n_read(1,Ntypes,1,nyr_ms,1,n_abins2)
  imatrix  ageerr_type_ms(1,Ntypes,1,nyr_ms)
  imatrix  gen_ms(1,Ntypes,1,nyr_ms)
  imatrix  mkt_ms(1,Ntypes,1,nyr_ms)
  imatrix  use_ms(1,Ntypes,1,nyr_ms)
  3darray header_ms(1,Ntypes,1,nyr_ms,1,7)
  ivector N_supyr_ms(1,Ntypes)      // N super_yrs per obs
  imatrix supyr_ms1(1,Ntypes,1,20)  //  max of 20 superyear obs are allowed per type
  imatrix supyr_ms2(1,Ntypes,1,20)  //  max of 20 superyear obs are allowed per type

 LOCAL_CALCS
   N_supyr_ms=0;
   nyr_ms=0;
   if(nobs_ms>0)
     {
    for(floop=1;floop<=Ntypes;floop++)
    for(tloop=styr;tloop<=(styr+(endyr+1-styr)*nseas);tloop++)
   for(i=1;i<=nobs_ms_rd;i++)
   {
    y=sizeagedata(i,1);
    if(y>=styr && y<=retro_yr)
    {
    s=sizeagedata(i,2);
    t=styr+(y-styr)*nseas+s-1;
    f=sizeagedata(i,3);
       if(f==floop && t==tloop)
         {
    nyr_ms(f)+=1;
    header_ms(f,nyr_ms(f))=sizeagedata(i)(1,7);
    yr_ms(f,nyr_ms(f))=t;
    yr_ms_y(f,nyr_ms(f))=y;
    gen_ms(f,nyr_ms(f))=sizeagedata(i,4);
    mkt_ms(f,nyr_ms(f))=sizeagedata(i,5);
    ageerr_type_ms(f,nyr_ms(f))=sizeagedata(i,6);
    use_ms(f,nyr_ms(f))=sizeagedata(i,7);
    if(y>retro_yr) use_ms(f,nyr_ms(f)) = -fabs(use_ms(f,nyr_ms(f)));
    for(b=1;b<=n_abins2;b++)
     {obs_ms(f,nyr_ms(f),b)=sizeagedata(i,7+b);}
    for(b=1;b<=n_abins2;b++)
      {obs_ms_n(f,nyr_ms(f),b)=sizeagedata(i,7+b+n_abins2);obs_ms_n_read(f,nyr_ms(f),b)=sizeagedata(i,7+b+n_abins2);}

//  ProgLabel_1074  create super_year indexes for mean size-at-age data
   if(sizeagedata(i,7)==-9999)  // start a super-year  ALL observations must be continguous in the file
     {N_supyr_ms(f)+=1; supyr_ms1(f,N_supyr_ms(f))=nyr_ms(f);}
   if(sizeagedata(i,7)==-9998)  // end a super-year
     {supyr_ms2(f,N_supyr_ms(f))=nyr_ms(f);}
   }
     }
    }
     }

   cout<<"  successful read of size@age data; N = "<<nobs_ms<<endl;
 END_CALCS


//  ProgLabel_1090  read environmental data that will be used to modify processes and expected values
    init_int N_envvar
  !!echoinput<<N_envvar<<" N_envvar "<<endl;
    init_int N_envdata
  !!echoinput<<N_envdata<<" N_envdata "<<endl;

    matrix env_data_RD(styr-1,endyr+100,1,N_envvar)  //  leave enough room for N_Fore_Yrs which is not yet known
    init_matrix env_temp(1,N_envdata,1,3)
 LOCAL_CALCS
     if(N_envdata>0)
     {
      if(N_envdata>0)echoinput<<" env data "<<endl<<env_temp<<endl;
      env_data_RD=0.;
      for (i=1;i<=N_envdata;i++)
        if(env_temp(i,1)>=(styr-1))
        {env_data_RD(env_temp(i,1), env_temp(i,2) ) = env_temp(i,3);}
     }
 END_CALCS

//ProgLabel_1045  read weight frequency data
  int WtFreqMethod;
  int iobs;
  init_int WtFreq_Nmeth;                                   // number of wtfreq methods to be read
  !!echoinput<<WtFreq_Nmeth<<" N sizefreq methods to read "<<endl;
  4darray WtFreq_HaveObs(1,Ntypes,1,WtFreq_Nmeth,styr,TimeMax,0,2)
  imatrix WtFreq_HaveObs2(1,WtFreq_Nmeth,styr,TimeMax)
  init_ivector WtFreq_Nbins(1,WtFreq_Nmeth);               //  number of bins for each method
  !!if(WtFreq_Nmeth>0) echoinput<<WtFreq_Nbins<<" Sizefreq N bins per method"<<endl;
  init_ivector WtFreq_units(1,WtFreq_Nmeth);               //  units for proportions (1 = biomass; 2=numbers ) for each method
  !!if(WtFreq_Nmeth>0) echoinput<<WtFreq_units<<" Sizetfreq units(bio/num) per method"<<endl;
  init_ivector WtFreq_scale(1,WtFreq_Nmeth);               //  bin scale (1=kg; 2=lbs; 3=cm; 4=in) for each method
  !!if(WtFreq_Nmeth>0) echoinput<<WtFreq_scale<<" Sizefreq scale(kg/lbs/cm/inches) per method"<<endl;
  init_vector WtFreq_mincomp(1,WtFreq_Nmeth);               //  mincomp to add for each method
  !!if(WtFreq_Nmeth>0) echoinput<<WtFreq_mincomp<<" Sizefreq mincomp per method "<<endl;
  init_ivector WtFreq_nobs(1,WtFreq_Nmeth);
  !!if(WtFreq_Nmeth>0) echoinput<<WtFreq_nobs<<" Sizefreq N obs per method"<<endl;
//  ivector WtFreq_Nbins_seas(1,WtFreq_Nmeth*nseas);
  ivector WtFreq_Nbins_seas_g(1,WtFreq_Nmeth*nseas);
//  ivector WtFreq_Nbins2(1,WtFreq_Nmeth)        // for calculating size of a matrix
  ivector WtFreq_Nbins3(1,WtFreq_Nmeth)        // for calculating size of a matrix

 LOCAL_CALCS
  g=0;
  if(WtFreq_Nmeth>0)
  {
    WtFreq_HaveObs.initialize();
    WtFreq_HaveObs2.initialize();
    for(k=1;k<=WtFreq_Nmeth;k++)
    {
//      WtFreq_Nbins2(k)=gender*WtFreq_Nbins(k)+1;
      WtFreq_Nbins3(k)=gender*WtFreq_Nbins(k);
    for(s=1;s<=nseas;s++)
    {
      g++;
//      WtFreq_Nbins_seas(g)=WtFreq_Nbins(k);
      WtFreq_Nbins_seas_g(g)=WtFreq_Nbins(k)*gender;
    }
  }
  }
 END_CALCS

  init_matrix WtFreq_bins1(1,WtFreq_Nmeth,1,WtFreq_Nbins);    // lower edge of wt bins
  !!if(WtFreq_Nmeth>0) echoinput<<" SizeFreq bins-raw "<<endl<<WtFreq_bins1<<endl;
  matrix WtFreq_bins(1,WtFreq_Nmeth,1,WtFreq_Nbins3);
  matrix WtFreq_bins2(1,WtFreq_Nmeth,0,WtFreq_Nbins3+1);
  ivector WtFreq_Omit_Small(1,WtFreq_Nmeth);
  int WtFreq_totobs
  int WtFreq_Nuse

 LOCAL_CALCS
  if(WtFreq_Nmeth>0)
  {
  for(k=1;k<=WtFreq_Nmeth;k++)
  {

// set flag for accumulating, or not, fish from small pop len bins up into first WtFreq data bin
    WtFreq_Omit_Small(k)=1;
    if(WtFreq_bins1(k,1)<0)
    {
      WtFreq_Omit_Small(k)=-1;
      WtFreq_bins1(k,1)*=-1;  // make this positive for use in model, then write out as negative in data.ss_new
    }

    WtFreq_bins(k)(1,WtFreq_Nbins(k))=WtFreq_bins1(k)(1,WtFreq_Nbins(k));
    if(gender==2)
    {
      for(j=1;j<=WtFreq_Nbins(k);j++)
      {
        WtFreq_bins(k,j+WtFreq_Nbins(k))=WtFreq_bins1(k,j);
      }
    }
    if(WtFreq_scale(k)==2)  // convert from lbs to kg
    {
      WtFreq_bins(k)*=0.4536;
    }
    else if (WtFreq_scale(k)==4)  // convert from inches to cm
    {
      WtFreq_bins(k)*=2.54;
    }
    WtFreq_bins2(k,0)=0.;
    WtFreq_bins2(k)(1,WtFreq_Nbins(k))=WtFreq_bins(k)(1,WtFreq_Nbins(k));
    if(gender==2)
    {
      WtFreq_bins2(k,WtFreq_Nbins(k)+1)=0.;
      for(j=1;j<=WtFreq_Nbins(k);j++)
      {WtFreq_bins2(k,j+WtFreq_Nbins(k)+1)=WtFreq_bins2(k,j);}
    }
    echoinput<<"Processed_SizeFreqMethod_bins"<<k<<endl<<WtFreq_bins(k)<<endl;;
  }
  WtFreq_totobs=sum(WtFreq_nobs);
  }
 END_CALCS

  ivector WtFreq_Setup(1,WtFreq_totobs);  //  stores the number of bins plus header info to read into ragged array
  ivector WtFreq_Setup2(1,WtFreq_totobs);   //  stores the number of bins for each obs to create the ragged array

 LOCAL_CALCS
  if(WtFreq_Nmeth>0)
  {
  g=0;
  for(k=1;k<=WtFreq_Nmeth;k++)
  for(j=1;j<=WtFreq_nobs(k);j++)
  {g++; WtFreq_Setup(g)=7+gender*WtFreq_Nbins(k); WtFreq_Setup2(g)=gender*WtFreq_Nbins(k);}
  }
 END_CALCS

//  the observations are read into a ragged array, with the number of elements for each obs stored in wtfreq_setup
  init_matrix WtFreq_obs1(1,WtFreq_totobs,1,WtFreq_Setup);
   !!if(WtFreq_totobs>0) echoinput<<" first wtfreq obs "<<endl<<WtFreq_obs1(1)<<endl<<" last obs"<<endl<<WtFreq_obs1(WtFreq_totobs)<<endl;;
  imatrix WtFreq_obs_hdr(1,WtFreq_totobs,1,8);
  // 1=y; 2=s; 3=f; 4=gender; 5=partition; 6=skip flag; 7=first obs in this time; 8=last obs
  vector WtFreq_effN(1,WtFreq_totobs);
  matrix WtFreq_obs(1,WtFreq_totobs,1,WtFreq_Setup2);
  imatrix WtFreq_use(1,Ntypes,1,WtFreq_Nmeth)
  // Year, season, Fleet, Partition, Gender, SampleSize, <data>
 LOCAL_CALCS
  WtFreq_Nuse=0;
  if(WtFreq_Nmeth>0)
  {
    WtFreq_use.initialize();
    iobs=0;
    for(k=1;k<=WtFreq_Nmeth;k++)
    {
      for(j=1;j<=WtFreq_nobs(k);j++)
      {
        iobs++;
        for(z=1;z<=5;z++)
        {WtFreq_obs_hdr(iobs,z) = int(WtFreq_obs1(iobs,z+1));}
        WtFreq_effN(iobs) = WtFreq_obs1(iobs,7);
        for(z=1;z<=WtFreq_Setup2(iobs);z++) {WtFreq_obs(iobs,z)=WtFreq_obs1(iobs,7+z);}
        WtFreq_obs(iobs)/=sum(WtFreq_obs(iobs));
        WtFreq_obs(iobs)+=WtFreq_mincomp(k);
        WtFreq_obs(iobs)/=sum(WtFreq_obs(iobs));
        y=WtFreq_obs_hdr(iobs,1);
        s=WtFreq_obs_hdr(iobs,2);
        t=styr+(y-styr)*nseas+s-1;
        f=WtFreq_obs_hdr(iobs,3);
        if(gender==1) {WtFreq_obs_hdr(iobs,4)=0;}
        z=WtFreq_obs_hdr(iobs,4);  // gender
// get min and max index according to use of 0, 1, 2, 3 gender index
        if(z!=2) {WtFreq_obs_hdr(iobs,7)=1;} else {WtFreq_obs_hdr(iobs,7)=WtFreq_Nbins(k)+1;}
        if(z<=1) {WtFreq_obs_hdr(iobs,8)=WtFreq_Nbins(k);} else {WtFreq_obs_hdr(iobs,8)=2*WtFreq_Nbins(k);}
  //      WtFreq_obs_hdr(iobs,5);  // partition
        WtFreq_obs_hdr(iobs,6)=k;  if(k!=WtFreq_obs1(iobs,1)) {N_warn++; warning<<" wtfreq ID # doesn't match "<<endl; } // save method code for later use
        if(y>=styr && y<=retro_yr)
        {
          WtFreq_use(f,k)=1;    // indicates that this combination is being used
          if(WtFreq_HaveObs(f,k,t,1)==0) WtFreq_HaveObs(f,k,t,1)=iobs;  // save first counter in time x fleet locations with data
          WtFreq_HaveObs(f,k,t,2)=iobs;  // saves last pointer to this source of data
          if(WtFreq_HaveObs2(k,t)==0 || f<=WtFreq_HaveObs2(k,t)) WtFreq_HaveObs2(k,t)=f;  // find the smallest numbered f index that uses this method
          have_data(f,t)=1;
        }
        else
        {
          WtFreq_effN(iobs) = -1.;
          WtFreq_obs_hdr(iobs,6)=-1;  //  flag for skipping this obs
        }
      }
    }
    WtFreq_Nuse=sum(WtFreq_use);
  }
 END_CALCS

    vector WtFreq_like_base(1,WtFreq_Nuse)  // this is a constant offset, so can be declared in data section
 LOCAL_CALCS
  if(WtFreq_Nmeth>0)
  {
    WtFreq_like_base.initialize();

//  count the number of type x methods being used to create vector length for the likelihoods
    g=0;
    for(f=1;f<=Ntypes;f++)
    for(k=1;k<=WtFreq_Nmeth;k++)
    {
      if(WtFreq_use(f,k)>0) {g++; WtFreq_use(f,k)=g;}
    }

    for(iobs=1;iobs<=WtFreq_totobs;iobs++)
    {
      z1=WtFreq_obs_hdr(iobs,7);
      z2=WtFreq_obs_hdr(iobs,8);
      f=WtFreq_obs_hdr(iobs,3);
      k=WtFreq_obs_hdr(iobs,6);
      if(k>0 && WtFreq_effN(iobs)>0.)  // k =-1 for out of range times; hdr(5) has sample size
      {
        g=WtFreq_use(f,k);
        WtFreq_like_base(g)+=WtFreq_effN(iobs)*WtFreq_obs(iobs)(z1,z2)*log(WtFreq_obs(iobs)(z1,z2));
      }
    }
  echoinput<<" done processing wtfreq data "<<endl;
  }
 END_CALCS

//  read tag release data
  init_int Do_TG
  !!echoinput<<Do_TG<<" Do_TagData(0/1) "<<endl;

  init_vector TG_temp(1,4*Do_TG)
  int TG;
  int N_TG   // N tag groups
  int N_TG2;
  int TG_timestart;
  int N_TG_recap;   //  N recapture events
  int TG_mixperiod; //  First period (seasons) to start comparing obs to expected recoveries; period=0 is the release period
  int TG_maxperiods; //  max number of periods (seasons) to track recoveries; period=0 is the release period
 LOCAL_CALCS
  if(Do_TG>0)
  {
    Do_TG=1;
    N_TG=TG_temp(1);
    N_TG_recap=TG_temp(2);
    TG_mixperiod=TG_temp(3);
    TG_maxperiods=TG_temp(4);
    N_TG2=N_TG;
    TG_timestart=9999;
    echoinput<<N_TG<<" N tag groups "<<endl
    <<N_TG_recap<<" N recapture events"<<endl
    <<TG_mixperiod<<"  Latency period for mixing"<<endl
    <<TG_maxperiods<<" N periods to track recoveries"<<endl;
  }
  else
  {
    N_TG=0;
    N_TG_recap=0;
    TG_mixperiod=0;
    TG_maxperiods=0;
    N_TG2=1;
    TG_timestart=1;
  }
 END_CALCS

  ivector TG_endtime(1,N_TG2)
  init_matrix TG_release(1,N_TG,1,8)
  // TG area  year season tindex gender age N_released
 LOCAL_CALCS
   echoinput<<" Tag Releases "<<endl<<"TG area year seas tindex gender age N_released "<<endl<<TG_release<<endl;
   TG_endtime(1)=0;
   if(N_TG>0)
   {
   for(TG=1;TG<=N_TG;TG++)
   {
     t=styr+int((TG_release(TG,3)-styr)*nseas+TG_release(TG,4)-1);
     TG_release(TG,5)=t;
     if(t<TG_timestart) TG_timestart=t;
     k=TG_maxperiods;
     if((t+TG_maxperiods)>TimeMax) k-=(t+TG_maxperiods-TimeMax);
      TG_endtime(TG)=k;
   }
  }
 END_CALCS

  init_matrix TG_recap_data(1,N_TG_recap,1,5)
  //  TG, year, season, fleet, gender, Number
  3darray TG_recap_obs(1,N_TG2,0,TG_endtime,0,Nfleet);   //  no area index because each fleet is in just one area
 LOCAL_CALCS
   if(N_TG>0)
   {
   echoinput<<"First row of tag-recapture data "<<TG_recap_data(1)<<endl;
   echoinput<<"Last  row of tag-recapture data "<<TG_recap_data(N_TG_recap)<<endl;
   TG_recap_obs.initialize();
   for(j=1;j<=N_TG_recap;j++)
   {
     TG=TG_recap_data(j,1);  // TD the tag group
     t=styr+int((TG_recap_data(j,2)-styr)*nseas+TG_recap_data(j,3)-1) - TG_release(TG,5); // find elapsed time in terms of number of seasons
     if(t>TG_maxperiods) t=TG_maxperiods;
     TG_recap_obs(TG,t,TG_recap_data(j,4))+=TG_recap_data(j,5);  //   save N recaptures by TG, fleet of recapture, elapsed time
   }
   for(TG=1;TG<=N_TG;TG++)
   {
     for(TG_t=0;TG_t<=TG_endtime(TG);TG_t++)
     {
       TG_recap_obs(TG,TG_t,0) = sum(TG_recap_obs(TG,TG_t)(1,Nfleet));
       if(TG_recap_obs(TG,TG_t,0)>0.) TG_recap_obs(TG,TG_t)(1,Nfleet)/=TG_recap_obs(TG,TG_t,0);
     }
   }
  }
 END_CALCS

//  ProgLabel_xxxx  Morphcomposition data
   init_int Do_Morphcomp
  !!echoinput<<Do_Morphcomp<<" Do_Morphcomp(0/1) "<<endl;
   init_vector mc_temp(1,3*Do_Morphcomp);
   int Morphcomp_nobs
   int Morphcomp_nmorph
   number Morphcomp_mincomp
 LOCAL_CALCS
  if(Do_Morphcomp>0)
  {
    Morphcomp_nobs=mc_temp(1);
    Morphcomp_nmorph=mc_temp(2);   // later compare this value to the n morphs in the control file and exit if different
    Morphcomp_mincomp=mc_temp(3);
  echoinput<<Morphcomp_nobs<<" Morphcomp_nobs "<<endl;
  echoinput<<Morphcomp_nmorph<<" Morphcomp_nmorph "<<endl;
  echoinput<<Morphcomp_mincomp<<" Morphcomp_mincomp "<<endl;
  }
  else
  {
    Morphcomp_nobs=0;
  }
 END_CALCS
 init_matrix Morphcomp_obs(1,Morphcomp_nobs,1,5+Morphcomp_nmorph)
//    yr, seas, type, partition, Nsamp, datavector

  3darray Morphcomp_havedata(1,Ntypes*Do_Morphcomp,styr,TimeMax,0,0)    // last dimension is reserved for future use of Partition
 LOCAL_CALCS
  if(Do_Morphcomp>0)
  {
  echoinput<<" morph composition data"<<endl<<"yr seas type partition Nsamp datavector"<<endl<< Morphcomp_obs<<endl;
  Morphcomp_havedata=0;
  for(i=1;i<=Morphcomp_nobs;i++)
  {
    y=Morphcomp_obs(i,1); s=Morphcomp_obs(i,2); t=styr+(y-styr)*nseas+s-1;
    f=Morphcomp_obs(i,3); z=Morphcomp_obs(i,4);   // z not used, partition must be 0 (e.g. combined discard and retained)
    Morphcomp_havedata(f,t,0)=i;
    have_data(f,t)=1;
    if(y>retro_yr) Morphcomp_obs(i,5) = -fabs(Morphcomp_obs(i,5));
    Morphcomp_obs(i)(6,5+Morphcomp_nmorph) /= sum(Morphcomp_obs(i)(6,5+Morphcomp_nmorph));
    Morphcomp_obs(i)(6,5+Morphcomp_nmorph) += Morphcomp_mincomp;
    Morphcomp_obs(i)(6,5+Morphcomp_nmorph) /= sum(Morphcomp_obs(i)(6,5+Morphcomp_nmorph));
  }
  }
 END_CALCS

//End of file indicator
  init_int fid
  !! if(fid!=999) {cout<<" final data value in error "<<fid<<endl; exit(1);}
  !! cout<<"Data read sucessful "<<fid<<endl<<endl;
  !!echoinput<<" data read successful"<<endl<<endl;

//**********************************************************************************************************************
//  read info for doing forecast                       ProgLabel_029a
 LOCAL_CALCS
  ad_comm::change_datafile_name("forecast.SS");
  cout<<" reading forecast file "<<endl;
  ifstream Forecast_Stream("forecast.SS");   //  even if the global_datafile name is used, there still is a different logical device created
  k=1;
  N_FC=0;
  while(k!=0)
  {
    Forecast_Stream >>  readline;          // reads the line from input stream
    if(length(readline)>2)
    {
      checkchar=readline(1);
      k=strcmp(checkchar,"#");
      checkchar=readline(1,2);
      j=strcmp(checkchar,"#C");
      if(j==0) {N_FC++; Forecast_Comments+=readline;}
    }
  }
 END_CALCS

  init_int Do_Forecast   //  0=none; 1=F(SPR); 2=F(MSY) 3=F(Btgt); 4=F(endyr); 5=Ave F (enter yrs); 6=read Fmult
  !!echoinput<<Do_Forecast<<" Do_Forecast "<<endl;
  init_int Fore_Sel_yr1a;
  !!echoinput<<Fore_Sel_yr1a<<" Sel_yr_start "<<endl;
  init_int Fore_Sel_yr2a;
  !!echoinput<<Fore_Sel_yr2a<<" Sel_yr_end "<<endl;
  int Fore_Sel_yr1
  int Fore_Sel_yr2
  init_int Do_Benchmark  // 0=skip; do Fspr, Fbtgt, Fmsy
  !!echoinput<<Do_Benchmark<<" Do_Benchmark "<<endl;
  init_int Do_MSY   //  1= set to F(SPR); 2=calc F(MSY); 3=set to F(Btgt); 4=set to F(endyr)
  !!echoinput<<Do_MSY<<" Do_MSY "<<endl;

  int did_MSY;
  int show_MSY;
  init_number SPR_target
  !!echoinput<<SPR_target<<" SPR_target "<<endl;
  init_number BTGT_target
  !!echoinput<<BTGT_target<<" BTGT_target "<<endl;
  init_int N_Fore_Yrs
  !!echoinput<<N_Fore_Yrs<<" N_Fore_Yrs "<<endl;

  init_int Do_Fore_Adv_Opt
  !!echoinput<<Do_Fore_Adv_Opt<<" Do_Fore_Adv_Opt "<<endl;
  init_vector Fore_Adv_Opt(1,10*Do_Fore_Adv_Opt)

  int Do_Rebuilder
  int Rebuild_Ydecl
  int Rebuild_Yinit
  int HarvestPolicy  // 1=west coast adjust catch; 2=AK to adjust F
  number H4010_top
  number H4010_bot
  number H4010_scale
  int Max_Fore_Catch_Basis;
  int Do_Impl_Error  //  not yet implemented
  number Impl_Error

 LOCAL_CALCS
  if(Do_Fore_Adv_Opt==0)
  {
    Do_Rebuilder=0;
    Rebuild_Ydecl=endyr-1;
    Rebuild_Yinit=endyr+1;
    HarvestPolicy=1;  // 1=west coast adjust catch; 2=AK to adjust F
    H4010_top=0.40;
    H4010_bot=0.10;
    H4010_scale=1.0;
    Max_Fore_Catch_Basis=0;
    Do_Impl_Error=0;  //  not yet implemented
    Impl_Error=0.1;
  }
  else if (Do_Fore_Adv_Opt==1)
  {
    Do_Rebuilder=int(Fore_Adv_Opt(1));
    Rebuild_Ydecl=int(Fore_Adv_Opt(2));
    Rebuild_Yinit=int(Fore_Adv_Opt(3));
    HarvestPolicy=int(Fore_Adv_Opt(4));
    H4010_top=Fore_Adv_Opt(5);
    H4010_bot=Fore_Adv_Opt(6);
    H4010_scale=Fore_Adv_Opt(7);
    Max_Fore_Catch_Basis=Fore_Adv_Opt(8);
    Do_Impl_Error=int(Fore_Adv_Opt(9));
    Impl_Error=Fore_Adv_Opt(10);
    if(H4010_scale>1.0) {N_warn++; warning<<" Sure you want harvest policy scalar > 1.0? "<<H4010_scale<<endl;}
    echoinput<<
    Do_Rebuilder<<"  Do_Rebuilder "<<endl<<
    Rebuild_Ydecl<<"  Rebuild_Ydecl "<<endl<<
    Rebuild_Yinit<<"  Rebuild_Yinit "<<endl<<
    HarvestPolicy<<"  HarvestPolicy "<<endl<<
    H4010_top<<"  H4010_top "<<endl<<
    H4010_bot<<"  H4010_bot "<<endl<<
    H4010_scale<<"  H4010_scale "<<endl<<
    Max_Fore_Catch_Basis<<"  Max_Fore_Catch_basis "<<endl<<
    Do_Impl_Error<<"  Do_Impl_Error "<<endl<<
    Impl_Error<<"  Impl_Error "<<endl;
  }
  else
  {
    cout<<" illegal value for Do_Fore_Adv_Opt "<<Do_Fore_Adv_Opt<<endl; exit(1);
  }
  if(Max_Fore_Catch_Basis>0)
  {k1=1;}
  else
  {k1=0;}
 END_CALCS

  init_matrix Max_Fore_Catch(1,nseas*k1,1,pop*k1)

 LOCAL_CALCS
  if(Do_Rebuilder>0 && Do_Forecast<=0) {N_warn++; warning<<" Rebuilder output selected without requesting forecast"<<endl;}


  if(Do_Benchmark==0)
  {
    if(Do_Forecast>=1 && Do_Forecast<=3) {Do_Benchmark=1; N_warn++; warning<<" Turn Benchmark on because Forecast needs it"<<endl;}
    if(Do_Forecast==0 && F_report_basis>0) {F_report_basis=0; N_warn++; warning<<" Set F_report_basis=0 because no benchmark or forecast"<<endl;}
    if(depletion_basis==2) {depletion_basis=1; N_warn++; warning<<" Change depletion basis to 1 because benchmarks are off"<<endl;}
    if(SPR_reporting>=1 && SPR_reporting<=3) {SPR_reporting=4; N_warn++; warning<<" Change SPR_reporting to 4 because benchmarks are off"<<endl;}
  }
  else
  {
     if(Do_MSY==0)  {Do_MSY=1; N_warn++; warning<<" Setting Do_MSY=1 because benchmarks are on"<<endl;}
  }
  if(Do_Forecast==2 && Do_MSY!=2) {Do_MSY=2; N_warn++; warning<<" Set MSY option =2 because Forecast option =2"<<endl;}
  if(depletion_basis==2 && Do_MSY!=2) {Do_MSY=2; N_warn++; warning<<" Set MSY option =2 because depletion basis is B_MSY"<<endl;}
  if(SPR_reporting==2 && Do_MSY!=2) {Do_MSY=2; N_warn++; warning<<" Set MSY option =2 because SPR basis is SPR_MSY"<<endl;}
  Fore_Sel_yr1=Fore_Sel_yr1a;
  Fore_Sel_yr2=Fore_Sel_yr2a;
  if(Fore_Sel_yr1<=0) Fore_Sel_yr1=endyr+Fore_Sel_yr1;
  if(Fore_Sel_yr2<=0) Fore_Sel_yr2=endyr+Fore_Sel_yr2;
  if(Fore_Sel_yr1>Fore_Sel_yr2) {N_warn++; cout<<" exit - see warning "<<endl; warning<<" Error, Fore_Sel_Yr1 must be at or before Fore_Sel_Yr1"<<endl;  exit(1);}
  if(Fore_Sel_yr1>endyr || Fore_Sel_yr1<styr) {N_warn++; cout<<" exit - see warning "<<endl; warning<<" Error, Fore_Sel_Yr1 must be between styr and endyr"<<endl;  exit(1);}
  if(Fore_Sel_yr2>endyr || Fore_Sel_yr2<styr) {N_warn++; cout<<" exit - see warning "<<endl; warning<<" Error, Fore_Sel_Yr2 must be between styr and endyr"<<endl;  exit(1);}

  did_MSY=0;
  if(Do_Forecast==0) {N_Fore_Yrs=0;}
  YrMax=endyr+N_Fore_Yrs;
  TimeMax_Fore_std = styr+(YrMax-styr)*nseas+nseas-1;
 END_CALCS
   init_int Fore_Rel_Harvest  // 1=use endyr pattern; 2=read below
   !! echoinput<<Fore_Rel_Harvest<<" fleet allocation (1/2) "<<endl;

  !! if(Fore_Rel_Harvest==2) {z=nseas;} else {z=0;}
   init_matrix Input_ForeRate1(1,z,1,Nfleet)
   !! if(Fore_Rel_Harvest==2) echoinput<<" fleet allocation by season and fleet "<<endl<<Input_ForeRate1<<endl;
   matrix Input_ForeRate(1,nseas,1,Nfleet)

 LOCAL_CALCS
  if(Fore_Rel_Harvest>1) Input_ForeRate=Input_ForeRate1;
  k1 = styr+(endyr-styr)*nseas-1 + nseas + 1;
  y=k1+(N_Fore_Yrs)*nseas-1;
 END_CALCS
  matrix Input_ForeCatch(k1,y,1,Nfleet)
  init_int N_fore_catches
   !! echoinput<<N_fore_catches<<" N_fore_catches "<<endl;
  int ForeCatch_basis  //  1=retained catch; 2=total dead catch

 LOCAL_CALCS
  if(N_fore_catches>0)
  {*(ad_comm::global_datafile) >> ForeCatch_basis;
   echoinput<<ForeCatch_basis<<" ForeCatch_basis "<<endl;
    }
  else
  {ForeCatch_basis=1;}
 END_CALCS

  init_matrix Input_ForeCatch_1(1,N_fore_catches,1,4)
  !! if(N_fore_catches>0) echoinput<<" fore_catches "<<endl<<Input_ForeCatch_1<<endl;
  init_number fif
 LOCAL_CALCS
  if(fif!=999) {cout<<" must have 999 to verify end of forecast inputs "<<fif<<endl; exit(1);}
  for(t=k1;t<=y;t++)
  for(f=1;f<=Nfleet;f++)
  {Input_ForeCatch(t,f)=-1;}
  if(N_fore_catches>0)
  {
    for(i=1;i<=N_fore_catches;i++)
    {
    	y=Input_ForeCatch_1(i,1); s=Input_ForeCatch_1(i,2); f=Input_ForeCatch_1(i,3);
    	if(y>endyr && y<=YrMax && f<=Nfleet)
    	{
    		t=styr+(y-styr)*nseas +s-1;
    		Input_ForeCatch(t,f)=Input_ForeCatch_1(i,4);
    	}
    }
  }
  echoinput<<" done reading forecast "<<endl<<endl;
 END_CALCS

  ivector STD_Yr_Reverse(styr-2,YrMax)
  ivector STD_Yr_Reverse_Dep(styr-2,YrMax)
  ivector STD_Yr_Reverse_Ofish(styr-2,YrMax)
  ivector STD_Yr_Reverse_F(styr-2,YrMax)
  int N_STD_Yr_Dep;
  int N_STD_Yr_Ofish;
  int N_STD_Yr_F;
  int N_STD_mgmtquant;

 LOCAL_CALCS
// create complete list of years for STD
  if(STD_Yr_min<0 || STD_Yr_min<(styr-2) ) STD_Yr_min=styr-2;
  if(STD_Yr_max==-1) STD_Yr_max=endyr;
  if(STD_Yr_max==-2) STD_Yr_max=YrMax;
  if(STD_Yr_max>YrMax) STD_Yr_max=YrMax;

   STD_Yr_Reverse.initialize();
   for(y=STD_Yr_min;y<=STD_Yr_max;y++) {STD_Yr_Reverse(y)=1;}
   for(i=1;i<=N_STD_Yr_RD;i++)
   {if(STD_Yr_RD(i)>=styr && STD_Yr_RD(i)<YrMax) {STD_Yr_Reverse(STD_Yr_RD(i))=1;}}

   N_STD_Yr=sum(STD_Yr_Reverse);
 END_CALCS

 LOCAL_CALCS
  STD_Yr_Reverse_Dep.initialize();
  STD_Yr_Reverse_Ofish.initialize();
  STD_Yr_Reverse_F.initialize();
  j=0;
  N_STD_Yr_Dep=0;
  N_STD_Yr_Ofish=0;
  N_STD_Yr_F=0;

  for(y=styr-2;y<=YrMax;y++)
  {
    if(STD_Yr_Reverse(y)>0)
    {
      j++;
      STD_Yr_Reverse(y)=j;  // use for SPB and recruitment
      if(y>=styr)
      {
      // depletion must start in year AFTER first catch.  It could vary earlier if recdevs happened enough earlier to change spbio, but this is not included
      if((depletion_basis>0 && y>first_catch_yr) || y==endyr) {N_STD_Yr_Dep++; STD_Yr_Reverse_Dep(y) = N_STD_Yr_Dep; }
      if(y<=endyr)
      {
        if((SPR_reporting>0 && totcat(y)>0.0) || y==endyr) {N_STD_Yr_Ofish++; STD_Yr_Reverse_Ofish(y) = N_STD_Yr_Ofish; }
        if((F_reporting>0 && totcat(y)>0.0) || y==endyr) {N_STD_Yr_F++; STD_Yr_Reverse_F(y) = N_STD_Yr_F; }
      }
      else
      {
        if(SPR_reporting>0) {N_STD_Yr_Ofish++; STD_Yr_Reverse_Ofish(y) = N_STD_Yr_Ofish; }
        if(F_reporting>0) {N_STD_Yr_F++; STD_Yr_Reverse_F(y) = N_STD_Yr_F; }
      }

      }
    }
  }
 END_CALCS

//********CONTROLS********************************
//  ProgLabel_1100   Begin Reading from Control File

  !! ad_comm::change_datafile_name(ctlfilename);
  !!echoinput<<endl<<" Begin reading control file "<<endl;

 LOCAL_CALCS
  ad_comm::change_datafile_name(ctlfilename);
  echoinput<<endl<<" Begin reading control file "<<endl;
  cout<<" reading from control  file"<<endl;
  ifstream Control_Stream(ctlfilename);   //  even if the global_datafile name is used, there still is a different logical device created
  k=1;
  N_CC=0;
  while(k!=0)
  {
    Control_Stream >>  readline;          // reads the line from input stream
    if(length(readline)>2)
    {
      checkchar=readline(1);
      k=strcmp(checkchar,"#");
      checkchar=readline(1,2);
      j=strcmp(checkchar,"#C");
      if(j==0) {N_CC++; Control_Comments+=readline;}
    }
  }
 END_CALCS

//  ProgLabel_1110  Set up indexing for growth patterns, sub-morphs, birthseasons
  init_int N_GP  // number of growth patterns
  !!echoinput<<N_GP<<" N growth patterns "<<endl;
  init_int N_GP_sub  //  number of sub-morphs  1, 3, 5 are best values to use
  !!echoinput<<N_GP_sub<<"  N sub-morphs (1, 3 or 5)"<<endl;
  number sd_ratio;  // ratio of stddev within sub-morph to between morphs
  vector submorphdist(1,N_GP_sub);
 LOCAL_CALCS
  cout<<" begin reading control file "<<endl;
  if(N_GP_sub>1)
  {
    *(ad_comm::global_datafile) >> sd_ratio;
    *(ad_comm::global_datafile) >> submorphdist;
  echoinput<<sd_ratio<<"  sd_ratio"<<endl;
  echoinput<<submorphdist<<"  submorphdist"<<endl;
  }
  else
  {
    sd_ratio=1.;
    submorphdist(1)=1.;
    echoinput<<"  do not read sd_ratio or submorphdist"<<endl;
  }
 END_CALCS
  int gmorph // number of gmorphs
  int gp
  int gp2
  int birthseas;
  !! gmorph = N_GP*N_GP_sub*gender*nseas;
  ivector sx(1,gmorph) //  define sex for each growth morph
  ivector GP(1,gmorph)    //  index for main gpattern*gender
  ivector GP3(1,gmorph)   // index for main gpattern*gender*birthseason
  ivector GP4(1,gmorph)   // index for main gpattern
  ivector Bseas(1,gmorph)
  ivector GP2(1,gmorph)  // reverse pointer for submorphs
//  following two containers are used to track which morphs are being used
  ivector use_morph(1,gmorph)
  imatrix TG_use_morph(1,N_TG2,1,gmorph)
  imatrix recr_dist_pattern_2(1,N_GP,1,nseas)   // used in get_growth to flag morphs needing to have growth calculated

  ivector ishadow(1,N_GP_sub)
  vector shadow(1,N_GP_sub)
  vector azero_seas(1,nseas);   // cumulative time within year up until this season
  vector azero_G(1,gmorph);
  3darray curr_age1(1,gmorph,1,nseas,0,nages);  // constants, so can be dvector
  3darray curr_age2(1,gmorph,1,nseas,0,nages);
  3darray curr_age3(1,gmorph,1,nseas,0,nages);
  imatrix first_grow_age(1,gmorph,1,nseas);
 LOCAL_CALCS
  azero_seas(1)=0.;
  if(nseas>1)
    for(s=2;s<=nseas;s++)
    {azero_seas(s)=sum(seasdur(1,s-1));}

   if(N_GP_sub==1)
     {ishadow(1)=0; shadow(1)=0.;}
   else if (N_GP_sub==3)
     {ishadow.fill_seqadd(-1,1); shadow.fill_seqadd(-1.,1.);}
   else if (N_GP_sub==5)
     {ishadow.fill_seqadd(-2,1); shadow.fill_seqadd(-2.,1.);}
   else
     {N_warn++; warning<<" illegal N submorphs, must be 1, 3 or 5 "<<N_GP_sub<<endl; cout<<" exit - see warning "<<endl; exit(1);}
 END_CALCS


//  ProgLabel_1018  define distribution of recruitment among growth patterns, seasons, areas
  3darray recr_dist_pattern(1,N_GP,1,nseas,1,pop);
  int recr_dist_inx
  int recr_dist_read
 LOCAL_CALCS
  recr_dist_pattern.initialize();
  if(N_GP*nseas*pop==1) {j=0;} else {j=2;}
 END_CALCS
  init_ivector recr_dist_input(1,j)

 LOCAL_CALCS
  if(j==0)
    {recr_dist_inx=0;  recr_dist_read=0; echoinput<<" do not need to read any recr distribution info"<<endl;}
    else
    {recr_dist_read=recr_dist_input(1);  recr_dist_inx=recr_dist_input(2);
      echoinput<<recr_dist_read<<" recr_dist_read"<<endl;
      echoinput<<recr_dist_inx<<" recr_dist_interaction"<<endl;
      }
 END_CALCS

  init_imatrix recr_dist_pattern_1(1,recr_dist_read,1,3)
  imatrix GP_finder(1,N_GP,1,gender)
 LOCAL_CALCS
   if(recr_dist_read>0)
    {
      echoinput<<" recr distribution as read "<<endl<<recr_dist_pattern_1<<endl;
      for(i=1;i<=recr_dist_read;i++)
      {
        gp=recr_dist_pattern_1(i,1); birthseas=recr_dist_pattern_1(i,2); p=recr_dist_pattern_1(i,3);
        recr_dist_pattern(gp,birthseas,p)=1;
      }
    }
    else
      {
        recr_dist_pattern=1;
      }
   g=0;
   int g3i;
   g3i=0;
   recr_dist_pattern_2.initialize();
   use_morph.initialize();
   TG_use_morph.initialize();
   for(k=1;k<=gender;k++)
   for(gp=1;gp<=N_GP;gp++)
   for(birthseas=1;birthseas<=nseas;birthseas++)
   {
     g3i++;
     for(gp2=1;gp2<=N_GP_sub;gp2++)
     {
       g++;
       GP3(g)=g3i;  // track counter for main morphs (pattern x gender x bseas)
       Bseas(g)=birthseas;
       sx(g)=k;
       GP(g)=gp+(k-1)*N_GP;   // counter for pattern x gender
       GP2(g)=gp2; //   reverse pointer to sub-morph counter
       GP4(g)=gp;  //  counter for growth pattern
       azero_G(g)=azero_seas(birthseas);
       for(p=1;p<=pop;p++)
       {
         if(recr_dist_pattern(gp,birthseas,p)>0.)
         {
           recr_dist_pattern_2(gp,birthseas)=1;
           use_morph(g)=1;
         }
       }
       if(use_morph(g)==1)
       {
         if( (N_GP_sub==1) || (N_GP_sub==3 && gp2==2) || (N_GP_sub==5 && gp2==3) ) GP_finder(gp,k)=g;  // finds g for a given GP and gender and last birstseason
       }
     }
   }

   for(g=1;g<=gmorph;g++)
   for(s=1;s<=nseas;s++)
   {
     curr_age1(g,s)=r_ages+azero_seas(s)-azero_G(g);
     curr_age2(g,s)=curr_age1(g,s)+seasdur2(s);
     curr_age3(g,s)=curr_age1(g,s)+seasdur(s);
     if(azero_G(g)>azero_seas(s))
     {
       a=0;
       while(curr_age2(g,s,a)<0.0)
       {curr_age2(g,s,a)=0.0; a++;}
       a=0;
       while(curr_age1(g,s,a)<0.0)
       {curr_age1(g,s,a)=0.0; a++;}
     }
     a=0;
   }

    if(N_TG>0)
    {
      for(TG=1;TG<=N_TG;TG++)
      {
        for(g=1;g<=gmorph;g++)
        {
          if(TG_release(TG,6)>2) {N_warn++; warning<<" gender for tag groups must be 0, 1 or 2 "<<endl;}
          if(use_morph(g)>0 && (TG_release(TG,6)==0 || TG_release(TG,6)==sx(g))) TG_use_morph(TG,g)=1;
        }
      }
    }
 END_CALCS

//  ProgLabel_1120  define movement between areas
   int do_migration  //  number of explicit movements to define
   number migr_firstage
   matrix migr_start(1,nseas,1,N_GP)
 LOCAL_CALCS
   migr_firstage=0.0;
   do_migration=0;
   if (pop>1)
   {
      *(ad_comm::global_datafile) >> do_migration;
      echoinput<<do_migration<<" N_migration definitions to read"<<endl;
      if(do_migration>0)
      {
        *(ad_comm::global_datafile) >> migr_firstage;
        echoinput<<migr_firstage<<" migr_firstage"<<endl;
      }
    }
    else
    {
      echoinput<<" only 1 area, so no read of do_migration or migr_firstage "<<endl;
    }
 END_CALCS
   init_matrix move_def(1,do_migration,1,6)   // seas morph source dest minage maxge
   4darray move_pattern(1,nseas,1,N_GP,1,pop,1,pop)
   int do_migr2
   ivector firstBseas(1,N_GP)

 LOCAL_CALCS
    move_pattern.initialize();
    do_migr2=0;
    if(do_migration>0)
    {
      echoinput<<" migration setup "<<endl<<move_def<<endl;
      for(k=1;k<=do_migration;k++)
      {
        s=move_def(k,1); gp=move_def(k,2); p=move_def(k,3); p2=move_def(k,4);
        move_pattern(s,gp,p,p2)=k;   // save index for definition of this pattern to find the right parameters
      }

      k=do_migration;
      for(s=1;s<=nseas;s++)
      for(gp=1;gp<=N_GP;gp++)
      for(p=1;p<=pop;p++)
      {
        if(move_pattern(s,gp,p,p)==0) {k++; move_pattern(s,gp,p,p)=k;} //  no explicit migration for staying in this area, so create implicit
      }
      do_migr2=k;
      migr_start.initialize();
      // need to modify so it only does the calc for the first birthseason used for each GP
      for(gp=1;gp<=N_GP;gp++)
      {
        //  use firstBseas so that the start age of migration is calculated only for the first birthseason used for each GP
        firstBseas(gp)=0;
        for(g=1;g<=gmorph;g++)
        if(use_morph(g)>0)
        {
          if(GP4(g)==gp && firstBseas(gp)==0) firstBseas(gp)=Bseas(g);
        }
      }
      for(g=1;g<=gmorph;g++)
      if(use_morph(g)>0 && firstBseas(GP4(g))==Bseas(g))
      {
        for(s=1;s<=nseas;s++)
        {
        a=0;
        while(curr_age1(g,s,a)<migr_firstage) {a++;}
        migr_start(s,GP4(g))=a;
        }
      }
    }
 END_CALCS
   matrix move_def2(1,do_migr2,1,6)    //  movement definitions.  First Do_Migration of these are explicit; rest are implicit

 LOCAL_CALCS
    if(do_migration>0)
    {
      for(k=1;k<=do_migration;k++) {move_def2(k)=move_def(k);}
      k=do_migration;
      for(s=1;s<=nseas;s++)
      for(gp=1;gp<=N_GP;gp++)
      for(p=1;p<=pop;p++)
      {
        if(move_pattern(s,gp,p,p)>do_migration)
        {
          k++;
          move_def2(k,1)=s; move_def2(k,2)=gp; move_def2(k,3)=p; move_def2(k,4)=p; move_def2(k,5)=0; move_def2(k,6)=nages;
        }
      }
    }
 END_CALCS


//  ProgLabel_1130  define the time blocks for time-varying parameters
  int k1
  int k2
  int k3
  init_int N_Block_Designs                      // read N block designs
  !!echoinput<<N_Block_Designs<<" N_Block_Designs"<<endl;
  init_ivector Nblk(1,N_Block_Designs)    // N blocks in each design
 LOCAL_CALCS
  if(N_Block_Designs>0) echoinput<<Nblk<<" N_Blocks_per design"<<endl;
  k1=N_Block_Designs;
  if(k1==0) k1=1;
 END_CALCS

  ivector Nblk2(1,k1)
 LOCAL_CALCS
  Nblk2=2;
  if(N_Block_Designs>0) Nblk2=Nblk + Nblk;
 END_CALCS
  init_imatrix Block_Design(1,N_Block_Designs,1,Nblk2)  // read the ending year for each block
  !!if(N_Block_Designs>0) echoinput<<" read block info "<<endl<<Block_Design<<endl;

//  ProgLabel_1160 - natmort, growth, biology, recruitment distribution, and migration setup
// read setup for natmort parameters:  LO, HI, INIT, PRIOR, PR_type, CV, PHASE, use_env, use_dev, dev_minyr, dev_maxyr, dev_stddev, Block, Block_type
  int N_MGparm
  int N_natMparms
  int N_growparms
  int MGparm_per_def
  number natM_amin;
  number natM_amax;
  init_number fracfemale;
  !!echoinput<<fracfemale<<" fracfemale"<<endl;

// read natmort setup
  init_int natM_type;  //  0=1Parm; 1=segmented; 2=Lorenzen; 3=agespecific; 4=agespec with seas interpolate
  !!echoinput<<natM_type<<" natM_type"<<endl;
  !! if(natM_type==1 || natM_type==2) {k=1;} else {k=0;}
  init_vector tempvec4(1,k)
 LOCAL_CALCS
  k=0; k1=0;
  if(natM_type==0)
  {N_natMparms=1;}
  else if(natM_type==1)
  {
    N_natMparms=tempvec4(1);  k=N_natMparms;
    echoinput<<N_natMparms<<" N_natMparms for segmented approach"<<endl;
  }
  else if(natM_type==2)
  {
    natM_amin=tempvec4(1);  N_natMparms=1;
    echoinput<<natM_amin<<" natM_A for Lorenzen"<<endl;
  }
  else
  {
    N_natMparms=0;
    if(natM_type>=3) {k1=N_GP*gender;}  // for reading age_natmort
  }
 END_CALCS

  init_vector NatM_break(1,k);  // these breakpoints only get read for natM_type=1
  !!if(k>0) echoinput<<NatM_break<<" NatM_breakages "<<endl;
  init_matrix Age_NatMort(1,k1,0,nages)
  !!if(k1>0) echoinput<<" Age_NatMort "<<Age_NatMort<<endl;

// read growth setup
  init_int Grow_type  // 1=vonbert; 2=Richards; 4=read vector
  !!echoinput<<Grow_type<<" growth model "<<endl;
  number AFIX;
  number AFIX2;
  number AFIX_delta;
  number AFIX_plus;
  !! if(Grow_type<=2) {k=2;} else {k=0;}
  init_vector tempvec5(1,k)
 LOCAL_CALCS
  if(Grow_type<=2) echoinput<<tempvec5<<" growth age1 and age2"<<endl;
  k1=0;
  AFIX=0.;
  AFIX2=999.;  // this value invokes setting Linf equal to the L2 parameter
  if(Grow_type==1)
  {
    N_growparms=5;
    AFIX=tempvec5(1);
    AFIX2=tempvec5(2);
  }
  else if(Grow_type==2)
  {
    N_growparms=6;
    AFIX=tempvec5(1);
    AFIX2=tempvec5(2);
  }
  else if(Grow_type==3)
  {N_growparms=5;}
  else if(Grow_type==4)
  {
    N_growparms=2;  // for the two CV parameters
    k1=N_GP*gender;  // for reading age_natmort
  }
  AFIX_delta=AFIX2-AFIX;
  if(AFIX!=0.0)
  {AFIX_plus=AFIX;}
   else
   {AFIX_plus=1.0e-06;}
  MGparm_per_def=N_natMparms+N_growparms;

   for(g=1;g<=gmorph;g++)
   for(s=1;s<=nseas;s++)
   {
     a=0;
     while(curr_age1(g,s,a)<AFIX)
     {a++;}
     first_grow_age(g,s)=a;
   }
   if(AFIX>0 && Grow_type==2) {N_warn++; warning<<"beware using AFIX>0 with Richards growth fxn; unpredictable behavior if Richards parameter is estimated"<<endl;}
 END_CALCS

  init_matrix Len_At_Age_rd(1,k1,0,nages)
  !!if(k1>0) echoinput<<"  Len_At_Age_rd"<<Len_At_Age_rd<<endl;

  init_number SD_add_to_LAA   // constant added to SD length-at-age (set to 0.1 for compatibility with SS2 V1.x
  !!echoinput<<SD_add_to_LAA<<"  SD_add_to_LAA"<<endl;
  init_int CV_depvar     //  select CV_growth pattern; 0 CV=f(LAA); 1 CV=F(A); 2 SD=F(LAA); 3 SD=F(A);  SS2 V1.x ony had CV=F(LAA)
  !!echoinput<<CV_depvar<<"  CV_depvar"<<endl;
  int CV_depvar_a;
  int CV_depvar_b;
 LOCAL_CALCS
   if(CV_depvar==0 || CV_depvar==2)
     {CV_depvar_a=0;}
   else
     {CV_depvar_a=1;}
   if(CV_depvar<=1)
     {CV_depvar_b=0;}
   else
     {CV_depvar_b=1;}
 END_CALCS

   init_int Maturity_Option       // 1=length logistic; 2=age logistic; 3=read age-maturity 4= read age-fecundity by growth_pattern
 LOCAL_CALCS
  echoinput<<Maturity_Option<<"  Maturity_Option"<<endl;
  if(Maturity_Option>=3)
    {k1=N_GP;}
  else
    {k1=0;}
 END_CALCS
  init_matrix Age_Maturity(1,k1,0,nages)
  !!if(k1>0) echoinput<<"  Age_Maturity"<<Age_Maturity<<endl;

   init_int First_Mature_Age     // first age with non-zero maturity
   !! echoinput<<First_Mature_Age<<"  First_Mature_Age"<<endl;

   init_int Fecund_Option
//   Value=1 means interpret the 2 egg parameters as linear eggs/gm on body weight (current SS default),
//   so eggs = wt * (a+b*wt), so value of a=1, b=0 causes eggs to be equiv to spawning biomass
//   Value=2 sets eggs=a*L^b   so cannot make equal to biomass
//   Value=3 sets eggs=a*W^b, so values of a=1, b=1 causes eggs to be equiv to spawning biomass
   !! echoinput<<Fecund_Option<<"  Fecundity option"<<endl;


   init_int MGparm_def       //  offset approach (1=none, 2= M, G, CV_G as offset from female-GP1, 3=like SS2 V1.x)
   !! echoinput<<MGparm_def<<"  MGparm_def"<<endl;
   init_int MG_adjust_method   //  1=do V1.xx approach to adjustment by env, block or dev; 2=use new logistic approach
   !! echoinput<<MG_adjust_method<<"  MG_adjust_method"<<endl;

  imatrix time_vary_MG(styr-1,endyr+2,0,5)
  ivector MG_active(0,5)
  int do_once;
  int doit;
  vector femfrac(1,N_GP*gender)
  number sd_withinmorph
  number sd_betweenmorph

  int MGP_CGD
  int CGD;  //  switch for cohort growth dev

 LOCAL_CALCS
  femfrac(1,N_GP)=fracfemale;
  if(gender==2) femfrac(N_GP+1,N_GP+N_GP)=1.-fracfemale;

//  ProgLabel_1066  assign distribution among growth sub-morphs
  if(submorphdist(1)<0.)
    {
    if(N_GP_sub==1)
      {submorphdist(1)=1.;}
    else if (N_GP_sub==3)
      {submorphdist.fill("{0.15,0.70,0.15}");}
    else if (N_GP_sub==5)
      {submorphdist.fill("{0.031, 0.237, 0.464, 0.237, 0.031}");}
    }
  submorphdist/=sum(submorphdist);

  ParCount=0;

  if(N_GP_sub>1)
    {
    sd_withinmorph = sd_ratio * sqrt(1. / (1. + sd_ratio*sd_ratio));
    sd_betweenmorph = sqrt(1. / (1. + sd_ratio*sd_ratio));
    }
  else
    {sd_withinmorph=1; sd_betweenmorph=0.000001;}

//  ProgLabel_1068  set up indexing for MG parameters
  N_MGparm=MGparm_per_def*N_GP*gender;     // dimension to hold the natmort, growth
  for(gg=1;gg<=gender;gg++)
  for(gp=1;gp<=N_GP;gp++)
  {
    for(k=1;k<=N_natMparms;k++)
    {
      ParCount++;
      onenum="    ";
//      _itoa( k, onenum, 10 );
      sprintf(onenum, "%d", k);
      ParmLabel+="NatM_p_"+onenum+"_"+GenderLbl(gg)+"_GP:"+NumLbl(gp);
    }
    switch (Grow_type)
    {
      case 1:
      {
        ParmLabel+="L_at_Amin_"+GenderLbl(gg)+"_GP_"+NumLbl(gp);
        ParmLabel+="L_at_Amax_"+GenderLbl(gg)+"_GP_"+NumLbl(gp);
        ParmLabel+="VonBert_K_"+GenderLbl(gg)+"_GP_"+NumLbl(gp);
        ParCount+=3;
        break;
      }
      case 2:
      {
        ParmLabel+="L_at_Amin_"+GenderLbl(gg)+"_GP_"+NumLbl(gp);
        ParmLabel+="L_at_Amax_"+GenderLbl(gg)+"_GP_"+NumLbl(gp);
        ParmLabel+="VonBert_K_"+GenderLbl(gg)+"_GP_"+NumLbl(gp);
        ParmLabel+="Richards_"+GenderLbl(gg)+"_GP_"+NumLbl(gp);
        ParCount+=4;
        break;
      }
      case 3:
      {
        ParmLabel+="A_zero_"+GenderLbl(gg)+"_GP_"+NumLbl(gp);
        ParmLabel+="Linf_"+GenderLbl(gg)+"_GP_"+NumLbl(gp);
        ParmLabel+="VonBert_K_"+GenderLbl(gg)+"_GP_"+NumLbl(gp);
        ParCount+=3;
        break;
      }
    }
    ParmLabel+="CV_young_"+GenderLbl(gg)+"_GP_"+NumLbl(gp);
    ParmLabel+="CV_old_"+GenderLbl(gg)+"_GP_"+NumLbl(gp);
    ParCount+=2;
  }
  N_MGparm+= 2*gender+2+2; // add for wt-len(by gender), mat-len parms; eggs
  ParCount+=6;
  ParmLabel+="Wtlen_1_"+GenderLbl(1);
  ParmLabel+="Wtlen_2_"+GenderLbl(1);
  ParmLabel+="Mat50%_"+GenderLbl(1);
  ParmLabel+="Mat_slope_"+GenderLbl(1);
  if(Fecund_Option==1)
  {
    ParmLabel+="Eg/gm_inter_"+GenderLbl(1);
    ParmLabel+="Eg/gm_slope_wt_"+GenderLbl(1);
  }
  else if(Fecund_Option==2)
  {
     ParmLabel+="Eggs_scalar_"+GenderLbl(1);
     ParmLabel+="Eggs_exp_len_"+GenderLbl(1);
  }
  else if(Fecund_Option>=3)
  {
     ParmLabel+="Eggs_scalar_"+GenderLbl(1);
     ParmLabel+="Eggs_exp_wt_"+GenderLbl(1);
  }


  if(gender==2)
  {
    ParCount+=2;
    ParmLabel+="Wtlen_1_"+GenderLbl(2);
    ParmLabel+="Wtlen_2_"+GenderLbl(2);
  }

//        recr_dist_pattern(gp,birthseas,p)=1;

  N_MGparm+=N_GP+pop+nseas;         // add for the assignment to areas
  for(k=1;k<=N_GP;k++) {ParCount++; ParmLabel+="RecrDist_GP_"+NumLbl(k);}
  for(k=1;k<=pop;k++)  {ParCount++; ParmLabel+="RecrDist_Area_"+NumLbl(k);}
  for(k=1;k<=nseas;k++){ParCount++; ParmLabel+="RecrDist_Seas_"+NumLbl(k);}

  if(recr_dist_inx==1)
    {
      N_MGparm+=N_GP*pop*nseas;  // add for the morph assignments within each area
      for(gp=1;gp<=N_GP;gp++)
      for(s=1;s<=nseas;s++)
      for(p=1;p<=pop;p++)
      {ParCount++; ParmLabel+="RecrDist_interaction_GP_"+NumLbl(gp)+"_seas_"+NumLbl(s)+"_area_"+NumLbl(p);}
    }
  N_MGparm++;  MGP_CGD=N_MGparm;             // add 1 parameter for cohort-specific growth parameter
  ParCount++; ParmLabel+="CohortGrowDev";

  if(do_migration>0)
  {
    N_MGparm+=2*do_migration;
   for(k=1;k<=do_migration;k++)
     {
     s=move_def(k,1); gp=move_def(k,2); p=move_def(k,3); p2=move_def(k,4);
     ParCount++; ParmLabel+="MoveParm_A_seas_"+NumLbl(s)+"_GP_"+NumLbl(gp)+"from_"+NumLbl(p)+"to_"+NumLbl(p2);
     ParCount++; ParmLabel+="MoveParm_B_seas_"+NumLbl(s)+"_GP_"+NumLbl(gp)+"from_"+NumLbl(p)+"to_"+NumLbl(p2);
    }
  }
 END_CALCS

  init_matrix MGparm_1(1,N_MGparm,1,14)   // matrix with natmort and growth parms controls
  ivector MGparm_offset(1,N_MGparm)

 LOCAL_CALCS
  echoinput<<" Mort and Growth parameter setup"<<endl;
  for(i=1;i<=N_MGparm;i++)
  echoinput<<i<<" "<<MGparm_1(i)<<" "<<ParmLabel(ParCount-N_MGparm+i)<<endl;
//  find MGparms for which the male parameter value is set equal to the female value
//  only applies for MGparm_def==1 which is direct estimation (no offsets)
//  only for the natmort and growth parameters (not wtlen, fecundity, movement, recr distribution)
  MGparm_offset.initialize();
  if(MGparm_def==1)
  {
    Ip=0;
    for (gp=1;gp<=N_GP*gender;gp++)
    {
      if(gp>1)
      {
        for(j=1;j<=MGparm_per_def;j++)
        {
          if(MGparm_1(Ip+j,3)==0.0 && MGparm_1(Ip+j,7)<0) MGparm_offset(Ip+j)=Ip+j-N_GP*MGparm_per_def;  // value is zero and not estimated
        }
      }
      Ip+=MGparm_per_def;
    }
  }
 END_CALCS

//  ProgLabel_1070  set up environmental linkage for MG parms
  int N_MGparm_env                            //  number of MGparms that use env linkage
  int customMGenvsetup  //  0=read one setup (if necessary) and apply to all; 1=read each
  ivector MGparm_env(1,N_MGparm)
  ivector mgp_type(1,N_MGparm)

 LOCAL_CALCS
   time_vary_MG.initialize();    // stores years to calc non-constant MG parms (1=natmort; 2=growth; 3=wtlen & fec; 4=recr_dist; 5=movement)
//   time_vary_MG(styr,0)=1;
//   time_vary_MG(styr,2)=1;
   CGD=0;
   k=1;
   for(f=1;f<=N_GP*gender;f++)
   {
     mgp_type(k,k+N_natMparms-1)=1; // natmort parms
     k+=N_natMparms;
//     mgp_type(k,k+4)=2;  // growth parms
//     k=k+5;
     mgp_type(k,k+N_growparms)=2;  // growth parms
     k=k+N_growparms;
   }
   mgp_type(k,k+5)=3;k=k+6;   // female wtlen and fecundity
   if(gender==2) mgp_type(k,k+1)=3; k=k+2;  // male wt-len
   mgp_type(k,MGP_CGD-1)=4;   // recruit apportionments
   mgp_type(MGP_CGD)=2;   // cohort growth dev
   if(do_migration>0)  mgp_type(MGP_CGD+1,N_MGparm)=5;

   MGparm_env.initialize();   //  will store the index of environ fxns here
   N_MGparm_env=0;
   for (f=1;f<=N_MGparm;f++)
   {
    if(MGparm_1(f,8)>=1)
    {
     N_MGparm_env ++;  MGparm_env(f)=N_MGparm+N_MGparm_env;
     ParCount++; ParmLabel+=ParmLabel(f)+"_ENV";

     if(f==MGP_CGD) CGD=1;    // cohort growth dev is a fxn of environ, so turn on CGD calculation
     for(y=styr;y<=endyr;y++)
     {
      if(env_data_RD(y,MGparm_1(f,8))!=0.0 || MGparm_1(f,8)<0) {time_vary_MG(y,mgp_type(f))=1; time_vary_MG(y+1,mgp_type(f))=1; }
      //       non-zero data were read    or fxn uses biomass or recruitment
     }
    }
   }

  if(N_MGparm_env>0)
  {
    *(ad_comm::global_datafile) >> customMGenvsetup;
    if(customMGenvsetup==0) {k1=1;} else {k1=N_MGparm_env;}
   echoinput<<customMGenvsetup<<" customMGenvsetup"<<endl;
  }
  else
  {customMGenvsetup=0; k1=0;
   echoinput<<" no mgparm env links, so don't read customMGenvsetup"<<endl;
    }
 END_CALCS
  init_matrix MGparm_env_1(1,k1,1,7)
  !!if(N_MGparm_env>0) echoinput<<" MGparm-env setup "<<endl<<MGparm_env_1<<endl;


//  ProgLabel_1072  set up block for MG parms
  int N_MGparm_blk                            // number of MGparms that use blocks
  imatrix Block_Defs_MG(1,N_MGparm,styr,endyr+1)

 LOCAL_CALCS
  Block_Defs_MG.initialize();
  N_MGparm_blk=0;  // counter for assigned parms
  for(j=1;j<=N_MGparm;j++)
  {
   z=MGparm_1(j,13);    // specified block definition
   if(z>N_Block_Designs) {N_warn++; warning<<" ERROR, Block > N Blocks "<<z<<" "<<N_Block_Designs<<endl;}
   if(z>0)
   {
    g=1;
    for(a=1;a<=Nblk(z);a++)
    {
      N_MGparm_blk++;
      y=Block_Design(z,g);
      time_vary_MG(y,mgp_type(j))=1;
//      _itoa( y, onenum, 10 );
      sprintf(onenum, "%d", y);
      ParCount++; ParmLabel+=ParmLabel(j)+"_BLK_"+onenum+CRLF(1);
      y=Block_Design(z,g+1)+1;  // first year after block
      if(y>endyr+1) y=endyr+1;
      time_vary_MG(y,mgp_type(j))=1;
     for(y=Block_Design(z,g);y<=Block_Design(z,g+1);y++)  // loop years for this block
     {
      Block_Defs_MG(j,y)=N_MGparm+N_MGparm_env+N_MGparm_blk;
     }
     g+=2;
    }
    cout<<"Block definitions for MGparms"<<endl<<Block_Defs_MG(j)<<endl;
    if(j==MGP_CGD) CGD=1;
   }
  }
 END_CALCS

  int customblocksetup_MG  //  0=read one setup and apply to all; 1=read each
 LOCAL_CALCS
  if(N_MGparm_blk>0)
  {
    *(ad_comm::global_datafile) >> customblocksetup_MG;
    if(customblocksetup_MG==0) {k1=1;} else {k1=N_MGparm_blk;}
    echoinput<<customblocksetup_MG<<" customblocksetup_MG"<<endl;
  }
  else
  {customblocksetup_MG=0; k1=0;
    echoinput<<" no mgparm blocks, so don't read customblocksetup_MG"<<endl;
    }
 END_CALCS
  init_matrix MGparm_blk_1(1,k1,1,7)  // read matrix that defines the block parms
  !!if(N_MGparm_blk>0) echoinput<<" MGparm-blk setup "<<endl<<MGparm_blk_1<<endl;

//  ProgLabel_1073  set up seasonal effects for MG parms
  init_ivector MGparm_seas_effects(1,10)  // femwtlen1, femwtlen2, mat1, mat2, fec1 fec2 Malewtlen1, malewtlen2 L1 K
  int MGparm_doseas
  int N_MGparm_seas                            // number of MGparms that use seasonal effects
 LOCAL_CALCS
   echoinput<<MGparm_seas_effects<<" MGparm_seas_effects"<<endl;
  adstring_array MGseasLbl;
  MGseasLbl+="F-WL1"+CRLF(1);
  MGseasLbl+="F-WL2"+CRLF(1);
  MGseasLbl+="F-Mat1"+CRLF(1);
  MGseasLbl+="F-Mat1"+CRLF(1);
  MGseasLbl+="F-Fec1"+CRLF(1);
  MGseasLbl+="F-Fec1"+CRLF(1);
  MGseasLbl+="M-WL1"+CRLF(1);
  MGseasLbl+="M-WL2"+CRLF(1);
  MGseasLbl+="L1"+CRLF(1);
  MGseasLbl+="VBK"+CRLF(1);
  MGparm_doseas=sum(MGparm_seas_effects);
  N_MGparm_seas=0;  // counter for assigned parms
  if(MGparm_doseas>0)
  {
    for(j=1;j<=10;j++)
    {
      if(MGparm_seas_effects(j)>0)
      {
        MGparm_seas_effects(j)=N_MGparm+N_MGparm_env+N_MGparm_blk+N_MGparm_seas;  // store base parameter count
        for(s=1;s<=nseas;s++)
        {
          N_MGparm_seas++; ParCount++; ParmLabel+=MGseasLbl(j)+"_seas_"+NumLbl(s);
        }
      }
    }
  }
  cout<<" reading mgparmseas "<<N_MGparm_seas<<endl;
 END_CALCS
  init_matrix MGparm_seas_1(1,N_MGparm_seas,1,7)  // read matrix that defines the seasonal parms
  !!if(N_MGparm_seas>0) echoinput<<" MGparm_seas"<<endl<<MGparm_seas_1<<endl;
  int N_MGparm2
  !!N_MGparm2=N_MGparm+N_MGparm_env+N_MGparm_blk+N_MGparm_seas;
  vector MGparm_LO(1,N_MGparm2)
  vector MGparm_HI(1,N_MGparm2)
  vector MGparm_RD(1,N_MGparm2)
  vector MGparm_PR(1,N_MGparm2)
  ivector MGparm_PRtype(1,N_MGparm2)
  vector MGparm_CV(1,N_MGparm2)
  ivector MGparm_PH(1,N_MGparm2)

 LOCAL_CALCS
   MG_active=0;   // initializes
   for (f=1;f<=N_MGparm;f++)
   {
    MGparm_LO(f)=MGparm_1(f,1);
    MGparm_HI(f)=MGparm_1(f,2);
    MGparm_RD(f)=MGparm_1(f,3);
    MGparm_PR(f)=MGparm_1(f,4);
    MGparm_PRtype(f)=MGparm_1(f,5);
    MGparm_CV(f)=MGparm_1(f,6);
    MGparm_PH(f)=MGparm_1(f,7);
    if(MGparm_PH(f)>0)
      {
      MG_active(mgp_type(f))=1;
      }
   }
   if(natM_type==2 && MG_active(2)>0) MG_active(1)=1;  // lorenzen M depends on growth

   j=N_MGparm;
   if(N_MGparm_env>0)
   {
    for (f=1;f<=N_MGparm_env;f++)
    {
     j++;
     if(customMGenvsetup==0) {k=1;}
     else {k=f;}

    MGparm_LO(j)=MGparm_env_1(k,1);
     MGparm_HI(j)=MGparm_env_1(k,2);
     MGparm_RD(j)=MGparm_env_1(k,3);
     MGparm_PR(j)=MGparm_env_1(k,4);
     MGparm_PRtype(j)=MGparm_env_1(k,5);
     MGparm_CV(j)=MGparm_env_1(k,6);
     MGparm_PH(j)=MGparm_env_1(k,7);
    }
   }

   if(N_MGparm_blk>0)
   for (f=1;f<=N_MGparm_blk;f++)
   {
    j++;
    if(customblocksetup_MG==0) k=1;
    else k=f;
    MGparm_LO(j)=MGparm_blk_1(k,1);
    MGparm_HI(j)=MGparm_blk_1(k,2);
    MGparm_RD(j)=MGparm_blk_1(k,3);
    MGparm_PR(j)=MGparm_blk_1(k,4);
    MGparm_PRtype(j)=MGparm_blk_1(k,5);
    MGparm_CV(j)=MGparm_blk_1(k,6);
    MGparm_PH(j)=MGparm_blk_1(k,7);
   }

   if(N_MGparm_seas>0)
   for (f=1;f<=N_MGparm_seas;f++)
   {
    j++;
    MGparm_LO(j)=MGparm_seas_1(f,1);
    MGparm_HI(j)=MGparm_seas_1(f,2);
    MGparm_RD(j)=MGparm_seas_1(f,3);
    MGparm_PR(j)=MGparm_seas_1(f,4);
    MGparm_PRtype(j)=MGparm_seas_1(f,5);
    MGparm_CV(j)=MGparm_seas_1(f,6);
    MGparm_PH(j)=MGparm_seas_1(f,7);
   }
 END_CALCS

//  ProgLabel_1074  set up random deviations for MG parms
  int N_MGparm_dev                            //  number of MGparms that use annual deviations
 LOCAL_CALCS
    N_MGparm_dev=0;
    for(f=1;f<=N_MGparm;f++)
    {
    if(MGparm_1(f,9)>=1) N_MGparm_dev ++;
    }
//    if(N_MGparm_dev>0) j=N_MGparm_dev; else j=1;    // for defining non-zero array size
 END_CALCS

  ivector MGparm_dev_minyr(1,N_MGparm_dev)
  ivector MGparm_dev_maxyr(1,N_MGparm_dev)
  vector  MGparm_dev_stddev(1,N_MGparm_dev)
  int MGparm_dev_PH
 LOCAL_CALCS
   int N_MGparm_dev_tot=0;
   if(N_MGparm_dev>0)
     {
       cout<<" do mgparm dev"<<endl;
       j=0;
       for (f=1;f<=N_MGparm;f++)
       {
       if(MGparm_1(f,9)>=1)
         {
          j++;
         MGparm_1(f,9)=j;
         MGparm_dev_stddev(j)=MGparm_1(f,12);

         y=MGparm_1(f,10);
         if(y<styr)
          {
            N_warn++; warning<<" reset MGparm_dev start year to styr for MGparm: "<<f<<" "<<y<<endl;
            y=styr;
          }
         MGparm_dev_minyr(j)=y;

         y=MGparm_1(f,11);
         if(y>endyr+1)
          {
            N_warn++; warning<<" reset MGparm_dev end year to endyr+1 for MGparm: "<<f<<" "<<y<<endl;
            y=endyr+1;
          }
         MGparm_dev_maxyr(j)=y;
         for(y=MGparm_dev_minyr(j);y<=MGparm_dev_maxyr(j);y++)
         {
           time_vary_MG(y,mgp_type(f))=1;
           if(y<=endyr) time_vary_MG(y+1,mgp_type(f))=1;
//           _itoa(y,onenum,10);
           sprintf(onenum, "%d", y);
           N_MGparm_dev_tot++;
           ParCount++; ParmLabel+=ParmLabel(f)+"_DEV_"+onenum+CRLF(1);
        }
         if(f==MGP_CGD) CGD=1;
         }
       }
       *(ad_comm::global_datafile) >> MGparm_dev_PH;
       echoinput<<MGparm_dev_PH<<" MGparm_dev_PH"<<endl;
     }
     else
     {
      MGparm_dev_PH=-6;
      echoinput<<" don't read MGparm_dev_PH"<<endl;
    }
     // CHECK FOR YEARS AFTER styr in which growth starts to change
     k=endyr+2;
    for(y=styr+1;y<=endyr+1;y++)
    {
      if(time_vary_MG(y,2)>0 && y<k)  k=y;
    }
    if(k<endyr+2)
    {
      for(y=k;y<=endyr+1;y++)
      {
        time_vary_MG(y,2)=1;
      }
    }
    for(y=styr;y<=endyr+1;y++)
    {
      for(f=1;f<=5;f++)
      {
        if(time_vary_MG(y,f)>0)
        {
          MG_active(f)=1;
          time_vary_MG(y,0)=1;  // tracks active status for all MG types
        }
      }
    }
    MG_active(0)=sum(MG_active(1,5));
 END_CALCS

//**************************************
//  ProgLabel_1080  read setup for SR parameters
// read setup for SR parameters:  LO, HI, INIT, PRIOR, PRtype, CV, PHASE
  init_int SR_fxn
  !!echoinput<<SR_fxn<<" SR_fxn "<<endl;
  init_matrix SR_parm_1(1,6,1,7)
  !!echoinput<<" SR parms "<<endl<<SR_parm_1<<endl;
  init_int SR_env_link
  !!echoinput<<SR_env_link<<" SR_env_link "<<endl;
  init_int SR_env_target_RD   // 0=none; 1=devs; 2=R0; 3=steepness
  !!echoinput<<SR_env_target_RD<<" SR_env_target_RD "<<endl;
  int SR_env_target
  int SR_autocorr;  // will be calculated later

  vector SRvec_LO(1,6)
  vector SRvec_HI(1,6)
  ivector SRvec_PH(1,6)

 LOCAL_CALCS
   SRvec_LO=column(SR_parm_1,1);
   SRvec_HI=column(SR_parm_1,2);
   SRvec_PH=ivector(column(SR_parm_1,7));
   if(SR_env_link>N_envvar)
   {
     N_warn++;
     warning<<" ERROR:  SR_env_link ( "<<SR_env_link<<" ) was set greater than the highest numbered environmental index ( "<<N_envvar<<" )"<<endl;
     cout<<" exit, see warnng.sso"<<endl;
     exit(1);
   }
   SR_env_target=SR_env_target_RD;
   if(SR_env_link==0) SR_env_target=0;
   if(SR_env_link==0 && SR_env_target_RD>0)
   {N_warn++; warning<<" WARNING:  SR_env_target was set, but no SR_env_link selected, SR_env_target set to 0"<<endl;}
  ParmLabel+="SR_R0";
  ParmLabel+="SR_steep";
  ParmLabel+="SR_sigmaR";
  ParmLabel+="SR_envlink";
  ParmLabel+="SR_R1_offset";
  ParmLabel+="SR_autocorr";
  ParCount+=6;
 END_CALCS

  init_int do_recdev  //  0=none; 1=devvector; 2=simple deviations
  !!echoinput<<do_recdev<<" do_recdev"<<endl;
  init_int recdev_start;
  !!echoinput<<recdev_start<<" recdev_start"<<endl;
  init_int recdev_end;
  !!echoinput<<recdev_end<<" recdev_end"<<endl;
  init_int recdev_PH;
  !!echoinput<<recdev_PH<<" recdev_PH"<<endl;
  init_int recdev_adv
  !!echoinput<<recdev_adv<<" recdev_adv"<<endl;

  init_vector recdev_options(1,11*recdev_adv)
  !!if( recdev_adv>0) echoinput<<recdev_options<<" advanced options "<<endl;
  int recdev_early_start_rd
  int recdev_early_start
  int recdev_early_end
  int recdev_first
  int recdev_early_PH
  int fore_recr_PH
  int fore_recr_PH2
  number fore_recr_lambda
  vector recdev_adj(1,4)
  int recdev_do_early
  int recdev_read
  number recdev_LO;
  number recdev_HI;
  ivector recdev_doit(styr-nages,endyr+1)
 LOCAL_CALCS
  recdev_doit=0;
  if(recdev_adv==1)
  {
    recdev_early_start_rd=recdev_options(1);
    recdev_early_PH=recdev_options(2);
    fore_recr_PH=recdev_options(3);
    fore_recr_lambda=recdev_options(4);
    recdev_adj(1)=recdev_options(5);
    recdev_adj(2)=recdev_options(6);
    recdev_adj(3)=recdev_options(7);
    recdev_adj(4)=recdev_options(8);
    recdev_LO=recdev_options(9);
    recdev_HI=recdev_options(10);
    recdev_read=recdev_options(11);
  }
  else
  {
    recdev_early_start_rd=0;   // 0 means no early
    recdev_early_end=-1;
    recdev_early_PH=-4;
    fore_recr_PH=0;  // so will be reset to maxphase+1
    fore_recr_lambda=1.;
    recdev_adj(1)=double(styr)-1000.;
    recdev_adj(2)=styr-nages;
    recdev_adj(3)=recdev_end;
    recdev_adj(4)=double(endyr)+1.;
    recdev_LO=-5;
    recdev_HI=5;
    recdev_read=0;
  }
  recdev_early_start=recdev_early_start_rd;
 END_CALCS

  vector biasadj(styr-nages,YrMax)

 LOCAL_CALCS
  if(recdev_end>retro_yr) recdev_end=retro_yr;
  if(recdev_start<(styr-nages)) {recdev_start=styr-nages; N_warn++; warning<<" adjust recdev_start to: "<<recdev_start<<endl;}
  recdev_first=recdev_start;   // stores first recdev, whether from the early period or the standard dev period

  if(recdev_early_start==0)  // do not do early rec devs
  {
    recdev_do_early=0;
    recdev_early_end=-1;
    if(recdev_early_PH>0) recdev_early_PH=-recdev_early_PH;
  }
  else
  {
    if(recdev_early_start<0) recdev_early_start+=recdev_start;  // do relative to start of recdevs
    recdev_do_early=1;
    if(recdev_early_start<(styr-nages)) {recdev_early_start=styr-nages; N_warn++; warning<<" adjust recdev_early to: "<<recdev_early_start<<endl;}
    recdev_first=recdev_early_start;
    recdev_early_end=recdev_start-1;
    for(y=recdev_early_start;y<=recdev_early_end;y++)
    {
      ParCount++;
      recdev_doit(y)=1;
      if(y>=styr)
      {
//      _itoa(y,onenum,10);
      sprintf(onenum, "%d", y);
      ParmLabel+="Early_RecrDev_"+onenum+CRLF(1);
    }
    else
      {
        onenum="    ";
//      _itoa(styr-y,onenum,10);
      sprintf(onenum, "%d", styr-y);
      ParmLabel+="InitAgeComp_"+onenum+CRLF(1);
    }

    }
  }

  if(SR_fxn!=4)
  {
  for (y=styr-nages; y<=YrMax; y++)
    {
      if(y<=recdev_first)
      {biasadj(y)=0.;}
    else if(y<=recdev_adj(1))
      {biasadj(y)=0.;}
    else if (y<=recdev_adj(2))
      {biasadj(y)=(y-recdev_adj(1)) / (recdev_adj(2)-recdev_adj(1));}
    else if (y<=recdev_adj(3))
      {biasadj(y)=1.;}
    else if (y<=recdev_adj(4))
      {biasadj(y)=1.-(y-recdev_adj(3)) / (recdev_adj(4)-recdev_adj(3));}
    else
      {biasadj(y)=0.;}
    }
  }
  else
  {
    biasadj=0.0;
  }
  if(do_recdev>0)
  {
  for(y=recdev_start;y<=recdev_end;y++)
  {
    ParCount++;
    recdev_doit(y)=1;

      if(y>=styr)
      {
//      _itoa(y,onenum,10);
      sprintf(onenum, "%d", y);
      ParmLabel+="RecrDev_"+onenum+CRLF(1);
    }
    else
      {
        onenum="    ";
//      _itoa(styr-y,onenum,10);
      sprintf(onenum, "%d", styr-y);
      ParmLabel+="InitAgeComp_"+onenum+CRLF(1);
    }
  }
  }

  if(Do_Forecast>0)
  {
    for(y=recdev_end+1;y<=YrMax;y++)
    {
//      _itoa(y,onenum,10);
      sprintf(onenum, "%d", y);
      ParCount++; ParmLabel+="ForeRecr_"+onenum+CRLF(1);
    }
  }
 END_CALCS
  init_matrix recdev_input(1,recdev_read,1,2);
  !!if(recdev_read>0) echoinput<<"recruitment deviation input "<<endl<<recdev_input<<endl;

// Input F quantities
  init_number F_ballpark
  init_int F_ballpark_yr
  init_int F_Method;           // 1=Pope's; 2=continuouos F; 3=hybrid
  init_number max_harvest_rate
  number Equ_F_joiner

 LOCAL_CALCS
    echoinput<<F_ballpark<<" F ballpark "<<endl;
    echoinput<<F_ballpark_yr<<" F_ballpark_yr (<0 to ignore)  "<<endl;
    echoinput<<F_Method<<" F_Method "<<endl;
    echoinput<<max_harvest_rate<<" max_harvest_rate "<<endl;
  if(F_Method<1 || F_Method>3)
    {
      N_warn++;
    warning<<" ERROR:  F_Method must be 1 or 2 or 3, value is: "<<F_Method<<endl;
    cout<<" exit, see warnng.sso"<<endl;
    exit(1);
    }
   if(F_Method==1)
   {
     k=-1;
     Equ_F_joiner=(log(1./max_harvest_rate -1.))/(max_harvest_rate-0.2);  //  used to spline the harvest rate
     if(max_harvest_rate>0.999)
     {N_warn++; cout<<" fatal error "<<endl; warning<<" max harvest rate must  be <1.0 for F_method 1 "<<max_harvest_rate<<endl; exit(1);}
     if(max_harvest_rate<=0.30)
     {N_warn++; warning<<" unexpectedly small value for max harvest rate for F_method 1:  "<<max_harvest_rate<<endl;}
   }
   else
   {
     if(max_harvest_rate<1.0)
     {N_warn++; warning<<" max harvest rate should be >1.0 for F_method 2 or 3 "<<max_harvest_rate<<endl;}
     if(F_Method==2)
     {k=3;}
     else if (F_Method==3)
     {k=1;}
   }
 END_CALCS

  init_vector F_setup(1,k)
// setup for F_rate with F_Method=2
// F_setup(1) = overall initial value
// F_setup(2) = overall phase
// F_setup(3) = number of specific initial values and phases to read
  int F_detail
  int F_Tune
 LOCAL_CALCS
  if(F_Method==2)
  {
    echoinput<<F_setup<<" initial F value, F phase, N_detailed Fsetups to read "<<endl;
    F_detail=F_setup(3);
  }
  else
  {
    F_detail=-1;
    if(F_Method==3)
    {
      F_Tune=F_setup(1);
      echoinput<<F_Tune<<" N iterations for tuning hybrid F "<<endl;
    }
  }
 END_CALCS

  init_matrix F_setup2(1,F_detail,1,6)  // fleet, yr, seas, Fvalue, se, phase
  !!echoinput<<" detailed F_setups "<<endl<<F_setup2<<endl;

//  ProgLabel_1090  read setup for init_F parameters
  init_matrix init_F_parm_1(1,Nfleet,1,7)
  !! echoinput<<" initial equil F parameter setup"<<endl<<init_F_parm_1<<endl;
  vector init_F_LO(1,Nfleet)
  vector init_F_HI(1,Nfleet)
  vector init_F_RD(1,Nfleet)
  vector init_F_PR(1,Nfleet)
  vector init_F_PRtype(1,Nfleet)
  vector init_F_CV(1,Nfleet)
  ivector init_F_PH(1,Nfleet)

 LOCAL_CALCS
   init_F_LO=column(init_F_parm_1,1);
   init_F_HI=column(init_F_parm_1,2);
   init_F_RD=column(init_F_parm_1,3);
   init_F_PR=column(init_F_parm_1,4);
   init_F_PRtype=column(init_F_parm_1,5);
   init_F_CV=column(init_F_parm_1,6);
   init_F_PH=ivector(column(init_F_parm_1,7));
   for (f=1;f<=Nfleet;f++)
     {
      ParCount++; ParmLabel+="InitF_"+NumLbl(f)+fleetname(f);
      if(obs_equ_catch(f)<=0.0)
      {
        if(init_F_RD(f)>0.0)
        {
          N_warn++;
          warning<<f<<" catch: "<<obs_equ_catch(f)<<" initF: "<<init_F_RD(f)<<" initF is reset to be 0.0"<<endl;
        }
        init_F_RD(f)=0.0; init_F_PH(f)=-1;
        }
      if(obs_equ_catch(f)>0.0 && init_F_RD(f)<=0.0)
       {N_warn++; cout<<" exit - see warning "<<endl;
        warning<<f<<" catch: "<<obs_equ_catch(f)<<" initF: "<<init_F_RD(f)<<" initF must be >0"<<endl; exit(1);}
     }

   cout<<" Done with init F "<<init_F_parm_1<<endl;

  if(F_Method==2)
  {
    for(f=1;f<=Nfleet;f++)
    for(y=styr;y<=endyr;y++)
    for(s=1;s<=nseas;s++)
    {
//      _itoa(y,onenum,10);
      sprintf(onenum, "%d", y);
      ParCount++;
      ParmLabel+="F_fleet_"+NumLbl(f)+"_YR_"+onenum+"_s_"+NumLbl(s)+CRLF(1);
    }
      g=0;
      for(f=1;f<=Nfleet;f++)
      for(y=styr;y<=endyr;y++)
      for(s=1;s<=nseas;s++)
      {
        t=styr+(y-styr)*nseas+s-1;
        g++;
        if(catch_ret_obs(f,t)>0.)
        {
          have_catch(g)=F_setup(2);
        }
        else
        {
          have_catch(g)=-1;
        }
      }
      if(F_detail>0)
      {
        for(k=1;k<=F_detail;k++)
        {
          f=F_setup2(k,1); y=F_setup2(k,2); s=F_setup2(k,3);
          g=(f-1)*(TimeMax-styr+1)+(y-styr)*nseas+s;
          t=styr+(y-styr)*nseas+s-1;
          if(F_setup2(k,6)!=-999) have_catch(g)=F_setup2(k,6);    //   used to setup the phase for F_rate
          if(F_setup2(k,5)!=-999) catch_se(t,f)=F_setup2(k,5);    //    reset the se for this observation
          //  setup of F_rate values occurs later in the parameter section
        }
      }
  }
 END_CALCS


//***********************************
//  ProgLabel_1100  read catchability setup
  init_matrix Q_setup(1,Ntypes,1,6)  // do power, env-var,  extra sd, devtype(<0=mirror, 0/1=none, 2=cons, 3=rand, 4=randwalk); num/bio, err_type(0=lognormal, >=1 is T-dist-lognormal)
                                        // change to matrix because devstd has real, not integer, values
  int Q_Npar2
  int Q_Npar
  int ask_detail

  imatrix Q_setup_parms(1,Ntypes,1,4)
 LOCAL_CALCS
  echoinput<<" Q setup "<<endl<<Q_setup<<endl;
  Q_Npar=0;
  ask_detail=0;
// creates index to the list of parameters
  for (f=1;f<=Ntypes;f++)
  {Q_setup_parms(f,1)=0;
   if(Q_setup(f,1)>0)
    {
      Q_Npar++; Q_setup_parms(f,1)=Q_Npar;
      ParCount++; ParmLabel+="Q_power_"+NumLbl(f)+"_"+fleetname(f);
    }
  }
  for (f=1;f<=Ntypes;f++)
  {
    Q_setup_parms(f,2)=0;
    if(Q_setup(f,2)>0)
      {
        Q_Npar++; Q_setup_parms(f,2)=Q_Npar;
        ParCount++; ParmLabel+="Q_envlink_"+NumLbl(f)+"_"+fleetname(f);
       }
  }
  for (f=1;f<=Ntypes;f++)
  {
    Q_setup_parms(f,3)=0;
    if(Q_setup(f,3)>0)
    {
      Q_Npar++; Q_setup_parms(f,3)=Q_Npar;
      ParCount++; ParmLabel+="Q_extraSD_"+NumLbl(f)+"_"+fleetname(f);
    }
  }
  Q_Npar2=Q_Npar;
  for (f=1;f<=Ntypes;f++)
  {
    Q_setup_parms(f,4)=0;
    if(Q_setup(f,4)>=2)
    {
      Q_Npar++; Q_Npar2++; Q_setup_parms(f,4)=Q_Npar;
      ParCount++; ParmLabel+="Q_base_"+NumLbl(f)+"_"+fleetname(f);
      if(Q_setup(f,4)==3)
      {
        ask_detail=1;
        Q_Npar2++;
        Q_Npar+=nyr_cr(f);
        for(j=1;j<=nyr_cr(f);j++)
        {
          y=yr_cr_y(f,j);
          ParCount++;
//          _itoa(y,onenum,10);
          sprintf(onenum, "%d", y);
          onenum+=CRLF(1);
          ParmLabel+="Q_dev_"+NumLbl(f)+"y_"+onenum;
        }
      }
      if(Q_setup(f,4)==4)
      {
        ask_detail=1;
        Q_Npar2++;
        Q_Npar+=nyr_cr(f)-1;
        for(j=2;j<=nyr_cr(f);j++)
        {
          y=yr_cr_y(f,j);
          ParCount++;
//          _itoa(y,onenum,10);
          sprintf(onenum, "%d", y);
          onenum+=CRLF(1);
          ParmLabel+="Q_walk_"+NumLbl(f)+"y_"+onenum;
        }
      }
    }
  }

  if(Q_Npar>0)
    {k=Q_Npar;}
  else
    {k=1;}
 END_CALCS

  vector Q_parm_LO(1,k)
  vector Q_parm_HI(1,k)
  ivector Q_parm_PH(1,k)

  int Q_parm_detail
  !! if(ask_detail>0) {*(ad_comm::global_datafile) >> Q_parm_detail;} else {Q_parm_detail=0;}
  !! if(Q_parm_detail==1) {j=Q_Npar;} else {j=Q_Npar2;}
    matrix Q_parm_1(1,Q_Npar,1,7)
//  ProgLabel_1104  read catchability parameters as necessary
  init_matrix Q_parm_2(1,j,1,7)
 LOCAL_CALCS
  if(j>0) echoinput<<" Catchability parameters"<<endl<<Q_parm_2<<endl;
  if(Q_parm_detail==0)
  {
    Q_Npar=0;  Q_Npar2=0;
    for (f=1;f<=Ntypes;f++)
    {
     if(Q_setup(f,1)>0)
      {
        Q_Npar++;
        Q_parm_1(Q_Npar)=Q_parm_2(Q_Npar);
      }
    }
    for (f=1;f<=Ntypes;f++)
    {
      if(Q_setup(f,2)>0)
        {
          Q_Npar++;
        Q_parm_1(Q_Npar)=Q_parm_2(Q_Npar);
         }
    }
    for (f=1;f<=Ntypes;f++)
    {
     if(Q_setup(f,3)>0)
      {
        Q_Npar++;
        Q_parm_1(Q_Npar)=Q_parm_2(Q_Npar);
      }
    }
    Q_Npar2=Q_Npar;
    for (f=1;f<=Ntypes;f++)
    {
      if(Q_setup(f,4)>=2)
      {
        Q_Npar++; Q_Npar2++;
        Q_parm_1(Q_Npar)=Q_parm_2(Q_Npar2);
        if(Q_setup(f,4)==3)
        {
          Q_Npar2++;
          for(j=1;j<=nyr_cr(f);j++)
          {
            Q_Npar++;
            Q_parm_1(Q_Npar)=Q_parm_2(Q_Npar2);
          }
        }
        if(Q_setup(f,4)==4)
        {
          Q_Npar2++;
          for(j=2;j<=nyr_cr(f);j++)
          {
            Q_Npar++;
            Q_parm_1(Q_Npar)=Q_parm_2(Q_Npar2);
          }
        }
      }
    }
  }
  else
  {
    Q_parm_1=Q_parm_2;
  }
 END_CALCS

  !! if(Q_Npar>0 ) echoinput<<" processed Q parms "<<endl<<Q_parm_1<<endl;

 LOCAL_CALCS
   if(Q_Npar>0)
     {
     for(f=1;f<=Q_Npar;f++)
       {
       Q_parm_LO(f)=Q_parm_1(f,1);
       Q_parm_HI(f)=Q_parm_1(f,2);
       Q_parm_PH(f)=Q_parm_1(f,7);
       }
     }
   else
     {Q_parm_LO=-1.; Q_parm_HI=1.; Q_parm_PH=-4;}
 END_CALCS


//******************************************
//  ProgLabel_1120  Define Selectivity types
  ivector seltype_Nparam(0,33)
 LOCAL_CALCS
   seltype_Nparam(0)=0;   // selex=1.0 for all sizes
   seltype_Nparam(1)=2;   // logistic; with 95% width specification
   seltype_Nparam(2)=8;   // double logistic, with defined peak
   seltype_Nparam(3)=6;   // flat middle, power up, power down
   seltype_Nparam(4)=0;   // set size selex=female maturity
   seltype_Nparam(5)=2;   // mirror another selex; PARMS pick the min-max bin to mirror
   seltype_Nparam(6)=2;   // non-parm len selex, additional parm count is in seltype(f,4)
   seltype_Nparam(7)=8;   // New doublelogistic with smooth transitions and constant above Linf option
   seltype_Nparam(8)=8;   // New doublelogistic with smooth transitions and constant above Linf option
   seltype_Nparam(9)=6;   // simple 4-parm double logistic with starting length; parm 5 is first length; parm 6=1 does desc as offset

   seltype_Nparam(10)=0;   //  First age-selex  selex=1.0 for all ages
   seltype_Nparam(11)=2;   //  pick min-max age
   seltype_Nparam(12)=2;   //   logistic
   seltype_Nparam(13)=8;   //   double logistic
   seltype_Nparam(14)=nages+1;   //   empirical
   seltype_Nparam(15)=0;   //   mirror another selex
   seltype_Nparam(16)=2;   //   Coleraine - Gaussian
//   seltype_Nparam(17)=5;   //   Logistic - plus
   seltype_Nparam(17)=nages+1;   //   empirical as random walk
   seltype_Nparam(18)=8;   //   double logistic - smooth transition
   seltype_Nparam(19)=6;   //   simple 4-parm double logistic with starting age
   seltype_Nparam(20)=6;   //   double_normal,using joiners

   seltype_Nparam(21)=8;   //   new size-selec nonparametric
   seltype_Nparam(22)=4;   //   double_normal as in CASAL
   seltype_Nparam(23)=6;   //   double_normal with sel(minL) and sel(maxL), using IF
   seltype_Nparam(24)=6;   //   double_normal with sel(minL) and sel(maxL), using joiners
   seltype_Nparam(25)=0;   //   undefined
   seltype_Nparam(26)=0;   //   undefined
   seltype_Nparam(27)=0;   //   undefined
   seltype_Nparam(28)=0;   //   undefined
   seltype_Nparam(29)=0;   //   undefined
   seltype_Nparam(30)=0;   //   spawning biomass
   seltype_Nparam(31)=0;   //   recruitment dev
   seltype_Nparam(32)=0;   //   pre-recruitment (spawnbio * recrdev)
   seltype_Nparam(33)=0;   //   recruitment

 END_CALCS

//  ProgLabel_1124  read selectivity definitions
//  do 2*Ntypes to create options for size-selex (first), then age-selex
  init_imatrix seltype(1,2*Ntypes,1,4)    // read selex type for each fleet/survey, Do_retention, Do_male
  !! echoinput<<" selex types "<<endl<<seltype<<endl;
  int N_selparm   // figure out the Total number of selex parameters
  int N_selparm2                 // N selparms plus env links and blocks
  ivector N_selparmvec(1,2*Ntypes)  //  N selparms by type
  ivector MaleSelParm(1,2*Ntypes)
  ivector RetainParm(1,Ntypes)
  int blkparm
  int firstselparm
  int Do_Retain

 LOCAL_CALCS
   firstselparm=ParCount;
   N_selparm=0;
   Do_Retain=0;
   for (f=1;f<=Ntypes;f++)
   {
     N_selparmvec(f)=seltype_Nparam(seltype(f,1));   // N Length selex parms
     if(seltype(f,1)==6) N_selparmvec(f) +=seltype(f,4);  // special setup of N parms
     for(j=1;j<=N_selparmvec(f);j++)
     {
       ParCount++; ParmLabel+="SizeSel_"+NumLbl(f)+"P_"+NumLbl(j)+"_"+fleetname(f);
     }

     if(seltype(f,2)>=1)
     {
       Do_Retain=1;
       RetainParm(f)=N_selparmvec(f)+1;
       N_selparmvec(f) +=4*seltype(f,2);          // N retention parms first 4 for retention; next 4 for mortality
       for(j=1;j<=4;j++)
       {
         ParCount++; ParmLabel+="Retain_"+NumLbl(f)+"P_"+NumLbl(j)+"_"+fleetname(f);
       }
       if(seltype(f,2)==2)
       {
         for(j=1;j<=4;j++)
         {
           ParCount++; ParmLabel+="DiscMort_"+NumLbl(f)+"P_"+NumLbl(j)+"_"+fleetname(f);
         }
       }
     }
     if(seltype(f,3)>=1)
      {
        MaleSelParm(f)=N_selparmvec(f)+1;
        N_selparmvec(f) +=4;  // add male parms
        for(j=1;j<=4;j++)
        {
          ParCount++; ParmLabel+="SizeSelMale_"+NumLbl(f)+"P_"+NumLbl(j)+"_"+fleetname(f);
        }
        if(seltype(f,3)==3)
        {
          if(seltype(f,1)==1 || seltype(f,1)==24)
          {
            // ok
          }
          else
          {
            N_warn++; warning<<" male option 3 only available for selex 1 and selex 24 "<<endl; exit(1);
          }
        }
      }

     if(seltype(f,1)==7) {N_warn++; warning<<"ERROR:  selectivity pattern #7 is no longer supported "<<endl;}
     N_selparm += N_selparmvec(f);
   }
   for (f=Ntypes+1;f<=2*Ntypes;f++)
   {
     N_selparmvec(f)=seltype_Nparam(seltype(f,1));   // N Age selex parms
     for(j=1;j<=N_selparmvec(f);j++)
     {
       ParCount++; ParmLabel+="AgeSel_"+NumLbl(f-Ntypes)+"P_"+NumLbl(j)+"_"+fleetname(f-Ntypes);
    }
     if(seltype(f,3)>=1)
      {
        N_selparmvec(f) +=4;  // add male parms
        for(j=1;j<=4;j++)
        {
          ParCount++; ParmLabel+="AgeSelMale_"+NumLbl(f-Ntypes)+"P_"+NumLbl(j)+"_"+fleetname(f-Ntypes);
        }
      }
     N_selparm += N_selparmvec(f);
   }
   for(f=1;f<=Nfleet;f++)
     {
     if(nyr_disc(f)>0 && seltype(f,2)==0)
       {N_warn++; cout<<" exit - see warning "<<endl; warning<<" ERROR:  discard data exist for fleet "<<f<<"  but retention parms not setup "<<endl; exit(1);}
     else if (nyr_disc(f)==0 && seltype(f,2)!=0)
       {N_warn++; warning<<" WARNING:  no discard amount data for fleet "<<f<<"  but retention parms have been defined "<<endl;}
     }
 END_CALCS

//  ProgLabel_1126  read setup for each selex parameter
  init_matrix selparm_1(1,N_selparm,1,14)
  !!echoinput<<" selex parm setup "<<endl<<selparm_1<<endl;

  imatrix time_vary_sel(styr,endyr+1,1,2*Ntypes)

//  ProgLabel_1128  define environmental linkages for selectivity parameters
  int N_selparm_env                            // number of selparms that use env linkage
  int customenvsetup  //  0=read one setup and apply to all; 1=read each
  ivector selparm_env(1,N_selparm)             //  pointer to parameter with env link for each selparm
 LOCAL_CALCS
  N_selparm_env=0;
  selparm_env=0;
  for(j=1;j<=N_selparm;j++)
  {
    if(selparm_1(j,8)>=1)          // env linkage
    {
      N_selparm_env++; selparm_env(j)=N_selparm+N_selparm_env;
      ParCount++; ParmLabel+=ParmLabel(j+firstselparm)+"_env";
    }
  }

  if(N_selparm_env>0)
  {
    *(ad_comm::global_datafile) >> customenvsetup;
    if(customenvsetup==0) {k1=1;} else {k1=N_selparm_env;}
    echoinput<<customenvsetup<<" customenvsetup"<<endl;
  }
  else
  {customenvsetup=0; k1=0;
    echoinput<<" no envlinks; so don't read customenvsetup"<<endl;
    }
 END_CALCS

  init_matrix selparm_env_1(1,k1,1,7)  // read matrix that sets up the env linkage parms
  !!if(k1>0) echoinput<<" selex-env parameters "<<selparm_env_1<<endl;

//  ProgLabel_1130  define block patterns for selectivity parameters
  int N_selparm_blk                            // number of selparms that use blocks
  imatrix Block_Defs(1,N_selparm,styr,endyr)
  int customblocksetup  //  0=read one setup and apply to all; 1=read each

 LOCAL_CALCS
  Block_Defs.initialize();
  N_selparm_blk=0;  // counter for assigned parms
  for(j=1;j<=N_selparm;j++)
  {
   z=selparm_1(j,13);    // specified block definition
   if(z>N_Block_Designs) {N_warn++; warning<<" ERROR, Block > N Blocks "<<z<<" "<<N_Block_Designs<<endl; exit(1);}
   if(z>0)
   {
    g=1;
    for(a=1;a<=Nblk(z);a++)
    {
     N_selparm_blk++;
     y=Block_Design(z,g);
//     _itoa( y, onenum, 10 );
     sprintf(onenum, "%d", y);
     ParCount++; ParmLabel+=ParmLabel(j+firstselparm)+"_BLK_"+onenum+CRLF(1);
     for(y=Block_Design(z,g);y<=Block_Design(z,g+1);y++)  // loop years for this block
     {
      Block_Defs(j,y)=N_selparm+N_selparm_env+N_selparm_blk;
     }
     g+=2;
    }
   }
  }
  if(N_selparm_blk>0)
  {
    *(ad_comm::global_datafile) >> customblocksetup;
    if(customblocksetup==0) {k1=1;} else {k1=N_selparm_blk;}
    echoinput<<customblocksetup<<" customblocksetup"<<endl;
  }
  else
  {customblocksetup=0; k1=0;
    echoinput<<" no blocks; so don't read customblocksetup"<<endl;
  }
 END_CALCS

  init_matrix selparm_blk_1(1,k1,1,7)  // read matrix that defines the block parms
  !!if(k1>0) echoinput<<"selex block parameters "<<endl<<selparm_blk_1<<endl;

  int N_selparm_dev   // number of selparms that use random deviations
  int N_selparm_dev_tot   // number of selparms that use random deviations
 LOCAL_CALCS
  N_selparm_dev=0;
  N_selparm_dev_tot=0;
  for(j=1;j<=N_selparm;j++)
  {
    if(selparm_1(j,9)>=1)
      {
        N_selparm_dev++;
         for(y=selparm_1(j,10);y<=selparm_1(j,11);y++)
         {
         N_selparm_dev_tot++;
//         _itoa(y,onenum,10);
         sprintf(onenum, "%d", y);
         ParCount++; ParmLabel+=ParmLabel(j+firstselparm)+"_DEV_"+onenum+CRLF(1);
        }
      }
  }
 END_CALCS

  !!N_selparm2=N_selparm+N_selparm_env+N_selparm_blk;
  vector selparm_LO(1,N_selparm2)
  vector selparm_HI(1,N_selparm2)
  vector selparm_RD(1,N_selparm2)
  vector selparm_PR(1,N_selparm2)
  vector selparm_PRtype(1,N_selparm2)
  vector selparm_CV(1,N_selparm2)
  ivector selparm_PH(1,N_selparm2)

 LOCAL_CALCS

// special bound checking
    z=0;  // parameter counter within this section
    for (f=1;f<=Ntypes;f++)
    {
      if(seltype(f,1)==8 || seltype(f,1)==22 || seltype(f,1)==23 || seltype(f,1)==24)
      {
        if(selparm_1(z+1,1)<len_bins_m(2))
        {N_warn++;
          warning<<"Fleet:_"<<f<<" min bound on parameter for size at peak is "<<selparm_1(z+1,1)<<"; should be >= midsize bin 2 ("<<len_bins_m(2)<<")"<<endl;}
        if(selparm_1(z+1,2)>len_bins_m(nlength-1))
        {N_warn++;
          warning<<"Fleet:_"<<f<<" max bound on parameter for size at peak is "<<selparm_1(z+1,2)<<"; should be <= midsize bin N-1 ("<<len_bins_m(nlength-1)<<")"<<endl;}
      }
      z+=N_selparmvec(f);
    }
// end special bound checking



  time_vary_sel.initialize();
  time_vary_sel(styr)=1;
  time_vary_sel(endyr+1)=1;
  for(y=styr+1;y<=endyr;y++)
  {
    z=0;  // parameter counter within this section
    for (f=1;f<=2*Ntypes;f++)
    {
      if(seltype(f,1)==5 || seltype(f,1)==15)   // mirror
      {
        if(f<=Ntypes) {time_vary_sel(y,f)=time_vary_sel(y,seltype(f,4));} else {time_vary_sel(y,f)=time_vary_sel(y,seltype(f,4)+Ntypes);}
        z+=seltype_Nparam(seltype(f,1));
      }
      else
      {
        if(seltype_Nparam(seltype(f,1))>0)      // type has parms, so look for adjustments
        {
          for(j=1;j<=N_selparmvec(f);j++)
          {
            z++;
            if(selparm_1(z,8)>=1)          // env linkage
            {
             if((env_data_RD(y,selparm_1(z,8))!=env_data_RD(y-1,selparm_1(z,8)) || selparm_1(z,8)<0 )) time_vary_sel(y,f)=1;
            }
            if(selparm_1(z,9)>=1)  // dev vector
            {
              s=selparm_1(z,11)+1;
              if(s>endyr) s=endyr;
              if(y>=selparm_1(z,10) && y<=s) time_vary_sel(y,f)=1;
            }
            if(selparm_1(z,13)>=1) //   blocks
            {
              if(Block_Defs(z,y)!=Block_Defs(z,y-1) ) time_vary_sel(y,f)=1;
            }
          }
        }
      }
      if(f<=Ntypes && seltype(f,2)<0)  //  retention is being mirrored
      {
        k=-seltype(f,2);
        if(time_vary_sel(y,k)>0) time_vary_sel(y,f)=1;
      }
    }  // end type
  } // end years


   for (f=1;f<=N_selparm;f++)
   {
    selparm_LO(f)=selparm_1(f,1);
    selparm_HI(f)=selparm_1(f,2);
    selparm_RD(f)=selparm_1(f,3);
    selparm_PR(f)=selparm_1(f,4);
    selparm_PRtype(f)=selparm_1(f,5);
    selparm_CV(f)=selparm_1(f,6);
    selparm_PH(f)=selparm_1(f,7);
   }
   j=N_selparm;
   if(N_selparm_env>0)
   for (f=1;f<=N_selparm_env;f++)
   {
    j++;
    if(customenvsetup==0) k=1;
    else k=f;
    selparm_LO(j)=selparm_env_1(k,1);
    selparm_HI(j)=selparm_env_1(k,2);
    selparm_RD(j)=selparm_env_1(k,3);
    selparm_PR(j)=selparm_env_1(k,4);
    selparm_PRtype(j)=selparm_env_1(k,5);
    selparm_CV(j)=selparm_env_1(k,6);
    selparm_PH(j)=selparm_env_1(k,7);
   }

   if(N_selparm_blk>0)
   for (f=1;f<=N_selparm_blk;f++)
   {
    j++;
    if(customblocksetup==0) k=1;
    else k=f;
    selparm_LO(j)=selparm_blk_1(k,1);
    selparm_HI(j)=selparm_blk_1(k,2);
    selparm_RD(j)=selparm_blk_1(k,3);
    selparm_PR(j)=selparm_blk_1(k,4);
    selparm_PRtype(j)=selparm_blk_1(k,5);
    selparm_CV(j)=selparm_blk_1(k,6);
    selparm_PH(j)=selparm_blk_1(k,7);
   }
   if(N_selparm_dev>0) j=N_selparm_dev; else j=1;    // for defining non-zero array size
 END_CALCS

//  ProgLabel_1132  set up the dev vectors for the selex parms
  ivector selparm_dev_minyr(1,j)
  ivector selparm_dev_maxyr(1,j)
  vector  selparm_dev_stddev(1,j)
  number selparm_dev_PH

 LOCAL_CALCS

  if(N_selparm_dev==0)
  {
    selparm_dev_PH=-6;
    echoinput<<" No selparm devs selected, so don't read selparm_dev_PH"<<endl;
  }
  else
  {
    j=0;
    for (f=1;f<=N_selparm;f++)
    {
      if(selparm_1(f,9)>=1)
      {
        j++;
        selparm_1(f,9)=j;
        selparm_dev_minyr(j)=selparm_1(f,10);
        selparm_dev_maxyr(j)=selparm_1(f,11);
        selparm_dev_stddev(j)=selparm_1(f,12);
      }
    }
    *(ad_comm::global_datafile) >> selparm_dev_PH;
    echoinput<<selparm_dev_PH<<" selparm_dev_PH"<<endl;
  }
 END_CALCS

  int selparm_adjust_method   //  1=do V1.xx approach to adjustment by env, block or dev; 2=use new logistic approach
 LOCAL_CALCS
  if(N_selparm_env+N_selparm_blk+N_selparm_dev > 0)
  {*(ad_comm::global_datafile) >> selparm_adjust_method;
    echoinput<<selparm_adjust_method<<" selparm_adjust_method"<<endl;
    }
  else
  {selparm_adjust_method=0;
    echoinput<<" No selparm adjustments, so don't read selparm_adjust_method"<<endl;
    }
 END_CALCS

// if Tags are used, the read parameters for initial tag loss, chronic tag loss, andd
// fleet-specific tag reporting.  Of these, only reporting rate will be allowed to be time-varying
  init_int TG_custom;  // 1=read; 0=create default parameters
  !! echoinput<<TG_custom<<" TG_custom (need to read even if no tag data )"<<endl;
  !! k=TG_custom*Do_TG*(3*N_TG+2*Nfleet);
  init_matrix TG_parm1(1,k,1,14);  // read initial values
  !! if(k>0) echoinput<<" Tag parameters as read "<<endl<<TG_parm1<<endl;
  !! k=Do_TG*(3*N_TG+2*Nfleet);
  matrix TG_parm2(1,k,1,14);
  !!if(Do_TG>0) {k1=k;} else {k1=1;}
  vector TG_parm_LO(1,k1);
  vector TG_parm_HI(1,k1);
  ivector TG_parm_PH(1,k1);
 LOCAL_CALCS
  if(Do_TG>0)
  {
    if(TG_custom==1)
    {
      TG_parm2=TG_parm1;  // assign to the read values
    }
    else
    {
      TG_parm2.initialize();
      onenum="    ";
      for(j=1;j<=N_TG;j++)
      {
        TG_parm2(j,1)=-10;  // min
        TG_parm2(j,2)=10;   // max
        TG_parm2(j,3)=-9.;   // init
        TG_parm2(j,4)=-9.;   // prior
        TG_parm2(j,5)=1.;   // default prior type is symmetric beta
        TG_parm2(j,6)=0.001;  //  prior is quite diffuse
        TG_parm2(j,7)=-4;  // phase
      }
      for(j=1;j<=N_TG;j++)
      {
        TG_parm2(j+N_TG)=TG_parm2(1);  // set chronic tag retention equal to initial tag_retention
      }
      for(j=1;j<=N_TG;j++)  // set overdispersion
      {
        TG_parm2(j+2*N_TG,1)=1;  // min
        TG_parm2(j+2*N_TG,2)=10;   // max
        TG_parm2(j+2*N_TG,3)=2.;   // init
        TG_parm2(j+2*N_TG,4)=2.;   // prior
        TG_parm2(j+2*N_TG,5)=1.;   // default prior type is symmetric beta
        TG_parm2(j+2*N_TG,6)=0.001;  //  prior is quite diffuse
        TG_parm2(j+2*N_TG,7)=-4;  // phase
      }
      for(j=1;j<=Nfleet;j++)
      {
        TG_parm2(j+3*N_TG)=TG_parm2(1);  // set tag reporting equal to near 1.0, as is the tag retention parameters
      }
      // set tag reporting decay to nil decay rate
      for(j=1;j<=Nfleet;j++)
      {
        k=j+3*N_TG+Nfleet;
        TG_parm2(k,1)=-4.;
        TG_parm2(k,2)=0.;
        TG_parm2(k,3)=0.;
        TG_parm2(k,4)=0.;    // prior of zero
        TG_parm2(k,5)=0.;  // default prior is squared dev
        TG_parm2(k,6)=2.;  // sd dev of prior
        TG_parm2(k,7)=-4.;
      }
    }
       onenum="    ";
       for(j=1;j<=N_TG;j++)
       {
//       _itoa( j, onenum, 10 );
       sprintf(onenum, "%d", j);
       ParCount++; ParmLabel+="TG_loss_init_"+onenum+CRLF(1);
      }
       for(j=1;j<=N_TG;j++)
      {
//       _itoa( j, onenum, 10 );
       sprintf(onenum, "%d", j);
       ParCount++; ParmLabel+="TG_loss_chronic_"+onenum+CRLF(1);
      }
       for(j=1;j<=N_TG;j++)
      {
//       _itoa( j, onenum, 10 );
       sprintf(onenum, "%d", j);
       ParCount++; ParmLabel+="TG_overdispersion_"+onenum+CRLF(1);
      }
       for(j=1;j<=Nfleet;j++)
      {
//       _itoa( j, onenum, 10 );
       sprintf(onenum, "%d", j);
       ParCount++; ParmLabel+="TG_report_fleet:_"+onenum+CRLF(1);
      }
       for(j=1;j<=Nfleet;j++)
      {
//       _itoa( j, onenum, 10 );
       sprintf(onenum, "%d", j);
       ParCount++; ParmLabel+="TG_rpt_decay_fleet:_"+onenum+CRLF(1);
      }

    TG_parm_LO=column(TG_parm2,1);
    TG_parm_HI=column(TG_parm2,2);
    k=3*N_TG+2*Nfleet;
    for(j=1;j<=k;j++) TG_parm_PH(j)=TG_parm2(j,7);  // write it out due to no typecast available
    echoinput<<" Processed/generated Tag parameters "<<endl<<TG_parm2<<endl;

  }
  else
  {
    TG_parm_LO.initialize();
    TG_parm_HI.initialize();
    TG_parm_PH.initialize();
  }
 END_CALCS


//  read variance adjustment
  init_int Do_Var_adjust
  init_matrix var_adjust1(1,6*Do_Var_adjust,1,Ntypes)
  matrix var_adjust(1,6,1,Ntypes)
 LOCAL_CALCS
  echoinput<<Do_Var_adjust<<" Do_Var_adjust "<<endl;
  if(Do_Var_adjust>0)
  {
    var_adjust=var_adjust1;
   echoinput<<" Varadjustments as read "<<endl<<var_adjust1<<endl;
  }
  else
  {
    var_adjust(1)=0.;
    var_adjust(2)=0.;
    var_adjust(3)=0.;
    var_adjust(4)=1.;
    var_adjust(5)=1.;
    var_adjust(6)=1.;
  }
 END_CALCS

  init_number DF_disc    //  DF For discard T-distribution
  init_number DF_bodywt  // DF For meanbodywt T-distribution
  init_number max_lambda_phase
  init_number sd_offset
  number sd_offset_rec

 LOCAL_CALCS
  echoinput<<DF_disc<<" degrees of freedom for discard T-distribution "<<endl;
  echoinput<<DF_bodywt<<" degrees of freedom for bodywt T-distribution "<<endl;
  echoinput<<max_lambda_phase<<" max_lambda_phase "<<endl;
  echoinput<<sd_offset<<" sd_offset (adds log(s)) "<<endl;
  sd_offset_rec=sum(biasadj)*sd_offset;    //sd_offset*double(recdev_end-recdev_first+1.);

 END_CALCS

  matrix surv_lambda(1,Ntypes,1,max_lambda_phase)
  matrix disc_lambda(1,Ntypes,1,max_lambda_phase)
  matrix mnwt_lambda(1,Ntypes,1,max_lambda_phase)
  matrix length_lambda(1,Ntypes,1,max_lambda_phase)
  matrix age_lambda(1,Ntypes,1,max_lambda_phase)
  matrix sizeage_lambda(1,Ntypes,1,max_lambda_phase)
  vector init_equ_lambda(1,max_lambda_phase)
  matrix catch_lambda(1,Ntypes,1,max_lambda_phase)
  vector recrdev_lambda(1,max_lambda_phase)
  vector parm_prior_lambda(1,max_lambda_phase)
  vector parm_dev_lambda(1,max_lambda_phase)
  vector CrashPen_lambda(1,max_lambda_phase)
  vector Morphcomp_lambda(1,max_lambda_phase)
  matrix WtFreq_lambda(1,WtFreq_Nuse,1,max_lambda_phase)
  matrix TG_lambda1(1,N_TG2,1,max_lambda_phase)
  matrix TG_lambda2(1,N_TG2,1,max_lambda_phase)

  init_int N_lambda_changes
  init_matrix Lambda_changes(1,N_lambda_changes,1,5)
 LOCAL_CALCS
   echoinput<<N_lambda_changes<<" N lambda changes "<<endl;
   if(N_lambda_changes>0) echoinput<<" lambda changes "<<endl<<Lambda_changes<<endl;
   surv_lambda=1.;  // 1
   disc_lambda=1.;  // 2
   mnwt_lambda=1.;  // 3
   length_lambda=1.; // 4
   age_lambda=1.;  // 5
   WtFreq_lambda=1.;  // 6
   sizeage_lambda=1.; // 7
   catch_lambda=1.; // 8
   init_equ_lambda=1.; // 9
   recrdev_lambda=1.; // 10
   parm_prior_lambda=1.; // 11
   parm_dev_lambda=1.; // 12
   CrashPen_lambda=1.; // 13
   Morphcomp_lambda=1.; // 14
   TG_lambda1=1.; // 15
   TG_lambda2=1.;  //16
    for(j=1;j<=N_lambda_changes;j++)
    {
      k=Lambda_changes(j,1);  // like component
      f=Lambda_changes(j,2);  // fleet
      s=Lambda_changes(j,3);  // phase
      if(f>Ntypes)
      {k=0; N_warn++;  warning<<" illegal request for lambda change at row: "<<j<<" fleet: "<<f<<" > Ntypes"<<endl;}
      if(s>max_lambda_phase)
      {k=0; N_warn++;  warning<<" illegal request for lambda change at row: "<<j<<" phase: "<<s<<" > max_lam_phase: "<<max_lambda_phase<<endl;}
//      if(s>Turn_off_phase) s=max(1,Turn_off_phase);
      temp=Lambda_changes(j,4);  // value
      z=Lambda_changes(j,5);   // special for wtfreq
      switch(k)
      {
        case 0:  // do nothing
        {break;}
        case 1:  // survey
          {surv_lambda(f)(s,max_lambda_phase)=temp;  break;}
        case 2:  // discard
          {disc_lambda(f)(s,max_lambda_phase)=temp;  break;}
        case 3:  // meanbodywt
          {mnwt_lambda(f)(s,max_lambda_phase)=temp; break;}
        case 4:  // lengthcomp
          {length_lambda(f)(s,max_lambda_phase)=temp; break;}
        case 5:  // agecomp
        {age_lambda(f)(s,max_lambda_phase)=temp; break;}
        case 6:  // wtfreq comp
        {
          z=Lambda_changes(j,5);  //  wtfreq method
          if(z>WtFreq_Nmeth) {N_warn++; cout<<" exit - see warning "<<endl; warning<<" reading wtfreq lambda change for method > Nmeth "<<Lambda_changes(j,5)<<endl; exit(1);}
          WtFreq_lambda(WtFreq_use(f,z))(s,max_lambda_phase) = temp;
          break;
        }
        case 7:  // size-at-age
          {sizeage_lambda(f)(s,max_lambda_phase)=temp; break;}
        case 8:  // catch
          {catch_lambda(f)(s,max_lambda_phase)=temp; break;}
        case 9:  // init_equ_catch
          {init_equ_lambda(s,max_lambda_phase)=temp; break;}
        case 10:  // recr_dev
          {recrdev_lambda(s,max_lambda_phase)=temp; break;}
        case 11:  // parm_prior
          {parm_prior_lambda(s,max_lambda_phase)=temp; break;}
        case 12:  // parm_dev
          {parm_dev_lambda(s,max_lambda_phase)=temp; break;}
        case 13:  // crash_penalty
          {CrashPen_lambda(s,max_lambda_phase)=temp; break;}
        case 14:  // morphcomp
          {Morphcomp_lambda(s,max_lambda_phase)=temp; break;}
        case 15:  // Tag - multinomial by fleet
          {TG_lambda1(f)(s,max_lambda_phase)=temp; break;}
        case 16:  // Tag - total by time
          {TG_lambda2(f)(s,max_lambda_phase)=temp; break;}
      }
    }
    for(f=1;f<=Ntypes;f++)
    {
      if(nyr_cr(f)==0) surv_lambda(f)=0.;
      if(nyr_disc(f)==0) disc_lambda(f)=0.;
      if(nyr_l(f)==0) length_lambda(f)=0.;
      if(nyr_a(f)==0) age_lambda(f)=0.;
      if(nyr_ms(f)==0) sizeage_lambda(f)=0.;
    }
    if(nobs_mnwt==0) mnwt_lambda=0.;  //  more complicated to turn off for each fleet
 END_CALCS

  init_int Do_More_Std
  init_ivector More_Std_Input(1,Do_More_Std*9)
 LOCAL_CALCS
  echoinput<<Do_More_Std<<" # read specs for more stddev reporting "<<endl;
  if(Do_More_Std>0)
  {echoinput<<More_Std_Input<<" # vector with selex type, len/age, year, N selex bins, Growth pattern, N growth ages, N_at_age_Area, NatAge_yr, Natage_ages"<<endl;}
  else
  {echoinput<<" # placeholder vector with selex type, len/age, year, N selex bins, Growth pattern, N growth ages"<<endl;}
 END_CALCS

  int Do_Selex_Std;
  int Selex_Std_AL;
  int Selex_Std_Year;
  int Selex_Std_Cnt;
  int Do_Growth_Std;
  int Growth_Std_Cnt;
  int Do_NatAge_Std;
  int NatAge_Std_Year;
  int NatAge_Std_Cnt;
  int Extra_Std_N;   //  dimension for the sdreport vector Selex_Std which also contains the Growth_Std

 LOCAL_CALCS
   if(Do_More_Std==1)
   {
     Do_Selex_Std=More_Std_Input(1);
     Selex_Std_AL=More_Std_Input(2);
     Selex_Std_Year=More_Std_Input(3);
     if(Selex_Std_Year<0) Selex_Std_Year=endyr;
     Selex_Std_Cnt=More_Std_Input(4);
     Do_Growth_Std=More_Std_Input(5);
     if(MG_active(2)==0) Do_Growth_Std=0;
     Growth_Std_Cnt=More_Std_Input(6);
     Do_NatAge_Std=More_Std_Input(7);
     NatAge_Std_Year=More_Std_Input(8);
     if(NatAge_Std_Year<0) NatAge_Std_Year=endyr+1;
     NatAge_Std_Cnt=More_Std_Input(9);
   }
   else
   {
     Do_Selex_Std=0;
     Selex_Std_AL=1;
     Selex_Std_Year=endyr;
     Selex_Std_Cnt=0;
     Do_Growth_Std=0;
     Growth_Std_Cnt=0;
     Do_NatAge_Std=0;
     NatAge_Std_Cnt=0;
     NatAge_Std_Year=endyr;
   }
 END_CALCS

  init_ivector Selex_Std_Pick(1,Selex_Std_Cnt);
  init_ivector Growth_Std_Pick(1,Growth_Std_Cnt);
  init_ivector NatAge_Std_Pick(1,NatAge_Std_Cnt);

 LOCAL_CALCS
  if(Selex_Std_Cnt>0) echoinput<<Selex_Std_Pick<<" # vector with selex std bin picks (-1 in first bin to self-generate)"<<endl;
  if(Growth_Std_Cnt>0) echoinput<<Growth_Std_Pick<<" # vector with growth std bin picks (-1 in first bin to self-generate)"<<endl;
  if(NatAge_Std_Cnt>0) echoinput<<NatAge_Std_Pick<<" # vector with NatAge std bin picks (-1 in first bin to self-generate)"<<endl;

// reset the counter here after using it to dimension the input statement above
  if(Do_Selex_Std<=0) Selex_Std_Cnt=0;
  if(Do_Growth_Std<=0) Growth_Std_Cnt=0;
  if(Do_NatAge_Std==0) NatAge_Std_Cnt=0;

  Extra_Std_N=0;
  if(Do_Selex_Std>0)
  {
    if(Selex_Std_Pick(1)<=0)  //  then self-generate even bin selection
    {
      if(Selex_Std_AL==1)
      {
        j=nlength/(Selex_Std_Cnt-1);
        Selex_Std_Pick(1)=j/2;
        for(i=2;i<=Selex_Std_Cnt-1;i++) Selex_Std_Pick(i)=Selex_Std_Pick(i-1)+j;
        Selex_Std_Pick(Selex_Std_Cnt)=nlength;
      }
      else
      {
        j=nages/(Selex_Std_Cnt-1);
        Selex_Std_Pick(1)=j/2;
        for(i=2;i<=Selex_Std_Cnt-1;i++) Selex_Std_Pick(i)=Selex_Std_Pick(i-1)+j;
        Selex_Std_Pick(Selex_Std_Cnt)=nages;
      }
    }
    Extra_Std_N=gender*Selex_Std_Cnt;
  }

  if(Do_Growth_Std>0)
  {
    if(Growth_Std_Pick(1)<=0)
    {
      Growth_Std_Pick(1)=AFIX;
      Growth_Std_Pick(Growth_Std_Cnt)=nages;
      if(Growth_Std_Cnt>2)
      {
        k=Growth_Std_Cnt/2;
        for(i=2;i<=k;i++) Growth_Std_Pick(i)=Growth_Std_Pick(i-1)+1;
        j=(nages-Growth_Std_Pick(k))/(Growth_Std_Cnt-k);
        for(i=k+1;i<=Growth_Std_Cnt-1;i++) Growth_Std_Pick(i)=Growth_Std_Pick(i-1)+j;
      }
    }
  }
  Extra_Std_N+=gender*Growth_Std_Cnt;

  if(Do_NatAge_Std>0)
  {
    if(NatAge_Std_Pick(1)<=0)
    {
      NatAge_Std_Pick(1)=1;
      NatAge_Std_Pick(NatAge_Std_Cnt)=nages;
      if(NatAge_Std_Cnt>2)
      {
        k=NatAge_Std_Cnt/2;
        for(i=2;i<=k;i++) NatAge_Std_Pick(i)=NatAge_Std_Pick(i-1)+1;
        j=(nages-NatAge_Std_Pick(k))/(NatAge_Std_Cnt-k);
        for(i=k+1;i<=NatAge_Std_Cnt-1;i++) NatAge_Std_Pick(i)=NatAge_Std_Pick(i-1)+j;
      }
    }
  }
  Extra_Std_N+=gender*NatAge_Std_Cnt;

  if(Extra_Std_N==0) Extra_Std_N=1;   //  assign a minimum length to dimension the sdreport vector Selex_Std
 END_CALCS

  init_int fim // end of file indicator

 LOCAL_CALCS
  cout<<"If you see 999, we got to the end of the control file successfully! "<<fim<<endl;
  echoinput<<fim<<"  If you see 999, we got to the end of the control file successfully! "<<endl;
  if(fim!=999) abort();
 END_CALCS


  int CoVar_Count;
  int active_count;    // count the active parameters
 LOCAL_CALCS
  if(Do_Benchmark>0)
  {
    N_STD_mgmtquant=6;
    if(Do_Retain==1) N_STD_mgmtquant++;
  }
  else
  {N_STD_mgmtquant=1;}
  Fore_catch_start=N_STD_mgmtquant;
  if(Do_Forecast>0) {N_STD_mgmtquant+=N_Fore_Yrs*(1+Do_Retain);}
  k=ParCount+2*N_STD_Yr+N_STD_Yr_Dep+N_STD_Yr_Ofish+N_STD_Yr_F+N_STD_mgmtquant+gender*Selex_Std_Cnt+gender*Growth_Std_Cnt;
 END_CALCS
  ivector active_parm(1,k)  //  pointer from active list to the element of the full parameter list to get label later


//***********************************************
//  adjust the phases                                       ProgLabel_029
  int max_phase;
  int report_phase;

 LOCAL_CALCS
  cout<<" adjust the phases and count the number of active parameters"<<endl;
  max_phase=1;
  active_count=0;
  active_parm(1,ParCount)=0;
  ParCount=0;

  j=MGparm_PH.indexmax();
  for(k=1;k<=j;k++)
  {
    ParCount++;
    if(MGparm_PH(k) > Turn_off_phase) MGparm_PH(k) =-1;
    if(MGparm_PH(k) > max_phase) max_phase=MGparm_PH(k);
    if(MGparm_PH(k)==-9999) {MGparm_RD(k)=prof_var(prof_var_cnt); prof_var_cnt+=1;}
    if(MGparm_PH(k)>=0)
    {
      active_count++; active_parm(active_count)=ParCount;
    }
  }

  if(MGparm_dev_PH>Turn_off_phase) MGparm_dev_PH =-1;
  if(MGparm_dev_PH>max_phase) max_phase=MGparm_dev_PH;
  for(k=1;k<=N_MGparm_dev_tot;k++)
  {
    ParCount++;
    if(MGparm_dev_PH>=0)
    {
    active_count++; active_parm(active_count)=ParCount;
    }
  }

  for(j=1;j<=SRvec_PH.indexmax();j++)
  {
    ParCount++;
    if(SRvec_PH(j) > Turn_off_phase) SRvec_PH(j) =-1;
    if(SRvec_PH(j) > max_phase) max_phase=SRvec_PH(j);
    if(SRvec_PH(j)==-9999) {SR_parm_1(j,3)=prof_var(prof_var_cnt); prof_var_cnt+=1;}
    if(SRvec_PH(j)>=0)
    {
      active_count++; active_parm(active_count)=ParCount;
    }
  }

  if(recdev_PH > Turn_off_phase) recdev_PH =-1;
  if(recdev_PH > max_phase) max_phase=recdev_PH;
  if(recdev_early_PH > Turn_off_phase) recdev_early_PH =-1;
  if(recdev_early_PH > max_phase) max_phase=recdev_early_PH;

  if(recdev_do_early>0)
  {
  for(y=recdev_early_start;y<=recdev_early_end;y++)
  {
    ParCount++;
    if(recdev_early_PH>=0) {active_count++; active_parm(active_count)=ParCount;}
  }
  }

  if(do_recdev>0)
  {
  for(y=recdev_start;y<=recdev_end;y++)
  {
    ParCount++;
    if(recdev_PH>=0) {active_count++; active_parm(active_count)=ParCount;}
  }
  }

  if(Do_Forecast>0)
  {
    for(y=recdev_end+1;y<=YrMax;y++)
    {
      ParCount++;
      active_count++; active_parm(active_count)=ParCount;
    }
    if(Turn_off_phase>0)
    {
      if(fore_recr_PH==0)
      {fore_recr_PH2=max_phase+1;report_phase=fore_recr_PH2;}
      else
      {
        fore_recr_PH2=fore_recr_PH;
        if(fore_recr_PH2 > Turn_off_phase) fore_recr_PH2 =-1;
        if(fore_recr_PH2 > max_phase) max_phase=fore_recr_PH2;
        report_phase=max_phase;
      }
    }
    else
    {fore_recr_PH2=-1;report_phase=max_phase;}
  }
  else
  {fore_recr_PH2=-1;report_phase=max_phase;}

  for(f=1;f<=Nfleet;f++)
  {
    ParCount++;
    if(init_F_PH(f) > Turn_off_phase) init_F_PH(f) =-1;
    if(init_F_PH(f) > max_phase) max_phase=init_F_PH(f);
    if(init_F_PH(f)>=0)
    {
      active_count++; active_parm(active_count)=ParCount;
    }
  }

  if(F_Method==2)
  {
    for(g=1;g<=Nfleet*(TimeMax-styr+1);g++)
    {
      ParCount++;
      if(have_catch(g) > Turn_off_phase) have_catch(g) =-1;
      if(have_catch(g) > max_phase) max_phase=have_catch(g);
      if(have_catch(g)>=0)
      {
        active_count++; active_parm(active_count)=ParCount;
      }
    }
  }

  for(f=1;f<=Q_Npar;f++)
  {
    ParCount++;
    if(Q_parm_PH(f) > Turn_off_phase) Q_parm_PH(f) =-1;
    if(Q_parm_PH(f) > max_phase) max_phase=Q_parm_PH(f);
    if(Q_parm_PH(f)==-9999) {Q_parm_1(f,3)=prof_var(prof_var_cnt); prof_var_cnt+=1;}
    if(Q_parm_PH(f)>=0)
    {
      active_count++; active_parm(active_count)=ParCount;
    }
  }

   for(k=1;k<=selparm_PH.indexmax();k++)
   {
     ParCount++;
     if(selparm_PH(k) > Turn_off_phase) selparm_PH(k) =-1;
     if(selparm_PH(k) > max_phase) max_phase=selparm_PH(k);
     if(selparm_PH(k)==-9999) {selparm_RD(k)=prof_var(prof_var_cnt); prof_var_cnt+=1;}
     if(selparm_PH(k)>=0)
    {
      active_count++; active_parm(active_count)=ParCount;
    }
   }

   if(selparm_dev_PH > Turn_off_phase) selparm_dev_PH =-1;
   if(selparm_dev_PH > max_phase) max_phase=selparm_dev_PH;
  cout<<" turn_off_phase "<<Turn_off_phase<<endl<<" max_phase "<<max_phase<<endl;
  for(k=1;k<=N_selparm_dev_tot;k++)
  {
    ParCount++;
    if(selparm_dev_PH>=0)
    {
    active_count++; active_parm(active_count)=ParCount;
    }
  }
  cout<<N_selparm_dev_tot<<" selparmdev "<<endl;

  if(Do_TG>0)
  {
    for(k=1;k<=3*N_TG+2*Nfleet;k++)
    {
      ParCount++;
      if(TG_parm_PH(k) > Turn_off_phase) TG_parm_PH(k) =-1;
      if(TG_parm_PH(k) > max_phase) max_phase=TG_parm_PH(k);
      if(TG_parm_PH(k)>=0)
      {
      active_count++; active_parm(active_count)=ParCount;
      }
    }
  }

  if(Turn_off_phase<=0)
  {func_eval(1)=1;}
  else
  {
     func_conv(max_phase)=final_conv;  func_eval(max_phase)=10000;
     func_conv(max_phase+1)=final_conv;  func_eval(max_phase+1)=10000;
  }

  // sdreport
    j=ParCount;
    CoVar_Count=active_count;
  onenum="    ";
  for(y=styr-2;y<=YrMax;y++)
  {
    if(STD_Yr_Reverse(y)>0)
    {
    CoVar_Count++; j++; active_parm(CoVar_Count)=j;
    if(y==styr-2)
    {ParmLabel+="VirginSPB";}
    else if(y==styr-1)
    {ParmLabel+="InitialSPB";}
    else
    {
//      _itoa(y,onenum,10);
      sprintf(onenum, "%d", y);
      ParmLabel+="SPB_"+onenum+CRLF(1);
    }
    }
  }

  for(y=styr-2;y<=YrMax;y++)
  {
    if(STD_Yr_Reverse(y)>0)
    {
    CoVar_Count++; j++; active_parm(CoVar_Count)=j;
    if(y==styr-2)
    {ParmLabel+="VirginRecr";
      }
    else if(y==styr-1)
    {ParmLabel+="InitialRecr";
      }
    else
    {
//      _itoa(y,onenum,10);
     sprintf(onenum, "%d", y);
      ParmLabel+="Recr_"+onenum+CRLF(1);
    }
  }
  }

  for(y=styr;y<=YrMax;y++)
  {
    if(STD_Yr_Reverse_Ofish(y)>0)
    {
      CoVar_Count++; j++; active_parm(CoVar_Count)=j;
//      _itoa(y,onenum,10);
      sprintf(onenum, "%d", y);
      ParmLabel+="SPRratio_"+onenum+CRLF(1);
    }
  }

  //F_std
  for(y=styr;y<=YrMax;y++)
  {
    if(STD_Yr_Reverse_F(y)>0)
    {
      CoVar_Count++; j++; active_parm(CoVar_Count)=j;
//      _itoa(y,onenum,10);
      sprintf(onenum, "%d", y);
      ParmLabel+="F_"+onenum+CRLF(1);
    }
  }

  for(y=styr;y<=YrMax;y++)
  {
    if(STD_Yr_Reverse_Dep(y)>0)
    {
      CoVar_Count++; j++; active_parm(CoVar_Count)=j;
//      _itoa(y,onenum,10);
    sprintf(onenum, "%d", y);
    ParmLabel+="Bratio_"+onenum+CRLF(1);
    }
  }

  if(Do_Benchmark>0)
    {
      ParmLabel+="MSY"+CRLF(1); CoVar_Count++; j++; active_parm(CoVar_Count)=j;
      ParmLabel+="B_MSY"+CRLF(1); CoVar_Count++; j++; active_parm(CoVar_Count)=j;
      ParmLabel+="SPR_MSY"+CRLF(1); CoVar_Count++; j++; active_parm(CoVar_Count)=j;
      ParmLabel+="F_SPR"+CRLF(1); CoVar_Count++; j++; active_parm(CoVar_Count)=j;
      ParmLabel+="F_MSY"+CRLF(1); CoVar_Count++; j++; active_parm(CoVar_Count)=j;
      ParmLabel+="F_Btgt"+CRLF(1); CoVar_Count++; j++; active_parm(CoVar_Count)=j;
      if(Do_Retain==1) {ParmLabel+="MSY_retain"+CRLF(1); CoVar_Count++; j++; active_parm(CoVar_Count)=j;}
    }
    else
    {
      ParmLabel+="Bzero_again"+CRLF(1); CoVar_Count++; j++; active_parm(CoVar_Count)=j;
    }

    if(Do_Forecast>0)
    {
      for(y=endyr+1;y<=YrMax;y++)
      {
        CoVar_Count++; j++; active_parm(CoVar_Count)=j;
//      _itoa(y,onenum,10);
        sprintf(onenum, "%d", y);
        ParmLabel+="Fore_catch_"+onenum+CRLF(1);
      }
      if(Do_Retain==1)
      {
        for(y=endyr+1;y<=YrMax;y++)
        {
          CoVar_Count++; j++; active_parm(CoVar_Count)=j;
          sprintf(onenum, "%d", y);
          ParmLabel+="Fore_catch_ret_"+onenum+CRLF(1);
        }
      }
    }

// do labels for Selex_Std
    if(Do_Selex_Std>0)
    {
      for(g=1;g<=gender;g++)
      for(i=1;i<=Selex_Std_Cnt;i++)
      {
        CoVar_Count++; j++; active_parm(CoVar_Count)=j;
        if(Selex_Std_AL==1)
        {
          if(Selex_Std_Pick(i)>nlength)
          {
            N_warn++; warning<<" cannot select stdev for length bin greater than nlength "<<Selex_Std_Pick(i)<<" > "<<nlength<<endl; exit(1);
          }
          ParmLabel+="Selex_std_"+NumLbl(Do_Selex_Std)+"_"+GenderLbl(g)+"_L_"+NumLbl(len_bins(Selex_Std_Pick(i)))+CRLF(1);
        }
        else
        {
          if(Selex_Std_Pick(i)>nages)
          {
            N_warn++; warning<<" cannot select stdev for age bin greater than maxage "<<Selex_Std_Pick(i)<<" > "<<nages<<endl; exit(1);
          }
          ParmLabel+="Selex_std_"+NumLbl(Do_Selex_Std)+"_"+GenderLbl(g)+"_A_"+NumLbl(age_vector(Selex_Std_Pick(i)))+CRLF(1);
        }
      }
    }
    if(Do_Growth_Std>0)
    {
      for(g=1;g<=gender;g++)
      for(i=1;i<=Growth_Std_Cnt;i++)
      {
        CoVar_Count++; j++; active_parm(CoVar_Count)=j;
        ParmLabel+="Grow_std_"+NumLbl(Do_Growth_Std)+"_"+GenderLbl(g)+"_A_"+NumLbl(age_vector(Growth_Std_Pick(i)))+CRLF(1);
      }
    }
    if(Do_NatAge_Std>0)
    {
      for(g=1;g<=gender;g++)
      for(i=1;i<=NatAge_Std_Cnt;i++)
      {
        CoVar_Count++; j++; active_parm(CoVar_Count)=j;
        ParmLabel+="NatAge_std_"+NumLbl(Do_NatAge_Std)+"_"+GenderLbl(g)+"_A_"+NumLbl(age_vector(NatAge_Std_Pick(i)))+CRLF(1);
      }
    }
    if(Do_Selex_Std==0 && Do_Growth_Std==0 && Do_NatAge_Std==0)
    {
      CoVar_Count++; j++; active_parm(CoVar_Count)=j;
      ParmLabel+="B0_again_No_selex_std"+CRLF(1);
    }

   sprintf(onenum, "%d", int(100*depletion_level));
   switch(depletion_basis)
    {
      case 0:
      {
        depletion_basis_label+="no_depletion_basis";
        break;
      }
      case 1:
      {
        depletion_basis_label+=" "+onenum+"%*Virgin_Biomass";
        break;
      }
      case 2:
      {
        depletion_basis_label+=" "+onenum+"%*B_MSY";
        break;
      }
      case 3:
      {
        depletion_basis_label+=" "+onenum+"%*StartYr_Biomass";
        break;
      }
    }

   switch (SPR_reporting)
  {
    case 0:      // keep as raw value
    {
      SPR_report_label+=" raw_SPR";
      break;
    }
    case 1:  // compare to SPR
    {
      sprintf(onenum, "%d", int(100.*SPR_target));
      SPR_report_label+=" (1-SPR)/(1-SPR_"+onenum+"%)";
      break;
    }
    case 2:  // compare to SPR_MSY
    {
      SPR_report_label+=" (1-SPR)/(1-SPR_MSY)";
      break;
    }
    case 3:  // compare to SPR_Btarget
    {
      sprintf(onenum, "%d", int(100.*BTGT_target));
      SPR_report_label+=" (1-SPR)/(1-SPR_at_B"+onenum+"%)";
      break;
    }
    case 4:
    {
      SPR_report_label+=" 1-SPR";
      break;
    }
  }

  switch (F_report_basis)
  {
    case 0:  // raw
    {
      F_report_label="_abs_F";
      break;
    }
    case 1:
    {
      sprintf(onenum, "%d", int(100.*SPR_target));
      F_report_label="(F)/(F"+onenum+"%SPR)";
      break;
    }
    case 2:
    {
      F_report_label="(F)/(Fmsy)";
      break;
    }
    case 3:
    {
      sprintf(onenum, "%d", int(100.*BTGT_target));
      F_report_label="(F)/(F_at_B"+onenum+"%)";
      break;
    }
  }

   switch (F_reporting)
  {
    case 0:      // keep as raw value
    {
      F_report_label+=";_no_F_report";
      break;
    }
    case 1:      // keep as raw value
    {
      F_report_label+=";_with_F=Exploit(bio)";
      break;
    }
    case 2:      // keep as raw value
    {
      F_report_label+=";_with_F=Exploit(num)";
      break;
    }
    case 3:      // keep as raw value
    {
      F_report_label+=";_with_F=sum(full_Fs)";
      break;
    }
  }

 END_CALCS

  !!k=gmorph*(YrMax-styr+1);

  matrix save_G_parm(1,k,1,22);
  matrix save_seas_parm(1,nseas,1,10);
  matrix CoVar(1,CoVar_Count,1,CoVar_Count+1);
  !!CoVar.initialize();
  !!set_covariance_matrix(CoVar);

  matrix save_SPR(styr,YrMax,1,6+2*gmorph)  // totbio, smrybio, S0, S1, Gentime, YPR

//  Completed reading of input; now setup the output files

  !!CLASS ofstream report2("CumReport.SSO",ios::app);
  !!CLASS ofstream SS2out("Report.SSO");


//  ProgLabel_0990_#  INITIALIZATION_SECTION (not used in SS2)
INITIALIZATION_SECTION

//  ProgLabel_1000_#   PARAMETER_SECTION
PARAMETER_SECTION

 LOCAL_CALCS
    if(readparfile>=1)
    {cout<<" read parm file"<<endl;
    ad_comm::change_pinfile_name("SS3.PAR");}


    maximum_function_evaluations.allocate(func_eval.indexmin(),func_eval.indexmax());
    maximum_function_evaluations=func_eval;
    convergence_criteria.allocate(func_conv.indexmin(),func_conv.indexmax());
    convergence_criteria=func_conv;
 END_CALCS

  init_bounded_number dummy_parm(0,2,dummy_phase)  //  estimate in phase 0

  // natural mortality and growth
  init_bounded_number_vector MGparm(1,N_MGparm2,MGparm_LO,MGparm_HI,MGparm_PH)
  init_bounded_matrix MGparm_dev(1,N_MGparm_dev,MGparm_dev_minyr,MGparm_dev_maxyr,-10,10,MGparm_dev_PH)
  !! cout<< " MGdev OK"<<endl;
  vector L_inf(1,N_GP*gender);
  vector Lmax_temp(1,N_GP*gender);
  vector VBK(1,N_GP*gender);
  vector Richards(1,N_GP*gender);
  vector Lmin(1,N_GP*gender);
//  vector natM1(1,N_GP*gender)
//  vector natM2(1,N_GP*gender)
  matrix natMparms(1,N_natMparms,1,N_GP*gender)
  3darray natM(1,nseas,1,N_GP*gender*nseas,0,nages)   //  need nseas to capture differences due to birthseason
  3darray surv1(1,nseas,1,N_GP*gender*nseas,0,nages)
  3darray surv2(1,nseas,1,N_GP*gender*nseas,0,nages)
  vector CVLmin(1,N_GP*gender)
  vector CVLmax(1,N_GP*gender)
  vector CV_const(1,N_GP*gender)
  matrix mgp_save(styr,endyr+1,1,N_MGparm2);
  vector mgp_adj(1,N_MGparm2);
  matrix Cohort_Growth(styr,YrMax,0,nages)
  vector VBK_seas(0,nseas);
  matrix wtlen_seas(0,nseas,1,8);
  vector wtlen_p(1,8);

  3darray wt_len(1,nseas,1,gender,1,nlength)
  matrix wt_len2(1,nseas,1,nlength2)
  matrix wt_len_fd(1,nseas,1,nlength2-1)
  vector mat_len(1,nlength)
  vector fec_len(1,nlength)   // fecundity at length
  vector mat_len_wt(1,nlength)
  vector mat_age(0,nages)

// Age-length keys for each gmorph
   4darray ALK(1,nseas,1,gmorph,0,nages,1,nlength)
//   3darray Sd_Size(1,nseas,1,gmorph,0,nages)
   3darray Sd_Size_within(1,2*nseas,1,gmorph,0,nages)  //  2*nseas stacks begin of seas and end of seas
   3darray Sd_Size_between(1,2*nseas,1,gmorph,0,nages)  //  2*nseas stacks begin of seas and end of seas
   4darray Ave_Size(styr-2*nseas,TimeMax_Fore_std+nseas,0,1,1,gmorph,0,nages)
   3darray Use_Ave_Size(1,2*nseas,1,gmorph,0,nages)
   4darray Save_Ave_Size(styr-2*nseas,TimeMax_Fore_std+nseas,0,1,1,gmorph,0,nages)
//   vector AL(1,nlength1)     // define globally to allow 2 values to be set constant
   matrix CV_G(0,1,0,nages);   //  temporary storage of CV enroute to sd of len-at-age
   3darray Save_Wt_Age(styr,TimeMax_Fore_std+1,1,gmorph,0,nages)
   3darray Wt_Age_beg(1,nseas,1,gmorph,0,nages)
   3darray Wt_Age_mid(1,nseas,1,gmorph,0,nages)

  3darray natage_temp(1,pop,1,gmorph,0,nages)
  3darray migrrate(styr,endyr+1,1,do_migr2,0,nages)

//  3darray morphdist(styr,endyr+1,1,pop,1,gmorph);
//  matrix areadist(styr,endyr+1,1,pop);
  3darray recr_dist(1,N_GP*gender,1,nseas,1,pop);

//recruitment and initial conditions
  init_bounded_number_vector SR_parm(1,6,SRvec_LO,SRvec_HI,SRvec_PH)
  number sigmasq;
  number rho;
 LOCAL_CALCS
  if(SR_parm(6)!=0.0 || SRvec_PH(6)>0) {SR_autocorr=1;} else {SR_autocorr=0;}  // flag for recruitment autocorrelation
  if(do_recdev==1)
  {k=recdev_start; j=recdev_end; s=1; p=-1;}
  else if(do_recdev==2)
  {s=recdev_start; p=recdev_end; k=1; j=-1;}
  else
  {s=1; p=-1; k=1; j=-1;}
 END_CALCS

  init_bounded_dev_vector recdev_early(recdev_early_start,recdev_early_end,recdev_LO,recdev_HI,recdev_early_PH)
  init_bounded_dev_vector recdev1(k,j,recdev_LO,recdev_HI,recdev_PH)
  init_bounded_vector recdev2(s,p,recdev_LO,recdev_HI,recdev_PH)
  init_bounded_vector fore_recruitments(recdev_end+1,YrMax,recdev_LO,recdev_HI,fore_recr_PH2)
  vector recdev(recdev_first,YrMax);

  number SpawnBio;                            // Spawning biomass
  number spb_vir_LH
  vector S1(0,1);
  3darray Spbio(styr-2,YrMax,1,pop,1,N_GP)         //Spawning biomass
  vector Spbio_tot(styr-2,YrMax)
  matrix Spbio_equil(1,pop,1,N_GP);
  number Spbio_equil_sum;

  number Recruits;                            // Age0 Recruits
  number R_base;
  number S_base;
  number steepness;
  matrix Recr(1,pop,styr-2,YrMax)         //Recruitment
  vector exp_rec(styr-2,YrMax) //expected value for recruitment (deterministic)
  vector pred_rec(styr-2,YrMax) //predicted value for recruitment (stochastic)
  vector use_rec(styr-2,YrMax) //value used to calc Numbers at age
  matrix Nmid(1,gmorph,0,nages);
  matrix Nsurv(1,gmorph,0,nages);

//likelihood profile numbers
//  likeprof_number R0_lprof

  number ave_age    //  average age of fish in unfished population; used to weight R1
  init_bounded_number_vector init_F(1,Nfleet,init_F_LO,init_F_HI,init_F_PH)
  vector est_equ_catch(1,Nfleet)
//  vector equ_catch(1,Nfleet)
//  vector equ_catch_enc(1,Nfleet)
//  vector equ_catch_ret(1,Nfleet)

  !!if(Do_Forecast>0) {k=TimeMax_Fore_std+1;} else {k=TimeMax+nseas;}
  4darray natage(styr-2*nseas,k,1,pop,1,gmorph,0,nages)  //  add +1 year
  4darray catage(styr-nseas,TimeMax,1,Nfleet,1,gmorph,0,nages)
  4darray equ_catage(1,nseas,1,Nfleet,1,gmorph,0,nages)
  4darray equ_numbers(1,nseas,1,pop,1,gmorph,0,3*nages)
  4darray equ_Z(1,nseas,1,pop,1,gmorph,0,nages)
  matrix catage_tot(1,gmorph,0,nages)//sum the catches for all fleets, reuse matrix each year
  matrix Hrate(1,Nfleet,styr-nseas,k) //Harvest Rate for each fleet
  3darray catch_fleet(styr-nseas,TimeMax_Fore_std,1,Nfleet,1,6)
  matrix equ_catch_fleet(1,Nfleet,1,6)
//  matrix tot_catch_enc(1,Nfleet,styr-nseas,TimeMax) //total catch encountered for each fleet
//  matrix tot_catch_dead(1,Nfleet,styr-nseas,TimeMax) //total dead catch for each fleet
//  matrix tot_catch_ret(1,Nfleet,styr-nseas,TimeMax) //total retained catch for each fleet to be compared to observed catch amount
  matrix fec(1,gmorph,0,nages)            //relative fecundity at age, is the maturity times the weight-at-age times eggs/gm for females
  matrix virg_fec(1,gmorph,0,nages)
  number fish_bio;
  number fish_bio_r;
  number fish_bio_e;
  number fish_num_e;
  number fish_num;
  number fish_num_r;
  number vbio;
  number totbio;
  number smrybio;
  number smrynum;
  number harvest_rate;                        // Harvest rate
  matrix exp_AL(0,gender*nages+gender-1,1,nlength2);
  vector agetemp(0,gender*nages+gender-1)

  4darray Z_rate(styr-2*nseas,k,1,pop,1,gmorph,0,nages)
  matrix Zrate2(1,gmorph,0,nages)

 LOCAL_CALCS
  if(F_Method==2)    // continuous F
    {k=Nfleet*(TimeMax-styr+1);}
  else
    {k=-1;}
 END_CALCS
  init_bounded_number_vector F_rate(1,k,0.,8.,have_catch)

//  matrix SPRage(1,pop,0,3*nages);
  vector Nmigr(1,pop);
  number Nsurvive;
  number YPR_tgt_enc;
  number YPR_tgt_dead;
  number YPR_tgt_N_dead;
  number YPR_tgt_ret;
  number YPR_spr; number Vbio_spr; number Vbio1_spr; number SPR_actual;
//  number MSY_Fmult; number SPR_Fmult; number Btgt_Fmult;

  number YPR_Btgt_enc;
  number YPR_Btgt_dead;
  number YPR_Btgt_N_dead;
  number YPR_Btgt_ret;
  number YPR_Btgt; number Vbio_Btgt; number Vbio1_Btgt;
  number Btgt; number Btgttgt; number SPR_Btgt; number Btgt_Rec;
  number Bspr; number Bspr_rec;

  number YPR    // variable still used in SPR series
  number MSY
  number Bmsy
  number Recr_msy
  number YPR_msy_enc;
  number YPR_msy_dead;
  number YPR_msy_N_dead;
  number YPR_msy_ret;

  number YPR_enc;
  number YPR_dead;
  number YPR_N_dead;
  number YPR_ret;
  number MSY_Fmult;
  number SPR_Fmult;
  number Btgt_Fmult;

  number caa;
   number Fmult; number F_forecast;
   number Fchange;
   number last_calc;
   matrix ForeRatePattern(1,nseas,1,Nfleet);
   number alpha;
   number beta;
   number SPR;
   number GenTime;
//   3darray annualF(styr,YrMax,1,pop,1,gmorph)
   vector cumF(1,gmorph);
   vector maxF(1,gmorph);
   number Yield;
   number Adj4010;

  !!k1 = styr+(endyr-styr)*nseas-1 + nseas + 1;
  !!y=k1+N_Fore_Yrs*nseas-1;
  init_bounded_number_vector Q_parm(1,Q_Npar,Q_parm_LO,Q_parm_HI,Q_parm_PH)

  matrix log_q_cr(1,Ntypes,1,nyr_cr);
  matrix sd_cr(1,Ntypes,1,nyr_cr)
  matrix exp_cr(1,Ntypes,1,nyr_cr)    //  will store log(expected survey )
  vector surv_like(1,Ntypes) // likelihood of the indices
  matrix Q_dev_like(1,Ntypes,1,2) // likelihood of the Q deviations

  vector disc_like(1,Ntypes) // likelihood of the discard biomass
  vector mnwt_like(1,Ntypes) // likelihood of the mean body wt

  matrix exp_disc(1,Ntypes,1,nyr_disc)
  3darray retain(styr,endyr,1,Ntypes,1,nlength2)
  vector retain_M(1,nlength)
  3darray discmort(styr,endyr,1,Ntypes,1,nlength2)
  vector discmort_M(1,nlength)
  vector exp_mnwt(1,nobs_mnwt)

  matrix Morphcomp_exp(1,Morphcomp_nobs,6,5+Morphcomp_nmorph)   // expected value for catch by growthpattern

//  matrix WtFreq_begin(styr,endyr,1,nlength2);
  3darray WtFreqTrans(1,WtFreq_Nmeth*nseas,1,nlength2,1,WtFreq_Nbins_seas_g);

  matrix TG_alive(1,pop,1,gmorph)
  matrix TG_alive_temp(1,pop,1,gmorph)
  3darray TG_recap_exp(1,N_TG2,0,TG_endtime,0,Nfleet)   //  do not need to store POP index because each fleet is in just one area
  vector TG_like1(1,N_TG2)
  vector TG_like2(1,N_TG2)
  number overdisp     // overdispersion

 LOCAL_CALCS
  k=Do_TG*(3*N_TG+2*Nfleet);
 END_CALCS

    init_bounded_number_vector TG_parm(1,k,TG_parm_LO,TG_parm_HI,TG_parm_PH);

  // Selectivity-related parameters
  init_bounded_number_vector selparm(1,N_selparm2,selparm_LO,selparm_HI,selparm_PH)

   init_bounded_matrix selparm_dev(1,N_selparm_dev,selparm_dev_minyr,selparm_dev_maxyr,-10,10,selparm_dev_PH)

  4darray sel_l(styr,endyr+1,1,Ntypes,1,gender,1,nlength)
  4darray sel_l_r(styr,endyr+1,1,Ntypes,1,gender,1,nlength)   //  selex x retained
  4darray discmort2(styr,endyr+1,1,Ntypes,1,gender,1,nlength)
  4darray sel_a(styr,endyr+1,1,Ntypes,1,gender,0,nages)
  vector sel(1,nlength)  //  used to multiply by ALK
  4darray fish_body_wt(1,nseas,1,gmorph,1,Nfleet,0,nages);  // wt (adjusted for size selex)
  4darray sel_al_1(1,nseas,1,gmorph,1,Nfleet,0,nages);  // selected * wt
  4darray sel_al_2(1,nseas,1,gmorph,1,Nfleet,0,nages);  // selected * retained * wt
  4darray sel_al_3(1,nseas,1,gmorph,1,Nfleet,0,nages);  // selected numbers
  4darray sel_al_4(1,nseas,1,gmorph,1,Nfleet,0,nages);  // selected * retained numbers
  4darray deadfish(1,nseas,1,gmorph,1,Nfleet,0,nages);  // sel * (retain + (1-retain)*discmort)
  4darray deadfish_B(1,nseas,1,gmorph,1,Nfleet,0,nages);  // sel * (retain + (1-retain)*discmort) * wt

  4darray Sel_for_tag(TG_timestart*Do_TG,TimeMax*Do_TG,1,gmorph*Do_TG,1,Nfleet,0,nages)
  vector TG_report(1,Nfleet*Do_TG);
  vector TG_rep_decay(1,Nfleet*Do_TG);

  3darray save_sp_len(styr,endyr+1,1,Ntypes,0,50);     // use to output selex parm values after adjustment
  3darray save_sp_age(styr,endyr+1,1,Ntypes,0,50);


  3darray exp_l(1,Ntypes,1,nyr_l,1,nlen_bin2)
  matrix neff_l(1,Ntypes,1,nyr_l)
  vector exp_l_temp(1,nlength2);
  vector exp_l_temp_ret(1,nlength2);     // retained lengthcomp
  vector exp_l_temp_dat(1,nlen_bin2);
  vector offset_l(1,Ntypes) // Compute OFFSET for multinomial (i.e, value for the multinonial function
  vector length_like(1,Ntypes)  // likelihood of the length-frequency data

  matrix WtFreq_exp(1,WtFreq_totobs,1,WtFreq_Setup2);
  vector WtFreq_like(1,WtFreq_Nuse)
  3darray exp_a(1,Ntypes,1,nyr_a,1,n_abins2)
  vector exp_a_temp(1,n_abins2)
  vector tempvec(0,nages)
  matrix neff_a(1,Ntypes,1,nyr_a)
  vector offset_a(1,Ntypes) // Compute OFFSET for multinomial (i.e, value for the multinonial function
  vector age_like(1,Ntypes)  // likelihood of the age-frequency data
  vector sizeage_like(1,Ntypes)  // likelihood of the age-frequency data
  3darray exp_ms(1,Ntypes,1,nyr_ms,1,n_abins2)
  3darray exp_ms_sq(1,Ntypes,1,nyr_ms,1,n_abins2)

  number Morphcomp_like
  number equ_catch_like
  vector catch_like(1,Ntypes)
  number prior_rec
  number prior_fore_rec
  number parm_like
  number parm_dev_like
  number CrashPen
  number SoftBoundPen
  number Equ_penalty
  number F_ballpark_like
  number F_ballpark_lambda

  number R1
  number R1_exp
  number t1
  number t2
  number temp
  number temp1
  number temp2
  number join1
  number join2
  number join3
  number upselex
  number downselex
  number peak
  number peak2
  number point1
  number point2
  number point3
  number point4
  number timing
  number equ_Recr
  number equ_F_std

  vector SmryBio(styr-2,YrMax);
  vector SmryNum(styr-2,YrMax);
  matrix smry(styr-2,YrMax,1,7);  // bio, smrybio, enc_catch, dead_catch, ret_catch, spbio, recruit
  matrix env_data(styr-1,YrMax,-2,N_envvar)
  matrix TG_save(1,N_TG,1,3+TG_endtime)

  number R0
  number S0

  sdreport_vector spbio_std(1,N_STD_Yr);
  sdreport_vector recr_std(1,N_STD_Yr);
  sdreport_vector SPR_std(1,N_STD_Yr_Ofish);
  sdreport_vector F_std(1,N_STD_Yr_F);
  sdreport_vector depletion(1,N_STD_Yr_Dep);
  sdreport_vector Mgmt_quant(1,N_STD_mgmtquant)
  sdreport_vector Extra_Std(1,Extra_Std_N)

  vector MGparm_Like(1,N_MGparm2)
  vector init_F_Like(1,Nfleet)
  vector Q_parm_Like(1,Q_Npar)
  vector selparm_Like(1,N_selparm2)
  vector SR_parm_Like(1,6)
  !! k=Do_TG*(3*N_TG+2*Nfleet);
  vector TG_parm_Like(1,k);

  objective_function_value obj_fun
  number last_objfun
  vector phase_output(1,max_phase+1)
  !!cout<<"end of parameter section"<<endl;

//******************************************************************************************
//  ProgLabel_2000_#  PRELIMINARY_CALCS_SECTION
PRELIMINARY_CALCS_SECTION
  random_number_generator radm(long(time(&finish)));
  if(F_ballpark_yr>endyr) F_ballpark_yr=endyr;
  if(F_ballpark_yr>=styr) {F_ballpark_lambda=1.;} else {F_ballpark_lambda=0.;}
  sel_l.initialize();sel_a.initialize();
  offset_l.initialize();offset_a.initialize();
  save_sp_len.initialize(); save_sp_age.initialize();

  if(Turn_off_phase<=0) {dummy_parm=0.5;} else {dummy_parm=1.0;}
  cout<<" do variance adjustment and tail compression "<<endl;

//  AL(1)=0.0;
//  AL(nlength1)=1.0;
  Cohort_Growth=1.0;    // adjustment for cohort growth deviations
  for (f=1; f<=Ntypes; f++)
    {
    if(nyr_cr(f)>0)
      {
      for (i=1; i<=nyr_cr(f); i++)
        {
        if(obs_cr(f,i)>0)
          {
          cv_cr(f,i)+=var_adjust(1,f);
          if(cv_cr(f,i)<=0.0) cv_cr(f,i)=0.001;
          }
        }
      cout<<" survey OK "<<endl;
      }

    if(nyr_disc(f)>0)
      {
      for (i=1; i<=nyr_disc(f); i++)
        {
        if(obs_disc(f,i)>=0.)
          {
//          cv_disc(f,i)+=var_adjust(2,f);   // OK to do this because the -9999 super year flag has already  been processed
          if(cv_disc(f,i)<=0.0) cv_disc(f,i)=0.001;
          }
//        sd_disc(f,j)=cv_disc(f,j)*obs_disc(f,j);   //  index typo  error discovered on 6/20/2007
        sd_disc(f,i)=cv_disc(f,i)*obs_disc(f,i);
        sd_disc(f,i)+=var_adjust(2,f);
        if(sd_disc(f,i)<0.001) sd_disc(f,i)=0.001;
        }
      }
    cout<<" discard OK "<<endl;
    }

  for(i=1;i<=nobs_mnwt;i++)
  {
    if(mnwtdata(5,i)>0.)
    {
      mnwtdata(6,i)+=var_adjust(3,mnwtdata(3,i));
      if(mnwtdata(6,i)<=0.0) mnwtdata(6,i)=0.001;
      mnwtdata(7,i)=mnwtdata(5,i)*mnwtdata(6,i);
      mnwtdata(8,i)=DF_bodywt*square(mnwtdata(7,i));
      mnwtdata(9,i)=sd_offset*log(mnwtdata(7,i));
    }
  }
    cout<<" mnwt OK "<<endl;
// Compute OFFSET for length comp
  if(nobsl>0)
  for (f=1; f <= Ntypes; f++)
  for (i=1; i <= nyr_l(f); i++)
  if(nsamp_l(f,i)>0)
  { nsamp_l(f,i)*=var_adjust(4,f);  {if(nsamp_l(f,i)<=1.0) nsamp_l(f,i)=1.;}                              //  adjust sample size
  if(gen_l(f,i) !=2) offset_l(f) -= nsamp_l(f,i) *
    obs_l(f,i)(tails_l(f,i,1),tails_l(f,i,2))*log(obs_l(f,i)(tails_l(f,i,1),tails_l(f,i,2)));
  if(gen_l(f,i) >=2) offset_l(f) -= nsamp_l(f,i) *
    obs_l(f,i)(tails_l(f,i,3),tails_l(f,i,4))*log(obs_l(f,i)(tails_l(f,i,3),tails_l(f,i,4)));
  }

// Compute OFFSET for age comp
  if(nobsa>0)
  for (f=1; f <= Ntypes; f++)
  for (i=1; i <= nyr_a(f); i++)
  if(nsamp_a(f,i)>0)
  {nsamp_a(f,i)*=var_adjust(5,f);  {if(nsamp_a(f,i)<=1.0) nsamp_a(f,i)=1.;}                                //  adjust sample size
  if(gen_a(f,i) !=2) offset_a(f) -= nsamp_a(f,i) *
    obs_a(f,i)(tails_a(f,i,1),tails_a(f,i,2))*log(obs_a(f,i)(tails_a(f,i,1),tails_a(f,i,2)));
  if(gen_a(f,i) >=2) offset_a(f) -= nsamp_a(f,i) *
    obs_a(f,i)(tails_a(f,i,3),tails_a(f,i,4))*log(obs_a(f,i)(tails_a(f,i,3),tails_a(f,i,4)));
  }
   cout<<" agecomp offset "<<offset_a<<endl;

// adjust input sample size for mean size-at-age
  if(nobs_ms>0)
  {for (f=1; f <= Ntypes; f++)
  for (i=1; i <= nyr_ms(f); i++)
  for(b=1;b<=n_abins2;b++)
    {if(obs_ms_n(f,i,b)>0) {obs_ms_n(f,i,b)=sqrt(var_adjust(6,f)*obs_ms_n(f,i,b));{if(obs_ms_n(f,i,b)<=1.0) obs_ms_n(f,i,b)=1.;}  }
  }}


//================================    ProgLabel_041
// Compute the reverse pointers
  cout<<" reverse pointers "<<endl;
  yr_cr2.initialize();
  yr_disc2.initialize();
  yr_l2.initialize();
  yr_a2.initialize();
  yr_ms2.initialize();

  for (f=1; f<=Ntypes; f++)
  {
    if(nyr_cr(f)>0)
    for (i=1; i<=nyr_cr(f); i++)
     {
      if(yr_cr_y(f,i)>=styr && yr_cr_y(f,i)<=retro_yr)
       {
         if(yr_cr2(f,yr_cr(f,i))>0)
         {
          cout<<" fatal error "<<endl;
          warning<<" replicate survey observations are not allowed (fleet, ith obs, year) "<<f<<" "<<i<<" "<<yr_cr(f,i)<<endl; exit(1);
        }
        else
        {
         yr_cr2(f,yr_cr(f,i))=i;have_data(f,yr_cr(f,i))=1;
       }     //  yr_cr(f,i) stores value of t so has period within year info
      }
     }

   if(nyr_disc(f)>0)
   for (i=1; i<=nyr_disc(f); i++)
       {yr_disc2(f,yr_disc(f,i))=i;
        have_data(f,yr_disc(f,i))=1;
     }

   if(nyr_l(f)>0)
   for (i=1; i<=nyr_l(f); i++)
   {
    if(yr_l2(1,f,yr_l(f,i))==0) yr_l2(1,f,yr_l(f,i))=i;    //  stores index of first obs of this type/time
    yr_l2(2,f,yr_l(f,i))=i;   //  stores index of last obs of this type/time
    have_data(f,yr_l(f,i))=1;
   }

   if(nyr_a(f)>0)
   for (i=1; i <= nyr_a(f); i++)
   {
    if(yr_a2(1,f,yr_a(f,i))==0) yr_a2(1,f,yr_a(f,i))=i;    //  stores index of first obs of this type/time
    yr_a2(2,f,yr_a(f,i))=i;   //  stores index of last obs of this type/time
    have_data(f,yr_a(f,i))=1;
   }

   if(nyr_ms(f)>0)
   for (i=1; i <= nyr_ms(f); i++)
   {
    if(yr_ms2(1,f,yr_ms(f,i))==0) yr_ms2(1,f,yr_ms(f,i))=i;    //  stores index of first obs of this type/time
    yr_ms2(2,f,yr_ms(f,i))=i;   //  stores index of last obs of this type/time
    have_data(f,yr_ms(f,i))=1;
   }
  }
  cout<<" done reverse pointers "<<endl;


//================================ ProgLabel_042
//  calc the age transition matrix
   //  FUTURE: calculate adjustment to oldest age based on continued ageing of old fish
    age_age.initialize();

    if(N_ageerr>0)
      {
   for (j=1; j<=N_ageerr;j++)
   {
   for (a=0; a<=nages;a++)
    {
     if(age_err(j,1,a)<=-1)
     {age=double(a)+0.5; age_err(j,1,a)=age; }
     else
     {age=age_err(j,1,a);}
     if(age_err(j,2,a)<=0.0)
       {
       N_warn++;
       warning<<" ageing error was 0.0 for key, age: "<<j<<" "<<a<<endl;
       age_err(j,2,a)=0.001;
       }

     for (b=2;b<=n_abins;b++)
       age_age(j,b,a)= cumd_norm((age_bins(b)-age)/age_err(j,2,a));

     for (b=1;b<=n_abins-1;b++)
       age_age(j,b,a) -= age_age(j,b+1,a);

     age_age(j,n_abins,a) -= 1.;
    }

     age_age(j) *= -1;

     if(gender == 2)                     //  copy ageing error matrix into male location also
     {
      L2=n_abins;
      A2=nages+1;
      for(b=1;b<=n_abins;b++)
      for(a=0;a<=nages;a++)
       {age_age(j,b+L2,a+A2)=age_age(j,b,a);}
     }
      }}

       for (f=1;f<=Nfleet;f++)
       if(obs_equ_catch(f)<=0.001)
       {init_F(f)=0.0;}

// ****************************************  // ProgLabel_043
//   do assignments of initial parameter values, using the "read" values from the "CTL" file
//   skip this assignment if the parameters are being read from a "SS2.PAR" file

   if(readparfile==0)
   {
    cout<< " set parms to init values in CTL file "<<endl;
    for(i=1;i<=N_MGparm2;i++)
    MGparm(i) = MGparm_RD(i);    //  set vector of initial natmort and growth parms

    for(i=1;i<=6;i++)
    {SR_parm(i)=SR_parm_1(i,3);}

    if(recdev_do_early>0) recdev_early.initialize();
    if(Do_Forecast>0) fore_recruitments.initialize();

    if(do_recdev==1)
    {recdev1.initialize();}                // set devs to zero
    else if(do_recdev==2)
    {recdev2.initialize();}                // set devs to zero

    if(recdev_read>0)
    {
      for(j=1;j<=recdev_read;j++)
      {
        y=recdev_input(j,1);
        if(y>=recdev_first && y<=YrMax)
        {
          if(y<recdev_start)
          {
            recdev_early(y)=recdev_input(j,2);
          }
          else if (y<=recdev_end)
          {
            if(do_recdev==1)
            {recdev1(y)=recdev_input(j,2);}
            else if(do_recdev==2)
            {recdev2(y)=recdev_input(j,2);}
          }
          else
          {
            fore_recruitments(y)=recdev_input(j,2);
          }
        }
        else
        {
          N_warn++; warning<<" Trying to specify a recdev out of allowable range of years "<<y<<endl;
        }
      }
      if(recdev_do_early>0) recdev_early-=sum(recdev_early)/(float(recdev_early_end-recdev_early_start+1));
      if(do_recdev==1) recdev1-=sum(recdev1)/(float(recdev_end-recdev_start+1));
      //  no rescaling for recdev2 or fore_recruitments because not dev_vectors
    }

// **************************************************
    for(i=1;i<=Q_Npar;i++)
        {Q_parm(i) = Q_parm_1(i,3);}    //  set vector of initial index Q parms

    for(i=1;i<=Nfleet;i++)
    init_F(i) = init_F_RD(i);    //  set vector of initial parms

    if(F_Method==2)
    {
      g=0;
      for(f=1;f<=Nfleet;f++)
      for(y=styr;y<=endyr;y++)
      for(s=1;s<=nseas;s++)
      {
        t=styr+(y-styr)*nseas+s-1;
        g++;
        if(catch_ret_obs(f,t)>0.)
        {
          F_rate(g)=F_setup(1);
        }
        else
        {F_rate(g)=0.;}
      }
      if(F_detail>0)
      {
        for(k=1;k<=F_detail;k++)
        {
          f=F_setup2(k,1); y=F_setup2(k,2); s=F_setup2(k,3);
          g=(f-1)*(TimeMax-styr+1)+(y-styr)*nseas+s;
          if(F_setup2(k,4)!=-999) F_rate(g)=F_setup2(k,4);
        }
      }
    }

    for(i=1;i<=N_selparm2;i++)
    selparm(i) = selparm_RD(i);    //  set vector of initial selex parms

    if(Do_TG>0)
    {
    k=Do_TG*(3*N_TG+2*Nfleet);
    for(i=1;i<=k;i++)
    {
      TG_parm(i)=TG_parm2(i,3);
    }
  }
   }


//  check bounds and do jitter
    for(i=1;i<=N_MGparm2;i++)
    if(MGparm_PH(i)>0)
    {MGparm(i)=Check_Parm(MGparm_LO(i),MGparm_HI(i), jitter, MGparm(i));}

    for(i=1;i<=6;i++)
    if(SR_parm_1(i,7)>0)
    {SR_parm(i) = Check_Parm(SR_parm_1(i,1),SR_parm_1(i,2), jitter, SR_parm(i));}

    if(recdev_do_early>0 && recdev_early_PH>0)
    {
    for(y=recdev_early_start;y<=recdev_early_end;y++)
      {recdev_early(y) = Check_Parm(recdev_LO, recdev_HI, jitter, recdev_early(y));}
      recdev_early -=sum(recdev_early)/(recdev_early_end-recdev_early_start+1);
    }

    if(recdev_PH>0 && do_recdev>0)
    {
      if(do_recdev==1)
      {
        for(i=recdev_start;i<=recdev_end;i++)
        {recdev1(i) = Check_Parm(recdev_LO, recdev_HI, jitter, recdev1(i));}
        recdev1 -=sum(recdev1)/(recdev_end-recdev_start+1);
      }
      else
      {
        for(i=recdev_start;i<=recdev_end;i++)
        {recdev2(i) = Check_Parm(recdev_LO, recdev_HI, jitter, recdev2(i));}
        recdev2 -=sum(recdev2)/(recdev_end-recdev_start+1);
      }
    }

    if(Q_Npar>0)
    {
    for(i=1;i<=Q_Npar;i++)
    if(Q_parm_1(i,7)>0)
    {Q_parm(i) = Check_Parm(Q_parm_1(i,1),Q_parm_1(i,2), jitter, Q_parm(i));}
    }

    for(i=1;i<=Nfleet;i++)
      {
      if(init_F_PH(i)>0)
        {init_F(i) = Check_Parm(init_F_LO(i),init_F_HI(i), jitter, init_F(i));}
      }

    for(i=1;i<=N_selparm2;i++)
    if(selparm_PH(i)>0)
    {selparm(i)=Check_Parm(selparm_LO(i),selparm_HI(i), jitter, selparm(i));}

    if(Do_TG>0)
    {
      k=Do_TG*(3*N_TG+2*Nfleet);
      for(i=1;i<=k;i++)
      {
      if(TG_parm_PH(i)>0)
        {TG_parm(i)=Check_Parm(TG_parm_LO(i),TG_parm_HI(i), jitter, TG_parm(i));}
      }
    }
//  end bound check and jitter

    env_data.initialize();
    if(N_envvar>=1)
      {
      for (y=styr-1;y<=(YrMax);y++)
        for(j=1;j<=N_envvar;j++)
          {env_data(y,j)=env_data_RD(y,j);}
      }

    if(Rebuild_Ydecl==-1) Rebuild_Ydecl=1999;
    if(Rebuild_Yinit==-1) Rebuild_Yinit=endyr+1;

    if(Rebuild_Ydecl>YrMax) Rebuild_Ydecl=YrMax;
    if(Rebuild_Yinit>YrMax) Rebuild_Yinit=YrMax;

    migrrate.initialize();
    depletion.initialize();
    sel_l.initialize(); sel_a.initialize(); retain.initialize();  discmort.initialize();

    Richards=1.0;

    do_once=1;
    niter=0;
    y=styr;
    yz=styr;
    t_base=styr+(y-styr)*nseas-1;
    get_MGsetup();

    get_growth1();
    VBK_seas=value(VBK_seas);
    wtlen_seas=value(wtlen_seas);
    CVLmin=value(CVLmin);
    CVLmax=value(CVLmax);

    get_growth2();
    cout<<" did growth once"<<endl;
    if(minL>10.0) {N_warn++; warning<<" Minimum size bin is:_"<<minL<<"; which is >10cm, which is large for use as size-at-age 0.0 recruitment"<<endl;}
    temp=max(column(Use_Ave_Size(1),nages));
    if(temp>0.95*len_bins(nlength)) {N_warn++; warning<<" Maximum size at age: "<<temp
    <<"; is within 5% of the largest size bin: "<<len_bins(nlength)<<"; Add more bins"<<endl;}
    get_natmort();
    natM = value(natM);
    surv1 = value(surv1);
    surv2 = value(surv2);
    cout<<" did natmort once "<<endl;

    get_wtlen();
    wt_len=value(wt_len);
    wt_len2=value(wt_len2);
    wt_len_fd=value(wt_len_fd);
    mat_len=value(mat_len);
    mat_len_wt=value(mat_len_wt);
    mat_age=value(mat_age);
    cout<<" did wtlen and maturity once"<<endl;

    for(s=1;s<=nseas;s++)
    {
      t = styr+s-1;
      Make_AgeLength_Key();
    ALK(s) = value(ALK(s));
    }
    Wt_Age_beg=value(Wt_Age_beg);
    fec = value(fec);

    get_recr_distribution();
    recr_dist = value(recr_dist);    //  so the just calculated constant values will be used unless its parms are active

    if(do_migration>0)
    {
      get_migration();
      migrrate=value(migrrate);
    }
    if(Turn_off_phase<0) {cout<<" Requested exit after read when turn_off_phase < 0 "<<endl; exit(1);}
    cout<<endl<<endl<<"Estimating...please wait..."<<endl;
    last_objfun=1.0e30;
    if(Do_ParmTrace==1 || Do_ParmTrace==4)
    {
    ParmTrace<<"Phase Iter ObjFun Change SPB_start SPB_end";
    for(i=1;i<=active_count;i++) {ParmTrace<<" "<<ParmLabel(active_parm(i));}
    ParmTrace<<endl;
    }
    else if(Do_ParmTrace>=2)
   {
    ParmTrace<<"Phase Iter ObjFun Change SPB_start SPB_end";
    for(i=1;i<=ParCount;i++) {ParmTrace<<" "<<ParmLabel(i);}
    ParmTrace<<endl;
    }

// ****************************************************************************************************************
//  ProgLabel_3000_#  PROCEDURE_SECTION
PROCEDURE_SECTION
   niter++;
    if( mceval_phase() && (initial_params::mc_phase==0))
   {
      Do_ParmTrace=0;
      biasadj=1.;
    }

  Mgmt_quant.initialize();
  if(recdev_do_early>0) {recdev(recdev_early_start,recdev_early_end)=recdev_early(recdev_early_start,recdev_early_end);}
  if(do_recdev==1)
    {recdev(recdev_start,recdev_end)=recdev1(recdev_start,recdev_end);}
  else if(do_recdev==2)
    {recdev(recdev_start,recdev_end)=recdev2(recdev_start,recdev_end);}
  if(Do_Forecast>0) recdev(recdev_end+1,YrMax)=fore_recruitments(recdev_end+1,YrMax);  // only needed here for reporting
  if(mccounter==1 || (mccounter>burn_intvl &  ((double(mccounter)/double(thin_intvl)) - double((mccounter/thin_intvl))==0)  )) // check to see if burn in period is over
    {

    CrashPen.initialize();
    if(last_phase() || current_phase()==max_phase) {F_ballpark_lambda=0.0;}
    y=styr;
    get_initial_conditions();
      if(do_once==1) cout<<" OK with initial conditions "<<endl;
    get_time_series();
      if(do_once==1) cout<<" OK with time series "<<endl;

    evaluate_the_objective_function();
    if(do_once==1) cout<<" OK with obj_func "<<endl;
    do_once=0;
    if( (sd_phase() || mceval_phase()) && (initial_params::mc_phase==0))
    {
      if(Fore_Rel_Harvest==1)
      {
        for(f=1;f<=Nfleet;f++)
        for(s=1;s<=nseas;s++)
        {t=styr+(endyr-styr)*nseas+s-1; ForeRatePattern(s,f)=Hrate(f,t);}
      }
      else
      {
        for(f=1;f<=Nfleet;f++)
        for(s=1;s<=nseas;s++)
        {ForeRatePattern(s,f)=Input_ForeRate(s,f);}
      }

      if(Do_Benchmark>0)
      {
        Get_Benchmarks();
        did_MSY=1;
      }
      else
      {Mgmt_quant(1)=S0;}

      if(mceval_phase()==0) {show_MSY=1;}

      if(Do_Forecast>0) {Get_Forecast(); did_MSY=1;}

      Process_STDquant();

    if(Selex_Std_Cnt>0)
    {
      for(i=1;i<=Selex_Std_Cnt;i++)
      {
        j=Selex_Std_Pick(i);
        if(Selex_Std_AL==1)
        {
          Extra_Std(i)=sel_l(Selex_Std_Year,Do_Selex_Std,1,j);
          if(gender==2) Extra_Std(i+Selex_Std_Cnt)=sel_l(Selex_Std_Year,Do_Selex_Std,2,j);
        }
        else
        {
          Extra_Std(i)=sel_a(Selex_Std_Year,Do_Selex_Std,1,j);
          if(gender==2) Extra_Std(i+Selex_Std_Cnt)=sel_a(Selex_Std_Year,Do_Selex_Std,2,j);
        }
      }
    }

    if(Growth_Std_Cnt>0)
    {
      for(i=1;i<=Growth_Std_Cnt;i++)
      {
        j=Growth_Std_Pick(i);  // selected age
        k=GP_finder(Do_Growth_Std,1);  // selected GP and gender  gp3
        Extra_Std(gender*Selex_Std_Cnt+i)=Use_Ave_Size(1,k,j);
        k=GP_finder(Do_Growth_Std,2);  // selected GP and gender  gp3
        if(gender==2) Extra_Std(gender*Selex_Std_Cnt+Growth_Std_Cnt+i)=Use_Ave_Size(1,k,j);
      }
    }

    if(NatAge_Std_Cnt>0)
    {
      if(Do_NatAge_Std<0)  // selected area
      {
        p1=1; p2=pop;
      }
      else
      {
        p1=Do_NatAge_Std; p2=Do_NatAge_Std;
      }
      y=NatAge_Std_Year;
      t=styr+(y-styr)*nseas;  // first season of selected year
      for(i=1;i<=NatAge_Std_Cnt;i++)
      {
        a=NatAge_Std_Pick(i);  // selected age
        temp=0.;
        for(p=p1;p<=p2;p++)
        {
          for(g=1;g<=gmorph;g++)
          if(sx(g)==1 && use_morph(g)>0)
          {
            temp+=natage(t,p,g,a);  //  note, uses season 1 only
          }
        }
        Extra_Std(gender*(Selex_Std_Cnt+Growth_Std_Cnt)+i)=temp;
        if(gender==2)
        {
          temp=0.;
          for(p=p1;p<=p2;p++)
          {
            for(g=1;g<=gmorph;g++)
            if(sx(g)==2 && use_morph(g)>0)
            {
              temp+=natage(t,p,g,a);  //  note, uses season 1 only
            }
          }
          Extra_Std(gender*(Selex_Std_Cnt+Growth_Std_Cnt)+NatAge_Std_Cnt+i)=temp;
        }
      }
    }

    if(Selex_Std_Cnt<=0 && Growth_Std_Cnt<=0 && NatAge_Std_Cnt==0)
    {
      Extra_Std(1)=S0;
    }

    }  // end of things to do in std_phase

    if(current_phase() <= max_phase+1) phase_output(current_phase())=value(obj_fun);


    if(rundetail>1)
      {
       if(nobs>0) cout<<" CPUE " <<surv_like<<endl;
       if(nobs_disc>0) cout<<" Disc " <<disc_like<<endl;
       if(nobs_mnwt>0) cout<<" MnWt " <<mnwt_like<<endl;
       if(nobsl>0) cout<<" LEN  " <<length_like<<endl;
       if(nobsa>0) cout<<" AGE  " <<age_like<<endl;
       if(nobs_ms>0) cout<<" L-at-A  " <<sizeage_like<<endl;
       if(WtFreq_Nmeth>0) cout<<" Wtfreq "<<WtFreq_like<<endl;
       if(Do_TG>0) cout<<" TG-fleetcomp "<<TG_like1<<endl<<" TG-negbin "<<TG_like2<<endl;
       cout<<" Recr " <<prior_rec<<endl;
       cout<<" Parm_Priors " <<parm_like<<endl;
       cout<<" SoftBound "<<SoftBoundPen<<endl;
       cout<<" F_ballpark " <<F_ballpark_like<<" Lambda: "<<F_ballpark_lambda<<endl;
       if(F_Method>1) {cout<<"Catch "<<catch_like;} else {cout<<"  crash "<<CrashPen;}
       cout<<" EQUL " <<equ_catch_like<<endl;
      }
     if(rundetail>0)
     {
     cout<<current_phase()<<" "<<niter<<" -log(L): "<<obj_fun<<"  Spbio: "<<value(Spbio_tot(styr))<<
       " "<<value(Spbio_tot(endyr));
       if(F_ballpark_lambda>0.) cout<<" F_like " <<F_ballpark_like;
       if(F_Method>1) {cout<<" cat "<<sum(catch_like);}
       else {cout<<"  crash "<<CrashPen;}
       cout<<endl;
     }

      if((Do_ParmTrace==1 && obj_fun<=last_objfun) || Do_ParmTrace==4)
      {
        ParmTrace<<current_phase()<<" "<<niter<<" "<<obj_fun<<" "<<obj_fun-last_objfun<<" "<<value(Spbio_tot(styr))<<" "<<value(Spbio_tot(endyr));
        for(j=1;j<=MGparm_PH.indexmax();j++)
        {
          if(MGparm_PH(j)>=0) {ParmTrace<<" "<<MGparm(j);}
        }
        if(MGparm_dev_PH>0) {ParmTrace<<" "<<MGparm_dev;}
        for(j=1;j<=SRvec_PH.indexmax();j++)
        {
          if(SRvec_PH(j)>=0) {ParmTrace<<" "<<SR_parm(j);}
        }
        if(recdev_early_PH>0) {ParmTrace<<" "<<recdev_early;}
        if(recdev_PH>0)
        {
          if(do_recdev==1) {ParmTrace<<" "<<recdev1;}
          if(do_recdev==2) {ParmTrace<<" "<<recdev2;}
        }
        if(Do_Forecast>0) ParmTrace<<fore_recruitments<<" ";
        for(f=1;f<=Nfleet;f++)
        {
          if(init_F_PH(f)>0) {ParmTrace<<" "<<init_F(f);}
        }
        if(F_Method==2)    // continuous F
        {
          for(k=1;k<=F_rate.indexmax();k++)
          {
            if(have_catch(k)>0) {ParmTrace<<" "<<F_rate(k);}
          }
        }
        for(f=1;f<=Q_Npar;f++)
        {
          if(Q_parm_PH(f)>0) {ParmTrace<<" "<<Q_parm(f);}
        }
        for(k=1;k<=selparm_PH.indexmax();k++)
        {
          if(selparm_PH(k)>0) {ParmTrace<<" "<<selparm(k);}
        }
        if(selparm_dev_PH>0) {ParmTrace<<" "<<selparm_dev;}
        for(k=1;k<=TG_parm_PH.indexmax();k++)
        {
          if(TG_parm_PH(k)>0) {ParmTrace<<" "<<TG_parm(k);}
        }
//        ParmTrace<<surv_like<<" "<<length_like<<" "<<age_like;
//        ParmTrace<<" "<<natage(styr,1,1)<<" "<<natage(endyr,1,1);
//        ParmTrace<<deadfish_B(1,1,1)<<" "<<sel_a(styr,1,1)<<" "<<Wt_Age_mid(1,1);
        ParmTrace<<endl;
      }
      else if((Do_ParmTrace==2 && obj_fun<=last_objfun) || Do_ParmTrace==3)
      {
        ParmTrace<<current_phase()<<" "<<niter<<" "<<obj_fun<<" "<<obj_fun-last_objfun<<" "<<value(Spbio_tot(styr))<<" "<<value(Spbio_tot(endyr));
        ParmTrace<<" "<<MGparm<<" ";
        if(N_MGparm_dev>0) ParmTrace<<MGparm_dev<<" ";
        ParmTrace<<SR_parm<<" ";
        if(recdev_do_early>0) ParmTrace<<recdev_early<<" ";
        if(do_recdev==1) {ParmTrace<<recdev1<<" ";}
        if(do_recdev==2) {ParmTrace<<recdev2<<" ";}
        if(Do_Forecast>0) ParmTrace<<fore_recruitments<<" ";
        ParmTrace<<init_F<<" ";
        if(F_Method==2) ParmTrace<<" "<<F_rate;
        if(Q_Npar>0) ParmTrace<<Q_parm<<" ";
        ParmTrace<<selparm<<" ";
        if(N_selparm_dev>0) ParmTrace<<selparm_dev<<" ";
        if(Do_TG>0) ParmTrace<<TG_parm<<" ";
        ParmTrace<<endl;
      }
      last_objfun=obj_fun;
     docheckup=0;  // turn off reporting to checkup.sso
     if(mceval_phase() ) get_posteriors();
    }
  if(mceval_phase() ) mccounter += 1;   // increment the counter

//********************************************************************
//  ProgLabel_5000_#  RUNTIME_SECTION (not used in SS)
RUNTIME_SECTION
//  maximum_function_evaluations 200, 200, 200, 200, 200, 200, 200, 2000;
//  convergence_criteria 100, 10, 1, 0.1, 1e-4, 1e-4, 1e-4, 1e-4;

//  ProgLabel_5100_#  TOP_OF_MAIN_SECTION
TOP_OF_MAIN_SECTION
  arrmblsize = 50000000;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(20000000000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(170000000);
  gradient_structure::set_MAX_NVAR_OFFSET(5000);
  gradient_structure::set_NUM_DEPENDENT_VARIABLES(10000);
//  arrmblsize = 50000000;
//  gradient_structure::set_GRADSTACK_BUFFER_SIZE(20000000000);
//  gradient_structure::set_CMPDIF_BUFFER_SIZE(100000000);
//  gradient_structure::set_MAX_NVAR_OFFSET(5000);
// gradient_structure::set_NUM_DEPENDENT_VARIABLES(5000);
//  arrmblsize = 50000000;
//  gradient_structure::set_GRADSTACK_BUFFER_SIZE(10000000000);
//  gradient_structure::set_CMPDIF_BUFFER_SIZE(100000000);
//  gradient_structure::set_MAX_NVAR_OFFSET(5000);
//  gradient_structure::set_NUM_DEPENDENT_VARIABLES(5000);
//  arrmblsize = 5000000;
//  gradient_structure::set_GRADSTACK_BUFFER_SIZE(6000000);
//  gradient_structure::set_CMPDIF_BUFFER_SIZE(10000000);
//  gradient_structure::set_MAX_NVAR_OFFSET(500);
//  gradient_structure::set_NUM_DEPENDENT_VARIABLES(500);
  time(&start); //this is to see how long it takes to run

//  ProgLabel_5200_#   GLOBALS_SECTION
GLOBALS_SECTION
  #include <admodel.h>
  #include <time.h>
  time_t start,finish;
  long hour,minute,second;
  double elapsed_time;
  ofstream warning("warning.SSO");
  ofstream checkup("checkup.SSO");
  ofstream echoinput("echoinput.SSO");
  ofstream ParmTrace("ParmTrace.SSO");
  ofstream report5("Forecast-report.SSO");
  adstring_array ParmLabel;  // extendable array to hold the parameter labels
  adstring_array fleetname;
  adstring depletion_basis_label;
  adstring F_report_label;
  adstring SPR_report_label;
  adstring onenum(4);
  adstring version_info;
  adstring_array Starter_Comments;
  adstring_array Data_Comments;
  adstring_array Control_Comments;
  adstring_array Forecast_Comments;
  random_number_generator radm(long(time(&finish)));

//  ProgLabel_5300_#  BETWEEN_PHASES_SECTION
BETWEEN_PHASES_SECTION
  F_ballpark_lambda *=0.1;

//  objective_function_value::pobjfun->gmax;    // this does not seem to report the correct value
//  cout<<" max gradient "<<gmax<<endl;


//ProgLabel_5400_#  FINAL_SECTION
FINAL_SECTION
  //Calculates how long is taking to run
  int jj;
  time(&finish);
  elapsed_time = difftime(finish,start);
  hour = long(elapsed_time)/3600;
  minute = long(elapsed_time)%3600/60;
  second = (long(elapsed_time)%3600)%60;
  cout<<endl<<endl<<"starting time: "<<ctime(&start);
  cout<<"finishing time: "<<ctime(&finish);
  cout<<"This run took: ";
  cout<<hour<<" hours, "<<minute<<" minutes, "<<second<<" seconds."<<endl<<endl;
  ofstream covarout("CoVar.SSO");
  covarout<<"active-i active-j all-i all-j Par?-i Par?-j label-i label-j corr"<<endl;

  for(i=1;i<=CoVar_Count;i++)
  {
    covarout<<i<<" "<<0<<" "<<active_parm(i)<<" "<<active_parm(i);
    if(i<=active_count) {covarout<<" Par ";} else {covarout<<" Der ";}
    covarout<<" Std "<<ParmLabel(active_parm(i))<<"   _   "<<CoVar(i,1)<<endl;
    for(j=2;j<=i;j++)
    {
      covarout<<i<<" "<<j-1<<" "<<active_parm(i)<<" "<<active_parm(j-1);
      if(i<=active_count) {covarout<<" Par ";} else {covarout<<" Der ";}
      if((j-1)<=active_count) {covarout<<" Par ";} else {covarout<<" Der ";}
      covarout<<ParmLabel(active_parm(i))<<" "<<ParmLabel(active_parm(j-1))<<" "<<CoVar(i,j)<<endl;
    }
  }

  cout<<"Finished writing COVAR.SSO"<<endl;
  save_for_report=1;
  CrashPen.initialize();
  save_gparm=0;
  y=styr;
  get_initial_conditions();
  get_time_series();
  evaluate_the_objective_function();
    if(Fore_Rel_Harvest==1)
    {
      for(f=1;f<=Nfleet;f++)
      for(s=1;s<=nseas;s++)
      {t=styr+(endyr-styr)*nseas+s-1; ForeRatePattern(s,f)=Hrate(f,t);}
    }
    else
    {
      for(f=1;f<=Nfleet;f++)
      for(s=1;s<=nseas;s++)
      {ForeRatePattern(s,f)=Input_ForeRate(s,f);}
    }

      if(Do_Benchmark>0)
      {
        if(did_MSY==0) Get_Benchmarks();
      }
      else
      {Mgmt_quant(1)=S0;}
      if(mceval_phase()==0) {show_MSY=1;}

      if(Do_Forecast>0) {Get_Forecast();}
  Process_STDquant();
  write_bigoutput();
  cout<<" finished big report "<<endl;
  if(Do_CumReport>0) write_summaryoutput();
  cout<<" finished summary report "<<endl;
  if(Do_Rebuilder>0) write_rebuilder_output();
  cout<<" finished rebuilder report "<<endl;
  write_nudata();
  cout<<" finished nudata report "<<endl;
  write_nucontrol();
  cout<<" finished nucontrol report "<<endl;
  write_Bzero_output();
  if(N_warn>0) cout<<endl<<"See warning.sso for N warnings: "<<N_warn<<endl;

//  ProgLabel_5500_#  REPORT_SECTION
REPORT_SECTION

  if(nobs>0) report<<" CPUE " <<surv_like<<endl;
  if(nobs_disc>0) report<<" Disc " <<disc_like<<endl;
  if(nobs_mnwt>0) report<<" MnWt " <<mnwt_like<<endl;
  if(nobsl>0) report<<" LEN  " <<length_like<<endl;
  if(nobsa>0) report<<" AGE  " <<age_like<<endl;
  if(nobs_ms>0) report<<" L-at-A  " <<sizeage_like<<endl;
  report<<" EQUL " <<equ_catch_like<<endl;
  report<<" Recr " <<prior_rec<<endl;
  report<<" Parm " <<parm_like<<endl;
  report<<" F_ballpark " <<F_ballpark_like<<" Lambda: "<<F_ballpark_lambda<<endl;
  if(F_Method>1) {report<<"Catch "<<catch_like<<endl;} else {report<<"  crash "<<CrashPen<<endl;}
  if(WtFreq_Nmeth>0) report<<" Wtfreq "<<WtFreq_like<<endl;
  if(Do_TG>0) report<<" TG-fleetcomp "<<TG_like1<<endl<<" TG-negbin "<<TG_like2<<endl;
  report<<" -log(L): "<<obj_fun<<"  Spbio: "<<value(Spbio_tot(styr))<<
  " "<<value(Spbio_tot(endyr))<<endl;

  report<<endl<<"Year Spbio Recruitment"<<endl;
  report<<"Virg "<<Spbio_tot(styr-2)<<" "<<use_rec(styr-2)<<endl;
  report<<"Init "<<Spbio_tot(styr-1)<<" "<<use_rec(styr-1)<<endl;
  for(y=styr;y<=endyr;y++) report<<y<<" "<<Spbio_tot(y)<<" "<<use_rec(y)<<endl;

  report<<endl<<"EXPLOITATION F_Method: ";
  if(F_Method==1) {report<<" Pope's_approx ";} else {report<<" instantaneous_annual_F ";}
  report<<endl<<"X Catch_Units ";
  for(f=1;f<=Nfleet;f++) if(catchunits(f)==1) {report<<" Bio ";} else {report<<" Num ";}
  report<<endl<<"yr seas"; for(f=1;f<=Nfleet;f++) report<<" "<<f;
  report<<endl<<"init_yr 1 "<<init_F<<endl;
  for(y=styr;y<=endyr;y++)
  for(s=1;s<=nseas;s++)
  {
    t=styr+(y-styr)*nseas+s-1;
    report<<y<<" "<<s<<" "<<column(Hrate,t)<<endl;
  }

  report<<endl<< "LEN_SELEX" << endl;
  report<<"Fleet gender "<<len_bins_m<<endl;
  for (f=1;f<=Ntypes;f++)
  {
    if(seltype(f,1)>0)
    {
      for (gg=1;gg<=gender;gg++) report<<f<<"-"<<fleetname(f)<<gg<<" "<<sel_l(endyr,f,gg)<<endl;
    }
  }

  report<<endl<< "AGE_SELEX" << endl;
  report<<"Fleet gender "<<age_vector<<endl;
  for (f=1;f<=Ntypes;f++)
  {
    if(seltype(f+Ntypes,1)>10)
    {
      for (gg=1;gg<=gender;gg++) report<<f<<"-"<<fleetname(f)<<" "<<gg<<" "<<sel_a(endyr,f,gg)<<endl;
    }
  }

//*********************************************************************
//  apply time-varying factors to the MG parameters to create mgp_adj vector
FUNCTION get_MGsetup
  mgp_adj=MGparm;
  switch(MG_adjust_method)
  {
    case 1:
    {
      for(f=1;f<=N_MGparm;f++)
      {
        if(MGparm_env(f)>0)  //  do environmental effect first
          {mgp_adj(f) *= mfexp(MGparm(MGparm_env(f))* env_data(yz,MGparm_1(f,8)));}

        if(MGparm_1(f,13)>0)   // blocks
        {
          z=Block_Defs_MG(f,yz);  // identifies parameter that holds the block effect
          if(z>0)
          {
            if(MGparm_1(f,14)==0)
              {mgp_adj(f) *= mfexp(MGparm(z));}
            else if(MGparm_1(f,14)==1)
              {mgp_adj(f) += MGparm(z);}
            else
              {mgp_adj(f) = MGparm(z);}
          }
        }

        k=fabs(MGparm_1(f,9));     //  Annual deviations;  use kth dev series (absolute value syntax allows mirroring)
        if(k>0)
        {
          if(yz>=MGparm_dev_minyr(k) && yz<=MGparm_dev_maxyr(k))
            {mgp_adj(f) *= mfexp(MGparm_dev(k,yz));}
        }
        if(save_for_report==1 || do_once==1)
        {
          if(mgp_adj(f)<MGparm_1(f,1) || mgp_adj(f)>MGparm_1(f,2))
          {
            N_warn++;
            warning<<" warning: MGparm out of bounds (parm#, yr, min, max, base, adj_value) "<<endl<<f<<" "<<yz<<" "<<
            MGparm_1(f,1)<<" "<<MGparm_1(f,2)<<" "<<MGparm(f)<<" "<<mgp_adj(f)<<endl;
          }
        }
      }  // end parameter loop (f)
      break;
    }

    case 2:
    {
      for(f=1;f<=N_MGparm;f++)
      {
        j=0;
        temp=log((MGparm_HI(f)-MGparm_LO(f)+0.0000002)/(mgp_adj(f)-MGparm_LO(f)+0.0000001)-1.)/(-2.);   // transform the parameter
        if(MGparm_1(f,13)>0)   // blocks
        {
          z=Block_Defs_MG(f,yz);  // identifies parameter that holds the block effect
          if(z>0)
          {
            j=1;
            if(MGparm_1(f,14)==1)
              {temp += MGparm(z);}   // block as offset
            else if (MGparm_1(f,14)==2)
              {temp=log((MGparm_HI(f)-MGparm_LO(f)+0.0000002)/(MGparm(z)-MGparm_LO(f)+0.0000001)-1.)/(-2.);}  // block as replacement
            else
              {cout<<" disabled multiplicative block effect with logistic approach"<<endl;}
          }
        }

        if(MGparm_env(f)>0)  //  do environmental effect
          {j=1; temp += MGparm(MGparm_env(f))* env_data(yz,MGparm_1(f,8));}


        k=fabs(MGparm_1(f,9));     //  Annual deviations;  use kth dev series (absolute value syntax allows mirroring)
        if(k>0)
        {
          if(yz>=MGparm_dev_minyr(k) && yz<=MGparm_dev_maxyr(k))
            {j=1; temp += MGparm_dev(k,yz);}            // but how to define variance of these devs in this logistic space??
        }
        if(j==1) mgp_adj(f)=MGparm_LO(f)+(MGparm_HI(f)-MGparm_LO(f))/(1.+mfexp(-2.*temp));   // backtransform
      }  // end parameter loop (f)
      break;
    }  // end case 2
  }   // end switch method

// if direct estimation (no offsets) is used; then look for M and growth parameters
// for which male value is set equal to female value
  if(MGparm_def==1)
  {
    for(j=1;j<=N_GP*gender*MGparm_per_def;j++)
    {
      if(MGparm_offset(j)>0) mgp_adj(j) = mgp_adj(MGparm_offset(j));
    }
  }
  if(save_for_report==1) mgp_save(yz)=value(mgp_adj);

//********************************************************************
FUNCTION get_growth1
    if(MGparm_doseas>0)
    {
      if(MGparm_seas_effects(10)>0)  // for seasonal K
      {
        VBK_seas(0)=0.0;
        for(s=1;s<=nseas;s++)
        {
          VBK_seas(s)=mfexp(MGparm(MGparm_seas_effects(10)+s));
          VBK_seas(0)+=VBK_seas(s)*seasdur(s);
        }
      }
      else
      {
        VBK_seas=sum(seasdur);  // set vector to null effect
      }

      for(j=1;j<=8;j++)
      {
        if(MGparm_seas_effects(j)>0)
        {
          wtlen_seas(0,j)=0.0;
          for(s=1;s<=nseas;s++)
          {
            wtlen_seas(s,j)=mfexp(MGparm(MGparm_seas_effects(j)+s));
            wtlen_seas(0,j)+=wtlen_seas(s,j)*seasdur(s);
          }
        }
        else
        {
          for(s=0;s<=nseas;s++) {wtlen_seas(s,j)=1.0;}
        }
      }
    }
    else
    {
      VBK_seas=sum(seasdur);  // set vector to null effect
      wtlen_seas=1.0;  // set vector to null effect
    }

//  CVLmin(g) and CVLmax(g) defined only as constant over time
      Ip=1-MGparm_per_def;
      for (gp=1;gp<=N_GP*gender;gp++)
        {
        Ip+=MGparm_per_def;
        j=Ip+MGparm_per_def-2;  // index for CVmin
        k=j+1;  // index for CVmax
        switch(MGparm_def)    // for CV of size-at-age
          {
            case 1:  // direct
            {
            if(MGparm(j)>0)
              {CVLmin(gp)=MGparm(j);} else {CVLmin(gp)=MGparm(MGparm_per_def-1);}
            if(MGparm(k)>0)
              {CVLmax(gp)=MGparm(k);} else {CVLmax(gp)=MGparm(MGparm_per_def);}
            break;
            }
            case 2:  // offset
            {
            if(gp==1)
              {CVLmin(gp)=MGparm(j); CVLmax(gp)=MGparm(k);}
            else
              {CVLmin(gp)=CVLmin(1)*mfexp(MGparm(j)); CVLmax(gp)=CVLmax(1)*mfexp(MGparm(k));}
            break;
            }
            case 3:  // offset like SS2 V1.23
            {
            if(gp==1)
              {CVLmin(gp)=MGparm(j); CVLmax(gp)=CVLmin(1)*mfexp(MGparm(k));}
            else
              {CVLmin(gp)=CVLmin(1)*mfexp(MGparm(j)); CVLmax(gp)=CVLmin(gp)*mfexp(MGparm(k));}
            break;
            }
          }  // end switch
          if((CVLmin(gp)!=CVLmax(gp)) || active(MGparm(MGparm_per_def)) || active(MGparm(k)))
          {CV_const(gp)=1;} else {CV_const(gp)=0;}
        }

//********************************************************************
//  ProgLabel_6000_FUNCTION   get growth2 (do biology calculations)
FUNCTION get_growth2
//  progress mean growth through time series, accounting for seasonality and possible change in parmaters
//   get size distribution at the mid-point of the season, except for the spawning season
    dvariable grow;
    dvariable growhalf;
    dvariable CV_delta;
    dvariable LminR;
    dvariable LmaxR;
    dvariable LinfR;
    int k_fg;
    int k2;

      if(CGD>0)   //  cohort specific growth multiplier
      {
        temp=mgp_adj(MGP_CGD);
        k=min(nages,(YrMax-y));
        for(a=0;a<=k;a++) {Cohort_Growth(y+a,a)=temp;}
      }

      Ip=N_natMparms+1;  // first growth parameter
      for (gp=1;gp<=N_GP*gender;gp++)
      {
        if(MGparm_def>1 && gp>1)   // switch for growth parms
        {
          Lmin(gp)=Lmin(1)*mfexp(mgp_adj(Ip));
          Lmax_temp(gp)=Lmax_temp(1)*mfexp(mgp_adj(Ip+1));
          VBK(gp)=VBK(1)*mfexp(mgp_adj(Ip+2));
          if(Grow_type==2) Richards(gp)=Richards(1)*mfexp(mgp_adj(Ip+3));
        }
        else
        {
          Lmin(gp)=mgp_adj(Ip);
          Lmax_temp(gp)=mgp_adj(Ip+1);
          VBK(gp)=-mgp_adj(Ip+2);  // because always used as negative
          if(Grow_type==2) Richards(gp)=mgp_adj(Ip+3);
        }

        if(Grow_type!=2)
        {
          if(AFIX2==999)
          {L_inf(gp)=Lmax_temp(gp);}
          else
          {
            L_inf(gp)=Lmin(gp)+(Lmax_temp(gp)-Lmin(gp))/(1.-mfexp(VBK(gp)*VBK_seas(0)*(AFIX_delta)));
          }
        }
        else
        {
          LminR=pow(Lmin(gp),Richards(gp));
          if(AFIX2==999)
          {L_inf(gp)=Lmax_temp(gp);}
          else
          {
            LmaxR=pow(Lmax_temp(gp), Richards(gp));
            L_inf(gp)=pow( (LminR+(LmaxR-LminR)/(1.-mfexp(VBK(gp)*VBK_seas(0)*(AFIX_delta)))),1./Richards(gp));
          }
          LinfR=pow(L_inf(gp),Richards(gp));
        }



        if(CV_const(gp)>0)
        {
          if(CV_depvar_a==0)
            {CV_delta=(CVLmax(gp)-CVLmin(gp))/(Lmax_temp(gp)-Lmin(gp));}
          else
            {CV_delta=(CVLmax(gp)-CVLmin(gp))/(AFIX_delta);}
        }
        else
        {
          CV_G(0)=CVLmin(gp);
          CV_G(1)=CVLmin(gp);
        }
        g=(gp-1)*nseas*N_GP_sub+int(N_GP_sub/2)+1-N_GP_sub;

        for(birthseas=1;birthseas<=nseas;birthseas++)  // loop birth seasons (really looping more morphs)
        {
          g+=N_GP_sub;
          if(use_morph(g)>0)
          {
            k_fg=first_grow_age(g,1);

              if(y==styr)   //  do growth for first season in initial year
              {
                switch(Grow_type)
                {
                  case 1:
                  {
                    Ave_Size(styr,0,g) = L_inf(gp) + (Lmin(gp)-L_inf(gp))*mfexp(VBK(gp)*VBK_seas(0)*(curr_age1(g,1)-AFIX));
                    if(docheckup==1) checkup<<" growth "<<g<<" "<<gp<<" Lmin: "<<Lmin(gp)<<" Linf: "<<L_inf(gp)<<" VBK: "<<VBK(gp)<<endl<<Ave_Size(styr,0,g)(0,6)<<endl;
                    break;
                  }
                  case 2:
                  {
                    for(a=0;a<=nages;a++)
                    {
                      temp = pow((LinfR + (LminR-LinfR)*mfexp(VBK(gp)*VBK_seas(0)*(curr_age1(g,1,a)-AFIX))),(1./Richards(gp)));
                      Ave_Size(styr,0,g,a) = posfun(temp,0.01,CrashPen);
                    }
//                    cout<<y<<" growth "<<g<<" "<<gp<<" Lmin: "<<LminR<<" Linf: "<<LinfR<<" VBK: "<<VBK(gp)<<" Rich: "<<Richards(gp)<<endl<<
//                    "first "<<Ave_Size(styr,0,g)(0,5)<<endl;
                    if(docheckup==1) checkup<<" growth "<<g<<" "<<gp<<" Lmin: "<<Lmin(gp)<<" Linf: "<<L_inf(gp)<<" VBK: "<<VBK(gp)<<endl<<Ave_Size(styr,0,g)(0,6)<<endl;
                    break;
                  }
                }
              }

// loop seasons
              for (s=1;s<=nseas;s++)
              {
                smid=s+nseas;
  // calc constants
                t=t_base+s;
                grow = (mfexp(VBK(gp)*seasdur(s)*VBK_seas(s))-1.0);
                growhalf = (mfexp(VBK(gp)*seasdur2(s)*VBK_seas(s))-1.0);
                if(s==nseas) k=1; else k=0;   //      advance age or not
                if(s==birthseas && t>styr)
                {
                  switch(Grow_type)
                  {
                  case 1:
                  {
                    Ave_Size(t,0,g,0) = L_inf(gp) + (Lmin(gp)-L_inf(gp))*mfexp(VBK(gp)*VBK_seas(0)*(curr_age1(g,s,0)-AFIX));
                    break;
                  }
                  case 2:
                  {
                    temp = pow((LinfR + (LminR-LinfR)*mfexp(VBK(gp)*VBK_seas(0)*(curr_age1(g,s,0)-AFIX))),(1./Richards(gp)));
                    Ave_Size(t,0,g,0) = posfun(temp,0.01,CrashPen);
                    break;
                  }
                  }
                }

// growth to mid-period and next period
                  switch(Grow_type)
                  {
                  case 1:
                  {
                    Ave_Size(t,1,g) = Ave_Size(t,0,g)+growhalf * elem_prod((Ave_Size(t,0,g)-L_inf(gp)),Cohort_Growth(y));
                    if(k==1) {Ave_Size(t,1,g).shift(k);  Cohort_Growth(y).shift(k);}
                    Ave_Size(t+1,0,g)(k,nages) = Ave_Size(t,1,g)(k,nages)+growhalf * elem_prod((Ave_Size(t,1,g)(k,nages)-L_inf(gp)),Cohort_Growth(y)(k,nages));
                    if(k==1) {Ave_Size(t,1,g).shift(0);  Cohort_Growth(y).shift(0);}
                    break;
                  }
                  case 2:
                  {

                    for(a=0;a<=nages;a++)
                    {
                      temp1=pow(Ave_Size(t,0,g,a),Richards(gp));
                      if(temp1<=0.0) cout<<" crash in mid "<<y<<" "<<a<<" "<<Ave_Size(t,0,g,a)<<endl;
                      temp=posfun(temp1,0.01,CrashPen);
                      Ave_Size(t,1,g,a) = pow((temp+growhalf*(temp-LinfR)*Cohort_Growth(y,a)),(1./Richards(gp)));
                      if(a<nages) {k2=a+k;} else {k2=a;}
                      temp1=pow(Ave_Size(t,1,g,a),Richards(gp));
                      if(temp1<=0.0) cout<<" crash in next "<<y<<" "<<a<<" "<<Ave_Size(t,1,g,a)<<endl;
                      temp=posfun(temp1,0.01,CrashPen);
                      Ave_Size(t+1,0,g,k2) = pow((temp+growhalf*(temp-LinfR)*Cohort_Growth(y,a)),(1./Richards(gp)));
                      if(y<=1900)
                      {
                      cout<<y<<" "<<a<<" "<<Ave_Size(t,0,g,a)<<" "<<Ave_Size(t,1,g,a)<<" ";
                      if(a<nages) cout<<temp<<" "<<Ave_Size(t+1,0,g,k2);
                      cout<<endl;
                    }
                    }
                    break;
                  }
                  }

                if(y>styr)  // then must be doing time-vary growth, so trap for decreasing size
                for (a=0;a<=nages;a++)
                if(Ave_Size(t,0,g,a)>L_inf(gp))
                {
                  Ave_Size(t,1,g,a) = Ave_Size(t,0,g,a);
                  if((a+k)<=nages) Ave_Size(t+1,0,g,a+k) = Ave_Size(t,0,g,a);
                }

                a=0;
                while(curr_age1(g,s,a)<AFIX)
                {Use_Ave_Size(s,g,a) = len_bins(1)+curr_age1(g,s,a)/AFIX*(Lmin(gp)-len_bins(1));  a++;}
                Use_Ave_Size(s,g)(a,nages) = Ave_Size(t,0,g)(a,nages);

                a=0;
                while(curr_age2(g,s,a)<AFIX)
                {Use_Ave_Size(smid,g,a) = len_bins(1)+curr_age2(g,s,a)/AFIX*(Lmin(gp)-len_bins(1));  a++;}
                Use_Ave_Size(smid,g)(a,nages) = Ave_Size(t,1,g)(a,nages);

                if(CV_const(gp)>0)
                {
                for (a=0;a<=nages;a++)
                {
                  if(curr_age1(g,s,a)<AFIX)
                  {CV_G(0,a)=CVLmin(gp);}
                  else if(curr_age1(g,s,a)>=AFIX2)
                  {CV_G(0,a)=CVLmax(gp);}
                  else if(CV_depvar_a==0)
                  {CV_G(0,a)=CVLmin(gp) + (Use_Ave_Size(s,g,a)-Lmin(gp))*CV_delta;}
                  else
                  {CV_G(0,a)=CVLmin(gp) + (curr_age1(g,s,a)-AFIX)*CV_delta;}

                  if(curr_age2(g,s,a)<AFIX)
                  {CV_G(1,a)=CVLmin(gp);}
                  else if(curr_age2(g,s,a)>=AFIX2)
                  {CV_G(1,a)=CVLmax(gp);}
                  else if(CV_depvar_a==0)
                  {CV_G(1,a)=CVLmin(gp) + (Use_Ave_Size(smid,g,a)-Lmin(gp))*CV_delta;}
                  else
                  {CV_G(1,a)=CVLmin(gp) + (curr_age2(g,s,a)-AFIX)*CV_delta;}
                }   // end age loop
              }
              Ave_Size(t+nseas,0,g,0)=Ave_Size(t,0,g,0);  // this used to be inside the age loop
                if(CV_depvar_b==0)
                {
                  Sd_Size_within(s,g)=SD_add_to_LAA+elem_prod(CV_G(0),Use_Ave_Size(s,g));
                  Sd_Size_within(smid,g)=SD_add_to_LAA+elem_prod(CV_G(1),Use_Ave_Size(smid,g));
                }
                else
                {
                  Sd_Size_within(s,g)=SD_add_to_LAA+CV_G(0);
                  Sd_Size_within(smid,g)=SD_add_to_LAA+CV_G(1);
                }
                if(N_GP_sub>1)
                {
                  Sd_Size_between(s,g)=Sd_Size_within(s,g)*sd_betweenmorph;
                  Sd_Size_between(smid,g)=Sd_Size_within(smid,g)*sd_betweenmorph;
                  Sd_Size_within(s,g)*=sd_withinmorph;
                  Sd_Size_within(smid,g)*=sd_withinmorph;
                }
                if(save_for_report==1)
                {
                  Save_Ave_Size(t,0,g)=value(Use_Ave_Size(s,g));
                  Save_Ave_Size(t,1,g)=value(Use_Ave_Size(smid,g));
                }
              }  // end season loop

    k=yz+1;
    j=yz+1;
    while(time_vary_MG(j,2)==0 && k<=YrMax)
    {
              for (s=1;s<=nseas;s++)
              {
                smid=s+nseas;
                t=styr+(k-styr)*nseas+s-1;
                Ave_Size(t,0,g)=Ave_Size(t-nseas,0,g);
                if(s==1 && k<YrMax) Ave_Size(t+nseas,0,g)=Ave_Size(t,0,g);  // prep for time-vary next yr
                Ave_Size(t,1,g)=Ave_Size(t-nseas,1,g);
                if(save_for_report==1)
                {
                  Save_Ave_Size(t,0,g)=value(Use_Ave_Size(s,g));
                  Save_Ave_Size(t,1,g)=value(Use_Ave_Size(smid,g));
                }
              }  // end season loop
      k++;
      if(j<endyr+1) j++;
    }
          }  // end need to consider this GP x birthseason combo (usemorph>0)
        }  // end loop of birthseasons
        Ip+=MGparm_per_def;
      }    // end loop of growth patterns, gp
// end do growth

//*******************************************************************
//  do natural mortality
FUNCTION get_natmort
  dvariable Loren_M1;
  dvariable Loren_temp;
  dvariable Loren_temp2;
  dvariable t_age;

  t_base=styr+(yz-styr)*nseas-1;
  Ip=-MGparm_per_def;   // start counter for MGparms
  for (gp=1;gp<=N_GP*gender;gp++)
  {
  	if(N_natMparms>0)
  	{
    Ip+=MGparm_per_def;
    for(j=1;j<=N_natMparms;j++) natMparms(j,gp)=mgp_adj(Ip+j);
    switch(MGparm_def)   //  switch for natmort parms
    {
      case 1:  // direct
      {
      	for(j=1;j<=N_natMparms;j++)
      	{
      		if(natMparms(j,gp)<0) natMparms(j,gp)=natMparms(j,1);
      	}
        break;
      }
      case 2:  // offset
      {
        if(gp>1)
        {
          for(j=1;j<=N_natMparms;j++)
          {
            natMparms(j,gp)=natMparms(j,1)*mfexp(natMparms(j,gp));
          }
        }
        break;
      }
      case 3:  // offset like SS2 V1.23
      {
          if(gp>1) natMparms(1,gp)=natMparms(1,1)*mfexp(natMparms(1,gp));
          if(N_natMparms>1)
          {
          for(j=2;j<=N_natMparms;j++)
          {
            natMparms(j,gp)=natMparms(j-1,gp)*mfexp(natMparms(j,gp));
          }
        }
        break;
      }
    }  // end switch
    }  // end have natmort parms

    g=(gp-1)*nseas*N_GP_sub+int(N_GP_sub/2)+1-N_GP_sub;
    for(birthseas=1;birthseas<=nseas;birthseas++)  // loop birth seasons (really looping more morphs)
    {
      g+=N_GP_sub;
      gg=GP3(g);   // gpattern*gender*birthseason
      if(use_morph(g)>0)
      {
        switch(natM_type)
        {
          case 0:  // constant M
          {
            for(s=1;s<=nseas;s++)
            {
              natM(s,gg)=natMparms(1,gp);
              surv1(s,gg)=mfexp(-natMparms(1,gp)*seasdur2(s));   // refers directly to the constant value
              surv2(s,gg)=square(surv1(s,gg));
            }
            break;
          }

          case 1:  // breakpoints
          {
            dvariable natM1;
            dvariable natM2;
            for(s=1;s<=nseas;s++)
            {
              if(s>=Bseas(g))
              {a=0; t_age=azero_seas(s)-azero_G(g);}
              else
              {a=1; t_age=1.0+azero_seas(s)-azero_G(g);}
              natM_amax=NatM_break(1);
              natM2=natMparms(1,gp);
              k=a;

              for(loop=1;loop<=N_natMparms+1;loop++)
              {
                natM_amin=natM_amax;
                natM1=natM2;
                if(loop<=N_natMparms)
                {
                  natM_amax=NatM_break(loop);
                  natM2=natMparms(loop,gp);
                }
                else
                {
                  natM_amax=r_ages(nages)+1.;
                }
                if(natM_amax>natM_amin)
                {temp=(natM2-natM1)/(natM_amax-natM_amin);}  //  calc the slope
                else
                {temp=0.0;}
                while(t_age<natM_amax && a<=nages)
                {
                  natM(s,gg,a)=natM1+(t_age-natM_amin)*temp;
                  t_age+=1.0; a++;
                }
              }
              if(k==1) natM(s,gg,0)=natM(s,gg,1);
              surv1(s,gg)=mfexp(-natM(s,gg)*seasdur2(s));
              surv2(s,gg)=square(surv1(s,gg));
            } // end season
            break;
          }  // end natM_type==1

          case 2:  //  Lorenzen M
          {
            Loren_temp2=L_inf(gp)*(mfexp(-VBK(gp)*VBK_seas(0))-1.);   // need to verify ue of VBK_seas here
            t=styr+(yz-styr)*nseas+Bseas(g)-1;
            Loren_temp=Use_Ave_Size(1+nseas,g,int(natM_amin));  // uses mean size in middle of season 1 for the reference age
            Loren_M1=natMparms(1,gp)/log(Loren_temp/(Loren_temp+Loren_temp2));
            for(s=nseas;s>=1;s--)
            {
              smid=s+nseas;    //  mid-season size-at-age is stored in season s+nseas
              for (a=nages; a>=0;a--)
              {
                if(a==0 && s<Bseas(g))
                {natM(s,gg,a)=natM(s+1,gg,a);}
                else
                {natM(s,gg,a)=log(Use_Ave_Size(smid,g,a)/(Use_Ave_Size(smid,g,a)+Loren_temp2))*Loren_M1;}
                surv1(s,gg,a)=mfexp(-natM(s,gg,a)*seasdur2(s));
                surv2(s,gg,a)=square(surv1(s,gg,a));
              }   // end age loop
            }
            break;
          }
          case(3):   // read age_natmort as constant
          {
            for(s=1;s<=nseas;s++)
            {
              natM(s,gg)=Age_NatMort(gp);
              surv1(s,gg)=value(mfexp(-natM(s,gg)*seasdur2(s)));
              surv2(s,gg)=value(square(surv1(s,gg)));
            }
            break;
          }

          case(4):   // read age_natmort as constant and interpolate to seasonal real age
          {
            for(s=1;s<=nseas;s++)
            {
              if(s>=Bseas(g))
              {
                k=0; t_age=azero_seas(s)-azero_G(g);
                for (a=k;a<=nages-1;a++)
                {
                  natM(s,gg,a) = Age_NatMort(gp,a)+t_age*(Age_NatMort(gp,a+1)-Age_NatMort(gp,a));
                } // end age
              }
              else
              {
                k=1; t_age=azero_seas(s)+(1.-azero_G(g));
                for (a=k;a<=nages-1;a++)
                {
                  natM(s,gg,a) = Age_NatMort(gp,a)+t_age*(Age_NatMort(gp,a+1)-Age_NatMort(gp,a));
                } // end age
                natM(s,gg,0)=natM(s,gg,1);
              }
              natM(s,gg,nages)=Age_NatMort(gp,nages);
              surv1(s,gg)=mfexp(-natM(s,gg)*seasdur2(s));
              surv2(s,gg)=square(surv1(s,gg));
            } // end season
            break;
          }
        }  // end natM_type switch
      } //  end use of this morph
    } // end birthseason
  }   // end growth pattern x gender loop
// end nat mort

//*******************************************************************
//  do morph and area distribution
FUNCTION get_recr_distribution
  dvar_vector recr_dist_parm(1,N_GP+nseas+pop+recr_dist_inx*N_GP*pop*nseas);
  recr_dist.initialize();
  Ip=MGparm_per_def*N_GP*gender+2*gender+5-1;
  for(f=1;f<=N_GP+nseas+pop+recr_dist_inx*N_GP*pop*nseas;f++)
  {recr_dist_parm(f)=mfexp(mgp_adj(Ip+f));}

  for(gp=1;gp<=N_GP;gp++)
  for(s=1;s<=nseas;s++)         //  really looping birthseas
  for(p=1;p<=pop;p++)
  if(recr_dist_pattern(gp,s,p)>0)
  {
    recr_dist(gp,s,p)=femfrac(gp)*recr_dist_parm(gp)*recr_dist_parm(N_GP+p)*recr_dist_parm(N_GP+pop+s);
//    cout<<" recr_dist "<<gp<<" "<<s<<" "<<p<<" "<<recr_dist_parm(N_GP+p)<<" "<<recr_dist(gp,s,p)<<endl;
    if(gender==2) recr_dist(gp+N_GP,s,p)=femfrac(gp+N_GP)*recr_dist_parm(gp)*recr_dist_parm(N_GP+p)*recr_dist_parm(N_GP+pop+s);  //males
  }

  if(recr_dist_inx==1)
  {
    f=N_GP+nseas+pop;
    for(gp=1;gp<=N_GP;gp++)
    for(s=1;s<=nseas;s++)
    for(p=1;p<=pop;p++)
    {
      f++;
      if(recr_dist_pattern(gp,s,p)>0)
      {
        recr_dist(gp,s,p)*=recr_dist_parm(f);
        if(gender==2) recr_dist(gp+N_GP,s,p)*=recr_dist_parm(f);
      }
    }
  }

  recr_dist/=sum(recr_dist);

// **************************************************
//  wt-len and maturity fecundity
FUNCTION get_wtlen
  Ip=MGparm_per_def*N_GP*gender+1;
  for(f=0;f<=3+2*gender;f++) {wtlen_p(f+1)=mgp_adj(Ip+f);}

  for(s=1;s<=nseas;s++)
  {
    t=styr+(y-styr)*nseas+s-1;
    if(MGparm_seas_effects(1)>0 || MGparm_seas_effects(2)>0 )        //  get seasonal effect on fem wtlen parameters
    {wt_len(s,1)=(wtlen_p(1)*wtlen_seas(s,1))*pow(len_bins_m(1,nlength),(wtlen_p(2)*wtlen_seas(s,2)));}               //  ProgLabel_053
    else
    {wt_len(s,1) = wtlen_p(1)*pow(len_bins_m(1,nlength),wtlen_p(2));}               //  ProgLabel_053

    wt_len2(s)(1,nlength)=wt_len(s,1)(1,nlength);
    if(s==spawn_seas)
    {
      if(Maturity_Option==4)
      {  }//will use gp specific Age_Maturity and interpret as fecundity at age;}
      else
      {
        if(Maturity_Option==2)
        {mat_age = 1./(1. + mfexp(wtlen_p(4)*(r_ages-wtlen_p(3))));}
        else
        {mat_age=1.;}
        if(First_Mature_Age>0)
        {mat_age(0,First_Mature_Age-1)=0.;}


        if(Maturity_Option==1)
        {mat_len = 1./(1. + mfexp(wtlen_p(4)*(len_bins_m(1,nlength)-wtlen_p(3))));}
        else
        {mat_len=1.;}

        switch (Fecund_Option)
        {
          case 1:    // as eggs/gram (SS original configuration)
          {
            fec_len = wtlen_p(5)+wtlen_p(6)*wt_len(s,1);
            fec_len = elem_prod(wt_len(s,1),fec_len);
            break;
          }
          case 2:
          {       // as eggs = f(length)
            fec_len = wtlen_p(5)*pow(len_bins_m,wtlen_p(6));
            break;
          }
          case 3:
          {       // as eggs = f(body weight)
            fec_len = wtlen_p(5)*pow(wt_len(s,1),wtlen_p(6));
            break;
          }
        }
        mat_len_wt = elem_prod(mat_len,fec_len);
      }
    }

    if(gender==2)
    {
      if(MGparm_seas_effects(7)>0 || MGparm_seas_effects(8)>0 )        //  get seasonal effect on male wt-len parameters
      {wt_len(s,2) = (wtlen_p(7)*wtlen_seas(s,7))*pow(len_bins_m(1,nlength),(wtlen_p(8)*wtlen_seas(s,8)));}               //  ProgLabel_053
      else
      {wt_len(s,2) = wtlen_p(7)*pow(len_bins_m(1,nlength),wtlen_p(8));}               //  ProgLabel_053
      wt_len2(s)(nlength1,nlength2)=wt_len(s,2).shift(nlength1);
      wt_len(s,2).shift(1);
    }
    wt_len_fd(s)=first_difference(wt_len2(s));
  }
//  end wt-len and fecundity

//===============================   ProgLabel_080   ======================================
//  do migration/movement
// do_migration contains N explicit rates; do_migr2 contains explicit and implicit (stay) rates
FUNCTION get_migration
  Ip=MGP_CGD;   // start counter for  movement parms
  for(k=1;k<=do_migr2;k++)   //  loop all movement rates for this year (includes seas, morphs)
  {
    t=styr+(yz-styr)*nseas+move_def2(k,1)-1;
    if(k<=do_migration)    // movement based on parameters
    {
      temp=1./(move_def2(k,6)-move_def2(k,5));
      temp1=temp*(mgp_adj(Ip+2)-mgp_adj(Ip+1));
      for (a=0;a<=nages;a++)
      {
        if(a<=move_def2(k,5)) {migrrate(yz,k,a) = mgp_adj(Ip+1);}
        else if(a>=move_def2(k,6)) {migrrate(yz,k,a) = mgp_adj(Ip+2);}
        else {migrrate(yz,k,a) = mgp_adj(Ip+1) + (r_ages(a)-move_def2(k,5))*temp1;}
      }   // end age loop
      migrrate(yz,k)=mfexp(migrrate(yz,k));
      Ip+=2;
    }
    else               // default movement strength
    {
      migrrate(yz,k)=1.;
    }
  }

  for (s=1;s<=nseas;s++)
  {
    t=styr+(yz-styr)*nseas+s-1;
    for(gp=1;gp<=N_GP;gp++)
    {
      for (p=1;p<=pop;p++)
      {
        tempvec.initialize();   // zero out the summation vector
        for (p2=1;p2<=pop;p2++)
        {
          k=move_pattern(s,gp,p,p2);
          if(k>0)
          {
            if(p2!=p && nseas>1) migrrate(yz,k)*=seasdur(move_def2(k,1));  // fraction leaving an area is reduced if the season is short
            tempvec+=migrrate(yz,k);          //  sum of all movement weights for the p2 fish
          }
        }   //end destination area
//  now normalize for all movement from source area p
        for (p2=1;p2<=pop;p2++)
        {
          k=move_pattern(s,gp,p,p2);
          if(k>0)
          {
            migrrate(yz,k)=elem_div(migrrate(yz,k),tempvec);
            if(migr_start(s,gp)>0)
            {
              if(p!=p2)
              {
                migrrate(yz,k)(0,migr_start(s,gp)-1)=0.0;
              }
              else
              {
                migrrate(yz,k)(0,migr_start(s,gp)-1)=1.0;
              }
            }
          }
        }
      }    //  end source areas loop
    }  // end growth pattern
  }  // end season

  if(yz<endyr)
  {
    k=yz+1;
    while(time_vary_MG(k,5)==0 && k<=endyr)
    {
      migrrate(k)=migrrate(k-1);  k++;
    }
  }
//  end migration

//*************************************
FUNCTION get_saveGparm
      for (gp=1;gp<=N_GP*gender;gp++)
      {
        g=(gp-1)*nseas*N_GP_sub+int(N_GP_sub/2)+1-N_GP_sub;
        for(birthseas=1;birthseas<=nseas;birthseas++)  // loop birth seasons (really looping more morphs)
        {
          g+=N_GP_sub;
          save_gparm++;
          save_G_parm(save_gparm,1)=save_gparm;
          save_G_parm(save_gparm,2)=y;
          save_G_parm(save_gparm,3)=g;
          save_G_parm(save_gparm,4)=AFIX;
          save_G_parm(save_gparm,5)=AFIX2;
          save_G_parm(save_gparm,6)=value(Lmin(gp));
          save_G_parm(save_gparm,7)=value(L_inf(gp));
          save_G_parm(save_gparm,8)=value(-VBK(gp)*VBK_seas(0));
          save_G_parm(save_gparm,9)=value( -log(L_inf(gp)/(L_inf(gp)-Lmin(gp))) / (-VBK(gp)*VBK_seas(0)) +AFIX+azero_G(g) );
          save_G_parm(save_gparm,10)=value(L_inf(gp));
          save_G_parm(save_gparm,11)=value(CVLmin(gp));
          save_G_parm(save_gparm,12)=value(CVLmax(gp));
          save_G_parm(save_gparm,13)=natM_amin;
          save_G_parm(save_gparm,14)=natM_amax;
//          save_G_parm(save_gparm,15)=value(natM1(gp));
//          save_G_parm(save_gparm,16)=value(natM2(gp));
          if(sx(g)==1)
          {
          for(k=1;k<=6;k++) save_G_parm(save_gparm,16+k)=value(wtlen_p(k));
          }
          else
          {
          for(k=1;k<=2;k++) save_G_parm(save_gparm,16+k)=value(wtlen_p(k+6));
          }
          save_gparm_print=save_gparm;
        }
      }
    if(MGparm_doseas>0)
      {
        for(s=1;s<=nseas;s++)
        {
          for(k=1;k<=8;k++)
          {
          save_seas_parm(s,k)=value(wtlen_p(k)*wtlen_seas(s,k));
          }
          save_seas_parm(s,9)=value(Lmin(1));
          save_seas_parm(s,10)=value(VBK(1)*VBK_seas(s));
        }
      }

//********************************************************************
//  ProgLabel_6500_FUNCTION get_selectivity
FUNCTION get_selectivity
  int Ip_env;
  dvariable t1;
  dvariable t2;
  dvariable t3;
  dvariable t4;
  dvariable t1min; dvariable t1max; dvariable t1power;
  dvariable t2min; dvariable t2max; dvariable t2power; dvariable final; dvariable sel_maxL;
  dvariable lastsel; dvariable lastSelPoint; dvariable SelPoint;
  dvariable asc;
  dvariable dsc;
  dvar_vector sp(1,199);                 // temporary vector for selex parms
  Ip=0;

// **   Do Size selex
  for (f=1;f<=Ntypes;f++)
  {
    if(time_vary_sel(y,f)==1)
    {    // recalculate the selex in this year x type
      if(N_selparmvec(f)>0)      // type has parms, so look for adjustments
      {
//        sp.initialize();
        for(j=1;j<=N_selparmvec(f);j++) sp(j)=selparm(Ip+j);
        switch(selparm_adjust_method)
        {
          case 0:
          {
            save_sp_len(y,f,0)=N_selparmvec(f);
            for(j=1;j<=N_selparmvec(f);j++) save_sp_len(y,f,j)=selparm(Ip+j);
            break;
          }
          case(1):
          {
            for(j=1;j<=N_selparmvec(f);j++)
            {
              if(selparm_env(Ip+j)>0)       // if env then modify sp
              {sp(j) *= mfexp(selparm(selparm_env(Ip+j))* env_data(y,selparm_1(Ip+j,8)));}

              if(selparm_1(Ip+j,13)>0)
              {
                blkparm=Block_Defs(Ip+j,y);

                if(blkparm>0)
                {
                  if(selparm_1(Ip+j,14)==0)
                  {sp(j) *= mfexp(selparm(blkparm));}
                  else if(selparm_1(Ip+j,14)==1)
                  {sp(j) += selparm(blkparm);}
                  else
                  {sp(j) = selparm(blkparm);}
                }
              }

              k=selparm_1(Ip+j,9);     // if dev then modify sp
              if(k>0)
              {
                if(y>=selparm_dev_minyr(k) && y<=selparm_dev_maxyr(k))
                {sp(j) *= mfexp(selparm_dev(k,y));}
              }
              if(save_for_report==1 || do_once==1)
              {
                if(j==1) save_sp_len(y,f,0)=N_selparmvec(f);
                save_sp_len(y,f,j)=sp(j);
                if(sp(j)<selparm_1(Ip+j,1) || sp(j)>selparm_1(Ip+j,2))
                {
                  N_warn++;
                  warning<<" warning: len selparm out of bounds (Parm#, yr, min, max, base, value) "<<endl<<
                  Ip+j<<" "<<y<<" "<<selparm_1(Ip+j,1)<<" "<<selparm_1(Ip+j,2)<<" "<<selparm(Ip+j)<<" "<<sp(j)<<endl;
                }
              }
            }  // end j parm loop
            break;
          }
          case(2):
            {
            for(j=1;j<=N_selparmvec(f);j++)
              {
              temp=log((selparm_1(Ip+j,2)-selparm_1(Ip+j,1)+0.0000002)/(sp(j)-selparm_1(Ip+j,1)+0.0000001)-1.)/(-2.);   // transform the parameter
              doit=0;
              if(selparm_1(Ip+j,13)>0)   // blocks
              {
                blkparm=Block_Defs(Ip+j,y);  // identifies parameter that holds the block effect
                if(blkparm>0)
                {
                  doit=1;
                  if(selparm_1(Ip+j,14)==1)
                    {temp += selparm(blkparm);}   // block as offset
                  else if (selparm_1(Ip+j,14)==2)
                    {temp=log((selparm_1(Ip+j,2)-selparm_1(Ip+j,1)+0.0000002)/(selparm(blkparm)-selparm_1(Ip+j,1)+0.0000001)-1.)/(-2.);}  // block as replacement
                  else
                    {N_warn++; warning<<" disabled multiplicative block effect with logistic approach"<<endl;}
                }
              }

              if(selparm_env(Ip+j)>0)  //  do environmental effect
                {doit=1;temp += selparm(selparm_env(Ip+j))* env_data(y,selparm_1(Ip+j,8));}

              k=selparm_1(Ip+j,9); //  Annual deviations;  use kth dev series
              if(k>0)
                {
                if(y>=selparm_dev_minyr(k) && y<=selparm_dev_maxyr(k))
                  {doit=1;temp += selparm_dev(k,y);}            // but how to define variance of these devs in this logistic space??
                }
              if(doit==1) sp(j)=selparm_1(Ip+j,1)+(selparm_1(Ip+j,2)-selparm_1(Ip+j,1))/(1+mfexp(-2.*temp));   // backtransform
              if(save_for_report==1 || do_once==1)
                {
                if(j==1) save_sp_len(y,f,0)=N_selparmvec(f);
                save_sp_len(y,f,j)=sp(j);
               }
              }  // end parameter loop j
            break;
            }
        }
        if(docheckup==1) checkup<<" selex len parms "<<f<<" "<<endl<<sp(1,N_selparmvec(f))<<endl;
      }  // end adjustment of parms

      for(gg=1;gg<=gender;gg++)
      {
        if(gg==1 || (gg==2 && seltype(f,3)==3))
        {
          switch(seltype(f,1))  // select the selectivity pattern
          {
            case 0:   // ***********   constant
             {sel = 1.;break;}

            case 1:                      // ***********   logistic    ProgLabel_055
              {
                if(gg==1 || seltype(f,3)<3)
                {sel = 1./(1.+mfexp(neglog19*(len_bins_m-sp(1))/sp(2)));}
                else
                {
                  temp=sp(1)+sp(MaleSelParm(f));
                  temp1=sp(2)+sp(MaleSelParm(f)+1);
                  sel = 1./(1.+mfexp(neglog19*(len_bins_m-temp)/temp1));}
                break;
              }

            case 2:                  // *******double logistic     ProgLabel_056
              {
                                     // 1=peak, 2=init,  3=infl,  4=slope, 5=final, 6=infl2, 7=slope2
            N_warn++; cout<<" exit - see warning "<<endl; warning<<" selex pattern 2 discontinued; use pattern 8 for double logistic "<<endl; exit(1);
 /*
           t1=minL+(1./(1.+mfexp(-sp(3))))*(sp(1)-minL);    // INFL
           t1min=1./(1.+mfexp(-sp(4)*(minL-t1)))*0.9999;  // asc value at minsize
           t1max=1./(1.+mfexp(-sp(4)*(sp(1)-t1)))*1.00001;  // asc value at peak
           t1power=log(0.5)/log((0.5-t1min)/(t1max-t1min));

           t2=(sp(1)+sp(8))+(1./(1.+mfexp(-sp(6))))*(maxL-(sp(1)+sp(8)));    // INFL
           t2min=1./(1.+mfexp(-sp(7)*(sp(1)+sp(8)-t2)))*0.9999;  // asc value at peak+
           t2max=1./(1.+mfexp(-sp(7)*(maxL-t2)))*1.00001;  // asc value at maxL
           t2power=log(0.5)/log((0.5-t2min)/(t2max-t2min));
           final=1./(1.+mfexp(-sp(5)));

           for (j=1; j<=nlength; j++)  //calculate the value over length bins
           {
            if (len_bins_m(j) <= sp(1)) // ascending limb
            {sel(j) = sp(2) + (1. - sp(2)) * pow(
              (( 1./(1.+mfexp(-sp(4)*(len_bins_m(j)-t1))) -t1min ) / (t1max-t1min) )
              ,t1power); }
            else if (len_bins_m(j) >= (sp(1)+sp(8))) // descending limb
            {sel(j) = 1. + (final - 1.) * pow(
              (( 1./(1.+mfexp(-sp(7)*(len_bins_m(j)-t2))) -t2min ) / (t2max-t2min) )
              ,t2power); }
            else // at the peak
            {sel(j) = 1.0;}
           }   // end size bin loop
 */
           break;
          }    // end double logistic

          case 3:                  // ********   ProgLabel_057
          {
            N_warn++; cout<<" exit - see warning "<<endl; warning<<" selex pattern 3 discontinued "<<endl; exit(1);
 /*
           t1=minL+(1/(1+mfexp(-sp(1))))*(maxL-minL);  // size to get to 1.0
           t2=t1+(1/(1+mfexp(-sp(2))))*(maxL-t1);      // size to begin decline from 1.0
           t3=(1/(1+mfexp(-sp(3))));  // selex at min size
           t4=(1/(1+mfexp(-sp(4))));  // selex at min size
           for(j=1;j<=nlength;j++)
           {
            if(len_bins_m(j)<t1)
            {sel(j)=t3 + pow( (len_bins_m(j)-minL)/(t1-minL),(1.+sp(5)) ) * (1.0 - t3);}
            else if(len_bins_m(j)<=t2)
            {sel(j)=1.0;}
            else
            {sel(j)=1.0 + pow( (len_bins_m(j)-t2)/(maxL-t2),(1.+sp(6)) ) * (t4-1.0);}
           }
 */
           break;
          }  // end seltype=3

    //*********
          case 4:               //  use maturity curve as selex  ProgLabel_058
            {N_warn++; cout<<" exit - see warning "<<endl; warning<<" selex pattern 4 discontinued; use pattern 30 to get spawning biomass "<<endl; exit(1); break;}                   // do this as a numbers survey because wt is included here

    //**********
          case 5:      //  borrow another selex  ProgLabel_059
                                            //  use only the specified bin range
                                           // must refer to a lower numbered type (f)
          {
           i=int(value(sp(1)));  if(i<=0) i=1;
           j=int(value(sp(2)));  if(j<=0) j=nlength;
           sel.initialize();
           sel(i,j)=sel_l(y,seltype(f,4),1)(i,j);
           break;
          }

    //**********
          case 6:       //  non-parametric selex pattern
          {
          lastsel=-10.0; lastSelPoint=1.; SelPoint=value(sp(1)); z=3;
          temp1 = (sp(2)-sp(1))/(seltype(f,4)-1.0);  // step interval
          for(j=1;j<=nlength;j++)
          {
           if(j<SelPoint)
            {temp=lastsel + (double(j)-lastSelPoint)/(SelPoint-lastSelPoint) * (sp(z)-lastsel);}
           else if(j==SelPoint)
            {temp=sp(z);
           lastsel=sp(z); lastSelPoint=SelPoint; SelPoint+=temp1;
           if(SelPoint<=sp(2)) {z++;} else {SelPoint=sp(2);}
           }
           else if(j<=sp(2))
            {lastsel=sp(z); lastSelPoint=SelPoint; SelPoint+=temp1;
           if(SelPoint<=sp(2)) {z++;} else {SelPoint=sp(2);}
           temp=lastsel + (double(j)-lastSelPoint)/(SelPoint-lastSelPoint) * (sp(z)-lastsel);
           }
           else
           {;}

           sel(j) = 1./(1.+mfexp(-temp));
          }
          break;
          }

          case 7:                  // *******New double logistic
    // 1=peak, 2=init,  3=infl,  4=slope, 5=final, 6=infl2, 7=slope2 8=binwidth;    Mirror=1===const_above_Linf
          {
            N_warn++; cout<<" exit - see warning "<<endl; warning<<" selex pattern 7 discontinued; use pattern 8 for double logistic "<<endl; exit(1);
 /*
           t1=minL+(1./(1.+mfexp(-sp(3))))*(sp(1)-minL);    // INFL
           t1min=1./(1.+mfexp(-sp(4)*(minL-t1)))*0.9999;  // asc value at minsize
           t1max=1./(1.+mfexp(-sp(4)*(sp(1)-t1)))*1.00001;  // asc value at peak
           t1power=log(0.5)/log((0.5-t1min)/(t1max-t1min));  // so the parameter will actual correspond to 50% point

           if(seltype(f,4)==0) {sel_maxL=maxL;} else {sel_maxL=Ave_Size(styr,1,1,nages);}
           t2=(sp(1)+sp(8))+(1./(1.+mfexp(-sp(6))))*(sel_maxL-(sp(1)+sp(8)));    // INFL
           t2min=1./(1.+mfexp(-sp(7)*(sp(1)+sp(8)-t2)))*0.9999;  // asc value at peak+
           t2max=1./(1.+mfexp(-sp(7)*(sel_maxL-t2)))*1.00001;  // asc value at maxL
           t2power=log(0.5)/log((0.5-t2min)/(t2max-t2min));
           final=1./(1.+mfexp(-sp(5)));

           for (j=1; j<=nlength; j++)  //calculate the value over length bins
           {sel(j) =
             (
             (
             (sp(2) + (1. - sp(2)) * pow((( 1./(1.+mfexp(-sp(4)*(len_bins_m(j)-t1))) -t1min ) / (t1max-t1min) ),t1power))
              /(1.+mfexp(10.*(len_bins_m(j)-sp(1))))   // scale ascending side
              +
              1./(1.+mfexp(-10.*(len_bins_m(j)-sp(1))))   // flattop, with scaling
              )
              /(1.+mfexp( 10.*(len_bins_m(j)-(sp(1)+sp(8)))))    // scale combo of ascending and flattop
              +
              (1. + (final - 1.) * pow(sqrt(square((( 1./(1.+mfexp(-sp(7)*(len_bins_m(j)-t2))) -t2min ) / (t2max-t2min) ))),t2power))
              /(1.+mfexp( -10.*(len_bins_m(j)-(sp(1)+sp(8)))))    // scale descending
              ) / (1.+mfexp(10.*(len_bins_m(j)-sel_maxL)));       // scale combo of ascend, flattop, descending
             sel(j)+=final/(1.+mfexp(-10.*(len_bins_m(j)-sel_maxL)));  // add scaled portion above Linf
           }   // end size bin loop
  */
           break;
          }    // end New double logistic

    //**********
          case 8:                  // *******New double logistic in simpler code
    // 1=peak, 2=init,  3=infl,  4=slope, 5=final, 6=infl2, 7=slope2 8=binwidth;    Mirror=1===const_above_Linf
          {
           t1=minL+(1./(1.+mfexp(-sp(3))))*(sp(1)-minL);    // INFL
           t1min=1./(1.+mfexp(-mfexp(sp(4))*(minL-t1)))*0.9999;  // asc value at minsize
           t1max=1./(1.+mfexp(-mfexp(sp(4))*(sp(1)-t1)))*1.0001;  // asc value at peak
           t1power=log(0.5)/log((0.5-t1min)/(t1max-t1min));  // so the parameter will actual correspond to 50% point

           if(seltype(f,4)==0) {sel_maxL=maxL;} else {sel_maxL=Ave_Size(styr,1,1,nages);}
           t2=(sp(1)+sp(8))+(1./(1.+mfexp(-sp(6))))*(sel_maxL-(sp(1)+sp(8)));    // INFL
           t2min=1./(1.+mfexp(-mfexp(sp(7))*(sp(1)+sp(8)-t2)))*0.9999;  // asc value at peak+
           t2max=1./(1.+mfexp(-mfexp(sp(7))*(sel_maxL-t2)))*1.0001;  // asc value at maxL
           t2power=log(0.5)/log((0.5-t2min)/(t2max-t2min));
           final=1./(1.+mfexp(-sp(5)));
           for (j=1; j<=nlength; j++)  //calculate the value over length bins
           {join1=1./(1.+mfexp(10.*(len_bins_m(j)-sp(1))));
            join2=1./(1.+mfexp(10.*(len_bins_m(j)-(sp(1)+sp(8)))));
            join3=1./(1.+mfexp(10.*(len_bins_m(j)-sel_maxL)));
            upselex=sp(2) + (1. - sp(2)) * pow((( 1./(1.+mfexp(-mfexp(sp(4))*(len_bins_m(j)-t1)))-t1min ) / (t1max-t1min)),t1power);
            downselex=(1. + (final - 1.) * pow(fabs(((( 1./(1.+mfexp(-mfexp(sp(7))*(len_bins_m(j)-t2))) -t2min ) / (t2max-t2min) ))),t2power));
            sel(j) = ((((upselex*join1)+1.0*(1.0-join1))*join2) + downselex*(1-join2))*join3 + final*(1-join3);
           }   // end size bin loop
           break;
          }    // end New double logistic

    //***********************
          case 9:                      // ***********   old double logistic
          {k1=int(value(sp(5)));
           if(k1>1) sel(1,k1-1) = 0.0;
           sel(k1,nlength) =   elem_prod(  (1/(1+mfexp(-sp(2)*(len_bins_m(k1,nlength)-sp(1)) ))),
                                                (1-1/(1+mfexp(-sp(4)*(len_bins_m(k1,nlength)-(sp(1)*sp(6)+sp(3))) ))) );
           sel += 1.0e-6;
           sel /= max(sel);
           break;
            }

    //***********************************
          case 21:                 // *******New non-parametric
          {
            N_warn++; cout<<" exit - see warning "<<endl; warning<<" selex pattern 21 discontinued; "<<endl; exit(1);
 /*
           dvar_vector tempsel1(1,nlength);
           dvar_vector tempsel2(1,nlength);
           dvar_vector tempsel3(1,nlength);
           dvar_vector tempsel4(1,nlength);
           dvar_vector tempsel5(1,nlength);
           dvar_vector tempsel6(1,nlength);

           upselex=1./(1.+mfexp(-sp(1)));
           downselex=1./(1.+mfexp(-sp(2)));
           peak=minL+(maxL-minL)*(0.001+0.998/(1.+mfexp(-sp(3))));
           peak2=peak+sp(8);
           point1=minL+(peak-minL)*(0.001+0.998/(1.+mfexp(-sp(4))));
           point2=point1+(peak-point1)*(0.001+0.998/(1.+mfexp(-sp(5))));
           point3=peak2+(maxL-peak2)*(0.001+0.998/(1.+mfexp(-sp(6))));
           point4=point3+(maxL-point3)*(0.001+0.998/(1.+mfexp(-sp(7))));
           t1min=6;
           t1max=1.5;
           tempsel1=-t1min+(t1min-t1max)/(point1-minL)*(len_bins_m-minL);
           tempsel2=-t1max+(2*t1max)/(point2-point1)*(len_bins_m-point1);
           tempsel3=t1max+(t1min-t1max)/(peak-point2)*(len_bins_m-point2);
           tempsel4=t1min+(t1max-t1min)/(point3-peak2)*(len_bins_m-(peak2));
           tempsel5=t1max+(-2*t1max)/(point4-point3)*(len_bins_m-point3);
           tempsel6=-t1max+(t1max-t1min)/(maxL-point4)*(len_bins_m-point4);

           for(j=1;j<=nlength;j++)
             {t1=len_bins_m(j);
              if      (t1<=(point1+point2)/2)   {join1=1./(1.+mfexp(30.*(t1-point1))); t2=join1*tempsel1(j)+(1-join1)*tempsel2(j);}
              else if (t1<=(point2+peak)/2)     {join1=1./(1.+mfexp(30.*(t1-point2))); t2=join1*tempsel2(j)+(1-join1)*tempsel3(j);}
              else if (t1<=(peak+peak2)/2)      {join1=1./(1.+mfexp(30.*(t1-peak)));   t2=join1*tempsel3(j)+(1-join1)*t1min;}
              else if (t1<=(peak2+point3)/2)    {join1=1./(1.+mfexp(30.*(t1-peak2)));  t2=join1*t1min+      (1-join1)*tempsel4(j);}
              else if (t1<=(point3+point4)/2)   {join1=1./(1.+mfexp(30.*(t1-point3))); t2=join1*tempsel4(j)+(1-join1)*tempsel5(j);}
              else                              {join1=1./(1.+mfexp(30.*(t1-point4))); t2=join1*tempsel5(j)+(1-join1)*tempsel6(j);}

              join1=1./(1.+mfexp(30.*(t1-peak2)));
              sel(j)=join1*(upselex+(1.-upselex)/(1+mfexp(-t2))) + (1-join1)*(1.+(downselex-1)*(1-1/(1+mfexp(-t2))));
             }   // end size bin loop
  */
           break;
          }

    // ***************************************
          case 22:                 // *******double_normal_plateau (similar to CASAL)
            {peak2=sp(1)+ (0.99*len_bins(nlength)-sp(1))/(1.+mfexp(-sp(2))); upselex=mfexp(sp(3)); downselex=mfexp(sp(4));
             for(j=1;j<=nlength;j++)
             {
              t1=len_bins_m(j);
              if(t1<sp(1))
                {sel(j)=mfexp(-square(t1-sp(1))/upselex);}
              else if (t1<=peak2)
                {sel(j)=1.0;}
              else
                {sel(j)=mfexp(-square(t1-peak2)/downselex);}
             }
             break;
            }

    // ***************************************
          case 23:                 // *******double_normal_plateau (similar to CASAL)
            {
            N_warn++; cout<<" exit - see warning "<<endl; warning<<" selex pattern 23 discontinued; use pattern 24 "<<endl; exit(1);
 /*
            peak2=sp(1)+ (0.99*len_bins(nlength)-sp(1))/(1.+mfexp(-sp(2))); upselex=mfexp(sp(3)); downselex=mfexp(sp(4));
             point1=1./(1.+mfexp(-sp(5))); point2=1./(1.+mfexp(-sp(6)));
             t1min=mfexp(-(square(len_bins_m(1)-sp(1))/upselex));  // fxn at first bin
             t2min=mfexp(-(square(len_bins_m(nlength)-peak2)/downselex));  // fxn at last bin
             for(j=1;j<=nlength;j++)
             {
              t1=len_bins_m(j);
              if(t1<sp(1))
                {sel(j)=point1+(1.0-point1)*mfexp(-square(t1-sp(1))/upselex) - t1min*(sp(1)-t1)/(sp(1)-len_bins_m(1));}
              else if (t1<=peak2)
                {sel(j)=1.0;}
              else
                {sel(j)=point2+(1.0-point2)*mfexp(-square(t1-peak2)/downselex) - t2min*(peak2-t1)/(peak2-len_bins_m(nlength));}
             }
 */
             break;
            }

    // ***************************************
          case 24:                 // *******double_normal_plateau
          {
            if(gg==1 || seltype(f,3)<3)
            {peak=sp(1); upselex=mfexp(sp(3)); downselex=mfexp(sp(4)); final=sp(6);}
            else
            {   // offset male parameters if seltype(f,3)==3
              peak=sp(1)+sp(MaleSelParm(f)); upselex=mfexp(sp(3)+sp(MaleSelParm(f)+1)); downselex=mfexp(sp(4)+sp(MaleSelParm(f)+2));
              if(sp(6)>-999) final=sp(6)+sp(MaleSelParm(f)+3);
            }

            if(sp(5)<-1000.)
            {
              j1=-1001-int(value(sp(5)));      // selex is nil thru bin j1, so set sp(5) equal to first bin with selex (e.g. -1002 to start selex at bin 2)
              sel(1,j1)=1.0e-06;
            }
            else
            {
              j1=startbin-1;                // start selex at bin equal to min sizecomp databin  (=j1+1)
              if(sp(5)>-999)
              {
                point1=1.0/(1.0+mfexp(-sp(5)));
              t1min=mfexp(-(square(len_bins_m(startbin)-peak)/upselex));  // fxn at first bin
              }
            }
            if(sp(6)<-1000.)
            {
              j2=-1000-int(value(sp(6))); // selex is constant beyond this sizebin, so set sp(6) equal to last bin with estimated selex
            }
            else
            {j2=nlength;}
            peak2=peak+binwidth2+ (0.99*len_bins_m(j2)-peak-binwidth2)/(1.+mfexp(-sp(2)));
            if(sp(6)>-999)
            {
              point2=1.0/(1.0+mfexp(-final));
              t2min=mfexp(-(square(len_bins_m(j2)-peak2)/downselex));  // fxn at last bin
            }
            for(j=j1+1;j<=j2;j++)
            {
              t1=len_bins_m(j)-peak;  t2=len_bins_m(j)-peak2;
              join1=1.0/(1.0+mfexp(-(20.*t1/(1.0+fabs(t1)))));  //  note the logit transform on t1 causes range of mfexp to be over -20 to 20
              join2=1.0/(1.0+mfexp(-(20.*t2/(1.0+fabs(t2)))));
              if(sp(5)>-999)
                {asc=point1+(1.0-point1)*(mfexp(-square(t1)/upselex)-t1min)/(1.0-t1min);}
              else
                {asc=mfexp(-square(t1)/upselex);}
              if(sp(6)>-999)
                {dsc=1.0+(point2-1.0)*(mfexp(-square(t2)/downselex)-1.0    )/(t2min-1.0);}
              else
                {dsc=mfexp(-square(t2)/downselex);}
              sel(j)=asc*(1.0-join1)+join1*(1.0-join2+dsc*join2);
            }
            if(startbin>1 && sp(5)>=-1000.)
            {
              for(j=1;j<=startbin-1;j++)
              {
                sel(j)=square(len_bins_m(j)/len_bins_m(startbin))*sel(startbin);
              }
            }

            if(j2<nlength) {sel(j2+1,nlength)=sel(j2);}
            break;
          }

          case 30:
          {
            sel=1.0;
            break;
          }
          case 31:
          {
            sel=1.0;
            break;
          }
          case 32:
          {
            sel=1.0;
            break;
          }
          case 33:
          {
            sel=1.0;
            break;
          }

          }
          sel_l(y,f,gg)=sel;    // Store size-selex in year*type array
        }  // end direct calc of selex from parameters

// Do male relative to female selex
        if(gg==2)         // males exist
        {
         if(seltype(f,1)==4)
           {sel_l(y,f,2)=0.;}  // set males to zero for spawning biomass
         else if(seltype(f,1)==5)    // set males equal to mirrored males
         {
          i=int(value(sp(1)));  if(i<=0) i=1;
          j=int(value(sp(2)));  if(j<=0) j=nlength;
          sel_l(y,f,2)(i,j)=sel_l(y,seltype(f,4),2)(i,j);
         }
         else if(seltype(f,3)==1 || seltype(f,3)==2)   // do gender selex
         {
//           k=seltype_Nparam(seltype(f,1)) + 1;
//           if(seltype(f,2)>0) k+=seltype(f,2)*4;   // first gender offset parm (skip over the retention parameters
//           if(seltype(f,1)==6) k += seltype(f,4);    // for non-parametric in which N parm is stored in special column
           k=MaleSelParm(f);
           temp=sp(k);
           temp1=1.;
           switch(seltype(f,3))
           {
             case 1:
             {                            // do males relative to females
               for(j=1;j<=nlength;j++)
               {
                 if(len_bins_m(j)<=temp)
                   {sel(j)*=mfexp(sp(k+1)+(len_bins_m(j)-minL_m)/(temp-minL_m) * (sp(k+2)-sp(k+1)) );}
                 else
                   {sel(j)*=mfexp(sp(k+2)+(len_bins_m(j)-temp) /(maxL-temp)  * (sp(k+3)-sp(k+2)) );}
                 if(sel(j)>temp1) temp1=sel(j);
               }
               sel_l(y,f,2)=sel;
               sel_l(y,f) /=temp1;
               break;
             }
             case 2:
             {                   //  do females relative to males
               sel_l(y,f,2)=sel;
               for(j=1;j<=nlength;j++)
               {
                 if(len_bins_m(j)<=temp)
                   {sel(j)*=mfexp(sp(k+1)+(len_bins_m(j)-minL_m)/(temp-minL_m) * (sp(k+2)-sp(k+1)) );}
                 else
                   {sel(j)*=mfexp(sp(k+2)+(len_bins_m(j)-temp) /(maxL-temp)  * (sp(k+3)-sp(k+2)) );}
                 if(sel(j)>temp1) temp1=sel(j);
               }
               sel_l(y,f,1)=sel;
               sel_l(y,f)/=temp1;
               break;
             }
           }  // end switch
         }  // end do gender selex as offset from other gender
         else
         {
           sel_l(y,f,2)=sel;   // set males = females, but also will set male selex to calculated selex if seltype(f,3)==3
         }
        }  // end doing males
      }  // end loop of genders
      if(docheckup==1) checkup<<"sel-len "<<sel_l(y,f)<<endl;

//************************************************************************************************************************************
//    Do size-Retention -------------------------------------------------------------------
      if(seltype(f,2)!=0)               // ProgLabel_070
      {
        if(seltype(f,2)>0)
        {
          k=seltype_Nparam(seltype(f,1))+1;  // first retention parm
          if(seltype(f,1)==6) k += seltype(f,4);
          temp=1.-sp(k+2);
          temp1=1.-posfun(temp,0.0,CrashPen);
          retain(y,f)=temp1/(1.+mfexp(-(len_bins_m2-(sp(k)+male_offset*sp(k+3)))/sp(k+1)));  // males are at end of vector, so automatically get done
          if(docheckup==1&&y==styr) checkup<<" retention "<<retain(y,f)<<endl;
        }
        else  // mirror
        {
          retain(y,f)=retain(y,-seltype(f,2));
          discmort(y,f)=discmort(y,-seltype(f,2));
//          discmort2(y,f)=discmort2(y,-seltype(f,2));

          discmort2(y,f,1)=elem_prod(sel_l(y,f,1), retain(y,f)(1,nlength) + elem_prod((1.-retain(y,f)(1,nlength)),discmort(y,f)(1,nlength)) );
          if(gender==2)
          {
            discmort_M.shift(nlength1)=discmort(y,f)(nlength1,nlength2);
            discmort2(y,f,2)=elem_prod(sel_l(y,f,2), retain_M.shift(1) + elem_prod((1.-retain_M),discmort_M.shift(1)) );
          }

        }
        sel_l_r(y,f,1)=elem_prod(sel_l(y,f,1),retain(y,f)(1,nlength));
        if(gender==2)
        {
         retain_M.shift(nlength1)=retain(y,f)(nlength1,nlength2);
         sel_l_r(y,f,2)=elem_prod(sel_l(y,f,2),retain_M.shift(1));
        }

        if(seltype(f,2)==2)     // do discard mortality
        {
      // where discmort is the size-specific fraction of discarded fish that die
      // and discmort2 is size-specpfic fraction that die from being retained or are dead discard = sel * (retain + (1-retain)*discmort)
          k +=4;  // first discard mortality parm
          temp=1.-sp(k+2);
          temp1=posfun(temp,0.0,CrashPen);
          discmort(y,f)=(1.-temp1/(1+mfexp(-(len_bins_m2-(sp(k)+male_offset*sp(k+3)))/sp(k+1))));  // males are at end of vector, so automatically get done
          if(docheckup==1&&y==styr) checkup<<" discmort "<<discmort(y,f)<<endl;
          discmort2(y,f,1)=elem_prod(sel_l(y,f,1), retain(y,f)(1,nlength) + elem_prod((1.-retain(y,f)(1,nlength)),discmort(y,f)(1,nlength)) );
          if(gender==2)
          {
            discmort_M.shift(nlength1)=discmort(y,f)(nlength1,nlength2);
            discmort2(y,f,2)=elem_prod(sel_l(y,f,2), retain_M.shift(1) + elem_prod((1.-retain_M),discmort_M.shift(1)) );
          }
        }
      }
      else  // no retention or discmort
      {
        retain(y,f)=1.0; sel_l_r(y,f)=sel_l(y,f); discmort(y,f)=1.0; discmort2(y,f)=sel_l_r(y,f);
      }
      if(docheckup==1&&y==styr) checkup<<"sel-len-r "<<sel_l_r(y,f)<<endl;
      if(docheckup==1&&y==styr) checkup<<" dead "<<discmort2(y,f)<<endl;
    }
    else
    { // carryover from previous year
      sel_l(y,f)=sel_l(y-1,f);   // this does both genders
      sel_l_r(y,f)=sel_l_r(y-1,f);
      retain(y,f)=retain(y-1,f);
      discmort(y,f)=discmort(y-1,f);
      discmort2(y,f)=discmort2(y-1,f);
    }

    Ip+=seltype_Nparam(seltype(f,1));
    if(seltype(f,2)>0) Ip+=seltype(f,2)*4;  // increment parm count
    if(seltype(f,3)>0) Ip+=4;
    if(seltype(f,1)==6) Ip+=seltype(f,4);
  }  //  end fleet loop
// ----------------------------------------------------------------------------------
//   do age-selex
  for (f=1;f<=Ntypes;f++)
  {
    z=f+Ntypes;   // index for age-selex parms
    if(time_vary_sel(y,z)==1)
    {  // recalculate the selex in this year x type
      if(seltype_Nparam(seltype(z,1))>0)
      {
        for(j=1;j<=N_selparmvec(z);j++) {sp(j) = selparm(Ip+j);}
        if(do_once==1) save_sp_age(y,f,0)=N_selparmvec(z);

        switch(selparm_adjust_method)
        {
          case(0):
          {
            if(save_for_report==1 || do_once==1)
            {
              for(j=1;j<=N_selparmvec(z);j++)   // N selex parms
              {save_sp_age(y,f,j) = selparm(Ip+j);}
            }
            break;
          }
          case(1):
          {
            for(j=1;j<=N_selparmvec(z);j++)   // N selex parms
            {
              if(selparm_env(Ip+j)>0)       // if env then modify sp
              {sp(j) *= mfexp(selparm(selparm_env(Ip+j))* env_data(y,selparm_1(Ip+j,8)));}

              k=selparm_1(Ip+j,13);
              if(k>0)
              {
                blkparm=Block_Defs(Ip+j,y);
                if(blkparm>0)
                {
                  if(selparm_1(Ip+j,14)==0)
                  {sp(j) *= mfexp(selparm(blkparm));}
                  else if(selparm_1(Ip+j,14)==1)
                  {sp(j) += selparm(blkparm);}
                  else
                  {sp(j) = selparm(blkparm);}
                }
              }
              k=selparm_1(Ip+j,9);     // if dev then modify sp
              if(k>0)
              {
                if(y>=selparm_dev_minyr(k) && y<=selparm_dev_maxyr(k))
                {sp(j) *= mfexp(selparm_dev(k,y));}
              }
              if(save_for_report==1 || do_once==1)
              {
                save_sp_age(y,f,j)=sp(j);
                if(sp(j)<selparm_1(Ip+j,1) || sp(j)>selparm_1(Ip+j,2))
                {
                   N_warn++;
                   warning<<" warning: age selparm out of bounds (#, yr, min, max, base, value) "<<endl<<
                  Ip+j<<" "<<y<<" "<<selparm_1(Ip+j,1)<<" "<<selparm_1(Ip+j,2)<<" "<<selparm(Ip+j)<<" "<<sp(j)<<endl;
                }
              }
            }
          break;
          }   // end case 1

        case(2):
          {
          for(j=1;j<=N_selparmvec(z);j++)
            {
            doit=0;
            temp=log((selparm_1(Ip+j,2)-selparm_1(Ip+j,1)+0.0000002)/(sp(j)-selparm_1(Ip+j,1)+0.0000001)-1.)/(-2.);   // transform the parameter
            if(selparm_1(Ip+j,13)>0)   // blocks
              {
              blkparm=Block_Defs(Ip+j,y);  // identifies parameter that holds the block effect
              if(blkparm>0)
                {doit=1;
                if(selparm_1(Ip+j,14)==1)
                  {temp += selparm(blkparm);}   // block as offset
                else if (selparm_1(Ip+j,14)==2)
                  {temp=log((selparm_1(Ip+j,2)-selparm_1(Ip+j,1)+0.0000002)/(selparm(blkparm)-selparm_1(Ip+j,1)+0.0000001)-1.)/(-2.);}  // block as replacement
                else
                  {N_warn++; warning<<" disabled multiplicative block effect with logistic approach"<<endl;}
                }
              }

            if(selparm_env(Ip+j)>0)  //  do environmental effect
              {doit=1; temp += selparm(selparm_env(Ip+j))* env_data(y,selparm_1(Ip+j,8));}

            k=selparm_1(Ip+j,9); //  Annual deviations;  use kth dev series
            if(k>0)
              {
              if(y>=selparm_dev_minyr(k) && y<=selparm_dev_maxyr(k))
                {doit=1; temp += selparm_dev(k,y);}            // but how to define variance of these devs in this logistic space??
              }
            if(doit==1) sp(j)=selparm_1(Ip+j,1)+(selparm_1(Ip+j,2)-selparm_1(Ip+j,1))/(1+mfexp(-2.*temp));   // backtransform
            if(save_for_report==1 || do_once==1)
              {
              save_sp_age(y,f,j)=sp(j);
              }
            }  // end parameter loop

          }   //  end case 2
        }    // end adjustment method
         if(docheckup==1) checkup<<" age selex parms "<<f<<endl<<sp(1,N_selparmvec(z))<<endl;
     }  // end adjustment of parms


      switch(seltype(z,1))
        {

        case 10:   // constant age-specific selex
        {sel_a(y,f,1)(1,nages)=1.00; break;}                 //  change with version 1.21 to omit age 0

        case 11:   // selex=1.0 within a range of ages
        {
          a=int(value(sp(2)));
          if(a>nages) {a=nages;}
          sel_a(y,f,1)(int(value(sp(1))),a)=1.;
          break;
        }

        case 12:                      // ***********   logistic    ProgLabel_055
        { sel_a(y,f,1) = 1/(1+mfexp(neglog19*(r_ages-sp(1))/sp(2))); break;}

        case 13:                 // *******double logistic     ProgLabel_056
                                 // 1=peak, 2=init,  3=infl,  4=slope, 5=final, 6=infl2, 7=slope2
        {
          t1=0.+(1./(1.+mfexp(-sp(3))))*(sp(1)-0.);    // INFL
          t1min=1./(1.+mfexp(-sp(4)*(0.-t1)))*0.9999999;  // asc value at minage
          t1max=1./(1.+mfexp(-sp(4)*(sp(1)-t1)))*1.00001;  // asc value at peak
          t1power=log(0.5)/log((0.5-t1min)/(t1max-t1min));

          t2=(sp(1)+sp(8))+(1./(1.+mfexp(-sp(6))))*(r_ages(nages)-(sp(1)+sp(8)));    // INFL
          t2min=1./(1.+mfexp(-sp(7)*(sp(1)+sp(8)-t2)))*0.9999;  // asc value at peak+
          t2max=1./(1.+mfexp(-sp(7)*(r_ages(nages)-t2)))*1.00001;  // asc value at maxage
          t2power=log(0.5)/log((0.5-t2min)/(t2max-t2min));
          final=1./(1.+mfexp(-sp(5)));
          k1=int(value(sp(1))); k2=int(value(sp(1)+sp(8)));

          for (a=0; a<=nages; a++)  //calculate the value over ages
          {
            if (a < k1) // ascending limb
            {
              sel_a(y,f,1,a) = sp(2) + (1. - sp(2)) *
              pow((( 1./(1.+mfexp(-sp(4)*(r_ages(a)-t1))) -t1min ) / (t1max-t1min) ),t1power);
            }
            else if (a > k2) // descending limb
            {
              sel_a(y,f,1,a) = 1. + (final - 1.) *
              pow((( 1./(1.+mfexp(-sp(7)*(r_ages(a)-t2))) -t2min ) / (t2max-t2min) ),t2power);
            }
            else // at the peak
            { sel_a(y,f,1,a) = 1.0;}
          }   // end age loop
          break;
        }    // end double logistic

        case 14:                  // separate parm for each age
      {
       temp=9.-max(sp(1,nages+1));  //  this forces at least one age to have selex weight equal to 9
       for (a=0;a<=nages;a++)
       {
        if(sp(a+1)>-999)
        {sel_a(y,f,1,a) = 1./(1.+mfexp(-(sp(a+1)+temp)));}
        else
        {sel_a(y,f,1,a) = sel_a(y,f,1,a-1);}
        }
        break;
      }

        case 15:                //  mirror another selex
                                // must refer to a lower numbered type (f)
      {
        sel_a(y,f)=sel_a(y,seltype(z,4));
        break;
      }

        case 16:                  // Coleraine - Gaussian
      {
       t1 = 1/(1+mfexp(-sp(1)))*nages;
       for (a=0;a<=nages;a++)
       {
        if(a<t1)
        {sel_a(y,f,1,a) = mfexp(-square(r_ages(a)-t1)/mfexp(sp(2)));}
        else
        {sel_a(y,f,1,a)=1.0;}
       }
       break;
      }

 /*
        case 17:                  // logistic plus
      {
       k1=int(value(sp(1)));  k2=int(value(sp(2)));  k3=int(value(sp(3)));
       t1 = 1/(1+mfexp(neglog19*(r_ages(k2)-sp(4))/sp(5)));  // age beyond which is constant selex
       t2 = 1/(1+mfexp(neglog19*(r_ages(k3)-sp(4))/sp(5)));  // value at age for scaling
       for (a=0;a<=nages;a++)
       {
        if(a<k1)
        {sel_a(y,f,1,a) = 0.0;}
        else if(a<k2)
        {sel_a(y,f,1,a) = 1/(1+mfexp(neglog19*(r_ages(a)-sp(4))/sp(5)));}
        else
        {sel_a(y,f,1,a)=t1;}
       }
       sel_a(y,f,1) /=t2;
       break;
      }
 */

 /*
        case 17:                  // separate parm for each age as random walk towards 1 or zero
      {
       tempvec(0)=sp(1);
       for(a=1;a<=nages;a++)
       {
         if(sp(a+1)>=0.0)
         { tempvec(a)=tempvec(a-1)+sp(a+1)*(1.0-tempvec(a-1));}
         else
         { tempvec(a)=tempvec(a-1)-sp(a+1)*(1.0e-08-tempvec(a-1));}
       }
        temp=max(tempvec);
        sel_a(y,f,1)=tempvec/temp;
        break;
      }
 */
        case 17:                  // separate parm for each age as random walk towards 1 or zero
      {
        tempvec(0)=sp(1);
        for(a=1;a<=nages;a++) {tempvec(a)=tempvec(a-1)+sp(a+1);}
        temp=max(tempvec);
        sel_a(y,f,1)=mfexp(tempvec-temp);
        break;
      }

        case 18:                 // *******double logistic with smooth transition
                                 // 1=peak, 2=init,  3=infl,  4=slope, 5=final, 6=infl2, 7=slope2
      {
       t1=0.+(1./(1.+mfexp(-sp(3))))*(sp(1)-0.);    // INFL
       t1min=1./(1.+mfexp(-sp(4)*(0.-t1)))*0.9999;  // asc value at minsize
       t1max=1./(1.+mfexp(-sp(4)*(sp(1)-t1)))*1.00001;  // asc value at peak
       t1power=log(0.5)/log((0.5-t1min)/(t1max-t1min));

       t2=(sp(1)+sp(8))+(1./(1.+mfexp(-sp(6))))*(r_ages(nages)-(sp(1)+sp(8)));    // INFL
       t2min=1./(1.+mfexp(-sp(7)*(sp(1)+sp(8)-t2)))*0.9999;  // asc value at peak+
       t2max=1./(1.+mfexp(-sp(7)*(r_ages(nages)-t2)))*1.00001;  // asc value at maxage
       t2power=log(0.5)/log((0.5-t2min)/(t2max-t2min));
       final=1./(1.+mfexp(-sp(5)));
       for (a=0; a<=nages; a++)  //calculate the value over ages
       {
        sel_a(y,f,1,a) =
          (
          (
          (sp(2) + (1.-sp(2)) *
           pow((( 1./(1.+mfexp(-sp(4)*(r_ages(a)-t1)))-t1min)/ (t1max-t1min)),t1power))
          /(1.0+mfexp(30.*(r_ages(a)-sp(1))))  // scale ascending side
          +
          1./(1.+mfexp(-30.*(r_ages(a)-sp(1))))   // flattop, with scaling
          )
          /(1.+mfexp( 30.*(r_ages(a)-(sp(1)+sp(8)))))    // scale combo of ascending and flattop
          +
          (1. + (final - 1.) *
//           pow(sqrt(square((( 1./(1.+mfexp(-sp(7)*(r_ages(a)-t2))) -t2min ) / (t2max-t2min) ))),t2power))
           pow(fabs((( 1./(1.+mfexp(-sp(7)*(r_ages(a)-t2))) -t2min ) / (t2max-t2min) )),t2power))
          /(1.+mfexp( -30.*(r_ages(a)-(sp(1)+sp(8)))))    // scale descending
          );
       }   // end age loop
       break;
      }    // end double logistic with smooth transition

      case 19:                     // ***********   old double logistic   TAG_069
      {
        k1=int(value(sp(5)));
        sel_a(y,f,1)(k1,nages) =   elem_prod((1./(1.+mfexp(-sp(2)*(r_ages(k1,nages)-sp(1)) ))),
                                             (1.-1./(1.+mfexp(-sp(4)*(r_ages(k1,nages)-(sp(1)*sp(6)+sp(3))) ))) );
        sel_a(y,f,1)(k1,nages) /= max(sel_a(y,f,1)(k1,nages));
        if(k1>0) sel_a(y,f,1)(0,k1-1)=1.0e-6;
        break;
      }


// ***************************************
      case 20:                 // *******double_normal_plateau
      {
        upselex=mfexp(sp(3)); downselex=mfexp(sp(4));
        if(sp(5)<-1000.)
        {
          j=-1001-int(value(sp(5)));      // selex is nil thru age j, so set sp(5) equal to first age with selex (e.g. -1002 to start selex at age 2)
          sel_a(y,f,1)(0,j)=1.0e-06;
        }
        else
        {
          j=-1;                // start selex at age 0
          if(sp(5)>-999)
          {
            point1=1./(1.+mfexp(-sp(5)));
            t1min=mfexp(-(square(0.-sp(1))/upselex));  // fxn at first bin
          }
        }
        if(sp(6)<-1000.)
        {
          j2=-1000-int(value(sp(6))); // selex is constant beyond this age, so set sp(6) equal to last age with estimated selex
                                        //  (e.g. -1008 to be constant beyond age 8)
        }
        else
        {j2=nages;}
        peak2=sp(1)+1.+(0.99*r_ages(j2)-sp(1)-1.)/(1.+mfexp(-sp(2)));        // note, this uses age=j2 as constraint on range of "peak2"
        if(sp(6)>-999)
        {
          point2=1./(1.+mfexp(-sp(6)));
          t2min=mfexp(-(square(r_ages(nages)-peak2)/downselex));  // fxn at last bin
        }

        for(a=j+1;a<=j2;a++)
        {
          t1=r_ages(a)-sp(1);  t2=r_ages(a)-peak2;
          join1=1./(1.+mfexp(-(20./(1.+fabs(t1)))*t1));
          join2=1./(1.+mfexp(-(20./(1.+fabs(t2)))*t2));
          if(sp(5)>-999)
            {asc=point1+(1.-point1)*(mfexp(-square(t1)/upselex  )-t1min)/(1.-t1min);}
          else
            {asc=mfexp(-square(t1)/upselex);}
          if(sp(6)>-999)
            {dsc=1.+(point2-1.)*(mfexp(-square(t2)/downselex)-1.    )/(t2min-1.);}
          else
            {dsc=mfexp(-square(t2)/downselex);}
          sel_a(y,f,1,a)=asc*(1.-join1)+join1*(1.-join2+dsc*join2);
        }
        if(j2<nages) {sel_a(y,f,1)(j2+1,nages)=sel_a(y,f,1,j2);}
        break;
      }

    }  // end last age selex pattern

      if(seltype(z,3)>0)
      {
        k=seltype_Nparam(seltype(z,1))+1;   // first male parm
        temp=sp(k)-0.00001;
        temp1=1.;
        switch(seltype(z,3))
        {
          case 1:
          {                       // do males relative to females
            for(a=0;a<=nages;a++)   //
            {
              if(r_ages(a)<=temp)
              {sel_a(y,f,2,a)=sel_a(y,f,1,a)*mfexp(sp(k+1)+(r_ages(a)-0.)   /(temp-0.)   * (sp(k+2)-sp(k+1)) );}
              else
              {sel_a(y,f,2,a)=sel_a(y,f,1,a)*mfexp(sp(k+2)+(r_ages(a)-temp) /(double(nages)-temp) * (sp(k+3)-sp(k+2)) );}
              if(sel_a(y,f,2,a)>temp1) temp1=sel_a(y,f,2,a);
            }
            sel_a(y,f)/=temp1;
            break;
          }
          case 2:
          {                   //  do females relative to males
            sel_a(y,f,2)=sel_a(y,f,1);
            for(a=0;a<=nages;a++)   //
            {
              if(r_ages(a)<=temp)
                {sel_a(y,f,1,a)=sel_a(y,f,2,a)*mfexp(sp(k+1)+(r_ages(a)-0.)   /(temp-0.)   * (sp(k+2)-sp(k+1)) );}
              else
                {sel_a(y,f,1,a)=sel_a(y,f,2,a)*mfexp(sp(k+2)+(r_ages(a)-temp) /(double(nages)-temp) * (sp(k+3)-sp(k+2)) );}
              if(sel_a(y,f,1,a)>temp1) temp1=sel_a(y,f,1,a);
            }
            sel_a(y,f)/=temp1;
            break;
          }
        }
      }
      else if(gender==2&&seltype(z,1)!=15)
      {sel_a(y,f,2)=sel_a(y,f,1);}   // set males = females

    }  // end recalc of the selex
    else
    {  // carryover from previous year
      sel_a(y,f)=sel_a(y-1,f);  // does both genders
    }
//    }  // end gender loop
     if(docheckup==1) checkup<<" sel-age "<<sel_a(y,f)<<endl;

     Ip+=seltype_Nparam(seltype(z,1));
     if(seltype(z,3)>0) Ip+=4;  // increment parm count for male parameters
  }  //  end fleet loop

//***********************************************************************************
//  ProgLabel_7000_FUNCTION get_initial_conditions
FUNCTION get_initial_conditions
  catch_fleet.initialize();

//  if(do_once==0) natage.initialize();
    if(F_Method==2)
      {g=0;
      for(f=1;f<=Nfleet;f++)
        for(t=styr;t<=TimeMax;t++)
          {g++;
           Hrate(f,t)=F_rate(g);
          }
      }

// Initial size-at-age distribution             ProgLabel_091
  y=styr;
  yz=styr;
//  t_base=styr+(y-styr)*nseas-1;
  t_base=styr-1;
  if(MG_active(0)>0 || save_for_report==1) get_MGsetup();
  if(do_once==1) cout<<" MG setup OK "<<endl;
  if(MG_active(2)>0) get_growth1();   // seasonal effects and CV
  if(do_once==1) cout<<" growth OK"<<endl;
  if(MG_active(2)>0 || save_for_report==1)
  {
    get_growth2();   // do growth before natmort in case lorensen M is used
  }
  if(do_once==1) cout<<" growth-2 OK"<<endl;
  if(MG_active(1)>0) get_natmort();
  if(do_once==1) cout<<" natmort OK"<<endl;
  if(MG_active(3)>0) get_wtlen();
  if(MG_active(4)>0) get_recr_distribution();
  if(MG_active(5)>0) get_migration();
  if(do_once==1) cout<<" migr OK"<<endl;
  if(save_for_report==1) get_saveGparm();
  if(do_once==1) cout<<" growth OK, ready to call selex "<<endl;
  get_selectivity();
  if(do_once==1) cout<<" selex OK, ready to call ALK and fishselex "<<endl;
   for(s=1;s<=nseas;s++)
     {
     t = styr+s-1;
     if(MG_active(2)>0 || MG_active(3)>0 || save_for_report==1)  Make_AgeLength_Key();
     for(g=1;g<=gmorph;g++)
       if(use_morph(g)>0)
       {
       Make_FishSelex();
       }
     }
  virg_fec = fec;
  //*/
  if(do_once==1) cout<<" ready for virgin age struc "<<endl;
//Virgin age structure                    ProgLabel_092
  eq_yr=styr-2;
  R0=mfexp(SR_parm(1));
  exp_rec(eq_yr)=(R0);                 //  expected Recr from s-r parms
  pred_rec(eq_yr)=(mfexp(SR_parm(1)-SR_parm(3)*SR_parm(3)*0.5));   // predicted level adjusted downwards for bias correction
//  pred_rec(eq_yr)=R0;
  use_rec(eq_yr)=R0;

   bio_yr=styr;
   Fishon=0;
   equ_Recr=R0;

   Do_Equil_Calc();                      //  call function to do equilibrium calculation
   S0=Spbio_equil_sum;
   Spbio(eq_yr)=Spbio_equil;   // dimensions of pop x N_GP
   Spbio_tot(eq_yr)=Spbio_equil_sum;
   t=styr-2*nseas-1;
   for(p=1;p<=pop;p++)
   for(g=1;g<=gmorph;g++)
   for(s=1;s<=nseas;s++)
     {natage(t+s,p,g)(0,nages)=value(equ_numbers(s,p,g)(0,nages));}


   //****************************************************************************
   //Initial Age Structure; in equilibrium with init_equ_catch    ProgLabel_093
  if(do_once==1) cout<<" ready for initial age struc "<<endl;
   eq_yr=styr-1;
   R1_exp=R0;
   if(SR_env_target==2) {R1_exp*=mfexp(SR_parm(4)* env_data(eq_yr,SR_env_link));}
   R1 = R1_exp*mfexp(SR_parm(5));
   exp_rec(eq_yr)=(R1);
   pred_rec(eq_yr)=(pred_rec(eq_yr-1));
   use_rec(eq_yr)=R1;

   bio_yr=styr;
   if(fishery_on_off==1) {Fishon=1;} else {Fishon=0;}
   equ_Recr=R1;
   t=styr-nseas;
   for(f=1;f<=Nfleet;f++) {Hrate(f,t) = init_F(f);}
   Do_Equil_Calc();
   CrashPen += Equ_penalty;
   Spbio(eq_yr)=Spbio_equil;   // dimensions of pop x N_GP
   Spbio_tot(eq_yr)=Spbio_equil_sum;
   Spbio_tot(styr)=Spbio_equil_sum;

   for(f=1;f<=Nfleet;f++)
   {
     if(catchunits(f)==1)
     {
      est_equ_catch(f)=equ_catch_fleet(f,2);
    }
    else
     {
      est_equ_catch(f)=equ_catch_fleet(f,5);
     }
    }

   t=styr-nseas-1;
   if(save_for_report==1)
     {
     for(f=1;f<=Nfleet;f++)
       {
        catch_fleet(t+1,f)=equ_catch_fleet(f);  // gets all 6 elements
       for(g=1;g<=gmorph;g++)
       for(s=1;s<=nseas;s++)
         {catage(t+s,f,g)=value(equ_catage(s,f,g)); }
       }
     }

   for(p=1;p<=pop;p++)
   for(g=1;g<=gmorph;g++)
   for(s=1;s<=nseas;s++)
     {natage(t+s,p,g)(0,nages)=equ_numbers(s,p,g)(0,nages);}

   natage(styr) = natage(t+1);
   if(docheckup==1) checkup<<" init age comp"<<endl<<natage(styr)<<endl<<endl;


   // if recrdevs start before styr, then use them to adjust the initial agecomp
   //  apply a fraction of the bias adjustment, so bias adjustment gets less linearly as proceed back in time
   if(recdev_first<styr)
   {
     for (p=1;p<=pop;p++)
     for (g=1;g<=gmorph;g++)
     for (a=styr-recdev_first; a>=1; a--)
     {
       j=styr-a;
       natage(styr,p,g,a) *=mfexp(recdev(j)-biasadj(j)*SR_parm(3)*SR_parm(3)*0.5);
     }
   }

//********************************************************************
//  ProgLabel_7500_FUNCTION  get_time_series
FUNCTION get_time_series
  dvar_vector pre_AL(1,nlength);
  dvariable crashtemp; dvariable crashtemp1;
  dvariable Z_adjuster2; dvariable Z_adjuster;
  if(Do_Morphcomp) Morphcomp_exp.initialize();

//loop over time
  SpawnBio = Spbio_tot(styr);  //  need these initial assignments in case recruitment distribution occurs before spawnbio&recruits
  if(recdev_doit(styr-1)>0)
  { Recruits = R1 * mfexp(recdev(styr-1)-biasadj(styr-1)*SR_parm(3)*SR_parm(3)*0.5); }
  else
  { Recruits = R1;}

  for (y=styr;y<=endyr;y++)
  {
    yz=y;
    if(STD_Yr_Reverse_F(y)>0) F_std(STD_Yr_Reverse_F(y))=0.0;
    t_base=styr+(y-styr)*nseas-1;
    if(y>styr)
    {
      if(time_vary_MG(y,0)>0) get_MGsetup();
      if(time_vary_MG(y,2)>0 || save_for_report==1) get_growth2();  // do growth before natmort in case lorensen M is used
      if(time_vary_MG(y,1)>0) get_natmort();
      if(time_vary_MG(y,3)>0) get_wtlen();
      if(time_vary_MG(y,4)>0) get_recr_distribution();
      if(time_vary_MG(y,5)>0) get_migration();
      if(save_for_report==1)
      {
        if(time_vary_MG(y,1)>0 || time_vary_MG(y,2)>0 || time_vary_MG(y,3)>0)
        {
          get_saveGparm();
        }
      }
      get_selectivity();
    }
    for (s=1;s<=nseas;s++)
    {
      t = t_base+s;
//      if (do_once==1) cout<<" year, seas "<<y<<" "<<s<<" "<<t<<endl;
      if (docheckup==1) checkup<<endl<<"************************************"<<endl<<" year, seas "<<y<<" "<<s<<endl;
      if(time_vary_MG(y,2)>0 || time_vary_MG(y,3)>0)         //  ProgLabel_102
      {
        Make_AgeLength_Key();        // indexed by season and gmorph
      }
      if(y>styr)    // because styr is done as part of initial conditions
      {
        for (g=1;g<=gmorph;g++)
        if(use_morph(g)>0)
        {Make_FishSelex();}
        if(do_once==1 || MG_active(2)>0 || MG_active(3)>0)
        {
        Save_Wt_Age(t)=Wt_Age_beg(s);
        }
      }

      if(s==1)
      {
        SmryBio(y)=0.0;
        SmryNum(y)=0.0;
        for(g=1;g<=gmorph;g++)
        if(use_morph(g)>0)
        {
        for(p=1;p<=pop;p++)
        {
          SmryBio(y)+=natage(t,p,g)(Smry_Age,nages)*Save_Wt_Age(t,g)(Smry_Age,nages);
          SmryNum(y)+=sum(natage(t,p,g)(Smry_Age,nages));   //sums to accumulate across submorphs and birthseasons
        }
        }
      }

// Compute spawning biomass------------------------------ProgLabel_170
      if(s==spawn_seas)    //  spawning
      {
        Spbio(y).initialize();
        for (p=1;p<=pop;p++)
        {
          for (g=1;g<=gmorph;g++)
          if(sx(g)==1 && use_morph(g)>0)     //  female
          {
            Spbio(y,p,GP4(g)) += fec(g)*natage(t,p,g);
          }
        }
        SpawnBio=sum(Spbio(y));
        Spbio_tot(y)=SpawnBio;

// Compute recruitment--------------------------   ProgLabel_180
        R_base=R0;  S_base=S0;  steepness=SR_parm(2);
        if(SR_env_target==2) {R_base*=mfexp(SR_parm(4)* env_data(y,SR_env_link)); S_base*=mfexp(SR_parm(4)* env_data(y,SR_env_link));}
        if(SR_env_target==3)
        {
          temp=log((SRvec_HI(2)-SRvec_LO(2)+0.0000002)/(SR_parm(2)-SRvec_LO(2)+0.0000001)-1.)/(-2.);
          temp+=SR_parm(4)* env_data(y,SR_env_link);
          steepness=SRvec_LO(2)+(SRvec_HI(2)-SRvec_LO(2))/(1+mfexp(-2.*temp));
        }

        if(SR_fxn==1)
        {
          if(SpawnBio>S_base) {SpawnBio=S_base;}
          Recruits =  (4.*steepness*R_base*SpawnBio) / (S_base*(1.-steepness)+(5.*steepness-1.)*SpawnBio); //Beverton-Holt constrained
        }
        else if(SR_fxn==2)
        {Recruits = R_base*SpawnBio/S_base * mfexp(steepness*(1.-SpawnBio/S_base));}  // ricker
        else if(SR_fxn==3)
        {Recruits =  (4.*steepness*R_base*SpawnBio) / (S_base*(1.-steepness)+(5.*steepness-1.)*SpawnBio);} // Beverton-Holt
        else if(SR_fxn==4)
        {Recruits=R_base;}
        else
        {Recruits=0.;}

        exp_rec(y)  = (Recruits);
        if(SR_env_target==1) Recruits *= mfexp(SR_parm(4)* env_data(y,SR_env_link));
        if(SR_fxn!=4)
        { pred_rec(y) = (Recruits * mfexp(-biasadj(y)*SR_parm(3)*SR_parm(3)*0.5));}
        else
        { pred_rec(y)=(Recruits);}

        if(recdev_doit(y)>0) Recruits = pred_rec(y)*mfexp(recdev(y));
        if(y >recdev_end && Do_Forecast>0)
        {
          if(SR_fxn!=4)
          { Recruits *= mfexp(-biasadj(y)*SR_parm(3)*SR_parm(3)*0.5) * mfexp(fore_recruitments(y));}
          else
          { Recruits *= mfexp(fore_recruitments(y));}
        }

        use_rec(y) = Recruits;
      }  //  end of spawner-recruitment calculations in spawn_seas

//                                                ProgLabel_182
// distribute Recruitment of age 0 fish among the pops and gmorphs
      for (g=1;g<=gmorph;g++)
      if(use_morph(g)>0 && s==Bseas(g))
      {
        for (p=1;p<=pop;p++)
        { natage(t,p,g,0) = Recruits*recr_dist(GP(g),s,p)*submorphdist(GP2(g));}
      }
      for (p=1;p<=pop;p++)     //loop over populations      ProgLabel_104
      {
        catage_tot.initialize();
        if(catch_seas_area(t,p,0)==1 && fishery_on_off==1)
        {
          switch (F_Method)
          {
            case 1:          // F_Method is Pope's approximation
            {
              for (g=1;g<=gmorph;g++)
              if(use_morph(g)>0)
              {
                Nmid(g) = elem_prod(natage(t,p,g),surv1(s,GP3(g)));      //  get numbers-at-age(g,a) surviving to middle of time period
                if(docheckup==1) checkup<<p<<" "<<g<<" "<<GP3(g)<<" area & morph "<<endl<<"N-at-age "<<natage(t,p,g)(0,5)<<endl
                <<"survival "<<surv1(s,GP3(g))(0,5)<<endl;
              }
              for (f=1;f<=Nfleet;f++)       //loop over fishing fleets       ProgLabel_105
              if (catch_seas_area(t,p,f)==1)
              {
                dvar_matrix catage_w=catage(t,f);      // do shallow copy

                vbio.initialize();
                for (g=1;g<=gmorph;g++)
                if(use_morph(g)>0)
                {
                  gg=sx(g);              //  ProgLabel_107
                  // use sel_l to get total catch and use sel_l_r to get retained vbio
                  // note that vbio in numbers can be used for both survey abund and fishery available "biomass"
                  // vbio is for retained catch only;  harvest rate = retainedcatch/vbio;
                  // then harvestrate*catage_w = total kill by this fishery for this morph

                  catage_w(g)=elem_prod(Nmid(g),deadfish(s,g,f));     // total kill numbers at age
                  if(docheckup==1) checkup<<"killrate "<<deadfish(s,g,f)(0,6)<<endl;
                  if(catchunits(f)==1)
                  { vbio+=Nmid(g)*sel_al_2(s,g,f);}    // retained catch bio
                  else
                  { vbio+=Nmid(g)*sel_al_4(s,g,f);}  // retained catch numbers

                }  //close gmorph loop
                if(docheckup==1) checkup<<"fleet vbio obscatch "<<f<<" "<<vbio<<" "<<catch_ret_obs(f,t)<<endl;
                crashtemp1=0.;
                crashtemp=max_harvest_rate-catch_ret_obs(f,t)/(vbio+NilNumbers);                           // ProgLabel_152
                crashtemp1=posfun(crashtemp,0.000001,CrashPen);
                harvest_rate=max_harvest_rate-crashtemp1;
                if(crashtemp<0.&&rundetail>=2) {cout<<y<<" "<<f<<" crash vbio "<<catch_ret_obs(f,t)/vbio<<" "<<crashtemp<<
                 " "<<crashtemp1<<" "<<CrashPen<<" "<<harvest_rate<<endl;}
                Hrate(f,t) = harvest_rate;

                for (g=1;g<=gmorph;g++)
                if(use_morph(g)>0)
                {
                  catage_w(g) *= harvest_rate;                       // Total catch at age
                  catage_tot(g) += catage_w(g);                      //catch at age for all fleets
                  gg=sx(g);
                  catch_fleet(t,f,2)+=Hrate(f,t)*Nmid(g)*deadfish_B(s,g,f);      // total fishery kill in biomass
                  catch_fleet(t,f,5)+=Hrate(f,t)*Nmid(g)*deadfish(s,g,f);     // total fishery kill in numbers
                  catch_fleet(t,f,1)+=Hrate(f,t)*Nmid(g)*sel_al_1(s,g,f);      //  total fishery encounter in biomass
                  catch_fleet(t,f,3)+=Hrate(f,t)*Nmid(g)*sel_al_2(s,g,f);      // retained fishery kill in biomass
                  catch_fleet(t,f,4)+=Hrate(f,t)*Nmid(g)*sel_al_3(s,g,f);      // encountered numbers
                  catch_fleet(t,f,6)+=Hrate(f,t)*Nmid(g)*sel_al_4(s,g,f);      // retained fishery kill in numbers
                }  // end g loop
              }  // close fishery

              for (g=1;g<=gmorph;g++)
              if(use_morph(g)>0)
              {
                for (a=0;a<=nages;a++)    //  check for negative abundance, starting at age 1
                {
                  crashtemp=max_harvest_rate-catage_tot(g,a)/(Nmid(g,a)+0.0000001);
                  crashtemp1=posfun(crashtemp,0.000001,CrashPen);
                  if(crashtemp<0.&&rundetail>=2) {cout<<" crash age "<<catage_tot(g,a)/(Nmid(g,a)+0.0000001)<<" "<<crashtemp<<
                    " "<<crashtemp1<<" "<<CrashPen<<" "<<(max_harvest_rate-crashtemp1)*Nmid(g,a)<<endl; }
                  if(crashtemp<0.&&docheckup==1) {checkup<<" crash age "<<catage_tot(g,a)/(Nmid(g,a)+0.0000001)<<" "<<crashtemp<<
                    " "<<crashtemp1<<" "<<CrashPen<<" "<<(max_harvest_rate-crashtemp1)*Nmid(g,a)<<endl; }
                  catage_tot(g,a)=(max_harvest_rate-crashtemp1)*Nmid(g,a);
                }
                if(docheckup==1) checkup<<"total catch-at-age for morph "<<g<<" "<<catage_tot(g)(0,6)<<endl;
              }
              break;
            }   //  end Pope's approx

            case 2:          // continuous F_method
            {
              for (g=1;g<=gmorph;g++)
              if(use_morph(g)>0)
              {
                Z_rate(t,p,g)=natM(s,GP3(g));
                for (f=1;f<=Nfleet;f++)       //loop over fishing fleets to get Z       ProgLabel_105
                if (catch_seas_area(t,p,f)==1)
                {
                  Z_rate(t,p,g)+=deadfish(s,g,f)*Hrate(f,t);
                }
                Zrate2(g)=elem_div( (1.-mfexp(-seasdur(s)*Z_rate(t,p,g))), Z_rate(t,p,g));
              }

              for (f=1;f<=Nfleet;f++)       //loop over fishing fleets       ProgLabel_105
              if (catch_seas_area(t,p,f)==1)
              {
                for (g=1;g<=gmorph;g++)
                if(use_morph(g)>0)
                {
                  catch_fleet(t,f,1)+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_1(s,g,f))*Zrate2(g);
                  catch_fleet(t,f,2)+=Hrate(f,t)*elem_prod(natage(t,p,g),deadfish_B(s,g,f))*Zrate2(g);
                  catch_fleet(t,f,3)+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_2(s,g,f))*Zrate2(g); // retained bio
                  catch_fleet(t,f,4)+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_3(s,g,f))*Zrate2(g);
                  catch_fleet(t,f,5)+=Hrate(f,t)*elem_prod(natage(t,p,g),deadfish(s,g,f))*Zrate2(g);
                  catch_fleet(t,f,6)+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_4(s,g,f))*Zrate2(g);  // retained numbers
                  catage(t,f,g)=Hrate(f,t)*elem_prod(elem_prod(natage(t,p,g),deadfish(s,g,f)),Zrate2(g));
                }  //close gmorph loop
              }  // close fishery
              break;
            }   //  end continuous F method

            case 3:          // hybrid F_method
            {
              // start by doing a Pope's approximation
              for (g=1;g<=gmorph;g++)
              if(use_morph(g)>0)
              {
                Nmid(g) = elem_prod(natage(t,p,g),surv1(s,GP3(g)));      //  get numbers-at-age(g,a) surviving to middle of time period
              }
              for (f=1;f<=Nfleet;f++)       //loop over fishing fleets       TAG_105
              if (catch_seas_area(t,p,f)==1)  // do exact catch for this fleet
              {
                vbio.initialize();
                for (g=1;g<=gmorph;g++)
                if(use_morph(g)>0)
                {
                  if(catchunits(f)==1)
                    {vbio+=Nmid(g)*sel_al_2(s,g,f);}    // retained catch bio
                  else
                    {vbio+=Nmid(g)*sel_al_4(s,g,f);}  // retained catch numbers
                }  //close gmorph loop
                temp = catch_ret_obs(f,t)/vbio;  //  Pope's rate
                join1=1./(1.+mfexp(30.*(temp-0.95)));  // steep logistic joiner at harvest rate of 0.95
                temp1=join1*temp + (1.-join1)*0.95;
                Hrate(f,t)=-log(1.-temp1)/seasdur(s);  // initial estimate of F (even though labelled as Hrate)
                //  done with starting values from Pope's approximation
              }
              else
              {
                // Hrate(f,t) previously set to zero or set to a parameter value
              }
              int tune_F;
            	for(tune_F=1;tune_F<=F_Tune;tune_F++)
              {
                // add F+M to get Z using both exact and parameter based F
                for (g=1;g<=gmorph;g++)
                if(use_morph(g)>0)
                {
                  Z_rate(t,p,g)=natM(s,GP3(g));
                  for (f=1;f<=Nfleet;f++)       //loop over fishing fleets to get Z
                  if (catch_seas_area(t,p,f)!=0)
                  {
                    Z_rate(t,p,g)+=deadfish(s,g,f)*Hrate(f,t);
                  }
                  Zrate2(g)=elem_div( (1.-mfexp(-seasdur(s)*Z_rate(t,p,g))), Z_rate(t,p,g));
                }
                //  now calc adjustment to Z based on changes to be made to Hrate
                if(tune_F<F_Tune)
                {
                  Z_adjuster2=0.0;   // this is the expected total catch that would occur with the current Hrates and Z
                  for (f=1;f<=Nfleet;f++)
                  if (catch_seas_area(t,p,f)==1)
                  {
                    for (g=1;g<=gmorph;g++)
                    if(use_morph(g)>0)
                    {
                      if(catchunits(f)==1)
                      {
                        Z_adjuster2+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_2(s,g,f))*Zrate2(g);  // biomass basis
                      }
                      else
                      {
                        Z_adjuster2+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_4(s,g,f))*Zrate2(g);  //  numbers basis
                      }
                    }  //close gmorph loop
                  }  // close fishery
                  Z_adjuster = totcatch_byarea(t,p)/(Z_adjuster2+0.0001);   // but this totcatch_by_area needs to exclude fisheries with F from param
                  for (g=1;g<=gmorph;g++)
                  if(use_morph(g)>0)
                  {
                    Z_rate(t,p,g)=natM(s,GP3(g)) + Z_adjuster*(Z_rate(t,p,g)-natM(s,GP3(g)));  // need to modify to only do the exact catches
                    Zrate2(g)=elem_div( (1.-mfexp(-seasdur(s)*Z_rate(t,p,g))), Z_rate(t,p,g));
                  }
                  for (f=1;f<=Nfleet;f++)       //loop over fishing fleets       TAG_105
                  if(catch_seas_area(t,p,f)==1)
                  {
                    Z_adjuster2=0.;  // now use this to calc the available biomass to each fishery with the adjusted Zrate2
                    for (g=1;g<=gmorph;g++)
                    if(use_morph(g)>0)
                    {
                      if(catchunits(f)==1)
                      {
                        Z_adjuster2+=elem_prod(natage(t,p,g),sel_al_2(s,g,f))*Zrate2(g);
                      }
                      else
                      {
                        Z_adjuster2+=elem_prod(natage(t,p,g),sel_al_4(s,g,f))*Zrate2(g);
                      }
                    }  //close gmorph loop
                    temp=catch_ret_obs(f,t)/(Z_adjuster2+0.0001);
                    join1=1./(1.+mfexp(30.*(temp-0.95*max_harvest_rate)));
                    Hrate(f,t)=join1*temp + (1.-join1)*max_harvest_rate;
                  }  // close fishery
                }
                else
                {
                for (f=1;f<=Nfleet;f++)       //loop over fishing fleets       ProgLabel_105
                if (catch_seas_area(t,p,f)==1)
                {
                  for (g=1;g<=gmorph;g++)
                  if(use_morph(g)>0)
                  {
                    catch_fleet(t,f,1)+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_1(s,g,f))*Zrate2(g);
                    catch_fleet(t,f,2)+=Hrate(f,t)*elem_prod(natage(t,p,g),deadfish_B(s,g,f))*Zrate2(g);
                    catch_fleet(t,f,3)+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_2(s,g,f))*Zrate2(g);
                    catch_fleet(t,f,4)+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_3(s,g,f))*Zrate2(g);
                    catch_fleet(t,f,5)+=Hrate(f,t)*elem_prod(natage(t,p,g),deadfish(s,g,f))*Zrate2(g);
                    catch_fleet(t,f,6)+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_4(s,g,f))*Zrate2(g);
                    catage(t,f,g)=Hrate(f,t)*elem_prod(elem_prod(natage(t,p,g),deadfish(s,g,f)),Zrate2(g));
                  }  //close gmorph loop
                }  // close fishery
              }
              }
              break;
            }   //  end hybrid F_Method
          }  // end F_Method switch
        }  //  end have some catch in this seas x area
        else
        {
          for (g=1;g<=gmorph;g++)
          if(use_morph(g)>0)
          {Z_rate(t,p,g)=natM(s,GP3(g));}
        }
        int dolen;
//  check for data
        for (f=1;f<=Ntypes;f++)       //loop over fleets and surveys with data       ProgLabel_105
        if (fleet_area(f)==p)
        {
          if(have_data(f,t)>0)      // ProgLabel_106  make the age-length available pop summed over all growth morphs
          {
            exp_AL.initialize();
            timing = seasdur(s)*surveytime(f);
            if(seltype(f,1)>0 && seltype(f,1)<30) {dolen=1;} else {dolen=0;}
            for (g=1;g<=gmorph;g++)
            if(use_morph(g)>0)
            {
              gg=sx(g);
              if(gg==2)
              { L1=nlength1; L2= nlength2; A2=nages+1;}    //  move over on length dimension to store males
              else
              { L1=1; L2=nlength; A2=0;}
              if(F_Method==1) //  Pope's approximation
              {
                for (a=0;a<=nages;a++)
                {
                  temp=(natage(t,p,g,a)*mfexp(-natM(s,GP3(g),a)*timing)-surveytime(f)*catage_tot(g,a))*sel_a(y,f,gg,a);
                  if(dolen==1)
                  {pre_AL.shift(1)=temp*elem_prod(ALK(s,g,a),sel_l(y,f,gg));}
                  else
                  {pre_AL.shift(1)=temp*ALK(s,g,a);}

                  exp_AL(a+A2)(L1,L2) += pre_AL.shift(L1);  // shifted to store males in right place and accumulated across morphs
                  tempvec(a)=temp;
                } // close age loop
              }  // end Pope's approx

              else   //  continuous F
              {
                for (a=0;a<=nages;a++)
                {
                  temp=natage(t,p,g,a)*mfexp(-Z_rate(t,p,g,a)*timing) *sel_a(y,f,gg,a);
                  if(dolen==1)
                  {pre_AL.shift(1)=temp*elem_prod(ALK(s,g,a),sel_l(y,f,gg));}
                  else
                  {pre_AL.shift(1)=temp*ALK(s,g,a);}
                  exp_AL(a+A2)(L1,L2) += pre_AL.shift(L1);  // shifted to store males in right place and accumulated across morphs
                  tempvec(a)=temp;
                } // close age loop
              }  // end continuous F

              if(Do_Morphcomp)
              {
                if(Morphcomp_havedata(f,t,0)>0)
                {
                  Morphcomp_exp(Morphcomp_havedata(f,t,0),5+GP4(g))+=sum(tempvec);     // total catch of this gpattern in this season x area
                }
              }
            } //close gmorph loop

        exp_l_temp=colsum(exp_AL);
        if(seltype(f,2)!=0)
          {exp_l_temp_ret=elem_prod(exp_l_temp,retain(y,f));}
        else
          {exp_l_temp_ret=exp_l_temp;}

//          end creation of selected A-L
// expected discard amount ************************************* ProgLabel_109
        if(yr_disc2(f,t)>0)
          {
            j=yr_disc2(f,t);
            if(catch_ret_obs(f,t)>0.0)
            {
              if(catchunits(f)==1)
              {
            exp_disc(f,j)=catch_fleet(t,f,1)-catch_fleet(t,f,3);
            if(disc_type==2) exp_disc(f,j) /= (catch_fleet(t,f,1) + 0.0000001);
          }
          else
              {
            exp_disc(f,j)=catch_fleet(t,f,4)-catch_fleet(t,f,6);
            if(disc_type==2) exp_disc(f,j) /= (catch_fleet(t,f,4) + 0.0000001);
          }

            }
            else
            {
              exp_disc(f,j)=-1.;
            }
          }

// expected mean weight *************************************** ProgLabel_109a
        if(nobs_mnwt>0)
          {
          j=yr_mnwt2(f,t,0);
          if(j>0) {exp_mnwt(j) = (exp_l_temp*wt_len2(s)) / sum(exp_l_temp);}  // total sample
          j=yr_mnwt2(f,t,1);
          if(j>0) exp_mnwt(j) = (exp_l_temp-exp_l_temp_ret)*wt_len2(s) / (sum(exp_l_temp)-sum(exp_l_temp_ret));  // discard sample
          j=yr_mnwt2(f,t,2);
          if(j>0) exp_mnwt(j) = (exp_l_temp_ret*wt_len2(s)) / sum(exp_l_temp_ret);    // retained only
          }

// expected weight frequency ****************************************ProgLabel_041
//    int ibin;
//    int ibinsave;
//    int fini;
    int WtFreqMethod_seas;
    if(WtFreq_Nmeth>0)       //  have some wtfreq data
    {
//     create the transition matrices to convert population length bins to weight freq
      for(WtFreqMethod=1;WtFreqMethod<=WtFreq_Nmeth;WtFreqMethod++)
      {
        WtFreqMethod_seas=nseas*(WtFreqMethod-1)+s;     // index that combines wtfreqmethod and season and used in WtFreqTrans
        if(WtFreq_HaveObs2(WtFreqMethod,t)==f)  // first occurrence of this method at this time is with fleet = f
        {
          if(do_once==1 || (MG_active(3)>0 && (time_vary_MG(y,3)>0 )))  // calc the matrix because it may have changed
          {
            for(gg=1;gg<=gender;gg++)
            {
              if(gg==1)
              {z1=1;z2=nlength;ibin=0; ibinsave=0;}  // female
              else
              {z1=nlength1; z2=nlength2; ibin=0; ibinsave=WtFreq_Nbins(WtFreqMethod);}   // male
              topbin=0.;
              botbin=0.;

              switch(WtFreq_units(WtFreqMethod))    // biomass vs. numbers
              {
                case(1):  // units are biomass, so accumulate body weight into the bins;  Assume that bin demarcations are also in biomass
                {
                  if(WtFreq_Omit_Small(WtFreqMethod)==1)
                  {while(wt_len2(s,z1+1)<WtFreq_bins(WtFreqMethod,1)) {z1++;}}      // ignore tiny fish

                  for(z=z1;z<=z2;z++)
                  {
                    if(ibin==WtFreq_Nbins(WtFreqMethod))
                    {WtFreqTrans(WtFreqMethod_seas,z,ibinsave)=wt_len2(s,z);}  //checkup<<" got to last ibin, so put rest of popbins here"<<endl;
                    else
                    {
                      if(wt_len2(s,z)>=topbin) {ibin++; ibinsave++;}  //checkup<<" incr ibin "<<z<<" "<<ibin<<" "<<len_bins(z)<<" "<<len_bins_dat(ibin);
                      if(ibin>1)  {botbin=WtFreq_bins2(WtFreqMethod,ibin);}
                      if(ibin==WtFreq_Nbins(WtFreqMethod))  // checkup<<" got to last ibin, so put rest of popbins here"<<endl;
                      {
                        WtFreqTrans(WtFreqMethod_seas,z,ibinsave)=wt_len2(s,z);
                        topbin=99999.;
                      }
                      else
                      {
                        topbin=WtFreq_bins2(WtFreqMethod,ibin+1);
                        if(wt_len2(s,z)>=botbin && wt_len2(s,z+1)<=topbin )  //checkup<<" pop inside dat, put here"<<endl;
                        {WtFreqTrans(WtFreqMethod_seas,z,ibinsave)=wt_len2(s,z);}
                        else       // checkup<<" overlap"<<endl;
                        {
                          temp=(wt_len2(s,z+1)-topbin)/wt_len_fd(s,z);  // frac in pop bin above (data bin +1)
                          temp1=wt_len2(s,z)+(1.-temp*0.5)*wt_len_fd(s,z);  // approx body wt for these fish
                          temp2=wt_len2(s,z)+(1.-temp)*0.5*wt_len_fd(s,z);  // approx body wt for  fish below
//                          checkup<<z<<" "<<wt_len2(s,z)<<" "<<topbin<<" "<<temp<<" "<<temp1<<" "<<temp2<<endl;
                          WtFreqTrans(WtFreqMethod_seas,z,ibinsave+1)=temp*temp1;
                          WtFreqTrans(WtFreqMethod_seas,z,ibinsave)=(1.-temp)*temp2;
                        }
                      }
                    }
                  }
                  break;
                }  //  end of units in biomass
                // NOTE: even though  the transition matrix is currently in units of biomass distribution, there is no need to
                // normalize to sum to 1.0 here because the normalization will occur after it gets used to create WtFreq_exp

                case(2):   // units are numbers
                {
                  if(WtFreq_scale(WtFreqMethod)<=2)   //  bin demarcations are in weight units (1=kg, 2=lbs), so uses wt_len to compare to bins
                  {
                    if(WtFreq_Omit_Small(WtFreqMethod)==1)
                    {while(wt_len2(s,z1+1)<WtFreq_bins(WtFreqMethod,1)) {z1++;}}      // ignore tiny fish
                    for(z=z1;z<=z2;z++)
                    {
                      if(ibin==WtFreq_Nbins(WtFreqMethod))
                      {WtFreqTrans(WtFreqMethod_seas,z,ibinsave)=1.;}  //checkup<<" got to last ibin, so put rest of popbins here"<<endl;
                      else
                      {
                        if(wt_len2(s,z)>=topbin) {ibin++; ibinsave++;}  //checkup<<" incr ibin "<<z<<" "<<ibin<<" "<<len_bins(z)<<" "<<len_bins_dat(ibin);
                        if(ibin>1)  {botbin=WtFreq_bins2(WtFreqMethod,ibin);}
                        if(ibin==WtFreq_Nbins(WtFreqMethod))  // checkup<<" got to last ibin, so put rest of popbins here"<<endl;
                        {
                          WtFreqTrans(WtFreqMethod_seas,z,ibinsave)=1.;
                          topbin=99999.;
                        }
                        else
                        {
                          topbin=WtFreq_bins2(WtFreqMethod,ibin+1);
                          if(wt_len2(s,z)>=botbin && wt_len2(s,z+1)<=topbin )  //checkup<<" pop inside dat, put here"<<endl;
                          {WtFreqTrans(WtFreqMethod_seas,z,ibinsave)=1.;}
                          else       // checkup<<" overlap"<<endl;
                          {
                            WtFreqTrans(WtFreqMethod_seas,z,ibinsave+1)=(wt_len2(s,z+1)-topbin)/wt_len_fd(s,z);
                            WtFreqTrans(WtFreqMethod_seas,z,ibinsave)=1.-WtFreqTrans(WtFreqMethod_seas,z,ibinsave+1);
                          }
                        }
                      }
                    }
                  }

                  else       //  bin demarcations are in length unit (3=cm, 4=inch) so uses population len_bins to compare to data bins
                  {
                    if(WtFreq_Omit_Small(WtFreqMethod)==1)
                    {while(len_bins2(z1+1)<WtFreq_bins(WtFreqMethod,1)) {z1++;}}      // ignore tiny fish
                    for(z=z1;z<=z2;z++)
                    {
                      if(ibin==WtFreq_Nbins(WtFreqMethod))
                      {WtFreqTrans(WtFreqMethod_seas,z,ibinsave)=1.;} //checkup<<" got to last ibin, so put rest of popbins here"<<endl;
                      else
                      {
                        if(len_bins2(z)>=topbin) {ibin++; ibinsave++;}  //checkup<<" incr ibin "<<z<<" "<<ibin<<" "<<len_bins(z)<<" "<<len_bins_dat(ibin);
                        if(ibin>1)  {botbin=WtFreq_bins2(WtFreqMethod,ibin);}
                        if(ibin==WtFreq_Nbins(WtFreqMethod))  // checkup<<" got to last ibin, so put rest of popbins here"<<endl;
                        {
                          WtFreqTrans(WtFreqMethod_seas,z,ibinsave)=1.;
                          topbin=99999.;
                        }
                        else
                        {
                          topbin=WtFreq_bins2(WtFreqMethod,ibin+1);
                          if(len_bins2(z)>=botbin && len_bins2(z+1)<=topbin )  //checkup<<" pop inside dat, put here"<<endl;
                          {WtFreqTrans(WtFreqMethod_seas,z,ibinsave)=1.;}
                          else       // checkup<<" overlap"<<endl;
                          {
                            WtFreqTrans(WtFreqMethod_seas,z,ibinsave+1)=(len_bins2(z+1)-topbin)/(len_bins2(z+1)-len_bins2(z));
                            WtFreqTrans(WtFreqMethod_seas,z,ibinsave)=1.-WtFreqTrans(WtFreqMethod_seas,z,ibinsave+1);
                          }
                        }
                      }
                    }
                  }
                  break;
                }  //  end of units in numbers
              }
              if(docheckup==1 && gg==gender) checkup<<" wtfreq trans_matrix: method/season "<<WtFreqMethod<<" / "<<s<<endl
              <<trans(WtFreqTrans(WtFreqMethod_seas))<<endl;
            }  // end gender loop
          }  //  end needing to calc the matrix because it may have changed
        }  // done calculating the WtFreqTransition matrix for this method

        if(WtFreq_HaveObs(f,WtFreqMethod,t,1)>0)
        {
          for(iobs=WtFreq_HaveObs(f,WtFreqMethod,t,1);iobs<=WtFreq_HaveObs(f,WtFreqMethod,t,2);iobs++)
          {
            switch(WtFreq_obs_hdr(iobs,5))   // discard/retained partition
            {
              case(0):
              {
                WtFreq_exp(iobs)=trans(WtFreqTrans(WtFreqMethod_seas))*exp_l_temp;
                break;
              }
              case(1):
              {
                WtFreq_exp(iobs)=trans(WtFreqTrans(WtFreqMethod_seas))*(exp_l_temp-exp_l_temp_ret);
                break;
              }
              case(2):
              {
                WtFreq_exp(iobs)=trans(WtFreqTrans(WtFreqMethod_seas))*exp_l_temp_ret;
                break;
              }
            }
            if(gender==2)
            {
              k=WtFreq_obs_hdr(iobs,8);  // max bins for this method
              switch(WtFreq_obs_hdr(iobs,4))   //  combine, select or each gender
              {
                case(0):                    // combine genders
                {
                  for(ibin=1;ibin<=k;ibin++) WtFreq_exp(iobs,ibin)+=WtFreq_exp(iobs,k+ibin);
                  WtFreq_exp(iobs)(1,k)/=sum(WtFreq_exp(iobs)(1,k));
                  if(WtFreq_mincomp(WtFreqMethod)>0.0)
                  {
                    WtFreq_exp(iobs)(1,k)+=WtFreq_mincomp(WtFreqMethod);
                    WtFreq_exp(iobs)(1,k)/=sum(WtFreq_exp(iobs)(1,k));
                  }
                  break;
                }
                case(1):     // female only
                {
                  WtFreq_exp(iobs)(1,k)/=sum(WtFreq_exp(iobs)(1,k));
                  if(WtFreq_mincomp(WtFreqMethod)>0.0)
                  {
                    WtFreq_exp(iobs)(1,k)+=WtFreq_mincomp(WtFreqMethod);
                    WtFreq_exp(iobs)(1,k)/=sum(WtFreq_exp(iobs)(1,k));
                  }
                  break;
                }
                case(2):            //   male only
                {
                  ibin=WtFreq_obs_hdr(iobs,7);
                  WtFreq_exp(iobs)(ibin,k)/=sum(WtFreq_exp(iobs)(ibin,k));
                  if(WtFreq_mincomp(WtFreqMethod)>0.0)
                  {
                    WtFreq_exp(iobs)(ibin,k)+=WtFreq_mincomp(WtFreqMethod);
                    WtFreq_exp(iobs)(ibin,k)/=sum(WtFreq_exp(iobs)(ibin,k));
                  }
                  break;
                }
                case(3):           //  each gender
                {
                  WtFreq_exp(iobs)/=sum(WtFreq_exp(iobs));
                  if(WtFreq_mincomp(WtFreqMethod)>0.0)
                  {
                    WtFreq_exp(iobs)+=WtFreq_mincomp(WtFreqMethod);
                    WtFreq_exp(iobs)/=sum(WtFreq_exp(iobs));
                  }
                  break;
                }
              }  //  end gender switch
            }  // end have 2 genders
            else
            {
              k=WtFreq_obs_hdr(iobs,8);  // max bins for this method
              WtFreq_exp(iobs)(1,k)/=sum(WtFreq_exp(iobs)(1,k));
              if(WtFreq_mincomp(WtFreqMethod)>0.0)
              {
                WtFreq_exp(iobs)(1,k)+=WtFreq_mincomp(WtFreqMethod);
                WtFreq_exp(iobs)(1,k)/=sum(WtFreq_exp(iobs)(1,k));
              }
            }
          }  // end loop of obs for fleet = f
        }   //  end having some obs for this method in this fleet
      }  // end loop of wtfreqmethods
    }    //  end use of wt freq data


        // expected biomass index ************************************* ProgLabel_110
// NOTE that the Q scaler is factored in later on
       if(yr_cr2(f,t)>0)
         {
         j=yr_cr2(f,t);
         if (seltype(f,1)>=30)
         {
           switch(seltype(f,1))
           {
             case 30:  // spawning biomass  #30
             {
               if(pop==1 || fleet_area(f)==0)
               {
                 vbio=SpawnBio;
                }
                else
                {
                  vbio=sum(Spbio(y,fleet_area(f)));
                }
               break;
             }
             case 31:  // recruitment deviation  #31
             {vbio=mfexp(recdev(y)); break;}
             case 32:  // recruitment without density-dependence (for pre-recruit survey) #32
             {vbio=SpawnBio*mfexp(recdev(y)); break;}
             case 33:  // recruitment  #33
             {vbio=Recruits; break;}
           }
         }
         else
           {
           if(Q_setup(f,5)==1)
             {vbio=exp_l_temp_ret*wt_len2(s);}   // biomass
           else
             {vbio=sum(exp_l_temp_ret);}              // numbers
           }
         vul_bio(f,j)=value(vbio);
         if(Q_setup(f,1)>0) vbio=pow(vbio,1.0+Q_parm(Q_setup_parms(f,1)));
         exp_cr(f,j)=log(vbio+0.000001);
         }
//                              if (do_once==1) cout<<" survey OK  "<<endl;

//  Calc expected size comp ************************************* ProgLabel_120
        if(yr_l2(1,f,t)>0)
        {
         for(i=yr_l2(1,f,t);i<=yr_l2(2,f,t);i++)                          // loop obs in this type/time
         {
//                                                               ProgLabel_122
          if(LenBin_option>1)
          {
          if(mkt_l(f,i)==0) exp_l(f,i) = make_len_bin*exp_l_temp;           // expected size comp  MAtrix * vector = vector
          else if(mkt_l(f,i)==1) exp_l(f,i) = make_len_bin*(exp_l_temp-exp_l_temp_ret);  // discard sample
          else exp_l(f,i) = make_len_bin*exp_l_temp_ret;    // retained only
          }
          else
          {
          if(mkt_l(f,i)==0) exp_l(f,i) = exp_l_temp;           // expected size comp  MAtrix * vector = vector
          else if(mkt_l(f,i)==1) exp_l(f,i) = (exp_l_temp-exp_l_temp_ret);  // discard sample
          else exp_l(f,i) = exp_l_temp_ret;    // retained only
          }
          if(docheckup==1) checkup<<" len obs "<<mkt_l(f,i)<<" "<<tails_l(f,i)<<endl<<obs_l(f,i)<<endl<<exp_l(f,i)<<endl;
         // move code for tail compression, etc to the likelihood section to allow for superyear combinations                                                                      // mkt=0 Do nothing
         }  // end lengthcomp loop within fleet/time
        }  // end have lengthcomps in this fleet/time

//  ProgLabel_130   size@age in the bins and with ageing error
        if(yr_ms2(1,f,t)>0)
         {
         for(i=yr_ms2(1,f,t);i<=yr_ms2(2,f,t);i++)         // loop obs in this type/time
         {
          k=ageerr_type_ms(f,i);                           //  age-err type
          if(mkt_ms(f,i)==0)
          {
           exp_a_temp = age_age(k) * rowsum(exp_AL) + 1.0e-10;             //  numbers at binned age = age_age(bins,age) * sum(age)
           exp_ms(f,i) = age_age(k) * (exp_AL * len_bins_m2);  // numbers * length
           exp_ms_sq(f,i) = age_age(k) * (exp_AL * len_bins_sq);  // numbers * length^2
          }
          if(mkt_ms(f,i)==1)
          {
           exp_a_temp = age_age(k) * (exp_AL * (1-retain(y,f)))+ 1.0e-10;             //  numbers at binned age = age_age(bins,age) * sum(age)
           exp_ms(f,i) = age_age(k) * (exp_AL * elem_prod((1-retain(y,f)),len_bins_m2));  // numbers * length
           exp_ms_sq(f,i) = age_age(k) * (exp_AL * elem_prod((1-retain(y,f)),len_bins_sq));  // numbers * length^2
          }

          if(mkt_ms(f,i)==2)
          {
           exp_a_temp = age_age(k) * (exp_AL * retain(y,f) ) + 1.0e-10;             //  numbers at binned age = age_age(bins,age) * sum(age)
           exp_ms(f,i) = age_age(k) * (exp_AL * elem_prod((retain(y,f)),len_bins_m2));  // numbers * length
           exp_ms_sq(f,i) = age_age(k) * (exp_AL * elem_prod((retain(y,f)),len_bins_sq));  // numbers * length^2
          }
          exp_ms_sq(f,i) = sqrt(
            elem_div(
            (exp_ms_sq(f,i) - elem_div(elem_prod(exp_ms(f,i),exp_ms(f,i)), exp_a_temp))
            , exp_a_temp))
            + 0.000001;    //std.dev. of size at binned age = sqrt( (P2-P1*P1/P0) / P0 )

          exp_ms(f,i) = elem_div(exp_ms(f,i), exp_a_temp);   //  mean size at binned age
         }
          }   // end size-at-age

//                              if (do_once==1) cout<<" got LAA  "<<endl;

//  get expected age comp in the bins and with ageing error *****ProgLabel_140
        if(yr_a2(1,f,t)>0)
        {
         for(i=yr_a2(1,f,t);i<=yr_a2(2,f,t);i++)                          // loop obs in this type/time
         {
          k=ageerr_type_a(f,i);                           //  age-err type

          if(use_Lbin_filter(f,i)==0)
           {                                              // sum across all length bins
          if(mkt_a(f,i)==0) agetemp = rowsum(exp_AL);             //  numbers at binned age = age_age(bins,age) * sum(age)
          if(mkt_a(f,i)==1) agetemp = exp_AL * (1.-retain(y,f));  // discard sample
          if(mkt_a(f,i)==2) agetemp = exp_AL * retain(y,f);    // retained only
           }
          else
           {            // only use ages from specified range of size bins
                        // Lbin_filter is a vector with 0 for unselected size bins and 1 for selected bins
          if(mkt_a(f,i)==0) agetemp = exp_AL * Lbin_filter(f,i);             //  numbers at binned age = age_age(bins,age) * sum(age)
          if(mkt_a(f,i)==1) agetemp = exp_AL * elem_prod(Lbin_filter(f,i),(1.-retain(y,f)));  // discard sample
          if(mkt_a(f,i)==2) agetemp = exp_AL * elem_prod(Lbin_filter(f,i),retain(y,f));    // retained only
           }
          exp_a(f,i) = age_age(k) * agetemp;

          //if(docheckup==1) checkup<<" age obs "<<mkt_a(f,i)<<" "<<k<<" "<<tails_a(f,i)<<endl<<obs_a(f,i)<<endl<<exp_a(f,i)<<endl;

         }  // end agecomp loop within fleet/time
        }  // end have agecomps in this fleet/time
          }  // end have data
        }  //  close fleet loop

//  survival to next year --------------------------  ProgLabel_150
        if(s==nseas) {k=1;} else {k=0;}   //      advance age or not
        for (g=1;g<=gmorph;g++)
        if(use_morph(g)>0)
        {
          if(F_Method==1)  // pope's
          {
              if(s<nseas) natage(t+1,p,g,0) = natage(t,p,g,0)*surv2(s,GP3(g),0) -catage_tot(g,0)*surv1(s,GP3(g),0);  // advance age zero within year

              for (a=1;a<nages;a++)
              {natage(t+1,p,g,a) = natage(t,p,g,a-k)*surv2(s,GP3(g),a-k) -catage_tot(g,a-k)*surv1(s,GP3(g),a-k);}
              natage(t+1,p,g,nages) = natage(t,p,g,nages)*surv2(s,GP3(g),nages) - catage_tot(g,nages)*surv1(s,GP3(g),nages);   // plus group
              if(s==nseas) natage(t+1,p,g,nages) += natage(t,p,g,nages-1)*surv2(s,GP3(g),nages-1) - catage_tot(g,nages-1)*surv1(s,GP3(g),nages-1);
          }
          else   // continuous F
          {
            if(s<nseas) natage(t+1,p,g,0) = natage(t,p,g,0)*mfexp(-Z_rate(t,p,g,0)*seasdur(s));  // advance age zero within year
            for (a=1;a<nages;a++) {natage(t+1,p,g,a) = natage(t,p,g,a-k)*mfexp(-Z_rate(t,p,g,a-k)*seasdur(s));}
            natage(t+1,p,g,nages) = natage(t,p,g,nages)*mfexp(-Z_rate(t,p,g,nages)*seasdur(s));   // plus group
            if(s==nseas) natage(t+1,p,g,nages) += natage(t,p,g,nages-1)*mfexp(-Z_rate(t,p,g,nages-1)*seasdur(s));
          }
          if(docheckup==1)
          {
            checkup<<" Morph "<<g<<endl<<" natM:"<<endl<<natM<<endl;
            if(F_Method>1) checkup<<"Z-at-age "<<Z_rate(t,p,g)(0,6)<<endl;
            checkup<<" survivors "<<natage(t+1,p,g)(0,6)<<endl;
          }

        } // close gmorph loop
      } //close population loop                  ProgLabel_160


//do migration between populations, for each gmorph and age      ProgLabel_190
      if(do_migration>0)
      {
        natage_temp=natage(t+1);
        natage(t+1)=0.0;
        for (p=1;p<=pop;p++)  //   source population
        for (p2=1;p2<=pop;p2++)  //  destination population
        for (g=1;g<=gmorph;g++)
        if(use_morph(g)>0)
        {
          k=move_pattern(s,GP4(g),p,p2);
          if(k>0) natage(t+1,p2,g) += elem_prod(natage_temp(p,g),migrrate(y,k));}
      }  //  end migration

//  save selectivity*Hrate for tag-recapture
      if(Do_TG>0 && t>=TG_timestart)
      {
        for(g=1;g<=gmorph;g++)
        for(f=1;f<=Nfleet;f++)
        {
          Sel_for_tag(t,g,f) = sel_al_4(s,g,f)*Hrate(f,t);
        }
      }

    if( (save_for_report==1) || ((sd_phase() || mceval_phase()) && (initial_params::mc_phase==0)) )
    {
      if(STD_Yr_Reverse_F(y)>0)
      {
        if(F_reporting<=1)
        {
          for(f=1;f<=Nfleet;f++) F_std(STD_Yr_Reverse_F(y))+=catch_fleet(t,f,2);   // add up dead catch biomass
          F_std(STD_Yr_Reverse_F(y))/=SmryBio(y);
        }
        else if(F_reporting==2)
        {
          for(f=1;f<=Nfleet;f++) F_std(STD_Yr_Reverse_F(y))+=catch_fleet(t,f,5);   // add up dead catch numbers
          F_std(STD_Yr_Reverse_F(y))/=SmryNum(y);
        }
        else if(F_reporting==3)
        {
          for(f=1;f<=Nfleet;f++)
          {
            F_std(STD_Yr_Reverse_F(y))+=Hrate(f,t)*seasdur(s);
          }
        }
      }
    }

    } //close season loop


//  calculate the SPR value for
    if( (save_for_report==1) || ((sd_phase() || mceval_phase()) && (initial_params::mc_phase==0)) )
    {
      eq_yr=y; equ_Recr=R0; bio_yr=y;
      Fishon=0;
      dvariable SPR_base;
      Do_Equil_Calc();                      //  call function to do equilibrium calculation
      SPR_base=Spbio_equil_sum;
      save_SPR(y,3)=value(SPR_base);
      save_SPR(y,5)=value(GenTime);
      Fishon=1;
      Do_Equil_Calc();                      //  call function to do equilibrium calculation
      if(STD_Yr_Reverse_Ofish(y)>0)
      {
        SPR_std(STD_Yr_Reverse_Ofish(y))=Spbio_equil_sum/SPR_base;
      }
      save_SPR(y,1)=value(totbio);
      save_SPR(y,2)=value(smrybio);
      save_SPR(y,4)=value(Spbio_equil_sum);
      save_SPR(y,6)=value(YPR_dead);
      for(g=1;g<=gmorph;g++)
      {
        save_SPR(y,6+g)=value(cumF(g));
        save_SPR(y,6+gmorph+g)=value(maxF(g));
      }
    }

  } //close year loop

// ******************************************************************
//  do tag mortality, movement and recapture     ProgLabel_195
  if(Do_TG>0)
  {
    dvariable TG_init_loss;
    dvariable TG_chron_loss;
    TG_recap_exp.initialize();
    for(TG=1;TG<=N_TG;TG++)
    {
      firstseas=int(TG_release(TG,4));  // release season
      t=int(TG_release(TG,5));  // release t index calculated in data section from year and season of release
      p=int(TG_release(TG,2));  // release area
      gg=int(TG_release(TG,6));  // gender (1=fem; 2=male; 0=both
      a1=int(TG_release(TG,7));  // age at release

      TG_alive.initialize();
      if(gg==0)
      {
        for (g=1;g<=gmorph;g++) {TG_alive(p,g) = natage(t,p,g,a1);}   //  gets both genders
      }
      else
      {
        for (g=1;g<=gmorph;g++)
        {
          if(sx(g)==gg) {TG_alive(p,g) = natage(t,p,g,a1);}  //  only does the selected gender
        }
      }
      TG_init_loss = mfexp(TG_parm(TG))/(1.+mfexp(TG_parm(TG)));
      TG_chron_loss = mfexp(TG_parm(TG+N_TG))/(1.+mfexp(TG_parm(TG+N_TG)));
      for(f=1;f<=Nfleet;f++)
      {
        k=3*N_TG+f;
        TG_report(f) = mfexp(TG_parm(k))/(1.0+mfexp(TG_parm(k)));
        TG_rep_decay(f) = TG_parm(k+Nfleet);
      }
      TG_alive /= sum(TG_alive);
      TG_alive *= TG_release(TG,8);
      TG_alive *= (1.-TG_init_loss);  // initial mortality
      if(save_for_report==1)
      {
        TG_save(TG,1)=value(TG_init_loss);
        TG_save(TG,2)=value(TG_chron_loss);
      }

      TG_t=0;
      for(y=TG_release(TG,3);y<=endyr;y++)
      {
        for(s=firstseas;s<=nseas;s++)
        {
          if(save_for_report==1 && TG_t<=TG_endtime(TG))
          {TG_save(TG,3+TG_t)=value(sum(TG_alive));} //  OK to do simple sum because only selected morphs are populated

          for(p=1;p<=pop;p++)
          {
            for (g=1;g<=gmorph;g++)
            if(TG_use_morph(TG,g)>0)
            {
              for (f=1;f<=Nfleet;f++)       //loop over fishing fleets       ProgLabel_105
              if (fleet_area(f)==p)
              {
// calculate recaptures by fleet
// NOTE:  Sel_for_tag(t,g,f,a1) = sel_al_4(s,g,f,a1)*Hrate(f,t)
                if(F_Method==1)
                {
                  TG_recap_exp(TG,TG_t,f)+=TG_alive(p,g)  // tags recaptured
                  *mfexp(-(natM(s,GP3(g),a1)+TG_chron_loss*seasdur2(s)))
                  *Sel_for_tag(t,g,f,a1)
                  *TG_report(f)
                  *mfexp(TG_t*TG_rep_decay(f));
                }
                else   // use for method 2 and 3
                {
                  TG_recap_exp(TG,TG_t,f)+=TG_alive(p,g)
                  *Sel_for_tag(t,g,f,a1)/(Z_rate(t,p,g,a1)+TG_chron_loss)
                  *(1.-mfexp(-seasdur(s)*(Z_rate(t,p,g,a1)+TG_chron_loss)))
                  *TG_report(f)
                  *mfexp(TG_t*TG_rep_decay(f));
                }
              }  // end fleet loop for recaptures

// calculate survival
              if(F_Method==1)
              {
                if(s==nseas) {k=1;} else {k=0;}   //      advance age or not
                if((a1+k)<=(nages-1)) {f=a1-1;} else {f=nages-2;}
                TG_alive(p,g)*=natage(t+1,p,g,f+k)/natage(t,p,g,f)*(1.-TG_chron_loss*seasdur(s));
              }
              else   //  use for method 2 and 3
              {
                TG_alive(p,g)*=mfexp(-seasdur(s)*(Z_rate(t,p,g,a1)+TG_chron_loss));
              }
            }  // end morph loop
          }  // end area loop

          if(do_migration>0)
          {
            TG_alive_temp=TG_alive;
            TG_alive=0.0;
            for (g=1;g<=gmorph;g++)
            if(use_morph(g)>0)
            {
            for (p=1;p<=pop;p++)  //   source population
            for (p2=1;p2<=pop;p2++)  //  destination population
            {
             k=move_pattern(s,GP4(g),p,p2);
             if(k>0) TG_alive(p2,g) += TG_alive_temp(p,g)*migrrate(y,k,a1);
            }
          }
          }
          t++;         //  increment seasonal time counter
          if(TG_t<TG_endtime(TG)) TG_t++;
          if(s==nseas && a1<nages) a1++;
        }  // end seasons
        firstseas=1;  // so start with season 1 in year following the tag release
      }  // end years
    }  //  end loop of tag groups
  }  // end having tag groups

//*************************************************************************************************************************************
//  ProgLabel_7900_FUNCTION evaluate_the_objective_function
FUNCTION evaluate_the_objective_function

  surv_like.initialize();   Q_dev_like.initialize(); disc_like.initialize();   length_like.initialize(); age_like.initialize();
  sizeage_like.initialize(); parm_like.initialize(); parm_dev_like.initialize(); log_q_cr.initialize();
  mnwt_like.initialize(); equ_catch_like.initialize(); prior_rec.initialize(); prior_fore_rec.initialize();
  catch_like.initialize(); Morphcomp_like.initialize(); TG_like1.initialize(); TG_like2.initialize();
  obj_fun=0.0;

    int k_phase=current_phase();
    if(k_phase>max_lambda_phase) k_phase=max_lambda_phase;


// Fit to indices (lognormal)                       ProgLabel_210
    if(nobs>0)
    {
    for(f=1;f<=Ntypes;f++)
    if(surv_lambda(f,k_phase)>0.0 || save_for_report==1)      // skip if zero emphasis
      {
      if(nyr_cr(f)>0)
        {
        if(Q_setup(f,3)>0)
          {sd_cr(f)=cv_cr(f) + Q_parm(Q_setup_parms(f,3));}
        else
          {sd_cr(f) = cv_cr(f);}
        for(j=1;j<=N_supyr_cr(f);j++)                  // do super years  Max of 20 allowed per type(f)
          {temp=0.0; temp1=0.0;
          for(i=supyr_cr1(f,j);i<=supyr_cr2(f,j);i++) {temp+=exp_cr(f,i); temp1+=1.;} // combine across range of observations
          temp/=temp1;                                        // average
          for(i=supyr_cr1(f,j);i<=supyr_cr2(f,j);i++) {exp_cr(f,i)=temp;}   // assign back to each original obs  note that these are in log-space
          }
        if(Q_setup(f,4)==0 || Q_setup(f,4)==1)   // do float option=automatic scaling      // ProgLabel_211
          {
          temp=0.; temp1=0.; temp2=0.;
          for (i=1;i<=nyr_cr(f);i++)
            {
            if(obs_cr(f,i) > 0.0)
              {
              temp2 += (Ln_obs_cr(f,i)-exp_cr(f,i))/square(sd_cr(f,i));     //  exp_cr is already in log-space
              temp += 1.0/square(sd_cr(f,i));
              temp1 += 1.;
              }
            }
          if(Q_setup(f,4)==0)                               // median unbiased
            {log_q_cr(f) = temp2/temp;}
          else                  // for value = 1        // mean unbiased
            {log_q_cr(f) = (temp2 + temp1*0.5)/temp;}
          }
        else if(Q_setup(f,4)<=-1)        // mirror Q from lower numbered survey
                                         // because Q is a vector for each observation, the mirror is to the first observation's Q
                                         // so time-varying property cannot be mirrored
          {
            log_q_cr(f) = log_q_cr(-Q_setup(f,4),1);
          }
        else
          {                                               //  Q from parameter
          log_q_cr(f) = Q_parm(Q_setup_parms(f,4));   // base Q
          if(Q_setup(f,4)>=3)
            {
            temp=0.0; temp2=0.0; temp1=0.;
            if(Q_setup(f,4)==3)  // random devs
              {
              for(i=1;i<=nyr_cr(f);i++)
                {
                j=Q_setup_parms(f,4)+i;
                log_q_cr(f,i)+=Q_parm(j);
                if(obs_cr(f,i)>0) {temp+=Q_parm(j); temp2+=square(Q_parm(j)); temp1+=1.;}
                }
              }
            else if(Q_setup(f,4)==4)   // random walk
              {
              for(i=2;i<=nyr_cr(f);i++)
                {
                j=Q_setup_parms(f,4)+i-1;
                log_q_cr(f,i)=log_q_cr(f,i-1)+Q_parm(j);
                if(obs_cr(f,i)>0) {temp+=Q_parm(j); temp2+=square(Q_parm(j)); temp1+=1.;}
                }
              }
            Q_dev_like(f,1)=square(1.+square(temp))-1.;
            if(temp1>0.0) Q_dev_like(f,2)=sqrt((temp2+0.0000001)/temp1);
            }

          if(Q_setup(f,2)>0)    // environ effect on log(q)
            {
            for(i=1;i<=nyr_cr(f);i++)
              {
              log_q_cr(f,i) += Q_parm(Q_setup_parms(f,2)) * env_data(yr_cr_y(f,i),Q_setup(f,2));  // note that this environ effect is after the dev effect!
              }
            }
          }

        if(Q_setup(f,6)==0)  // lognormal
          {
          for(i=1;i<=nyr_cr(f);i++)
          if(obs_cr(f,i)>0)
            {
            surv_like(f) +=0.5*square( ( Ln_obs_cr(f,i)-exp_cr(f,i)-log_q_cr(f,i) ) / sd_cr(f,i)) + sd_offset*log(sd_cr(f,i));
            }
          }
        else if (Q_setup(f,6)>0)        // t-distribution
          {
          dvariable df = Q_setup(f,6);
          for(i=1;i<=nyr_cr(f);i++)
          if(obs_cr(f,i)>0)
            {
            surv_like(f) +=((df+1.)/2.)*log((1.+square((Ln_obs_cr(f,i)-exp_cr(f,i)-log_q_cr(f,i) ))/(df*square(sd_cr(f,i))) )) + sd_offset*log(sd_cr(f,i));
            }
          }

        }    // end having obs for this survey
      }
     if(do_once==1) cout<<" did survey obj_fun "<<surv_like<<endl;
    }

// Fit to discard biomass (normal)               ProgLabel_215
    if(nobs_disc>0)
    {
    for(f=1;f<=Nfleet;f++)
    if(disc_lambda(f,k_phase)>0.0 || save_for_report==1)
    {
     if(nyr_disc(f)>0)
     {
     for(j=1;j<=N_supyr_disc(f);j++)                  // do super years  Max of 20 allowed per type(f)
       {temp=0.0; temp1=0.0;
     for(i=supyr_disc1(f,j);i<=supyr_disc2(f,j);i++) {temp+=exp_disc(f,i); temp1+=1.;} // combine across range of observations
        temp/=temp1;                                        // average
        for(i=supyr_disc1(f,j);i<=supyr_disc2(f,j);i++) exp_disc(f,i)=temp;   // assign back to each original obs
       }
//  use T-dist with
      for (i=1;i<=nyr_disc(f);i++)
      if(obs_disc(f,i)>=0.0)
       {
//        disc_like(f) +=0.5*square( (obs_disc(f,i)-exp_disc(f,i)) / (cv_disc(f,i)*obs_disc(f,i))) + sd_offset*log(cv_disc(f,i)*obs_disc(f,i));
            disc_like(f) +=((DF_disc+1.)/2.)*log((1.+square(obs_disc(f,i)-exp_disc(f,i))/(DF_disc*square(sd_disc(f,i))) )) + sd_offset*log(sd_disc(f,i));
       }
     }
    }
    if(do_once==1) cout<<" did discard obj_fun "<<disc_like<<endl;
   }

// Fit to mean body wt (normal with student's T)
   if(nobs_mnwt>0)
   {
     for(i=1;i<=nobs_mnwt;i++)
     if(mnwtdata(5,i)>0.)
     {
       mnwt_like(mnwtdata(3,i)) +=0.5*(DF_bodywt+1.)*log(1.+square(mnwtdata(5,i)-exp_mnwt(i))/mnwtdata(8,i))+ mnwtdata(9,i);
     }
  if(do_once==1) cout<<" did meanwt obj_fun "<<mnwt_like<<endl;
   }

//Length comp likelihood (multinomial)        // ProgLabel_220
   if(nobsl>0)
   {
   for(f=1;f<=Ntypes;f++)
   if(length_lambda(f,k_phase)>0.0 || save_for_report==1)
    {
    if(nyr_l(f)>=1)
    {

     length_like(f) = -offset_l(f);

     for(j=1;j<=N_supyr_l(f);j++)                  // do super years  Max of 20 allowed per type(f)
       {exp_l_temp.initialize();
        for(i=supyr_l1(f,j);i<=supyr_l2(f,j);i++) exp_l_temp+=exp_l(f,i);  // combine across range of observations
        exp_l_temp/=sum(exp_l_temp);                                        // normalize
        for(i=supyr_l1(f,j);i<=supyr_l2(f,j);i++) exp_l(f,i)=exp_l_temp;   // assign back to each original obs
       }

     for(i=1;i<=nyr_l(f);i++)
     {
     if(gender==2)
     {
       if(gen_l(f,i)==0)                        // combined sex observation   ProgLabel_124
       {
         for(z=1;z<=nlen_bin;z++) {exp_l(f,i,z)+=exp_l(f,i,z+nlen_bin);}
         exp_l(f,i)(nlen_binP,nlen_bin2)=0.00;
       }
       else if(gen_l(f,i)==1)                   // female only
       {exp_l(f,i)(nlen_binP,nlen_bin2)=0.00;}
       else if(gen_l(f,i)==2)                   // male only
       {exp_l(f,i)(1,nlen_bin)=0.00;}
       else if(gen_l(f,i)==3 && CombGender_l>0)
       {
         for(z=1;z<=CombGender_l;z++)
         {exp_l(f,i,z)+=exp_l(f,i,z+nlen_bin);  exp_l(f,i,z+nlen_bin)=0.00;}
       }
     }
     exp_l(f,i) /= sum(exp_l(f,i));
     tails_w=ivector(tails_l(f,i));


        if(gen_l(f,i)!=2)                          // ProgLabel_126
        {
         if(tails_w(1)>1)
           {exp_l(f,i,tails_w(1))=sum(exp_l(f,i)(1,tails_w(1)));  exp_l(f,i)(1,tails_w(1)-1)=0.;}
         if(tails_w(2)<nlen_bin)
           {exp_l(f,i,tails_w(2))=sum(exp_l(f,i)(tails_w(2),nlen_bin));  exp_l(f,i)(tails_w(2)+1,nlen_bin)=0.;}
         exp_l(f,i)(tails_w(1),tails_w(2))+= min_comp;
        }

        if(gender==2 && gen_l(f,i)>=2)
        {
         if(tails_w(3)>nlen_binP)
           {exp_l(f,i,tails_w(3))=sum(exp_l(f,i)(nlen_binP,tails_w(3)));  exp_l(f,i)(nlen_binP,tails_w(3)-1)=0.;}
         if(tails_w(4)<nlen_bin2)
           {exp_l(f,i,tails_w(4))=sum(exp_l(f,i)(tails_w(4),nlen_bin2));  exp_l(f,i)(tails_w(4)+1,nlen_bin2)=0.;}
         exp_l(f,i)(tails_w(3),tails_w(4))+= min_comp;
        }
        exp_l(f,i) /= sum(exp_l(f,i));

     if(nsamp_l(f,i)>0)
   {
   if(gen_l(f,i) !=2) length_like(f) -= nsamp_l(f,i) *
     obs_l(f,i)(tails_w(1),tails_w(2)) * log(exp_l(f,i)(tails_w(1),tails_w(2)));
   if(gen_l(f,i) >=2) length_like(f) -= nsamp_l(f,i) *
     obs_l(f,i)(tails_w(3),tails_w(4)) * log(exp_l(f,i)(tails_w(3),tails_w(4)));
     }
     }
     }
   }
  if(do_once==1) cout<<" did lencomp obj_fun "<<length_like<<endl;
   }

// age comp likelihood (multinomial)        // ProgLabel_230
  if(nobsa>0)
  {
    for(f=1;f<=Ntypes;f++)
    if(age_lambda(f,k_phase)>0.0 || save_for_report==1)
    {
      if(nyr_a(f)>=1)
      {
        age_like(f) = -offset_a(f);

        for(j=1;j<=N_supyr_a(f);j++)                  // do super years  Max of 20 allowed per type(f)
        {
          exp_a_temp.initialize();
          for(i=supyr_a1(f,j);i<=supyr_a2(f,j);i++) exp_a_temp+=exp_a(f,i);  // combine across range of observations
          exp_a_temp/=(1.0e-15+sum(exp_a_temp));                                        // normalize
          for(i=supyr_a1(f,j);i<=supyr_a2(f,j);i++) exp_a(f,i)=exp_a_temp;   // assign back to each original obs
        }

        for(i=1;i<=nyr_a(f);i++)
        {
          if(gender==2)
          {
            if(gen_a(f,i)==0)                         // combined sex observation
            {
              for(z=1;z<=n_abins;z++) {exp_a(f,i,z)+=exp_a(f,i,z+n_abins);}
              exp_a(f,i)(n_abins1,n_abins2)=0.00;
            }
            else if(gen_a(f,i)==1)                   // female only
            {exp_a(f,i)(n_abins1,n_abins2)=0.00;}
            else if(gen_a(f,i)==2)                   // male only
            {exp_a(f,i)(1,n_abins)=0.00;}
            else if(gen_a(f,i)==3 && CombGender_a>0)
            {
              for(z=1;z<=CombGender_a;z++)
              {exp_a(f,i,z)+=exp_a(f,i,z+n_abins);  exp_a(f,i,z+n_abins)=0.00;}
            }
          }

          exp_a(f,i) /= (1.0e-15+sum(exp_a(f,i)));                      // proportion at binned age

          tails_w=ivector(tails_a(f,i));
          if(gen_a(f,i)!=2)
          {
            if(tails_w(1)>1)
            {exp_a(f,i,tails_w(1))=sum(exp_a(f,i)(1,tails_w(1)));  exp_a(f,i)(1,tails_w(1)-1)=0.;}
            if(tails_w(2)<n_abins)
            {exp_a(f,i,tails_w(2))=sum(exp_a(f,i)(tails_w(2),n_abins));  exp_a(f,i)(tails_w(2)+1,n_abins)=0.;}
            exp_a(f,i)(tails_w(1),tails_w(2))+= min_comp;
          }

          if(gender==2 && gen_a(f,i)>=2)
          {
            if(tails_w(3)>n_abins1)
            {exp_a(f,i,tails_w(3))=sum(exp_a(f,i)(n_abins1,tails_w(3)));  exp_a(f,i)(n_abins1,tails_w(3)-1)=0.;}
            if(tails_w(4)<n_abins2)
            {exp_a(f,i,tails_w(4))=sum(exp_a(f,i)(tails_w(4),n_abins2));  exp_a(f,i)(tails_w(4)+1,n_abins2)=0.;}
            exp_a(f,i)(tails_w(3),tails_w(4))+= min_comp;
          }

          exp_a(f,i) /= (1.0e-15+sum(exp_a(f,i)));

          if(nsamp_a(f,i)>0)
          {
            if(gen_a(f,i) !=2) age_like(f) -= nsamp_a(f,i) *
            obs_a(f,i)(tails_w(1),tails_w(2)) * log(exp_a(f,i)(tails_w(1),tails_w(2)));
            if(gen_a(f,i) >=2) age_like(f) -= nsamp_a(f,i) *
            obs_a(f,i)(tails_w(3),tails_w(4)) * log(exp_a(f,i)(tails_w(3),tails_w(4)));
          }
        }
      }
    }
    if(do_once==1) cout<<" did agecomp obj_fun "<<age_like<<endl;
  }

// size@age likelihood  (normal)      // ProgLabel_240
    if(nobs_ms>0)
    {
    for(f=1;f<=Ntypes;f++)
    if(nyr_ms(f)>0 && sizeage_lambda(f,k_phase)>0.0)
    {
     for(j=1;j<=N_supyr_ms(f);j++)                  // do super years  Max of 20 allowed per type(f)
       {exp_a_temp.initialize(); temp=0.;
     for(i=supyr_ms1(f,j);i<=supyr_ms2(f,j);i++) {exp_a_temp+=exp_ms(f,i); temp+=1.;} // combine across range of observations
        exp_a_temp/=temp;                                        // normalize
        for(i=supyr_ms1(f,j);i<=supyr_ms2(f,j);i++) exp_ms(f,i)=exp_a_temp;   // assign back to each original obs
       }

     for(i=1;i<=nyr_ms(f);i++)
       if(use_ms(f,i)>0)
         {
     for(b=1;b<=n_abins2;b++)
     if(obs_ms_n(f,i,b)>0 && obs_ms(f,i,b)>0)
     {
     sizeage_like(f) += 0.5*square((obs_ms(f,i,b) -exp_ms(f,i,b)) / (exp_ms_sq(f,i,b)/obs_ms_n(f,i,b)))
     + sd_offset*log(exp_ms_sq(f,i,b)/obs_ms_n(f,i,b));}
      }}
      if(do_once==1) cout<<" did meanlength obj_fun "<<sizeage_like<<endl;
     }


//  Weight Frequency likelihood
    if(WtFreq_Nmeth>0)       //  have some wtfreq data
    {
      WtFreq_like=WtFreq_like_base;  // initializes
      for(iobs=1;iobs<=WtFreq_totobs;iobs++)
      {
        k=WtFreq_obs_hdr(iobs,6);
        f=WtFreq_obs_hdr(iobs,3);
        z1=WtFreq_obs_hdr(iobs,7);
        z2=WtFreq_obs_hdr(iobs,8);
        if(k>0 && WtFreq_effN(iobs)>0.) WtFreq_like(WtFreq_use(f,k))-=WtFreq_effN(iobs)*WtFreq_obs(iobs)(z1,z2)*log(WtFreq_exp(iobs)(z1,z2));
      }
      if(do_once==1) cout<<" did wtfreq obj_fun "<<WtFreq_totobs<<" like "<<WtFreq_like<<endl;
    }

    if(Do_Morphcomp>0)
    {
      for(iobs=1;iobs<=Morphcomp_nobs;iobs++)
      {
        k=5+Morphcomp_nmorph;
        Morphcomp_exp(iobs)(6,k) /= sum(Morphcomp_exp(iobs)(6,k));
        Morphcomp_exp(iobs)(6,k) += Morphcomp_mincomp;
        Morphcomp_exp(iobs)(6,k) /= 1.+Morphcomp_mincomp*Morphcomp_nmorph;
        if(Morphcomp_obs(iobs,5)>0.) Morphcomp_like -= Morphcomp_obs(iobs,5)*Morphcomp_obs(iobs)(6,k) * log(elem_div(Morphcomp_exp(iobs)(6,k),Morphcomp_obs(iobs)(6,k)));
      }
    if(do_once==1) cout<<" did morphcomp obj_fun "<<Morphcomp_like<<endl;
    }

    if(Do_TG>0)
    {
      for(TG=1;TG<=N_TG;TG++)
      {
        overdisp=TG_parm(2*N_TG+TG);
        for(TG_t=TG_mixperiod;TG_t<=TG_endtime(TG);TG_t++)
        {
          TG_recap_exp(TG,TG_t)(1,Nfleet)+=1.0e-6;  // add a tiny amount
          TG_recap_exp(TG,TG_t,0) = sum(TG_recap_exp(TG,TG_t)(1,Nfleet));
          TG_recap_exp(TG,TG_t)(1,Nfleet)/=TG_recap_exp(TG,TG_t,0);
          if(Nfleet>1) TG_like1(TG)-=TG_recap_obs(TG,TG_t,0)* (TG_recap_exp(TG,TG_t)(1,Nfleet) * log(TG_recap_exp(TG,TG_t)(1,Nfleet)));
          TG_like2(TG)-=log_negbinomial_density(TG_recap_obs(TG,TG_t,0),TG_recap_exp(TG,TG_t,0),overdisp);
        }
      }
    if(do_once==1) cout<<" did tag obj_fun "<<TG_like1<<endl<<TG_like2<<endl;
    }

//  initial equilibrium catch  (lognormal)      // ProgLabel_250
    if(init_equ_lambda(k_phase)>0.0)
    {
      for(f=1;f<=Nfleet;f++)
      {
        if(obs_equ_catch(f)>0.0)
          {equ_catch_like += 0.5*square( (log(obs_equ_catch(f)) -log(est_equ_catch(f)+0.000001)) / catch_se(styr-1,f));}
      }
    if(do_once==1) cout<<" initequ_catch -log(L) "<<equ_catch_like<<endl;
    }

    if(F_Method>1)
      {for(f=1;f<=Nfleet;f++)
        if(catchunits(f)==1)
        {
      for(t=styr;t<=TimeMax;t++)
        {
        if(catch_ret_obs(f,t)>0.0)
          {
            catch_like(f) += 0.5*square( (log(catch_ret_obs(f,t)) -log(catch_fleet(t,f,3)+0.000001)) / catch_se(t,f));
          }
        }
      }
      else
        {
      for(t=styr;t<=TimeMax;t++)
        {
        if(catch_ret_obs(f,t)>0.0)
          {
            catch_like(f) += 0.5*square( (log(catch_ret_obs(f,t)) -log(catch_fleet(t,f,6)+0.000001)) / catch_se(t,f));
          }
        }
      }
      }

//The recruitment prior is assumed to be a lognormal pdf with expected
// value equal to the deterministic stock-recruitment curve          // ProgLabel_260
//  R1 deviation is weighted by ave_age because R1 represents a time series of recruitments
//  SR_parm(3) is sigmaR
//  SR_parm(6) is rho, the autocorrelation coefficient
//  POP code from Ianelli
//  if (rho>0)
//    for (i=styr_rec+1;i<=endyr;i++)
//      rec_like(1) += square((chi(i)- rho*chi(i-1)) /(sqrt(1.-rho*rho))) / (2.*sigmaRsq) + log(sigr);
//  else
//    rec_like(1)    = (norm2( chi +  sigmaRsq/2. ) / (2*sigmaRsq)) / (2.*sigmaRsq) + size_count(chi)*log(sigr);

    if(recrdev_lambda(k_phase)>0.0 && (do_recdev>0 || recdev_do_early>0) )
    {
      sigmasq=2.0*square(SR_parm(3));
      prior_rec = sd_offset_rec*log(SR_parm(3));
      // where sd_offset_rec takes account for the number of recruitment years fully estimated
      // this is calculated as the sum of the biasadj vector, so will be the same in MLE and MCMC mode
      // even though the biaasadj vector itself gets reset to be 1.0 throughout when in MCMC mode
      if(SR_autocorr==0)
      {
      prior_rec += norm2(recdev(recdev_first,recdev_end))/sigmasq;
      }
      else
      {
        rho=SR_parm(6);
        prior_rec += square(recdev(recdev_first))/sigmasq;
        for(y=recdev_first+1;y<=recdev_end;y++)
        {
          prior_rec += square(recdev(y)-rho*recdev(y-1)) / ((1.0-rho*rho)*sigmasq);
        }
      }
      ave_age = 1.0/natM(1,1,nages/2)-0.5;
      prior_rec += 0.5 * square( log(R1/R1_exp) / (SR_parm(3)/ave_age) );
      if(do_once==1) cout<<" did recruitdev obj_fun "<<prior_rec<<endl;
    }

    if(Do_Forecast>0)
    {
      if(recdev_end<endyr)
      {
        prior_fore_rec = fore_recr_lambda*(norm2(fore_recruitments(recdev_end+1,endyr)))/sigmasq;
//        prior_fore_rec += sd_offset_fore*log(SR_parm(3));  this is now part of the prior_recr logL calculated above
      }
      else
      {prior_fore_rec=0.0;}
//      prior_fore_rec += 0.5*norm2(fore_recruitments(endyr+1,endyr+N_Fore_Yrs))/(SR_parm(3)*SR_parm(3));
//      prior_fore_rec += sd_offset*size_count(fore_recruitments)*log(SR_parm(3));  // from SS2  test only
      prior_fore_rec += (norm2(fore_recruitments(endyr+1,YrMax)))/sigmasq;  // ss3
    }

//  ____________________________________________________
//  likelihood for the parameter priors  // ProgLabel_270
    dvariable mu; dvariable tau; dvariable Aprior; dvariable Bprior;
    int Ptype;
    dvariable Pconst;
    Pconst=0.0001;

    if(parm_prior_lambda(k_phase)>0.0 || Do_all_priors>0)
    {
      for(i=1;i<=N_MGparm2;i++)
      if(MGparm_PRtype(i)>-1 && (active(MGparm(i))|| Do_all_priors>0))
        {
        MGparm_Like(i)=Get_Prior(MGparm_PRtype(i), MGparm_LO(i), MGparm_HI(i), MGparm_PR(i), MGparm_CV(i), MGparm(i));
        parm_like+=MGparm_Like(i);
        }

      for(i=1;i<=Nfleet;i++)
      if(init_F_PRtype(i)>-1 && (active(init_F(i))|| Do_all_priors>0))
        {
        init_F_Like(i)=Get_Prior(init_F_PRtype(i), init_F_LO(i), init_F_HI(i), init_F_PR(i), init_F_CV(i), init_F(i));
        parm_like+=init_F_Like(i);
        }

      for(i=1;i<=Q_Npar;i++)
      if(Q_parm_1(i,5)>-1 && (active(Q_parm(i))|| Do_all_priors>0))
        {
        Q_parm_Like(i)=Get_Prior(Q_parm_1(i,5), Q_parm_1(i,1), Q_parm_1(i,2), Q_parm_1(i,4), Q_parm_1(i,6), Q_parm(i));
        parm_like+=Q_parm_Like(i);
        }

      for(i=1;i<=N_selparm2;i++)
      if(selparm_PRtype(i)>-1 && (active(selparm(i))|| Do_all_priors>0))
        {
        selparm_Like(i)=Get_Prior(selparm_PRtype(i), selparm_LO(i), selparm_HI(i), selparm_PR(i), selparm_CV(i), selparm(i));
        parm_like+=selparm_Like(i);
        }

    if(Do_TG>0)
    {
      k=3*N_TG+2*Nfleet;
      for(i=1;i<=k;i++)
      if(TG_parm2(i,5)>-1 && (active(TG_parm(i))|| Do_all_priors>0))
      {
        TG_parm_Like(i)=Get_Prior(TG_parm2(i,5), TG_parm_LO(i), TG_parm_HI(i), TG_parm2(i,4), TG_parm2(i,6), TG_parm(i));
        parm_like+=TG_parm_Like(i);
      }
    }

    for(i=1;i<=6;i++)
      if(SR_parm_1(i,5)>-1 && (active(SR_parm(i))|| Do_all_priors>0))
        {
        SR_parm_Like(i)=Get_Prior(SR_parm_1(i,5), SR_parm_1(i,1), SR_parm_1(i,2), SR_parm_1(i,4), SR_parm_1(i,6), SR_parm(i));
        parm_like+=SR_parm_Like(i);
        }
    }

//   likelihood for the random parameter time series  ProgLabel_280
    if(active(MGparm_dev) && parm_dev_lambda(k_phase)>0.0 )
    {
     for(i=1;i<=N_MGparm_dev;i++)
     for(j=MGparm_dev_minyr(i);j<=MGparm_dev_maxyr(i);j++)
     {parm_dev_like += 0.5*square( MGparm_dev(i,j) / MGparm_dev_stddev(i) );}
    }

    for(f=1;f<=Ntypes;f++)
      if(Q_setup(f,4)==3)
      {
      parm_dev_like += Q_dev_like(f,1); // mean component for dev approach (var component is already in the parm priors)
                                        //  do not include for randwalk (Qsetup==4)
      }

    if(active(selparm_dev) && parm_dev_lambda(k_phase)>0.0 )
    {
     for(i=1;i<=N_selparm_dev;i++)
     for(j=selparm_dev_minyr(i);j<=selparm_dev_maxyr(i);j++)
     {parm_dev_like += 0.5*square( selparm_dev(i,j) / selparm_dev_stddev(i) );}
    }

    if(F_ballpark_yr>0 && F_ballpark_lambda>0.)
      {
      temp=0.00001;
      for (s=1;s<=nseas;s++)
        {
        t = styr+(F_ballpark_yr-styr)*nseas+s-1;
        temp+=sum(column(Hrate,t));
        }
      F_ballpark_like = mfexp(sfabs( log(F_ballpark / temp)))-1.;
      F_ballpark_like = 10000.0*F_ballpark_like/(10000.+F_ballpark_like);
      }
    else
      {F_ballpark_like=0.0;}

//  *******************************************
//  Penalty for soft boundaries, uses the symettric beta prior code
  if(SoftBound>0)
  {
    SoftBoundPen=0.0;

      for(i=1;i<=N_selparm2;i++)
      if(active(selparm(i)))
        {SoftBoundPen+=Get_Prior(1, selparm_LO(i), selparm_HI(i), 1., 0.001, selparm(i));}

 /*
      for(i=1;i<=N_MGparm2;i++)
      if(active(MGparm(i)))
        {SoftBoundPen+=Get_Prior(1, MGparm_LO(i), MGparm_HI(i), 1., 0.001, MGparm(i));}

// for init_F, 0.0 is permissable value, so use artificial lower bound of -1
      for(i=1;i<=Nfleet;i++)
      if(active(init_F(i)))
        {SoftBoundPen+=Get_Prior(1, -1., init_F_HI(i), 1., 0.001, init_F(i));}

      for(i=1;i<=Q_Npar;i++)
      if(active(Q_parm(i)))
        {SoftBoundPen+=Get_Prior(1, Q_parm_1(i,1), Q_parm_1(i,2), 1., 0.001, Q_parm(i));}

    if(Do_TG>0)
    {
      k=3*N_TG+2*Nfleet;
      for(i=1;i<=k;i++)
      if(active(TG_parm(i)))
      {SoftBoundPen+=Get_Prior(1, TG_parm_LO(i), TG_parm_HI(i), 1., 0.001, TG_parm(i));}
    }

    for(i=1;i<=6;i++)
      if(active(SR_parm(i)))
        {SoftBoundPen+=Get_Prior(1, SR_parm_1(i,1), SR_parm_1(i,2), 1., 0.001, SR_parm(i));}

    if(active(MGparm_dev))
    {
     for(i=1;i<=N_MGparm_dev;i++)
     for(j=MGparm_dev_minyr(i);j<=MGparm_dev_maxyr(i);j++)
     {SoftBoundPen+=Get_Prior(1,-10.,10., 1., 0.001, MGparm_dev(i,j));}
    }

    if(active(selparm_dev))
    {
     for(i=1;i<=N_selparm_dev;i++)
     for(j=selparm_dev_minyr(i);j<=selparm_dev_maxyr(i);j++)
     {SoftBoundPen+=Get_Prior(1,-10.,10., 1., 0.001, selparm_dev(i,j));}
    }
 */
  }


//   CrashPen = square(1.0+CrashPen)-1.0;   this was used until V3.00L  7/10/2008
     CrashPen = square(1.0+ (1000.*CrashPen/(1000.+CrashPen)))-1.0;
//  sum the likelihood components weighted by lambda factors // ProgLabel_290
//   cout<<" obj_fun start "<<obj_fun<<endl;
   obj_fun = column(surv_lambda,k_phase)*surv_like;
//   cout<<" obj_fun surv "<<obj_fun<<surv_like<<endl;
   obj_fun += column(disc_lambda,k_phase)*disc_like;
//   cout<<" obj_fun disc "<<obj_fun<<endl;
   obj_fun += column(mnwt_lambda,k_phase)*mnwt_like;
//   cout<<" obj_fun mnwt "<<obj_fun<<endl;
   obj_fun += column(length_lambda,k_phase)*length_like;
//   cout<<" obj_fun len "<<obj_fun<<endl;
   obj_fun += column(age_lambda,k_phase)*age_like;
//   cout<<" obj_fun age "<<obj_fun<<endl;
   obj_fun += column(sizeage_lambda,k_phase)*sizeage_like;
//   cout<<" obj_fun ms "<<obj_fun<<endl;

   obj_fun += equ_catch_like*init_equ_lambda(k_phase);
//   cout<<" obj_fun equ_cat "<<obj_fun<<endl;
   obj_fun += column(catch_lambda,k_phase)*catch_like;
//   cout<<" obj_fun catch "<<obj_fun<<catch_like<<endl;
   obj_fun += prior_rec*recrdev_lambda(k_phase);
//   cout<<" obj_fun recr "<<obj_fun<<endl;
   obj_fun += parm_like*parm_prior_lambda(k_phase);
//   cout<<" obj_fun parm "<<obj_fun<<endl;
   obj_fun += parm_dev_like*parm_dev_lambda(k_phase);
//   cout<<" obj_fun parmdev "<<obj_fun<<endl;
   obj_fun += F_ballpark_like * F_ballpark_lambda;
//   cout<<" obj_fun Fball "<<obj_fun<<endl;
   obj_fun += CrashPen_lambda(k_phase)*CrashPen;
//   cout<<" obj_fun crash "<<obj_fun<<endl;
   obj_fun += square(dummy_datum-dummy_parm);
//   cout<<" obj_fun dummy "<<obj_fun<<endl;
   obj_fun += prior_fore_rec;  //  lambda already factored in
//   cout<<" obj_fun forerecr "<<obj_fun<<endl;
   obj_fun += SoftBoundPen;
//   cout<<" obj_fun soft "<<obj_fun<<endl;
   if(WtFreq_Nmeth>0)  obj_fun += WtFreq_like*column(WtFreq_lambda,k_phase);
   if(Do_Morphcomp>0) obj_fun += Morphcomp_lambda(k_phase)*Morphcomp_like;
   if(Do_TG>0 && Nfleet>1) obj_fun += TG_like1*column(TG_lambda1,k_phase);
   if(Do_TG>0) obj_fun += TG_like2*column(TG_lambda2,k_phase);
//   cout<<" obj_fun final "<<obj_fun<<endl;


FUNCTION Process_STDquant
  {
    cout<<" Process STD quant "<<endl;
      for(y=styr-2; y<=YrMax;y++)
      {
        if(STD_Yr_Reverse(y)>0)
        {
          spbio_std(STD_Yr_Reverse(y))=Spbio_tot(y);
          recr_std(STD_Yr_Reverse(y))=use_rec(y);
        }
        if(STD_Yr_Reverse_Dep(y)>0) {depletion(STD_Yr_Reverse_Dep(y))=Spbio_tot(y);}
      }

      switch(depletion_basis)
      {
        case 0:
        {
          depletion/=S0;
          break;
        }
        case 1:
        {
          depletion/= (depletion_level*S0);
          break;
        }
        case 2:
        {
          depletion/= (depletion_level*Bmsy);
          break;
        }
        case 3:
        {
          depletion/= (depletion_level*Spbio_tot(styr));
          break;
        }
      }

      switch (SPR_reporting)
      {
        case 0:      // keep as raw value
        {
          break;
        }
        case 1:  // compare to SPR
        {
//          SPR_std = (1.-SPR_std)/(1.-SPR_actual);
          SPR_std = (1.-SPR_std)/(1.-SPR_target);
          break;
        }
        case 2:  // compare to SPR_MSY
        {
          SPR_std = (1.-SPR_std)/(1.-SPR);
          break;
        }
        case 3:  // compare to SPR_Btarget
        {
          SPR_std = (1.-SPR_std)/(1.-SPR_Btgt);
          break;
        }
        case 4:
        {
          SPR_std = 1.-SPR_std;
          break;
        }
      }

//  init_int Do_Forecast   //  0=none; 1=F(SPR); 2=F(MSY) 3=F(Btgt); 4=F(endyr); 5=Ave F (enter yrs); 6=read Fmult
//  Use the selected F method for the forecast as the denominator for the F_std ratio
      switch (F_report_basis)
      {
        case 0:      // keep as raw value
        {
          break;
        }
        case 1:  // compare to SPR
        {
          F_std /= Mgmt_quant(4);
          break;
        }
        case 2:  // compare to SPR_MSY
        {
          F_std /= Mgmt_quant(5);
          break;
        }
        case 3:  // compare to SPR_Btarget
        {
          F_std /= Mgmt_quant(5);
          break;
        }
      }

  }
//  *******************************************************
FUNCTION dvariable Check_Parm(const double& Pmin, const double& Pmax, const double& jitter, const prevariable& Pval)
  {
    dvariable NewVal;
    dvariable temp;
    NewVal=Pval;
    if(Pval<Pmin)
    {N_warn++; warning<<" parameter init value is less than parameter min "<<Pval<<" < "<<Pmin<<endl; NewVal=Pmin;}
    if(Pval>Pmax)
    {N_warn++; warning<<" parameter init value is greater than parameter max "<<Pval<<" > "<<Pmax<<endl; NewVal=Pmax;}
    if(jitter>0.0)
    {
      temp=log((Pmax-Pmin+0.0000002)/(NewVal-Pmin+0.0000001)-1.)/(-2.);   // transform the parameter
      temp += randn(radm) * jitter;
      NewVal=Pmin+(Pmax-Pmin)/(1.+mfexp(-2.*temp));
    }
    return NewVal;
  }


//  *******************************************************
FUNCTION dvariable Get_Prior(const int T, const double& Pmin, const double& Pmax, const double& Pr, const double& Psd, const prevariable& Pval)
  {
    dvariable Prior_Like;
    dvariable mu;
    dvariable tau;
    dvariable Pconst=0.0001;
    dvariable Bprior;
    dvariable Aprior;
    switch (T)
    {
      case -1:
        {
        Prior_Like = 0.;
        break;
        }
      case 0: // normal
        {
        Prior_Like = 0.5*square((Pval-Pr)/Psd);
        break;
        }
      case 1:  // symmetric beta    value of Psd must be >0.0
        {
        mu=-(Psd*(log( (Pmax+Pmin)*0.5- Pmin)))- (Psd*(log(0.5)));
        Prior_Like = -(mu+ (Psd*(log(Pval-Pmin+Pconst)))+(Psd*(log(1.-((Pval-Pmin-Pconst)/(Pmax-Pmin))))));
        break;
        }
      case 2:  // CASAL's Beta;  check to be sure that Aprior and Bprior are OK before running SS2!
        {
        mu=(Pr-Pmin) / (Pmax-Pmin);  // CASAL's v
        tau=(Pr-Pmin)*(Pmax-Pr)/square(Psd)-1.0;
        Bprior=tau*mu;  Aprior=tau*(1-mu);  // CASAL's m and n
        if(Bprior<=1.0 || Aprior <=1.0) {cout<<" bad Beta prior "<<endl;exit(1);}
        Prior_Like =  (1.0-Bprior)*log(Pconst+Pval-Pmin) + (1.0-Aprior)*log(Pconst+Pmax-Pval)
              -(1.0-Bprior)*log(Pconst+Pr-Pmin) - (1.0-Aprior)*log(Pconst+Pmax-Pr);
        break;
        }
    }
    return Prior_Like;
  }

//********************************************************************************************************
//  ProgLabel_8000_FUNCTION   Do_Equil_Calc
FUNCTION Do_Equil_Calc

  int t_base;
  int bio_t_base;
  int bio_t;
  int s_start;
  dvariable N_mid;
  dvariable N_beg;
  dvariable Fishery_Survival;
  dvariable crashtemp;
  dvariable crashtemp1;

   t_base=styr+(eq_yr-styr)*nseas-1;
   bio_t_base=styr+(bio_yr-styr)*nseas-1;
   GenTime.initialize(); Equ_penalty.initialize();
   cumF.initialize(); maxF.initialize();
   Spbio_equil.initialize();
   equ_catch_fleet.initialize();
   equ_F_std=0.0;
   totbio=0.0;
   smrybio=0.0;
   smrynum=0.0;
   for (g=1;g<=gmorph;g++)
   if(use_morph(g)>0)
   {
     gg=sx(g);    // gender
     for(s=1;s<=nseas;s++)
     if(s==Bseas(g))
     {
       for(p=1;p<=pop;p++)
       {equ_numbers(s,p,g,0) = equ_Recr*recr_dist(GP(g),s,p)*submorphdist(GP2(g));}   // get the age 0 recruits for season=recr_seas
     }

     for (a=0;a<=nages*3-1;a++)     // go to 3x nages to approximate the infinite tail
     {
       if(a<=nages) {a1=a;} else {a1=nages;}    // because selex and biology max out at nages
       if(a>0)
         {s_start=1;}
       else
         {s_start=Bseas(g);} //recr_seas(g);}

       for (s=s_start;s<=nseas;s++)
       {
         t=t_base+s;
         bio_t=bio_t_base+s;
         Nmigr.initialize();                                //  zero out the migrant container
         for (p=1;p<=pop;p++)
         {
           N_beg=equ_numbers(s,p,g,a);          // initial numbers at age (but using Nmid as container)
           equ_Z(s,p,g,a1)=natM(s,GP3(g),a1);

           if(F_Method==1)   // Pope's approx
             {
               N_mid = N_beg*surv1(s,GP3(g),a1);     // numbers at middle of season
               Nsurvive=N_mid;                            // initial number of fishery survivors
               if(Fishon==1)
               {                       //  remove catch this round
               // check to see if total harves would exceed max_harvest_rate
               crashtemp=0.;  harvest_rate=1.0;
                 for (f=1;f<=Nfleet;f++)
                 if (fleet_area(f)==p && Hrate(f,t)>0.)
                   {
                   crashtemp+=Hrate(f,t)*deadfish(s,g,f,a1);
                   }
//                 crashtemp1=max_harvest_rate-crashtemp;              // goes negative if over the max_harvest_rate
//                 temp=posfun(crashtemp1,0.00000,Equ_penalty);         // retains delta or creates a penalty for being over
//                 harvest_rate=(max_harvest_rate-temp)/(crashtemp+1.0e-30);

                   if(crashtemp>0.20)                  // only worry about this if the exploit rate is at all high
                     {
                     join1=1./(1.+mfexp(40.0*(crashtemp-max_harvest_rate)));  // steep joiner logistic curve at limit
                     upselex=1./(1.+mfexp(Equ_F_joiner*(crashtemp-0.2)));          //  value of a shallow logistic curve that goes through the limit
//                     crashtemp1=crashtemp*join1+(1.-join1)*upselex;       // combination of initial calc and the shallow
                     harvest_rate = join1 + (1.-join1)*upselex/(crashtemp);      // ratio by which all Hrates will be adjusted
                     }

//                 crashtemp1=0.9999-crashtemp;              // goes negative if over the max_harvest_rate
//                 temp=posfun(crashtemp1,0.00000,Equ_penalty);         // retains delta or creates a penalty for being over
//                 harvest_rate=(0.9999-temp)/(crashtemp+1.0e-30);
//                if(crashtemp1<0.0 && rundetail==2) {cout<<a<<" crash in equil "<<crashtemp<<" "<<crashtemp1<<" "<<Equ_penalty<<" "<<harvest_rate<<endl;}

                 for (f=1;f<=Nfleet;f++)
                 if (fleet_area(f)==p && Hrate(f,t)>0.)
                 {
                   temp=N_mid*Hrate(f,t)*harvest_rate;     // numbers that would be caught if fully selected
                   Nsurvive-=temp*deadfish(s,g,f,a1);       //  survival from fishery kill
                     equ_catch_fleet(f,2) += temp*deadfish_B(s,g,f,a1);
                     equ_catch_fleet(f,5) += temp*deadfish(s,g,f,a1);
                     equ_catch_fleet(f,3) += temp*sel_al_2(s,g,f,a1);      // retained fishery kill in biomass

                 if(save_for_report==1)
                   {
                   if(catchunits(f)==1)
                   {
                     equ_catch_fleet(f,1)+=temp*sel_al_1(s,g,f,a1);      //  total fishery encounter in biomass
                   }
                   else
                   {
                     equ_catch_fleet(f,4)+=temp*sel_al_3(s,g,f,a1);    // total fishery encounter in numbers
                     equ_catch_fleet(f,6)+=temp*sel_al_4(s,g,f,a1);      // retained fishery kill in numbers
                   }
                     equ_catage(s,f,g,a1)+=temp*deadfish(s,g,f,a1);      //  dead catch numbers per recruit  (later accumulate N in a1)
                   }
                 }
               }   // end removing catch

               Fishery_Survival = -log((Nsurvive+1.0e-23)/(N_mid+1.0e-20));
               if(a>=Smry_Age && a<=nages) cumF(g)+=Fishery_Survival;
               if(Fishery_Survival/seasdur(s)>maxF(g)) maxF(g)=Fishery_Survival/seasdur(s);

               Nsurvive *= surv1(s,GP3(g),a1);  // decay to end of season
               }   // end Pope's approx

             else          // Continuous F for method 2 or 3
             {
               if(Fishon==1)
               {
                 if(a1<=nages)
                 {
                   for (f=1;f<=Nfleet;f++)       //loop over fishing fleets to get Z
                   if (fleet_area(f)==p && Hrate(f,t)>0.0)
                   {
                     equ_Z(s,p,g,a1)+=deadfish(s,g,f,a1)*Hrate(f,t);
                   }
                   if(save_for_report==1)
                   {
                     temp=equ_Z(s,p,g,a1)-natM(s,GP3(g),a1);
                     if(a>=Smry_Age) cumF(g)+=temp;
                     if(temp>maxF(g)) maxF(g)=temp;
                   }
                 }
               }
               Nsurvive=N_beg*mfexp(-seasdur(s)*equ_Z(s,p,g,a1));
             }  //  end F method

           int jj;
           if(do_migration==0)
           {Nmigr(p) = Nsurvive;}
           else
           {
             for(p2=1;p2<=pop;p2++)
             {
             	 jj=move_pattern(s,GP4(g),p,p2);
               if(jj>0) Nmigr(p2) += Nsurvive*migrrate(bio_yr,jj,a1);
             }  // end destination pop
           }  // end do migration
         }  // end pop

         if(s==nseas) {k=a+1; s2=1;} else {k=a;s2=s+1;}
         for(p=1;p<=pop;p++) {equ_numbers(s2,p,g,k) = Nmigr(p);}    // move migrants into correct age according to season
       }  // end season
     }  // end age

// now calc contribution to catch
       for(s=1;s<=nseas;s++)
       for(p=1;p<=pop;p++)
       {
         t=t_base+s;
         bio_t=bio_t_base+s;
         equ_numbers(s,p,g,nages)=sum(equ_numbers(s,p,g)(nages,3*nages));
         if(Fishon==1)
         {
           if(F_Method>=2)
           {
             Zrate2(g)=elem_div( (1.-mfexp(-seasdur(s)*equ_Z(s,p,g))), equ_Z(s,p,g));
             if(s<Bseas(g)) Zrate2(g,0)=0.0;
             for (f=1;f<=Nfleet;f++)
             if (fleet_area(f)==p && Hrate(f,t)>0.0)
             {
               equ_catch_fleet(f,2)+=Hrate(f,t)*elem_prod(equ_numbers(s,p,g)(0,nages),deadfish_B(s,g,f))*Zrate2(g);      // dead catch bio
               equ_catch_fleet(f,5)+=Hrate(f,t)*elem_prod(equ_numbers(s,p,g)(0,nages),deadfish(s,g,f))*Zrate2(g);      // deadfish catch numbers
               equ_catch_fleet(f,3)+=Hrate(f,t)*elem_prod(equ_numbers(s,p,g)(0,nages),sel_al_2(s,g,f))*Zrate2(g);      // retained catch bio
               if(save_for_report==1)
               {
                 equ_catage(s,f,g)=elem_prod(elem_prod(equ_numbers(s,p,g)(0,nages),deadfish(s,g,f)) , Zrate2(g));
                 equ_catch_fleet(f,1)+=Hrate(f,t)*elem_prod(equ_numbers(s,p,g)(0,nages),sel_al_1(s,g,f))*Zrate2(g);      // encountered catch bio
                 equ_catch_fleet(f,4)+=Hrate(f,t)*elem_prod(equ_numbers(s,p,g)(0,nages),sel_al_3(s,g,f))*Zrate2(g);      // encountered catch bio
                 equ_catch_fleet(f,6)+=Hrate(f,t)*elem_prod(equ_numbers(s,p,g)(0,nages),sel_al_4(s,g,f))*Zrate2(g);      // retained catch numbers
               }
             }
           }
           else  // F_method=1
           {
             // already done in the age loop
           }
         }

         if(s==1)
         {
           totbio += equ_numbers(s,p,g)(0,nages)*Wt_Age_beg(s,g)(0,nages);
           smrybio += equ_numbers(s,p,g)(Smry_Age,nages)*Wt_Age_beg(s,g)(Smry_Age,nages);
           smrynum += sum(equ_numbers(s,p,g)(Smry_Age,nages));
         }
         if(s==spawn_seas && gg==1)
         {
           Spbio_equil(p,GP4(g))+=equ_numbers(s,p,g)(0,nages)*fec(g);
           GenTime+=equ_numbers(s,p,g)(0,nages)*elem_prod(fec(g),r_ages);
         }
       }
   } // end morph

     YPR_dead = sum(column(equ_catch_fleet,2));           // dead yield per recruit
     YPR_N_dead = sum(column(equ_catch_fleet,5));           // dead numbers per recruit
     YPR_enc = sum(column(equ_catch_fleet,1));               //  encountered yield per recruit
     YPR_ret = sum(column(equ_catch_fleet,3));           // retained yield per recruit

   if(Fishon==1)
   {
   if(F_reporting<=1)
   {
     equ_F_std=YPR_dead/smrybio;
   }
   else if(F_reporting==2)
   {
     equ_F_std=YPR_N_dead/smrynum;
   }
   else if(F_reporting==3)
   {
     for(s=1;s<=nseas;s++)
     {
       t=t_base+s;
       for (f=1;f<=Nfleet;f++)
       {
         equ_F_std+=Hrate(f,t)*seasdur(s);
       }
     }
   }
   }
   Spbio_equil_sum=sum(Spbio_equil);  GenTime/=Spbio_equil_sum; cumF/=(nages-Smry_Age+1.);

// **********************************************************************************************
// ProgLabel_8100_FUNCTION Make_AgeLength_Key
FUNCTION Make_AgeLength_Key
  dvar_vector templen(2,nlength);
  dvar_vector AL(1,nlength1);
  dvar_vector use_Ave_Size_W(0,nages);
  AL(1)=0.0; AL(nlength1)=1.0;
  int gstart;
  int gpattern;
  int sex;
   smid=s+nseas;
   if(y>endyr) {yz=endyr;} else {yz=y;}
   gp=0;
    for(sex=1;sex<=gender;sex++)
    for(gpattern=1;gpattern<=N_GP;gpattern++)
    {
    gp=gp+1;
    gstart=(gp-1)*nseas*N_GP_sub+int(N_GP_sub/2)+1-N_GP_sub;
    for(birthseas=1;birthseas<=nseas;birthseas++)
      {
      gstart+=N_GP_sub;
      if(recr_dist_pattern_2(gpattern,birthseas)>0)
        {
      for(gp2=1;gp2<=N_GP_sub;gp2++)      // loop the sub-morphs
        {
        g=gstart+ishadow(gp2);
        use_Ave_Size_W=Use_Ave_Size(s,gstart);
        if(N_GP_sub>1) use_Ave_Size_W += shadow(gp2)*Sd_Size_between(s,gstart);

        dvar_matrix ALK_w=ALK(s,g);        //  shallow copy
        gg=sx(g);
//        if((s==spawn_seas && gg==1) || save_for_report==1)   //  spawning season
        {
          for (a=0;a<=nages;a++)
          {
            templen=(len_bins(2,nlength)-use_Ave_Size_W(a))/(Sd_Size_within(s,gstart,a));
            for (z=2;z<=nlength;z++) {AL(z)= cumd_norm(templen(z));}
            ALK_w(a)=first_difference(AL);
          }   // end age loop
        }
        if(s==spawn_seas && gg==1)
        {
          if(Maturity_Option==4)
          {fec(g)=Age_Maturity(gp);}
          else
          {
            fec(g) = ALK_w*mat_len_wt;
            if(Maturity_Option==3)
            {fec(g) = elem_prod(fec(g),Age_Maturity(gp));}
            else
            {fec(g) = elem_prod(fec(g),mat_age);}
          }
        }
        {
          Wt_Age_beg(s,g)=(ALK_w*wt_len(s,gg));   // wt-at-age at beginning of period
          Save_Wt_Age(t,g)=Wt_Age_beg(s,g);
        }
        if(save_for_report==1)
        {
          Save_Ave_Size(t,0,g)=value(use_Ave_Size_W);
        }

        use_Ave_Size_W=extract_row(Use_Ave_Size(smid),gstart);
        if(N_GP_sub>1) use_Ave_Size_W += shadow(gp2)*Sd_Size_between(smid,gstart);
        if(save_for_report==1) {Save_Ave_Size(t,1,g)=value(use_Ave_Size_W);}

        for (a=0; a<=nages;a++)
          {
          templen=(len_bins(2,nlength)-use_Ave_Size_W(a))/(Sd_Size_within(smid,gstart,a));
          for (z=2;z<=nlength;z++) {AL(z)=cumd_norm(templen(z));}
          ALK_w(a)=first_difference(AL);
          Wt_Age_mid(s,g)=ALK_w*wt_len(s,gg);  // use for fisheries with no size selectivity
          }   // end age loop
        }  // end sub-morph loop
        }
      }   // end birthseason loop
    }  // end growth pattern&gender loop

//****************************************************************************
// ProgLabel_8200_FUNCTION  Make_FishSelex
FUNCTION Make_FishSelex
    dvar_matrix ALK_w=ALK(s,g);        //  shallow copy
    int yf;
    int tz;

    gg=sx(g);
    if(y>endyr) {yz=endyr; } else {yz=y;}
    if(y>endyr+1) {yf=endyr+1;} else {yf=y;}
    for(f=1;f<=Nfleet;f++)
    {
      if(time_vary_sel(yz,f+Ntypes)>0 || time_vary_sel(yz,f)>0 || time_vary_MG(yz,2)>0 || time_vary_MG(yz,3)>0)
      {
        if(seltype(f,1)==0)  // no size_slectivity
        {
          sel_al_1(s,g,f)=elem_prod(sel_a(yf,f,gg),Wt_Age_mid(s,g));
          sel_al_3(s,g,f)=sel_a(yf,f,gg);
        }
        else
        {
          sel_al_1(s,g,f)=elem_prod(sel_a(yf,f,gg),(ALK_w * elem_prod( sel_l(yf,f,gg),wt_len(s,gg) )) );
          sel_al_3(s,g,f)=elem_prod(sel_a(yf,f,gg),(ALK_w * sel_l(yf,f,gg) ));
        }
        if(mceval_phase() || save_for_report==1) fish_body_wt(s,g,f)=elem_div( ALK_w*elem_prod(sel_l(yf,f,gg),wt_len(s,gg)) , ALK_w*sel_l(yf,f,gg));
        if(seltype(f,2)!=0)
          {
          sel_al_2(s,g,f)=elem_prod(sel_a(yf,f,gg),(ALK_w * elem_prod( sel_l_r(yf,f,gg),wt_len(s,gg) )) );
          sel_al_4(s,g,f)=elem_prod(sel_a(yf,f,gg),(ALK_w * sel_l_r(yf,f,gg) ));
          }
        else
          {
            sel_al_2(s,g,f)=sel_al_1(s,g,f);
            sel_al_4(s,g,f)=sel_al_3(s,g,f);
          }
        if(seltype(f,2)>=2)
          {
          deadfish(s,g,f)=elem_prod(sel_a(yf,f,gg),(ALK_w * discmort2(yf,f,gg)));  //  selected dead by numbers
          deadfish_B(s,g,f)=elem_prod(sel_a(yf,f,gg),(ALK_w * elem_prod(discmort2(yf,f,gg),wt_len(s,gg)) )); // selected dead by weight
          }
        else
          {
            deadfish_B(s,g,f)=sel_al_1(s,g,f);
            deadfish(s,g,f)=sel_al_3(s,g,f);
          }

      }  // end need to do it
    }  // end fleet loop for mortality, retention

// ********************************************************************************************************
//  ProgLabel_8400_FUNCTION get_posteriors  (MCMC eval)
FUNCTION get_posteriors
  if(rundetail>0) cout<<" mceval counter: "<<mccounter<<endl;

  if(mccounter==1)    // first pass through the mceval phase
  {
    // delete any old mcmc output files
    // will generate a warning if no files exist
    // but will play through just fine
    system("del rebuild.SSO");
    system("del posteriors.rep");
    system("del derived_posteriors.rep");
    if(rundetail>0) cout<<" did system commands "<<endl;
  };
  // define the mcmc output files;
  ofstream rebuilder("rebuild.SSO",ios::app);
  ofstream posts("posteriors.rep",ios::app);
  ofstream der_posts("derived_posteriors.rep",ios::app);

  if(mccounter==1)    // first pass through the mceval phase
  {
    // produce the appropriate headers for the posteriors.rep
    // and derived_posteriors.rep files
    // parameters.rep matches "PARAMETERS" section in Report.SSO file
    if(rundetail>0) cout<<" write mcmc headers "<<endl;
    NP=0;   // counter for parameters index
    for(j=1;j<=N_MGparm2;j++)
    {
      NP++;  if(active(MGparm(j))) posts<<ParmLabel(NP)<<" ";
    }
    if(N_MGparm_dev>0)
    {
      for(i=1;i<=N_MGparm_dev;i++)
        for(j=MGparm_dev_minyr(i);j<=MGparm_dev_maxyr(i);j++)
        {
          NP++;  if(active(MGparm_dev)) posts<<ParmLabel(NP)<<" ";
        }
    }
    for(i=1;i<=6;i++)
    {
      NP++; if(active(SR_parm(i))) posts<<ParmLabel(NP)<<" ";
    }
    if(recdev_do_early>0)
    {
      for(i=recdev_early_start;i<=recdev_early_end;i++)
      {
        NP++;  if( active(recdev_early) ) posts<<ParmLabel(NP)<<" ";
      }
    }
    if(do_recdev>0)
    {
      for(i=recdev_start;i<=recdev_end;i++)
      {
        NP++;  if( active(recdev1)||active(recdev2) ) posts<<ParmLabel(NP)<<" ";
      }
    }
    if(Do_Forecast>0)
    {
      for(i=recdev_end+1;i<=YrMax;i++)
      {
        NP++; if(active(fore_recruitments)) posts<<ParmLabel(NP)<<" ";
      }
    }
    for(i=1;i<=Nfleet;i++)
    {
      NP++; if(active(init_F(i))) posts<<ParmLabel(NP)<<" ";
    }
    if(F_Method==2)
    {
      for(i=1;i<=Nfleet*(TimeMax-styr+1);i++)
      {
        NP++;  if(active(F_rate(i))) posts<<ParmLabel(NP)<<" ";
      }
    }
    for(i=1;i<=Q_Npar;i++)
    {
      NP++;  if(active(Q_parm(i))) posts<<ParmLabel(NP)<<" ";
    }
    for (j=1;j<=N_selparm2;j++)
    {
      NP++;  if(active(selparm(j))) posts<<ParmLabel(NP)<<" ";
    }
    for(i=1;i<=N_selparm_dev;i++)
      for(j=selparm_dev_minyr(i);j<=selparm_dev_maxyr(i);j++)
      {
        NP++;  if(active(selparm_dev)) posts<<ParmLabel(NP)<<" ";
      }
    if(Do_TG>0)
    {
      k=3*N_TG+2*Nfleet;
      for (j=1;j<=k;j++)
      {
        NP++;  if(active(TG_parm(j))) posts<<ParmLabel(NP)<<" ";
      }
    }
    posts << endl;  // include "endl" on last entry of a file

    // derived quantities
    // derived_parameters.rep matches "DERIVED_PARAMETERS" section in Report.SSO file
    der_posts<<"Objective_function ";
    for(j=1;j<=N_STD_Yr;j++) // spawning biomass
    {
      NP++;  der_posts<<ParmLabel(NP)<<" ";
    }
    for(j=1;j<=N_STD_Yr;j++) // recruitment
    {
      NP++;  der_posts<<ParmLabel(NP)<<" ";
    }
    for(j=1;j<=N_STD_Yr_Ofish;j++) // SPRratio
    {
      NP++;  der_posts<<ParmLabel(NP)<<" ";
    }
    for(j=1;j<=N_STD_Yr_F;j++) // F
    {
      NP++;  der_posts<<ParmLabel(NP)<<" ";
    }
    for(j=1;j<=N_STD_Yr_Dep;j++) // depletion (Bratio)
    {
      NP++;  der_posts<<ParmLabel(NP)<<" ";
    }
    for(j=1;j<=N_STD_mgmtquant;j++) // Management quantities
    {
      NP++;  der_posts<<ParmLabel(NP)<<" ";
    }
    for(j=1;j<=Extra_Std_N;j++) // Management quantities
    {
      NP++;  der_posts<<ParmLabel(NP)<<" ";
    }
    der_posts << endl;
  };  //  end writing headers for mccounter==1

  if(mccounter==1 || mccounter > burn_intvl) // check to see if burn in period is over
  {
    if(rundetail>0) cout<<" past burn-in"<<endl;
    // check to see if this draw is kept after thinning
    if(mccounter==1 || (double(mccounter)/double(thin_intvl)) - double((mccounter/thin_intvl))==0)
    {
      cout<<" MCEVAL "<<mccounter<<endl;
      // produce standard output of all estimated parameters
      NP=0;   // count of number of parameters
      for(j=1;j<=N_MGparm2;j++)
      {
        NP++;  if(active(MGparm(j))) posts<<MGparm(j)<<" ";
      }
      if(N_MGparm_dev>0)
      {
        for(i=1;i<=N_MGparm_dev;i++)
          for(j=MGparm_dev_minyr(i);j<=MGparm_dev_maxyr(i);j++)
          {
            NP++;  if(active(MGparm_dev)) posts<<MGparm_dev(i,j)<<" ";
          }
      }
      for(i=1;i<=6;i++)
      {
        NP++; if(active(SR_parm(i))) posts<<SR_parm(i)<<" ";
      }
      if(recdev_do_early>0)
      {
        for(i=recdev_early_start;i<=recdev_early_end;i++)
        {
          NP++;  if( active(recdev_early) ) posts<<recdev(i);
        }
      }
      if(do_recdev>0)
      {
        for(i=recdev_start;i<=recdev_end;i++)
        {
          NP++;  if( active(recdev1)||active(recdev2) ) posts<<recdev(i)<<" ";
        }
      }
      if(Do_Forecast>0)
      {
        for(i=recdev_end+1;i<=YrMax;i++)
        {
          NP++; if(active(fore_recruitments)) posts<<fore_recruitments(i)<<" ";
        }
      }
      for(i=1;i<=Nfleet;i++)
      {
        NP++; if(active(init_F(i))) posts<<init_F(i)<<" ";
      }
      if(F_Method==2)
      {
        for(i=1;i<=Nfleet*(TimeMax-styr+1);i++)
        {
          NP++;  if(active(F_rate(i))) posts<<F_rate(i)<<" ";
        }
      }
      for(i=1;i<=Q_Npar;i++)
      {
        NP++;  if(active(Q_parm(i)))posts<<Q_parm(i)<<" ";
      }
      for (j=1;j<=N_selparm2;j++)
      {
        NP++;  if(active(selparm(j))) posts<<selparm(j)<<" ";
      }
      for(i=1;i<=N_selparm_dev;i++)
        for(j=selparm_dev_minyr(i);j<=selparm_dev_maxyr(i);j++)
        {
          NP++;  if(active(selparm_dev)) posts<<selparm_dev(i,j)<<" ";
        }
      if(Do_TG>0)
      {
        k=3*N_TG+2*Nfleet;
        for (j=1;j<=k;j++)
        {
          NP++;  if(active(TG_parm(j))) posts<<TG_parm(j)<<" ";
        }
      }
      posts << endl;

      // derived quantities
      der_posts<<obj_fun<<" ";
      for(j=1;j<=N_STD_Yr;j++) // spawning biomass
      {
        NP++;  der_posts<<spbio_std(j)<<" ";
      }
      for(j=1;j<=N_STD_Yr;j++) // recruitment
      {
        NP++;  der_posts<<recr_std(j)<<" ";
      }
      for(j=1;j<=N_STD_Yr_Ofish;j++) // SPRratio
      {
        NP++;  der_posts<<SPR_std(j)<<" ";
      }
      for(j=1;j<=N_STD_Yr_F;j++) // F
      {
        NP++;  der_posts<<F_std(j)<<" ";
      }
      for(j=1;j<=N_STD_Yr_Dep;j++) // depletion (Bratio)
      {
        NP++;  der_posts<<depletion(j)<<" ";
      }
      for(j=1;j<=N_STD_mgmtquant;j++) // Management quantities
      {
        NP++;  der_posts<<Mgmt_quant(j)<<" ";
      }
      for(j=1;j<=Extra_Std_N;j++) // Management quantities
      {
        NP++;  der_posts<<Extra_Std(j)<<" ";
      }
      der_posts << endl;

      if(Do_Rebuilder>0) write_rebuilder_output();

    }; //end thin check
  }; // end burn check

  mccounter += 1;   // increment the counter


// ***************************************************************************************
//  ProgLabel_8600_FUNCTION Get_Benchmarks(); (Find Fspr, MSY)
FUNCTION Get_Benchmarks
  int jj;  int Nloops;
  int bio_t;
  dvariable last_F1;  dvariable Closer;
  dvariable Vbio1_unfished;
  dvariable SPBperREC_at_target;
  dvariable junk; dvariable Nmid_c;

  dvariable df;
  dvariable BestYield; dvariable BestF1;
  dvar_vector F1(1,3);
  dvariable FF;
  dvar_vector yld1(1,3);
  dvariable dyld;
  dvariable dyldp;
  dvar_vector tempvec_l(1,nlength);
  dvariable S1_trial;
  dvariable maxpossF;
  dvariable Fmax;
  dvariable bestF1;
  dvariable bestF2;

  show_MSY=0;
  if(mceval_phase()==0) {show_MSY=1;}

      maxpossF.initialize();
      for(g=1;g<=gmorph;g++)
        for(s=1;s<=nseas;s++)
        {
          tempvec.initialize();
          for(f=1;f<=Nfleet;f++) {tempvec+=ForeRatePattern(s,f)*deadfish(s,g,f);}
          temp=max(tempvec);
          if(temp>maxpossF) maxpossF=temp;
        }
        maxpossF =max_harvest_rate/maxpossF;    //  applies to any F_method

    if(SR_fxn==1 || SR_fxn==3)
      {
      alpha = 4.0 * SR_parm(2)*R0 / (5.*SR_parm(2)-1.);
      beta = (S0*(1.-SR_parm(2))) / (5.*SR_parm(2)-1.);
      }

//  calc average selectivity to use in equil and forecast; store in endyr+1
   for(gg=1;gg<=gender;gg++)
   for(f=1;f<=Nfleet;f++)
     {
     tempvec_l.initialize();
     for(y=Fore_Sel_yr1;y<=Fore_Sel_yr2;y++) {tempvec_l+=sel_l(y,f,gg);}
     sel_l(endyr+1,f,gg)=tempvec_l/(Fore_Sel_yr2-Fore_Sel_yr1+1);

     tempvec_l.initialize();
     for(y=Fore_Sel_yr1;y<=Fore_Sel_yr2;y++) {tempvec_l+=sel_l_r(y,f,gg);}
     sel_l_r(endyr+1,f,gg)=tempvec_l/(Fore_Sel_yr2-Fore_Sel_yr1+1);

     tempvec_l.initialize();
     for(y=Fore_Sel_yr1;y<=Fore_Sel_yr2;y++) {tempvec_l+=discmort2(y,f,gg);}
     discmort2(endyr+1,f,gg)=tempvec_l/(Fore_Sel_yr2-Fore_Sel_yr1+1);

     tempvec.initialize();
     for(y=Fore_Sel_yr1;y<=Fore_Sel_yr2;y++) {tempvec+=sel_a(y,f,gg);}
     sel_a(endyr+1,f,gg)=tempvec/(Fore_Sel_yr2-Fore_Sel_yr1+1);
     }

   y=endyr+1;
   for (s=1;s<=nseas;s++)
   for (g=1;g<=gmorph;g++)
   if(use_morph(g)>0)
     {Make_FishSelex();}

    yz=y;
    t_base=yz+(y-styr)*nseas-1;
    get_MGsetup();
    get_recr_distribution();

// find Fspr             ProgLabel_710
    if(show_MSY==1)
    {
    report5<<" & & & & & Fspr search"<<endl;
    report5<<"Iter Fmult SPR";
    for(p=1;p<=pop;p++)
    for(gp=1;gp<=N_GP;gp++)
    {report5<<" Area:"<<p<<"_GP:"<<gp;}
    report5<<endl;
    }
    Fmult=0.; Nloops=18; Closer=1.;
    F1(1)=log(1.0e-3); last_calc=0.; Fchange=-4.0;

    bio_yr=endyr;
    equ_Recr=1.0;
    eq_yr=endyr+1;

    Fishon=0;
    Do_Equil_Calc();
    S1(0)=Spbio_equil_sum;
    Vbio1_unfished=smrybio;       // gets value from equil_calc
          if(show_MSY==1)
          {
          report5<<0<<" "<<0.00<<" "<<1.0;
          for(p=1;p<=pop;p++)
          for(gp=1;gp<=N_GP;gp++)
          {report5<<" "<<Spbio_equil(p,gp);}
          report5<<endl;
          }


    df=1.e-5;
    Fishon=1;
    for(j=1;j<=Nloops;j++)   // loop find Fspr
    {
      if(fabs(Fchange)<=0.25)
        {
          jj=3;
          F1(2) = F1(1) + df*.5;
          F1(3) = F1(2) - df;
        }
      else
        {jj=1;}

      for(int ii=jj;ii>=1;ii--)
        {
          Fmult=mfexp(F1(ii));

          for(f=1;f<=Nfleet;f++)
          for(s=1;s<=nseas;s++)
            {t=styr+(endyr+1-styr)*nseas+s-1; Hrate(f,t)=Fmult*ForeRatePattern(s,f);}

          Fishon=1;
          Do_Equil_Calc();
          yld1(ii)=Spbio_equil_sum/S1(0);
        }
        S1_trial=Spbio_equil_sum;
        SPR_actual=yld1(1);

          if(jj==3)
            {
            Closer*=0.5;
              dyld=(yld1(2) - yld1(3))/df;                      // First derivative (to find the root of this)
//              if(dyld!=0. && Equ_penalty==0.00)
              if(dyld!=0.)
                {last_F1=F1(1); F1(1) += (SPR_target-SPR_actual)/dyld;
                 F1(1)=(1.-Closer)*F1(1)+Closer*last_F1;
                }        // averages with last good value to keep from changing too fast
              else
                {F1(1)=(F1(1)+last_F1)*0.5;}    // go halfway back towards previous value
            }
          else
            {
              if((last_calc-SPR_target)*(SPR_actual-SPR_target)<0.0) {Fchange*=-0.5;}   // changed sign, so reverse search direction
              F1(1)+=Fchange;  last_calc=SPR_actual;
            }

          if(show_MSY==1)
          {
          report5<<j<<" "<<Fmult<<" "<<SPR_actual;
          for(p=1;p<=pop;p++)
          for(gp=1;gp<=N_GP;gp++)
          {report5<<" "<<Spbio_equil(p,gp);}
          report5<<endl;
          }
    }   // end search loop

    if(fabs(SPR_actual-SPR_target)>=0.001)
    {N_warn++; warning<<" warning: poor convergence in Fspr search "<<SPR_target<<" "<<SPR_actual<<endl;}
    report5<<"catch_by_fleet_by_(encB,deadB,retB,encN,deadN,retN): "<<endl<<equ_catch_fleet<<endl;

          if(SR_fxn==1 || SR_fxn==3)
            {
             Bspr = alpha * S1_trial - beta;
             Bspr=posfun(Bspr,0.0001,temp);
             Bspr_rec =  (4.*SR_parm(2)*R0*Bspr) / (S0*(1.-SR_parm(2))+(5.*SR_parm(2)-1.)*Bspr); //Beverton-Holt
            }
          else if(SR_fxn==2)
            {
            Bspr=S0*(1.+(log(R0/S0)+log(S1_trial))/SR_parm(2));
            Bspr_rec = R0*Bspr/S0 * mfexp(SR_parm(2)*(1.-Bspr/S0)); // Ricker
            }
          else if(SR_fxn==4)   // constant; no bias correction
            {
            Bspr=S1_trial*R0;  Bspr_rec=R0;
            }
          else
            {Bspr_rec=0.;}


    YPR_tgt_enc  = YPR_enc;         //  total encountered yield per recruit
    YPR_tgt_dead = YPR_dead;           // total dead yield per recruit
    YPR_tgt_N_dead = YPR_N_dead;
    YPR_tgt_ret = YPR_ret;  SPR_Fmult=Fmult;
    if(rundetail>0) cout<<" got Fspr "<<SPR_Fmult<<" "<<SPR_actual<<endl;
    YPR_spr=YPR_tgt_dead; Vbio_spr=totbio; Vbio1_spr=smrybio;
    Mgmt_quant(4)=equ_F_std;
    if(show_MSY==1) {SPBperREC_at_target=S1_trial;}
//   end finding Fspr


// ******************************************************
//  find F giving Btarget      ProgLabel_720
    if(show_MSY==1) report5<<"+ + + + + + + + + findBtarget"<<endl<<"Iter Fmult SPR Catch SSB Recruits SSB/Bzero "<<endl;
    Nloops=18; F1(1)=log(1.0e-3); last_calc=0.; Fchange=-4.0; df=1.e-5; Closer=1.;

    Btgttgt=BTGT_target*S0;

    for(j=0;j<=Nloops;j++)   // loop find Btarget
      {
      if(fabs(Fchange)<=0.25)
        {
        jj=3;
        F1(2) = F1(1) + df*.5;
        F1(3) = F1(2) - df;
        }
      else
        {jj=1;}

      for(int ii=jj;ii>=1;ii--)
        {
        if(j==0) {Fmult=0.0;} else {Fmult=mfexp(F1(ii));}

        for(f=1;f<=Nfleet;f++)
        for(s=1;s<=nseas;s++)
          {t=styr+(endyr+1-styr)*nseas+s-1; Hrate(f,t)=Fmult*ForeRatePattern(s,f);}

        Do_Equil_Calc();
        S1_trial=Spbio_equil_sum;

        SPR_Btgt=S1_trial/S1(0);
        if(SR_fxn==1 || SR_fxn==3)
          {
           Btgt = alpha * S1_trial - beta;
           Btgt=posfun(Btgt,0.0001,temp);
           Btgt_Rec = (4.*SR_parm(2)*R0*Btgt) / (S0*(1.-SR_parm(2))+(5.*SR_parm(2)-1.)*Btgt); //Beverton-Holt
          }
        else if(SR_fxn==2)
          {
          Btgt=S0*(1.+(log(R0/S0)+log(S1_trial))/SR_parm(2));
          Btgt_Rec = R0*Btgt/S0 * mfexp(SR_parm(2)*(1.-Btgt/S0)); // Ricker
          }
        else if(SR_fxn==4)   // constant; no bias correction
          {
          Btgt=S1_trial*R0;  Btgt_Rec=R0;
          }
        else
          {Btgt_Rec=0.;}

        yld1(ii)=Btgt;
        }
      Btgt=yld1(1);

      if(jj==3)
        {
        Closer *=0.5;
        dyld=(yld1(2) - yld1(3))/df;                      // First derivative
//        if(dyld!=0. && Equ_penalty==0.00)
        if(dyld!=0.)
          {last_F1=F1(1); F1(1) -= (Btgt-Btgttgt)/dyld;
           F1(1)=(1.-Closer)*F1(1)+(Closer)*last_F1;
          }        // weighted average with last good value to keep from changing too fast
        else
          {F1(1)=(F1(1)+last_F1)*0.5;}    // go halfway back towards previous value
        }
      else
        {
          if((last_calc-Btgttgt)*(Btgt-Btgttgt)<0.0) {Fchange*=-0.5;}   // changed sign, so reverse search direction
          F1(1)+=Fchange;  last_calc=Btgt;
        }

      if(show_MSY==1) report5<<j<<" "<<Fmult<<" "<<SPR_Btgt<<" "<<YPR_dead*Btgt_Rec<<" "<<Btgt<<" "<<Btgt_Rec<<" "<<Btgt/S0<<endl;

      }   // end search loop
    if(fabs(log(Btgt/Btgttgt))>=0.001)
    {N_warn++; warning<<" warning: poor convergence in Btarget search "<<Btgttgt<<" "<<Btgt<<endl;}
    report5<<"catch_by_fleet_by_(encB,deadB,retB,encN,deadN,retN): "<<endl<<equ_catch_fleet*Btgt_Rec<<endl;
    Btgt_Fmult=Fmult;
    if(rundetail>0) cout<<" got_Btgt "<<Btgt_Fmult<<" "<<Btgt/S0<<endl;
    YPR_Btgt_enc  = YPR_enc;         //  total encountered yield per recruit
    YPR_Btgt_dead = YPR_dead;           // total dead yield per recruit
    YPR_Btgt_N_dead = YPR_N_dead;           // total dead yield per recruit
    YPR_Btgt_ret = YPR_ret;
    Vbio_Btgt=totbio; Vbio1_Btgt=smrybio;
    Mgmt_quant(6)=equ_F_std;

//  end finding F for Btarget

// ******************************************************
//  Do Btarget  profile
    if(show_MSY==1)
      {
        report5<<"+ + + + + + + + + Btarget profile"<<endl<<"Iter Fmult SPR Catch SSB Recruits SSB/Bzero YPR";
        for(f=1;f<=Nfleet;f++) {report5<<" catch:_"<<f;}
        for(p=1;p<=pop;p++)
        for(gp=1;gp<=N_GP;gp++)
        {report5<<" Area:"<<p<<"_GP:"<<gp;}
        report5<<endl;
        int SPRloop;
        dvariable Fmult2=value(maxpossF);
        dvariable Fmultchanger1 = value(pow(0.0001/Fmult2,0.05));
        dvariable Fmultchanger2 = value(Fmult2/19.);
        dvariable Btgt_prof;
        dvariable Btgt_prof_rec;

        for(int SPRloop1=1; SPRloop1<=3; SPRloop1++)
        {if(SPRloop1==3) Fmult2=value(Btgt_Fmult)/2.;
        for(SPRloop=1; SPRloop<=20; SPRloop++)
        {
          for(f=1;f<=Nfleet;f++)
          for(s=1;s<=nseas;s++)
            {t=styr+(endyr+1-styr)*nseas+s-1; Hrate(f,t)=Fmult2*ForeRatePattern(s,f);}

          Fishon=1;
          Do_Equil_Calc();
          S1_trial=value(Spbio_equil_sum);
          if(SR_fxn==1 || SR_fxn==3)
            {
             Btgt_prof = value(alpha * S1_trial - beta);
             Btgt_prof=posfun(Btgt_prof,0.0001,temp);
             Btgt_prof_rec = value((4.*SR_parm(2)*R0*Btgt_prof) / (S0*(1.-SR_parm(2))+(5.*SR_parm(2)-1.)*Btgt_prof)); //Beverton-Holt
            }
          else if(SR_fxn==2)
            {
            Btgt_prof=value(S0*(1.+(log(R0/S0)+log(S1_trial))/SR_parm(2)));
            Btgt_prof_rec = value(R0*Btgt_prof/S0 * mfexp(SR_parm(2)*(1.-Btgt_prof/S0))); // Ricker
            }
          else if(SR_fxn==4)   // constant; no bias correction
            {
            Btgt_prof=value(S1_trial*R0);  Btgt_prof_rec=value(R0);
            }
          else
            {Btgt_prof_rec=0.;}
          report5<<SPRloop<<" "<<Fmult2<<" "<<value(S1_trial/S1(0))<<" "<<value(YPR_dead*Btgt_prof_rec)<<" "<<Btgt_prof<<" "<<Btgt_prof_rec<<" "<<value(Btgt_prof/S0)<<" "<<value(YPR_dead)<<" "<<value(column(equ_catch_fleet,2)*Btgt_prof_rec);
          for(p=1;p<=pop;p++)
          for(gp=1;gp<=N_GP;gp++)
          {report5<<" "<<Spbio_equil(p,gp)*Btgt_prof_rec;}
          report5<<" end "<<R0<<" "<<S0<<endl;
          if(SPRloop1==1)
            {Fmult2*=Fmultchanger1;}
          else if(SPRloop1==2)
            {Fmult2+=Fmultchanger2;}
          else
          {Fmult2*=1.075;}
        }
        }  // end Fmult profile

      }  // end Btarget profile
// ******************************************************
//  start finding Fmsy     ProgLabel_730
//  consider using maxpossF here, instead of calculating a new Fmax

    if(Do_MSY==0)
      {
       Fmax=1.; MSY=-1; Bmsy=-1; Recr_msy=-1; SPR=-1; Yield=-1; totbio=1; smrybio=1.; MSY_Fmult=-1.;   //  use these values if MSY is not calculated
       Mgmt_quant(1)=S0;  // this may be redundant
       if(show_MSY==1) report5<<"MSY_not_calculated;_ignore_values"<<endl;
      }
    else
      {
      if(F_Method>=2) {Fmax=10./sum(ForeRatePattern);}

      switch(Do_MSY)
        {
        case 1:  // set Fmsy=Fspr
          {Fmult=SPR_Fmult;
           if(F_Method==1) {Fmax=SPR_Fmult*1.1;}
           F1(1)=-log(Fmax/SPR_Fmult-1.); last_calc=0.; Fchange=1.0; Closer=1.; Nloops=0;
           break;}
        case 2:  // calc Fmsy
          {last_calc=0.; Fchange=0.51; Closer=1.0; Nloops=19;
          if(F_Method==1) {Fmax=(Btgt_Fmult+SPR_Fmult)*0.5*SR_parm(2)/0.05;}    //  previously /0.18
           F1(1)=-log(Fmax/Btgt_Fmult-1.);
          break;}
        case 3:  // set Fmsy=Fbtgt
          {Fmult=Btgt_Fmult;
           if(F_Method==1) {Fmax=Btgt_Fmult*1.1;}
            F1(1)=-log(Fmax/Btgt_Fmult-1.); last_calc=0.; Fchange=1.0; Closer=1.0; Nloops=0;
          break;}
        case 4:   //  set fmult for Fmsy to 1
          {Fmult=1; Fmax=1.1; F1(1)=-log(Fmax/Fmult-1.); last_calc=0.; Fchange=1.0; Closer=1.0; Nloops=0;
          break;}
        }

      if(show_MSY==1) report5<<"+ + + + + + + + + findFmsy"<<endl<<"Iter Fmult SPR Catch SSB Recruits SSB/Bzero Gradient Curvature"<<endl;

        bestF1.initialize(); bestF2.initialize();

      df=0.050;
      jj=3;
      for(j=0;j<=Nloops;j++)   // loop to find Fmsy
        {
        df*=.95;
        Closer*=0.8;
          F1(2) = F1(1) + df*.5;
          F1(3) = F1(2) - df;

        for(int ii=jj;ii>=1;ii--)
          {
          Fmult=Fmax/(1+mfexp(-F1(ii)));
          for(f=1;f<=Nfleet;f++)
          for(s=1;s<=nseas;s++)
            {t=styr+(endyr+1-styr)*nseas+s-1; Hrate(f,t)=Fmult*ForeRatePattern(s,f);}

          Fishon=1;
          Do_Equil_Calc();
          S1_trial=Spbio_equil_sum;
          SPR = S1_trial/S1(0);

          if(SR_fxn==1 || SR_fxn==3)  //Beverton-Holt
            {
            Bmsy = alpha * S1_trial - beta;
            Bmsy=posfun(Bmsy,0.0001,temp);
            Recr_msy =  (4.*SR_parm(2)*R0*Bmsy) / (S0*(1.-SR_parm(2))+(5.*SR_parm(2)-1.)*Bmsy);
            }
          else if(SR_fxn==2)          // Ricker
            {
            Bmsy=S0*(1.+(log(R0/S0)+log(S1_trial))/SR_parm(2));
            Recr_msy = R0*Bmsy/S0 * mfexp(SR_parm(2)*(1.-Bmsy/S0));
            }
          else if(SR_fxn==4)   // constant; no bias correction
            {
            Bmsy=S1_trial*R0;  Recr_msy=R0;
            }
          else
            {Recr_msy=0.;}

          yld1(ii)=YPR_dead*Recr_msy;   //  *mfexp(-Equ_penalty);
          Yield=YPR_dead*Recr_msy;
          bestF1+=F1(ii)*(pow(mfexp(Yield/1.0e08),5)-1.);
          bestF2+=pow(mfexp(Yield/1.0e08),5)-1.;
          }   //  end gradient calc

        dyld   = (yld1(2) - yld1(3))/df;                      // First derivative (to find the root of this)
        temp  = (yld1(2) + yld1(3) - 2.*yld1(1))/(.25*df*df);   // Second derivative (for Newton Raphson)
        dyldp = -sqrt(temp*temp+1.);   //  add 1 to keep curvature reasonably large
        last_F1=F1(1);
        temp = F1(1)-dyld*(1.-Closer)/(dyldp);
        if(show_MSY==1) report5<<j<<" "<<Fmult<<" "<<SPR<<" "<<yld1(1)<<" "<<Bmsy<<" "<<Recr_msy<<" "<<Bmsy/S0<<" "
          <<dyld <<" "<<dyldp <<endl;

        if(j<=9)
          {F1(1)=(1.-Closer)*temp+Closer*(bestF1/bestF2);}        // averages with best value to keep from changing too fast
        else
          {F1(1)=temp;}
//        report5<<" "<<F1(1)<<endl;
        }   // end search loop
    if(fabs(dyld/dyldp)>=0.001 && Do_MSY==2)
    {N_warn++; warning<<" warning: poor convergence in Fmsy, final dy/dy2= "<<dyld/dyldp<<endl;}
    report5<<"catch_by_fleet_by_(encB,deadB,retB,encN,deadN,retN): "<<endl<<equ_catch_fleet*Recr_msy<<endl;
    if(Fmult*3.0 <= SPR_Fmult) {N_warn++; warning<<" Fmsy is <1/3 of Fspr are you sure?  check for convergence "<<endl;}
    if(Fmult/3.0 >= SPR_Fmult) {N_warn++; warning<<" Fmsy is >3x of Fspr are you sure?  check for convergence "<<endl;}
    if(Fmult/0.98 >= Fmax) {N_warn++; warning<<" Fmsy is close to max allowed; check for convergence "<<endl;}

      YPR_msy_enc = YPR_enc;
      YPR_msy_dead = YPR_dead;           // total dead yield per recruit
      YPR_msy_N_dead = YPR_N_dead;           // total dead yield per recruit
      YPR_msy_ret = YPR_ret;           // total retained yield per recruit
      MSY=Yield;
      MSY_Fmult=Fmult;
      Mgmt_quant(1)=Yield;
      Mgmt_quant(2)=Bmsy;
      Mgmt_quant(3)=SPR;
      Mgmt_quant(5)=equ_F_std;
      if(Do_Retain==1) Mgmt_quant(7)=YPR_ret*Recr_msy;
      }

    if(rundetail>0) cout<<" got Fmsy "<<MSY_Fmult<<" "<<MSY<<endl;

// ***************** show management report   ProgLabel_740
    if(show_MSY==1)
      {
    report5<<"+ + + + +"<<endl<<"Management_report"<<endl;
    report5<<"Steepness_R0_S0 "<<SR_parm(2)<<" "<<R0<<" "<<S0<<endl;
    report5<<"+"<<endl<<"Element Value B_per_Recr B_per_R0 B_Total N_per_Recr N_total (B_in_mT;_N_in_thousands)"<<endl;
    report5<<"Recr_unfished(R0) -- "<<1.0<<" "<<1.0<<" "<<R0<<endl;
    report5<<"SPB_unfished(S0) -- "<<S1(0)<<" "<<S1(0)<<" "<<S1(0)*R0<<endl;
    report5<<"BIO_Smry_unfished -- "<<Vbio1_unfished<<" "<<Vbio1_unfished<<" "<<Vbio1_unfished*R0<<endl<<"+ + + + +"<<endl;

    report5<<"SPR_target "<<SPR_target<<endl;
    report5<<"SPR_calc "<<SPR_actual<<endl;
    report5<<"Fmult "<<SPR_Fmult<<endl;
    report5<<"Exploit(Y/Bsmry) "<<YPR_spr/Vbio1_spr<<endl;
    report5<<"Recruit -- -- "<<Bspr_rec/R0<<" "<<Bspr_rec<<endl;
    report5<<"SPBio -- "<<SPBperREC_at_target<<" -- "<<SPBperREC_at_target*Bspr_rec<<endl;
    report5<<"YPR_encountered -- "<<YPR_tgt_enc<<" -- "<<YPR_tgt_enc*Bspr_rec<<endl;
    report5<<"YPR_dead -- "<<YPR_tgt_dead<<" -- "<<YPR_tgt_dead*Bspr_rec<<" "<<YPR_tgt_N_dead<<" "<<YPR_tgt_N_dead*Bspr_rec<<endl;
    report5<<"YPR_retain -- "<<YPR_tgt_ret<<" -- "<<YPR_tgt_ret*Bspr_rec<<endl;
    report5<<"Biomass_Smry -- "<<Vbio1_spr<<" -- "<<Vbio1_spr*Bspr_rec<<endl<<"+ + + + +"<<endl;

    report5<<"Btarget_rel_to_S0 "<<BTGT_target<<endl;
    report5<<"Btgt_calc "<<Btgt/S0<<endl;
    report5<<"SPR "<<SPR_Btgt<<endl;
    report5<<"Fmult "<<Btgt_Fmult<<endl;
    report5<<"Exploit(Y/Bsmry) "<<YPR_Btgt_dead/Vbio1_Btgt<<endl;
    report5<<"Recruit -- -- "<<Btgt_Rec/R0<<" "<<Btgt_Rec<<endl;
    report5<<"SPBio -- "<<Btgt/Btgt_Rec<<" -- "<<Btgt<<endl;
    report5<<"YPR_encountered -- "<<YPR_Btgt_enc<<" -- "<<YPR_Btgt_enc*Btgt_Rec<<endl;
    report5<<"YPR_dead -- "<<YPR_Btgt_dead<<" -- "<<YPR_Btgt_dead*Btgt_Rec<<" "<<YPR_Btgt_N_dead<<" "<<YPR_Btgt_N_dead*Btgt_Rec<<endl;
    report5<<"YPR_retain -- "<<YPR_Btgt_ret<<" -- "<<YPR_Btgt_ret*Btgt_Rec<<endl;
    report5<<"Biomass_Smry -- "<<Vbio1_Btgt<<" -- "<<Vbio1_Btgt*Btgt_Rec<<endl<<"+ + + + +"<<endl;

        switch(Do_MSY)
          {
          case 1:  // set Fmsy=Fspr
            {report5<<"set_Fmsy=Fspr"<<endl;
            break;}
          case 2:  // calc Fmsy
            {report5<<"calculate_FMSY"<<endl;
            break;}
          case 3:  // set Fmsy=Fbtgt
            {report5<<"set_Fmsy=Fbtgt"<<endl;
            break;}
          case 4:   //  set fmult for Fmsy to 1
            {report5<<"set_Fmsy_using_Fmult=1.0"<<endl;
            break;}
          }
    report5<<"SPR "<<SPR<<endl;
    report5<<"Fmult "<<MSY_Fmult<<endl;
    report5<<"Exploit(Y/Bsmry) "<<MSY/(smrybio*Recr_msy)<<endl;
    report5<<"Recruits -- -- "<<Recr_msy/R0<<" "<<Recr_msy<<endl;
    report5<<"SPBio -- "<<Bmsy/Recr_msy<<" -- "<<Bmsy<<endl;
    report5<<"SPBmsy/SPBzero(using_S0) -- "<<Bmsy/S0<<" -- --"<<endl;  // new version
    report5<<"SPBmsy/SPBzero(using_endyear_LifeHistory) -- "<<Bmsy/(R0*S1(0))<<" -- --"<<endl;
    report5<<"MSY_for_optimize -- "<<MSY/Recr_msy<<" -- "<<MSY<<endl;
    report5<<"MSY_encountered -- "<<YPR_msy_enc<<" -- "<<YPR_msy_enc*Recr_msy<<endl;
    report5<<"MSY_dead -- "<<YPR_msy_dead<<" -- "<<YPR_msy_dead*Recr_msy<<" "<<YPR_msy_N_dead<<" "<<YPR_msy_N_dead*Recr_msy<<endl;
    report5<<"MSY_retain -- "<<YPR_msy_ret<<" -- "<<YPR_msy_ret*Recr_msy<<endl;
    report5<<"Biomass_Smry -- "<<smrybio<<" -- "<<smrybio*Recr_msy<<endl<<"+"<<endl;

    report5<<"Summary_age: "<<Smry_Age<<endl<<"+"<<endl;

      }

FUNCTION Get_Forecast
// ******************************************************************************
//  start forecast using Fspr and endyr specifications         ProgLabel_750
  int Do_4010;
  int bio_t;
  dvariable ABC_catch;
  dvariable Fore_Crash;
  dvariable totcatch;
  dvar_matrix catage_w(1,gmorph,0,nages);
  dvar_vector tempcatch(1,Nfleet);

  {
    if(rundetail>0) cout<<" Do Forecast "<<YrMax<<endl;
    Adj4010=1.0;   // for use when do 4010 = 0

        switch(Do_Forecast)
          {
          case 1:
            {F_forecast=SPR_Fmult; if(show_MSY==1) report5<<"Forecast_using_Fspr"<<endl; break;}
          case 2:
            {F_forecast=MSY_Fmult; if(show_MSY==1) report5<<"Forecast_using_Fmsy"<<endl; break;}
          case 3:
            {F_forecast=Btgt_Fmult; if(show_MSY==1) report5<<"Forecast_using_F(Btarget)"<<endl; break;}
          case 4:
            {F_forecast=1.0; if(show_MSY==1) report5<<"Forecast_using_current_F "<<endl; break;}
          }
    if(show_MSY==1)
    {
      if(Fore_Rel_Harvest==1) {report5<<"Allocation_Pattern_as_in_endyear";} else {report5<<"Allocation_Pattern_from_Input";}
      report5<<endl<<"Harvest_Rates_by_Season&Fleet_(equals_selected_forecast_Fmult_*_Allocation_pattern"<<endl;
      report5<<"Season"; for (f=1;f<=Nfleet;f++) {report5<<" fleet:"<<f;}
      report5<<endl;
      for(s=1;s<=nseas;s++) {report5<<s<<" "<<F_forecast*ForeRatePattern(s)<<endl;}

      report5<<"N_forecast_yrs: "<<N_Fore_Yrs<<endl;
      report5<<"OY_Control: Method: "<<HarvestPolicy<<" Top: "<<H4010_top<<" Bottom: "<<H4010_bot<<" Scale: "<<H4010_scale<<endl<<"+"<<endl;
      if(N_fore_catches>0)
      {
        if(ForeCatch_basis==1)
        {report5<<"Input catches as retained catch"<<endl;}
        else
        {report5<<"Input catches as total dead catch"<<endl;}
      }
    }

    for(Do_4010=0; Do_4010<=1; Do_4010++)
    {
      k1 = styr+(endyr-styr)*nseas-1;   // 0 point for beginning of last year

      if(show_MSY==1)
      {
        if(Do_4010==0)
        {report5<<"FORECAST:_With_Constant_F"<<endl;}
        else
        {
          report5<<"FORECAST:__with_Target_Adjustment_when_SPB_is_between: "<<H4010_top<<" and "<<H4010_bot<<" with overall adjustment of: "<<H4010_scale;
          if(HarvestPolicy==1) {report5<<" adjust_catch"<<endl;} else {report5<<" adjust_F"<<endl;}
        }
        report5<<"pop year season 4010 bio-all bio-Smry SpawnBio Depletion recruit-0 ";
        for (f=1;f<=Nfleet;f++) {report5<<" enc(B):_"<<f<<" dead(B):_"<<f<<" retain(B):_"<<f<<
              " enc(N):_"<<f<<" dead(N):_"<<f<<" retain(N):_"<<f<<" F:_"<<f;}
        report5<<" R/C ABC"<<endl;
      }

   //  note that spawnbio and Recruits need to retain their value from calculation in endyr, so can be used to distribute recruitment
   //  in year endyr+1 if recruitment distribution occurs before spawning season
      SpawnBio=Spbio_tot(endyr);
      Recruits=use_rec(endyr);
      for (y=endyr+1;y<=YrMax;y++)
      {
        t_base=styr+(y-styr)*nseas-1;
        smry(y).initialize();
        SmryBio(y)=0.0;
        SmryNum(y)=0.0;
        Mgmt_quant(Fore_catch_start+y-endyr)=0.0;
        if(Do_Retain==1) Mgmt_quant(Fore_catch_start+N_Fore_Yrs+y-endyr)=0.0;
        if(STD_Yr_Reverse_F(y)>0) F_std(STD_Yr_Reverse_F(y))=0.0;

        if(time_vary_MG(endyr+1,2)>0 || save_for_report==1)
        {
          get_MGsetup();
          get_growth2();
        }

        for (s=1;s<=nseas;s++)
        {
          t = t_base+s;
          catch_fleet(t).initialize();
          bio_t=styr+(endyr-styr)*nseas+s-1;
          Fore_Crash=0.;
          if(time_vary_MG(endyr+1,2)>0 || time_vary_MG(endyr+1,3)>0)
          {
            Make_AgeLength_Key();        // indexed by season and gmorph
          }
          else
          {
//            if(save_for_report==1)
            {
              Save_Ave_Size(t)=Save_Ave_Size(t-nseas);
            }
            Save_Wt_Age(t)=Wt_Age_beg(s);
          }
          for (g=1;g<=gmorph;g++)
          if(use_morph(g)>0)
          {Make_FishSelex();}

          if(s==nseas) {k=1;} else {k=0;}   //      advance age or not

          if(s==spawn_seas)    //
          {
            Spbio(y).initialize();
            for (p=1;p<=pop;p++)
            {
              for (g=1;g<=gmorph;g++)
              if(sx(g)==1 && use_morph(g)>0)     //  female
              {Spbio(y,p,GP4(g))+=fec(g)*natage(t,p,g);}
            }
            SpawnBio=sum(Spbio(y));
            Spbio_tot(y)=SpawnBio;

            R_base=R0;  S_base=S0;  steepness=SR_parm(2);
            if(SR_env_target==2) {R_base*=mfexp(SR_parm(4)* env_data(y,SR_env_link)); S_base*=mfexp(SR_parm(4)* env_data(y,SR_env_link));}
            if(SR_env_target==3)
            {
              temp=log((SRvec_HI(2)-SRvec_LO(2)+0.0000002)/(SR_parm(2)-SRvec_LO(2)+0.0000001)-1.)/(-2.);
              temp+=SR_parm(4)* env_data(y,SR_env_link);
              steepness=SRvec_LO(2)+(SRvec_HI(2)-SRvec_LO(2))/(1+mfexp(-2.*temp));
            }
            if(SR_fxn==1)
            {
              if(SpawnBio>S_base) {t1=S_base;} else {t1=SpawnBio;}
              Recruits = (4.*steepness*R_base*t1) / (S_base*(1.-steepness)+(5.*steepness-1.)*t1);  // beverton-holt with cap
            }
            else if(SR_fxn==2)
            {Recruits = R_base*SpawnBio/S_base * mfexp(steepness*(1.-SpawnBio/S_base));}  // ricker
            else if(SR_fxn==3)
            {Recruits = (4.*steepness*R_base*SpawnBio) / (S_base*(1.-steepness)+(5.*steepness-1.)*SpawnBio);}  // beverton-holt
            else if(SR_fxn==4)
            {Recruits=R_base;}
            else
            {Recruits = 0.;}

            exp_rec(y)=Recruits;
            if(SR_env_target==1) Recruits *= mfexp(SR_parm(4)* env_data(y,SR_env_link));

//            if(y<=YrMax)
//            {
              if(SR_fxn!=4) Recruits*=mfexp(-biasadj(y)*SR_parm(3)*SR_parm(3)*0.5);
              pred_rec(y)=(Recruits);
              Recruits*=mfexp(fore_recruitments(y));
              use_rec(y)=Recruits;
//            }
          }  //  end of spawner-recruitment calculations

          for (g=1;g<=gmorph;g++)
          if(use_morph(g)>0 && s==Bseas(g))
          for (p=1;p<=pop;p++)
          {natage(t,p,g,0) = Recruits*recr_dist(GP(g),s,p)*submorphdist(GP2(g));}

          if(Do_4010==1)
          {
            if(HarvestPolicy==1)  // west coast
            {
              Adj4010 = H4010_scale*
              ((0.0001*SpawnBio/(H4010_bot*S0) )
              /(1.+mfexp(10.*(SpawnBio-H4010_bot*S0)))   // low
              +(0.0001+(1.0-0.0001)*(H4010_top*S0/SpawnBio)*(SpawnBio-H4010_bot*S0)/(H4010_top*S0-H4010_bot*S0))
              /(1.+mfexp(-10.*(SpawnBio-H4010_bot*S0)))   // curve
              )
              /(1.+mfexp( 10.*(SpawnBio-H4010_top*S0)))    // scale combo
              +
              (1.)
              /(1.+mfexp( -10.*(SpawnBio-H4010_top*S0)));    // scale right side
            }
            else if(HarvestPolicy==2)  // Alaska
            {
              Adj4010 = H4010_scale*
              ((0.0001*SpawnBio/(H4010_bot*S0) )
              /(1.+mfexp(10.*(SpawnBio-H4010_bot*S0)))   // low
              +(0.0001+(1.0-0.0001)*(SpawnBio-H4010_bot*S0)/(H4010_top*S0-H4010_bot*S0))
              /(1.+mfexp(-10.*(SpawnBio-H4010_bot*S0)))   // curve
              )
              /(1.+mfexp( 10.*(SpawnBio-H4010_top*S0)))    // scale combo
              +
              (1.)
              /(1.+mfexp( -10.*(SpawnBio-H4010_top*S0)));    // scale right side
            }
          }  // end do_4010==1

          for (p=1;p<=pop;p++)
          {
            totbio.initialize();smrybio.initialize(); ABC_catch.initialize();
              for (g=1;g<=gmorph;g++)
              if(use_morph(g)>0)
              {
                gg=sx(g);
                temp=natage(t,p,g)*Wt_Age_beg(s,g);
                totbio+=temp;
                temp=natage(t,p,g)(Smry_Age,nages)*Wt_Age_beg(s,g)(Smry_Age,nages);
                smrybio+=temp;
                if(s==1) SmryBio(y)+=temp;
                if(s==1) SmryNum(y)+=sum(natage(t,p,g)(Smry_Age,nages));   //sums to accumulate across submorphs and birthseasons
                Nmid(g) = elem_prod(natage(t,p,g),surv1(s,GP3(g)));
              }

  int Tune_ForeCatch;
            if (F_Method==1)  // Pope's approximation
            {
              Nsurv=Nmid;
              if(fishery_on_off==1)
              {
                k1=1;
                if(Do_4010==1 && Max_Fore_Catch_Basis>0)
                {
                  if(Max_Fore_Catch(s,p)>0.)
                  {k1=2;}
                }

                totcatch.initialize();
                for(Tune_ForeCatch=1;Tune_ForeCatch<=k1;Tune_ForeCatch++)
                {
                  for (f=1;f<=Nfleet;f++)
                  if (fleet_area(f)==p && ForeRatePattern(s,f)>0.0)   // active fishery in this area in endyr
                  {
                    fish_bio.initialize(); fish_bio_r.initialize(); fish_bio_e.initialize();
                    fish_num.initialize(); fish_num_r.initialize(); fish_num_e.initialize();

                    for (g=1;g<=gmorph;g++)
                    if(use_morph(g)>0)
                    {
                      gg=sx(g);
                      fish_bio+= Nmid(g)*deadfish_B(s,g,f);
                      fish_bio_r+= Nmid(g)*sel_al_2(s,g,f);
                      catage_w(g)= elem_prod(Nmid(g),deadfish(s,g,f));
                      fish_num+=  sum(catage_w(g));  // numbers of deadfish
                      fish_num_r+=Nmid(g)*sel_al_4(s,g,f);  // numbers of retained fish
                      fish_bio_e+= Nmid(g)*sel_al_1(s,g,f);
                      fish_num_e+= Nmid(g)*sel_al_3(s,g,f);
                    }  //close gmorph loop
                    if(Tune_ForeCatch==1)
                    {
                      // only setup the Hrate if this is not the second stage of adjusting for max Catch
                      if(Input_ForeCatch(t,f)<0. || Do_4010==0)
                      {                                                       // get catch from F
                        Hrate(f,t)=Adj4010*F_forecast*ForeRatePattern(s,f);
                      }
                      else
                      {                                                       // get F from catch
                        if(ForeCatch_basis==1)
                        {temp=max_harvest_rate-Input_ForeCatch(t,f)/(fish_bio_r+NilNumbers);}
                        else
                        {temp=max_harvest_rate-Input_ForeCatch(t,f)/(fish_bio+NilNumbers);}
                        Hrate(f,t)=max_harvest_rate-posfun(temp,0.0001,Fore_Crash);
                       }  // end calc of catch and rate
                    }
                    catch_fleet(t,f,1)=Hrate(f,t)*fish_bio_e;
                    catch_fleet(t,f,2)=Hrate(f,t)*fish_bio;
                    catch_fleet(t,f,3)=Hrate(f,t)*fish_bio_r;
                    catch_fleet(t,f,4)=Hrate(f,t)*fish_num_e;
                    catch_fleet(t,f,5)=Hrate(f,t)*fish_num;
                    catch_fleet(t,f,6)=Hrate(f,t)*fish_num_r;

                    if(Do_4010==1 && Tune_ForeCatch==k1)
                    {
//                      if(Input_ForeCatch(t,f)<0. && Tune_ForeCatch==1)
                      if(Input_ForeCatch(t,f)<0.)
                      {
                        Mgmt_quant(Fore_catch_start+y-endyr)+=catch_fleet(t,f,2);
                        if(Do_Retain==1) Mgmt_quant(Fore_catch_start+N_Fore_Yrs+y-endyr)+=catch_fleet(t,f,3);
                      }
                      else     //  accumulate the harvest rates, not the catches
                      {
                        Mgmt_quant(Fore_catch_start+y-endyr)+=Hrate(f,t);
                        if(Do_Retain==1) Mgmt_quant(Fore_catch_start+N_Fore_Yrs+y-endyr)+=Hrate(f,t);
                      }
                    }

                    if(Tune_ForeCatch<k1)
                    {
                      switch(Max_Fore_Catch_Basis)
                      {
                        case 1:
                        {totcatch+=catch_fleet(t,f,2); break;}      // dead catch bio
                        case 2:
                        {totcatch+=catch_fleet(t,f,3); break;}      // retained catch bio
                        case 3:
                        {totcatch+=catch_fleet(t,f,5); break;}      // deadfish catch numbers
                        case 4:
                        {totcatch+=catch_fleet(t,f,6); break;}      // retained catch numbers
                      }
                    }
                    else
                    {
                      Nsurv -= Hrate(f,t)*catage_w;
                      ABC_catch+=F_forecast*ForeRatePattern(s,f)*fish_bio;
                      if(Do_4010==1)
                      {
                        smry(y,3)+=catch_fleet(t,f,1);
                        smry(y,4)+=catch_fleet(t,f,2);
                        smry(y,5)+=catch_fleet(t,f,3);
                      }
                    }
                  } // end fleet
                  if(Tune_ForeCatch<k1)
                  {
                    temp = totcatch/Max_Fore_Catch(s,p);
                    join1=1./(1.+mfexp(1000.*(temp-1.0)));  // steep logistic joiner at adjustment of 1.0
                    temp1=join1*1.0 + (1.-join1)*temp;
                    for(f=1;f<=Nfleet;f++)
                    if (fleet_area(f)==p)
                    {
                       Hrate(f,t)/=temp1;
                    }
                  }
                }  // end tune to keep catch < maxcatch
              }   // end fishery_on_off

              for (g=1;g<=gmorph;g++)
              if(use_morph(g)>0)
              {
                if(s<nseas) natage(t+1,p,g,0) = Nsurv(g,0)*surv1(s,GP3(g),0);  // advance age zero within year
                for (a=1;a<nages;a++) {natage(t+1,p,g,a) = Nsurv(g,a-k)*surv1(s,GP3(g),a-k);}    //  make -k correction with V1.23
                natage(t+1,p,g,nages) = Nsurv(g,nages)*surv1(s,GP3(g),nages);   // plus group
                if(s==nseas) natage(t+1,p,g,nages) += Nsurv(g,nages-1)*surv1(s,GP3(g),nages-1);
              }
            }   //  end Pope's approx as F_Method

            else   // continuous F for method 2 or 3
            {
              k1=0;
              for(f=1;f<=Nfleet;f++)
              {
                Hrate(f,t)=Adj4010*F_forecast*ForeRatePattern(s,f);
                if(Input_ForeCatch(t,f)>0.0) k1=1;  // have a positive catch for some fleet
              }
              if(k1==1 && fishery_on_off==1)
              {
                for(k1=1;k1<=5;k1++)  // tuning loops
                {
                  tempcatch.initialize();
                  for (g=1;g<=gmorph;g++)
                  if(use_morph(g)>0)
                  {
                    Z_rate(t,p,g)=natM(s,GP3(g));
                    for (f=1;f<=Nfleet;f++)       //loop over fishing fleets to get Z       ProgLabel_105
                    if (fleet_area(f)==p && ForeRatePattern(s,f)>0.0)
                    {
                      Z_rate(t,p,g)+=deadfish(s,g,f)*Hrate(f,t);
                    }
                    Zrate2(g)=elem_div( (1.-mfexp(-seasdur(s)*Z_rate(t,p,g))), Z_rate(t,p,g));
                  }  //  end morph

                  for (f=1;f<=Nfleet;f++)       //loop over fishing fleets       ProgLabel_105
                  if (fleet_area(f)==p && ForeRatePattern(s,f)>0.0 && Input_ForeCatch(t,f)>0.0)
                  {
                    for (g=1;g<=gmorph;g++)
                    if(use_morph(g)>0)
                    {
                      if(catchunits(f)==1)
                      {
                       if(ForeCatch_basis==2)
                      {tempcatch(f)+=Hrate(f,t)*elem_prod(natage(t,p,g),deadfish_B(s,g,f))*Zrate2(g);}      // dead catch bio
                      else
                      {tempcatch(f)+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_2(s,g,f))*Zrate2(g);}      // retained catch bio
                     }
                     else
                     {
                       if(ForeCatch_basis==2)
                       {tempcatch(f)+=Hrate(f,t)*elem_prod(natage(t,p,g),deadfish(s,g,f))*Zrate2(g);}      // deadfish catch numbers
                      else
                      {tempcatch(f)+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_4(s,g,f))*Zrate2(g);}      // retained catch numbers
                     }
                    }  //close gmorph loop
                  }  // close fishery

                  for(f=1;f<=Nfleet;f++)
                  if (fleet_area(f)==p && ForeRatePattern(s,f)>0.0 && Input_ForeCatch(t,f)>0.0)
                  {
                     Hrate(f,t)*=Input_ForeCatch(t,f)/tempcatch(f);
                  }
                }  // end tuning loop
              }  // end need to do tuning because of a specified catch level

// now tune to keep catch < maxcatch
              k1=0;
              if(Max_Fore_Catch_Basis>0 && fishery_on_off==1)
              {
                if(Max_Fore_Catch(s,p)>0.) k1=1;
              }

              if(k1>0)
              {
                for(k1=1;k1<=5;k1++)  // tuning loops
                {
                  totcatch=0.;
                  for (g=1;g<=gmorph;g++)
                  if(use_morph(g)>0)
                  {
                    Z_rate(t,p,g)=natM(s,GP3(g));
                    for (f=1;f<=Nfleet;f++)       //loop over fishing fleets to get Z       ProgLabel_105
                    if (fleet_area(f)==p && ForeRatePattern(s,f)>0.0)
                    {
                      Z_rate(t,p,g)+=deadfish(s,g,f)*Hrate(f,t);
                    }
                    Zrate2(g)=elem_div( (1.-mfexp(-seasdur(s)*Z_rate(t,p,g))), Z_rate(t,p,g));
                  }  //  end morph

                  for (f=1;f<=Nfleet;f++)       //loop over fishing fleets       ProgLabel_105
                  if (fleet_area(f)==p && ForeRatePattern(s,f)>0.0)
                  {
                    for (g=1;g<=gmorph;g++)
                    if(use_morph(g)>0)
                    {
                      switch(Max_Fore_Catch_Basis)
                      {
                        case 1:
                        {totcatch+=Hrate(f,t)*elem_prod(natage(t,p,g),deadfish_B(s,g,f))*Zrate2(g); break;}      // dead catch bio
                        case 2:
                        {totcatch+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_2(s,g,f))*Zrate2(g); break;}      // retained catch bio
                        case 3:
                        {totcatch+=Hrate(f,t)*elem_prod(natage(t,p,g),deadfish(s,g,f))*Zrate2(g); break;}      // deadfish catch numbers
                        case 4:
                        {totcatch+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_4(s,g,f))*Zrate2(g); break;}      // retained catch numbers
                     }
                    }  //close gmorph loop
                  }  // close fishery
                  temp=totcatch/Max_Fore_Catch(s,p);
                  join1=1./(1.+mfexp(1000.*(temp-1.0)));  // steep logistic joiner at adjustment of 1.0
                  temp1=join1*1.0 + (1.-join1)*temp;
                  cout<<k1<<" "<<Max_Fore_Catch(s,p)<<" "<<totcatch<<" "<<temp<<" "<<join1<<" "<<temp1<<endl;
                  for(f=1;f<=Nfleet;f++)
                  if (fleet_area(f)==p)
                  {
                     Hrate(f,t)/=temp1;
                  }
                }  // end tuning loop
              }  // end need to do tuning for max catch

//  after tuning, redo the continuous F calcs to store the needed quantities
              for (g=1;g<=gmorph;g++)
              if(use_morph(g)>0)
              {
                Z_rate(t,p,g)=natM(s,GP3(g));
                for (f=1;f<=Nfleet;f++)       //loop over fishing fleets to get Z       ProgLabel_105
                if (fleet_area(f)==p && ForeRatePattern(s,f)>0.0 && fishery_on_off==1)
                {
                  Z_rate(t,p,g)+=deadfish(s,g,f)*Hrate(f,t);
                }
                Zrate2(g)=elem_div( (1.-mfexp(-seasdur(s)*Z_rate(t,p,g))), Z_rate(t,p,g));
              }  //  end morph
              if(fishery_on_off==1)
              {
                for (f=1;f<=Nfleet;f++)       //loop over fishing fleets       ProgLabel_105
                if (fleet_area(f)==p && ForeRatePattern(s,f)>0.0)
                {
                  for (g=1;g<=gmorph;g++)
                  if(use_morph(g)>0)
                  {
                    catch_fleet(t,f,1)+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_1(s,g,f))*Zrate2(g);      // encountered catch bio
                    catch_fleet(t,f,2)+=Hrate(f,t)*elem_prod(natage(t,p,g),deadfish_B(s,g,f))*Zrate2(g);      // dead catch bio
                    catch_fleet(t,f,3)+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_2(s,g,f))*Zrate2(g);      // retained catch bio
                    catch_fleet(t,f,4)+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_3(s,g,f))*Zrate2(g);      // encountered catch bio
                    catch_fleet(t,f,5)+=Hrate(f,t)*elem_prod(natage(t,p,g),deadfish(s,g,f))*Zrate2(g);      // deadfish catch numbers
                    catch_fleet(t,f,6)+=Hrate(f,t)*elem_prod(natage(t,p,g),sel_al_4(s,g,f))*Zrate2(g);      // retained catch numbers
                  }  //close gmorph loop
                  if(Do_4010==1)
                  {
                    Mgmt_quant(Fore_catch_start+y-endyr)+=catch_fleet(t,f,2);
                    if(Do_Retain==1) Mgmt_quant(Fore_catch_start+N_Fore_Yrs+y-endyr)+=catch_fleet(t,f,3);
                  }
                  ABC_catch+=catch_fleet(t,f,2)/Adj4010;

                  if(Do_4010==1)
                  {
                    smry(y,3)+=catch_fleet(t,f,1);
                    smry(y,4)+=catch_fleet(t,f,2);
                    smry(y,5)+=catch_fleet(t,f,3);
                  }
                }  // close fishery
              }
              for (g=1;g<=gmorph;g++)
              if(use_morph(g)>0)
              {
                if(s<nseas) natage(t+1,p,g,0) = natage(t,p,g,0)*mfexp(-Z_rate(t,p,g,0)*seasdur(s));  // advance age zero within year
                for (a=1;a<nages;a++) {natage(t+1,p,g,a) = natage(t,p,g,a-k)*mfexp(-Z_rate(t,p,g,a-k)*seasdur(s));}
                natage(t+1,p,g,nages) = natage(t,p,g,nages)*mfexp(-Z_rate(t,p,g,nages)*seasdur(s));   // plus group
                if(s==nseas) natage(t+1,p,g,nages) += natage(t,p,g,nages-1)*mfexp(-Z_rate(t,p,g,nages-1)*seasdur(s));
              }  // end morph loop
            }  // end continuous F_method

           if(show_MSY==1)
           {
            report5<<p<<" "<<y<<" "<<s<<" "<<Adj4010<<" "<<totbio<<" "<<smrybio<<" ";
            if(s==spawn_seas)
            {report5<<SpawnBio<<" "<<SpawnBio/S0<<" "<<Recruits;}
            else
            {report5<<0<<" "<<0<<" "<<0;}

            for (f=1;f<=Nfleet;f++)
            {
            if(fleet_area(f)==p)
            {report5<<" "<<catch_fleet(t,f)(1,6)<<" "<<Hrate(f,t);}
            else
            {report5<<" - - - - - ";}
            if(Input_ForeCatch(t,f)<0) {report5<<" R ";} else {report5<<" C ";}
           }
            report5<<" "<<ABC_catch;
            if(Fore_Crash>0.) report5<<" crashed "<<Fore_Crash;
            report5<<endl;
           }
           if(s==1&&Do_4010==1)
           {
             smry(y,1)+=totbio;
             smry(y,2)+=smrybio;
           }
         }  // end pop loop

     if(do_migration>0)
       {
       natage_temp=natage(t+1);
       natage(t+1).initialize();
       for (p=1;p<=pop;p++)  //   source population
       for (p2=1;p2<=pop;p2++)  //  destination population
       for (g=1;g<=gmorph;g++)
       if(use_morph(g)>0)
         {
       	 k=move_pattern(s,GP4(g),p,p2);
         if(k>0) natage(t+1,p2,g) += elem_prod(natage_temp(p,g),migrrate(bio_yr,k));
         }
       }
     if(Do_4010==1)
       {//natage(t)=natage(t);
        if(s==spawn_seas)
          {
          smry(y,6)=SpawnBio;
          smry(y,7)=Recruits;
          }
            if( (save_for_report==1) || ((sd_phase() || mceval_phase()) && (initial_params::mc_phase==0)) )
            {
              if(STD_Yr_Reverse_F(y)>0)
              {
                if(F_reporting<=1)
                {
                  for(f=1;f<=Nfleet;f++) F_std(STD_Yr_Reverse_F(y))+=catch_fleet(t,f,2);   // add up dead catch biomass
                  F_std(STD_Yr_Reverse_F(y))/=SmryBio(y);
                }
                else if(F_reporting==2)
                {
                  for(f=1;f<=Nfleet;f++) F_std(STD_Yr_Reverse_F(y))+=catch_fleet(t,f,5);   // add up dead catch numbers
                  F_std(STD_Yr_Reverse_F(y))/=SmryNum(y);
                }
                else if(F_reporting==3)
                {
                  for(f=1;f<=Nfleet;f++)
                  {
                    F_std(STD_Yr_Reverse_F(y))+=Hrate(f,t)*seasdur(s);
                  }
                }
              }
            }
       }
    } //close season loop
    if(Do_4010==1)
      {

    if( (save_for_report==1) || ((sd_phase() || mceval_phase()) && (initial_params::mc_phase==0)) )
    {
      eq_yr=y; equ_Recr=R0; bio_yr=endyr;
      Fishon=0;
      Do_Equil_Calc();                      //  call function to do equilibrium calculation
      S1(0)=Spbio_equil_sum;
      save_SPR(y,3)=value(S1(0));
      save_SPR(y,5)=value(GenTime);
      Fishon=1;
      Do_Equil_Calc();                      //  call function to do equilibrium calculation
      S1(1)=Spbio_equil_sum;
      if(STD_Yr_Reverse_Ofish(y)>0) SPR_std(STD_Yr_Reverse_Ofish(y))=S1(1)/S1(0);
      save_SPR(y,1)=value(totbio);
      save_SPR(y,2)=value(smrybio);
      save_SPR(y,4)=value(S1(1));
      save_SPR(y,6)=value(YPR_dead);
      for(g=1;g<=gmorph;g++)
      {
        save_SPR(y,6+g)=value(cumF(g));
        save_SPR(y,6+gmorph+g)=value(maxF(g));
      }
     }
    }
      } //close year loop

    } // end DO_4010 loop
  }
//  end forecast function


//********************************************************************
//  ProgLabel_8800_FUNCTION  Write Summary output
FUNCTION write_summaryoutput
  random_number_generator radm(long(time(&finish)));

  time(&finish);
  elapsed_time = difftime(finish,start);
  report2<<runnumber<<" -logL: "<<obj_fun<<" Spbio(Vir_Start_End): "<<Spbio_tot(styr-2)<<" "<<Spbio_tot(styr)<<" "<<Spbio_tot(endyr)<<endl;
  report2<<runnumber<<" Files: "<<datfilename<<" "<<ctlfilename;
  if(readparfile>=1) report2<<" Start_from_SS3.PAR";
  report2<<endl<<runnumber<<" N_iter: "<<niter<<" runtime(sec): "<<elapsed_time<<" finish_at:  "<<ctime(&finish);
  report2<<runnumber<<" F_Method: "<<F_Method<<" Retro_YR: "<<retro_yr<<" Forecast_Type: "<<Do_Forecast<<" MSY_Type: "<<Do_MSY<<endl;
  if(N_SC>0)
  {
    for(j=1;j<=N_SC;j++) report2<<runnumber<<" Comment S_"<<j<<" "<<Starter_Comments(j)<<endl;
  }
  if(N_DC>0)
  {
    for(j=1;j<=N_DC;j++) report2<<runnumber<<" Comment D_"<<j<<" "<<Data_Comments(j)<<endl;
  }
  if(N_CC>0)
  {
    for(j=1;j<=N_CC;j++) report2<<runnumber<<" Comment C_"<<j<<" "<<Control_Comments(j)<<endl;
  }
  if(N_FC>0)
  {
    for(j=1;j<=N_FC;j++) report2<<runnumber<<" Comment F_"<<j<<" "<<Forecast_Comments(j)<<endl;
  }
  k=current_phase();
  if(k>max_lambda_phase) k=max_lambda_phase;
  report2<<runnumber<<" Like_Emph Total 1 "<<endl<<runnumber<<" Like_Value Total "<<obj_fun<<endl;
  if(nobs>0) report2<<runnumber<<" Like_Emph Indices All "<<column(surv_lambda,k)<<endl<<
  runnumber<<" Like_Value Indices "<<surv_like*column(surv_lambda,k)<<" " <<surv_like<<endl;
  if(nobs_disc>0) report2<<runnumber<<" Like_Emph Discard All "<<column(disc_lambda,k)<<endl<<
  runnumber<<" Like_Value Discard "<<disc_like*column(disc_lambda,k)<<" " <<disc_like<<endl;
  if(nobs_mnwt>0) report2<<runnumber<<" Like_Emph MeanBodyWt All "<<column(mnwt_lambda,k)<<endl<<
  runnumber<<" Like_Value MeanBodyWt "<<mnwt_like*column(mnwt_lambda,k)<<" " <<mnwt_like<<endl;
  if(nobsl>0) report2<<runnumber<<" Like_Emph LenComp All "<<column(length_lambda,k)<<endl<<
  runnumber<<" Like_Value LenComp "<<length_like*column(length_lambda,k)<<" " <<length_like<<endl;
  if(nobsa>0) report2<<runnumber<<" Like_Emph AgeComp All "<<column(age_lambda,k)<<endl<<
  runnumber<<" Like_Value AgeComp "<<age_like*column(age_lambda,k)<<" " <<age_like<<endl;
  if(nobs_ms>0) report2<<runnumber<<" Like_Emph MeanLAA All "<<column(sizeage_lambda,k)<<endl<<
  runnumber<<" Like_Value MeanLAA "<<sizeage_like*column(sizeage_lambda,k)<<" " <<sizeage_like<<endl;
  if(F_Method>1) report2<<runnumber<<" Like_Emph Catch All "<<column(catch_lambda,k)<<endl<<
  runnumber<<" Like_Value Catch "<<catch_like*column(catch_lambda,k)<<" " <<catch_like<<endl;
  if(WtFreq_Nmeth>0) report2<<runnumber<<" Like_Emph WeightFreq All "<<column(WtFreq_lambda,k)<<endl<<
  runnumber<<" Like_Value WeightFreq "<<WtFreq_like*column(WtFreq_lambda,k)<<" " <<WtFreq_like<<endl;
  if(Do_Morphcomp>0) report2<<runnumber<<" Like_Emph Morphcomp All "<<Morphcomp_lambda(k)<<endl<<
  runnumber<<" Like_Value Morphcomp "<<Morphcomp_like*Morphcomp_lambda(k)<<" " <<Morphcomp_like<<endl;
  if(Do_TG>0) report2<<runnumber<<" Like_Emph Tag_comp All "<<column(TG_lambda1,k)<<endl<<
  runnumber<<" Like_Value Tag_comp "<<TG_like1*column(TG_lambda1,k)<<" " <<TG_like1<<endl;
  if(Do_TG>0) report2<<runnumber<<" Like_Emph Tag_negbin All "<<column(TG_lambda2,k)<<endl<<
  runnumber<<" Like_Value Tag_negbin "<<TG_like2*column(TG_lambda2,k)<<" " <<TG_like2<<endl;

  report2<<runnumber<<" Like_Comp Equ_Catch Recruits Fore_Recr  Priors ParmDevs CrashPen"<<endl;
  report2<<runnumber<<" Like_Emph "<<init_equ_lambda(k)<<" "<<recrdev_lambda(k)<<" " <<1.<<" "
         <<parm_prior_lambda(k)<<" " <<parm_dev_lambda(k)<<" " <<CrashPen_lambda(k)<<endl;
  report2<<runnumber<<" Like_Value*Emph "<<equ_catch_like*init_equ_lambda(k)<<" "<<prior_rec*recrdev_lambda(k)<<" "
         <<prior_fore_rec<<" "<<parm_like*parm_prior_lambda(k)<<" "<<parm_dev_like*parm_dev_lambda(k)<<" "<<CrashPen*CrashPen_lambda(k)<<endl;

  report2 <<runnumber<<" TimeSeries Year Vir Equ "<<years<<" ";
  k=YrMax;
  if(k==endyr) k=endyr+1;
  for(y=endyr+1;y<=k;y++) {report2<<y<<"F ";}
  report2 <<endl;
  report2 <<runnumber<<" Timeseries Spbio "<<column(smry,6)<<endl;
  report2 <<runnumber<<" Timeseries Recruit "<<column(smry,7)<<endl;
  report2 <<runnumber<<" Timeseries TotBio "<<column(smry,1)<<endl;
  report2 <<runnumber<<" Timeseries SmryBio-"<<Smry_Age<<" "<<column(smry,2)<<endl;
  report2 <<runnumber<<" Timeseries TotCatch "<<column(smry,4)<<endl;
  report2 <<runnumber<<" Timeseries RetCatch "<<column(smry,5)<<endl;
  report2 <<runnumber<<" MG_Parms "<<MGparm<<endl;
  report2 <<runnumber<<" SR_Parms "<<SR_parm<<endl;
  if(Do_Benchmark>0) report2<<runnumber<<" Mgmt_Quant "<<Mgmt_quant(1,6+Do_Retain)<<endl;
  if(Q_Npar>0) report2 <<runnumber<<" Q_Parms "<<Q_parm<<endl;
  if(N_selparm>0) report2 <<runnumber<<" Sel_Parms "<<selparm<<endl;
  if(Do_CumReport==2)
  {
    if(nobs>0)
    for(f=1;f<=Ntypes;f++)
    if(nyr_cr(f)>0)
    {
     report2 <<runnumber<<" Index:"<<f<<" Year "<<yr_cr_y(f)<<endl;
 //    report2 <<runnumber<<" Index:"<<f<<" VBIO "<<vul_bio(f)<<endl;
     report2 <<runnumber<<" Index:"<<f<<" OBS "<<obs_cr(f)<<endl;
     report2 <<runnumber<<" Index:"<<f<<" EXP "<<elem_prod(mfexp(log_q_cr(f)),mfexp(exp_cr(f)))<<endl;
    }

    for(f=1;f<=Ntypes;f++)
    if(nyr_l(f)>0)
    {
     report2 <<runnumber<<" Len:"<<f<<" YR "<<yr_l_y(f)<<endl;
     report2 <<runnumber<<" Len:"<<f<<" effN "<<neff_l(f)<<endl;
    }
    for(f=1;f<=Ntypes;f++)
    if(nyr_a(f)>0)
    {
     report2 <<runnumber<<" Age:"<<f<<" YR "<<yr_a_y(f)<<endl;
     report2 <<runnumber<<" Age:"<<f<<" effN "<<neff_a(f)<<endl;
    }
    }
    report2<<endl;

//*****************************************************************************************
//  ProgLabel_8900_FUNCTION write_rebuilder_output
FUNCTION write_rebuilder_output

    cout<<" produce output for rebuilding package"<<endl;
    ofstream rebuilder("rebuild.SSO",ios::app);
    ofstream rebuild_dat("rebuild.dat");

      if(mccounter==1)
        {
        rebuild_dat<<"#Title"<<" #runnumber: "<<runnumber<<" "<<datfilename<<" "<<ctlfilename<<" "<<obj_fun<<
        " "<<Spbio_tot(styr-2)<<" "<<Spbio_tot(endyr+1)<<endl<<"SS2_default_rebuild.dat"<<endl;
        rebuild_dat<<"# Number of sexes"<<endl<<gender<<endl;
        rebuild_dat<<"# Age range to consider (minimum age; maximum age)"<<endl<<0<<" "<<nages<<endl;
        rebuild_dat<<"# Number of fleets"<<endl<<Nfleet<<endl;
        rebuild_dat<<"# First year of projection (Yinit)"<<endl<<Rebuild_Yinit<<endl;
        rebuild_dat<<"# First Year of rebuilding period (Ydecl)"<<endl<<Rebuild_Ydecl<<endl;
        rebuild_dat<<"# Is the maximum age a plus-group (1=Yes;2=No)"<<endl<<1<<endl;
        rebuild_dat<<"# Generate future recruitments using historical recruitments (1)  historical recruits/spawner (2)  or a stock-recruitment (3)"<<endl<<3<<endl;
        rebuild_dat<<"# Constant fishing mortality (1) or constant Catch (2) projections"<<endl<<1<<endl;
        rebuild_dat<<"# Fishing mortality based on SPR (1) or actual rate (2)"<<endl<<1<<endl;
        rebuild_dat<<"# Pre-specify the year of recovery (or -1) to ignore"<<endl<<-1<<endl;
        rebuild_dat<<"# Fecundity-at-age"<<endl;

        }

//a. blank line agevector and run info here
      rebuilder << age_vector <<" #Age vector"<<endl;
      if(mccounter==1) rebuild_dat <<"#"<< age_vector << " #runnumber: "<<runnumber<<" "<<datfilename<<" "<<ctlfilename<<" "<<obj_fun<<
        " "<<Spbio_tot(styr-2)<<" "<<Spbio_tot(endyr+1)<<endl;

//b.  fecundity-at-age
      t = styr+(Rebuild_Yinit-styr)*nseas;
      dvar_vector tempvec2(0,nages);
      dvar_vector tempvec3(0,nages);
      tempvec.initialize(); tempvec2.initialize();
      for(p=1;p<=pop;p++)
      for(g=1;g<=gmorph;g++)
      if(sx(g)==1)
        {
        tempvec+=elem_prod(fec(g),natage(t+spawn_seas-1,p,g)); tempvec2+=natage(t+spawn_seas-1,p,g);
        }
      tempvec = elem_div(tempvec,tempvec2);
      rebuilder<<tempvec<<" #female fecundity; weighted by N in year Y_init across morphs and areas"<<endl;
      if(mccounter==1)
        {
        rebuild_dat<<tempvec<<" #female fecundity; weighted by N in year Y_init across morphs and areas"<<endl;
        rebuild_dat<<"# Age specific selectivity and weight adjusted for discard and discard mortality"<<endl;
        }

//c.  Weight-at-age and selectivity-at-age (ordered by sex and fleet).
      // use the deadfish vectors that account for discard and for mortality of discards
      // average across morphs and areas using N_at_Age in year Yinit and across seasons using Input_ForeRate
    for (gg=1;gg<=gender;gg++)
    for (f=1;f<=Nfleet;f++)
      {
      tempvec.initialize();tempvec2.initialize();tempvec3.initialize(); j=0;
      for(s=1;s<=nseas;s++)
      for(p=1;p<=pop;p++)
      if(Input_ForeRate(s,f)>0. && fleet_area(f)==p)
        {
        j=1;
        for(g=1;g<=gmorph;g++)
        if(sx(g)==gg)
          {
          tempvec+=elem_prod(fish_body_wt(s,g,f),natage(t+s-1,p,g)*Input_ForeRate(s,f));  // body wt
          tempvec2+=elem_prod(sel_al_3(s,g,f),natage(t+s-1,p,g)*Input_ForeRate(s,f));  //no wt
          tempvec3+=natage(t+s-1,p,g)*Input_ForeRate(s,f);
          }
        }
      if(j==1)
        {
        tempvec = elem_div(tempvec,tempvec3);
        tempvec2 = elem_div(tempvec2,tempvec3);
        rebuilder <<tempvec<< " #bodywt for gender,fleet: "<<gg<<" / "<<f<< endl;
        rebuilder <<tempvec2<< " #selex for gender,fleet: "<<gg<<" / "<<f<< endl;
        if(mccounter==1)
          {
          rebuild_dat << " #wt and selex for gender,fleet: "<<gg<<" "<<f<< endl;
          rebuild_dat <<tempvec <<endl<<tempvec2<< endl;
          }
        }
      }


//d.  Natural mortality and numbers-at-age for year Yinit  (females then males).
    if(mccounter==1) rebuild_dat<<"# M and current age-structure in year Yinit: "<<Rebuild_Yinit<<endl;

    for (gg=1;gg<=gender;gg++)
    {
      tempvec.initialize();tempvec2.initialize();tempvec3.initialize();
      for(p=1;p<=pop;p++)
        {
        for(g=1;g<=gmorph;g++)
        if(sx(g)==gg && use_morph(g)>0)
          {
          tempvec+=elem_prod(natM(1,GP3(g)),natage(t,p,g));  tempvec2+=natage(t,p,g);  //  note, uses season 1 only
          }
        }
      tempvec=elem_div(tempvec,tempvec2);
      rebuilder<<tempvec<<" #mean M for year Yinit: "<<Rebuild_Yinit<<" sex: "<<gg<<endl;
      rebuilder<<tempvec2<<" #numbers for year Yinit: "<<Rebuild_Yinit<<" sex: "<<gg<<endl;
      if(mccounter==1) rebuild_dat<<" # gender = "<<gg<<endl<< tempvec<<endl<<tempvec2<< endl;
    }

//e.  Numbers-at-age for year Ydecl  (females then males).
    t = styr+(Rebuild_Ydecl-styr)*nseas;
    if(mccounter==1) rebuild_dat<<"# Age-structure at Ydeclare= "<<Rebuild_Ydecl<<endl;
    for (gg=1;gg<=gender;gg++)
      {
      tempvec.initialize();tempvec2.initialize();tempvec3.initialize();
      for(p=1;p<=pop;p++)
        {
        for(g=1;g<=gmorph;g++)
        if(sx(g)==gg && use_morph(g)>0)
          {
          tempvec2+=natage(t,p,g);
          }
        }
      rebuilder <<tempvec2<<" #numbers for year Ydeclare: "<<Rebuild_Ydecl<<" sex: "<<gg<< endl;
      if(mccounter==1) rebuild_dat<<tempvec2<< endl;
      }

      k=endyr;
      if(Rebuild_Yinit>k) k=Rebuild_Yinit;

//f.  Blank line.
      rebuilder <<"R0 "<<years<< " #years"<<endl;

//g. recruitment
        rebuilder << use_rec(styr-2)<<" "<<use_rec(styr,k) << " #Recruits"<<endl;

//h. spawnbio
        rebuilder << Spbio_tot(styr-2)<<" "<<Spbio_tot(styr,k) <<" #SpawnBio"<<endl;

//i. steepness; SigmaR; rho
      rebuilder << SR_parm(2) <<" "<< SR_parm(3) <<" "<< SR_parm(6) <<" # spawn-recr steepness, sigmaR, autocorr"<< endl;

    if(mccounter==1)
      {
      rebuild_dat<<"# Year for Tmin Age-structure (set to Ydecl by SS2)"<<endl<<Rebuild_Ydecl<<endl;

      rebuild_dat<<"# Number of simulations"<<endl<<1000<<endl;
      rebuild_dat<<"#  recruitment and biomass"<<endl<<"# Number of historical assessment years"<<endl<<k-styr+2<<endl;
      rebuild_dat<<"# Historical data"<<endl<<"# year recruitment spawner in B0 in R project in R/S project"<<endl;
      rebuild_dat<<styr-1<<" "<<years;
      if(Rebuild_Yinit>endyr) rebuild_dat<<" "<<Rebuild_Yinit;
      rebuild_dat<<" #years (with first value representing R0)"<<endl;
      rebuild_dat<<use_rec(styr-2)<<" "<<use_rec(styr,k) <<" #recruits; first value is R0 (virgin)"<< endl;
      rebuild_dat<<Spbio_tot(styr-2)<<" "<<Spbio_tot(styr,k) <<" #spbio; first value is S0 (virgin)"<< endl;
      rebuild_dat<<1<<" ";
      for(y=styr;y<=k;y++) rebuild_dat<<0<<" ";
      rebuild_dat<<" # in Bzero"<<endl;
      rebuild_dat<<0<<" ";
      for(y=styr;y<=k-3;y++) rebuild_dat<<1<<" ";
      rebuild_dat<<" 0 0 0 # in R project"<<endl;
      rebuild_dat<<0<<" ";
      for(y=styr;y<=k-3;y++) rebuild_dat<<1<<" ";
      rebuild_dat<<" 0 0 0 # in R/S project"<<endl;

      rebuild_dat<<"# Number of years with pre-specified catches"<<endl<<0<<endl;

      rebuild_dat<<"# catches for years with pre-specified catches go next"<<endl;

      rebuild_dat<<"# Number of future recruitments to override"<<endl<<0<<endl;

      rebuild_dat<<"# Process for overiding (-1 for average otherwise index in data list)"<<endl;
      rebuild_dat<<"# Which probability to product detailed results for (1=0.5; 2=0.6; etc.)"<<endl<<3<<endl;
      rebuild_dat<<"# Steepness sigma-R Auto-correlation"<<endl<<SR_parm(2) <<" "<< SR_parm(3) <<" "<< 0 << endl;
      rebuild_dat<<"# Target SPR rate (FMSY Proxy); manually change to SPR_MSY if not using SPR_target"<<endl<<SPR_target<<endl;
      rebuild_dat<<"# Target SPR information: Use (1=Yes) and power"<<endl<<0<<" "<<20<<endl;
      rebuild_dat<<"# Discount rate (for cumulative catch)"<<endl<<0.1<<endl;
      rebuild_dat<<"# Truncate the series when 0.4B0 is reached (1=Yes)"<<endl<<0<<endl;
      rebuild_dat<<"# Set F to FMSY once 0.4B0 is reached (1=Yes)"<<endl<<0<<endl;
      rebuild_dat<<"# Percentage of FMSY which defines Ftarget"<<endl<<0.75<<endl;
      rebuild_dat<<"# Maximum possible F for projection (-1 to set to FMSY)"<<endl<<-1<<endl;
      rebuild_dat<<"# Conduct MacCall transition policy (1=Yes)"<<endl<<0<<endl;
      rebuild_dat<<"# Defintion of recovery (1=now only;2=now or before)"<<endl<<2<<endl;
      rebuild_dat<<"# Results for rec probs by Tmax (1) or 0.5 prob for various Ttargets (2)"<<endl<<1<<endl;
      rebuild_dat<<"# Definition of the 40-10 rule"<<endl<<10<<" "<<40<<endl;
      rebuild_dat<<"# Produce the risk-reward plots (1=Yes)"<<endl<<0<<endl;
      rebuild_dat<<"# Calculate coefficients of variation (1=Yes)"<<endl<<0<<endl;
      rebuild_dat<<"# Number of replicates to use"<<endl<<10<<endl;
      rebuild_dat<<"# Random number seed"<<endl<<-99004<<endl;
      rebuild_dat<<"# Conduct projections for multiple starting values (0=No;else yes)"<<endl<<0<<endl;
      rebuild_dat<<"# File with multiple parameter vectors "<<endl<<"rebuild.ss2"<<endl;
      rebuild_dat<<"# Number of parameter vectors: value is placeholder only, user needs to change it"<<endl<<"1"<<endl;
      rebuild_dat<<"# User-specific projection (1=Yes); Output replaced (1->9)"<<endl<<"0  5  0  0.1"<<endl;
      rebuild_dat<<"# Catches and Fs (Year; 1/2/3 (F or C or SPR); value); Final row is -1"<<endl<<k<<" 1 1"<<endl
        <<"-1 -1 -1"<<endl;
      tempvec(1,Nfleet)=colsum(Input_ForeRate);
      rebuild_dat<<"# Split of Fs"<<endl<<Rebuild_Yinit;
      for(f=1;f<=Nfleet;f++)
        {
        if(tempvec(f)>0.) rebuild_dat<<" "<<tempvec(f);
        }
      rebuild_dat<<endl;
      rebuild_dat<<"-1 ";
      for(f=1;f<=Nfleet;f++)
        {if(tempvec(f)>0.) rebuild_dat<<" 99 ";}
      rebuild_dat<<endl<<"# Yrs to define T_target for projection type 4 "<<endl;
      rebuild_dat<<endyr+6<<" "<<endyr+7<<" "<<endyr+8<<" "<<endyr+9<<" "<<endyr+10<<" "<<endl;
      rebuild_dat<<"# Year for probability of recovery"<<endl<<endyr+10<<endl;
      rebuild_dat<<"# Time varying weight-at-age (1=Yes;0=No)"<<endl<<0<<endl;
      rebuild_dat<<"# File with time series of weight-at-age data"<<endl<<"none"<<endl;
      rebuild_dat<<"# Use bisection (0) or linear interpolation (1)"<<endl<<1<<endl;
      rebuild_dat<<"# Target Depletion"<<endl<<0.4<<endl;
      rebuild_dat<<"# Project with Historical recruitments when computing Tmin (1=Yes)"<<endl<<0<<endl;
      rebuild_dat<<"# CV of implementation error"<<endl<<0<<endl;
      }


//  end output of rebuilding quantities

//********************************************************************
//  ProgLabel_9000_FUNCTION write_nudata
FUNCTION write_nudata
//  code for multinomial distribution developed by Ian Stewart, Oct 2005
  random_number_generator radm(long(time(&finish)));

  dvector temp_mult(1,1000);
  dvector temp_probs(1,nlen_bin2);
  int compindex;
  dvector temp_probs2(1,n_abins2);
  int Nudat;
//  create bootstrap data files; except first file just replicates the input
  for(i=1;i<=1234;i++) temp = randn(radm);
  cout << " N_nudata: " << N_nudata << endl;
  ofstream report1("Data.SS_New");

  report1  << "#_Number_of_datafiles: " << N_nudata << endl;
  for(Nudat=1;Nudat<=N_nudata;Nudat++)
  {
  if(Nudat==1)
  {
    report1<<Data_Comments<<endl;
    report1 << "#_observed data: "<< endl;
  }
  else if(Nudat==2)
  {report1 << "#_expected values with no error added " << endl;}
  else
  {report1 << "#_bootstrap file: " << Nudat-2 << endl;}

  report1 << styr << " #_styr"<<endl;
  report1 << endyr <<" #_endyr"<< endl;
  report1 << nseas <<" #_nseas"<< endl;
  report1 << 12.*seasdur<<" #_months/season"<< endl;

  report1 << spawn_seas <<" #_spawn_seas"<< endl;
  report1 << Nfleet<<" #_Nfleet"<< endl;
  report1 << Nsurvey<<" #_Nsurveys"<< endl;
  report1 << pop<<" #_N_areas"<<endl;
  report1 << fleetnameread<<endl;
  report1 << surveytime<<" #_surveytiming_in_season"<<endl;
  report1 << fleet_area<<" #_area_assignments_for_each_fishery_and_survey"<<endl;
  report1 << catchunits<<" #_units of catch:  1=bio; 2=num"<<endl;
  report1 << catch_se_rd<<" #_se of log(catch) only used for init_eq_catch and for Fmethod 2 and 3"<<endl;
  report1 << gender<<" #_Ngenders"<< endl;
  report1 << nages<<" #_Nages"<< endl;

  report1 << obs_equ_catch<<" #_init_equil_catch_for_each_fishery"<<endl;
  report1 << N_ReadCatch<<" #_N_lines_of_catch_to_read"<<endl;
  report1 << "#_catch_biomass(mtons):_columns_are_fisheries,year,season"<<endl;
  report1 << catch_bioT<< endl << endl;

  if(Nudat==1)  // report back the input data
  {
  report1 << nobs_rd <<" #_N_cpue_and_surveyabundance_observations"<< endl;
  report1 << "#_year seas index obs se(log)"<<endl;
  if(nobs_rd>0)
  for (i=1;i<=nobs_rd;i++)
  {
    f=indexdata(i,3);
    report1 << indexdata(i)<<" # "<<fleetname(f)<<endl;
  }

  report1  <<endl<< disc_type <<" #_discard_type (1=bio or num; 2=fraction)"<< endl << nobs_disc_rd <<" #_N_discard_obs"<< endl;
  if(nobs_disc_rd>0)
  {
  report1 << "#_year seas index obs cv"<<endl;
  for (i=1;i<=nobs_disc_rd;i++)
  {
    f=discdata(i,3);
   report1 << discdata(i)<<" # "<<fleetname(f)<<endl;
   }
   }

  report1 <<endl<< nobs_mnwt_rd <<" #_N_meanbodywt_obs"<< endl;
  if(nobs_mnwt_rd>0)
   {
    report1 << "#_year seas index part obs cv"<<endl;
    for (i=1;i<=nobs_mnwt_rd;i++)
    {
      f=mnwtdata1(i,3);
      report1 << mnwtdata1(i)<<" # "<<fleetname(f)<<endl;
    }
   }

  report1<<endl<<LenBin_option<<" # length bin method: 1=use databins; 2=generate from binwidth,min,max below; 3=read vector"<<endl;
  if(LenBin_option==1)
  {report1<<"# no additional input for option 1"<<endl;
    report1<<"# read binwidth, minsize, lastbin size for option 2"<<endl;
    report1<<"# read N poplen bins, then vector of bin lower boundaries, for option 3"<<endl;}
  else if(LenBin_option==2)
  {
    report1<<binwidth2<<" # binwidth for population size comp "<<endl;
    report1<<minLread<<" # minimum size in the population (lower edge of first bin and size at age 0.00) "<<endl;
    report1<<maxLread<<" # maximum size in the population (lower edge of last bin) "<<endl;
  }
  else
  {
    report1<<nlength<<" # number of population size bins "<<endl;
    report1<<len_bins<<endl;
  }

  report1<<endl<<min_tail<<" #_comp_tail_compression"<<endl;
  report1<<min_comp<<" #_add_to_comp"<<endl;
  report1<<CombGender_l<<" #_combine males into females at or below this bin number"<<endl;
  report1<<nlen_bin<<" #_N_LengthBins"<<endl<<len_bins_dat<<endl;

  report1<<nobsl_rd<<" #_N_Length_obs"<<endl;
  report1<<"#Yr Seas Flt/Svy Gender Part Nsamp datavector(female-male)"<<endl;
  if(nobsl_rd>0) report1<<lendata<<endl;

   report1 <<endl<<n_abins<<" #_N_age_bins"<<endl;
  if(n_abins>0) report1<<age_bins1<<endl;
  report1 << N_ageerr <<" #_N_ageerror_definitions"<< endl;
  if(N_ageerr>0) report1 << age_err << endl;

  report1 <<nobsa_rd<<" #_N_Agecomp_obs"<<endl;
  report1<<Lbin_method<<" #_Lbin_method: 1=poplenbins; 2=datalenbins; 3=lengths"<<endl;
  report1<<CombGender_a<<" #_combine males into females at or below this bin number"<<endl;
  report1<<"#Yr Seas Flt/Svy Gender Part Ageerr Lbin_lo Lbin_hi Nsamp datavector(female-male)"<<endl;
   if(nobsa_rd>0) report1<<agedata<<endl;

  report1 <<endl<<nobs_ms_rd<<" #_N_MeanSize-at-Age_obs"<<endl;
  report1<<"#Yr Seas Flt/Svy Gender Part Ageerr Ignore datavector(female-male)"<<endl;
  report1<<"#                                          samplesize(female-male)"<<endl;
   if(nobs_ms_rd>0) report1<<sizeagedata<<endl;

    report1 << endl << N_envvar<<" #_N_environ_variables"<<endl<<N_envdata<<" #_N_environ_obs"<<endl;
    if(N_envdata>0) report1<<env_temp<<endl;

  report1<<WtFreq_Nmeth<<" # N sizefreq methods to read "<<endl;
  if(WtFreq_Nmeth>0)
  {
    report1<<WtFreq_Nbins<<" #Sizefreq N bins per method"<<endl;
    report1<<WtFreq_units<<" #Sizetfreq units(bio/num) per method"<<endl;
    report1<<WtFreq_scale<<" #Sizefreq scale(kg/lbs/cm/inches) per method"<<endl;
    report1<<WtFreq_mincomp<<" #Sizefreq mincomp per method "<<endl;
    report1<<WtFreq_nobs<<" #Sizefreq N obs per method"<<endl;
    report1<<"#_Sizefreq bins "<<endl;
    for(i=1;i<=WtFreq_Nmeth;i++) {report1<<WtFreq_Omit_Small(i)*WtFreq_bins1(i,1)<<WtFreq_bins1(i)(2,WtFreq_Nbins(i))<<endl;}
    report1<<"#_Year season Fleet Partition Gender SampleSize <data> "<<endl<<WtFreq_obs1<<endl;
 }


    report1<<endl<<0<<" # no tag data "<<endl;
    report1<<endl<<0<<" # no morphcomp data "<<endl;
    report1 << endl << "999" << endl << endl;

  }

  else if(Nudat==2)  // report expected value with no added error
  {
  report1 << nobs <<" #_N_cpue_and_surveyabundance_observations"<< endl;
  report1 << "#_year seas index obs se(log)"<<endl;
  if(nobs>0)
  for(f=1;f<=Ntypes;f++)
  for (i=1;i<=nyr_cr(f);i++)
    {
    s=yr_cr(f,i)+1-styr-(yr_cr_y(f,i)-styr)*nseas;
    report1 << yr_cr_y(f,i)<<" "<<s<<" "<<f<<" ";
    if(obs_cr(f,i) > 0 )
      {
        report1 << mfexp(exp_cr(f,i)+log_q_cr(f,i));    //  adjusts the sd by the df sample size
      }
      else
      {
      report1 << obs_cr(f,i);
      }
    report1 <<" "<<cv_cr(f,i)<<" #_orig_obs: "<<obs_cr(f,i)<<" "<<fleetname(f)<<endl;
    }

  report1  <<endl<< disc_type <<" #_discard_type (1=bio or num; 2=fraction)"<< endl << nobs_disc <<" #_N_discard_obs"<< endl;
  if(nobs_disc>0)
  {
  report1 << "#_year seas index obs cv"<<endl;
  for(f=1;f<=Ntypes;f++)
  if(nyr_disc(f)>0)
  for (i=1;i<=nyr_disc(f);i++)
  {
   s=yr_disc(f,i)+1-styr-(yr_disc_y(f,i)-styr)*nseas;
   report1 << yr_disc_y(f,i)<<" "<<s<<" "<<f<<" ";
   if(obs_disc(f,i) >= 0.0 )
     {report1 << exp_disc(f,i);}
   else
   { report1 << obs_disc(f,i);}
   report1 << " "<< cv_disc(f,i)<<" #_orig_obs: "<<obs_disc(f,i)<<endl;
   }}

  report1 <<endl<< nobs_mnwt <<" #_N_meanbodywt_obs"<< endl;
  if(nobs_mnwt>0)
   {report1 << "#_year seas index part obs cv"<<endl;
   for(i=1;i<=nobs_mnwt;i++)
    {
     report1 << mnwtdata(1,i)<<" "<<mnwtdata(2,i)<<" "<<mnwtdata(3,i)<<" "<<mnwtdata(4,i)<<" "<<
     exp_mnwt(i)<<" "<<mnwtdata(6,i)<<" #_orig_obs: "<<mnwtdata(5,i)<< endl;
    }
   }

  report1<<endl<<LenBin_option<<" # length bin method: 1=use databins; 2=generate from binwidth,min,max below; 3=read vector"<<endl;
  if(LenBin_option==1)
  {report1<<"# no additional input for option 1"<<endl;
    report1<<"# read binwidth, minsize, lastbin size for option 2"<<endl;
    report1<<"# read N poplen bins, then vector of bin lower boundaries, for option 3"<<endl;}
  else if(LenBin_option==2)
  {
    report1<<binwidth2<<" # binwidth for population size comp "<<endl;
    report1<<minLread<<" # minimum size in the population (lower edge of first bin and size at age 0.00) "<<endl;
    report1<<maxLread<<" # maximum size in the population (lower edge of last bin) "<<endl;
  }
  else
  {
    report1<<nlength<<" # number of population size bins "<<endl;
    report1<<len_bins<<endl;
  }

  report1<<endl<<min_tail<<" #_comp_tail_compression"<<endl;
  report1<<min_comp<<" #_add_to_comp"<<endl;
  report1<<CombGender_l<<" #_combine males into females at or below this bin number"<<endl;
  report1<<nlen_bin<<" #_N_LengthBins"<<endl<<len_bins_dat<<endl;
  report1<<sum(nyr_l)<<" #_N_Length_obs"<<endl;
  report1<<"#Yr Seas Flt/Svy Gender Part Nsamp datavector(female-male)"<<endl;
   for(f=1;f<=Ntypes;f++)
    {
    if(nyr_l(f)>0)
    {
     for(i=1;i<=nyr_l(f);i++)
     {
      if(nsamp_l(f,i)>0) // do only if this was a real observation
      {
       k=1000;  if(nsamp_l(f,i)<k) k=nsamp_l(f,i);
       exp_l_temp_dat = nsamp_l(f,i)*value(exp_l(f,i));
      }
      else
      {exp_l_temp_dat = obs_l(f,i);}
     report1 << header_l(f,i)<<" "<<gen_l(f,i)<<" "<<mkt_l(f,i)<<" "<<nsamp_l(f,i)<<" "<<nsamp_l(f,i)*exp_l_temp_dat<<endl;
    }}}

   report1 <<endl<<n_abins<<" #_N_age_bins"<<endl;
  if(n_abins>0) report1<<age_bins1<<endl;
  report1 << N_ageerr <<" #_N_ageerror_definitions"<< endl;
  if(N_ageerr>0) report1 << age_err << endl;

  report1 <<nobsa<<" #_N_Agecomp_obs"<<endl;
  report1<<Lbin_method<<" #_Lbin_method: 1=poplenbins; 2=datalenbins; 3=lengths"<<endl;
  report1<<CombGender_a<<" #_combine males into females at or below this bin number"<<endl;
  report1<<"#Yr Seas Flt/Svy Gender Part Ageerr Lbin_lo Lbin_hi Nsamp datavector(female-male)"<<endl;
   if(nobsa>0)
   for(f=1;f<=Ntypes;f++)
    {
    if(nyr_a(f)>=1)
    {
     for(i=1;i<=nyr_a(f);i++)
     {
     if(nsamp_a(f,i)>0) // if real observation
     {
      k=1000;  if(nsamp_a(f,i)<k) k=nsamp_a(f,i);  // note that nsamp is adjusted by var_adjust, so var_adjust
                                                   // should be reset to 1.0 in control files that read the nudata.dat files
      exp_a_temp = nsamp_a(f,i)*value(exp_a(f,i));
     }
     else
     {exp_a_temp = obs_a(f,i);}
    report1 << header_a(f,i)(1,8)<<" "<<nsamp_a(f,i)<<" "<<nsamp_a(f,i)*exp_a_temp<<endl;
    }
    }
    }
  report1 <<endl<<nobs_ms<<" #_N_MeanSize-at-Age_obs"<<endl;
  report1<<"#Yr Seas Flt/Svy Gender Part Ageerr Ignore datavector(female-male)"<<endl;
  report1<<"#                                          samplesize(female-male)"<<endl;
   if(nobs_ms>0)
   for(f=1;f<=Ntypes;f++)
    {
    if(nyr_ms(f)>0)
    {
     for(i=1;i<=nyr_ms(f);i++)
     {
     report1 << header_ms(f,i);
     for(a=1;a<=n_abins2;a++)
     {
     report1 << " " ;
         if(obs_ms_n(f,i,a)>0)
          {temp=exp_ms(f,i,a);
          if(temp<=0.) {temp=0.0001;}
          report1 << temp;}
         else
             {report1 << obs_ms(f,i,a) ;}
         }

     report1 << endl<< elem_prod(obs_ms_n(f,i),obs_ms_n(f,i)) << endl;
      }
      }
      }
    report1 << endl << N_envvar<<" #_N_environ_variables"<<endl<<N_envdata<<" #_N_environ_obs"<<endl;
    if(N_envdata>0) report1<<env_temp<<endl;

  report1<<WtFreq_Nmeth<<" # N sizefreq methods to read "<<endl;
  if(WtFreq_Nmeth>0)
  {
    report1<<WtFreq_Nbins<<" #Sizefreq N bins per method"<<endl;
    report1<<WtFreq_units<<" #Sizetfreq units(bio/num) per method"<<endl;
    report1<<WtFreq_scale<<" #Sizefreq scale(kg/lbs/cm/inches) per method"<<endl;
    report1<<WtFreq_mincomp<<" #Sizefreq mincomp per method "<<endl;
    report1<<WtFreq_nobs<<" #Sizefreq N obs per method"<<endl;
    report1<<"#_Sizefreq bins "<<endl;
    for(i=1;i<=WtFreq_Nmeth;i++) {report1<<WtFreq_Omit_Small(i)*WtFreq_bins1(i,1)<<WtFreq_bins1(i)(2,WtFreq_Nbins(i))<<endl;}
    report1<<"#_Year season Fleet Partition Gender SampleSize <data> "<<endl;
    for(iobs=1;iobs<=WtFreq_totobs;iobs++)
    {
      y=WtFreq_obs_hdr(iobs,1);
      s=WtFreq_obs_hdr(iobs,2);
      f=WtFreq_obs_hdr(iobs,3);
      gg=WtFreq_obs_hdr(iobs,4);  // gender
      k=WtFreq_obs_hdr(iobs,6);
      if(k>0)  // flag for date range in bounds
      {
        report1<<WtFreq_obs1(iobs)(1,7)<<" "<<WtFreq_exp(iobs)<<endl;
      }
      else
      {
        report1<<WtFreq_obs1(iobs)<<endl;
      }
    }
  }

    report1<<endl<<0<<" # no tag data "<<endl;
    report1<<endl<<0<<" # no morphcomp data "<<endl;
    report1 << endl << "999" << endl << endl;

  }

  else     // add error to expected value
  {
  report1 << nobs <<" #_N_cpue_and_surveyabundance_observations"<< endl;
  report1 << "#_year seas index obs se(log)"<<endl;
  if(nobs>0)
  for(f=1;f<=Ntypes;f++)
  for (i=1;i<=nyr_cr(f);i++)
    {
    s=yr_cr(f,i)+1-styr-(yr_cr_y(f,i)-styr)*nseas;
    report1 << yr_cr_y(f,i)<<" "<<s<<" "<<f<<" ";
    if(obs_cr(f,i) > 0 )
      {
      if(Q_setup(f,6)==0)
        {
         report1 << mfexp(exp_cr(f,i)+log_q_cr(f,i)+ randn(radm)*sd_cr(f,i) );    //  uses sd_cr, not cv_cr to include both effect of input var_adjust and extra_sd
       }
      else
        {
        temp = sqrt( (Q_setup(f,6)+1.)/Q_setup(f,6));  // where df=Q_setup(f,6)
        report1 << mfexp(exp_cr(f,i)+log_q_cr(f,i)+ randn(radm)*sd_cr(f,i)*temp );    //  adjusts the sd by the df sample size
        }
      }
      else
      {
      report1 << obs_cr(f,i);
      }
    report1 <<" "<<cv_cr(f,i)<<" #_orig_obs: "<<obs_cr(f,i)<<" "<<fleetname(f)<<endl;
    }

  report1  <<endl<< disc_type <<" #_discard_type (1=bio or num; 2=fraction)"<< endl << nobs_disc <<" #_N_discard_obs"<< endl;
  if(nobs_disc>0)
  {
  report1 << "#_year seas index obs cv"<<endl;
  for(f=1;f<=Ntypes;f++)
  if(nyr_disc(f)>0)
  for (i=1;i<=nyr_disc(f);i++)
  {
   s=yr_disc(f,i)+1-styr-(yr_disc_y(f,i)-styr)*nseas;
   report1 << yr_disc_y(f,i)<<" "<<s<<" "<<f<<" ";
   if(obs_disc(f,i) >= 0.0)
     { temp=exp_disc(f,i) + randn(radm)*cv_disc(f,i)*sqrt((DF_disc+1.)/DF_disc) * exp_disc(f,i); if(temp<=0.){temp=0.0001;} report1 << temp;}
   else
   { report1 << obs_disc(f,i);}
   report1 << " "<< cv_disc(f,i)<<" #_orig_obs: "<<obs_disc(f,i)<<endl;
   }}

  report1 <<endl<< nobs_mnwt <<" #_N_meanbodywt_obs"<< endl;
  if(nobs_mnwt>0)
   {report1 << "#_year seas index part obs cv"<<endl;
   for(i=1;i<=nobs_mnwt;i++)
    {temp=exp_mnwt(i)+randn(radm)*mnwtdata(6,i)*sqrt((DF_bodywt+1.)/DF_bodywt) *exp_mnwt(i);
     if(temp<=0.0) {temp=0.0001;}
     report1 << mnwtdata(1,i)<<" "<<mnwtdata(2,i)<<" "<<mnwtdata(3,i)<<" "<<mnwtdata(4,i)<<" "<<
     temp<<" "<<mnwtdata(6,i)<<" #_orig_obs: "<<mnwtdata(5,i)<< endl;
    }
   }

  report1<<endl<<LenBin_option<<" # length bin method: 1=use databins; 2=generate from binwidth,min,max below; 3=read vector"<<endl;
  if(LenBin_option==1)
  {report1<<"# no additional input for option 1"<<endl;
    report1<<"# read binwidth, minsize, lastbin size for option 2"<<endl;
    report1<<"# read N poplen bins, then vector of bin lower boundaries, for option 3"<<endl;}
  else if(LenBin_option==2)
  {
    report1<<binwidth2<<" # binwidth for population size comp "<<endl;
    report1<<minLread<<" # minimum size in the population (lower edge of first bin and size at age 0.00) "<<endl;
    report1<<maxLread<<" # maximum size in the population (lower edge of last bin) "<<endl;
  }
  else
  {
    report1<<nlength<<" # number of population size bins "<<endl;
    report1<<len_bins<<endl;
  }

  report1<<endl<<min_tail<<" #_comp_tail_compression"<<endl;
  report1<<min_comp<<" #_add_to_comp"<<endl;
  report1<<CombGender_l<<" #_combine males into females at or below this bin number"<<endl;
  report1<<nlen_bin<<" #_N_LengthBins"<<endl<<len_bins_dat<<endl;
  report1<<sum(nyr_l)<<" #_N_Length_obs"<<endl;
  report1<<"#Yr Seas Flt/Svy Gender Part Nsamp datavector(female-male)"<<endl;
   for(f=1;f<=Ntypes;f++)
    {
    if(nyr_l(f)>0)
    {
     for(i=1;i<=nyr_l(f);i++)
     {
      if(nsamp_l(f,i)>0) // do only if this was a real observation
      {
       k=1000;  if(nsamp_l(f,i)<k) k=nsamp_l(f,i);
       exp_l_temp_dat.initialize();
       temp_probs = value(exp_l(f,i));
       temp_mult.fill_multinomial(radm,temp_probs);  // create multinomial draws with prob = expected values
       for (compindex=1; compindex<=k; compindex++) // cumulate the multinomial draws by index in the new data
       {exp_l_temp_dat(temp_mult(compindex)) += 1.0;}
      }
      else
      {exp_l_temp_dat = obs_l(f,i);}
     report1 << header_l(f,i)<<" "<<gen_l(f,i)<<" "<<mkt_l(f,i)<<" "<<nsamp_l(f,i)<<" "<<exp_l_temp_dat<<endl;
    }}}

   report1 <<endl<<n_abins<<" #_N_age_bins"<<endl;
  if(n_abins>0) report1<<age_bins1<<endl;
  report1 << N_ageerr <<" #_N_ageerror_definitions"<< endl;
  if(N_ageerr>0) report1 << age_err << endl;

  report1 <<nobsa<<" #_N_Agecomp_obs"<<endl;
  report1<<Lbin_method<<" #_Lbin_method: 1=poplenbins; 2=datalenbins; 3=lengths"<<endl;
  report1<<CombGender_a<<" #_combine males into females at or below this bin number"<<endl;
  report1<<"#Yr Seas Flt/Svy Gender Part Ageerr Lbin_lo Lbin_hi Nsamp datavector(female-male)"<<endl;
   if(nobsa>0)
   for(f=1;f<=Ntypes;f++)
    {
    if(nyr_a(f)>=1)
    {
     for(i=1;i<=nyr_a(f);i++)
     {
     if(nsamp_a(f,i)>0) // if real observation
     {
      k=1000;  if(nsamp_a(f,i)<k) k=nsamp_a(f,i);  // note that nsamp is adjusted by var_adjust, so var_adjust
                                                   // should be reset to 1.0 in control files that read the nudata.dat files
      exp_a_temp = 0.0;
      temp_probs2 = value(exp_a(f,i));
      temp_mult.fill_multinomial(radm,temp_probs2);
      for (compindex=1; compindex<=k; compindex++) // cumulate the multinomial draws by index in the new data
      {exp_a_temp(temp_mult(compindex)) += 1.0;}
     }
     else
     {exp_a_temp = obs_a(f,i);}
    report1 << header_a(f,i)(1,8)<<" "<<nsamp_a(f,i)<<" "<<exp_a_temp<<endl;
    }
    }
    }
  report1 <<endl<<nobs_ms<<" #_N_MeanSize-at-Age_obs"<<endl;
  report1<<"#Yr Seas Flt/Svy Gender Part Ageerr Ignore datavector(female-male)"<<endl;
  report1<<"#                                          samplesize(female-male)"<<endl;
   if(nobs_ms>0)
   for(f=1;f<=Ntypes;f++)
    {
    if(nyr_ms(f)>0)
    {
     for(i=1;i<=nyr_ms(f);i++)
     {
     report1 << header_ms(f,i);
     for(a=1;a<=n_abins2;a++)
     {
     report1 << " " ;
         if(obs_ms_n(f,i,a)>0)
          {temp=exp_ms(f,i,a)+randn(radm)*exp_ms_sq(f,i,a)/obs_ms_n(f,i,a);
          if(temp<=0.) {temp=0.0001;}
          report1 << temp;}
         else
             {report1 << exp_ms(f,i,a) ;}
         }

     report1 << endl<< elem_prod(obs_ms_n(f,i),obs_ms_n(f,i)) << endl;
      }
      }
      }
    report1 << endl << N_envvar<<" #_N_environ_variables"<<endl<<N_envdata<<" #_N_environ_obs"<<endl;
    if(N_envdata>0) report1<<env_temp<<endl;

  report1<<WtFreq_Nmeth<<" # N sizefreq methods to read "<<endl;
  if(WtFreq_Nmeth>0)
  {
    report1<<WtFreq_Nbins<<" #Sizefreq N bins per method"<<endl;
    report1<<WtFreq_units<<" #Sizetfreq units(bio/num) per method"<<endl;
    report1<<WtFreq_scale<<" #Sizefreq scale(kg/lbs/cm/inches) per method"<<endl;
    report1<<WtFreq_mincomp<<" #Sizefreq mincomp per method "<<endl;
    report1<<WtFreq_nobs<<" #Sizefreq N obs per method"<<endl;
    report1<<"#_Sizefreq bins "<<endl;
    for(i=1;i<=WtFreq_Nmeth;i++) {report1<<WtFreq_Omit_Small(i)*WtFreq_bins1(i,1)<<WtFreq_bins1(i)(2,WtFreq_Nbins(i))<<endl;}
    report1<<"#_Year season Fleet Partition Gender SampleSize <data> "<<endl;
    j=2*max(WtFreq_Nbins);
    dvector temp_probs3(1,j);
    dvector WtFreq_newdat(1,j);
    for(iobs=1;iobs<=WtFreq_totobs;iobs++)
    {
      k=WtFreq_obs_hdr(iobs,6);  // medthod
      if(k>0)  // flag for date range in bounds
      {

      if(WtFreq_obs1(iobs,7)>0.) // do only if this was a real observation
      {
       j=1000;  if(WtFreq_obs1(iobs,7)<j) j=WtFreq_obs1(iobs,7);
       WtFreq_newdat.initialize();
       temp_probs3(1,WtFreq_Setup2(iobs)) = value(WtFreq_exp(iobs));
//       cout<<temp_probs3<<endl;
       temp_mult.fill_multinomial(radm,temp_probs3(1,WtFreq_Setup2(iobs)));  // create multinomial draws with prob = expected values
//       cout<<temp_mult<<endl;
       for (compindex=1; compindex<=j; compindex++) // cumulate the multinomial draws by index in the new data
       {WtFreq_newdat(temp_mult(compindex)) += 1.0;}
//       cout<<WtFreq_newdat<<endl;
      }

        report1<<WtFreq_obs1(iobs)(1,7)<<" "<<WtFreq_newdat(1,WtFreq_Setup2(iobs))<<endl;
      }
      else
      {
        report1<<WtFreq_obs1(iobs)<<endl;
      }
    }
  }
    report1<<endl<<0<<" # no tag data "<<endl;
    report1<<endl<<0<<" # no morphcomp data "<<endl;
    report1 << endl << "999" << endl << endl;
  }
    }
  report1 << "ENDDATA" << endl;

//***********************************************************************************
//  ProgLabel_9100_FUNCTION write_nucontrol  write new control file
FUNCTION write_nucontrol

  cout<<" Write new starter file "<<endl;
  ofstream NuStart("Starter.SS_New");
  NuStart<<Starter_Comments<<endl;
  NuStart<<datfilename<<endl<<ctlfilename<<endl;
  NuStart<<readparfile<<" # 0=use init values in control file; 1=use ss3.par"<<endl;
  NuStart<<rundetail<<" # run display detail (0,1,2)"<<endl;
  NuStart<<reportdetail<<" # detailed age-structured reports in REPORT.SSO (0,1) "<<endl;
  NuStart<<docheckup<<" # write detailed checkup.sso file (0,1) "<<endl;
  NuStart<<Do_ParmTrace<<" # write parm values to ParmTrace.sso (0=no,1=good,active; 2=good,all; 3=every_iter,all_parms; 4=every,active)"<<endl;
  NuStart<<Do_CumReport<<" # write to cumreport.sso (0=no,1=like&timeseries; 2=add survey fits)"<<endl;
  NuStart<<Do_all_priors<<" # Include prior_like for non-estimated parameters (0,1) "<<endl;
  NuStart<<SoftBound<<" # Use Soft Boundaries to aid convergence (0,1) (recommended)"<<endl;
  NuStart<<N_nudata<<" # Number of bootstrap datafiles to produce"<<endl;
  NuStart<<Turn_off_phase<<" # Turn off estimation for parameters entering after this phase"<<endl;
  NuStart<<burn_intvl<<" # MCMC burn interval"<<endl;
  NuStart<<thin_intvl<<" # MCMC thin interval"<<endl;
  NuStart<<jitter<<" # jitter initial parm value by this fraction"<<endl;
  NuStart<<STD_Yr_min<<" # min yr for sdreport outputs (-1 for styr)"<<endl;
  NuStart<<STD_Yr_max<<" # max yr for sdreport outputs (-1 for endyr; -2 for endyr+Nforecastyrs"<<endl;
  NuStart<<N_STD_Yr_RD<<" # N individual STD years "<<endl;
  NuStart<<"#vector of year values "<<endl<<STD_Yr_RD<<endl;

  NuStart<<final_conv<<" # final convergence criteria (e.g. 1.0e-04) "<<endl;
  NuStart<<retro_yr-endyr<<" # retrospective year relative to end year (e.g. -4)"<<endl;
  NuStart<<Smry_Age<<" # min age for calc of summary biomass"<<endl;
  NuStart<<depletion_basis<<" # Depletion basis:  denom is: 0=skip; 1=rel X*B0; 2=rel X*Bmsy; 3=rel X*B_styr"<<endl;
  NuStart<<depletion_level<<" # Fraction (X) for Depletion denominator (e.g. 0.4)"<<endl;
  NuStart<<SPR_reporting<<" # SPR_report_basis:  0=skip; 1=(1-SPR)/(1-SPR_tgt); 2=(1-SPR)/(1-SPR_MSY); 3=(1-SPR)/(1-SPR_Btarget); 4=rawSPR"<<endl;
  NuStart<<F_reporting<<" # F_report_units: 0=skip; 1=exploitation(Bio); 2=exploitation(Num); 3=sum(Frates)"<<endl;
  NuStart<<F_report_basis<<" # F_report_basis: 0=raw; 1=F/Fspr; 2=F/Fmsy ; 3=F/Fbtgt"<<endl;
  NuStart<<999<<" # check value for end of file"<<endl;

  cout<<" Write new forecast file "<<endl;
  ofstream NuFore("Forecast.SS_New");
  NuFore<<Forecast_Comments<<endl;
  NuFore<<Do_Forecast<<" # Forecast: 0=none; 1=F(SPR); 2=F(MSY) 3=F(Btgt); 4=F(endyr); 5=Ave F (enter yrs); 6=read Fmult"<<endl;
  NuFore<<"# -4  # first year for recent ave F for option 5 (not yet implemented)"<<endl;
  NuFore<<"# -1  # last year for recent ave F for option 5 (not yet implemented)"<<endl;
  NuFore<<"# 0.74  # F multiplier for option 6 (not yet implemented "<<endl;
  NuFore<<Fore_Sel_yr1a<<" # first year to use for averaging selex to use in forecast (e.g. 2004; or use -x to be rel endyr)"<<endl;
  NuFore<<Fore_Sel_yr2a<<" # last year to use for averaging selex to use in forecast "<<endl;
  NuFore<<Do_Benchmark<<" # Benchmarks: 0=skip; 1=calc F_spr,F_btgt,F_msy "<<endl;
  NuFore<<Do_MSY<<" # MSY: 1= set to F(SPR); 2=calc F(MSY); 3=set to F(Btgt); 4=set to F(endyr) "<<endl;
  NuFore<<SPR_target<<" # SPR target (e.g. 0.40)"<<endl;
  NuFore<<BTGT_target<<" # Biomass target (e.g. 0.40)"<<endl;
  NuFore<<N_Fore_Yrs<<" # N forecast years "<<endl;
  NuFore<<Do_Fore_Adv_Opt<<" # read 10 advanced options"<<endl;
  if(Do_Fore_Adv_Opt==1) {onenum=" ";} else {onenum="#";}
  NuFore<<onenum<<Do_Rebuilder<<" # Do West Coast gfish rebuilder output (0/1) "<<endl;
  NuFore<<onenum<<Rebuild_Ydecl<<" # Rebuilder:  first year catch could have been set to zero (Ydecl)(-1 to set to 1999)"<<endl;
  NuFore<<onenum<<Rebuild_Yinit<<" # Rebuilder:  year for current age structure (Yinit) (-1 to set to endyear+1)"<<endl;
  NuFore<<onenum<<HarvestPolicy<<" # Control rule method (1=west coast adjust catch; 2=adjust F) "<<endl;
  NuFore<<onenum<<H4010_top<<" # Control rule Biomass level for constant F (as frac of Bzero, e.g. 0.40) "<<endl;
  NuFore<<onenum<<H4010_bot<<" # Control rule Biomass level for no F (as frac of Bzero, e.g. 0.10) "<<endl;
  NuFore<<onenum<<H4010_scale<<" # Control rule fraction of Flimit (e.g. 0.75) "<<endl;
  NuFore<<onenum<<Max_Fore_Catch_Basis<<" # basis for max forecast catch by seas and area (0=none; 1=deadbio; 2=retainbio; 3=deadnum; 4=retainnum)"<<endl;
  NuFore<<onenum<<Do_Impl_Error<<" # 0= no implementation error; 1=use implementation error in forecast (not coded yet)"<<endl;
  NuFore<<onenum<<Impl_Error<<" # stddev of log(realized F/target F) in forecast (not coded yet)"<<endl;
  NuFore<<"# end of advanced options"<<endl;
  if(Max_Fore_Catch_Basis>0)
  {
    NuFore<<"# max forecast catch"<<endl<<"# rows are seasons, columns are areas"<<endl;
    for(s=1;s<=nseas;s++) {NuFore<<Max_Fore_Catch(s)<<endl;}
  }
  else
  {
    NuFore<<"# placeholder for max forecast catch by season and area"<<endl;
  }
  NuFore<<Fore_Rel_Harvest<<" # fleet allocation (in terms of F) (1=use endyr pattern, no read; 2=read below)"<<endl;
  for(s=1;s<=nseas;s++)
  {
    if(Fore_Rel_Harvest==1) NuFore<<"# ";
    NuFore<<ForeRatePattern(s)<<endl;
  }
  NuFore<<N_fore_catches<<" # Number of forecast catch levels to input (rest calc catch from forecast F "<<endl;
  if(N_fore_catches==0) NuFore<<"# ";
  NuFore<<ForeCatch_basis<<" # basis for input forecatch:  1=retained catch; 2=total dead catch"<<endl;
  NuFore<<"#Year Seas Fleet Catch "<<endl;
  NuFore<<Input_ForeCatch_1<<endl;
  NuFore<<endl<<999<<" # verify end of input "<<endl;

//**********************************************************
  cout<<" Write new control file "<<endl;
  ofstream report4("Control.SS_New");
  report4<<Control_Comments<<endl;
  report4 << "#_data_and_control_files: "<<datfilename<<" // "<<ctlfilename<<endl;
  report4<<"#_"<<version_info<<endl;
  report4 << N_GP << "  #_N_Growth_Patterns"<<endl;
  report4 << N_GP_sub << " #_N_Morphs_Within_GrowthPattern "<<endl;
  if(N_GP_sub==1) report4<<"#_Cond ";
  report4<<sd_ratio<<" #_Morph_between/within_stdev_ratio (no read if N_morphs=1)"<<endl;
  if(N_GP_sub==1) report4<<"#_Cond ";
  report4<<submorphdist(1,N_GP_sub)<<" #vector_Morphdist_(-1_in_first_val_gives_normal_approx)"<<endl;

  if(N_GP*nseas*pop==1)
  {
    report4<<endl<<"#_Cond 0  #  N recruitment designs goes here if N_GP*nseas*area>1"<<endl<<
                   "#_Cond 0  #  placeholder for recruitment interaction request"<<endl<<
                   "#_Cond 1 1 1  # example recruitment design element for GP=1, seas=1, area=1"<<endl;
  }
  else
  {
    report4<<recr_dist_read<<" #  number of recruitment assignments (overrides GP*area*seas parameter values) "<<endl<<
             recr_dist_inx<< " # recruitment interaction requested"<<endl<<
             "#GP seas area for each recruitment assignment"<<endl<<recr_dist_pattern_1<<endl;
  }

  if(pop==1)
  {report4<<endl<<"#_Cond 0 # N_movement_definitions goes here if N_areas > 1"<<endl
    <<"#_Cond 1.0 # first age that moves (real age at begin of season, not integer) also cond on do_migration>0"<<endl
    <<"#_Cond 1 1 1 2 4 10 # example move definition for seas=1, morph=1, source=1 dest=2, age1=4, age2=10"<<endl;}
  else
  {
    report4<<endl<<do_migration<<" #_N_movement_definitions"<<endl;
    if(do_migration>0)
    {
      report4<<migr_firstage<<" # first age that moves (real age at begin of season, not integer)"<<endl
      <<"# seas,GP,source_area,dest_area,minage,maxage"<<endl<<move_def<<endl;
    }
    else
    {
    report4<<"#_Cond 1.0 # first age that moves (real age at begin of season, not integer) if do_migration>0"<<endl
    <<"#_Cond 1 1 1 2 4 10 # example move definition for seas=1, GP=1, source=1 dest=2, age1=4, age2=10"<<endl;
    }
  }

  report4<<endl<<N_Block_Designs<<" #_Nblock_Patterns"<<endl;
  if(N_Block_Designs>0)
  {report4<<Nblk<<" #_blocks_per_pattern "<<endl<<"# begin and end years of blocks"<<endl<<Block_Design<<endl<<endl;}
  else
  {report4<<"#_Cond "<<0<<" #_blocks_per_pattern "<<endl<<"# begin and end years of blocks"<<endl<<endl;}


  report4<<fracfemale<<" #_fracfemale "<<endl;
  report4<<natM_type<<" #_natM_type:_0=1Parm; 1=N_breakpoints;_2=Lorenzen;_3=agespecific;_4=agespec_withseasinterpolate"<<endl;
    if(natM_type==1)
    {report4<<N_natMparms<<" #_N_breakpoints"<<endl<<NatM_break<<" # age(real) at M breakpoints"<<endl;}
    else if(natM_type==2)
    {report4<<natM_amin<<" #_reference age for Lorenzen M; read 1P per morph"<<endl;}
    else if(natM_type>=3)
    {report4<<" #_Age_natmort_by gender x growthpattern"<<endl<<Age_NatMort<<endl;}
    else
    {report4<<"  #_no additional input for selected M option; read 1P per morph"<<endl;}

    report4<<Grow_type<<" # GrowthModel: 1=vonBert with L1&L2; 2=Richards with L1&L2; 3=not implemented; 4=not implemented"<<endl;
    if(Grow_type<=2)
    {report4<<AFIX<<" #_Growth_Age_for_L1"<<endl<<AFIX2<<" #_Growth_Age_for_L2 (999 to use as Linf)"<<endl;}
    else
    {report4<<" #_No Growth_Age_for_L1 and L2 for grow_type 3 & 4"<<endl;}

    report4<<SD_add_to_LAA<<" #_SD_add_to_LAA (set to 0.1 for SS2 V1.x compatibility)"<<endl;   // constant added to SD length-at-age (set to 0.1 for compatibility with SS2 V1.x
    report4<<CV_depvar<<" #_CV_Growth_Pattern:  0 CV=f(LAA); 1 CV=F(A); 2 SD=F(LAA); 3 SD=F(A)"<<endl;
    report4<<Maturity_Option<<" #_maturity_option:  1=length logistic; 2=age logistic; 3=read age-maturity matrix by growth_pattern; 4=read age-fecundity"<<endl;
    if(Maturity_Option>=3)
    {report4<<"#_Age_Maturity by growth pattern"<<endl<<Age_Maturity<<endl;}
    else
    {report4<<"#_placeholder for empirical age-maturity by growth pattern"<<endl;}
    report4<<First_Mature_Age<<" #_First_Mature_Age"<<endl;

    report4<<Fecund_Option<<" #_fecundity option:(1)eggs=Wt*(a+b*Wt);(2)eggs=a*L^b;(3)eggs=a*Wt^b"<<endl;
    report4<<MGparm_def<<" #_parameter_offset_approach (1=none, 2= M, G, CV_G as offset from female-GP1, 3=like SS2 V1.x)"<<endl;
    report4<<MG_adjust_method<<" #_env/block/dev_adjust_method (1=standard; 2=with logistic trans to keep within base parm bounds)"<<endl;

  report4<<endl<<"#_growth_parms"<<endl;
  report4<<"#_LO HI INIT PRIOR PR_type SD PHASE env-var use_dev dev_minyr dev_maxyr dev_stddev Block Block_Fxn"<<endl;
  NP=0;
  for (f=1;f<=N_MGparm;f++)
  {
    NP++;
    MGparm_1(f,3)=value(MGparm(f));
    report4<<MGparm_1(f)<<" # "<<ParmLabel(NP)<<endl;
  }

  j=N_MGparm;

  if(N_MGparm_env>0)
  {
    report4<<endl<<1<<" #_custom_MG-env_setup (0/1)"<<endl;
    for (f=1;f<=N_MGparm_env;f++)
    {j++; NP++; if(customMGenvsetup==0) {k=1;} else {k=f;}  // use read value of custom here
    MGparm_env_1(k,3)=value(MGparm(j)); report4<<MGparm_env_1(k)<<" # "<<ParmLabel(NP)<<endl;}
   }
  else
  {
    report4<<endl<<"#_Cond 0  #custom_MG-env_setup (0/1)"<<endl;
    report4<<"#_Cond -2 2 0 0 -1 99 -2 #_placeholder when no MG-environ parameters"<<endl;
  }

  if(N_MGparm_blk>0)
  {
    report4<<endl<<1<<" #_custom_MG-block_setup (0/1)"<<endl;
    for (f=1;f<=N_MGparm_blk;f++)
    {j++; NP++; if(customblocksetup_MG==0) {k=1;} else {k=f;}
    MGparm_blk_1(k,3)=value(MGparm(j));report4<<MGparm_blk_1(k)<<" # "<<ParmLabel(NP)<<endl;}
  }
  else
  {
    report4<<endl<<"#_Cond 0  #custom_MG-block_setup (0/1)"<<endl;
    report4<<"#_Cond -2 2 0 0 -1 99 -2 #_placeholder when no MG-block parameters"<<endl;
  }

  report4<<endl<<"#_seasonal_effects_on_biology_parms"<<endl<<MGparm_seas_effects<<" #_femwtlen1,femwtlen2,mat1,mat2,fec1,fec2,Malewtlen1,malewtlen2,L1,K"<<endl;
  if(MGparm_doseas>0)
  {
    for(f=1;f<=N_MGparm_seas;f++)
    {
      NP++; j++;  MGparm_seas_1(f,3)=value(MGparm(j));
      report4<<MGparm_seas_1(f)<<" # "<<ParmLabel(NP)<<endl;
    }
  }
  else
  {
    report4<<"#_Cond -2 2 0 0 -1 99 -2 #_placeholder when no seasonal MG parameters"<<endl;
  }
  report4<<endl;
  if(N_MGparm_dev>0)
  {
   for(i=1;i<=N_MGparm_dev;i++)
   for(j=MGparm_dev_minyr(i);j<=MGparm_dev_maxyr(i);j++)
   {
     NP++;
    report4<<"#DisplayOnly "<<MGparm_dev(i,j)<<" # "<<ParmLabel(NP)<<endl;
   }
    report4<<MGparm_dev_PH<<" #_MGparm_Dev_Phase"<<endl;
  }
  else
  {
    report4<<"#_Cond -4 #_MGparm_Dev_Phase"<<endl;
  }


   report4<<endl<<"#_Spawner-Recruitment"<<endl<<SR_fxn<<" #_SR_function"<<endl;
   report4<<"#_LO HI INIT PRIOR PR_type SD PHASE"<<endl;
   for(f=1;f<=6;f++)
   { NP++;
     SR_parm_1(f,3)=value(SR_parm(f));
     report4<<SR_parm_1(f)<<" # "<<ParmLabel(NP)<<endl;
   }
   report4<<SR_env_link<<" #_SR_env_link"<<endl;
   report4<<SR_env_target_RD<<" #_SR_env_target_0=none;1=devs;_2=R0;_3=steepness"<<endl;
   report4<<endl<<do_recdev<<" #do_recdev:  0=none; 1=devvector; 2=simple deviations"<<endl;
   report4<<recdev_start<<" # first year of main recr_devs; early devs can preceed this era"<<endl;
   report4<<recdev_end<<" # last year of main recr_devs; forecast devs start in following year"<<endl;
   report4<<recdev_PH<<" #_recdev phase "<<endl;
   report4<<recdev_adv<<" # (0/1) to read 11 advanced options"<<endl;
   if(recdev_adv==0) {onenum="#_Cond ";} else {onenum=" ";}
   report4<<onenum<<recdev_early_start_rd<<" #_recdev_early_start (0=none; neg value makes relative to recdev_start)"<<endl;
   report4<<onenum<<recdev_early_PH<<" #_recdev_early_phase"<<endl;
   report4<<onenum<<fore_recr_PH<<" #_forecast_recruitment phase (incl. late recr) (0 value resets to maxphase+1)"<<endl;
   report4<<onenum<<fore_recr_lambda<<" #_lambda for prior_fore_recr occurring before endyr+1"<<endl;
   report4<<onenum<<recdev_adj(1)<<" #_last_early_yr_nobias_adj_in_MPD"<<endl;
   report4<<onenum<<recdev_adj(2)<<" #_first_yr_fullbias_adj_in_MPD"<<endl;
   report4<<onenum<<recdev_adj(3)<<" #_last_yr_fullbias_adj_in_MPD"<<endl;
   report4<<onenum<<recdev_adj(4)<<" #_first_recent_yr_nobias_adj_in_MPD"<<endl;
   report4<<onenum<<recdev_LO<<" #min rec_dev"<<endl;
   report4<<onenum<<recdev_HI<<" #max rec_dev"<<endl;
   report4<<onenum<<recdev_read<<" #_read_recdevs"<<endl;
   report4<<"#_end of advanced SR options"<<endl<<endl;
    if(recdev_read>0)
    {
      report4<<"# Specified recr devs to read"<<endl;
      report4<<"#_Yr Input_value # Final_value"<<endl;
      for(j=1;j<=recdev_read;j++)
      {
        y=recdev_input(j,1);
        report4<<recdev_input(j)<<" # ";
        if(y>=recdev_first)
        {report4<<recdev(y)<<endl;}
        else
        {report4<<" not used "<<endl;}
      }
    }
    else
    {
      report4<<"# read specified recr devs"<<endl;
      report4<<"#_Yr Input_value"<<endl;
    }
    report4<<endl<<"# all recruitment deviations"<<endl;
    if(Do_Forecast>0) {k=YrMax;}  else {k=recdev_end;}
    for(y=recdev_first;y<=k;y++)
    {
      NP++;  report4<<"#DisplayOnly "<<recdev(y)<<" # "<<ParmLabel(NP)<<endl;
    }

  report4<<endl<<"#Fishing Mortality info "<<endl<<F_ballpark<<" # F ballpark for tuning early phases"<<endl;
  report4<<F_ballpark_yr<<" # F ballpark year (neg value to disable)"<<endl;
  report4<<F_Method<<" # F_Method:  1=Pope; 2=instan. F; 3=hybrid (hybrid is recommended)"<<endl;
  report4<<max_harvest_rate<<" # max F or harvest rate, depends on F_Method"<<endl;
  report4<<"# no additional F input needed for Fmethod 1"<<endl;
  report4<<"# read overall start F value; overall phase; N detailed inputs to read for Fmethod 2"<<endl;
  report4<<"# read N iterations for tuning for Fmethod 3 (recommend 3 to 7)"<<endl;
 if(F_Method==2)
  {
    report4<<F_setup<<" # overall start F value; overall phase; N detailed inputs to read"<<endl;
  }
  else if(F_Method==3)
  {
   report4<<F_Tune<<"  # N iterations for tuning F in hybrid method (recommend 3 to 7)"<<endl;
  }
  report4<<"#Fleet Year Seas F_value se phase (for detailed setup of F_Method=2)"<<endl<<F_setup2<<endl;

   report4<<endl<<"#_initial_F_parms"<<endl;
   report4<<"#_LO HI INIT PRIOR PR_type SD PHASE"<<endl;
   for(f=1;f<=Nfleet;f++)
   {
    NP++;
    init_F_parm_1(f,3)=value(init_F(f));
    report4<<init_F_parm_1(f)<<" # "<<ParmLabel(NP)<<endl;
   }

   if(F_Method==2)
   {
    report4<<endl<<"# F rates for Fmethod=2"<<endl;
    k=0;
    for(f=1;f<=Nfleet;f++)
    for(y=styr;y<=endyr;y++)
    for(s=1;s<=nseas;s++)
    {
      NP++; k++;
      report4<<"# "<<F_rate(k)<< " "<<ParmLabel(NP)<<endl;
    }
   }

   report4<<endl<<"#_Q_setup"<<endl<<
   " # A=do power, B=env-var, C=extra SD, D=devtype(<0=mirror, 0/1=none, 2=cons, 3=rand, 4=randwalk); E=0=num/1=bio, F=err_type"<<endl;
   report4<<" #_A  B  C  D  E  F"<<endl;
   for(f=1;f<=Ntypes;f++)
   report4<<Q_setup(f)<<" # "<<f<<" "<<fleetname(f)<<endl;
   report4<<endl;
   if(ask_detail>0)  // report q_parm_detail
   {
    report4<<1<<" #_0=read one parm for each fleet with random q; 1=read a parm for each year of index"<<endl;
   }
  else
  {
    report4<<"#_Cond 0 #_If q has random component, then 0=read one parm for each fleet with random q; 1=read a parm for each year of index"<<endl;
  }

   report4<<"#_Q_parms(if_any)"<<endl;
   if(Q_Npar>0)
   {
    report4<<"# LO HI INIT PRIOR PR_type SD PHASE"<<endl;
    for(f=1;f<=Q_Npar;f++)
    {
      NP++;
      Q_parm_1(f,3)=value(Q_parm(f));
      report4<<Q_parm_1(f)<<" # "<<ParmLabel(NP)<<endl;
    }
   }

   report4<<endl<<"#_size_selex_types"<<endl;
   report4<<"#_Pattern Discard Male Special"<<endl;
   for(f=1;f<=Ntypes;f++) report4<<seltype(f)<<" # "<<f<<" "<<fleetname(f)<<endl;
   report4<<endl<<"#_age_selex_types"<<endl;
   report4<<"#_Pattern ___ Male Special"<<endl;
   for(f=1;f<=Ntypes;f++) report4<<seltype(f+Ntypes)<<" # "<<f<<" "<<fleetname(f)<<endl;
   report4<<"#_LO HI INIT PRIOR PR_type SD PHASE env-var use_dev dev_minyr dev_maxyr dev_stddev Block Block_Fxn"<<endl;

  for (f=1;f<=N_selparm;f++)
  {
    NP++;
    selparm_1(f,3)=value(selparm(f));
    report4<<selparm_1(f)<<" # "<<ParmLabel(NP)<<endl;
  }

  j=N_selparm;

   if(N_selparm_env>0)
   {
     report4<<1<<" #_custom_sel-env_setup (0/1) "<<endl;
     for (f=1;f<=N_selparm_env;f++)
     {
       j++;  NP++;
       if(customenvsetup==0) {k=1;} else {k=f;}  // use read value of custom here
       selparm_env_1(k,3)=value(selparm(j)); report4<<selparm_env_1(k)<<" # "<<ParmLabel(NP)<<endl;
     }
   }
  else
  {
    report4<<"#_Cond 0 #_custom_sel-env_setup (0/1) "<<endl;
    report4<<"#_Cond -2 2 0 0 -1 99 -2 #_placeholder when no enviro fxns"<<endl;
  }

   if(N_selparm_blk>0)
   {
     report4<<1<<" #_custom_sel-blk_setup (0/1) "<<endl;
     for (f=1;f<=N_selparm_blk;f++)
     {
       j++;  NP++;
       if(customblocksetup==0) {k=1;} else {k=f;}  // use read value of custom here
       selparm_blk_1(k,3)=value(selparm(j)); report4<<selparm_blk_1(k)<<" # "<<ParmLabel(NP)<<endl;
     }
   }
  else
  {
    report4<<"#_Cond 0 #_custom_sel-blk_setup (0/1) "<<endl;
    report4<<"#_Cond -2 2 0 0 -1 99 -2 #_placeholder when no block usage"<<endl;
  }

  if(N_selparm_dev>0)
  {
    for(i=1;i<=N_selparm_dev;i++)
    for(j=selparm_dev_minyr(i);j<=selparm_dev_maxyr(i);j++)
    {
      NP++; report4<<"# "<<selparm_dev(i,j)<<" # "<<ParmLabel(NP)<<endl;
    }
    report4<<selparm_dev_PH<<" #_selparmdev-phase"<<endl;
  }
  else
  {
    report4<<"#_Cond -4 # placeholder for selparm_Dev_Phase"<<endl;
  }

  if(N_selparm_env+N_selparm_blk+N_selparm_dev == 0) report4<<"#_Cond ";
   report4<<selparm_adjust_method<<" #_env/block/dev_adjust_method (1=standard; 2=logistic trans to keep in base parm bounds)"<<endl;

  report4<<endl<<"# Tag loss and Tag reporting parameters go next"<<endl;
  if(Do_TG>0)
  {
    report4<<1<<" # TG_custom:  0=no read; 1=read"<<endl;
    for (f=1;f<=3*N_TG+2*Nfleet;f++)
    {
      NP++;
      report4<<TG_parm2(f)<<" # "<<ParmLabel(NP)<<endl;
    }
  }
  else
  {
    report4<<"0  # TG_custom:  0=no read; 1=read if tags exist"<<endl
    <<"#_Cond -6 6 1 1 2 0.01 -4 0 0 0 0 0 0 0  #_placeholder if no parameters"<<endl;;
  }

  report4 <<endl<<Do_Var_adjust<<" #_Variance_adjustments_to_input_values"<<endl;
  report4 <<"#_";  for(f=1;f<=Ntypes;f++) {report4<<f<<" ";}
  report4 <<endl;
  if(Do_Var_adjust==0)
  {onenum="#_Cond ";}
  else
  {onenum=" ";}

  report4<<onenum<<var_adjust(1)<<" #_add_to_survey_CV"<<endl;
  report4<<onenum<<var_adjust(2)<<" #_add_to_discard_stddev"<<endl;
  report4<<onenum<<var_adjust(3)<<" #_add_to_bodywt_CV"<<endl;
  report4<<onenum<<var_adjust(4)<<" #_mult_by_lencomp_N"<<endl;
  report4<<onenum<<var_adjust(5)<<" #_mult_by_agecomp_N"<<endl;
  report4<<onenum<<var_adjust(6)<<" #_mult_by_size-at-age_N"<<endl;

  report4<<DF_disc<<" #_DF_for_discard_like"<<endl;
  report4<<DF_bodywt<<" #_DF_for_meanbodywt_like"<<endl;

  report4<<endl<<max_lambda_phase<<" #_maxlambdaphase"<<endl;
  report4<<sd_offset<<" #_sd_offset"<<endl;

  report4<<endl<<N_lambda_changes<<" # number of changes to make to default Lambdas (default value is 1.0)"<<endl;
  report4<<"# Like_comp codes:  1=surv; 2=disc; 3=mnwt; 4=length; 5=age; 6=SizeFreq; 7=sizeage; 8=catch; "<<endl<<
   "# 9=init_equ_catch; 10=recrdev; 11=parm_prior; 12=parm_dev; 13=CrashPen; 14=Morphcomp; 15=Tag-comp; 16=Tag-negbin"<<
   endl<<"#like_comp fleet/survey  phase  value  sizefreq_method"<<endl;

  if(N_lambda_changes>0) report4<<Lambda_changes<<endl;

  report4<<endl<<"# lambdas (for info only; columns are phases)"<<endl;
  if(nobs>0) {for(f=1;f<=Ntypes;f++) report4<<"# "<<surv_lambda(f)<<" #_CPUE/survey:_"<<f<<endl;}
  if(nobs_disc>0) {for(f=1;f<=Ntypes;f++) report4<<"# "<< disc_lambda(f)<<" #_discard:_"<<f<<endl;}
  if(nobs_mnwt>0) {for(f=1;f<=Ntypes;f++) report4<<"# "<< mnwt_lambda(f)<<" #_meanbodywt:"<<f<<endl;}
  if(nobsl>0) {for(f=1;f<=Ntypes;f++) report4<<"# "<< length_lambda(f)<<" #_lencomp:_"<<f<<endl;}
  if(nobsa>0) {for(f=1;f<=Ntypes;f++) report4<<"# "<< age_lambda(f)<<" #_agecomp:_"<<f<<endl;}
  if(WtFreq_Nmeth>0) for(f=1;f<=WtFreq_Nuse;f++) report4<<"# "<<WtFreq_lambda(f)<<" #_sizefreq:_"<<f<<endl;
  if(nobs_ms>0) {for(f=1;f<=Ntypes;f++) report4<<"# "<< sizeage_lambda(f)<<" #_size-age:_"<<f<<endl;}
  report4<<"# "<< init_equ_lambda<<" #_init_equ_catch"<<endl;
  report4<<"# "<< recrdev_lambda<<" #_recruitments"<<endl;
  report4<<"# "<< parm_prior_lambda<<" #_parameter-priors"<<endl;
  report4<<"# "<< parm_dev_lambda<<" #_parameter-dev-vectors"<<endl;
  report4<<"# "<< CrashPen_lambda<<" #_crashPenLambda"<<endl;
  if(Do_Morphcomp>0) report4<<"# "<< Morphcomp_lambda<<" #_Morphcomplambda"<<endl;
  if(Do_TG>0)
  {
  for(TG=1;TG<=N_TG;TG++) report4<<"# "<<TG_lambda1(TG)<<" #_TG-comp_group:_"<<TG<<endl;
  for(TG=1;TG<=N_TG;TG++) report4<<"# "<<TG_lambda2(TG)<<" #_TG-negbin_group:_"<<TG<<endl;
  }

  report4<<Do_More_Std<<" # (0/1) read specs for more stddev reporting "<<endl;
  if(Do_More_Std>0)
  {
    report4<<More_Std_Input<<" # selex type, len/age, year, N selex bins, Growth pattern, N growth ages, NatAge_area(-1 for all), NatAge_yr, N Natages"<<endl;
    if(More_Std_Input(4)>0) report4<<Selex_Std_Pick<<" # vector with selex std bin picks (-1 in first bin to self-generate)"<<endl;
    if(More_Std_Input(6)>0) report4<<Growth_Std_Pick<<" # vector with growth std bin picks (-1 in first bin to self-generate)"<<endl;
    if(More_Std_Input(9)>0) report4<<NatAge_Std_Pick<<" # vector with NatAge std bin picks (-1 in first bin to self-generate)"<<endl;
  }
  else
  {
    report4<<" # 0 1 -1 5 1 5 1 -1 5 # placeholder for selex type, len/age, year, N selex bins, Growth pattern, N growth ages, NatAge_area(-1 for all), NatAge_yr, N Natages"<<endl;
    report4<<" # placeholder for vector of selex bins to be reported"<<endl;
    report4<<" # placeholder for vector of growth ages to be reported"<<endl;
    report4<<" # placeholder for vector of NatAges ages to be reported"<<endl;
  }


  report4<<fim<<endl<<endl; // end of file indicator


//****************************************************************************
//  ProgLabel_9200_FUNCTION write_bigoutput
FUNCTION write_bigoutput
  k=current_phase();
  if(k>max_lambda_phase) k=max_lambda_phase;
  SS2out<<version_info<<endl<<endl;
  time(&finish);
  cout<<" writing big output now "<<endl;
  SS2out<<"Time: "<<ctime(&finish);
  time(&finish);
  elapsed_time = difftime(finish,start);
  hour = long(elapsed_time)/3600;
  minute = long(elapsed_time)%3600/60;
  second = (long(elapsed_time)%3600)%60;
  SS2out<<"This run took: "<<hour<<" hours, "<<minute<<" minutes, "<<second<<" seconds."<<endl;
  SS2out<<endl<<"Data_File: "<<datfilename<<endl;
  SS2out<<"Control_File: "<<ctlfilename<<endl;
  if(readparfile>=1) SS2out<<"Start_parm_values_from_SS3.PAR"<<endl;
  SS2out<<endl<<"Convergence_Level: "<<endl<<"Hessian: "<<endl;
  SS2out<<endl<<"Starter_Comments"<<endl<<Starter_Comments<<endl;
  SS2out<<endl<<"Forecast_Comments"<<endl<<Forecast_Comments<<endl;
  SS2out<<endl<<"Data_Comments"<<endl<<Data_Comments<<endl;
  SS2out<<endl<<"Control_Comments"<<endl<<Control_Comments<<endl<<endl;
  SS2out<<"Sum_of_months_on_read_was:_ "<<sumseas<<" rescaled_to_sum_to: "<<sum(seasdur)<<endl;

  SS2out<<endl<<"KeyWords"<<endl;
  SS2out<<"X Fleetnames"<<endl;
  SS2out<<"X LIKELIHOOD"<<endl;
  SS2out<<"X Input_Variance_Adjustment"<<endl;
  SS2out<<"X PARAMETERS"<<endl;
  SS2out<<"X DERIVED_QUANTITIES"<<endl;
  SS2out<<"X MGParm_Block_Assignments"<<endl;
  SS2out<<"X Selex_Block_Assignments"<<endl;
  SS2out<<"X MGparm_By_Year_after_adjustments"<<endl;
  SS2out<<"X SELparm(Size)_By_Year_after_adjustments"<<endl;
  SS2out<<"X SELparm(Age)_By_Year_after_adjustments"<<endl;
  SS2out<<"X RECRUITMENT_DIST"<<endl;
  SS2out<<"X MORPH_INDEXING"<<endl;
  SS2out<<"X MOVEMENT"<<endl;
  SS2out<<"X EXPLOITATION"<<endl;
  SS2out<<"X TIME_SERIES"<<endl;
  SS2out<<"X SPR_series"<<endl;
  SS2out<<"X Spawning_Biomass_Report_1"<<endl;
  SS2out<<"X NUMBERS_AT_AGE_Annual_1"<<endl;
  SS2out<<"X Z_AT_AGE_Annual_1"<<endl;
  SS2out<<"X Spawning_Biomass_Report_2"<<endl;
  SS2out<<"X NUMBERS_AT_AGE_Annual_2"<<endl;
  SS2out<<"X Z_AT_AGE_Annual_2"<<endl;
  SS2out<<"X SPAWN_RECRUIT"<<endl;
  SS2out<<"X INDEX_1"<<endl;
  SS2out<<"X INDEX_2"<<endl;
  SS2out<<"X INDEX_3"<<endl;
  SS2out<<"X DISCARD"<<endl;
  SS2out<<"X MEAN_BODY_WT"<<endl;
  SS2out<<"X FIT_LEN_COMPS"<<endl;
  SS2out<<"X FIT_AGE_COMPS"<<endl;
  SS2out<<"X LEN_SELEX"<<endl;
  SS2out<<"X RETENTION"<<endl;
  SS2out<<"X DISCARD_MORT"<<endl;
  SS2out<<"X KEEPERS"<<endl;
  SS2out<<"X DEADFISH"<<endl;
  SS2out<<"X AGE_SELEX"<<endl;
  SS2out<<"X AGE_SELEX_from_size_selex"<<endl;
  SS2out<<"X Combined_SELEX"<<endl;
  SS2out<<"X ENVIRONMENTAL_DATA"<<endl;
  SS2out<<"X TAG_Recapture"<<endl;
  SS2out<<"X NUMBERS_AT_AGE"<<endl;
  SS2out<<"X CATCH_AT_AGE"<<endl;
  SS2out<<"X BIOLOGY"<<endl;

  SS2out<<endl<<"FleetNames"<<endl;

  for(f=1;f<=Ntypes;f++)  SS2out<<f<<" "<<fleetname(f)<<endl;

  SS2out<<endl<<"LIKELIHOOD "<<obj_fun<<endl;                         //ProgLabel_310
  SS2out<<"Component logL*Lambda Lambda"<<endl;
  SS2out<<"TOTAL "<<obj_fun<<endl;
  if(F_Method>1) SS2out <<"Catch "<<catch_like*column(catch_lambda,k)<<endl;
  SS2out <<"Equil_catch "<<equ_catch_like*init_equ_lambda(k)<<" "<<init_equ_lambda(k)<<endl;
  if(nobs>0) SS2out <<"Survey "<<surv_like*column(surv_lambda,k)<<endl;
  if(nobs_disc>0) SS2out <<"Discard "<<disc_like*column(disc_lambda,k)<<endl;
  if(nobs_mnwt>0) SS2out <<"Mean_body_wt "<<mnwt_like*column(mnwt_lambda,k)<<endl;
  if(nobsl>0) SS2out <<"Length_comp "<<length_like*column(length_lambda,k)<<endl;
  if(nobsa>0) SS2out <<"Age_comp "<<age_like*column(age_lambda,k)<<endl;
  if(nobs_ms>0) SS2out <<"Size_at_age "<<sizeage_like*column(sizeage_lambda,k)<<endl;
  if(WtFreq_Nmeth>0) SS2out <<"SizeFreq "<<WtFreq_like*column(WtFreq_lambda,k)<<endl;
  if(Do_Morphcomp>0) SS2out <<"Morphcomp "<<Morphcomp_lambda(k)*Morphcomp_like<<" "<<Morphcomp_lambda(k)<<endl;
  if(Do_TG>0) SS2out <<"Tag_comp "<<TG_like1*column(TG_lambda1,k)<<endl;
  if(Do_TG>0) SS2out <<"Tag_negbin "<<TG_like2*column(TG_lambda2,k)<<endl;
  SS2out <<"Recruitment "<<prior_rec*recrdev_lambda(k)<<" "<<recrdev_lambda(k)<<endl;
  SS2out <<"Forecast_Recruitment "<<prior_fore_rec<<" "<<1.0<<endl;
  SS2out <<"Parm_priors "<<parm_like*parm_prior_lambda(k)<<" "<<parm_prior_lambda(k)<<endl;
  SS2out <<"Parm_softbounds "<<SoftBoundPen<<" "<<" NA "<<endl;
  SS2out <<"Parm_devs "<<parm_dev_like*parm_dev_lambda(k)<<" "<<parm_dev_lambda(k)<<endl;
  SS2out <<"Crash_Pen "<<CrashPen_lambda(k)*CrashPen<<" "<<CrashPen_lambda(k)<<endl;

  SS2out<<"_"<<endl<<"Fleet:  ALL ";
  for(f=1;f<=Ntypes;f++) SS2out<<f<<" ";
  SS2out<<endl;
  if(F_Method>1) SS2out<<"Catch_lambda: _ "<<column(catch_lambda,k)<<endl<<"Catch_like: "<<catch_like*column(catch_lambda,k) <<" "<<catch_like<<endl;
  if(nobs>0) SS2out<<"Surv_lambda: _ "<<column(surv_lambda,k)<<endl<<"Surv_like: "<<surv_like*column(surv_lambda,k)<<" "<<surv_like<<endl;
  if(nobs_disc>0) SS2out<<"Disc_lambda: _ "<<column(disc_lambda,k)<<endl<<"Disc_like: "<<disc_like*column(disc_lambda,k)<<" "<<disc_like<<endl;
  if(nobs_mnwt>0) SS2out<<"mnwt_lambda: _ "<<column(mnwt_lambda,k)<<endl<<"mnwt_like: "<<mnwt_like*column(mnwt_lambda,k)<<" "<<mnwt_like<<endl;
  if(nobsl>0) SS2out<<"Length_lambda: _ "<<column(length_lambda,k)<<endl<<"Length_like: "<<length_like*column(length_lambda,k)<<" "<<length_like<<endl;
  if(nobsa>0) SS2out<<"Age_lambda: _ "<<column(age_lambda,k)<<endl<<"Age_like: "<<age_like*column(age_lambda,k)<<" "<<age_like<<endl;
  if(nobs_ms>0) SS2out<<"Sizeatage_lambda: _ "<<column(sizeage_lambda,k)<<endl<<"sizeatage_like: "<<sizeage_like*column(sizeage_lambda,k)<<" "<<sizeage_like<<endl;

  if(WtFreq_Nmeth>0)
  {
    for(j=1;j<=WtFreq_Nmeth;j++)
    {
      SS2out<<"SizeFreq_lambda:_"<<j<<"; ";
    if(j==1) {SS2out<<"_ ";} else {SS2out<<"_ ";}
      for(f=1;f<=Ntypes;f++)
      {
        if(WtFreq_use(f,j)>0) {SS2out<<WtFreq_lambda(WtFreq_use(f,j),k)<<" ";}
        else {SS2out<<" NA ";}
      }
      SS2out<<endl;
      SS2out<<"SizeFreq_like:_"<<j<<"; ";
    if(j==1) {SS2out<<WtFreq_like*column(WtFreq_lambda,k)<<" ";} else {SS2out<<"_ ";}
      for(f=1;f<=Ntypes;f++)
      {
        if(WtFreq_use(f,j)>0) {SS2out<<WtFreq_like(WtFreq_use(f,j))<<" ";}
        else {SS2out<<" NA ";}
      }
      SS2out<<endl;
    }
  }

  if(Do_TG>0)
  {
    SS2out<<endl<<"_"<<endl<<"Tag_Group:  ALL ";
    for(f=1;f<=N_TG;f++) SS2out<<f<<" ";
    SS2out<<endl;
    SS2out<<"Tag_comp_Lambda _ "<<column(TG_lambda1,k)<<endl<<
    "Tag_comp_Like "<<TG_like1*column(TG_lambda1,k)<<" "<<TG_like1<<endl;
    SS2out<<"Tag_negbin_Lambda _ "<<column(TG_lambda2,k)<<endl<<
    "Tag_negbin_Like "<<TG_like2*column(TG_lambda2,k)<<" "<<TG_like2<<endl;
  }
  SS2out<<endl;

  SS2out<<"Input_Variance_Adjustment"<<endl<<"Fleet ";
  for(i=1;i<=Ntypes;i++) {SS2out<<" "<<i;}
  SS2out<<endl;
  SS2out << "Index_extra_CV "<<var_adjust(1)<<endl;
  SS2out << "Discard_extra_CV "<<var_adjust(2)<<endl;
  SS2out << "MeanBodyWt_extra_CV "<<var_adjust(3)<<endl;
  SS2out << "effN_mult_Lencomp "<<var_adjust(4)<<endl;
  SS2out << "effN_mult_Agecomp "<<var_adjust(5)<<endl;
  SS2out << "effN_mult_Len_at_age "<<var_adjust(6)<<endl;

  SS2out<<"MG_parms"<<"Using_offset_approach_#:_"<<MGparm_def<<"  (1=none, 2= M, G, CV_G as offset from female_GP1, 3=like SS2 V1.x)"<<endl;

  SS2out<<endl<<"PARAMETERS"<<endl<<"Num Label Value Active_Cnt Phase Min Max Init Prior PR_type Pr_SD Prior_Like Parm_StDev Status"<<endl;

  NP=0;   // count of number of parameters
  active_count=0;
  for(j=1;j<=N_MGparm2;j++)
  {
    NP++;  SS2out<<NP<<" "<<ParmLabel(NP)<<" "<<MGparm(j);
    if(active(MGparm(j)))
    {
      active_count++;
      SS2out<<" "<<active_count<<" "<<MGparm_PH(j)<<" "<<MGparm_LO(j)<<" "<<MGparm_HI(j)<<" "<<MGparm_RD(j)
      <<" "<<MGparm_PR(j)<<" "<<MGparm_PRtype(j)<<" "<<MGparm_CV(j)<<" "<<MGparm_Like(j)<<" "<<CoVar(active_count,1);
      if (MGparm(j)==MGparm_RD(j))
      {
        SS2out<<" NO_MOVE ";
      }
      else
      {
        temp=(MGparm(j)-MGparm_LO(j))/(MGparm_HI(j)-MGparm_LO(j));
        if(temp==0.0 || temp==1.0) {SS2out<<" BOUND ";} else if(temp<0.01) {SS2out<<" LO ";}
        else if(temp>=0.99) {SS2out<<" HI ";} else {SS2out<<" OK ";}
      }
    }
    else
      {
        SS2out<<" _ "<<MGparm_PH(j)<<" "<<MGparm_LO(j)<<" "<<MGparm_HI(j)<<" "<<MGparm_RD(j)
        <<" "<<MGparm_PR(j)<<" "<<MGparm_PRtype(j)<<" "<<MGparm_CV(j)<<" "<<MGparm_Like(j)<<" _ NA ";
      }
    SS2out<<endl;
  }

    if(N_MGparm_dev>0)
    {
    for(i=1;i<=N_MGparm_dev;i++)
    for(j=MGparm_dev_minyr(i);j<=MGparm_dev_maxyr(i);j++)
      {
      NP++;  SS2out<<NP<<" "<<ParmLabel(NP)<<" "<<MGparm_dev(i,j);
    if(active(MGparm_dev))
      {
        active_count++;
        SS2out<<" "<<active_count<<" "<<MGparm_dev_PH<<" _ _ _ _ _ _ _ "<<CoVar(active_count,1)<<" act";
      }
      else
        SS2out<<" _ _ _ _ _ _ _ _ _ _ NA";
    SS2out<<endl;
    }
    }

    for(i=1;i<=6;i++)
    {NP++;  SS2out<<NP<<" "<<ParmLabel(NP)<<" "<<SR_parm(i);
    if(active(SR_parm(i)))
      {
        active_count++;
        SS2out<<" "<<active_count<<" "<<SR_parm_1(i,7)<<" "<<SR_parm_1(i)(1,6)<<" "<<SR_parm_Like(i)<<" "<<CoVar(active_count,1);
        if(SR_parm(i)==SR_parm_1(i,3))
          {SS2out<<" NO_MOVE";}
          else
          {
            temp=(SR_parm(i)-SR_parm_1(i,1))/(SR_parm_1(i,2)-SR_parm_1(i,1));
            if(temp==0.0 || temp==1.0) {SS2out<<" BOUND";} else if(temp<0.01) {SS2out<<" LO";}
              else if(temp>=0.99) {SS2out<<" HI";} else {SS2out<<" OK";}
          }
      }
      else
        {
        SS2out<<" _ "<<SR_parm_1(i,7)<<" "<<SR_parm_1(i)(1,6)<<" "<<SR_parm_Like(i)<<" _ NA";
        }
    SS2out << endl;}

    if(recdev_do_early>0)
      {
        for(i=recdev_early_start;i<=recdev_early_end;i++)
        {NP++;  SS2out<<NP<<" "<<ParmLabel(NP)<<" "<<recdev(i);
        if( active(recdev_early) )
        {
          active_count++;
          SS2out<<" "<<active_count<<" _ _ _ _ _ _ _ _ "<<CoVar(active_count,1)<<" act";
        }
        else
          {
            SS2out<<" _ _ _ _ _ _ _ _ _ _ NA";
          }
        SS2out << endl;
          }
      }

    if(do_recdev>0)
      {
        for(i=recdev_start;i<=recdev_end;i++)
        {NP++;  SS2out<<NP<<" "<<ParmLabel(NP)<<" "<<recdev(i);
        if( active(recdev1)||active(recdev2) )
        {
          active_count++;
          SS2out<<" "<<active_count<<" _ _ _ _ _ _ _ _ "<<CoVar(active_count,1)<<" act";
        }
        else
          {
            SS2out<<" _ _ _ _ _ _ _ _ _ _ NA";
          }
        SS2out << endl;
          }
      }

    if(Do_Forecast>0)
    {
      for(i=recdev_end+1;i<=YrMax;i++)
      {
        NP++; SS2out<<NP<<" "<<ParmLabel(NP)<<" "<<fore_recruitments(i);
        if(active(fore_recruitments))
        {active_count++; SS2out<<" "<<active_count<<" _ _ _ _ _ _ _ _ "<<CoVar(active_count,1)<<" act ";}
        else
        {SS2out<<" _ _ _ _ _ _ _ _ _ _ NA";}
        SS2out << endl;
      }
    }

    for(i=1;i<=Nfleet;i++)
    {NP++;  SS2out<<NP<<" "<<ParmLabel(NP)<<" "<<init_F(i);
    if(active(init_F(i)))
      {
        active_count++;
        SS2out<<" "<<active_count<<" "<<init_F_PH(i)<<" "<<init_F_LO(i)<<" "<<init_F_HI(i)<<" "<<init_F_RD(i)
      <<" "<<init_F_PR(i)<<" "<<init_F_PRtype(i)<<" "<<init_F_CV(i)<<" "<<init_F_Like(i)<<" "<<CoVar(active_count,1);
      if (init_F(i)==init_F_RD(i))
        {SS2out<<" NO_MOVE ";}
      else
        {
         temp=(init_F(i)-init_F_LO(i))/(init_F_HI(i)-init_F_LO(i));
         if(temp==0.0 || temp==1.0) {SS2out<<" BOUND ";} else if(temp<0.01) {SS2out<<" LO ";}
          else if(temp>=0.99) {SS2out<<" HI ";} else {SS2out<<" OK ";}
        }
      }
      else
        {
        SS2out<<" _ "<<init_F_PH(i)<<" "<<init_F_LO(i)<<" "<<init_F_HI(i)<<" "<<init_F_RD(i)<<" "<<init_F_PR(i)
        <<" "<<init_F_PRtype(i)<<" "<<init_F_CV(i)<<" "<<init_F_Like(i)<<" _ NA";
        }
    SS2out << endl;}

    if(F_Method==2)
    {
      for(i=1;i<=Nfleet*(TimeMax-styr+1);i++)
      {
        NP++;  SS2out<<NP<<" "<<ParmLabel(NP)<<" "<<F_rate(i);
    if(active(F_rate(i)))
      {
        active_count++;
        SS2out<<" "<<active_count<<" "<<have_catch(i)<<" "<<0.0<<" "<<8.0<<" "<<"NA"
      <<" "<<"NA"<<" "<<"NA"<<" "<<"NA"<<" "<<"NA"<<" "<<CoVar(active_count,1)<<" NA ";
      }
      SS2out << endl;}
      }

    for(i=1;i<=Q_Npar;i++)
    {NP++;  SS2out<<NP<<" "<<ParmLabel(NP)<<" "<<Q_parm(i);
    if(active(Q_parm(i)))
      {
        active_count++;
        SS2out<<" "<<active_count<<" "<<Q_parm_1(i,7)<<" "<<Q_parm_1(i)(1,6)<<" "<<Q_parm_Like(i)<<" "<<CoVar(active_count,1);
      if (Q_parm(i)==Q_parm_1(i,3))
        {SS2out<<" NO_MOVE ";}
        else
          {
          temp=(Q_parm(i)-Q_parm_1(i,1))/(Q_parm_1(i,2)-Q_parm_1(i,1));
          if(temp==0.0 || temp==1.0) {SS2out<<" BOUND ";} else if(temp<0.01) {SS2out<<" LO ";}  else if(temp>=0.99) {SS2out<<" HI ";} else {SS2out<<" OK ";}
          }
      }
      else
        {
        SS2out<<" _ "<<" "<<Q_parm_1(i,7)<<" "<<Q_parm_1(i)(1,6)<<" "<<Q_parm_Like(i)<<" _ NA";
        }
    SS2out << endl;}

  for (j=1;j<=N_selparm2;j++)
  {
    NP++;  SS2out<<NP<<" "<<ParmLabel(NP)<<" "<<selparm(j);
    if(active(selparm(j)))
    {
      active_count++;
      SS2out<<" "<<active_count<<" "<<selparm_PH(j)<<" "<<selparm_LO(j)<<" "<<selparm_HI(j)<<" "<<selparm_RD(j)
      <<" "<<selparm_PR(j)<<" "<<selparm_PRtype(j)<<" "<<selparm_CV(j)<<" "<<selparm_Like(j)<<" "<<CoVar(active_count,1);
      if (selparm(j)==selparm_RD(j))
      {SS2out<<" NO_MOVE ";}
      else
      {
        temp=(selparm(j)-selparm_LO(j))/(selparm_HI(j)-selparm_LO(j));
        if(temp==0.0 || temp==1.0) {SS2out<<" BOUND ";} else if(temp<0.01) {SS2out<<" LO ";}
        else if(temp>=0.99) {SS2out<<" HI ";} else {SS2out<<" OK ";}
      }
    }
    else
      {
        SS2out<<" _ "<<selparm_PH(j)<<" "<<selparm_LO(j)<<" "<<selparm_HI(j)<<" "<<selparm_RD(j)
        <<" "<<selparm_PR(j)<<" "<<selparm_PRtype(j)<<" "<<selparm_CV(j)<<" "<<selparm_Like(j)<<" _ NA ";
      }
    SS2out<<endl;
  }
    for(i=1;i<=N_selparm_dev;i++)
    for(j=selparm_dev_minyr(i);j<=selparm_dev_maxyr(i);j++)
      {
        NP++;  SS2out<<NP<<" "<<ParmLabel(NP)<<" "<<selparm_dev(i,j);
        if(active(selparm_dev))
          {active_count++; SS2out<<" "<<active_count<<" _ _ _ _ _ _ _ _ "<<CoVar(active_count,1)<<" act ";}
          else
          {SS2out<<" _ _ _ _ _ _ _ _ _ NA";}
    SS2out<<endl;
    }

    if(Do_TG>0)
    {
     k=3*N_TG+2*Nfleet;
  for (j=1;j<=k;j++)
  {
    NP++;  SS2out<<NP<<" "<<ParmLabel(NP)<<" "<<TG_parm(j);
    if(active(TG_parm(j)))
    {
      active_count++;
      SS2out<<" "<<active_count<<" "<<TG_parm_PH(j)<<" "<<TG_parm_LO(j)<<" "<<TG_parm_HI(j)
      <<" "<<TG_parm2(j)(3,6)<<" "<<TG_parm_Like(j)<<" "<<CoVar(active_count,1);
      if (TG_parm(j)==TG_parm2(j,3))
      {SS2out<<" NO_MOVE ";}
      else
      {
        temp=(TG_parm(j)-TG_parm_LO(j))/(TG_parm_HI(j)-TG_parm_LO(j));
        if(temp==0.0 || temp==1.0) {SS2out<<" BOUND ";} else if(temp<0.01) {SS2out<<" LO ";}
        else if(temp>=0.99) {SS2out<<" HI ";} else {SS2out<<" OK ";}
      }
    }
    else
      {
        SS2out<<" _ "<<TG_parm_PH(j)<<" "<<TG_parm2(j)(1,6)<<" "<<TG_parm_Like(j)<<" _ NA ";
      }
    SS2out<<endl;
  }

    }

  SS2out<<endl<<"DERIVED_QUANTITIES"<<endl;
  SS2out<<"SPR_ratio_basis: "<<SPR_report_label<<endl;
  SS2out<<"F_report_basis: "<<F_report_label<<endl;
  SS2out<<"B_ratio_denominator: "<<depletion_basis_label<<endl;

  SS2out<<" LABEL Value  StdDev"<<endl;
  for(j=1;j<=N_STD_Yr;j++)
  {
    NP++;  SS2out<<" "<<ParmLabel(NP)<<" "<<spbio_std(j);
    active_count++;
    SS2out<<" "<<CoVar(active_count,1)<<endl;
  }
  for(j=1;j<=N_STD_Yr;j++)
  {
    NP++;  SS2out<<" "<<ParmLabel(NP)<<" "<<recr_std(j);
    active_count++;
    SS2out<<" "<<CoVar(active_count,1)<<endl;
  }
  for(j=1;j<=N_STD_Yr_Ofish;j++)
  {
    NP++;  SS2out<<" "<<ParmLabel(NP)<<" "<<SPR_std(j);
    active_count++;
    SS2out<<" "<<CoVar(active_count,1)<<endl;
  }
  for(j=1;j<=N_STD_Yr_F;j++)
  {
    NP++;  SS2out<<" "<<ParmLabel(NP)<<" "<<F_std(j);
    active_count++;
    SS2out<<" "<<CoVar(active_count,1)<<endl;
  }
  for(j=1;j<=N_STD_Yr_Dep;j++)
  {
    NP++;  SS2out<<" "<<ParmLabel(NP)<<" "<<depletion(j);
    active_count++;
    SS2out<<" "<<CoVar(active_count,1)<<endl;
  }
  for(j=1;j<=N_STD_mgmtquant;j++)
  {
    NP++;  SS2out<<" "<<ParmLabel(NP)<<" "<<Mgmt_quant(j);
    active_count++;
    SS2out<<" "<<CoVar(active_count,1)<<endl;
  }

  for(j=1;j<=Extra_Std_N;j++)
  {
    NP++;  SS2out<<" "<<ParmLabel(NP)<<" "<<Extra_Std(j);
    active_count++;
    SS2out<<" "<<CoVar(active_count,1)<<endl;
  }


    SS2out<<endl<<"MGParm_Block_Assignments"<<endl;
    if(N_MGparm_blk>0)
      {SS2out<<"Base_parm# ";for(y=styr;y<=endyr;y++) {SS2out<<" "<<y;} SS2out<<endl;
   for(j=1;j<=N_MGparm;j++)
     {if(MGparm_1(j,13)>0) SS2out<<j<<" "<<Block_Defs_MG(j)<<endl;}}

    SS2out<<endl<<"Selex_Block_Assignments"<<endl;
    if(N_selparm_blk>0)
      {SS2out<<"Base_parm# ";for(y=styr;y<=endyr;y++) {SS2out<<" "<<y;} SS2out<<endl;
   for(j=1;j<=N_selparm;j++)
     {if(selparm_1(j,13)>0) SS2out<<j<<" "<<Block_Defs(j)<<endl;}}

   if(reportdetail==1) {k1=endyr;} else {k1=styr;}

   SS2out<<endl<<"MGparm_By_Year_after_adjustments"<<endl<<"Year"<<endl;
   for(y=styr;y<=k1;y++)
     SS2out<<y<<" "<<mgp_save(y)<<endl;

   SS2out<<endl<<"SELparm(Size)_By_Year_after_adjustments"<<endl<<"Fleet/Svy Year"<<endl;
   for(f=1;f<=Ntypes;f++)
   for(y=styr;y<=k1;y++)
     {
     k=int(value(save_sp_len(y,f,0)));
     if(k>0) SS2out<<f<<" "<<y<<" "<<save_sp_len(y,f)(1,k)<<endl;
     }

   SS2out<<endl<<"SELparm(Age)_By_Year_after_adjustments"<<endl<<"Fleet/Svy Year"<<endl;
   for(f=1;f<=Ntypes;f++)
   for(y=styr;y<=k1;y++)
     {
     k=int(value(save_sp_age(y,f,0)));
     if(k>0) SS2out<<f<<" "<<y<<" "<<save_sp_age(y,f)(1,k)<<endl;
     }
   SS2out<<endl<<"RECRUITMENT_DIST"<<endl<<"G_pattern Gender Seas Area Value Used?"<<endl;
   g=0;
   for(gg=1;gg<=gender;gg++)
     for(gp=1;gp<=N_GP;gp++)
       {g++;
       for(s=1;s<=nseas;s++)
         for(p=1;p<=pop;p++)
         {
         SS2out<<gp<<" "<<gg<<" "<<s<<" "<<p<<" "<<recr_dist(g,s,p)<<" "<<recr_dist_pattern(gp,s,p)<<endl;
         }
       }

   SS2out<<endl<<"MORPH_INDEXING"<<endl;
   SS2out<<"Index Gpattern Gender Bseas Sub_Morph Sub_Morph_Dist Gpattern_Gender Gpattern_Gender_Bseas BirthAge_Rel_Jan1"<<endl;
   for(g=1; g<=gmorph; g++)
   {
     SS2out<<g<<" "<<GP4(g)<<" "<<sx(g)<<" "<<Bseas(g)<<" "<<GP2(g)<<" "<<submorphdist(GP2(g))<<" "<<GP(g)<<" "<<GP3(g)<<" "<<azero_G(g)<<endl;
   }

   SS2out<<endl<<"MOVEMENT in endyear"<<endl<<"Seas Morph Source Dist minage maxage "<<age_vector<<endl;
   for(k=1;k<=do_migr2;k++)
   {
     SS2out<<move_def2(k)<<" "<<migrrate(endyr,k)<<endl;
   }

   SS2out<<endl<<"EXPLOITATION"<<endl<<"F_Method: "<<F_Method;
   if(F_Method==1) {SS2out<<"  Pope's_approx ";} else {SS2out<<"  Continuous_F ";}
   SS2out<<endl<<"F_std_units: "<<F_reporting<<F_report_label<<endl<<"_ _ _ ";
   for(f=1;f<=Nfleet;f++) if(catchunits(f)==1) {SS2out<<" Bio ";} else {SS2out<<" Num ";}
   SS2out<<endl<<"_ _ _ ";
   for(f=1;f<=Nfleet;f++) SS2out<<" "<<f;
   SS2out<<endl<<"Yr Seas F_std";
   for(f=1;f<=Nfleet;f++) SS2out<<" "<<fleetname(f);
   SS2out<<endl<<"init_yr _ _ "<<init_F<<endl;
   for(y=styr;y<=YrMax;y++)
     for(s=1;s<=nseas;s++)
       {
       t=styr+(y-styr)*nseas+s-1;
       SS2out<<y<<" "<<s<<" ";
      if(s==1 && y>=styr && STD_Yr_Reverse_F(y)>0 ) {SS2out<<F_std(STD_Yr_Reverse_F(y));} else {SS2out<<" _ ";}
      SS2out<<" "<<column(Hrate,t)<<endl;
       }

     int bio_t;

   SS2out<<endl<<"TIME_SERIES    BioSmry_age:_"<<Smry_Age;   // ProgLabel_320
   if(F_Method==1) {SS2out<<"  Pope's_approx"<<endl;} else {SS2out<<"  Continuous_F"<<endl;}
  SS2out<<"Area Yr Era Seas Bio_all Bio_smry SpawnBio Recruit_0 ";
  for(gp=1;gp<=N_GP;gp++) SS2out<<" Spbio_GP:"<<gp;
  for(gg=1;gg<=gender;gg++)
  for(gp=1;gp<=N_GP;gp++)
  {SS2out<<" SmryBio_SX:"<<gg<<"_GP:"<<gp;}
  for(gg=1;gg<=gender;gg++)
  for(gp=1;gp<=N_GP;gp++)
  {SS2out<<" SmryNum_SX:"<<gg<<"_GP:"<<gp;}
  dvector Bio_Comp(1,N_GP*gender);
  dvector Num_Comp(1,N_GP*gender);
  for (f=1;f<=Nfleet;f++)
  {
    SS2out<<" enc(B):_"<<f<<" dead(B):_"<<f<<" retain(B):_"<<f<<
    " enc(N):_"<<f<<" dead(N):_"<<f<<" retain(N):_"<<f<<
    " obs_cat:_"<<f;
     if(F_Method==1) {SS2out<<" Hrate:_"<<f;} else {SS2out<<" F:_"<<f;}
  }

  SS2out<<" SPB_vir_LH"<<endl;

  for (p=1;p<=pop;p++)
  {
   for (y=styr-2;y<=YrMax;y++)
   {
    if(y<=endyr && p==1) smry(y).initialize();
    for(s=1;s<=nseas;s++)
    {
    t = styr+(y-styr)*nseas+s-1;
    bio_t=t;
    if(y<=styr) {bio_t=styr-1+s;}
    Bio_Comp.initialize();
    Num_Comp.initialize();
    totbio.initialize(); smrybio.initialize(); spb_vir_LH.initialize();
    Recr(p,y)=0;
    for(g=1;g<=gmorph;g++)
    if(use_morph(g)>0)
    {
     if(s==Bseas(g)) Recr(p,y)+=natage(t,p,g,0);
     gg=sx(g);
     temp=natage(t,p,g)(Smry_Age,nages)*Save_Wt_Age(bio_t,g)(Smry_Age,nages);
     Bio_Comp(GP(g))+=value(temp);   //sums to accumulate across submorphs and birthseasons
     Num_Comp(GP(g))+=value(sum(natage(t,p,g)(Smry_Age,nages)));   //sums to accumulate across submorphs and birthseasons
     totbio += natage(t,p,g)*Save_Wt_Age(bio_t,g);
     smrybio += temp;
     spb_vir_LH += natage(t,p,g)*virg_fec(g);
    } //close gmorph loop
    SS2out<<p<<" "<<y;
       if(y==styr-2)
         {SS2out<<" VIRG ";}
       else if (y==styr-1)
         {SS2out<<" INIT ";}
       else if (y<=endyr)
         {SS2out<<" TIME ";}
       else
         {SS2out<<" FORE ";}

    SS2out<<s<<" "<<totbio<<" "<<smrybio<<" ";
    if(s==spawn_seas) {SS2out<<sum(Spbio(y,p));} else {SS2out<<" _ ";}
    SS2out<<" "<<Recr(p,y)<<" ";
    if(s==spawn_seas)
    {SS2out<<Spbio(y,p);}
    else
    {
    for(gp=1;gp<=N_GP;gp++) {SS2out<<" _ ";}
    }
     SS2out<<" "<<Bio_Comp<<" "<<Num_Comp;
      if(s==1 && y<=endyr) {smry(y,1)+=totbio; smry(y,2)+=smrybio;}			// already calculated for the forecast years
      smry(y,6)=Spbio_tot(y);
      smry(y,7)=use_rec(y);
    for (f=1;f<=Nfleet;f++)
      {
      if(fleet_area(f)==p&&y>=styr-1)
        {
          SS2out<<" "<<catch_fleet(t,f)<<" ";
          if(y<=endyr) {SS2out<<catch_ret_obs(f,t)<<" "<<Hrate(f,t);} else {SS2out<<" _ "<<Hrate(f,t);}
          if(y<=endyr) {smry(y,3)+=catch_fleet(t,f,1); smry(y,4)+=catch_fleet(t,f,2); smry(y,5)+=catch_fleet(t,f,3);}
        }
      else
        {SS2out<<" 0 0 0 0 0 0 0 0 ";}
      }
    if(s==spawn_seas)
        {SS2out<<" "<<spb_vir_LH<<endl;}
    else
      {SS2out<<" _"<<endl;}
    }
   }
  }

    // start SPR time series                                  ProgLabel_0322
   SS2out<<endl<<"SPR_series_uses_R0= "<<R0<<endl<<"###note_Y/R_unit_is_Dead_Biomass"<<endl;
   SS2out<<"Depletion_method: "<<depletion_basis<<" # "<<depletion_basis_label<<endl;
   SS2out<<"F_std_method: "<<F_reporting<<" # "<<F_report_label<<endl;
   SS2out<<"SPR_std_method: "<<SPR_reporting<<" # "<<SPR_report_label<<endl;
   SS2out<<"Year Bio_all Bio_Smry SPBzero SPBfished SPBfished/R SPR SPR_std Y/R GenTime Deplete F_std Actual: Bio_all Bio_Smry Enc_Catch Dead_Catch Retain_Catch SPB Recruits Tot_Exploit"<<
   " More_F(by_morph): ";
   for(g=1;g<=gmorph;g++) {SS2out<<" aveF_"<<g;}
   for(g=1;g<=gmorph;g++) {SS2out<<" maxF_"<<g;}
   SS2out<<endl;

   for (y=styr;y<=YrMax;y++)
     {
//    save_SPR(styr,YrMax,1,6+2*gmorph)  // totbio, smrybio, S0, S1, Gentime, YPR, cumF(g), maxF(g)
     SS2out<<y<<" "<<save_SPR(y)(1,4)<<" "<<value(save_SPR(y,4)/R0)<<" "<<save_SPR(y,4)/save_SPR(y,3)<<" ";
     if(STD_Yr_Reverse_Ofish(y)>0) {SS2out<<SPR_std(STD_Yr_Reverse_Ofish(y))<<" ";} else {SS2out<<" _ ";}
     SS2out<<value(save_SPR(y,6)/R0)<<" "<<save_SPR(y,5)<<" ";
     if(STD_Yr_Reverse_Dep(y)>0) {SS2out<<depletion(STD_Yr_Reverse_Dep(y));} else {SS2out<<" _ ";}
     if(y>=styr && STD_Yr_Reverse_F(y)>0 ) {SS2out<<" "<<F_std(STD_Yr_Reverse_F(y));} else {SS2out<<" _ ";}
     SS2out<<" & "<<smry(y)<<" "<<smry(y,4)/smry(y,2)<<" & "<<save_SPR(y)(7,6+gmorph)<<" "
     <<save_SPR(y)(7+gmorph,6+2*gmorph)<<endl;
     } // end year loop
// end SPR time series

// ******************************************************************************
  dvector rmse(1,Ntypes);    //  used in the SpBio, Index, Lencomp and Agecomp reports
  dvector Hrmse(1,Ntypes);
  dvector Rrmse(1,Ntypes);
  dvector n_rmse(1,Ntypes);
  dvector mean_CV(1,Ntypes);
  dvector mean_CV2(1,Ntypes);
//                                                            ProgLabel_330
  rmse = 0.0;  n_rmse = 0.0;
  SS2out<<endl<<"SPAWN_RECRUIT Function: "<<SR_fxn<<" _ _ _ _ _ _"<<endl<<
  SR_parm(1)<<" Ln(R0) "<<mfexp(SR_parm(1))<<endl<<
  SR_parm(2)<<" steep"<<endl<<
  SR_parm(3)<<" stddev_recr"<<endl<<
  SR_parm(4)<<" env_link_";
  if(SR_env_link>0)
    {
    SS2out<<"to_envvar:_"<<SR_env_link<<"_with_affect_on:";
    if(SR_env_target==1)
      {SS2out<<"_Annual_devs";}
    else if(SR_env_target==2)
      {SS2out<<"_Rzero";}
    else if(SR_env_target==3)
      {SS2out<<"_Steepness";}
    }
  SS2out<<endl<<SR_parm(5)<<" init_eq "<<mfexp(SR_parm(1)+SR_parm(5))<<endl<<
  recdev_start<<" "<<recdev_end<<" recdev:start_end  _ "<<
  recdev_adj<<" begin_and_full_year_for_bias_adjustment "<<endl;
  SS2out<<"year spawn_bio exp_recr with_env bias_adj pred_recr dev use_biasadj era"<<endl;
  SS2out<<"S/Rcurve "<<S0<<" "<<R0<<endl;
  SS2out<<"Virg "<<Spbio_tot(styr-2)<<" "<<exp_rec(styr-2)<<" "<<exp_rec(styr-2)<<" "<<pred_rec(styr-2)<<" "<<use_rec(styr-2)<<" - "<<0.0<<" Virg"<<endl;
  SS2out<<"Init "<<Spbio_tot(styr-1)<<" "<<exp_rec(styr-1)<<" "<<exp_rec(styr-1)<<" "<<pred_rec(styr-1)<<" "<<use_rec(styr-1)<<" - "<<0.0<<" Init"<<endl;

  if(recdev_first<styr)
  {
    for (y=recdev_first;y<=styr-1;y++)
    {
      SS2out<<y<<" "<<Spbio_tot(styr-1)<<" "<<exp_rec(styr-1)<<" _ _ "<<
      exp_rec(styr-1)*mfexp(recdev(y)-biasadj(y)*SR_parm(3)*SR_parm(3)*0.5)<<" "
      <<recdev(y)<<" "<<biasadj(y)<<" Init_age"<<endl;
    }
  }
   for (y=styr;y<=YrMax;y++)
   {
    temp=exp_rec(y);  temp1=log(use_rec(y)/pred_rec(y));
    if(SR_env_target==1) temp*=mfexp(SR_parm(4)* env_data(y,SR_env_link));
     SS2out<<y<<" "<<Spbio_tot(y)<<" "<<exp_rec(y)<<" "
         <<temp<<" "<<pred_rec(y)<<" "<<use_rec(y)<<" ";
     if(recdev_do_early>0 && y>=recdev_early_start && y<=recdev_early_end)
       {SS2out<<temp1<<" "<<biasadj(y)<<" Early";}
     else if(y>=recdev_start && y<=recdev_end)
       {SS2out<<temp1<<" "<<biasadj(y)<<" Main"; rmse(1)+=value(square(temp1)); n_rmse(1)+=1.;}
     else if(Do_Forecast>0 && y>recdev_end)
     {
        SS2out<<temp1<<" "<<biasadj(y);
        if(y<=endyr)
        {SS2out<<" Late";}
        else
        {SS2out<<" Forecast";}
      }
     else
       {SS2out<<" _ _ Fixed";}
     SS2out<<endl;
   }

   if(n_rmse(1)>0 && rmse(1)>0) rmse(1) = sqrt(rmse(1)/n_rmse(1));
   SS2out<<endl<<"N_est r.m.s.e."<<endl<<n_rmse(1)<<" "<<rmse(1)<<endl;

// ******************************************************************************
//                                             ProgLabel_340

  SS2out <<endl<< "INDEX_2" << endl;
  rmse = 0.0;  n_rmse = 0.0; mean_CV=0.0; mean_CV2=0.0;
  SS2out<<"Fleet Yr Vuln_bio Obs Exp Eff_Q SE Dev Like Like+log(s)"<<endl;
  if(nobs>0)
    {
    for(f=1;f<=Ntypes;f++)
      {
      for (i=1;i<=nyr_cr(f);i++)
        {
          if(yr_cr_y(f,i)>=styr && yr_cr_y(f,i)<=retro_yr)
          {
          temp = exp_cr(f,i)+log_q_cr(f,i);
        SS2out<<f<<"_"<<fleetname(f)<<" "<<yr_cr_y(f,i)<<" "<<vul_bio(f,i)<<" "<<obs_cr(f,i)<<" "
        <<mfexp(temp)<<" "<<mfexp(temp)/vul_bio(f,i)<<" "<<sd_cr(f,i);
        if(obs_cr(f,i)>0)
          {
          SS2out<<" "<<Ln_obs_cr(f,i)-temp<<" ";
          if(Q_setup(f,6)==0)
            {
            SS2out<<0.5*square( ( Ln_obs_cr(f,i)-temp ) / sd_cr(f,i))<<" "
            <<0.5*square( ( Ln_obs_cr(f,i)-temp ) / sd_cr(f,i))+log(sd_cr(f,i));}
          else if (Q_setup(f,6)>0)
            {SS2out<<((Q_setup(f,6)+1.)/2.)*log((1.+square((Ln_obs_cr(f,i)-temp ))/(Q_setup(f,6)*square(sd_cr(f,i))) ))<<" "
               <<((Q_setup(f,6)+1.)/2.)*log((1.+square((Ln_obs_cr(f,i)-temp ))/(Q_setup(f,6)*square(sd_cr(f,i))) ))+log(sd_cr(f,i));
            }
          rmse(f)+=value(square(Ln_obs_cr(f,i)-temp)); n_rmse(f)+=1.;
          mean_CV(f)+=cv_cr(f,i); mean_CV2(f)+=value(sd_cr(f,i));
          }
        SS2out<<endl;
      }
        }
        if(n_rmse(f)>0) {rmse(f) = sqrt((rmse(f)+1.0e-9)/n_rmse(f)); mean_CV(f) /= n_rmse(f); mean_CV2(f) /= n_rmse(f);}
      }
    }

  SS2out <<endl<< "INDEX_1" << endl;
  SS2out <<"Fleet Do_Power Power Do_Env_var Env_Link Do_ExtraVar Qtype  Q Num=0/Bio=1 Err_type"<<
    " N Npos r.m.s.e. mean_input_SE Input+VarAdj Input+VarAdj+extra VarAdj New_VarAdj pen_mean_Qdev rmse_Qdev"<<endl;
  for(f=1;f<=Ntypes;f++)
    {
    SS2out<<f<<" "<<Q_setup(f,1)<<" ";
    if(Q_setup(f,1)>0)
      {SS2out<<Q_parm(Q_setup(f,1))<<" ";}
    else
      {SS2out<<" 1.0 ";}
    SS2out<<Q_setup(f,2)<<" ";
    if(Q_setup(f,2)>0)
      {SS2out<<Q_parm(Q_setup_parms(f,2));}
    else
      {SS2out<<" 0.0";}
    SS2out<<Q_setup(f,3)<<" ";
    if(Q_setup(f,3)>0)
      {SS2out<<Q_parm(Q_setup_parms(f,3));}
    else
      {SS2out<<" 0.0";}
    SS2out<<" "<<Q_setup(f,4)<<" ";
    if(nyr_cr(f)>0)
      {SS2out<<mfexp(log_q_cr(f,1));}
    else
      {SS2out<<" _";}
    SS2out<<" "<<Q_setup(f)(5,6)<<" "<<nyr_cr(f)<<" "<<n_rmse(f)<<" "<<rmse(f)<<" "
      <<mean_CV(f)-var_adjust(1,f)<<" "<<mean_CV(f)<<" "<<mean_CV2(f)<<" "<<var_adjust(1,f)
      <<" "<<var_adjust(1,f)+rmse(f)-mean_CV(f)
      <<" "<<Q_dev_like(f,1)<<" "<<Q_dev_like(f,2)<<" "<<fleetname(f)<<endl;
    }
    SS2out<<"rmse_Qdev_not_in_logL"<<endl<<"pen_mean_Qdev_not_in_logL_in_randwalk_approach"<<endl;

  SS2out <<endl<< "INDEX_3"<<endl<<"Fleet  Q_parm_assignments"<<endl;
  for(f=1;f<=Ntypes;f++)
    {SS2out<<f<<" "<<Q_setup_parms(f,1)<<" _ "<<Q_setup_parms(f,2)<<" _ "<<Q_setup_parms(f)(3,4)<<" "<<fleetname(f)<<endl;}

  SS2out <<endl<< "DISCARD  log(L)_based_on_T_distribution_with_DF=_"<<DF_disc<< endl;
  if(disc_type == 1)
   { SS2out << "as_biomass" << endl; }
  else
   { SS2out << "as_fraction" << endl; }

  SS2out<<"Fleet Yr Seas Obs Exp CV Stddev Dev Like Like+log(s)"<<endl;
   if(nobs_disc>0)
   for(f=1;f<=Ntypes;f++)
   for (y=styr;y<=endyr;y++)
   for (s=1;s<=nseas;s++)
   {
    t = styr+(y-styr)*nseas+s-1;
    if(yr_disc2(f,t)>0)
    {
     i=yr_disc2(f,t);
     SS2out<<f<<" "<<y<<" "<<s<<" "<<obs_disc(f,i)<<" "
     <<exp_disc(f,i)<<" "<<" "<<cv_disc(f,i)<<" "<<sd_disc(f,i);
     if(obs_disc(f,i)>=0.0)
     { SS2out<<" "<<obs_disc(f,i)-exp_disc(f,i)<<" "<<
       ((DF_disc+1.)/2.)*log((1.+square(obs_disc(f,i)-exp_disc(f,i))/(DF_disc*square(sd_disc(f,i))) ))<<" "<<
       ((DF_disc+1.)/2.)*log((1.+square(obs_disc(f,i)-exp_disc(f,i))/(DF_disc*square(sd_disc(f,i))) )) + sd_offset*log(sd_disc(f,i));
     }
     SS2out<<endl;
    }
   }
   SS2out<<endl;

  SS2out <<endl<< "MEAN_BODY_WT log(L)_based_on_T_distribution_with_DF=_"<<DF_bodywt<< endl;
  SS2out<<" Fleet Yr Seas Mkt Obs Exp CV Dev NeglogL Neg(logL+log(s)) "<<endl;
  if(nobs_mnwt>0)
  for(i=1;i<=nobs_mnwt;i++)
  {
    SS2out << mnwtdata(3,i)<<" "<<mnwtdata(1,i)<<" "<<mnwtdata(2,i)<<" "<<mnwtdata(4,i)<<" "<<mnwtdata(5,i)<<" ";
    if(mnwtdata(5,i)>0.) SS2out<<" "<<exp_mnwt(i)<<" "<<mnwtdata(6,i)<<" "<<mnwtdata(5,i)-exp_mnwt(i)<<" "<<
     0.5*(DF_bodywt+1.)*log(1.+square(mnwtdata(5,i)-exp_mnwt(i))/mnwtdata(8,i))<<" "<<
     0.5*(DF_bodywt+1.)*log(1.+square(mnwtdata(5,i)-exp_mnwt(i))/mnwtdata(8,i))+ mnwtdata(9,i);
    SS2out<<endl;
  }

  SS2out <<endl<< "FIT_LEN_COMPS" << endl;                     // ProgLabel_350
  SS2out<<"Fleet Yr Seas Gender Mkt Nsamp effN Like"<<endl;
  rmse = 0.0;  n_rmse = 0.0; mean_CV=0.0;  Hrmse=0.0; Rrmse=0.0;
   for(f=1;f<=Ntypes;f++)
   for(i=1;i<=nyr_l(f);i++)
     {
     neff_l(f,i)  = exp_l(f,i)*(1-exp_l(f,i))+1.0e-06;     // constant added for stability
     neff_l(f,i) /= (obs_l(f,i)-exp_l(f,i))*(obs_l(f,i)-exp_l(f,i))+1.0e-06;
      temp=0.00;
     if(gen_l(f,i) !=2)
      {temp -= obs_l(f,i)(tails_l(f,i,1),tails_l(f,i,2)) * log(exp_l(f,i)(tails_l(f,i,1),tails_l(f,i,2)));
       temp += obs_l(f,i)(tails_l(f,i,1),tails_l(f,i,2)) * log(obs_l(f,i)(tails_l(f,i,1),tails_l(f,i,2)));
      }
     if(gen_l(f,i) >=2)
      {temp -= obs_l(f,i)(tails_l(f,i,3),tails_l(f,i,4)) * log(exp_l(f,i)(tails_l(f,i,3),tails_l(f,i,4)));
       temp += obs_l(f,i)(tails_l(f,i,3),tails_l(f,i,4)) * log(obs_l(f,i)(tails_l(f,i,3),tails_l(f,i,4)));
      }
     if(nsamp_l(f,i)>0)
       {n_rmse(f)+=1.; rmse(f)+=value(neff_l(f,i)); mean_CV(f)+=nsamp_l(f,i);
        Hrmse(f)+=value(1./neff_l(f,i)); Rrmse(f)+=value(neff_l(f,i)/nsamp_l(f,i));}
       s=yr_l(f,i)-styr+1-(yr_l_y(f,i)-styr)*nseas;
     SS2out<<f<<" "<<yr_l_y(f,i)<<" "<<s<<" "<<gen_l(f,i)<<" "<<mkt_l(f,i)<<" "<<nsamp_l(f,i)<<" "<<neff_l(f,i)<<" "<<
      temp*sfabs(nsamp_l(f,i))<<endl;
      }
   SS2out<<endl<<"Fleet N Npos mean_effN mean(inputN*Adj) HarMean(effN) Mean(effN/inputN) MeaneffN/MeaninputN Var_Adj"<<endl;
   for(f=1;f<=Ntypes;f++)
   {
    if(n_rmse(f)>0) {rmse(f)/=n_rmse(f); mean_CV(f)/=n_rmse(f); Hrmse(f)=n_rmse(f)/Hrmse(f); Rrmse(f)/=n_rmse(f); }
    SS2out<<f;
    if(nyr_l(f)>0)
    {SS2out<<" "<<nyr_l(f)<<" "<<n_rmse(f)<<" "<<rmse(f)<<" "<<mean_CV(f)<<" "<<Hrmse(f)<<" "<<Rrmse(f)<<" "<<rmse(f)/mean_CV(f)
    <<" "<<var_adjust(4,f)<<" "<<fleetname(f)<<endl;}
    else
    {SS2out<<" _ _ _ _ _ _ _ _ "<<endl;}
   }

  SS2out <<endl<< "FIT_AGE_COMPS" << endl;                        // ProgLabel_360
  SS2out<<"Fleet Yr Seas Gender Mkt Ageerr Lbin_lo Lbin_hi Nsamp effN Like"<<endl;
  rmse = 0.0;  n_rmse = 0.0; mean_CV=0.0;  Hrmse=0.0; Rrmse=0.0;
   if(nobsa>0)
   for(f=1;f<=Ntypes;f++)
   for(i=1;i<=nyr_a(f);i++)
     {  neff_a(f,i)  = exp_a(f,i)*(1-exp_a(f,i))+1.0e-06;     // constant added for stability
     neff_a(f,i) /= (obs_a(f,i)-exp_a(f,i))*(obs_a(f,i)-exp_a(f,i))+1.0e-06;
      temp=0.00;
     if(gen_a(f,i) !=2)
      {temp -= obs_a(f,i)(tails_a(f,i,1),tails_a(f,i,2)) * log(exp_a(f,i)(tails_a(f,i,1),tails_a(f,i,2)));
       temp += obs_a(f,i)(tails_a(f,i,1),tails_a(f,i,2)) * log(obs_a(f,i)(tails_a(f,i,1),tails_a(f,i,2)));
      }
     if(gen_a(f,i) >=2)
      {temp -= obs_a(f,i)(tails_a(f,i,3),tails_a(f,i,4)) * log(exp_a(f,i)(tails_a(f,i,3),tails_a(f,i,4)));
       temp += obs_a(f,i)(tails_a(f,i,3),tails_a(f,i,4)) * log(obs_a(f,i)(tails_a(f,i,3),tails_a(f,i,4)));
      }
     if(nsamp_a(f,i)>0)
       {
        n_rmse(f)+=1.; rmse(f)+=value(neff_a(f,i)); mean_CV(f)+=nsamp_a(f,i);
        Hrmse(f)+=value(1./neff_a(f,i)); Rrmse(f)+=value(neff_a(f,i)/nsamp_a(f,i));
       }
         s=yr_a(f,i)-styr+1-(yr_a_y(f,i)-styr)*nseas;
      SS2out<<f<<" "<<yr_a_y(f,i)<<" "<<s<<" "<<gen_a(f,i)<<" "<<mkt_a(f,i)<<" "<<ageerr_type_a(f,i)<<" "<<Lbin_lo(f,i)<<" "<<Lbin_hi(f,i)<<" "<<nsamp_a(f,i)<<" "<<neff_a(f,i)<<" "<<
      temp*sfabs(nsamp_a(f,i))<<endl;
      }
   SS2out<<endl<<"Fleet N Npos mean_effN mean(inputN*Adj) HarMean(effN) Mean(effN/inputN) MeaneffN/MeaninputN Var_Adj"<<endl;
   for(f=1;f<=Ntypes;f++)
   {
    if(n_rmse(f)>0) {rmse(f)/=n_rmse(f); mean_CV(f)/=n_rmse(f); Hrmse(f)=n_rmse(f)/Hrmse(f); Rrmse(f)/=n_rmse(f); }
    SS2out<<f;
    if(nyr_a(f)>0)
    {SS2out<<" "<<nyr_a(f)<<" "<<n_rmse(f)<<" "<<rmse(f)<<" "<<mean_CV(f)<<" "<<Hrmse(f)<<" "<<Rrmse(f)<<" "<<rmse(f)/mean_CV(f)
    <<" "<<var_adjust(5,f)<<" "<<fleetname(f)<<endl;}
    else
    {SS2out<<" _ _ _ _ _ _ _ _ "<<endl;}
   }


   SS2out <<endl<< "LEN_SELEX" << endl;     // ProgLabel_370
  SS2out<<"Fleet year gender label "<<len_bins_m<<endl;
  for (f=1;f<=Ntypes;f++)
    {
    if(f<=Nfleet) {j=1;} else {j=0;}
    for (y=styr;y<=endyr+j;y++)
  for (gg=1;gg<=gender;gg++)
   if(y==endyr || (time_vary_sel(y,f)>0 || time_vary_sel(y+1,f)>0))
  {
   SS2out<<f<<" "<<y<<" "<<gg<<" "<<y<<"_"<<f;
   for(z=1;z<=nlength;z++)
   {SS2out<<" "<<sel_l(y,f,gg,z);}
   SS2out<<endl;
    }
    }

  SS2out <<endl<< "RETENTION" << endl;            // ProgLabel_390
  SS2out<<"Fleet year gender label "<<len_bins_m<<endl;
  for (f=1;f<=Nfleet;f++)
  for (y=styr;y<=endyr;y++)
  for (gg=1;gg<=gender;gg++)
   if(time_vary_sel(y,f)>0)
  {
   SS2out<<f<<" "<<y<<" "<<gg<<" "<<y<<"_"<<f;
   if(gg==1) {for(z=1;z<=nlength;z++) {SS2out<<" "<<retain(y,f,z);}}
   else
    {for(z=nlength1;z<=nlength2;z++) {SS2out<<" "<<retain(y,f,z);}}
   SS2out<<endl;
  }

  SS2out <<endl<< "DISCARD_MORT" << endl;            // ProgLabel_390
  SS2out<<"fleet year gender label "<<len_bins_m<<endl;
  for (f=1;f<=Nfleet;f++)
  for (y=styr;y<=endyr;y++)
  for (gg=1;gg<=gender;gg++)
   if(time_vary_sel(y,f)>0)
  {
   SS2out<<f<<" "<<y<<" "<<gg<<" "<<y<<"_"<<f;
   if(gg==1) {for(z=1;z<=nlength;z++) {SS2out<<" "<<discmort(y,f,z);}}
   else
    {for(z=nlength1;z<=nlength2;z++) {SS2out<<" "<<discmort(y,f,z);}}
   SS2out<<endl;
  }
   SS2out <<endl<< "KEEPERS equals_sel*retain" << endl;     // ProgLabel_370
  SS2out<<"Fleet year gender label "<<len_bins_m<<endl;
  for (f=1;f<=Nfleet;f++)
    {
    for (y=styr;y<=endyr+1;y++)
  for (gg=1;gg<=gender;gg++)
   if(time_vary_sel(y,f)>0)
  {
   SS2out<<f<<" "<<y<<" "<<gg<<" "<<y<<"_"<<f;
   for(z=1;z<=nlength;z++)
   {SS2out<<" "<<sel_l_r(y,f,gg,z);}
   SS2out<<endl;
    }}

  SS2out <<endl<< "DEADFISH equals_sel*(retain+(1-retain)*discmort)" << endl;     // ProgLabel_370
  SS2out<<"fleet year gender label "<<len_bins_m<<endl;
  for (f=1;f<=Nfleet;f++)
    {
    for (y=styr;y<=endyr+1;y++)
    for (gg=1;gg<=gender;gg++)
    if(time_vary_sel(y,f)>0)
      {
      SS2out<<f<<" "<<y<<" "<<gg<<" "<<y<<"_"<<f;
      for(z=1;z<=nlength;z++)
        {SS2out<<" "<<discmort2(y,f,gg,z);}
      SS2out<<endl;
      }
    }

  SS2out <<endl<< "AGE_SELEX" << endl;
  SS2out<<"fleet year gender label ";
  for(a=0;a<=nages;a++)
    {SS2out<<" "<<a;}
   SS2out<<endl;
  for (f=1;f<=Ntypes;f++)
    {
    if(f<=Nfleet) {j=1;} else {j=0;}
    for (y=styr;y<=endyr+j;y++)
  for(gg=1;gg<=gender;gg++)
   if(y==endyr || (time_vary_sel(y,f+Ntypes)>0 || time_vary_sel(y+1,f+Ntypes)>0))
  {
   SS2out<<f<<" "<<y<<" "<<gg<<" "<<y<<"_"<<f;
   for(a=0;a<=nages;a++)
   {SS2out<<" "<<sel_a(y,f,gg,a);}
   SS2out<<endl;
    }
    }

  SS2out <<endl<< "Average_size_selex_at_age_in_endyear(ALK*selL)" << endl;     // ProgLabel_380
  SS2out<<"Fleet Yr Morph Seas ";
  if(reportdetail>0)
  {
  for(a=0;a<=nages;a++) SS2out<<a<<" ";
  SS2out<<endl;
      for(f=1;f<=Ntypes;f++)
      for(g=1;g<=gmorph;g++)
      {
        if(use_morph(g)>0)
        {
          for(s=1;s<=nseas;s++)
          { SS2out<<f<<" "<<endyr<<" "<<g<<" "<<s<<" "<<ALK(s,g)*sel_l(endyr,f,sx(g));
          SS2out<<endl;
        }
      }
      }
   }
  SS2out <<endl<< "COMBINED_ALK*selL*selA*wtlen*ret*discmort_in_endyear_" << endl;     // ProgLabel_380
  SS2out<<"Fleet Yr Morph Seas Label ";
  if(reportdetail>0)
  {
  for(a=0;a<=nages;a++) SS2out<<a<<" ";
  SS2out<<endl;
      for(f=1;f<=Nfleet;f++)
       for(g=1;g<=gmorph;g++)
       if(use_morph(g)>0)
       for(s=1;s<=nseas;s++)
        {
        SS2out<<f<<" "<<endyr<<" "<<g<<" "<<s<<" sel*wt "<<sel_al_1(s,g,f)<<endl;
        SS2out<<f<<" "<<endyr<<" "<<g<<" "<<s<<" sel*ret*wt "<<sel_al_2(s,g,f)<<endl;
        SS2out<<f<<" "<<endyr<<" "<<g<<" "<<s<<" sel_nums "<<sel_al_3(s,g,f)<<endl;
        SS2out<<f<<" "<<endyr<<" "<<g<<" "<<s<<" sel*ret_nums "<<sel_al_4(s,g,f)<<endl;
        SS2out<<f<<" "<<endyr<<" "<<g<<" "<<s<<" dead_nums "<<deadfish(s,g,f)<<endl;
        SS2out<<f<<" "<<endyr<<" "<<g<<" "<<s<<" dead*wt "<<deadfish_B(s,g,f)<<endl;
        SS2out<<f<<" "<<endyr<<" "<<g<<" "<<s<<" bodywt "<<fish_body_wt(s,g,f)<<endl;
        }
      }

   SS2out << endl<<"ENVIRONMENTAL_DATA Begins_in_startyr-1"<<endl;         // ProgLabel_397
   if(N_envdata>=1)
   {
   SS2out<<"Year "; for(i=-2;i<=N_envvar;i++) SS2out<<" "<<i;
   SS2out<<endl;
    for (y=styr-1;y<=YrMax;y++)
    {
     SS2out<<y<<" "<<env_data(y)<<endl;
    }
    SS2out<<endl;
   }

  SS2out<<endl<<"TAG_Recapture"<<endl;
  SS2out<<TG_mixperiod<<" First period to use recaptures in likelihood"<<endl;
  SS2out<<TG_maxperiods<<" Accumulation period"<<endl;
  if(Do_TG>0)
  {
    SS2out<<" Tag_release_info"<<endl;
    SS2out<<"TAG Area Yr Seas Time Gender Age Nrelease Init_Loss Chron_Loss"<<endl;;
    for(TG=1;TG<=N_TG;TG++)
    {
      SS2out<<TG<<" "<<TG_release(TG)(2,8)<<" "<<TG_save(TG)(1,2)<<endl;
    }
    SS2out<<"Tags_Alive ";
    k=max(TG_endtime);
    for(t=0;t<=k;t++) SS2out<<t<<" ";
    SS2out<<endl;
    for(TG=1;TG<=N_TG;TG++)
    {
      SS2out<<TG<<" "<<TG_save(TG)(3,3+TG_endtime(TG))<<endl;
    }
    SS2out<<"Total_recaptures ";
    for(t=0;t<=k;t++) SS2out<<t<<" ";
    SS2out<<endl;
    for(TG=1;TG<=N_TG;TG++)
    {
      SS2out<<TG<<" ";
      for(TG_t=0;TG_t<=TG_endtime(TG);TG_t++) SS2out<<TG_recap_exp(TG,TG_t,0)<<" ";
      SS2out<<endl;
    }

    SS2out<<endl<<"Reporting_Rates_by_Fishery"<<endl<<"Fleet Init_Reporting Report_Decay"<<endl;
    for(f=1;f<=Nfleet;f++) SS2out<<f<<" "<<TG_report(f)<<" "<<TG_rep_decay(f)<<endl;
    SS2out<<"See_composition_data_output_for_tag_recapture_details"<<endl;
  }


// ************************                     ProgLabel_400
  if(reportdetail>0)
  {
    SS2out << endl << "NUMBERS_AT_AGE" << endl;       // ProgLabel_410
    SS2out << "Area Bio_Pattern Gender BirthSeas SubMorph Morph Yr Seas Time Era"<<age_vector <<endl;
    for (p=1;p<=pop;p++)
    for (g=1;g<=gmorph;g++)
    if(use_morph(g)>0)
      {
      for (y=styr-2;y<=YrMax;y++)
      for (s=1;s<=nseas;s++)
       {
       t = styr+(y-styr)*nseas+s-1;
       temp=double(y)+double(s-1.)/nseas;
       SS2out <<p<<" "<<GP4(g)<<" "<<sx(g)<<" "<<Bseas(g)<<" "<<GP2(g)<<" "<<g<<" "<<y<<" "<<s<<" "<<temp;
       if(y==styr-2)
         {SS2out<<" VIRG ";}
       else if (y==styr-1)
         {SS2out<<" INIT ";}
       else if (y<=endyr)
         {SS2out<<" TIME ";}
       else
         {SS2out<<" FORE ";}
       SS2out<< natage(t,p,g) << endl;
       }
      }

     SS2out <<endl<< "CATCH_AT_AGE" << endl;              // ProgLabel_420
     SS2out << "Area Fleet Gender  XX XX Morph Yr Seas XX Era"<<age_vector <<endl;
     for (f=1;f<=Nfleet;f++)
     for (g=1;g<=gmorph;g++)
     {
     if(use_morph(g)>0)
     {
       for (y=styr-1;y<=endyr;y++)
       for (s=1;s<=nseas;s++)
       {
         t = styr+(y-styr)*nseas+s-1;
         SS2out <<fleet_area(f)<<" "<<f<<" "<<sx(g)<<" XX XX "<<g<<" "<<y<<" "<<s;
         if(y==styr-1)
           {SS2out<<" XX INIT ";}
         else if (y<=endyr)
           {SS2out<<" XX TIME ";}
         else
           {SS2out<<" XX FORE ";}
         SS2out<<catage(t,f,g)<< endl;
       }
     }
    }
  }

  SS2out <<endl<< "BIOLOGY "<<sum(use_morph)<<" "<<nlength<<" "<<nages<<" "<<nseas<<" N_Used_morphs;_lengths;_ages;_season;_by_season_in_endyr" << endl;               // ProgLabel_430
   SS2out<<"Bin Low Mean_Size Wt_len_F Mat_len Spawn Wt_len_M Fecundity"<<endl;
   for (z=1;z<=nlength;z++)
     {SS2out<<z<<" "<<len_bins(z)<<" "<<len_bins_m(z)<<" "<<wt_len(1,1,z)<<" "<<mat_len(z)<<" "<<mat_len_wt(z);
      if(gender==2) {SS2out<<" "<<wt_len(1,2,z);}
      SS2out<<" "<<fec_len(z)<<endl;
     }

    SS2out<<endl<<"Natural_Mortality Method:_"<<natM_type<<endl<<"Yr Bio_Pattern Gender BirthSeas Seas "<<age_vector<<endl;
    for(k=0;k<=1;k++)
    {
      y=styr+k*(endyr-styr);
      t_base=styr+(y-styr)*nseas-1;
      g=0;
      for(gg=1;gg<=gender;gg++)
      for(gp=1;gp<=N_GP;gp++)
      for(birthseas=1;birthseas<=nseas;birthseas++)
      {
        g++;
        if(use_morph(g)>0)
        {for(s=1;s<=nseas;s++) SS2out<<y<<" "<<gp<<" "<<gg<<" "<<birthseas<<" "<<s<<" "<<natM(s,g)<<endl;}
      }
    }

//                                                                ProgLabel_440

   SS2out<<endl<<"Growth_Parameters"<<endl<<" Count Yr Morph A1 A2 L_a_A1 L_a_A2 K A_a_L0 Linf CVmin CVmax natM_amin natM_max M_young M_old"
   <<" WtLen1 WtLen2 Mat1 Mat2 Fec1 Fec2"<<endl;
   for(g=1;g<=save_gparm_print;g++) {SS2out<<save_G_parm(g)<<endl;}

   if(MGparm_doseas>0)
    {
   SS2out<<endl<<"Seas_Effects"<<endl<<"Seas F_wtlen1 F_wtlen2 F_mat1 F_mat2 F_fec1 F_fec2 M_wtlen1 M_wtlen2 L_a_A1 VBK"<<endl;
      for(s=1;s<=nseas;s++)
      {
        SS2out<<s<<" "<<save_seas_parm(s)<<endl;
      }
    }
   SS2out<<"Biology_at_age"<<endl;
   SS2out<<"Seas Morph Bio_Pattern Gender BirthSeas Age Age_Beg Age_Mid M Len_Beg Len_Mid SD_Beg SD_Mid Wt_Beg Wt_Mid Len_Mat Age_Mat Mat*Fecund";
   for(f=1;f<=Ntypes;f++) SS2out<<" Len:_"<<f<<" SelWt:_"<<f<<" RetWt:_"<<f;
   SS2out<<endl;
   for (s=1;s<=nseas;s++)
   {t = styr+(endyr-styr)*nseas+s-1;
   for(g=1;g<=gmorph;g++)
     if(use_morph(g)>0)
   {
     for(a=0;a<=nages;a++)
     {
      SS2out<<s<<" "<<g<<" "<<GP(g)-(sx(g)-1)*N_GP<<" "<<sx(g)<<" "<<Bseas(g)<<" "<<a<<" "<<a+azero_seas(s)-azero_G(g)<<" "<<a+azero_seas(s)-azero_G(g)+seasdur2(s);
      SS2out<<" "<<natM(s,GP3(g),a)<<" "<<Save_Ave_Size(t,0,g,a)<<" "<<Save_Ave_Size(t,1,g,a)<<" "
        <<Sd_Size_within(s,g,a)<<" "<<Sd_Size_within(s+nseas,g,a)<<" "
      <<Wt_Age_beg(s,g,a)<<" "<<ALK(s,g,a)*wt_len(s,sx(g))<<" "<<ALK(s,g,a)*mat_len<<" ";
      if(Maturity_Option<=2)
        {SS2out<<mat_age(a);}
      else if(sx(g)==1)
        {SS2out<<Age_Maturity(GP(g),a);}
      else
        {SS2out<<-1.;}
      SS2out<<" "<<fec(g,a);
      for(f=1;f<=Ntypes;f++) SS2out<<
        " "<<ALK(s,g,a)*elem_prod(sel_l(endyr,f,sx(g)),len_bins_m)/(ALK(s,g,a)*sel_l(endyr,f,sx(g)))<<
        " "<<ALK(s,g,a)*elem_prod(sel_l(endyr,f,sx(g)),wt_len(s,sx(g)))/(ALK(s,g,a)*sel_l(endyr,f,sx(g)))<<
        " "<<ALK(s,g,a)*elem_prod(sel_l_r(endyr,f,sx(g)),wt_len(s,sx(g)))/(ALK(s,g,a)*sel_l_r(endyr,f,sx(g)));
      SS2out<<endl;
      }}}


  SS2out <<endl<< "MEAN_BODY_WT(begin)" << endl;
  SS2out <<"Morph Yr Seas";
  if(reportdetail>0)
  {
  for (a=0;a<=nages;a++) SS2out << " "<<a;
       SS2out<<endl;

    for(g=1;g<=gmorph;g++)
    if(use_morph(g)>0)
    {
    for(y=styr;y<=YrMax;y++)
    for(s=1;s<=nseas;s++)
     {
      t = styr+(y-styr)*nseas+s-1;
       SS2out<<g<<" "<<y<<" "<<s<<" "<<Save_Wt_Age(t,g)<<endl;
     }
    }
  }

  SS2out <<endl<< "MEAN_SIZE_TIMESERIES" << endl;           // ProgLabel_450
  SS2out <<"Morph Yr Seas Beg/Mid"<<age_vector<<endl;
  if(reportdetail>0)
  {
    for(g=1;g<=gmorph;g++)
    if(use_morph(g)>0)
    {
    for(y=styr;y<=YrMax;y++)
    for(s=1;s<=nseas;s++)
     {
      t = styr+(y-styr)*nseas+s-1;
      for(i=0;i<=1;i++)
      {
       if(Save_Ave_Size(t,i,g,nages)>0) SS2out<<g<<" "<<y<<" "<<s<<" "<<i<<" "<< Save_Ave_Size(t,i,g)<<endl;
      }
     }
    }
  }
  if(reportdetail>0)
  {
    s=1;
    for (i=1;i<=gender;i++)
    {
     SS2out<<endl<<" mean_size_Jan_1_for_gender: "<<i<<endl;
     for(y=styr;y<=YrMax;y++)
     {
      t = styr+(y-styr)*nseas+s-1;
      SS2out<<i<<" "<<y<<" "<<s<<" "<<0;
      for (a=0;a<=nages;a++)
      {
       temp=0.0;
       temp1=0.0;
       for(g=1;g<=gmorph;g++)
       {
        if(sx(g)==i && use_morph(g)>0)
        {
         for(p=1;p<=pop;p++)
         {
          temp+=natage(t,p,g,a);
          temp1+=Save_Ave_Size(t,0,g,a)*natage(t,p,g,a);
         }
         SS2out <<" "<< temp1/temp;
        }
       }
      }
      SS2out<<endl;
     }
    }
  }

  if(reportdetail>0)
  {
  SS2out <<endl<< "AGE_LENGTH_KEY"<<endl;               // ProgLabel_460
  SS2out<<" sdratio "<<sd_ratio<<endl;
  SS2out<<" sdwithin "<<sd_withinmorph<<endl;
  SS2out<<" sdbetween "<<sd_betweenmorph<<endl;
   for (s=1;s<=nseas;s++)
   for (g=1;g<=gmorph;g++)
     if(use_morph(g)>0)
   {
    t = styr+(endyr-styr)*nseas+s-1;
    SS2out <<endl<<" Seas: "<<s<<"   Morph: "<<g<<endl;
    SS2out <<"Age:";
  for (a=0;a<=nages;a++) SS2out << " "<<a;
       SS2out<<endl;
    for (z=nlength;z>=1;z--)
     {
      SS2out << len_bins2(z) << " ";
      for (a=0;a<=nages;a++)
        SS2out << ALK(s,g,a,z) << " " ;
      SS2out<<endl;
     }
      SS2out<<"mean " << Save_Ave_Size(t,1,g) << endl;
      SS2out<<"sdsize " << Sd_Size_within(s+nseas,g) << endl;
       }
      }

  if(reportdetail>0)
  {
  SS2out <<endl<< "AGE_AGE_KEY"<<endl;              // ProgLabel_470
    for (k=1;k<=N_ageerr;k++)
    {
    SS2out << "KEY: "<<k<<endl<< "mean " << age_err(k,1) << endl<< "SD " << age_err(k,2) << endl;
    for (b=n_abins;b>=1;b--)
     {
      SS2out << age_bins(b) << " ";
      for (a=0;a<=nages;a++)
        SS2out << age_age(k,b,a) << " " ;
      SS2out<<endl;
       }
     if(gender==2)
     {
     L2=n_abins;
     A2=nages+1;
    for (b=n_abins;b>=1;b--)
     {
      SS2out << age_bins(b) << " ";
      for (a=0;a<=nages;a++)
        SS2out << age_age(k,b+L2,a+A2) << " " ;
      SS2out<<endl;
       }
     }
     }
    }
    if(N_ageerr==0) SS2out<<"no_age_error_key_used"<<endl;

//  ********  report the composition database
  SS2out<<endl<<"Size_Bins_pop"<<endl;
  SS2out<<"Bin: ";
  for(j=1;j<=nlength;j++) SS2out<<" "<<j;
  SS2out<<endl<<"Length: "<<len_bins<<endl;
  SS2out<<"Len_mid: "<<len_bins_m<<endl;
  SS2out<<"Pop_len_mid_used_for_calc_of_selex_and_bio_quantities";
  SS2out<<"Size_Bins_dat"<<endl;
  SS2out<<"Bin: ";
  for(j=1;j<=nlen_bin;j++) SS2out<<" "<<j;
  SS2out<<endl<<"Length: "<<len_bins_dat<<endl;
  SS2out<<"Len_mid: "<<len_bins_dat_m<<endl;
  SS2out<<"Data_len_mid_for_reporting_only";

  SS2out<<"Combine_males_with_females_thru_sizedata_bin: "<<CombGender_l;
  if(CombGender_l>0) SS2out<<"   Size: "<<len_bins_dat(CombGender_l);
  SS2out<<endl<<"Combine_males_with_females_thru_agedata_bin: "<<CombGender_a;
  if(CombGender_a>0) SS2out<<"   Size: "<<age_bins(CombGender_a);
  SS2out<<endl<<"Method_for_Lbin_definition_for_agecomp_data: "<<Lbin_method<<endl;

  if(WtFreq_Nmeth>0) SS2out<<"For Sizefreq, Lbin_Lo is units(bio or numbers); Lbin_hi is scale(kg, lb, cm, in), Ageerr is method"<<endl;
  if(Do_TG>0) SS2out<<"For Tag output, Rep contains Tag_Group, Bin is fleet for TAG1 and Bin is Year.Seas for TAG2"<<endl;
  SS2out <<endl<< "Composition_Database" << endl;           // ProgLabel_480
  SS2out<<"Yr Seas Fleet Rep Pick_gender Kind Part Ageerr Gender Lbin_lo Lbin_hi Bin Obs Exp Pearson N effN Like Used"<<endl;
	 double DevResid;
   for (y=styr;y<=endyr;y++)
   {
    for (s=1;s<=nseas;s++)
    {
     t = styr+(y-styr)*nseas+s-1;
     temp1=s-1.;
     temp2=y;
     temp=temp2+temp1/nseas;
     for(f=1;f<=Ntypes;f++)
     {
      if(yr_l2(1,f,t)>0)
      {
       for(i=yr_l2(1,f,t);i<=yr_l2(2,f,t);i++)                          // loop obs in this type/time
       {
        if(gen_l(f,i)!=2)
         {s_off=1;
         for(z=tails_l(f,i,1);z<=tails_l(f,i,2);z++)
          {SS2out<<temp<<" "<<s<<" "<<f<<" "<<j<<" "<<gen_l(f,i)<<" LEN "<<mkt_l(f,i)<<" 0 "<<s_off<<" "<<
          1<<" "<<1<<" "<<len_bins_dat2(z)<<" "<<obs_l(f,i,z)<<" "<<exp_l(f,i,z)<<" "<<
         value((obs_l(f,i,z)-exp_l(f,i,z))/sqrt( exp_l(f,i,z) * (1-exp_l(f,i,z)) / sfabs(nsamp_l(f,i))))
         <<" "<<nsamp_l(f,i)<<" "<<neff_l(f,i);
         DevResid=value(obs_l(f,i,z)*log(obs_l(f,i,z)/exp_l(f,i,z))*nsamp_l(f,i));
				 SS2out<<" "<<DevResid;
         if(nsamp_l(f,i)>0) SS2out<<" 1";  SS2out<<endl;}
         SS2out<<temp<<" "<<s<<" "<<f<<" "<<j<<" "<<gen_l(f,i)<<" LEN "
          <<mkt_l(f,i)<<" 0 "<<s_off<<" "<<1<<" "<<1<<endl;}

          if(gen_l(f,i)>=2)
          {s_off=2;
         for(z=tails_l(f,i,3);z<=tails_l(f,i,4);z++)
          {SS2out<<temp<<" "<<s<<" "<<f<<" "<<j<<" "<<gen_l(f,i)<<" LEN "<<mkt_l(f,i)<<" 0 "<<s_off<<" "<<
          1<<" "<<nlength<<" "<<len_bins_dat2(z)<<" "<<obs_l(f,i,z)<<" "<<exp_l(f,i,z)<<" "<<
         value((obs_l(f,i,z)-exp_l(f,i,z))/sqrt( exp_l(f,i,z) * (1- exp_l(f,i,z)) / sfabs(nsamp_l(f,i))))
         <<" "<<nsamp_l(f,i)<<" "<<neff_l(f,i);
         DevResid=value(obs_l(f,i,z)*log(obs_l(f,i,z)/exp_l(f,i,z))*nsamp_l(f,i));
				 SS2out<<" "<<DevResid;
         if(nsamp_l(f,i)>0) SS2out<<" 1";  SS2out<<endl;}
         SS2out<<temp<<" "<<s<<" "<<f<<" "<<j<<" "<<gen_l(f,i)<<" LEN "
          <<mkt_l(f,i)<<" 0 "<<s_off<<" "<<1<<" "<<1<<endl;

            }
       }
      }  //end have data

      if(yr_a2(1,f,t)>0)
      {
       for(i=yr_a2(1,f,t);i<=yr_a2(2,f,t);i++)                          // loop obs in this type/time
       {
        if(gen_a(f,i)!=2)
         {s_off=1;
         for(z=tails_a(f,i,1);z<=tails_a(f,i,2);z++)
          {SS2out<<temp<<" "<<s<<" "<<f<<" "<<j<<" "<<gen_a(f,i)<<" AGE "<<mkt_a(f,i)<<" "<<ageerr_type_a(f,i)
         <<" "<<s_off<<" "<<len_bins(Lbin_lo(f,i))<<" "<<len_bins(Lbin_hi(f,i))<<" "<<age_bins(z)<<" "<<obs_a(f,i,z)
         <<" " <<exp_a(f,i,z)<<" "<<
        value((obs_a(f,i,z)-exp_a(f,i,z))/sqrt( exp_a(f,i,z) * (1-exp_a(f,i,z)) / sfabs(nsamp_a(f,i))))
        <<" "<<nsamp_a(f,i)<<" "<<neff_a(f,i);
         DevResid=value(obs_a(f,i,z)*log(obs_a(f,i,z)/exp_a(f,i,z))*nsamp_a(f,i));
				 SS2out<<" "<<DevResid;
         if(nsamp_a(f,i)>0) SS2out<<" 1";  SS2out<<endl;}
        SS2out<<temp<<" "<<s<<" "<<f<<" "<<j<<" "<<gen_a(f,i)<<" AGE "
         <<mkt_a(f,i)<<" "<<ageerr_type_a(f,i)<<" "<<s_off<<" "<<1<<" "<<nlength<<endl;}
        if(gen_a(f,i)>=2)
         {s_off=2;
         for(z=tails_a(f,i,3);z<=tails_a(f,i,4);z++)
          {SS2out<<y+(s-1)/4<<" "<<s<<" "<<f<<" "<<j<<" "<<gen_a(f,i)<<" AGE "<<mkt_a(f,i)<<" "<<ageerr_type_a(f,i)
         <<" "<<s_off<<" "<<len_bins(Lbin_lo(f,i))<<" "<<len_bins(Lbin_hi(f,i))<<" "<<age_bins(z)<<" "<<obs_a(f,i,z)<<" "
        <<exp_a(f,i,z)<<" "<<
        value((obs_a(f,i,z)-exp_a(f,i,z))/sqrt( exp_a(f,i,z) * (1-exp_a(f,i,z)) / sfabs(nsamp_a(f,i))))
        <<" "<<nsamp_a(f,i)<<" "<<neff_a(f,i);
         DevResid=value(obs_a(f,i,z)*log(obs_a(f,i,z)/exp_a(f,i,z))*nsamp_a(f,i));
				 SS2out<<" "<<DevResid;
         if(nsamp_a(f,i)>0) SS2out<<" 1";  SS2out<<endl;}
        SS2out<<temp<<" "<<s<<" "<<f<<" "<<j<<" "<<gen_a(f,i)<<" AGE "
         <<mkt_a(f,i)<<" "<<ageerr_type_a(f,i)<<" "<<s_off<<" "<<1<<" "<<nlength<<endl;}
       }
      }  //end have data

      if(yr_ms2(1,f,t)>0)
      {
       for(i=yr_ms2(1,f,t);i<=yr_ms2(2,f,t);i++)
       {
       for(z=1;z<=n_abins2;z++)
       {
        if(z<=n_abins) s_off=1; else s_off=2;
        t1=obs_ms_n(f,i,z);
        if(t1>0) t1=square(t1);
        SS2out<<temp<<" "<<s<<" "<<f<<" "<<j<<" "<<gen_ms(f,i)<<" L@A "<<mkt_ms(f,i)<<" "<<
         ageerr_type_ms(f,i)<<" "<<s_off<<" "<<1<<" "<<nlen_bin<<" "<<age_bins(z)<<" "<<
         obs_ms(f,i,z)<<" "<<exp_ms(f,i,z)<<" ";
        if(obs_ms(f,i,z)>0 && t1>0)
          {SS2out<<(obs_ms(f,i,z) -exp_ms(f,i,z)) / (exp_ms_sq(f,i,z)/obs_ms_n(f,i,z))<<" "<<t1<<" _ "
            <<fabs((obs_ms(f,i,z) -exp_ms(f,i,z)) / (exp_ms_sq(f,i,z)/obs_ms_n(f,i,z)));
           if(use_ms(f,i)>0) SS2out<<" 1";
           SS2out<<endl;}
        else
          {SS2out<<endl;}
        if(z==n_abins || z==n_abins2) SS2out<<temp<<" "<<s<<" "<<f<<" "<<j<<" "<<gen_ms(f,i)<<
         " L@A "<<mkt_ms(f,i)<<" "<<ageerr_type_ms(f,i)<<" "<<s_off<<" "<<1<<" "<<nlen_bin<<endl;
       }
      }  //end have data
      }
     }  // end fleet
    }  // end season
   }  // end year


//          for(iobs=WtFreq_HaveObs(f,WtFreqMethod,t,1);iobs<=WtFreq_HaveObs(f,WtFreqMethod,t,2);iobs++)

    if(WtFreq_Nmeth>0)       //  have some wtfreq data
    {
      for(iobs=1;iobs<=WtFreq_totobs;iobs++)
      {
        y=WtFreq_obs_hdr(iobs,1);
        s=WtFreq_obs_hdr(iobs,2);
        temp1=s-1.;
        temp2=y;
        temp=temp2+temp1/nseas;
        f=WtFreq_obs_hdr(iobs,3);
        gg=WtFreq_obs_hdr(iobs,4);  // gender
        k=WtFreq_obs_hdr(iobs,6);
        if(k>0)  // flag for date range in bounds
        {
        p=WtFreq_obs_hdr(iobs,5);  // partition
        z1=WtFreq_obs_hdr(iobs,7);
        z2=WtFreq_obs_hdr(iobs,8);
        for(z=z1;z<=z2;z++)
        {
          s_off=1;
        SS2out<<temp<<" "<<s<<" "<<f<<" "<<1<<" "<<gg<<" SIZE "<<p<<" "<<k;
        if(z>WtFreq_Nbins(k)) s_off=2;
         SS2out<<" "<<s_off<<" "<<WtFreq_units(k)<<" "<<WtFreq_scale(k)<<" "<<WtFreq_bins(k,z)<<" "<<WtFreq_obs(iobs,z)
         <<" " <<WtFreq_exp(iobs,z)<<" "<<
        value((WtFreq_obs(iobs,z)-WtFreq_exp(iobs,z))/sqrt( WtFreq_exp(iobs,z) * (1-WtFreq_exp(iobs,z)) / sfabs(WtFreq_effN(iobs))))
        <<" "<<WtFreq_effN(iobs)<<" "<<-1;
         DevResid=value(WtFreq_obs(iobs,z)*log(WtFreq_obs(iobs,z)/WtFreq_exp(iobs,z))*WtFreq_effN(iobs));
         SS2out<<" "<<DevResid;
         if(WtFreq_effN(iobs)>0) SS2out<<" 1";  SS2out<<endl;
         if(z==z2 || z==WtFreq_Nbins(k))
         SS2out<<temp<<" "<<s<<" "<<f<<" "<<1<<" "<<gg<<" SIZE "<<p<<" "<<k<<" "<<s_off<<" "<<0<<" "<<0<<endl;
          }
        }
      }
    }

    if(Do_Morphcomp>0)
    {
      for(iobs=1;iobs<=Morphcomp_nobs;iobs++)
      {
        y=Morphcomp_obs(iobs,1); s=Morphcomp_obs(iobs,2);
        temp1=s-1.;
        temp2=y;
        temp=temp2+temp1/nseas;
        f=Morphcomp_obs(iobs,3);
        k=5+Morphcomp_nmorph;
        for(z=6;z<=k;z++)
        {
          SS2out<<temp<<" "<<s<<" "<<f<<" "<<1<<" "<<1<<" GP% "<<0<<" "<<Morphcomp_obs(iobs,5);
         SS2out<<" "<<0<<" "<<0<<" "<<0<<" "<<z-5<<" "<<Morphcomp_obs(iobs,z)<<" " <<Morphcomp_exp(iobs,z)<<" "<<endl;
        }
      }
    }


    if(Do_TG>0)
    {
      for(TG=1;TG<=N_TG;TG++)
      {
        y=TG_release(TG,3); s=TG_release(TG,4);
        for(TG_t=0;TG_t<=TG_endtime(TG);TG_t++)
        {
          t = styr+(y-styr)*nseas+s-1;
          temp1=s-1.;
          temp=float(y)+temp1/float(nseas);
          SS2out<<temp<<" "<<s<<" "<<0<<" "<<TG<<" "<<TG_release(TG,6)<<" TAG2 NA NA NA NA NA "<<
          temp<<" "<<TG_recap_obs(TG,TG_t,0)<<" "<<TG_recap_exp(TG,TG_t,0)<<" 0 0 _ _ ";
          if(TG_t>=TG_mixperiod) {SS2out<<1<<endl;} else {SS2out<<0<<endl;}
          if(Nfleet>1)
          for(f=1;f<=Nfleet;f++)
          {
            SS2out<<temp<<" "<<s<<" "<<f<<" "<<TG<<" "<<TG_release(TG,6)<<" TAG1 NA NA NA NA NA "<<
            f<<" "<<TG_recap_obs(TG,TG_t,f)<<" "<<TG_recap_exp(TG,TG_t,f)<<" 0 "<<TG_recap_obs(TG,TG_t,0)
            <<" _ _ ";
            if(TG_t>=TG_mixperiod) {SS2out<<1<<endl;} else {SS2out<<0<<endl;}
          }
          s++; if(s>nseas) {s=1; y++;}
        }
      }
    }

  SS2out<<-1<<endl<<"End_comp_data"<<endl;
  SS2out <<endl<< "SELEX_database" << endl;
  SS2out<<"Fleet Yr Kind Gender Bin Selex"<<endl;

  if(reportdetail==0)
  {
    SS2out<<"1 1990 L 1 30 .5"<<endl;
  }
  else
  {
  for (f=1;f<=Ntypes;f++)
  for (y=styr;y<=endyr;y++)
  {
   if(y==endyr || (time_vary_sel(y,f)>0 || time_vary_sel(y+1,f)>0))
   {
    for (gg=1;gg<=gender;gg++)
    {
     for(z=1;z<=nlength;z++) {SS2out<<f<<" "<<y<<" L "<<gg<<" "<<len_bins(z)<<" "<<sel_l(y,f,gg,z)<<endl;}
     if(seltype(f,2)!=0)
     {
      if(gg==1) {for(z=1;z<=nlength;z++) {SS2out<<f<<" "<<y<<" D "<<gg<<" "<<len_bins(z)<<" "<<retain(y,f,z)<<endl;}}
      else
      {for(z=1;z<=nlength;z++) {SS2out<<f<<" "<<y<<" D "<<gg<<" "<<len_bins(z)<<" "<<retain(y,f,z+nlength)<<endl;}}
     }
     if(seltype(f,2)==2)
     {
      if(gg==1) {for(z=1;z<=nlength;z++) {SS2out<<f<<" "<<y<<" DM "<<gg<<" "<<len_bins(z)<<" "<<discmort(y,f,z)<<endl;}}
      else
      {for(z=1;z<=nlength;z++) {SS2out<<f<<" "<<y<<" DM "<<gg<<" "<<len_bins(z)<<" "<<discmort(y,f,z+nlength)<<endl;}}
     }
    }
   }
   if(time_vary_sel(y,f+Ntypes)>0)
   {
    for (gg=1;gg<=gender;gg++)
    for(a=0;a<=nages;a++) {SS2out<<f<<" "<<y<<" A "<<gg<<" "<<a<<" "<<sel_a(y,f,gg,a)<<endl;}
   }
  }
  }  // end do report detail
  SS2out<<" end selex output "<<endl;

FUNCTION write_Bzero_output
//  output annual time series for beginning of year and summing across areas for each GP and gender
    for(fishery_on_off=1;fishery_on_off>=0;fishery_on_off--)
    {
    SS2out<<endl<<endl;
    SS2out<<"Spawning_Biomass_Report";
    if(fishery_on_off==0) {SS2out<<"_1 No_fishery_for_Z=M_and_dynamic_Bzero";} else {SS2out<<"_2 With_fishery";}
    SS2out<<endl<<"Yr Area: ";
    for(p=1;p<=pop;p++)
    for(gp=1;gp<=N_GP;gp++)
    {SS2out<<p<<" ";}
    SS2out<<endl<<"xxxx GP: ";
    for(p=1;p<=pop;p++)
    for(gp=1;gp<=N_GP;gp++)
    {SS2out<<gp<<" ";}
    SS2out<<endl;

      save_gparm=0;
      if(fishery_on_off==0)
      {
        get_initial_conditions();
        get_time_series();
        if(Do_Forecast>0)
        {
          show_MSY=0;
          Get_Forecast();
        }
      }

    for(y=styr-2;y<=YrMax;y++)
    {
      SS2out<<y;
       if(y==styr-2)
         {SS2out<<" VIRG ";}
       else if (y==styr-1)
         {SS2out<<" INIT ";}
       else if (y<=endyr)
         {SS2out<<" TIME ";}
       else
         {SS2out<<" FORE ";}
      for(p=1;p<=pop;p++)
      for(gp=1;gp<=N_GP;gp++)
      {SS2out<<" "<<Spbio(y,p,gp);}
      SS2out<<endl;
    }

    SS2out << endl << "NUMBERS_AT_AGE_Annual";
    if(fishery_on_off==0) {SS2out<<"_1 No_fishery_for_Z=M_and_dynamic_Bzero";} else {SS2out<<"_2 With_fishery";}
    SS2out << endl;
    SS2out << "Bio_Pattern Gender Year "<<age_vector <<endl;
    dvector tempvec2(1,nages);
    for(gp=1;gp<=N_GP;gp++)
    for(gg=1;gg<=gender;gg++)
    for(y=styr;y<=YrMax;y++)
    {
      tempvec.initialize();
      t = styr+(y-styr)*nseas;  // first season only
      for (p=1;p<=pop;p++)
      for (g=1;g<=gmorph;g++)
      if(use_morph(g)>0)
      {
        if(GP4(g)==gp && sx(g)==gg) tempvec += value(natage(t,p,g));
      }
      if(nseas>1)
      {
        tempvec(0)=0.;
        for(s=1;s<=nseas;s++)
        for (p=1;p<=pop;p++)
        for (g=1;g<=gmorph;g++)
        if(use_morph(g)>0 && Bseas(g)==s)
        {
          if(GP4(g)==gp && sx(g)==gg) tempvec(0) += value(natage(t,p,g,0));
        }
      }
      SS2out <<gp<<" "<<gg<<" "<<y<<" "<<tempvec<<endl;
    }

    SS2out << endl << "Z_AT_AGE_Annual";
    if(fishery_on_off==0) {SS2out<<"_1 No_fishery_for_Z=M_and_dynamic_Bzero";} else {SS2out<<"_2 With_fishery";}
    SS2out << endl;
    SS2out << "Bio_Pattern Gender Year "<<age_vector <<endl;
    for(gp=1;gp<=N_GP;gp++)
    for(gg=1;gg<=gender;gg++)
    for(y=styr;y<=YrMax;y++)
    {
      tempvec.initialize();
      t = styr+(y-styr)*nseas;  // first season only
      for (p=1;p<=pop;p++)
      for (g=1;g<=gmorph;g++)
      if(use_morph(g)>0)
      {
        if(GP4(g)==gp && sx(g)==gg) tempvec += value(natage(t,p,g));
      }
      if(nseas>1)
      {
        tempvec(0)=0.;
        for(s=1;s<=nseas;s++)
        for (p=1;p<=pop;p++)
        for (g=1;g<=gmorph;g++)
        if(use_morph(g)>0 && Bseas(g)==s)
        {
          if(GP4(g)==gp && sx(g)==gg) tempvec(0) += value(natage(t,p,g,0));
        }
      }
      if(y>styr)
      {
      SS2out <<gp<<" "<<gg<<" "<<y-1<<" "<<log(elem_div(tempvec2(1,nages),tempvec(1,nages)))<<" _ "<<endl;
      }
      for(a=0;a<=nages-1;a++) tempvec2(a+1)=value(tempvec(a));
      tempvec2(nages)+=value(tempvec(nages));
    }
    }
    SS2out<<" Note:  Z calculated as -ln(Nt+1 / Nt)"<<endl;
    SS2out<<" Note:  Z calculation for maxage-1 includes numbers at maxage, so is approximate"<<endl;
    if(nseas>1) SS2out<<" Age zero fish summed across birthseasons, but Z calc is as if all born in season 1"<<endl;
    fishery_on_off=1;

