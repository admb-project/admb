/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <admodel.h>

#ifdef __GNUDOS__
  #include <gccmanip.h>
#endif

double inv_cumd_norm(_CONST double& x);
double inv_cumd_cauchy(_CONST double& x);
double inv_cumd_norms(_CONST double& x);
double cumd_norm(_CONST double& x);
double cumd_cauchy(_CONST double& x);
double density_cauchy(_CONST double& x);
double myran1(long int&);
double better_rand(long int&);

double log_likelihood_mixture(_CONST double& x);

void multivariate_mixture(BOR_CONST dvector& _mix,int nvar,long int& iseed,
  BOR_CONST double& _log_density_normal,BOR_CONST double& _log_density_cauchy,
  BOR_CONST double& _log_density_small_normal,int is);

dvector bounded_multivariate_cauchy(int nvar,BOR_CONST dvector& a1,
  dvector& b1,BOR_CONST dmatrix& ch,long int& iseed,BOR_CONST double& lprob,
  double& log_tprob,BOR_CONST int& outflag);

dvector bounded_robust_multivariate_normal(int nvar,BOR_CONST dvector& a1,
  dvector& b1,BOR_CONST dmatrix& ch,BOR_CONST dmatrix& ch3,BOR_CONST dmatrix& chinv,BOR_CONST dmatrix& ch3inv,
  double contaminant,long int& iseed,BOR_CONST double& lprob,BOR_CONST double& lprob3,
  double& log_tprob,BOR_CONST int& outflag);

