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

  // Number of leapfrog steps.
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hynstep",nopt))>-1) {
    if (nopt) {
      cerr << "Error: hynstep argument not allowed with NUTS " << endl;
      ad_exit(1);
    }
  }

  // Number of warmup samples if using adaptation of step size. Defaults to
  // half of iterations.
  int nwarmup= (int)nmcmc/2;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-nwarmup",nopt))>-1) {
    if (nopt) {
      int iii=atoi(ad_comm::argv[on+1]);
      if (iii <=0 || iii > nmcmc) {
	cerr << "Error: nwarmup must be 0 < nwarmup < nmcmc" << endl;
	ad_exit(1);
      } else {
	nwarmup=iii;
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
  dvector theta(1,nvar); // the accepted par values
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
    initial_params::copy_all_values(theta,1);
  }
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
  cout << "S=" << S << endl;
  cout << "chd=" << chd << endl;
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
  // ---------- Setup dual averaging components to adapt step size
  dvector epsvec(1,nmcmc+1), epsbar(1,nmcmc+1), Hbar(1,nmcmc+1);
  epsvec.initialize(); epsbar.initialize(); Hbar.initialize();
  // Timings
  double time_warmup=0;
  double time_total=0;
  std::clock_t start = clock();
  time_t now = time(0);
  tm* localtm = localtime(&now);
  cout << endl << "Starting static HMC for model '" << ad_comm::adprogram_name <<
    "' at " << asctime(localtm);
  // write sampler parameters in format used by Shinystan
  ofstream adaptation("adaptation.csv", ios::trunc);
  adaptation << "accept_stat__,stepsize__,treedepth__,n_leapfrog__,divergent__,energy__" << endl;
  // Declare and initialize the variables needed for the algorithm
  independent_variables z(1,nvar);
  dvector gr(1,nvar);		// gradients in unbounded space
  dvector gr2(1,nvar);		// initial rotated gradient
  dvector p(1,nvar);		// momentum vector
  double mu=log(10*eps);
  double alphasum=0;		// running sum for calculating final accept ratio
  // ---------- End of dual averaging setup

  // Setup and intitialize variables for build_tree trajectory
  dvector _thetaminus(1,nvar);
  dvector _thetaplus(1,nvar);
  dvector _thetaprime(1,nvar);
  dvector _rminus(1,nvar);
  dvector _rplus(1,nvar);
  dvector thetaminus(1,nvar);
  dvector thetaplus(1,nvar);
  dvector rminus(1,nvar);
  dvector rplus(1,nvar);
  double _alphaprime;
  int _nalphaprime;
  bool _sprime;
  int _nprime;
  int _nfevals=0;
  bool _divergent=0;
  int ndivergent=0; // # divergences post-warmup

  // Start of MCMC chain
  for (int is=1;is<=nmcmc;is++) {
    // Randomize momentum for next iteration and update H
    p.fill_randn(rng);
    _rminus=p;
    _rplus=p;
    _thetaminus=theta;
    _thetaplus=theta;
    _thetaprime=theta;
    // Reset model parameters to theta, whether updated or not in previous iteration
    z=chd*theta;
    double nll=get_hybrid_monte_carlo_value(nvar,z,gr);
    double _nllprime=nll;
    double H0=nll+0.5*norm2(p);
    double logu= -H0 - exprnd(1.0);
    if(useDA && is==1){
      eps=find_reasonable_stepsize(nvar,theta,p,chd);
      epsvec(1)=eps; epsbar(1)=eps; Hbar(1)=0;
    }

    // --------------------------------------------------
    // Careful tests of build_tree trajectories by manually specifying
    // starting theta & r and then building tree. Should match R for same
    // model. Read in input values so easier to control everything.
    cifstream cif("input.txt");
    cif >> theta;
    cif >> p;
    int jj;
    cif >> jj;
    _rminus=p; _rplus=p;
    _thetaminus=theta;
    _thetaplus=theta;
    _thetaprime=theta;
    z=chd*theta;
    nll=get_hybrid_monte_carlo_value(nvar,z,gr);
    _nllprime=nll;
    H0=nll+0.5*norm2(p);
    logu= -15;//-H0 - exprnd(1.0);
    cout << "theta=" << theta << endl;
    cout << "p=" << p << endl;
    cout << "seed=" << iseed << endl;
    cout << "j=" << jj << endl;
    cout.precision(12);
    cout << "chd=" << chd << endl;
    ofstream out("trajectory.txt", ios::app);
    out << theta << theta << theta << " " << H0 << " " << H0 << p <<endl;
    build_tree_test(nvar, gr, chd, eps, p, theta, gr2, logu, 1, jj,
		    H0, _thetaprime,  _thetaplus, _thetaminus, _rplus, _rminus,
		    _alphaprime, _nalphaprime, _sprime,
		    _nprime, _nfevals, _divergent, _nllprime, rng, out);
    ofstream out2("theta_prime.txt", ios::trunc);
    out2 << _thetaprime << endl;
    ad_exit(1);
    // --------------------------------------------------

    // Generate single NUTS trajectory by repeatedly doubling build_tree
    int n = 1;
    _divergent=0;
    _nfevals=0;
    bool s = true;
    int j=0;
    while (s) {
      double value = randu(rng);	   // runif(1)
      int v = 2 * (value < 0.5) - 1;
      thetaplus=_thetaplus;
      thetaminus=_thetaminus;
      rplus=_rplus;
      rminus=_rminus;
      // cout << "is=" <<is << " tprime "<< _thetaprime << _nllprime << endl;
      //% Double the size of the tree.
      if (v == -1) {
	build_tree(nvar, gr, chd, eps, rplus, thetaplus, gr2, logu, v, j,
		   H0, _thetaprime,  _thetaplus, _thetaminus, _rplus, _rminus,
		   _alphaprime, _nalphaprime, _sprime,
		   _nprime, _nfevals, _divergent, _nllprime, rng);
	thetaplus = _thetaplus;
	rplus = _rplus;
      } else {
	build_tree(nvar, gr, chd, eps, rminus, thetaminus, gr2, logu, v, j,
		   H0, _thetaprime,  _thetaplus, _thetaminus, _rplus, _rminus,
		   _alphaprime, _nalphaprime, _sprime,
		   _nprime, _nfevals, _divergent, _nllprime, rng);
	thetaminus = _thetaminus;
	rminus = _rminus;
      }

      //% Use Metropolis-Hastings to decide whether or not to move to a
      //% point from the half-tree we just generated.
      // cout << j << " " << theta << " " <<  _thetaprime << endl;
      double rn = randu(rng);	   // Runif(1)
      if (_sprime == 1 && rn < double(_nprime)/n) {
	// Save _thetaprime
	theta=_thetaprime;
	// Rerun model to update parameters internally before saving
	z=chd*theta;
	nll=get_hybrid_monte_carlo_value(nvar,z,gr);
	initial_params::copy_all_values(parsave,1.0);
      }

      //% Update number of valid points we've seen.
      n += _nprime;
      //% Decide if it's time to stop.
      bool b = stop_criterion(nvar, _thetaminus, _thetaplus, _rminus, _rplus);
      s = _sprime && b;
      //% Increment depth.
      ++j;
      if(j>max_treedepth){cout << "max treedepth exceeded "<< is <<endl; break;}
    } // end of single NUTS trajectory

    // Save parameters to psv file, duplicated if rejected
    (*pofs_psave) << parsave;
    double alpha;
    if(_nalphaprime==0){
      alpha=0;
    } else {
      alpha=_alphaprime/_nalphaprime;
    }
    if(std::isnan(alpha)) alpha=0;
    if(is > nwarmup){
      if(_divergent==1) ndivergent++;
      alphasum=alphasum+alpha;
    }
    // Adaptation of step size (eps).
    if(useDA && is <= nwarmup){
      eps=adapt_eps(is, eps,  alpha, adapt_delta, mu, epsvec, epsbar, Hbar);
    }
    adaptation <<  alpha << "," <<  eps <<"," << j <<","
	       << _nfevals <<"," << _divergent <<"," << _nllprime << endl;
    if(is ==nwarmup) time_warmup = ( std::clock()-start)/(double) CLOCKS_PER_SEC;
    print_mcmc_progress(is, nmcmc, nwarmup);
  } // end of MCMC chain

  // Information about run
  if(ndivergent>0)
    cout << "There were " << ndivergent << " divergent transitions after warmup" << endl;
  if(useDA)
    cout << "Final step size=" << eps << "; after " << nwarmup << " warmup iterations"<< endl;
  cout << "Final acceptance ratio=" << alphasum /(nmcmc-nwarmup) << endl;
  print_mcmc_timing(time_warmup, time_total);

  // I assume this closes the connection to the file??
  if (pofs_psave) {
      delete pofs_psave;
      pofs_psave=NULL;
    }
} // end of NUTS function

