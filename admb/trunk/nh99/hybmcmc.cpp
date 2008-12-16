/*
 * $Id$
 * Author: David Fournier
 * Copyright (c) 2008 Regents of the University of California 
 */
#if defined(USE_LAPLACE)
#  include <df1b2fun.h>
#  include <adrndeff.h>
#endif
#include <admodel.h>


#if defined(__GNU__) || defined(UNIXKLUDGE) || defined(__SUN__) \
  || defined(__linux__)
  #define getch getchar
#endif

#ifdef __GNUDOS__
  #include <gccmanip.h>
#endif

#if defined (__ZTC__) || defined(__TURBOC__) || defined(__WAT32__) \
  || defined (__MSVC32__)
#  if !defined(__linux__)
     #include <conio.h>
#  endif
#endif

double better_rand(long int&);
void store_mcmc_values(BOR_CONST ofstream& ofs);
void set_labels_for_mcmc(void);
void save_mcmc_for_gui(const dvector& mcmc_values,dmatrix &mdm,int& ids);
void save_mcmc_for_gui1(const dvector& mcmc_values,
  dmatrix &mdm,int& ids,int& iwrap,ivector& no);

void check_java_flags(int& start_flag,int& quit_flag,int& der_flag,
  int& next_flag);
void print_hist_data(BOR_CONST dmatrix& hist,BOR_CONST dmatrix& values,BOR_CONST dvector& h,
  dvector& m,BOR_CONST dvector& s,BOR_CONST dvector& parsave,long int iseed, double size_scale);


int minnz(BOR_CONST dvector& x);
int maxnz(BOR_CONST dvector& xa);

void read_hessian_matrix_and_scale1(int nvar,BOR_CONST dmatrix& SS,double s,
  int mcmc2_flag);

int read_hist_data(BOR_CONST dmatrix& hist,BOR_CONST dvector& h,
  dvector& m,BOR_CONST dvector& s,BOR_CONST dvector& parsave,long int& iseed,BOR_CONST double& size_scale);

void make_preliminary_hist(BOR_CONST dvector& s,BOR_CONST dvector& m,int nsim,BOR_CONST dmatrix& values,
  dmatrix& hist,BOR_CONST dvector& h,int slots,double total_spread,int probflag=0);

void add_hist_values(BOR_CONST dvector& s,BOR_CONST dvector& m,BOR_CONST dmatrix& hist,
  dvector& mcmc_values,double llc,BOR_CONST dvector& h,int nslots,
  double total_spreadd,int probflag=0);

void add_guihist_values(BOR_CONST dvector& s,BOR_CONST dvector& m,
  BOR_CONST dmatrix& _hist,dvector& mcmcnumber_values,double llc,
  BOR_CONST dvector& h,int nslots,double total_spread);

void write_empirical_covariance_matrix(int ncor,BOR_CONST dvector& s_mean,BOR_CONST dmatrix& s_covar,
  adstring& prog_name);

void read_empirical_covariance_matrix(int nvar,BOR_CONST dmatrix& S,BOR_CONST adstring& prog_name);


void read_hessian_matrix_and_scale(int nvar,BOR_CONST dmatrix& S,BOR_CONST dvector& pen_vector);

int user_stop(void);

extern int ctlc_flag;
class admb_javapointers;
extern admb_javapointers * adjm_ptr;

dvector new_probing_bounded_multivariate_normal(int nvar,BOR_CONST dvector& a1,BOR_CONST dvector& b1,
  dmatrix& ch,long int& iseed,BOR_CONST double& wght,double pprobe);

void new_probing_bounded_multivariate_normal_mcmc(int nvar,BOR_CONST dvector& a1,BOR_CONST dvector& b1,
  dmatrix& ch,long int& iseed,BOR_CONST double& wght,BOR_CONST dvector& _y,double pprobe);

//void  newton_raftery_bayes_estimate(double cbf,int ic,BOR_CONST dvector& lk,double d);
void  newton_raftery_bayes_estimate_new(double cbf,int ic,BOR_CONST dvector& lk,double d);

void ad_update_mcmc_stats_report
  (int feval,int iter,double fval,double gmax);

void ad_update_function_minimizer_report(int feval,int iter,int phase,
  double fval,double gmax,const char * cbuf);
void ad_update_mcmc_report(dmatrix& m,int i,int j,int ff=0);
void ad_update_mcmchist_report(dmatrix& mcmc_values,ivector& number_offsets,
  dvector& mean_mcmc_values,dvector& h,int ff=0);

void ADSleep(int);

