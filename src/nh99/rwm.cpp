
// The random walk metropolis algorithm. This is copied from mcmc_routine
// function and modified by Cole.
/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <ctime>
#include <admodel.h>

#if defined(_MSC_VER)
  #include <conio.h>
#else
  #define getch getchar
#endif

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

#ifdef ISZERO
  #undef ISZERO
#endif
#define ISZERO(d) ((d)==0.0)

double better_rand(long int&);
void set_labels_for_mcmc(void);

void print_hist_data(const dmatrix& hist, const dmatrix& values,
  const dvector& h, dvector& m, const dvector& s, const dvector& parsave,
  int iseed, double size_scale);

int minnz(const dvector& x);
int maxnz(const dvector& xa);

void read_hessian_matrix_and_scale1(int nvar, const dmatrix& _SS, double s,
  int mcmc2_flag);

int read_hist_data(const dmatrix& hist, const dvector& h, dvector& m,
  const dvector& s, const dvector& parsave, int& iseed,
  const double& size_scale);

void make_preliminary_hist(const dvector& s, const dvector& m,int nsim,
  const dmatrix& values, dmatrix& hist, const dvector& h,int slots,
  double total_spread,int probflag=0);

void add_hist_values(const dvector& s, const dvector& m, const dmatrix& hist,
  dvector& mcmc_values,double llc, const dvector& h,int nslots,
  double total_spreadd,int probflag=0);

void write_empirical_covariance_matrix(int ncor, const dvector& s_mean,
  const dmatrix& s_covar, adstring& prog_name);

void read_empirical_covariance_matrix(int nvar, const dmatrix& S,
  const adstring& prog_name);

void read_hessian_matrix_and_scale(int nvar, const dmatrix& S,
  const dvector& pen_vector);

int user_stop(void);

extern int ctlc_flag;

dvector new_probing_bounded_multivariate_normal(int nvar, const dvector& a1,
  const dvector& b1, dmatrix& ch, const double& wght,double pprobe,
   random_number_generator& rng);
 // const random_number_generator& rng);

void new_probing_bounded_multivariate_normal_mcmc(int nvar, const dvector& a1,
  const dvector& b1, dmatrix& ch, const double& wght, const dvector& _y,
  double pprobe, random_number_generator& rng);

//void newton_raftery_bayes_estimate(double cbf,int ic, const dvector& lk,
//  double d);
#if defined(USE_BAYES_FACTORS)
void newton_raftery_bayes_estimate_new(double cbf,int ic, const dvector& lk,
  double d);
#endif

void ad_update_mcmc_stats_report
  (int feval,int iter,double fval,double gmax);

void ad_update_function_minimizer_report(int feval,int iter,int phase,
  double fval,double gmax,const char * cbuf);
void ad_update_mcmc_report(dmatrix& m,int i,int j,int ff=0);
void ad_update_mcmchist_report(dmatrix& mcmc_values,ivector& number_offsets,
  dvector& mean_mcmc_values,dvector& h,int ff=0);

