/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
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

//void ADSleep(unsigned int);

/**
 * Monte Carlo Markov Chain minimization routine
 * Approximate the target distribution by performing a random walk
   across parameter space, integrating at each step.
 * This routine also parses the command line arguments and performs actions for
   the following ones:
 * -mcdiag     Use diagonal covariance matrix with covariance = dscale.
 * -mcrb N     Modify covariance matrix to reduce high correlations. 1<=N<=9
               where 1=10% and 9=90%.
 * -mcec       Read in empirical covariance matrix. This is a file with the
               program name prepended to extension '.ecm'.
 * -mcpin NAME Read in starting values for MCMC from file NAME. NAME must be a
               valid ADMB '.par' file.
 * -mcscale    Dynamically scales covariance matrix until a reasonable
               acceptance rate is observed.
 * -nosdmcmc   Turn off calculation os sdreport variables during mcsave phase
               (saves a lot of CPU time).
 * -mcu        Use uniform multivariate distributions as bounds, if this is not
               specified then random normal multivariate distributions will be
               used.
 * -mcnoscale  Don't rescale step size based on acceptance rate.
 * -mcr        Continue MCMC from a previous -mcmc call. Uses '.mcm' file to
               accomplish this.
 * -mcsave N   Save parameter values from every Nth simulation instead of every
               single one.
 * -mcprobe N  Use probing strategy, 0.00001<N<=0.499. See the function
               new_probing_bounded_multivariate_normal() in prmonte.cpp
               for more detail.
 * -mcgrope    Deprecated, equivalent to -mcprobe
 * \param int nmcmc The number of MCMC simulations to run.
 * \param int iseed0 Initial seed value for simulations.
 * \param double dscale Scale value used only if -mcdiag is specified.
 * \param int restart_flag Restart the MCMC, even if -mcr is specified.
 * \return Nothing.
 */
