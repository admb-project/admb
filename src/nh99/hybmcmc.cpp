/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include <sstream>
using std::istringstream;

#  include <df1b2fun.h>
#  include <adrndeff.h>
#include <admodel.h>

#if defined(_MSC_VER)
  #include <conio.h>
#endif

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

double better_rand(long int&);
void store_mcmc_values(const ofstream& ofs);
void set_labels_for_mcmc(void);

void print_hist_data(const dmatrix& hist, const dmatrix& values,
  const dvector& h, dvector& m, const dvector& s, const dvector& parsave,
  long int iseed, double size_scale);

int minnz(const dvector& x);
int maxnz(const dvector& xa);

void read_hessian_matrix_and_scale1(int nvar, const dmatrix& _SS,double s,
  int mcmc2_flag);

int read_hist_data(const dmatrix& hist, const dvector& h,
  dvector& m, const dvector& s, const dvector& parsave,long int& iseed,
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

dvector new_probing_bounded_multivariate_normal(int nvar, const dvector& a1,
  const dvector& b1, dmatrix& ch, const double& wght,double pprobe,
  random_number_generator& rng);

void new_probing_bounded_multivariate_normal_mcmc(int nvar, const dvector& a1,
  const dvector& b1, dmatrix& ch, const double& wght, const dvector& _y,
  double pprobe, random_number_generator& rng);

//void newton_raftery_bayes_estimate(double cbf,int ic, const dvector& lk,
//double d);

void ad_update_mcmc_stats_report
  (int feval,int iter,double fval,double gmax);

void ad_update_function_minimizer_report(int feval,int iter,int phase,
  double fval,double gmax,const char * cbuf);
void ad_update_mcmc_report(dmatrix& m,int i,int j,int ff=0);
void ad_update_mcmchist_report(dmatrix& mcmc_values,ivector& number_offsets,
  dvector& mean_mcmc_values,dvector& h,int ff=0);

/**
 * Description not yet available.
 * \param
 */
void function_minimizer::hybrid_mcmc_routine(int nmcmc,int iseed0,double dscale,
  int restart_flag)
{
  robust_hybrid_flag=0;
  uostream * pofs_psave=NULL;
  dmatrix mcmc_display_matrix;
  //int mcmc_save_index=1;
  //int mcmc_wrap_flag=0;

  int on2=-1;
  //int nvar1=0;
  if ( (on2=option_match(ad_comm::argc,ad_comm::argv,"-nosdmcmc"))>-1)
  {
    //int no_sd_mcmc = 1;
  }
  if (mcmc2_flag==1)
  {
    initial_params::restore_start_phase();
    //nvar1=initial_params::nvarcalc(); // get the number of active parameters
  }

  if (stddev_params::num_stddev_params==0)
  {
    cerr << " You must declare at least one object of type sdreport "
         << endl << " to do the mcmc calculations" << endl;
    //return;
  }
  {
    //ofstream of_bf("testbf");

    //if (adjm_ptr) set_labels_for_mcmc();

    ivector number_offsets;
    dvector lkvector;
    //double current_bf=0;
    //double lcurrent_bf=0;
    //double size_scale=1.0;
    //double total_spread=200;
    //double total_spread=2500;
    //uostream * pofs_sd = NULL;

    initial_params::set_inactive_random_effects();
    int nvar_x=initial_params::nvarcalc();
    initial_params::set_active_random_effects();
    int nvar_re=initial_params::nvarcalc();

    int nvar=initial_params::nvarcalc(); // get the number of active parameters
    dmatrix s_covar;
    dvector s_mean;
    //int ncsim=25000;
    //int nslots=800;
    //int nslots=3600;
    //int initial_nsim=4800;
    //int ntmp=0;
    //int ncor=0;
    //double bfsum=0;
    //int ibfcount=0;
    //double lbmax;

    s_covar.allocate(1,nvar,1,nvar);
    s_mean.allocate(1,nvar);
    s_mean.initialize();
    s_covar.initialize();

    int ndvar=stddev_params::num_stddev_calc();
    //int numdvar=stddev_params::num_stddev_number_calc();

    if (mcmc2_flag==0)
    {
      initial_params::set_inactive_random_effects();
      nvar=initial_params::nvarcalc(); // get the number of active parameters
    }

    independent_variables parsave(1,nvar_re);
    initial_params::restore_start_phase();

    dvector x(1,nvar);
    //dvector scale(1,nvar);
    dmatrix values;
    //int have_hist_flag=0;
    initial_params::xinit(x);
    dvector pen_vector(1,nvar);
    {
      initial_params::reset(dvar_vector(x),pen_vector);
      //cout << pen_vector << endl << endl;
    }

    initial_params::mc_phase=0;
    //initial_params::stddev_scale(scale,x);
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
    //int topt=0;
    int hybnstep=10;
    double hybeps=0.1;
    double _hybeps=-1.0;
    int old_Hybrid_bounded_flag=-1;

    int on,nopt = 0;
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hyeps",nopt))>-1)
    {
      if (!nopt)
      {
        cerr << "Usage -hyeps option needs number  -- ignored" << endl;
      }
      else
      {
        istringstream ist(ad_comm::argv[on+1]);
        ist >> _hybeps;

        if (_hybeps<=0)
        {
          cerr << "Usage -hyeps option needs positive number  -- ignored\n";
          _hybeps=-1.0;
        }
      }
    }
    if (_hybeps>0.0)
      hybeps=_hybeps;

    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hynstep",nopt))>-1)
    {
      if (nopt)
      {
        int iii=atoi(ad_comm::argv[on+1]);
        if (iii < 1 )
        {
          cerr << " -hynstep argument must be integer between > 0 --"
                  " using default of 10" << endl;
        }
        else
        {
          hybnstep=iii;
        }
      }
    }

    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcdiag"))>-1)
    {
      diag_option=1;
      cout << " Setting covariance matrix to diagonal with entries " << dscale
           << endl;
    }
    int mcrestart_flag=option_match(ad_comm::argc,ad_comm::argv,"-mcr");
    dmatrix S(1,nvar,1,nvar);
    dvector old_scale(1,nvar);
    int old_nvar;
    if (!diag_option)
    {
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
        if (mcmc2_flag==0)
        {
          read_covariance_matrix(S,nvar,old_Hybrid_bounded_flag,old_scale);
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
          dvector tmp=read_old_scale(old_nvar);
          old_scale=1.0;
          old_scale(1,old_nvar)=tmp;
        }
      }
      else
      {
        read_hessian_matrix_and_scale1(nvar,S,rescale_bounded_power,
          mcmc2_flag);
        //read_hessian_matrix_and_scale(nvar,S,pen_vector);
      }

      // maybe we dont want to do this?
      /*
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
      */
    }
    else
    {
      S.initialize();
      for (int i=1;i<=nvar;i++)
      {
        S(i,i)=dscale;
      }
    }

    // for hybrid mcmc option always save output
    //if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcsave"))>-1)
    if ( mcrestart_flag>-1)
    {
      // check that nvar is correct
      uistream uis((char*)(ad_comm::adprogram_name + adstring(".psv")));
      if (!uis)
      {
        cerr << "Error trying to open file" <<
          ad_comm::adprogram_name + adstring(".psv") <<
          " for mcrestart" <<   endl;
        ad_exit(1);
      } else {
        int nv1 = 0;
        uis >> nv1;
        if (nv1 !=nvar) {
          cerr << "wrong number of independent variables in" <<
            ad_comm::adprogram_name + adstring(".psv") << endl
           << " I found " << nv1 << " instead of " << nvar  << endl;
          ad_exit(1);
        }
        // get last x vector from file
#ifndef OPT_LIB
        assert(parsave.size() >= 0);
#endif
        std::streamoff sz = (unsigned int)parsave.size() * sizeof(double);
        // backup from end of file
        uis.seekg(-sz, ios::end);
        uis >> parsave;
       cout << " restored "  << parsave(parsave.indexmin()) << " "
            << parsave(parsave.indexmax()) << endl;
        if (!uis)
        {
          cerr << "error resotring last mcmc poistion from file "
            << ad_comm::adprogram_name + adstring(".psv") << endl;
          ad_exit(1);
        }
        int ii=1;
        dvector x0(1,nvar);
        initial_params::restore_all_values(parsave,ii);
        //x0.initialize();
        //dvector pen_vector(1,nvar);
        //initial_params::reset(dvar_vector(parsave),pen_vector);
        //initial_params::xinit(x0);
        //cout << " x0 " << x0(x0.indexmin()) << endl;
      }
    }


    if ( mcrestart_flag>-1)
    {
      pofs_psave= new uostream( (char*)(ad_comm::adprogram_name
          + adstring(".psv")),ios::app);
     /*
      pofs_psave->seekp(0,std::ios::end);
      *pofs_psave << 123;
      delete pofs_psave;
      uistream uis((char*)(ad_comm::adprogram_name + adstring(".psv")));
      if (!uis)
      {
        cerr << "Error trying to open file" <<
          ad_comm::adprogram_name + adstring(".psv") <<
          " for mcrestart" <<   endl;
        ad_exit(1);
      } else {
        int nv1;
        uis >> nv1;
        if (nv1 !=nvar) {
          cerr << "wrong number of independent variables in" <<
            ad_comm::adprogram_name + adstring(".psv") << endl
           << " I found " << nv1 << " instead of " << nvar  << endl;
          ad_exit(1);
        }
      }
     */
    }
    else
    {
      pofs_psave=
        new uostream((char*)(ad_comm::adprogram_name + adstring(".psv")));
    }

    if (!pofs_psave|| !(*pofs_psave))
    {
      cerr << "Error trying to open file" <<
        ad_comm::adprogram_name + adstring(".psv") << endl;
      ad_exit(1);
    }
    if (mcrestart_flag == -1 )
    {
        (*pofs_psave) << nvar;
    }

      // need to rescale the hessian
      // get the current scale
      dvector x0(1,nvar);
      dvector current_scale(1,nvar);
      initial_params::xinit(x0);
      // cout << "starting with " << x0(x0.indexmin()) << " "
        //    << x0(x0.indexmax()) << endl;
      int mctmp=initial_params::mc_phase;
      initial_params::mc_phase=0;
      initial_params::stddev_scale(current_scale,x);
      initial_params::mc_phase=mctmp;
      for (int i=1;i<=nvar;i++)
      {
        for (int j=1;j<=nvar;j++)
        {
          S(i,j)*=old_scale(i)*old_scale(j);
        }
      }
      for (int i=1;i<=nvar;i++)
      {
        for (int j=1;j<=nvar;j++)
        {
          S(i,j)/=current_scale(i)*current_scale(j);
        }
      }

      //cout << sort(eigenvalues(S)) << endl;
      dmatrix chd = choleski_decomp(S);
      //dmatrix tchd = trans(chd);
      //dmatrix chdinv=inv(chd);
      //int sgn;
      // ***************************************************************
      // ***************************************************************
      // NEW HYBRID MCMC
      // ***************************************************************
      // ***************************************************************
      independent_variables z(1,nvar);
      z=x0;
      gradient_structure::set_NO_DERIVATIVES();
      dvector g(1,nvar);
      cout << "initial ll value " << get_hybrid_monte_carlo_value(nvar,z,g)
          << endl;
      dvector y(1,nvar);
      y.initialize();

      if (mcmc2_flag==0)
      {
        initial_params::set_inactive_random_effects();
      }

      dvector p(1,nvar);  // momentum
      int iseed=2197;
      if (iseed0) iseed=iseed0;
      if ( mcrestart_flag>-1)
      {
        ifstream ifs("hybrid_seed");
        ifs >> iseed;
        if (!ifs)
        {
           cerr << "error reading random number seed" << endl;
        }
      }
      random_number_generator rng(iseed);
      gradient_structure::set_YES_DERIVATIVES();
      ofstream ogs("sims");
      initial_params::xinit(x0);

      z=x0+chd*y;
      /*double llc=*/get_hybrid_monte_carlo_value(nvar,z,g);
      /*double llbest=*/get_hybrid_monte_carlo_value(nvar,z,g);
      //lbmax=llbest;


       int number_sims;
       if (nmcmc<=0)
       {
         number_sims=  100000;
       }
       else
       {
         number_sims=  nmcmc;
       }
       //double hybeps2=0.5*hybeps;
       double beginprior=get_hybrid_monte_carlo_value(nvar,z,g);
       dvector Fbegin=g*chd;
       // use trand(chd) ?
       //dvector Fbegin=tchd*g;
       dvector F(1,nvar);
       F=Fbegin;
       p.fill_randn(rng);
       if (robust_hybrid_flag)
       {
         double choice=randu(rng);
         if (choice<0.05)
         {
           p*=3.0;
         }
       }
       dmatrix xvalues(1,number_sims,1,nvar);
       dvector yold(1,nvar);
       yold=y;
       double pprob;
       if (robust_hybrid_flag==0)
       {
         pprob=0.5*norm2(p);
       }
       else
       {
         double r2=0.5*norm2(p);
         pprob=-log(0.95*exp(-r2)+0.05/3.0*exp(-r2/9.0));
       }
       double Hbegin=beginprior+pprob;
       double tmpprior = 0;
       int ii=1;
       initial_params::copy_all_values(parsave,ii);
       // detmine whether to go forward or backward
       cout << "Starting from y=" << y << endl;
       cout << "Starting from z=" << z << endl;
       cout << "Starting from gr=" << g << endl;
       cout << "Starting from nll=" << beginprior << endl;
       // cout << "Starting from chd=" << chd << endl;
 
       double iaccept=0.0;
       for (int is=1;is<=number_sims;is++)
       {
         int forflag=1;
         //double rnd=randu(rng);
         //if (rnd<0.5) forflag=0;
         double hstep,hstep2;
         //if (forflag)
           hstep=hybeps;
         //else
         // hstep=-hybeps;
         hstep2=0.5*hstep;
         // randomize the number of steps
         double rnd2=randn(rng);
#ifdef OPT_LIB
         int hnsteps = (int)(exp(0.2 * rnd2) * hybnstep);
#else
         double _hnsteps=exp(0.2 * rnd2) * hybnstep;
         assert(_hnsteps > 0 && _hnsteps <= (double)INT_MAX);
         int hnsteps = (int)_hnsteps;
#endif
         for (int i=1;i<=hnsteps;i++)
         {
           if (forflag==1)
           {
             dvector phalf=p-hstep2*F;
             if (robust_hybrid_flag==0)
             {
               y+=hstep*phalf;
             }
             else
             {
               //pprob=-log(0.95*exp(-r2)+0.05/3.0*exp(-r2/9.0));
               double r2=0.5*norm2(phalf);
               double z=0.95*exp(-r2)+0.05/3.0*exp(-r2/9.0);
               double xx=(0.95*exp(-r2)+0.05/27.0*exp(-r2/9.0))/z;
               dvector zz=xx*phalf;
               y+=hstep*zz;
             }
             z=x0+chd*y;
             tmpprior=get_hybrid_monte_carlo_value(nvar,z,g);
             F=g*chd;
             //F=tchd*g;
             p=phalf-hstep2*F;
           }
           else
           {
             dvector phalf=p+hstep2*F;
             if (robust_hybrid_flag==0)
             {
               y-=hstep*phalf;
             }
             else
             {
               double r2=0.5*norm2(phalf);
               double z=0.95*exp(-r2)+0.05/3.0*exp(-r2/9.0);
               dvector zz=(0.95*exp(-r2)+0.05/27.0*exp(-r2/9.0))/z*phalf;
               y-=hstep*phalf;
             }
             z=x0+chd*y;
             tmpprior=get_hybrid_monte_carlo_value(nvar,z,g);
             F=g*chd;
             //F=tchd*g;
             p=phalf+hstep2*F;
           }
         }
         if (robust_hybrid_flag==0)
         {
           pprob=0.5*norm2(p);
         }
         else
         {
           double r2=0.5*norm2(p);
           pprob=-log(0.95*exp(-r2)+0.05/3.0*exp(-r2/9.0));
         }
         double Ham=tmpprior+pprob;
         double rr=randu(rng);
         double pp=exp(Hbegin-Ham);
         p.fill_randn(rng);
         //p*=1.2;
         if (robust_hybrid_flag)
         {
           double choice=randu(rng);
           if (choice<0.05)
           {
             p*=3.0;
           }
         }
         if (robust_hybrid_flag==0)
         {
           pprob=0.5*norm2(p);
         }
         else
         {
           double r2=0.5*norm2(p);
           pprob=-log(0.95*exp(-r2)+0.05/3.0*exp(-r2/9.0));
         }
         if ((is%50)==1)
           //  cout << iaccept/is << " " << Hbegin-Ham << " " << Ham << endl;
           cout << " hybrid sim " << is <<  "  accept rate " << iaccept/is
                << "  Hbegin-Ham " << Hbegin-Ham << "  Ham " << Ham << endl;
         if (rr<pp)
         {
           iaccept++;
           yold=y;
           beginprior=tmpprior;
           Hbegin=beginprior+pprob;
           Fbegin=F;
           ii=1;
           initial_params::copy_all_values(parsave,ii);
         }
         else
         {
           y=yold;
           z=x0+chd*y;
           Hbegin=beginprior+pprob;
           F=Fbegin;
         }
         (*pofs_psave) << parsave;
       }
      // cout << " saved  " << parsave(parsave.indexmin()) << " "
        //    << parsave(parsave.indexmax()) << endl;
       //double ll=get_hybrid_monte_carlo_value(nvar,parsave,g);
       //cout << "ll  " << ll << endl;
    // ***************************************************************
    // ***************************************************************
    // ***************************************************************
    ofstream ofs("hybrid_seed");
    int seed=(int) (10000*randu(rng));
    ofs << seed;
    if (pofs_psave)
    {
      delete pofs_psave;
      pofs_psave=NULL;
    }
  }
}