void function_minimizer::rwm_mcmc_routine(int nmcmc,int iseed0, double dscale,
				      int restart_flag)
{

  uostream * pofs_psave=NULL;
  dmatrix mcmc_display_matrix;
  //int mcmc_save_index=1;
  //int mcmc_wrap_flag=0;
  //int mcmc_gui_length=10000;
  int nvar=initial_params::nvarcalc(); // get the number of active parameters

  // Cole set this to 1 to essentially turn this feature off since no one seems to use it.
  int no_sd_mcmc=1;

  int on2=-1;
  if ( (on2=option_match(ad_comm::argc,ad_comm::argv,"-nosdmcmc"))>-1)
    {
      cerr << "The sdmcmc feature is disabled, so -nosdmcmc does nothing" << endl;
    }
  if (mcmc2_flag==1)
    {
      initial_params::restore_start_phase();
      //get the number of active parameters
      //int nvar1=initial_params::nvarcalc();
    }

  // if (stddev_params::num_stddev_params==0 & no_sd_mcmc==0)
  //   {
  //     cout << "No objects of type sdreport so cannot use sd report feature." << endl
  // 	   << "Use -nosdmcmc for future runs" << endl;
  //     no_sd_mcmc=1;
  //     // cerr << " You must declare at least one object of type sdreport "
  //     //      << endl << " to do the mcmc calculations" << endl;
  //   }
  {
    ivector number_offsets;
    dvector lkvector;
    //double current_bf=0;
#if defined(USE_BAYES_FACTORS)
    double lcurrent_bf=0;
#endif
    double size_scale=1.0;
    double total_spread=200;
    //double total_spread=2500;
    uostream * pofs_sd = NULL;

    initial_params::set_inactive_random_effects();
    // int nvar_x=initial_params::nvarcalc();
    initial_params::set_active_random_effects();
    int nvar_re=initial_params::nvarcalc();

    int nvar=initial_params::nvarcalc(); // get the number of active parameters
    //int scov_option=0;
    dmatrix s_covar;
    dvector s_mean;
    int on=-1;
    int nslots=800;
    //int nslots=3600;
    int initial_nsim=4800;
    int ncor=0;
    double bfsum=0;
    int ibfcount=0;
    double llbest;
    double lbmax;

    //int ntmp=0;
    //if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcscov",ntmp))>-1)
    //{
    //scov_option=1;
    s_covar.allocate(1,nvar,1,nvar);
    s_mean.allocate(1,nvar);
    s_mean.initialize();
    s_covar.initialize();

    int ndvar=stddev_params::num_stddev_calc();
    /*
      int numdvar=stddev_params::num_stddev_number_calc();
      if (adjm_ptr)
      {
      mcmc_display_matrix.allocate(1,numdvar,1,mcmc_gui_length);
      number_offsets.allocate(1,numdvar);
      number_offsets=stddev_params::copy_all_number_offsets();
      }
    */
    if (mcmc2_flag==0)
      {
	initial_params::set_inactive_random_effects();
	nvar=initial_params::nvarcalc(); // get the number of active parameters
      }
    dvector x(1,nvar);
    dvector scale(1,nvar);
    dmatrix values;
    int have_hist_flag=0;
    initial_params::xinit(x);
    dvector pen_vector(1,nvar);
    {
      initial_params::reset(dvar_vector(x),pen_vector);
      //cout << pen_vector << endl << endl;
    }

    initial_params::mc_phase=0;
    initial_params::stddev_scale(scale,x);
    initial_params::mc_phase=1;
    dvector bmn(1,nvar);
    dvector mean_mcmc_values(1,ndvar);
    dvector s(1,ndvar);
    dvector h(1,ndvar);
    //dvector h;
    dvector square_mcmc_values(1,ndvar);
    square_mcmc_values.initialize();
    mean_mcmc_values.initialize();
    bmn.initialize();
    int use_empirical_flag=0;
    // chain number -- for console display purposes only
    int chain=1;
    int nopt=0;
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-chain",nopt))>-1) {
      if (nopt) {
	int iii=atoi(ad_comm::argv[on+1]);
	if (iii <1) {
	  cerr << "Error: chain must be >= 1" << endl;
	  ad_exit(1);
	} else {
	  chain=iii;
	}
      }
    }
    int diag_option=0;
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcdiag"))>-1)
      {
	diag_option=1;
	cout << " Setting covariance matrix to diagonal with entries " << dscale
	     << endl;
      }
    dmatrix S(1,nvar,1,nvar);
    dvector sscale(1,nvar);
    if (!diag_option)
      {
	int nopt = 0;
	int rescale_bounded_flag=0;
	double rescale_bounded_power=0.5;
	if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcrb",nopt))>-1)
	  {
	    if (nopt)
	      {
		int iii=atoi(ad_comm::argv[on+1]);
		if (iii < 1 || iii > 9)
		  {
		    cerr << " -mcrb argument must be integer between 1 and 9 --"
		      " using default of 5" << endl;
		    rescale_bounded_power=0.5;
		  }
		else
		  rescale_bounded_power=iii/10.0;
	      }
	    else
	      {
		rescale_bounded_power=0.5;
	      }
	    rescale_bounded_flag=1;
	  }
	if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcec"))>-1)
	  {
	    use_empirical_flag=1;
	  }
	if (use_empirical_flag)
	  {
	    read_empirical_covariance_matrix(nvar,S,ad_comm::adprogram_name);
	  }
	else if (!rescale_bounded_flag)
	  {
	    int hbf;
	    if (mcmc2_flag==0)
	      {
		read_covariance_matrix(S,nvar,hbf,sscale);
	      }
	    else
	      {
		int tmp_nvar = 0;
		adstring tmpstring = ad_comm::adprogram_name + ".bgs";
		uistream uis((char*)(tmpstring));
		if (!uis)
		  {
		    cerr << "error opening file " << tmpstring << endl;
		    ad_exit(1);
		  }
		uis >> tmp_nvar;
		if (!uis)
		  {
		    cerr << "error reading from file " << tmpstring << endl;
		    ad_exit(1);
		  }
		if (tmp_nvar != nvar)
		  {
		    cerr << "size error reading from " <<  tmpstring << endl;
		    ad_exit(1);
		  }
		uis >> S;
		if (!uis)
		  {
		    cerr << "error reading from file " << tmpstring << endl;
		    ad_exit(1);
		  }
	      }
	  }
	else
	  {
	    read_hessian_matrix_and_scale1(nvar,S,rescale_bounded_power,
					   mcmc2_flag);
	    //read_hessian_matrix_and_scale(nvar,S,pen_vector);
	  }

	{  // scale covariance matrix for model space
	  dmatrix tmp(1,nvar,1,nvar);
	  for (int i=1;i<=nvar;i++)
	    {
	      tmp(i,i)=S(i,i)*(scale(i)*scale(i));
	      for (int j=1;j<i;j++)
		{
		  tmp(i,j)=S(i,j)*(scale(i)*scale(j));
		  tmp(j,i)=tmp(i,j);
		}
	    }
	  S=tmp;
	}
      }
    else
      {
	S.initialize();
	for (int i=1;i<=nvar;i++)
	  {
	    S(i,i)=dscale;
	  }
      }

    // cout << sort(eigenvalues(S)) << endl;
    dmatrix chd = choleski_decomp( (dscale*2.4/sqrt(double(nvar))) * S);
    dmatrix chdinv=inv(chd);
    dmatrix chdinv0=chdinv;
    dmatrix symbds(1,2,1,nvar);
    initial_params::set_all_simulation_bounds(symbds);
    ofstream ofs_sd1((char*)(ad_comm::adprogram_name + adstring(".mc2")));

    {
      int number_sims = 100000;
      if (nmcmc > 0)
	{
	  number_sims = nmcmc;
	}
      int iseed=0;
      //cin >> iseed;
      if (iseed0<=0)
	{
	  iseed=-36519;
	}
      else
	{
	  iseed=-iseed0;
	}
      if (iseed>0)
	{
	  iseed=-iseed;
	}
      // cout << "Initial seed value " << iseed << endl;
      random_number_generator rng(iseed);
      rng.better_rand();
      double lprob=0.0;
      double lpinv=0.0;
      // get lower and upper bounds

      independent_variables y(1,nvar);
      independent_variables parsave(1,nvar_re);
      initial_params::restore_start_phase();
      nopt=0;
      independent_variables z0(1,nvar); // inits in bounded space

      // read in the mcmc values to date
      int ii=1;
      dmatrix hist;
      if (restart_flag)
	{
	  int tmp=0;
	  if (!no_sd_mcmc) {
	    hist.allocate(1,ndvar,-nslots,nslots);
	    tmp=read_hist_data(hist,h,mean_mcmc_values,s,parsave,iseed,
			       size_scale);
	    values.allocate(1,ndvar,-nslots,nslots);
	    for (int i=1;i<=ndvar;i++)
	      {
		values(i).fill_seqadd(mean_mcmc_values(i)-0.5*total_spread*s(i)
				      +.5*h(i),h(i));
	      }
	  }
	  if (iseed>0)
	    {
	      iseed=-iseed;
	    }
	  /*double br=*/rng.better_rand();
	  if (tmp) have_hist_flag=1;
	  chd=size_scale*chd;
	  chdinv=chdinv/size_scale;
	} else {
	int nopt=0;
	if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcpin",nopt))>-1) {
	  if (nopt) {
	    cifstream cif((char *)ad_comm::argv[on+1]);
	    if (!cif) {
	      cerr << "Error trying to open mcmc par input file "
		   << ad_comm::argv[on+1] << endl;
	      exit(1);
	    }
	    cif >> parsave;
	    if (!cif) {
	      cerr << "Error reading from mcmc par input file "
		   << ad_comm::argv[on+1] << endl;
	      exit(1);
	    }
	  } else {
	    cerr << "Illegal option with -mcpin" << endl;
	  }
	} else {
	  // If user didnt specify one, use MLE values. Store saved MLEs from
	  // admodel.hes file in bounded space into initial parameters z0
	  read_mle_hmc(nvar, z0);
	}
      }

      ii=1;
      // cout << endl << endl << endl << "printing starting values" << endl;
      // cout << parsave << endl << endl;
      initial_params::restore_all_values(parsave,ii);
      // cout << endl << endl << endl << "printing starting values2" << endl;
      // cout << parsave << endl << endl;
      if (mcmc2_flag==0)
	{
	  initial_params::set_inactive_random_effects();
	}
      gradient_structure::set_NO_DERIVATIVES();
      initial_params::xinit(y);
      // cout << endl << endl << endl << "printing starting values3" << endl;
      // cout << y << endl << endl;

      ofstream ogs("sims");
      ogs << nvar << " " << number_sims << endl;
      double llc=-get_monte_carlo_value(nvar,y);
      llbest=-get_monte_carlo_value(nvar,y);
      lbmax=llbest;
      // store current mcmc variable values in param_values
      //void store_mcmc_values(const ofstream& ofs);
      //dmatrix store_mcmc_values(1,number_sims,1,ndvar);
#if defined(USE_BAYES_FACTORS)
      lkvector.allocate(1,number_sims);
#endif
      dvector mcmc_values(1,ndvar);
      dvector mcmc_number_values;
      //if (adjm_ptr) mcmc_number_values.allocate(1,numdvar);
      int offs=1;
      stddev_params::copy_all_values(mcmc_values,offs);

      /*
	if (adjm_ptr)
	{
        offs=1;
        stddev_params::copy_all_number_values(mcmc_number_values,offs);
	}
      */
      int change_ball= (int)nmcmc/2;
      int nopt = 0;
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcscale",nopt))>-1)
	{
	  if (nopt)
	    {
	      // int iii=atoi(ad_comm::argv[on+1]); old way that was buggy
	      int iii=(int)atof(ad_comm::argv[on+1]); // better way
	      if (iii <=0)
		{
		  cerr << " Invalid option following command line option -mcscale -- "
		       << endl << " ignored" << endl;
		}
	      else
		change_ball=iii;
	    }
	}
      int iac=0;
      int liac=0;
      int isim=0;
      int itmp=0;
      double logr;
      int u_option=0;
      double ll;
      int s_option=1;
      int psvflag=0;
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcu"))>-1)
	{
	  u_option=1;
	}
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcnoscale"))>-1)
	{
	  s_option=0;
	}
      //cout << llc << " " << llc << endl;
      int iac_old=0;
      int i_old=0;

      {
	if (!restart_flag)
	  {
	    pofs_sd =
	      new uostream((char*)(ad_comm::adprogram_name + adstring(".mcm")));
	  }

	int mcsave_flag=0;
	int mcrestart_flag=option_match(ad_comm::argc,ad_comm::argv,"-mcr");

	if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcsave"))>-1)
	  {
	    int jj=(int)atof(ad_comm::argv[on+1]);
	    if (jj <=0)
	      {
		cerr << " Invalid option following command line option -mcsave -- "
		     << endl;
	      }
	    else
	      {
		mcsave_flag=jj;
		if ( mcrestart_flag>-1)
		  {
		    // check that nvar is correct
		    {
		      uistream uis((char*)(ad_comm::adprogram_name + adstring(".psv")));
		      if (!uis)
			{
			  cerr << "Error trying to open file" <<
			    ad_comm::adprogram_name + adstring(".psv") <<
			    " for mcrestart" <<   endl;
			  cerr << " I am starting a new file " << endl;
			  psvflag=1;
			}
		      else
			{
			  int nv1 = 0;
			  uis >> nv1;
			  if (nv1 !=nvar)
			    {
			      cerr << "wrong number of independent variables in"
				   << ad_comm::adprogram_name + adstring(".psv")
				   << "\n starting a new file " << endl;
			      psvflag=1;
			    }
			}
		    }

		    if (!psvflag) {
		      pofs_psave=
			new uostream(
				     (char*)(ad_comm::adprogram_name + adstring(".psv")),ios::app);
		    } else {
		      pofs_psave= new uostream((char*)(ad_comm::adprogram_name
						       + adstring(".psv")));
		    }
		  } else {
		  pofs_psave=
		    new uostream((char*)(ad_comm::adprogram_name + adstring(".psv")));
		}
		if (!pofs_psave|| !(*pofs_psave))
		  {
		    cerr << "Error trying to open file" <<
		      ad_comm::adprogram_name + adstring(".psv") << endl;
		    mcsave_flag=0;
		    if (pofs_psave)
		      {
			delete pofs_psave;
			pofs_psave=NULL;
		      }
		  }
		else
		  {
		    if (psvflag || (mcrestart_flag == -1) )
		      {
			(*pofs_psave) << nvar_re;
		      }
		  }
	      }
	  }

	// Run duration. Can specify warmup and duration, or warmup and
	// iter. Sampling period will stop after exceeding duration hours.
	double duration=0;
	bool use_duration=0;		// whether to use this or iter
	if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-duration",nopt))>-1) {
	  double _duration=0;
	  use_duration=1;
	  if (nopt) {
	    istringstream ist(ad_comm::argv[on+1]);
	    ist >> _duration;
	    if (_duration <0) {
	      cerr << "Error: duration must be > 0" << endl;
	      ad_exit(1);
	    } else {
	      // input is in seconds, duration is in seconds so convert
	      duration=_duration*60;
	    }
	  }
	}

	double pprobe=0.05;
	int probe_flag=0;
	nopt=0;
	on = option_match(ad_comm::argc, ad_comm::argv, "-mcprobe", nopt);
	if (on == -1)
	  {
	    on = option_match(ad_comm::argc,ad_comm::argv,"-mcgrope",nopt);
	  }
	if (on > -1)
	  {
	    probe_flag=1;
	    if (nopt)
	      {
		char* end = 0;
		pprobe=strtod(ad_comm::argv[on+1],&end);
		if (pprobe<=0.00001 || pprobe > .499)
		  {
		    cerr << "Invalid argument to option -mcprobe" << endl;
		    pprobe=-1.0;
		    probe_flag=0;
		  }
	      }
	  }
	int java_quit_flag=0;


	double time_warmup=0;
	double time_total=0;
	std::clock_t start = clock();
	time_t now = time(0);
	tm* localtm = localtime(&now);
	std::string m=get_filename((char*)ad_comm::adprogram_name);
	cout << endl << "Starting RWM for model '" << m <<
	  "' at " << asctime(localtm);
	if(use_duration==1){
	  cout << "Model will run for " << duration/60 <<
	    " minutes or until " << number_sims << " total iterations" << endl;
	}

	// Need to save log-posterior (-NLL) to file to read in later.
	ofstream rwm_lp("rwm_lp.txt", ios::trunc);
	rwm_lp << "log-posterior" << endl;
	// ofstream rotated("rotated.csv", ios::trunc);
	// ofstream bounded("bounded.csv", ios::trunc);
	ofstream unbounded("unbounded.csv", ios::trunc);
	// cout << "Initial mle=" << mle << endl;
	// cout << "Initial z=" << parsave << endl;
	// cout << "Initial y=" << y << endl;
	cout << "Initial negative log density=" << -llbest << endl;
	// Start of MCMC chain
	for (int i=1;i<=number_sims;i++)
	  {
	    if (user_stop()) break;
	    if (java_quit_flag) break;

	    if (!((i-1)%200))
	      {
		// double ratio = double(iac)/i;
		iac_old=iac-iac_old;
		i_old=i-i_old;
		// cout << llc << " " << llc << endl;
		double tratio=double(liac)/200;
		liac=0;
		// cout << " mcmc sim " << i <<  "  acceptance rate "
		//      << ratio << " " << tratio << endl;

		/*
		  int start_flag;
		  int der_flag,next_flag;
		  if (adjm_ptr && i>1)
		  {
		  ad_update_mcmc_report(mcmc_display_matrix,mcmc_save_index,
		  mcmc_wrap_flag);

		  ad_update_mcmc_stats_report
		  (i,number_sims,100.*tratio,100.*ratio);

		  if (allocated(hist)) ad_update_mcmchist_report(hist,
		  number_offsets,mean_mcmc_values,h);
		  void check_java_flags(int& start_flag,int& quit_flag,int& der_flag,
		  int& next_flag);
		  check_java_flags(start_flag,java_quit_flag,der_flag,next_flag);
		  ADSleep(50);
		  }
		*/

		if (i>50 && s_option && i<change_ball && !restart_flag)
		  {
		    if (tratio < .15)
		      {
			chd=.2*chd;
			size_scale*=0.2;
			chdinv=chdinv/0.2;
			//cout << "decreasing step size " << ln_det(chd,itmp) << endl;
		      }
		    if (tratio > .6)
		      {
			chd=2.*chd;
			size_scale*=2.0;
			chdinv=chdinv/2.;
			//cout << "increasing step size " << ln_det(chd,itmp) << endl;
		      }
		    else if (tratio > .5)
		      {
			chd=1.5*chd;
			size_scale*=1.5;
			chdinv=chdinv/1.5;
			//cout << "increasing step size " << ln_det(chd,itmp) << endl;
		      }
		    else if (tratio > .4)
		      {
			chd=1.2*chd;
			size_scale*=1.2;
			chdinv=chdinv/1.2;
			//cout << "increasing step size " << ln_det(chd,itmp) << endl;
		      }
		  }
	      }
	    ii=1;
	    if (random_effects_flag)
	      {
		initial_params::restore_start_phase();
		initial_params::restore_all_values(parsave,ii);
		if (mcmc2_flag==0)
		  {
		    initial_params::set_inactive_random_effects();
		  }
	      }
	    else
	      {
		initial_params::restore_all_values(parsave,ii);
	      }
	    initial_params::set_all_simulation_bounds(symbds);

	    // option of generating uniform or normal random variables
	    dvector bmn1(1,nvar);
	    if (!u_option)
	      {
		if (!probe_flag)
		  bmn1=bounded_multivariate_normal(nvar,symbds(1),symbds(2),
						   chd,lprob,rng);
		else
		  bmn1=new_probing_bounded_multivariate_normal(
							       nvar,symbds(1),symbds(2),chd,lprob,pprobe,rng);

		initial_params::add_random_vector(bmn1);
		initial_params::xinit(y);
		// get the simulation bounds for the inverse transition
		initial_params::set_all_simulation_bounds(symbds);
		if (!probe_flag)
		  bounded_multivariate_normal_mcmc(nvar,symbds(1),symbds(2),chd,
						   lpinv,-1*(chdinv*bmn1),rng);
		else
		  new_probing_bounded_multivariate_normal_mcmc(nvar,symbds(1),
							       symbds(2), chd,lpinv,-1*(chdinv*bmn1),pprobe,rng);

		ll=-get_monte_carlo_value(nvar,y);
		if (random_effects_flag)
		  {
		    initial_params::restore_start_phase();
		  }
		//cout << ll << " " << llc << endl;
		double ldiff=lprob-lpinv;
		logr= ll - ldiff - llc;
	      }
	    else
	      {
		bmn1=bounded_multivariate_uniform(nvar,symbds(1),symbds(2),
						  chd, lprob,rng);
		initial_params::add_random_vector(bmn1);
		initial_params::xinit(y);
		// get the simulation bounds for the inverse transition
		initial_params::set_all_simulation_bounds(symbds);
		bounded_multivariate_uniform_mcmc(nvar,symbds(1),symbds(2),chd,
						  lpinv,-1*(chdinv*bmn1),rng);
		ll=-get_monte_carlo_value(nvar,y);
		double ldiff=lprob-lpinv;
		logr= ll - ldiff - llc;
	      }
	    //cout << logr << endl;
	    // decide whether to accept the new point
	    isim++;
	    double br=rng.better_rand();
	    if (logr>=0 || br< exp(logr) )
	      {
		ii=1;
		// save current parameter values
		initial_params::copy_all_values(parsave,ii);
		ii=1;
		// save current mcmc values
		stddev_params::copy_all_values(mcmc_values,ii);
		if (random_effects_flag)
		  {
		    if (mcmc2_flag==0)
		      {
			initial_params::set_inactive_random_effects();
		      }
		  }
		// update prob density for current point
		llc =ll;
		liac++;
		iac++;
	      }
	    int mmin=mcmc_values.indexmin();
	    int mmax=mcmc_values.indexmax();
	    double lbf=llbest-llc;
	    if (lbf>lbmax) lbmax=lbf;
	    //of_bf << lbf << endl;
	    bfsum+=exp(lbf);
	    ibfcount+=1;
#if defined(USE_BAYES_FACTORS)
	    lkvector(ibfcount)=llc;
	    //current_bf=1.0/(bfsum/double(ibfcount))*exp(llbest);
	    lcurrent_bf=-1.*log(bfsum/double(ibfcount))+llbest;
#endif
	    if (mcsave_flag && (!((i-1)%mcsave_flag)))
	      {
		// Save parameters and log posterior at each thinned iteration
		(*pofs_psave) << parsave;
		rwm_lp << llc << endl;
		if(i>change_ball){
		  // Calculate rotated parameter vector
		  independent_variables xtemp(1,nvar);
		  xtemp=chdinv0*y;
		  for(int i=1;i<nvar;i++) {
		    // rotated << xtemp(i) << ", ";
		    unbounded << y(i) << ", ";
		    // bounded << parsave(i) << ", ";
		  }
		  // rotated << xtemp(nvar) << endl;
		  unbounded << y(nvar) << endl;
		  // bounded << parsave(nvar) << endl;
		}
	      }
	    /*
	      if (adjm_ptr)
	      {
	      void save_mcmc_for_gui1(const dvector& mcmc_values,
	      dmatrix &mdm,int& ids,int& iwrap,ivector& no);
	      save_mcmc_for_gui1(mcmc_values,mcmc_display_matrix,
	      mcmc_save_index,mcmc_wrap_flag,number_offsets);
	      }
	    */
	    if (!no_sd_mcmc)
	      {
		if (!have_hist_flag)
		  {
		    for (ii=mmin;ii<=mmax;ii++)
		      {
			(*pofs_sd) << float(mcmc_values(ii));
		      }
		    (*pofs_sd) << (float)(llc);
		    mean_mcmc_values+=mcmc_values;
		    square_mcmc_values+=square(mcmc_values);
		  }
		else
		  {
		    add_hist_values(s,mean_mcmc_values,hist,mcmc_values,llc,
				    h,nslots,total_spread);
		  }
	      }
	    //if (scov_option)
	    {
	      ncor++;
	      s_mean+=parsave;
	      s_covar+=outer_prod(parsave,parsave);
	    }
	    if (!no_sd_mcmc && iac>5 && isim>initial_nsim)
	      {
		if (!have_hist_flag)
		  {
		    have_hist_flag=1;
		    delete pofs_sd;
		    pofs_sd=NULL;
		    mean_mcmc_values/=double(isim);
		    square_mcmc_values/=double(isim);
#if defined(USE_DDOUBLE)
		    s=2.*sqrt(double(1.e-20)+square_mcmc_values
			      -square(mean_mcmc_values));
#else
		    s=2.*sqrt(1.e-20+square_mcmc_values-square(mean_mcmc_values));
#endif
		    make_preliminary_hist(s,mean_mcmc_values,isim,values,hist,h,
					  nslots,total_spread);
		  }
	      }
	    if(i==change_ball)
	      time_warmup = ( std::clock()-start)/(double) CLOCKS_PER_SEC;
	    time_total = ( std::clock()-start)/(double) CLOCKS_PER_SEC;
	    if(use_duration==1 && time_total > duration){
	      // If duration option used, break loop after <duration> hours.
	      cout << i << " samples generated after " << duration/60 <<
		" minutes running." << endl;
	      break;
	    }
	    print_mcmc_progress(i, number_sims, change_ball, chain);
	  } // end of mcmc chain
	print_mcmc_timing(time_warmup, time_total);
      }
      if (!no_sd_mcmc && !have_hist_flag)
	{
	  delete pofs_sd;
	  pofs_sd=NULL;
	  mean_mcmc_values/=double(isim);
	  square_mcmc_values/=double(isim);
#if defined(USE_DDOUBLE)
	  s=2.*sqrt(double(1.e-20)+square_mcmc_values-square(mean_mcmc_values));
#else
	  s=2.*sqrt(1.e-20+square_mcmc_values-square(mean_mcmc_values));
#endif
	  make_preliminary_hist(s,mean_mcmc_values,isim,values,hist,h,nslots,
				total_spread);
	}
      if (!no_sd_mcmc)
        if (iac>5)
          print_hist_data(hist,values,h,mean_mcmc_values,s,parsave,iseed,
			  size_scale);
#ifndef OPT_LIB
      assert(isim != 0);
#endif
      cout << "Final acceptance ratio=";
      printf("%.2f", iac/double(isim));
      //     cout << iac/double(isim) << endl;
      cout << endl << endl;
      initial_params::mc_phase=0;
      /*
	if (adjm_ptr)
	{
        ad_update_mcmc_report(mcmc_display_matrix,mcmc_save_index,
	mcmc_wrap_flag,1);

        if (allocated(hist)) ad_update_mcmchist_report(hist,
	number_offsets,mean_mcmc_values,h,1);
	}
      */
    }

    // Cole commented this stuff out. Not sure what it does but shouldnt be needed
    // write_empirical_covariance_matrix(ncor,s_mean,s_covar,
    // 				      ad_comm::adprogram_name);
    //newton_raftery_bayes_estimate(current_bf,ibfcount,exp(lkvector),.01);
    // #if defined(USE_BAYES_FACTORS)
    //     cout << "log current bayes factor " << lcurrent_bf << endl;
    //     newton_raftery_bayes_estimate_new(lcurrent_bf,ibfcount,lkvector,.01);
    // #endif
    if (pofs_psave)
      {
	delete pofs_psave;
	pofs_psave=NULL;
      }
  }
}
