/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

//ofstream tmpof("testmc");

#if defined(__GNU__) || defined(UNIXKLUDGE) || defined(__SUN__)
  #define getch getchar
#endif

#ifdef __GNUDOS__
  #include <gccmanip.h>
#endif

#if defined (__ZTC__) || defined(__TURBOC__) || defined(__WAT32__) \
  || defined (_MSC_VER)
#  if  !defined(__linux__)
#    include <conio.h>
#  endif
#endif

//double better_rand(long int&);
void store_mcmc_values(const ofstream& ofs);
void set_labels_for_mcmc(void);
void save_mcmc_for_gui(const dvector& mcmc_values,dmatrix &mdm,int& ids);
void save_mcmc_for_gui1(const dvector& mcmc_values,
  dmatrix &mdm,int& ids,int& iwrap,ivector& no);

void check_java_flags(int& start_flag,int& quit_flag,int& der_flag,
  int& next_flag);
void print_hist_data(const dmatrix& hist, const dmatrix& values, const dvector& h,
  dvector& m, const dvector& s, const dvector& parsave, long int iseed, double size_scale);

void read_hessian_matrix_and_scale1(int nvar, const dmatrix& _SS,double s,
  int flag=0);

int minnz(const dvector& x);
int maxnz(const dvector& xa);

int read_hist_data(const dmatrix& hist, const dvector& h,
  dvector& m, const dvector& s, const dvector& parsave,long int& iseed, const double& size_scale);

void make_preliminary_hist(const dvector& s, const dvector& m,int nsim, const dmatrix& values,
  dmatrix& hist, const dvector& h,int slots,double total_spread,int probflag=0);

void add_hist_values(const dvector& s, const dvector& m, const dmatrix& hist,
  dvector& mcmc_values,double llc, const dvector& h,int nslots,
  double total_spreadd,int probflag=0);

void add_guihist_values(const dvector& s, const dvector& m,
  const dmatrix& _hist, dvector& mcmcnumber_values, double llc,
  const dvector& h,int nslots,double total_spread);

void write_empirical_covariance_matrix(int ncor, const dvector& s_mean, const dmatrix& s_covar,
  adstring& prog_name);

void read_empirical_covariance_matrix(int nvar, const dmatrix& S, const adstring& prog_name);


void read_hessian_matrix_and_scale(int nvar, const dmatrix& S, const dvector& pen_vector);

int user_stop(void);

extern int ctlc_flag;
class admb_javapointers;
extern admb_javapointers * adjm_ptr;

dvector new_probing_bounded_multivariate_normal(int nvar, const dvector& a1, const dvector& b1,
  dmatrix& ch, const double& wght,double pprobe, random_number_generator& rng);

void new_probing_bounded_multivariate_normal_mcmc(int nvar, const dvector& a1, const dvector& b1,
  dmatrix& ch, const double& wght, const dvector& _y,double pprobe, random_number_generator& rng);

//void  newton_raftery_bayes_estimate(double cbf,int ic, const dvector& lk,double d);
void  newton_raftery_bayes_estimate_new(double cbf,int ic, const dvector& lk,double d);

void ad_update_mcmc_stats_report
  (int feval,int iter,double fval,double gmax);

void ad_update_function_minimizer_report(int feval,int iter,int phase,
  double fval,double gmax,const char * cbuf);
void ad_update_mcmc_report(dmatrix& m,int i,int j,int ff=0);
void ad_update_mcmchist_report(dmatrix& mcmc_values,ivector& number_offsets,
  dvector& mean_mcmc_values,dvector& h,int ff=0);

void ADSleep(int);

#if !defined(USE_ADPVM)
void function_minimizer::pvm_master_mcmc_routine(int nmcmc,int iseed0,
  double dscale,int restart_flag){;}