void function_minimizer::hybrid_mcmc_routine(int nmcmc,int iseed0,double dscale,
  int restart_flag)
{
  robust_hybrid_flag=0;
  uostream * pofs_psave=NULL;
  dmatrix mcmc_display_matrix;
  int mcmc_save_index=1; 
  int mcmc_wrap_flag=0;
  int mcmc_gui_length=10000;
  int no_sd_mcmc=0;
  
  int on2=-1;
  int nvar1=0;
  if ( (on2=option_match(ad_comm::argc,ad_comm::argv,"-nosdmcmc"))>-1)
  {
    no_sd_mcmc=1;
    
  }
  if (mcmc2_flag==1)
  {
    initial_params::restore_start_phase();
    nvar1=initial_params::nvarcalc(); // get the number of active parameters
  }

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


    int nvar_x=0;
#if defined(USE_LAPLACE)
    initial_params::set_inactive_random_effects();
    nvar_x=initial_params::nvarcalc(); 
    initial_params::set_active_random_effects();
    int nvar_re=initial_params::nvarcalc(); 
#endif


    int nvar=initial_params::nvarcalc(); // get the number of active parameters
    int scov_option=0;
    dmatrix s_covar;
    dvector s_mean;
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
  
    scov_option=1;
    s_covar.allocate(1,nvar,1,nvar);
    s_mean.allocate(1,nvar);
    s_mean.initialize();
    s_covar.initialize();

    int ndvar=stddev_params::num_stddev_calc();
    int numdvar=stddev_params::num_stddev_number_calc();

#if defined(USE_LAPLACE)
    if (mcmc2_flag==0)
    {
      initial_params::set_inactive_random_effects();
      nvar=initial_params::nvarcalc(); // get the number of active parameters
    }
#endif
    dvector x(1,nvar);
    //dvector scale(1,nvar);
    dmatrix values;
    int have_hist_flag=0;
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
    int topt=0;
    int hybnstep=10;
    double hybeps=0.1;
    double _hybeps=-1.0;
    int old_Hybrid_bounded_flag=-1;

    int on,nopt;
    if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hyeps",nopt))>-1)
    {
      if (!nopt)
      {
        cerr << "Usage -hyeps option needs number  -- ignored" << endl;
      }
      else
      {   
    
        istrstream ist(ad_comm::argv[on+1]);
        ist >> _hybeps;
    
        if (_hybeps<=0)
        {
          cerr << "Usage -hyeps option needs positive number  -- ignored" << endl;
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
    dmatrix S(1,nvar,1,nvar);
    dvector old_scale(1,nvar);
    int old_nvar;
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
        if (mcmc2_flag==0)
        {
          read_covariance_matrix(S,nvar,old_Hybrid_bounded_flag,old_scale);
        }
        else
        {
          int tmp_nvar;
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
    
    // will need this stuff to do restarts but for now
    // just topen a new file
    /*
    if (!psvflag) {
      pofs_psave=
        new uostream(
          (char*)(ad_comm::adprogram_name + adstring(".psv")),ios::app);
    } else {
     */
      pofs_psave=
        new uostream((char*)(ad_comm::adprogram_name + adstring(".psv")));
      (*pofs_psave) << nvar;
    //}
      // need to rescale the hessian
      // get the current scale
      dvector x0(1,nvar);
      dvector current_scale(1,nvar);
      initial_params::xinit(x0);   
      int mctmp=initial_params::mc_phase;
      initial_params::mc_phase=0;
      initial_params::stddev_scale(current_scale,x);
      initial_params::mc_phase=mctmp;
      int i;
      for (i=1;i<=nvar;i++)
      {
        for (int j=1;j<=nvar;j++)
        {
          S(i,j)*=old_scale(i)*old_scale(j);
        }
      }
      for (i=1;i<=nvar;i++)
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
      int sgn;
      // ***************************************************************
      // ***************************************************************
      // NEW HYBRID MCMC
      // ***************************************************************
      // ***************************************************************
      independent_variables z(1,nvar);
      dvector y(1,nvar);
      y.initialize();
#if defined(USE_LAPLACE)
      independent_variables parsave(1,nvar_re);
      initial_params::restore_start_phase(); 
#else
      independent_variables parsave(1,nvar);
#endif

#if defined(USE_LAPLACE)
      if (mcmc2_flag==0)
      {
        initial_params::set_inactive_random_effects();
      }
#endif

      dvector p(1,nvar);  // momentum
      int iseed=2197;
      if (iseed0) iseed=iseed0;
      random_number_generator rng(iseed);
      gradient_structure::set_YES_DERIVATIVES();
      ofstream ogs("sims");
      initial_params::xinit(x0);   
      dvector g(1,nvar);
      
      z=x0+chd*y;
      double llc=get_hybrid_monte_carlo_value(nvar,z,g);
      llbest=get_hybrid_monte_carlo_value(nvar,z,g);
      lbmax=llbest;


       int number_sims;
       if (nmcmc<=0)
       {
         number_sims=  100000;
       }
       else
       {
         number_sims=  nmcmc;
       }
       double hybeps2=0.5*hybeps;
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
       double tmpprior;
       int ii=1;
       initial_params::copy_all_values(parsave,ii);
       // detmine whether to go forward or backward
       
       double iaccept=0.0;
       for (int is=1;is<=number_sims;is++)
       {
         int forflag=1;
         double rnd=randu(rng);
         //if (rnd<0.5) forflag=0;
         double hstep,hstep2;
         //if (forflag)
           hstep=hybeps;
         //else
         // hstep=-hybeps;
         hstep2=0.5*hstep;
         // randomize the number of steps
         double rnd2=randn(rng);
         int hnsteps=hybnstep*exp(.2*rnd2);
         
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
         cout << iaccept/is << " " << Hbegin-Ham << " " << Ham << endl;
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
    // ***************************************************************
    // ***************************************************************
    // ***************************************************************
    if (pofs_psave)
    {
      delete pofs_psave;
      pofs_psave=NULL;
    }
  }
}

double function_minimizer::get_hybrid_monte_carlo_value(int nvar, 
  const independent_variables& x,dvector& g)
{
  //initial_params::xinit(x);   
  double f=0.0;
#if defined(USE_LAPLACE)
  if (mcmc2_flag==0 && lapprox)
  {
    cerr << "error not implemented" << endl;
    ad_exit(1);
    g=(*lapprox)(x,f,this);
  }
  else
  {
#endif
    dvariable vf=0.0;
    dvar_vector vx=dvar_vector(x);
    vf=initial_params::reset(vx);
    *objective_function_value::pobjfun=0.0;
    userfunction();
    dvar_vector d(1,nvar);
    initial_params::stddev_vscale(d,vx);
    vf-=sum(log(d));
    vf+=*objective_function_value::pobjfun;
    f=value(vf);
    gradcalc(nvar,g);
#if defined(USE_LAPLACE)
  }
#endif
  return f;
}