void function_minimizer::mcmc_routine(int nmcmc,int iseed0, double dscale,
  int restart_flag)
 {
  uostream * pofs_psave=NULL;
  dmatrix mcmc_display_matrix;
  //int mcmc_save_index=1;
  //int mcmc_wrap_flag=0;
  //int mcmc_gui_length=10000;
  int no_sd_mcmc=0;

  int on2=-1;
  if ( (on2=option_match(ad_comm::argc,ad_comm::argv,"-nosdmcmc"))>-1)
  {
    no_sd_mcmc=1;
  }
  if (mcmc2_flag==1)
  {
    initial_params::restore_start_phase();
    //get the number of active parameters
    //int nvar1=initial_params::nvarcalc();
  }

  if (stddev_params::num_stddev_params==0)
  {
    cerr << " You must declare at least one object of type sdreport "
         << endl << " to do the mcmc calculations" << endl;
     return;
  }
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
    int nvar_x=initial_params::nvarcalc();
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

    cout << sort(eigenvalues(S)) << endl;
    dmatrix chd = choleski_decomp( (dscale*2.4/sqrt(double(nvar))) * S);
    dmatrix chdinv=inv(chd);

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
      cout << "Initial seed value " << iseed << endl;
      random_number_generator rng(iseed);
      rng.better_rand();
      double lprob=0.0;
      double lpinv=0.0;
      // get lower and upper bounds

      independent_variables y(1,nvar);
      independent_variables parsave(1,nvar_re);
      initial_params::restore_start_phase();

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
      }
      else
      {
        int nopt=0;
        if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcpin",nopt))>-1)
        {
          if (nopt)
          {
            cifstream cif((char *)ad_comm::argv[on+1]);
            if (!cif)
            {
              cerr << "Error trying to open mcmc par input file "
                   << ad_comm::argv[on+1] << endl;
              exit(1);
            }
            cif >> parsave;
            if (!cif)
            {
              cerr << "Error reading from mcmc par input file "
                   << ad_comm::argv[on+1] << endl;
              exit(1);
            }
          }
          else
          {
            cerr << "Illegal option with -mcpin" << endl;
          }
        }
        else
        {
          ii=1;
          initial_params::copy_all_values(parsave,ii);
        }
      }

      ii=1;
      initial_params::restore_all_values(parsave,ii);

      if (mcmc2_flag==0)
      {
        initial_params::set_inactive_random_effects();
      }

      gradient_structure::set_NO_DERIVATIVES();
      ofstream ogs("sims");
      ogs << nvar << " " << number_sims << endl;
      initial_params::xinit(y);
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
      int change_ball=2500;
      int nopt = 0;
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcscale",nopt))>-1)
      {
        if (nopt)
        {
          int iii=atoi(ad_comm::argv[on+1]);
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
       for (int i=1;i<=number_sims;i++)
       {
         if (user_stop()) break;
         if (java_quit_flag) break;

        if (!((i-1)%200))
        {
          double ratio = double(iac)/i;
          iac_old=iac-iac_old;
          i_old=i-i_old;
          cout << llc << " " << llc << endl;
          double tratio=double(liac)/200;
          liac=0;
          cout << " mcmc sim " << i <<  "  acceptance rate "
               << ratio << " " << tratio << endl;

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
              cout << "decreasing step size " << ln_det(chd,itmp) << endl;
            }
            if (tratio > .6)
            {
              chd=2.*chd;
              size_scale*=2.0;
              chdinv=chdinv/2.;
              cout << "increasing step size " << ln_det(chd,itmp) << endl;
            }
            else if (tratio > .5)
            {
              chd=1.5*chd;
              size_scale*=1.5;
              chdinv=chdinv/1.5;
              cout << "increasing step size " << ln_det(chd,itmp) << endl;
            }
            else if (tratio > .4)
            {
              chd=1.2*chd;
              size_scale*=1.2;
              chdinv=chdinv/1.2;
              cout << "increasing step size " << ln_det(chd,itmp) << endl;
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
          (*pofs_psave) << parsave;
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
       }
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
      cout << iac/double(isim) << endl;
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

    write_empirical_covariance_matrix(ncor,s_mean,s_covar,
      ad_comm::adprogram_name);
    //newton_raftery_bayes_estimate(current_bf,ibfcount,exp(lkvector),.01);
#if defined(USE_BAYES_FACTORS)
    cout << "log current bayes factor " << lcurrent_bf << endl;
    newton_raftery_bayes_estimate_new(lcurrent_bf,ibfcount,lkvector,.01);
#endif
    if (pofs_psave)
    {
      delete pofs_psave;
      pofs_psave=NULL;
    }
  }
}

/**
 * Writes the covariance matrix out to a file, which is prog_name
 * prepended to the extension '.ecm'.
 * Also writes the sorted eigenvalues of the covariance matrix to the screen.
 * \param int ncor
 * \param dvector& s_mean
 * \param dmatrix& s_covar
 * \param adstring& prog_name
 * \return Nothing.
 */
void write_empirical_covariance_matrix(int ncor, const dvector& s_mean,
  const dmatrix& s_covar,adstring& prog_name)
{
  uostream ofs((char*)(ad_comm::adprogram_name + adstring(".ecm")));
  dvector tmp=s_mean/ncor;
  int nvar=s_mean.indexmax();
  //ofs << ncor << " " << nvar << endl;
  dmatrix sigma=s_covar/ncor -outer_prod(tmp,tmp);
  cout << "In write empirical covariance matrix" << endl;
  cout << sort(eigenvalues(sigma)) << endl;
  dvector std(1,nvar);
  ofs << sigma;
  /*
  int i;
  for (i=1;i<=nvar;i++)
  {
    std(i)=sigma(i,i);
    for (int j=1;j<=i;j++)
    {
      sigma(i,j)/=sqrt(std(i)*std(j));
      sigma(j,i)=sigma(i,j);
    }
  }
  for (i=1;i<=nvar;i++)
  {
    ofs << setw(10) << setscientific() << std(i);
    for (int j=1;j<=i;j++)
    {
      ofs << " " << setfixed() << setw(7) << setprecision(4)
           << sigma(i,j);
    }
    ofs << endl;
  }
 */
}

/**
 * Reads the covariance matrix from a file, which is the program name
 * prepended to the extension '.ecm'.
 * \param int nvar
 * \param dmatrix& S
 * \param adstring& prog_name
 * \return Nothing, but S has been assigned to the contents of the file.
 */
void read_empirical_covariance_matrix(int nvar, const dmatrix& S,
  const adstring& prog_name)
{
  adstring infile_name=ad_comm::adprogram_name + adstring(".ecm");
  uistream ifs((char*)(infile_name));
  if (!ifs)
  {
    cerr << "Error opening file " << infile_name << endl;
  }
  ifs  >> S;
  /*
  int ncor=0;
  int _nvar=0;
  ifs >> ncor >> _nvar;
  if (nvar != _nvar)
  {
    cerr << "wromng number of indepdendent variables in routine"
      " read_empirical_covariance_matrix" << endl;
  }
  dvector std(1,nvar);
  int i;
  for (i=1;i<=nvar;i++)
  {
    ifs >> std(i);
    for (int j=1;j<=i;j++)
    {
      ifs  >> S(i,j);
      S(j,i)=S(i,j);
    }
  }
  if (!ifs)
  {
    cerr << "Error reading from file " << infile_name << endl;
  }
  for (i=1;i<=nvar;i++)
  {
    for (int j=1;j<=i;j++)
    {
      S(i,j)*=sqrt(std(i)*std(j));
      S(j,i)=S(i,j);
    }
  }
 */
}

void print_hist_data(const dmatrix& hist, const dmatrix& values,
  const dvector& h, dvector& m, const dvector& s, const dvector& parsave,
  int iseed, double size_scale)
{
  ofstream ofs((char*)(ad_comm::adprogram_name + adstring(".hst")));
  int nsdvars=stddev_params::num_stddev_calc();
  adstring_array param_labels(1,nsdvars);
  ivector param_size(1,nsdvars);
  int ii=1;
  //int max_name_length=0;
  int i;
  for (i=0;i< stddev_params::num_stddev_params;i++)
  {
    param_labels[ii]=
      stddev_params::stddevptr[i]->label();
    param_size[ii]=
      stddev_params::stddevptr[i]->size_count();
/*
    if (max_name_length<param_labels[ii].size())
    {
      max_name_length=param_labels[ii].size();
    }
*/
    ii++;
  }
  //int end_stdlabels=ii-1;

  int lc=1;
  int ic=1;
  ivector mmin(1,nsdvars);
  ivector mmax(1,nsdvars);

  for (i=1;i<=nsdvars;i++)
  {
    mmin(i)=minnz(hist(i));
    mmax(i)=maxnz(hist(i));
  }
#ifdef OPT_LIB
  int nsim = (int)sum(hist(1));
#else
  double _nsim = sum(hist(1));
  assert(_nsim <= (double)INT_MAX);
  int nsim = (int)_nsim;
#endif
  ofs << "# samples sizes" << endl;
  ofs << nsim << endl;
  ofs << "# step size scaling factor" << endl;
  ofs << size_scale << endl;
  ofs << "# step sizes" << endl;
  ofs << h << endl;
  ofs << "# means" << endl;
  ofs << m << endl;
  ofs << "# standard devs" << endl;
  ofs << s << endl;
  ofs << "# lower bounds" << endl;
  ofs << mmin << endl;
  ofs << "# upper bounds" << endl;
  ofs << mmax<< endl;
  ofs << "#number of parameters" << endl;
  ofs << parsave.indexmax() << endl;
  ofs << "#current parameter values for mcmc restart" << endl;
  ofs << parsave << endl;
  ofs << "#random number seed" << endl;
  ofs << iseed << endl;
  for (i=1;i<=nsdvars;i++)
  {
    ofs << "#" << param_labels[lc];
    if (param_size[lc]>1)
    {
      ofs << "[" << ic << "]";
    }
    ofs << endl;

    if (++ic> param_size[lc])
    {
      lc++;
      ic=1;
    }
    for (ii=mmin(i);ii<=mmax(i);ii++)
    {
      ofs << values(i,ii) << " " << hist(i,ii)/(nsim*h(i)) << endl;
    }
    if (i<nsdvars) ofs << endl;
  }
}

int read_hist_data(const dmatrix& _hist, const dvector& h, dvector& m,
  const dvector& s, const dvector& parsave, int& iseed,
  const double& size_scale)
{
  dmatrix& hist= (dmatrix&) _hist;
  cifstream cif((char*)(ad_comm::adprogram_name + adstring(".hst")));
  int nsdvars=stddev_params::num_stddev_calc();
  int nsim=0;
  int ii=1;
  int i;
  ivector mmin(1,nsdvars);
  ivector mmax(1,nsdvars);
  //ofs << # samples sizes << endl;
  cif >> nsim;
  cif >> size_scale;
  //ofs << # step sizes << endl;
  cif >> h;
  //ofs << # means << endl;
  cif >> m;
  //ofs << # standard devs << endl;
  cif >> s;
  //ofs << # lower bounds << endl;
  cif >> mmin;
  //ofs << # upper bounds << endl;
  cif >> mmax;
  int num_vars=0;
  cif >> num_vars;
  int flag=1;
  if (num_vars!=parsave.indexmax())
  {
    cerr << "wrong number of independent variables in file"
       << ad_comm::adprogram_name + adstring(".hst") << endl;
    flag=0;
  }
  if (flag)
  {
  cif >> parsave;
    cif >> iseed;
    double tmp=0.0;
    hist.initialize();
    for (i=1;i<=nsdvars;i++)
    {
      for (ii=mmin(i);ii<=mmax(i);ii++)
      {
        cif >> tmp >> hist(i,ii);
      }
      hist(i)*=nsim*h(i);
    }
  }
  return flag;
}

int minnz(const dvector& x)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int m=mmin;
  for (int ii=mmin;ii<=mmax;ii++)
  {
    if (!ISZERO(x(ii)))
    {
      m=ii;
      if (m>mmin) m--;
      break;
    }
  }
  return m;
}