#else
void function_minimizer::pvm_master_mcmc_routine(int nmcmc,int iseed0,double dscale,
  int restart_flag)
{
  uostream * pofs_psave=NULL;
  dmatrix mcmc_display_matrix;
  int mcmc_save_index=1;
  int mcmc_wrap_flag=0;
  int mcmc_gui_length=10000;
  int no_sd_mcmc=0;

  int on2=-1;
  if ( (on2=option_match(ad_comm::argc,ad_comm::argv,"-nosdmcmc"))>-1)
    no_sd_mcmc=1;

  if (stddev_params::num_stddev_params==0)
  {
    cerr << " You must declare at least one object of type sdreport "
         << endl << " to do the mcmc calculations" << endl;
     return;
  }
  {
    //ofstream of_bf("testbf");

    //if (adjm_ptr) set_labels_for_mcmc();

    ivector number_offsets;
    dvector lkvector;
    //double current_bf=0;
    double lcurrent_bf=0;
    double size_scale=1.0;
    double total_spread=200;
    //double total_spread=2500;
    uostream * pofs_sd = NULL;
    int nvar=initial_params::nvarcalc(); // get the number of active parameters
    int scov_option=0;
    dmatrix s_covar;
    dvector s_mean;
    int on=-1;
    int ncsim=25000;
    int nslots=800;
    //int nslots=3600;
    int initial_nsim=4800;
    int ntmp=0;
    int ncor=0;
    double bfsum=0;
    int ibfcount=0;
    double llbest;
    double lbmax;

    //if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcscov",ntmp))>-1)
    //{
    scov_option=1;
    s_covar.allocate(1,nvar,1,nvar);
    s_mean.allocate(1,nvar);
    s_mean.initialize();
    s_covar.initialize();

    int ndvar=stddev_params::num_stddev_calc();
    int numdvar=stddev_params::num_stddev_number_calc();
    /*
    if (adjm_ptr)
    {
      mcmc_display_matrix.allocate(1,numdvar,1,mcmc_gui_length);
      number_offsets.allocate(1,numdvar);
      number_offsets=stddev_params::copy_all_number_offsets();
    }
    */
    dvector x(1,nvar);
    dvector scale(1,nvar);
    dmatrix values;
    int have_hist_flag=0;
    initial_params::xinit(x);
    dvector pen_vector(1,nvar);
    {
      initial_params::reset(dvar_vector(x),pen_vector);
      cout << pen_vector << endl << endl;
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
    int topt=0;
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
      int on,nopt;
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
        int tmp;
        read_covariance_matrix(S,nvar,tmp,sscale);
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
    int sgn;

    dmatrix symbds(1,2,1,nvar);
    initial_params::set_all_simulation_bounds(symbds);
    ofstream ofs_sd1((char*)(ad_comm::adprogram_name + adstring(".mc2")));

    {
      long int iseed=0;
      int number_sims;
      if (nmcmc<=0)
      {
        number_sims=  100000;
      }
      else
      {
        number_sims=  nmcmc;
      }
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
      //better_rand(iseed);
      double lprob=0.0;
      double lpinv=0.0;
      double lprob3=0.0;
      // get lower and upper bounds

      independent_variables y(1,nvar);
      independent_variables parsave(1,nvar);

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
        double br=rng.better_rand();
        if (tmp) have_hist_flag=1;
        chd=size_scale*chd;
        chdinv=chdinv/size_scale;
      }
      else
      {
        int on=-1;
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

      gradient_structure::set_NO_DERIVATIVES();
      ofstream ogs("sims");
      ogs << nvar << " " << number_sims << endl;
      initial_params::xinit(y);

      send_int_to_slaves(1);
      double llc=-pvm_master_get_monte_carlo_value(nvar,y);
      send_int_to_slaves(1);
      llbest=-pvm_master_get_monte_carlo_value(nvar,y);



      lbmax=llbest;
      // store current mcmc variable values in param_values
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
      int nopt;
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcscale",nopt))>-1)
      {
        if (nopt)
        {
          int iii=atoi(ad_comm::argv[on+1]);
          if (iii <=0)
          {
            cerr << " Invalid option following command line option -mcball -- "
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
                int nv1;
                uis >> nv1;
                if (nv1 !=nvar)
                {
                  cerr << "wrong number of independent variables in" <<
                    ad_comm::adprogram_name + adstring(".psv") <<
                  cerr << " I am starting a new file " << endl;
                  psvflag=1;
                }
              }
            }

            if (!psvflag) {
              pofs_psave=
                new uostream(
                  (char*)(ad_comm::adprogram_name + adstring(".psv")),ios::app);
            } else {
              pofs_psave=
                new uostream((char*)(ad_comm::adprogram_name + adstring(".psv")));
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
              (*pofs_psave) << nvar;
          }
        }
      }

      double pprobe=0.05;
      int probe_flag=0;
      int nopt=0;
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
          char * end;
          pprobe=strtod(ad_comm::argv[on+1],&end);
          if (pprobe<=0.00001 || pprobe > .499)
          {
            cerr << "Invalid argument to option -mcgrope" << endl;
            pprobe=-1.0;
            probe_flag=0;
          }
        }
      }

       int start_flag;
       int java_quit_flag=0;
       int der_flag,next_flag;
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
          if (adjm_ptr && i>1)
          {
            ad_update_mcmc_report(mcmc_display_matrix,mcmc_save_index,
              mcmc_wrap_flag);

            ad_update_mcmc_stats_report
              (i,number_sims,100.*tratio,100.*ratio);

            if (allocated(hist)) ad_update_mcmchist_report(hist,
              number_offsets,mean_mcmc_values,h);
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
        initial_params::restore_all_values(parsave,ii);
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
            new_probing_bounded_multivariate_normal_mcmc(nvar,symbds(1),symbds(2),
              chd,lpinv,-1*(chdinv*bmn1),pprobe,rng);

          send_int_to_slaves(1);
          ll=-pvm_master_get_monte_carlo_value(nvar,y);
          //cout << ll << " " << llc << endl;
          double ldiff=lprob-lpinv;
          logr= ll - ldiff - llc;
        }
        else
        {
          dvector bmn1=bounded_multivariate_uniform(nvar,symbds(1),symbds(2),chd,
                                                    lprob,rng);
          initial_params::add_random_vector(bmn1);
          initial_params::xinit(y);
          // get the simulation bounds for the inverse transition
          initial_params::set_all_simulation_bounds(symbds);
          bounded_multivariate_uniform_mcmc(nvar,symbds(1),symbds(2),chd,
                                            lpinv,-1*(chdinv*bmn1),rng);
          send_int_to_slaves(1);
          ll=-pvm_master_get_monte_carlo_value(nvar,y);
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
          /*
          if (adjm_ptr)
          {
            ii=1;
            stddev_params::copy_all_number_values(mcmc_number_values,ii);
          }
          */
          // update prob density for current point
          llc =ll;
          liac++;
          iac++;
        }
        //tmpof << mcmc_values(1) << endl;
        //tofs << mcmc_values<< " "  << llc << endl;
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
            s=2.*sqrt(1.e-20+square_mcmc_values-square(mean_mcmc_values));
            make_preliminary_hist(s,mean_mcmc_values,isim,values,hist,h,
              nslots,total_spread);
          }
        }
       }
      }
      if (!no_sd_mcmc && !have_hist_flag)
      {
        have_hist_flag=1;
        delete pofs_sd;
        pofs_sd=NULL;
        mean_mcmc_values/=double(isim);
        square_mcmc_values/=double(isim);
        s=2.*sqrt(1.e-20+square_mcmc_values-square(mean_mcmc_values));
        make_preliminary_hist(s,mean_mcmc_values,isim,values,hist,h,nslots,
          total_spread);
      }
      if (!no_sd_mcmc)
        if (iac>5)
          print_hist_data(hist,values,h,mean_mcmc_values,s,parsave,iseed,
            size_scale);
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
  send_int_to_slaves(0);
}
#endif
