/**
   Author: Cole Monnahan
   Copyright (c) 2016 ADMB Foundation

   \file
   This file was copied from hybmcmc.cpp to use as a template to create updated Hamiltonian Monte Carlo
   samplers (static HMC and No-u-turn).
*/

#include "admodel.h"
#ifndef OPT_LIB
#include <cassert>
#endif
#include<ctime>

void read_empirical_covariance_matrix(int nvar, const dmatrix& S, const adstring& prog_name);
void read_hessian_matrix_and_scale1(int nvar, const dmatrix& _SS, double s, int mcmc2_flag);

void function_minimizer::hmc_mcmc_routine(int nmcmc,int iseed0,double dscale,
					  int restart_flag) {

  if (nmcmc<=0)
    {
      cerr << endl << "Error: Negative iterations for MCMC not meaningful" << endl;
      ad_exit(1);
    }

  uostream * pofs_psave=NULL;
  if (mcmc2_flag==1)
    {
      initial_params::restore_start_phase();
    }
  initial_params::set_inactive_random_effects();
  initial_params::set_active_random_effects();
  int nvar_re=initial_params::nvarcalc();
  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  if (mcmc2_flag==0)
    {
      initial_params::set_inactive_random_effects();
      nvar=initial_params::nvarcalc(); // get the number of active parameters
    }
  initial_params::restore_start_phase();

  independent_variables parsave(1,nvar_re);
  // dvector x(1,nvar);
  // initial_params::xinit(x);
  // dvector pen_vector(1,nvar);
  // {
  //   initial_params::reset(dvar_vector(x),pen_vector);
  // }
  initial_params::mc_phase=1;

  int old_Hybrid_bounded_flag=-1;
  int on,nopt = 0;

  //// ------------------------------ Parse input options
  // Step size. If not specified, will be adapted. If specified must be >0
  // and will not be adapted.
  double eps=0.1;
  double _eps=-1.0;
  int useDA=1; 			// whether to adapt step size
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hyeps",nopt))>-1)
    {
      if (!nopt) // not specified means to adapt, using function below to find reasonable one
	{
	  cerr << "Warning: No step size given after -hyeps, ignoring" << endl;
	  useDA=1;
	}
      else			// read in specified value and do not adapt
	{
	  istringstream ist(ad_comm::argv[on+1]);
	  ist >> _eps;
	  if (_eps<=0)
	    {
	      cerr << "Error: step size (-hyeps argument) needs positive number";
	      ad_exit(1);
	    }
	  else
	    {
	      eps=_eps;
	      useDA=0;
	    }
	}
    }

  // Number of leapfrog steps. Defaults to 10.
  int L=10;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hynstep",nopt))>-1)
    {
      if (nopt)
	{
	  int _L=atoi(ad_comm::argv[on+1]);
	  if (_L < 1 )
	    {
	      cerr << "Error: hynstep argument must be integer > 0 " << endl;
	      ad_exit(1);
	    }
	  else
	    {
	      L=_L;
	    }
	}
    }

  // Number of warmup samples if using adaptation of step size. Defaults to
  // half of iterations.
  int nwarmup= (int)nmcmc/2;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-nwarmup",nopt))>-1)
    {
      if (nopt)
        {
          int iii=atoi(ad_comm::argv[on+1]);
          if (iii <=0 || iii > nmcmc)
	    {
	      cerr << "Error: nwarmup must be 0 < nwarmup < nmcmc" << endl;
	      ad_exit(1);
	    }
          else
	    {
	      nwarmup=iii;
	    }
        }
    }

  // Target acceptance rate for step size adaptation. Must be
  // 0<adapt_delta<1. Defaults to 0.8.
  double adapt_delta=0.8; // target acceptance rate specified by the user
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-adapt_delta",nopt))>-1)
    {
      if (nopt)
	{
	  istringstream ist(ad_comm::argv[on+1]);
	  double _adapt_delta;
	  ist >> _adapt_delta;
	  if (_adapt_delta < 0 || _adapt_delta > 1 )
	    {
	      cerr << "Error: adapt_delta must be between 0 and 1"
		" using default of 0.8" << endl;
	    }
	  else
	    {
	      adapt_delta=_adapt_delta;
	    }
	}
    }
  // Use diagnoal covariance (identity mass matrix)
  int diag_option=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcdiag"))>-1)
    {
      diag_option=1;
      cout << " Setting covariance matrix to diagonal with entries " << dscale
	   << endl;
    }
  // Restart chain from previous run?
  int mcrestart_flag=option_match(ad_comm::argc,ad_comm::argv,"-mcr");
  if(mcrestart_flag > -1){
    cerr << endl << "Error: -mcr option not implemented for HMC" << endl;
    ad_exit(1);
  }

  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcec"))>-1)
    {
      cerr << endl << "Error: -mcec option not yet implemented with HMC" << endl;
      ad_exit(1);
      // use_empirical_flag=1;
      // read_empirical_covariance_matrix(nvar,S,ad_comm::adprogram_name);
    }

  // Prepare the mass matrix for use. Depends on many factors below.
  dmatrix S(1,nvar,1,nvar);
  dvector old_scale(1,nvar);
  int old_nvar;
  // Need to grab old_scale values still, since it is scaled below
  read_covariance_matrix(S,nvar,old_Hybrid_bounded_flag,old_scale);
  if (diag_option)		// set covariance to be diagonal
    {
      S.initialize();
      for (int i=1;i<=nvar;i++)
	{
	  S(i,i)=dscale;
	}
    }

  // How much to thin, for now fixed at 1.
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcsave"))>-1)
    {
      cerr << "Option -mcsave does not currently work with HMC -- every iteration is saved" << endl;
      ad_exit(1);
    }
  //// ------------------------------ End of input processing


  //// Setup more inputs and outputs
  pofs_psave=
    new uostream((char*)(ad_comm::adprogram_name + adstring(".psv")));
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
  int mctmp=initial_params::mc_phase;
  initial_params::mc_phase=0;
  initial_params::stddev_scale(current_scale,x0);
  initial_params::mc_phase=mctmp;
  // cout << "old scale=" <<  old_scale << endl;
  // cout << "current scale=" << current_scale << endl;
  // cout << "S before=" << S << endl;
  // I think this is only needed if mcmc2 is used??
  // for (int i=1;i<=nvar;i++)
  //   {
  //     for (int j=1;j<=nvar;j++)
  // 	{
  // 	  S(i,j)*=old_scale(i)*old_scale(j);
  // 	}
  //   }
  if(diag_option){
    for (int i=1;i<=nvar;i++)
      {
	for (int j=1;j<=nvar;j++)
	  {
	    S(i,j)*=current_scale(i)*current_scale(j);
	  }
      }
  }
  //  cout << "S after=" << S << endl;
  gradient_structure::set_NO_DERIVATIVES();
  if (mcmc2_flag==0)
    {
      initial_params::set_inactive_random_effects();
    }
  // Setup random number generator, based on seed passed
  int iseed=2197;
  if (iseed0) iseed=iseed0;
  random_number_generator rng(iseed);
  gradient_structure::set_YES_DERIVATIVES();
  initial_params::xinit(x0);

  // Dual averaging components
  double gamma=0.05;  double t0=10;  double kappa=0.75;
  double mu=log(10*eps);
  dvector epsvec(1,nmcmc+1), epsbar(1,nmcmc+1), Hbar(1,nmcmc+1);
  epsvec.initialize(); epsbar.initialize(); Hbar.initialize();
  epsvec(1)=eps; epsbar(1)=eps; Hbar(1)=0;
  int divergence;		// boolean for whether divergence occured
  dvector pp(1,nvar);
  pp.fill_randn(rng);
  double time_warmup=0;
  double time_total=0;
  std::clock_t start = clock();
  time_t now = time(0);
  tm* localtm = localtime(&now);
  cout << endl << "Starting static HMC for model '" << ad_comm::adprogram_name <<
    "' at " << asctime(localtm);
  // write sampler parameters
  ofstream adaptation("adaptation.csv", ios::trunc);
  adaptation << "accept_stat__,stepsize__,int_time__,energy__,lp__" << endl;


  // Declare and initialize the variables needed for the algorithm
  dmatrix chd = choleski_decomp(S); // cholesky decomp of mass matrix
  dvector y(1,nvar); // unbounded parameters
  y.initialize();
  // transformed params
  independent_variables z(1,nvar); z=chd*y;
  dvector gr(1,nvar);		// gradients in unbounded space
  // Need to run this to fill gr with current gradients and initial NLL.
  double nllbegin=get_hybrid_monte_carlo_value(nvar,z,gr);
  if(std::isnan(nllbegin)){
    cerr << "Starting MCMC trajectory at NaN -- something is wrong!" << endl;
    ad_exit(1);
  }
  // initial rotated gradient
  dvector gr2(1,nvar); gr2=gr*chd;
  dvector p(1,nvar);		// momentum vector
  // Copy initial value to parsave in case first trajectory rejected
  initial_params::copy_all_values(parsave,1.0);
  double iaccept=0.0;
  // The gradient and params at beginning of trajectory, in case rejected.
  dvector gr2begin(1,nvar); gr2begin=gr2;
  dvector ybegin(1,nvar); ybegin=y;
  double nll=nllbegin;
  if(useDA) eps=find_reasonable_stepsize(nvar,z,gr, chd, eps, pp);

  // Start of MCMC chain
  for (int is=1;is<=nmcmc;is++) {
    // Random momentum for next iteration, only affects Ham values
    p.fill_randn(rng);
    double H0=nll+0.5*norm2(p);

    // Generate trajectory
    divergence=0;
    for (int i=1;i<=L;i++) {
      // leapfrog updates gr, p, y, and gr2 by reference
      nll=leapfrog(nvar, gr, chd, eps, p, y, gr2);
      // Break trajectory early if a divergence occurs to save computation
      if(std::isnan(nll)){
	divergence=1; break;
      }
    } // end of trajectory

    // Test whether to accept the proposed state
    double Ham=nll+0.5*norm2(p); // Update Hamiltonian for proposed set
    double alpha=min(1.0, exp(H0-Ham)); // acceptance ratio
    double rr=randu(rng);	   // Runif(1)
    if (rr<alpha && !divergence){ // accept
      iaccept++;
      // Update for next iteration: params, Hamiltonian and gr2
      ybegin=y;
      gr2begin=gr2;
      nllbegin=nll;
      initial_params::copy_all_values(parsave,1.0);
    } else {
      // Reject and don't update anything to reuse initials for next trajectory
      y=ybegin;
      gr2=gr2begin;
      nll=nllbegin;
    }
    // Save parameters to psv file, duplicated if rejected
    (*pofs_psave) << parsave;

    // Adaptation of step size (eps).
    if(useDA && is <= nwarmup){
      // If divergence, there is 0 acceptance probability so alpha=0.
      if(std::isnan(alpha)) alpha=0;
      Hbar(is+1)= (1-1/(is+t0))*Hbar(is) + (adapt_delta-alpha)/(is+t0);
      double logeps=mu-sqrt(is)*Hbar(is+1)/gamma;
      epsvec(is+1)=exp(logeps);
      double logepsbar= pow(is, -kappa)*logeps+(1-pow(is,-kappa))*log(epsbar(is));
      epsbar(is+1)=exp(logepsbar);
      eps=epsvec(is+1);	// this is the adapted step size for the next iteration
    }
    adaptation << alpha << "," <<  eps << "," << eps*L << "," << H0 << "," << -nll << endl;
    if(is ==nwarmup){
      time_warmup = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    }
    print_mcmc_progress(is, nmcmc, nwarmup);
  } // end of MCMC chain
  // This final ratio should closely match adapt_delta
  if(useDA){
    cout << "Final acceptance ratio=" << iaccept/nmcmc << " and target is " << adapt_delta<<endl;
    cout << "Final step size=" << eps << "; after " << nwarmup << " warmup iterations"<< endl;
  } else {
    cout << "Final acceptance ratio=" << iaccept/nmcmc << endl;
  }

  time_total = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  print_mcmc_timing(time_warmup, time_total);

  // I assume this closes the connection to the file??
  if (pofs_psave)
    {
      delete pofs_psave;
      pofs_psave=NULL;
    }
} // end of HMC function


  /**
   * Written by Dave, commented by Cole starting 8/31/2016
   * Description not yet available.
   * \param
   * x is vector of Choleski decomposed parameters (i.e., x=y*chd).
   * g is a vector of empty gradients
   * returns the negative log likelihood (density), but also stores gradients for x in g
   */