void function_minimizer::monte_carlo_routine(void)
{
  initial_params::mc_phase=1;
  if (stddev_params::num_stddev_params==0) return;
  {
    int nvar=initial_params::nvarcalc(); // get the number of active parameters
    dvector x(1,nvar);
    dvector jac(1,nvar);
    initial_params::xinit(x); 
    initial_params::stddev_scale(jac,x);
    dvector bmn(1,nvar);
    bmn.initialize();
// ***************************************************************
    dvector scale(1,nvar);   // need to get scale from somewhere
    dvector diag(1,nvar);   // need to get scale from somewhere
    dvector v(1,nvar);  // need to read in v from model.rep
    dmatrix S(1,nvar,1,nvar);
    {
      adstring tmpstring="admodel.cov";
      if (ad_comm::wd_flag)
        tmpstring = ad_comm::adprogram_name + ".cov";
      uistream cif((char*)tmpstring);
      if (!cif)
      {
        cerr << "Error trying to open file " << tmpstring
	    << " for reading" << endl;
      }
      int tmp_nvar;
      cif >> tmp_nvar;
      if (nvar !=tmp_nvar)
      {
        cerr << "Incorrect number of independent variables in file"
            << tmpstring  << endl;
        exit(1);
      }
      cif >> S;
      if (!cif)
      {
        cerr << "error reading covariance matrix from "
	     <<   tmpstring << endl;
        exit(1);
      }

      initial_params::mc_phase=0;
      int check=initial_params::stddev_scale(scale,x);
      initial_params::mc_phase=1;
      {
        dmatrix tmp(1,nvar,1,nvar);
  
        int i;
        for (i=1;i<=nvar;i++)
        {
          tmp(i,i)=S(i,i)*scale(i)*scale(i);
          for (int j=1;j<i;j++)
          {
            tmp(i,j)=S(i,j)*scale(i)*scale(j);
            tmp(j,i)=tmp(i,j);
          }
          diag(i)=sqrt(tmp(i,i));
        }
        S=tmp;
        //cout << endl << S << endl << endl;
        //cout << endl << choleski_decomp(S) << endl << endl;

        for (i=1;i<=nvar;i++)
        {
          S(i,i)=S(i,i)/(diag(i)*diag(i));
          for (int j=1;j<i;j++)
          {
            S(i,j)=S(i,j)/(diag(i)*diag(j));
            S(j,i)=S(i,j);
          }
        }
      }
    }
    dmatrix CHD= choleski_decomp(S);
    int sgn;
    double lnd=ln_det(S,sgn);
    //cout << endl << S << endl << endl;
    //cout << endl << CHD << endl << endl;
  
    dmatrix chdec(1,nvar,1,nvar);
    chdec=choleski_decomp(S);
    {
      ofstream ofs("chol2");
      ofs << chdec << endl;
    }
    //cout << endl << chdec << endl << endl;

    //int check=initial_params::stddev_scale(jac,x);
    initial_params::montecarlo_scale(scale,x);
    {
      ofstream ofs("admodel.tmp");
      dmatrix covar(1,nvar,1,nvar);
    }
    double ll=0.0;
    initial_params::add_random_vector(jac,bmn,ll,diag);
#if defined(USE_DDOUBLE)
    double ljac0=sum(log(jac+double(1.e-50)));
#else
    double ljac0=sum(log(jac+1.e-50));
#endif
  
    dmatrix ch3=3.*chdec;
    dmatrix chinv=inv(chdec);
    dmatrix ch3inv=inv(ch3);
    double xxin;
  
    {
      long int iseed=0;
      int number_sims=  500;
      //cin >> iseed;
      iseed=-33517;
      cout << "Enter value for seed" << endl;
      cin >> iseed;
      cout << "Enter number of simulations" << endl;
      cin >> number_sims;
      if (iseed>0)
      {
        iseed=-iseed;
      }
      better_rand(iseed);   
      double lprob=0.0;
      double lprob3=0.0;
      // get lower and upper bounds
  
      //independent_variables x(1,nvar);
      independent_variables parsave(1,nvar);
  
      int ii=1;
      initial_params::copy_all_values(parsave,ii);
      gradient_structure::set_NO_DERIVATIVES();
      //ofstream ooff((char*) (ad_comm::adprogram_name + adstring(".mte")) );
      //ofstream ooff1((char*) (ad_comm::adprogram_name + adstring(".mt2")) );
      double cont=0.00;
      double log_tprob_normal=0.0;
      double log_tprob_small_normal=0.0;
      double log_tprob_cauchy=0.0;
      double log_tprob=0.0;
      int ndvar=stddev_params::num_stddev_calc();
      dvector param_values(1,ndvar);
      int outflag;
      //ooff1 << "Number of simulations = " << number_sims << endl; 
      ii=1;
      initial_params::restore_all_values(parsave,ii);

      double fbest;

      if (!ad_comm::pvm_manager)
      {
        fbest=get_monte_carlo_value(nvar,x);
      }
      else
      {
        switch (ad_comm::pvm_manager->mode)
        {
        case 1: // master
          fbest=pvm_master_get_monte_carlo_value(nvar,x); 
          break;
        case 2: // slave
          pvm_slave_get_monte_carlo_value(nvar); 
          break;
        default:
          cerr << "error illegal value for pvm_manager->mode" << endl;
          exit(1);
        }
      }

      multivariate_mixture(bmn,nvar,iseed,log_tprob_normal,
        log_tprob_cauchy,log_tprob_small_normal,-1);
      bmn=elem_div(bmn,scale);
      if (log_tprob_normal >= log_tprob_cauchy)
      {
        log_tprob=log_tprob_normal
          +log(0.95+0.05*exp(log_tprob_cauchy-log_tprob_normal));
      }
      else 
      {
        log_tprob=log_tprob_cauchy
          +log(0.95*exp(log_tprob_normal-log_tprob_cauchy)+.05);
      }
      double cdiff=-fbest-log_tprob;
      double cfb=-fbest;
      double clt=log_tprob;
      //ooff1 << " *  weight    likelihood   simprob  ln det "
       //"  ljac0   ljac     parameter value " << endl;
      //ooff1 << setw(10) << exp(-fbest-log_tprob) << " "  
        //<< setw(10) << exp(-fbest) << " "  
      //  << setw(10) << exp(log_tprob) << " "  
       //    << setw(10) << lnd << " "
       //    << setw(10) << param_values << endl;

      dvector y(1,nvar);

      // what is this supposed to do?
      //initial_params::get_jacobian_value(y,jac);
      //for (int i=1;i<=nvar;i++)
      //{
       // for (int j=1;j<=nvar;j++)
        //{
         // chdec(i,j)/=jac(i);
        //}
      //}

      //ofstream ogs("sims");
      //ogs << nvar << " " << number_sims << endl;
      for (int i=1;i<=number_sims;i++)
      {
        log_tprob_normal=0.0;
        log_tprob_small_normal=0.0;
        log_tprob_cauchy=0.0;
        log_tprob=0.0;
        ii=1;
        initial_params::restore_all_values(parsave,ii);

        double mixprob=better_rand(iseed);
        int mixswitch; 
        //if (mixprob<.0)
        if (mixprob<.05)
        {
          mixswitch=1; 
        }
        else if (mixprob<.50)
        {
          mixswitch=2; 
        }
        else
        {
          mixswitch=0; 
        }
        multivariate_mixture(bmn,nvar,iseed,log_tprob_normal,
          log_tprob_cauchy,log_tprob_small_normal,mixswitch);
        //bmn=elem_div(bmn,scale);

        if (log_tprob_normal >= log_tprob_cauchy)
        {
          log_tprob=log_tprob_normal
            +log( 0.50+.45*exp(log_tprob_small_normal-log_tprob_normal)
            +      .05*exp(log_tprob_cauchy-log_tprob_normal));
        }
        else 
        {
          log_tprob=log_tprob_cauchy
            +log( 0.50*exp(log_tprob_normal-log_tprob_cauchy)
            +     0.45*exp(log_tprob_small_normal-log_tprob_cauchy)+.05 );
        }
        dvector bmn1=CHD*bmn;
        //bmn1=elem_div(bmn1,scale);

        ll=0.0;
        initial_params::add_random_vector(jac,bmn1,ll,diag);
        initial_params::xinit(y);   

        //initial_params::stddev_scale(jac,y);
#if defined(USE_DDOUBLE)
        double ljac=sum(log(jac+double(1.e-50)));
#else
        double ljac=sum(log(jac+1.e-50));
#endif


       // ogs << log_tprob << " " << ll << " " << x << endl;
        double f;
        if (!ad_comm::pvm_manager)
        {
          f=get_monte_carlo_value(nvar,x);
        }
        else
        {
          switch (ad_comm::pvm_manager->mode)
          {
          case 1: // master
            f=pvm_master_get_monte_carlo_value(nvar,x); 
            break;
          case 2: // slave
            pvm_master_get_monte_carlo_value(nvar,x); 
            break;
          default:
            cerr << "error illega value for pvm_manager->mode" << endl;
            exit(1);
          }
        }
  
        //ooff << setw(12) << -f-log_tprob << "  " 
        //     << setw(12) << -f-log_tprob-ll << "  " 
        //     << setw(12) << fbest-f << "  " 
        //     << setw(12) << log_tprob << " " 
        //     << setw(5) << outflag << " " << setw(12) << -f;
        //ooff << endl;
       
        
        ii=1;
        stddev_params::copy_all_values(param_values,ii);
        //ooff << " " << setw(6) << "  " << param_values << endl; 
        /*
        if (mixswitch==1)
        {
          ooff1 << " *  weight    likelihood   simprob  ln det "
             "  ljac0   ljac     parameter value " << endl;
        }
        else if (mixswitch==2)
        {
          ooff1 << "    weight    likelihood   simprob  ln det "
             "  ljac0   ljac     parameter value " << endl;
        }
        else
        {
          ooff1 << " +  weight    likelihood   simprob  ln det "
             "  ljac0   ljac     parameter value " << endl;
        }
        ooff1 << setw(10) << exp(-f-log_tprob-cdiff+(ljac0-ljac) ) << " "  
          << setw(10) << -f << " "  
          << setw(10) << log_tprob << " "  
          << setw(10) << lnd << " "
          << setw(10) << ljac0 << " "
          << setw(10) << ljac << " "
          << setw(10) << param_values << endl;
        */
      }
      initial_params::mc_phase=0;
    }
  }
}