int maxnz(const dvector& x)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int m=mmax;
  for (int ii=mmax;ii>=mmin;ii--)
  {
    if (!ISZERO(x(ii)))
    {
      m=ii;
      if (m<mmax) m++;
      break;
    }
  }
  return m;
}

void add_hist_values(const dvector& s, const dvector& m, const dmatrix& _hist,
  dvector& mcmc_values, double llc, const dvector& h, int nslots,
  double total_spread,int probflag)
{
  dmatrix& hist= (dmatrix&) _hist;
  int nsdvars=stddev_params::num_stddev_calc();
  for (int ii=1;ii<=nsdvars;ii++)
  {
    int x;
    double xx=(mcmc_values(ii)-m(ii))/h(ii);
    if (xx>0.0)
      x=int (xx+0.5);
    else
      x=int(xx-0.5);

    if (x<-nslots)
    {
      x=-nslots;
    }
    if (x>nslots)
    {
      x=nslots;
    }
    if (!probflag)
    {
      hist(ii,x)+=1;
    }
    else
    {
      hist(ii,x)+=exp(llc);
    }
  }
}

/*
void add_guihist_values(const dvector& s, const dvector& m,
  const dmatrix& _hist,dvector& mcmcnumber_values,double llc,
  const dvector& h,int nslots,double total_spread)
{
  dmatrix& hist= (dmatrix&) _hist;
  int nsdvars=stddev_params::num_stddev_number_calc();
  for (int ii=1;ii<=nsdvars;ii++)
  {
    int x=int((mcmcnumber_values(ii)-m(ii))/h(ii));
    //cout << "xxx = " << xxx << endl;
    char ch;
    //cin >> ch;

    if (x<1)
    {
      x=-nslots;
    }
    if (x>nslots)
    {
      x=nslots;
    }
    {
      hist(ii,x)+=1;
    }
  }
}
*/