double function_minimizer::get_hybrid_monte_carlo_value(int nvar, const independent_variables& x,dvector& g)
{
  //initial_params::xinit(x);
  double f=0.0;
  if (mcmc2_flag==0 && lapprox)
    {
      cerr << "HMC not implemented for random effects models" << endl;
      ad_exit(1);
      g=(*lapprox)(x,f,this);
    }
  else
    {
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
    }
  return f;
}

void function_minimizer::print_mcmc_progress(int is, int nmcmc, int nwarmup)
{
  // Modified from Stan: sample::progress.hpp; 9/9/2016
  int refresh = floor(nmcmc/10);
  if (is==1 || is == nmcmc || is % refresh ==0 ){
    int width=1+std::ceil(std::log10(static_cast<double>(nmcmc)));
    cout << "Chain 1, " << "Iteration: " << std::setw(width) << is
	 << " / " << nmcmc << " [" << std::setw(3)
	 << static_cast<int>( (100.0 * (is / nmcmc )))
	 << "%] " << (is <= nwarmup ? " (Warmup)" : " (Sampling)") << endl;
  }
}

void function_minimizer::print_mcmc_timing(double time_warmup, double time_total)
{
  std::string title(" Elapsed Time: ");
  std::stringstream ss;
  ss.str("");
  ss << title << time_warmup << " seconds (Warm-up)";
  cout << ss.str() << endl;
  ss.str("");
  ss << std::string(title.size(), ' ') << time_total-time_warmup << " seconds (Sampling)";
  cout << ss.str() << endl;
  ss.str("");
  ss << std::string(title.size(), ' ') << time_total << " seconds (Total)";
  cout << ss.str() << endl;
}

