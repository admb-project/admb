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

void function_minimizer::nuts_mcmc_routine(int nmcmc,int iseed0,double dscale,
					   int restart_flag) {
  if (nmcmc<=0) {
      cerr << endl << "Error: Negative iterations for MCMC not meaningful" << endl;
      ad_exit(1);
    }

  // I haven't figured out what to do with RE yet, so leaving as is for
  // now. -Cole
  uostream * pofs_psave=NULL;
  if (mcmc2_flag==1) {
      initial_params::restore_start_phase();
    }
  initial_params::set_inactive_random_effects();
  initial_params::set_active_random_effects();
  int nvar_re=initial_params::nvarcalc();
  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  if (mcmc2_flag==0) {
      initial_params::set_inactive_random_effects();
      nvar=initial_params::nvarcalc(); // get the number of active parameters
    }
  initial_params::restore_start_phase();
  independent_variables parsave(1,nvar_re);
  initial_params::mc_phase=1;
  int old_Hybrid_bounded_flag=-1;
  int on,nopt = 0;

  dvector x(1,nvar);
  dvector scale(1,nvar);
  initial_params::xinit(x);
  dvector pen_vector(1,nvar);
  {
    initial_params::reset(dvar_vector(x),pen_vector);
    //cout << pen_vector << endl << endl;
  }
  initial_params::mc_phase=0;
  initial_params::stddev_scale(scale,x);
  initial_params::mc_phase=1;


  //// ------------------------------ Parse input options
  // Step size. If not specified, will be adapted. If specified must be >0
  // and will not be adapted.
  double eps=0.1;
  double _eps=-1.0;
  int useDA=1; 			// whether to adapt step size
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hyeps",nopt))>-1) {
    if (!nopt){ // not specified means to adapt, using function below to find reasonable one

      cerr << "Warning: No step size given after -hyeps, ignoring" << endl;
      useDA=1;
    } else {			// read in specified value and do not adapt
      istringstream ist(ad_comm::argv[on+1]);
      ist >> _eps;
      if (_eps<=0) {
	cerr << "Error: step size (-hyeps argument) needs positive number";
	ad_exit(1);
      } else {
	eps=_eps;
	useDA=0;
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
	// input is in minutes, duration is in seconds so convert
	duration=_duration*60;
      }
    }
  }

  // chain number -- for console display purposes only
  int chain=1;
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
  // Number of leapfrog steps.
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hynstep",nopt))>-1) {
    if (nopt) {
      cerr << "Error: hynstep argument not allowed with NUTS " << endl;
      ad_exit(1);
    }
  }
  // Number of warmup samples if using adaptation of step size. Defaults to
  // half of iterations.
  int warmup= (int)nmcmc/2;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-warmup",nopt))>-1) {
    if (nopt) {
      int iii=atoi(ad_comm::argv[on+1]);
      if (iii <=0 || iii > nmcmc) {
	cerr << "Error: warmup must be 0 < warmup < nmcmc" << endl;
	ad_exit(1);
      } else {
	warmup=iii;
      }
    }
  }
  // Target acceptance rate for step size adaptation. Must be
  // 0<adapt_delta<1. Defaults to 0.8.
  double adapt_delta=0.8; // target acceptance rate specified by the user
  if ((on=option_match(ad_comm::argc,ad_comm::argv,"-adapt_delta",nopt))>-1) {
    if (nopt) {
      istringstream ist(ad_comm::argv[on+1]);
      double _adapt_delta;
      ist >> _adapt_delta;
      if (_adapt_delta < 0 || _adapt_delta > 1 ) {
	cerr << "Error: adapt_delta must be between 0 and 1" << endl;
	ad_exit(1);
      } else {
	adapt_delta=_adapt_delta;
      }
    }
  }
  // Max treedpeth is the number of times a NUTS trajectory will double in
  // length before stopping. Thus length <= 2^max_treedepth+1
  int max_treedepth=12;
  if ((on=option_match(ad_comm::argc,ad_comm::argv,"-max_treedepth",nopt))>-1) {
    if (nopt) {
      istringstream ist(ad_comm::argv[on+1]);
      int _max_treedepth;
      ist >> _max_treedepth;
      if (_max_treedepth <= 1) {
	cerr << "Error: max_treedepth must be > 1" << endl;
	ad_exit(1);
      } else {
	max_treedepth=_max_treedepth;
      }
    }
  }
  // User-specified initial values
  nopt=0;
  int ii=1;
  independent_variables theta(1,nvar); // the accepted par values
  independent_variables y(1,nvar); // the accepted par values
  initial_params::restore_start_phase();
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcpin",nopt))>-1) {
    if (nopt) {
      cifstream cif((char *)ad_comm::argv[on+1]);
      if (!cif) {
	cerr << "Error trying to open mcmc par input file "
	     << ad_comm::argv[on+1] << endl;
	exit(1);
      }
      cif >> theta;
      if (!cif) {
	cerr << "Error reading from mcmc par input file "
	     << ad_comm::argv[on+1] << endl;
	exit(1);
      }
    } else {
      cerr << "Illegal option with -mcpin" << endl;
    }
  } else {
    // Copy the MLE I think? Whatever was last executed by the model.
    ii=1;
    initial_params::copy_all_values(theta,ii);
  }

  // I think this backtransforms theta
  ii=1;
  cout << endl << endl << endl << "printing starting values" << endl;
  cout << theta << endl << endl;
  initial_params::restore_all_values(theta,ii);
  cout << endl << endl << endl << "printing starting values2" << endl;
  cout << theta << endl << endl;
  if (mcmc2_flag==0)
    {
      initial_params::set_inactive_random_effects();
    }
  gradient_structure::set_NO_DERIVATIVES();
  initial_params::xinit(y);
  cout << y << endl << endl;

  // Use diagnoal covariance (identity mass matrix)
  int diag_option=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcdiag"))>-1) {
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
  // Not sure what mcec is? Use empirical covariance?
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcec"))>-1) {
    cerr << endl << "Error: -mcec option not yet implemented with HMC" << endl;
    ad_exit(1);
  }
  // How much to thin, for now fixed at 1 and done externally.
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcsave"))>-1) {
    cerr << "Option -mcsave does not currently work with HMC -- every iteration is saved" << endl;
    ad_exit(1);
  }
  // Prepare the mass matrix for use. For now assuming mass matrix passed
  // on the unconstrained scale. Thus all the scales are assumed 1. The MLE
  // one should also not need to be adjusted since it is written
  // unconstrained already.
  dmatrix S(1,nvar,1,nvar);
  dvector old_scale(1,nvar);
  if (diag_option){		// set covariance to be diagonal
    S.initialize();
    for (int i=1;i<=nvar;i++) {
      S(i,i)=1;
    }
  } else {
    // Need to grab old_scale values still, since it is scaled below
    read_covariance_matrix(S,nvar,old_Hybrid_bounded_flag,old_scale);
    // If user toggles between RWM and NUTS the bounded flag can be
    // wrong. This would cause critical issues with bounding so catch it.
    if(old_Hybrid_bounded_flag != gradient_structure::Hybrid_bounded_flag) {
      cerr << "hybrid_bounded_flag read in from admodel.cov does not match:" <<
	gradient_structure::Hybrid_bounded_flag << " vs " <<  old_Hybrid_bounded_flag << endl
	   << "try restimating model." << endl;
      //ad_exit(1);
    }
  }
  // // need to rescale the hessian
  // // get the current scale
  dvector x0(1,nvar);
  initial_params::xinit(x0);
  // dvector current_scale(1,nvar);
  // int mctmp=initial_params::mc_phase;
  // initial_params::mc_phase=0;
  // initial_params::stddev_scale(current_scale,x0);
  // initial_params::mc_phase=mctmp;
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
  // if(diag_option){
  //   for (int i=1;i<=nvar;i++) {
  //     for (int j=1;j<=nvar;j++) {
  // 	S(i,j)*=current_scale(i)*current_scale(j);
  //     }
  //   }
  // }
  gradient_structure::set_NO_DERIVATIVES();
  if (mcmc2_flag==0) {
    initial_params::set_inactive_random_effects();
  }
  dmatrix chd = choleski_decomp(S); // cholesky decomp of mass matrix
  // cout << "S=" << S << endl;
  // cout << "chd=" << chd << endl;
  //// End of input processing
  // --------------------------------------------------

  //// Start of algorithm
  // Setup binary psv file to write samples to
  pofs_psave=
    new uostream((char*)(ad_comm::adprogram_name + adstring(".psv")));
  if (!pofs_psave|| !(*pofs_psave)) {
    cerr << "Error trying to open file" <<
      ad_comm::adprogram_name + adstring(".psv") << endl;
    ad_exit(1);
  }
  // Save nvar first. If added mcrestart (mcrb) functionality later need to
  // fix this line.
  (*pofs_psave) << nvar;
  // Setup random number generator, based on seed passed or hardcoded
  int iseed=2197;
  if (iseed0) iseed=iseed0;
  random_number_generator rng(iseed);
  gradient_structure::set_YES_DERIVATIVES();
  initial_params::xinit(x0);
  // Timings
  double time_warmup=0;
  double time_total=0;
  std::clock_t start = clock();
  time_t now = time(0);
  tm* localtm = localtime(&now);
  cout << endl << "Starting NUTS for model '" << ad_comm::adprogram_name <<
    "' at " << asctime(localtm);
  if(use_duration==1){
    cout << "Model will run for " << duration/60 <<
      " minutes or until " << nmcmc << " total iterations" << endl;
  }
  // write sampler parameters in format used by Shinystan
  dvector epsvec(1,nmcmc+1), epsbar(1,nmcmc+1), Hbar(1,nmcmc+1);
  epsvec.initialize(); epsbar.initialize(); Hbar.initialize();
  double mu;
  ofstream adaptation("adaptation.csv", ios::trunc);
  adaptation << "accept_stat__,stepsize__,treedepth__,n_leapfrog__,divergent__,energy__" << endl;

  // Declare and initialize the variables needed for the algorithm
  independent_variables z(1,nvar);
  dvector gr(1,nvar);		// gradients in unbounded space
  dvector gr2(1,nvar);		// initial rotated gradient
  dvector p(1,nvar);		// momentum vector
  double alphasum=0;		// running sum for calculating final accept ratio
  // References to left most and right most theta and momentum for current
  // subtree inside of buildtree. The ones proceeded with _ are passed
  // through buildtree by reference. Inside build_tree, _thetaplus is left
  // the same if moving in the left direction. Thus these are the global
  // left and right points.
  dvector _thetaminus(1,nvar);
  dvector _thetaplus(1,nvar);
  dvector _thetaprime(1,nvar);
  dvector _rminus(1,nvar);
  dvector _rplus(1,nvar);
  double _alphaprime;
  int _nalphaprime;
  bool _sprime;
  int _nprime;			//
  int _nfevals;	   		// trajectory length
  bool _divergent; // divergent transition
  int ndivergent=0; // # divergences post-warmup
  int nsamples=0; // total samples, not always nmcmc if duration option used

  // Start of MCMC chain
  for (int is=1;is<=nmcmc;is++) {
    // Randomize momentum for next iteration, update H, and reset the tree
    // elements.
    p.fill_randn(rng);
    _rminus=p; _rplus=p;
    _thetaprime=theta; _thetaminus=theta; _thetaplus=theta;
    // Reset model parameters to theta, whether updated or not in previous
    // iteration
    z=chd*theta;
    double nll=get_hybrid_monte_carlo_value(nvar,z,gr);
    gr2=gr*chd;
    double H0=-nll-0.5*norm2(p); // initial Hamiltonian value
    double logu=H0+log(randu(rng)); // slice variable
    if(useDA && is==1){
      // Setup dual averaging components to adapt step size
      eps=find_reasonable_stepsize(nvar,theta,p,chd);
      mu=log(10*eps);
      epsvec(1)=eps; epsbar(1)=1; Hbar(1)=0;
    }

    // Generate single NUTS trajectory by repeatedly calling build_tree
    // until a u-turn  or divergence occurs.
    int n=1;
    _divergent=0;
    _nfevals=0;
    bool s=1;
    int j=0;
    while (s) {
      double value = randu(rng);	   // runif(1)
      int v = 2 * (value < 0.5) - 1;
      // Add a trajectory of length 2^j, built to the left or right of
      // edges of the current tree.
      if (v == 1) {
	// Build a tree to the right from thetaplus.
	z=chd*_thetaplus;
	double nll=get_hybrid_monte_carlo_value(nvar,z,gr);
	gr2=gr*chd;
	build_tree(nvar, gr, chd, eps, _rplus, _thetaplus, gr2, logu, v, j,
		   H0, _thetaprime,  _thetaplus, _thetaminus, _rplus, _rminus,
		   _alphaprime, _nalphaprime, _sprime,
		   _nprime, _nfevals, _divergent, rng);
      } else {
	// Same but to the left from thetaminus
	z=chd*_thetaminus;
	double nll=get_hybrid_monte_carlo_value(nvar,z,gr);
	gr2=gr*chd;
	build_tree(nvar, gr, chd, eps, _rminus, _thetaminus, gr2, logu, v, j,
		   H0, _thetaprime,  _thetaplus, _thetaminus, _rplus, _rminus,
		   _alphaprime, _nalphaprime, _sprime,
		   _nprime, _nfevals, _divergent, rng);
      }

      // _thetaprime is the proposed point from that sample (drawn
      // uniformly), but still need to detemine whether to accept it at
      // each doubling. The last accepted point becomes the next sample. If
      // none are accepted, the same point is repeated twice.
      double rn = randu(rng);	   // Runif(1)
      if (_sprime == 1 && rn < double(_nprime)/double(n))
	theta=_thetaprime;

      // Test if a u-turn occured and update stopping criterion
      bool b = stop_criterion(nvar, _thetaminus, _thetaplus, _rminus, _rplus);
      s = _sprime*b;
      // Increment valid points and depth
      n += _nprime;
      ++j;
      if(j>=max_treedepth) break;
    } // end of single NUTS trajectory

    // Rerun model to update saved parameters internally before saving. Is
    // there a way to avoid doing this? I think I need to because of the
    // bounding functions??
    z=chd*theta;
    nll=get_hybrid_monte_carlo_value(nvar,z,gr);
    initial_params::copy_all_values(parsave,1.0);
    (*pofs_psave) << parsave; // saves row to psv file
    double alpha=0;
    if(_nalphaprime>0){
      alpha=double(_alphaprime)/double(_nalphaprime);
    }
    if(is > warmup){
      // Increment divergences only after warmup
      if(_divergent==1) ndivergent++;
      // running sum of alpha to calculate samplin
      alphasum=alphasum+alpha;
    }
    // Adaptation of step size (eps).
    if(useDA){
      if(is <= warmup){
	eps=adapt_eps(is, eps,  alpha, adapt_delta, mu, epsvec, epsbar, Hbar);
      } else {
	eps=epsbar(warmup);
      }
    }
    adaptation <<  alpha << "," <<  eps <<"," << j <<","
	       << _nfevals <<"," << _divergent <<"," << -nll << endl;
    print_mcmc_progress(is, nmcmc, warmup, chain);
    if(is ==warmup) time_warmup = ( std::clock()-start)/(double) CLOCKS_PER_SEC;
    time_total = ( std::clock()-start)/(double) CLOCKS_PER_SEC;
    nsamples=is;
    if(use_duration==1 && time_total > duration){
      // If duration option used, break loop after <duration> minutes.
      cout << is << " samples generated after " << duration/60 <<
	" minutes running." << endl;
      break;
    }
  } // end of MCMC chain

  // Information about run
  if(ndivergent>0)
    cout << "There were " << ndivergent << " divergent transitions after warmup" << endl;
  if(useDA)
    cout << "Final step size=" << eps << "; after " << warmup << " warmup iterations"<< endl;
  cout << "Final acceptance ratio=";
  printf("%.2f", alphasum /(nsamples-warmup));
  if(useDA) cout << ", and target=" << adapt_delta << endl;
  print_mcmc_timing(time_warmup, time_total);

  // I assume this closes the connection to the file??
  if (pofs_psave) {
      delete pofs_psave;
      pofs_psave=NULL;
    }
} // end of NUTS function