void make_preliminary_hist(const dvector& s, const dvector& m,int nsim,
  const dmatrix& _values, dmatrix& hist, const dvector& _h, int nslots,
  double total_spread, int probflag)
{
  ADUNCONST(dmatrix,values)
  dvector& h = (dvector&) _h;
  int nsdvars=stddev_params::num_stddev_calc();
  dvector mcmc_values(1,nsdvars);
  values.allocate(1,nsdvars,-nslots,nslots);
  h=total_spread/(2*nslots+1)*s;
  hist.allocate(1,nsdvars,-nslots,nslots);
  hist.initialize();
  uistream ifs((char*)(ad_comm::adprogram_name + adstring(".mcm")));
  int i;
  double llc;
  for (i=1;i<=nsdvars;i++)
  {
    values(i).fill_seqadd(m(i)-.5*total_spread*s(i)+.5*h(i),h(i));
  }

  if (!ifs)
  {
    cerr << "Error trying to open file "
         << ad_comm::adprogram_name + adstring(".mcm");
    return;
  }
  if (!ifs)
  {
    cerr << "Error trying to read number of simulations from file "
         << ad_comm::adprogram_name + adstring(".mcm");
    return;
  }
  for (i=1;i<=nsim;i++)
  {
    float ftmp = 0.0;
    int ii;
    int mmin=mcmc_values.indexmin();
    int mmax=mcmc_values.indexmax();
    for (ii=mmin;ii<=mmax;ii++)
    {
      ifs >>  ftmp;
      mcmc_values(ii)=double(ftmp);
    }
    ifs >>  ftmp;
    llc=double(ftmp);
    for (ii=1;ii<=nsdvars;ii++)
    {
      int x;
      double xx=(mcmc_values(ii)-m(ii))/h(ii);
      if (xx>0.0)
        x=int (xx+0.5);
      else
        x=int(xx-0.5);
      if (x<-nslots)
      {
        x=-nslots;
      }
      if (x>nslots)
      {
        x=nslots;
      }
      if (!probflag)
      {
        hist(ii,x)+=1;
      }
      else
      {
        hist(ii,x)+=exp(llc);
      }
    }
    if (!ifs)
    {
      cerr << "Error trying to read data from file "
         << ad_comm::adprogram_name + adstring(".mcm");
      return;
    }
  }
}