double function_minimizer::find_reasonable_stepsize(int nvar, const independent_variables& x,dvector& gr,
						    dmatrix& chd, double eps, dvector pp)
{
  // Draw random momentum (used for all iterations)
  independent_variables z(1,nvar); // rotated bounded parameters???
  dvector pp2(1,nvar);
  dvector yy(1,nvar);
  dvector gr2(1,nvar);	  // rotated gradient

  yy.initialize();

  // Calculate initial Hamiltonian value
  double pprob1=0.5*norm2(pp);
  // negative log density at initial state
  z=chd*yy;
  double nll1=get_hybrid_monte_carlo_value(nvar,z,gr);
  dvector gr2begin=gr*chd; // rotated gradient
  double H1=nll1+pprob1;
  double eps2=eps;
  double a=-1;
  bool success=0; // whether or not algorithm worked after 50 iterations

  for(int k=1; k<50; k++){
    // Reset the position and momentum variables and gradients
    yy.initialize();

    // Make one leapfrog step
    dvector phalf=pp-eps2/2*gr2begin;
    yy+=eps2*phalf;
    z=chd*yy;
    double nll2=get_hybrid_monte_carlo_value(nvar,z,gr);
    gr2=gr*chd;
    pp2=phalf-eps2/2*gr2; // this leaves pp untouched
    // Calculate new Hamiltonian value
    double pprob2=0.5*norm2(pp2);
    double H2=nll2+pprob2;
    double accept_temp=exp(H1-H2);

    // On first step, determine whether to halve or double. If a=1, then
    // eps2 keeps doubling until alpha passes 0.5; otherwise it halves until
    // that happens.
    if(k==1){
      // Determine initial acceptance ratio is too big or too small
      bool result = exp(H1-H2)>0.5;
      if(std::isnan(result)) result=0; // if divergence occurs, acceptance prob is 0 so a=-1
      if(result) a=1;
    }
    // Check if the 1/2 threshold has been crossed
    double x1=pow(accept_temp,a);
    double x2=pow(2,-a);
    if(x1 < x2){
      cout << "Found reasonable step size of " << eps2 << " after " << k << " steps." << endl;
      eps=eps2;
      success=1;
      break;
    }
    // Otherwise either halve or double eps and do another iteration
    eps2=pow(2,a)*eps2;
  }
  if(success==0) {
    cerr << "Did not find reasonable initial step size after 50 iterations -- " <<
      "is something wrong with model?" << endl;
    ad_exit(1);
  }
  return(eps2);
} // end of function

/**
   Function to take a single HMC leapfrog step, given current position and
   momentum variables. Returns nll value but also updates position and
   momentum variables by reference.
 **/

double function_minimizer::leapfrog(int nvar, dvector& gr, dmatrix& chd, double eps, dvector& p, dvector& y,
				    dvector& gr2)
{
  independent_variables z(1,nvar); // rotated bounded parameters???
  dvector phalf;
  // Update momentum by half step (why negative?)
  phalf=p-eps/2*gr2;
  // Update parameters by full step
  y+=eps*phalf;
  // Transform parameters via mass matrix
  z=chd*y;
  // Get NLL and set updated gradient in gr by reference
  double nll=get_hybrid_monte_carlo_value(nvar,z,gr);
  // Update gradient via mass matrix
  gr2=gr*chd;
  // Last half step for momentum
  p=phalf-eps/2*gr2;
  return(nll);
}