void read_covariance_matrix(const dmatrix& S,int nvar,int& oldHbf,
  dvector & sscale)
{
  adstring tmpstring="admodel.cov";
  if (ad_comm::wd_flag)
    tmpstring = ad_comm::adprogram_name + ".cov";
  uistream cif((char*)tmpstring);
  if (!cif)
  {
    cerr << "Error trying to open file " << tmpstring
         << "  for reading" << endl;
  }
  int tmp_nvar = 0;
  cif >> tmp_nvar;
  if (nvar !=tmp_nvar)
  {
    cerr << "Incorrect number of independent variables in file"
      " model.cov" << endl;
    exit(1);
  }
  cif >> S;
  if (!cif)
  {
    cerr << "error reading covariance matrix from " << tmpstring
         << endl;
    exit(1);
  }
  cif >> oldHbf;
  if (!cif)
  {
    cerr << "error reading old_hybrid_bounded_flag from " << tmpstring
         << endl;
    exit(1);
  }
  cif >> sscale;
  if (!cif)
  {
    cerr << "error reading sscale from " << tmpstring
         << endl;
    exit(1);
  }
}
void read_hessian_matrix_and_scale(int nvar, const dmatrix& _SS,
  const dvector& pen_vector)
{
  dmatrix& S= (dmatrix&) _SS;
  adstring tmpstring="admodel.hes";
  if (ad_comm::wd_flag)
     tmpstring = ad_comm::adprogram_name + ".hes";
  uistream cif((char*)tmpstring);

  if (!cif)
  {
    cerr << "Error trying to open file " << tmpstring
         << "  for reading" << endl;
  }
  int tmp_nvar = 0;
  cif >> tmp_nvar;
  if (nvar !=tmp_nvar)
  {
    cerr << "Incorrect number of independent variables in file"
      " admodel.hes" << endl;
    exit(1);
  }
  cif >> S;
  if (!cif)
  {
    cerr << "error reading covariance matrix from model.cov" << endl;
    exit(1);
  }
  cifstream cifs((char*)(ad_comm::adprogram_name + adstring(".bvs")));
  dvector tmp(1,nvar);
  cifs >> tmp;
  dvector wts=pen_vector/.16;
  dvector diag_save(1,nvar);
  //int neg_flag;
  //double base=5.0;
  double dmin=min(eigenvalues(S));
  cout << "Smallest eigenvalue = " << dmin << endl;
  for (int i=1;i<=nvar;i++)
  {
    if (tmp(i)>0)
    {
#if defined(USE_DDOUBLE)
      S(i,i)/=pow(double(10.0),tmp(i));
#else
      S(i,i)/=pow(10.0,tmp(i));
#endif
    }
  }
  dmin=min(eigenvalues(S));
  if (dmin<0)
  {
    cout << "Smallest eigenvalue = " << dmin << endl;
    exit(1);
  }
  /*
  do
  {
    cout << wts << endl << endl;
    for (int i=1;i<=nvar;i++)
    {
      diag_save(i)=S(i,i);
      if (wts(i)>0)
      {
        S(i,i)/=pow(base,wts(i));
        cout << "  wts(" << i << ") = " << wts(i) << endl;
      }
    }
    dmin=min(eigenvalues(S));
    if (dmin<0)
    {
      cout << "Smallest eigenvalue = " << dmin << endl;
      neg_flag=1;
      base=sqrt(base);
      cout << "base = " << base << endl;
      for (int i=1;i<=nvar;i++)
      {
        S(i,i)=diag_save(i);
      }
      dmin=min(eigenvalues(S));
      cout << "XX Smallest eigenvalue = " << dmin << endl;
    }
    else
    {
      neg_flag=0;
    }
  }
  while (neg_flag);
 */
  S=inv(S);
}

void read_hessian_matrix_and_scale1(int nvar, const dmatrix& _SS,
  double rbp,int mcmc2_flag)
{
  dmatrix& S= (dmatrix&) _SS;
  adstring tmpstring="admodel.hes";
  if (mcmc2_flag)
  {
    tmpstring = ad_comm::adprogram_name + ".bgs";
  }
  else
  {
    if (ad_comm::wd_flag)
       tmpstring = ad_comm::adprogram_name + ".hes";
  }
  uistream cif((char*)tmpstring);

  if (!cif)
  {
    cerr << "Error trying to open file " << tmpstring
         << "  for reading" << endl;
  }
  int tmp_nvar = 0;
  cif >> tmp_nvar;
  if (nvar !=tmp_nvar)
  {
    cerr << "Incorrect number of independent variables in file"
      " admodel.hes" << endl;
    exit(1);
  }
  cif >> S;
  if (!cif)
  {
    cerr << "error reading covariance matrix from model.cov" << endl;
    exit(1);
  }
  dmatrix Save=1*S;
  // for mcmc2 option Hessian is already inverted.
  if (mcmc2_flag==0)
  {
    S=inv(S);
  }
  int mmin=S.indexmin();
  int mmax=S.indexmax();
  dvector diag(mmin,mmax);
  int i,j;
  for (i=mmin;i<=mmax;i++)
  {
    diag(i)=sqrt(S(i,i));
  }
  for (i=mmin;i<=mmax;i++)
    for (j=mmin;j<=mmax;j++)
      S(i,j)/=diag(i)*diag(j);

  dmatrix ch=choleski_decomp(S);
  ofstream ofs("corrtest");
  ofs << "corr matrix" << endl;
  ofs << S << endl;
  ofs << "choleski decomp of corr matrix" << endl;
  ofs << ch << endl;
  dmatrix tmp(mmin,mmax,mmin,mmax);

  for (i=mmin;i<=mmax;i++)
    tmp(i)=ch(i)/norm(ch(i));
  ofs << "tmp" << endl;
  ofs << tmp << endl;

  for (i=mmin;i<=mmax;i++)
    tmp(i)/=tmp(i,i);


  if (rbp<=0.0 || rbp >= 1.0)
    rbp=0.5;
  for (i=mmin;i<=mmax;i++)
  {
    for (j=mmin;j<=mmax;j++)
    {
      if (tmp(i,j)>=1)
         tmp(i,j)=pow(tmp(i,j),rbp);
      else if (tmp(i,j)<-1)
         tmp(i,j)=-pow(-tmp(i,j),rbp);
    }
  }

  for (i=mmin;i<=mmax;i++)
    tmp(i)/=norm(tmp(i));

  dmatrix T=tmp*trans(tmp);

  ofs << "T-S" << endl;
  ofs << T-S << endl;

  S=T;
  ofs << "modified corr matrix" << endl;
  ofs << S << endl;
  for (i=mmin;i<=mmax;i++)
    for (j=mmin;j<=mmax;j++)
      S(i,j)*=diag(i)*diag(j);

  ofs << "modified S" << endl;
  ofs << S << endl;

  ofs << "S* modified S" << endl;
  ofs << S*Save << endl;
}

int user_stop(void)
{
  int quit_flag=0;
#if defined(_MSC_VER)
  if (kbhit())
#else
  if(ctlc_flag)
#endif
  {
#if defined(__DJGPP__)
    int c = toupper(getxkey());
#else
    int c = toupper(getch());
#endif
    if (c == 'Q')
    {
      quit_flag=1;
    }
  }
  return quit_flag;
}

/*
void newton_raftery_bayes_estimate(double cbf, int ic, const dvector& lk,
  double d)
{
  double d1=1.0-d;
  double cbold=cbf;
  do
  {
    cout << "initial bayes factor" << cbf << endl;
    double sum1=0;
    double sum2=0;

    for (int i=1;i<=ic;i++)
    {
      sum1+=1./(d1/cbf+d/lk(i));

      sum2+=1./(d1/cbf*lk(i)+d);
    }
    sum1+=d*ic*cbf;
    sum2+=d*ic;

    cbf=sum1/sum2;
    double diff=log(cbf)-log(cbold);
    if (fabs(diff)<1.e-5) break;
    cbold=cbf;
 }
 while(1);
}
*/

#if defined(USE_BAYES_FACTORS)
void newton_raftery_bayes_estimate_new(double lcbf, int ic, const dvector& lk,
  double d)
{
  double d1=1.0-d;
  double lcbold=lcbf;
  do
  {
    cout << "initial log bayes factor" << lcbf << endl;
    double sum1=0;
    double sum2=0;

    for (int i=1;i<=ic;i++)
    {
      double dtmp=exp(lcbf-lk(i));
      sum1+=1./(d1+d*dtmp);
      sum2+=1./(d1/dtmp+d);
    }
    sum1+=d*ic;
    sum2+=d*ic;
    lcbf=lcbf+log(sum1)-log(sum2);
    double diff=lcbf-lcbold;
    if (fabs(diff)<1.e-5) break;
    lcbold=lcbf;
  }
  while(1);
}
#endif

/*
void save_mcmc_for_gui(const dvector& mcmc_number_values,
  dmatrix &mdm,int& ids)
{
  int imax=mdm.colmax();
  if (ids>imax) ids=1;
  int rmax=mcmc_number_values.indexmax();
  for (int i=1;i<=rmax;i++)
    mdm(i,ids)=mcmc_number_values(i);
  ids++;
}

void save_mcmc_for_gui1(const dvector& mcmc_values,
  dmatrix &mdm,int& ids,int& iwrap,ivector& no)
{
  int rmax=no.indexmax();
  int imax=mdm.colmax();
  if (ids>imax)
  {
    ids=1;
    iwrap=1;
  }
  for (int i=1;i<=rmax;i++)
    mdm(i,ids)=mcmc_values(no(i));
  ids++;
}
*/

dvector read_old_scale(int & old_nvar)
{
  adstring tmpstring="admodel.cov";
  if (ad_comm::wd_flag)
    tmpstring = ad_comm::adprogram_name + ".cov";
  uistream cif((char*)tmpstring);
  if (!cif)
  {
    cerr << "Error trying to open file " << tmpstring
         << "  for reading" << endl;
  }
  cif >> old_nvar;
  dmatrix S(1,old_nvar,1,old_nvar);
  cif >> S;
  if (!cif)
  {
    cerr << "error reading covariance matrix from " << tmpstring
         << endl;
    exit(1);
  }
  int oldHbf;
  cif >> oldHbf;
  if (!cif)
  {
    cerr << "error reading old_hybrid_bounded_flag from " << tmpstring
         << endl;
    exit(1);
  }
  dvector sscale(1,old_nvar);
  cif >> sscale;
  if (!cif)
  {
    cerr << "error reading sscale from " << tmpstring
         << endl;
    exit(1);
  }
  return sscale;
}
