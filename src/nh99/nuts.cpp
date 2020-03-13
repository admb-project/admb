
// $Id$
/**
 * @file nuts.cpp
 * The no-U-turn sampler (NUTS) MCMC routine.
 *
 * @author Cole C. Monnahan
 */

#include "admodel.h"
#ifndef OPT_LIB
#include <cassert>
#endif
#include<ctime>
void read_empirical_covariance_matrix(int nvar, const dmatrix& S, const adstring& prog_name);
void read_hessian_matrix_and_scale1(int nvar, const dmatrix& _SS, double s, int mcmc2_flag);

/**
   The function implements the MCMC algorithm NUTS, which is a self-tuning
   variant of Hamiltonian Monte Carlo. This function implements the
   original algorithm of Hoffman and Gelman (2014), namely dynamic
   trajectory lengths and step size adaptation via the dual averaging
   algorithm. In addition, it uses a diagonal mass matrix adaptation scheme
   based on Stan's. Thus, a covariance matrix is not necessary (so it works
   on models without an invertible Hessian).

   This routine also parses the command line arguments and performs actions for
   the following ones:
   * -adapt_delta Target acceptance rate [0,1]. Defaults to 0.8.
   * -adapt_mass Whether to use diagonal mass matrix adaptation (recommended).
   * -max_treedepth Maximum treedepth. Defaults to 12. Caps trajectory lengths at 2^12
   * -hyeps      The step size to use. If not specified it will be adapted.
   * -duration   The maximum runtime in minutes.
   * -mcdiag     Use diagonal covariance matrix
   * -mcpin NAME Read in starting values for MCMC from file NAME. NAME must be a valid ADMB '.par' file.
   * -warmup     The number of warmup iterations during which adaptation occurs.
   * -verbose_adapt_mass Flag whether to print mass adaptation updates to console.
   * \param int nmcmc The number of MCMC simulations to run.
   * \param int iseed0 Initial seed value for simulations.
   * \param double dscale Scale value used only if -mcdiag is specified. Disabled for NUTS.
   * \param int restart_flag Restart the MCMC, even if -mcr is specified. Disalbed for NUTS.
   * \return Nothing. Creates files <model>.psv with bounded parameters,
             and unbounded.csv with post-warmup unbounded samples.
**/

void function_minimizer::nuts_mcmc_routine(int nmcmc,int iseed0,double dscale,
					   int restart_flag) {
  if (nmcmc<=0) {
    cerr << endl << "Error: Negative iterations for MCMC not meaningful" << endl;
    ad_exit(1);
  }
  // I haven't figured out what to do with RE yet, so leaving as is for
  // now. It will throw an error later on. -Cole
  uostream * pofs_psave=NULL;
  if (mcmc2_flag==1) initial_params::restore_start_phase();
  initial_params::set_inactive_random_effects();
  initial_params::set_active_random_effects();
  // int nvar_re=initial_params::nvarcalc();
  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  if (mcmc2_flag==0){
    initial_params::set_inactive_random_effects();
    nvar=initial_params::nvarcalc(); // get the number of active parameters
  }
  initial_params::restore_start_phase();
  independent_variables parsave(1,nvar);
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

  // Run duration. Can specify warmup and duration, or warmup and
  // iter. Sampling period will stop after exceeding <duration> hours. If
  // duration ends before warmup is finished there will be no samples.
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
  // chain number -- for console display purposes only, useful when running
  // in parallel
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
  double adapt_delta=0.8;
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
      if (_max_treedepth < 0) {
	cerr << "Error: max_treedepth must be > 0" << endl;
	ad_exit(1);
      } else {
	max_treedepth=_max_treedepth;
      }
    }
  }
  // Use diagnoal covariance (identity mass matrix)
  int diag_option=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcdiag"))>-1) {
    diag_option=1;
    cout << "Setting covariance matrix to diagonal with entries" << endl;
  }
  // Whether to do diagonal adaptation of the mass matrix
  int adapt_mass=0;
  diagonal_metric_flag=0; // global flag used in functions to do more efficient calculations
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-adapt_mass"))>-1) {
    diagonal_metric_flag=1;
    adapt_mass=1;
  }
  // Whether to do dense adaptation of the mass matrix
  int adapt_mass_dense=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-adapt_mass_dense"))>-1) {
    if(adapt_mass==1){
      cerr << "You can only specify one of adapt_mass and adapt_mass_dense" << endl;
      ad_exit(1);
    }
    diagonal_metric_flag=0;
    adapt_mass_dense=1;
  }
  // Whether to print mass matrix adaptation steps to console
  int verbose_adapt_mass=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-verbose_adapt_mass"))>-1) {
    verbose_adapt_mass=1;
  }
  // Whether to print diagnostic info inside find_reasonable_stepsize function
  int verbose_find_epsilon=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-verbose_find_epsilon"))>-1) {
    verbose_find_epsilon=1;
  }
  // Whether to print diagnostic information
  int diagnostic_flag=0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-nutsdiagnostic"))>-1) {
    diagnostic_flag=1;
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
  // on the unconstrained scale using hybrid bounds, which is detectable
  // becuase the hbf flag is 1 in the .cov file. In that case, there is no
  // need to rescale. If unit mass matrix specified with -mcdiag then do
  // not rescale. If the user didnt overwrite admodel.cov, then it needs to
  // be rescaled since the scales in admodel.cov are with hbf=0. To rescale
  // means we need to know the MLE in bounded space, read in as mle
  // above. This prevents re-estimating the model each time. Then the new
  // scales can be calculated and the matrix converted to bounded, then
  // back to unbounded in hybrid space.
  //
  // Actually, I decided to force the user to rerun the model with -hbf 1
  // so that the scales are correct. This code wasnt working quite right
  // but leaving here in case someone wants to try adding this back later.
  dmatrix S(1,nvar,1,nvar);
  dvector old_scale(1,nvar);
  bool rescale_covar=0;
  if (diag_option){		// set covariance to be diagonal
    S.initialize();
    for (int i=1;i<=nvar;i++) {
      S(i,i)=1;
    }
  } else {
    // Need to grab old_scale values still
    read_covariance_matrix(S,nvar,old_Hybrid_bounded_flag,old_scale);
    // See above for why we need to check for this. Sometimes need to
    // rescale, sometimes not.
    if(old_Hybrid_bounded_flag != 1) {
      rescale_covar=1;
    }
  }
  if(rescale_covar){
    // If no covar was pushed by the user, then the MLE one is used
    // about. But since that admodel.cov file was written with the hbf=0
    // transformations, it is wrong now that hbf=1. So convert to covar in
    // transformed space using the old scales, and then back to the
    // untransformed space using the new scales.

    // For now turning this off. Might be easier and more reliable
    // to force user to rerun the model with the right hbf.
    cerr << "Error: To use -nuts a Hessian using the hybrid transformations is needed." <<
      endl << "...Rerun model with '-hbf' and try again" << endl;
    ad_exit(1);
    // cout << "Rescaling covariance matrix b/c scales don't match" << endl;
    // cout << "old scale=" <<  old_scale << endl;
    // cout << "current scale=" << current_scale << endl;
    // // cout << "S before=" << S << endl;
    // // Rescale the covariance matrix
    // for (int i=1;i<=nvar;i++) {
    //   for (int j=1;j<=nvar;j++) {
    // 	S(i,j)*=old_scale(i)*old_scale(j);
    // 	S(i,j)/=current_scale(i)*current_scale(j);
    //   }
    // }
  }
  dmatrix chd(1,nvar,1,nvar);
  dmatrix chdinv(1,nvar,1,nvar);
  // update chd and chdinv by reference
  calculate_chd_and_inverse(nvar, S, chd, chdinv);

  /// Mass matrix and inverse are now ready to be used.

  /// Prepare initial value. Need to both back-transform, and then rotate
  /// this to be in the "x" space.
  ///
  // User-specified initial values
  nopt=0;
  independent_variables z0(1,nvar); // inits in bounded space
  initial_params::restore_start_phase();
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcpin",nopt))>-1) {
    if (nopt) {
      cifstream cif((char *)ad_comm::argv[on+1]);
      if (!cif) {
	cerr << "Error trying to open mcmc par input file "
	     << ad_comm::argv[on+1] << endl;
	ad_exit(1);
      }
      cif >> z0;
      if (!cif) {
	cerr << "Error reading from mcmc par input file "
	     << ad_comm::argv[on+1] << endl;
	ad_exit(1);
      }
    } else {
      cerr << "Illegal option with -mcpin" << endl;
    }
  } else {
    // If user didnt specify one, use MLE values. Store saved MLEs from
    // admodel.hes file in bounded space into initial parameters z0
    read_mle_hmc(nvar, z0);
  }
  /// Now z0 is either the MLE or the user specified value
// Setup binary psv file to write samples to
  pofs_psave=
    new uostream((char*)(ad_comm::adprogram_name + adstring(".psv")));
  if (!pofs_psave|| !(*pofs_psave)) {
    cerr << "Error trying to open file" <<
      ad_comm::adprogram_name + adstring(".psv") << endl;
    ad_exit(1);
  }
  // These files holds the rotated (x), unbounded (y) and bounded (z)
  // samples (not warmup). Can read this in to get empirical covariance on
  // the unbounded scale and then put back into admodel.cov. Or look at how
  // mass matrix is doing. For now turned off rotated and bounded since
  // don't need those immediately
  // ofstream rotated("rotated.csv", ios::trunc);
  // ofstream bounded("bounded.csv", ios::trunc);
  ofstream unbounded("unbounded.csv", ios::trunc);
  // Save nvar first. If added mcrestart (mcrb) functionality later need to
  // fix this line.
  (*pofs_psave) << nvar;
  // Setup random number generator, based on seed passed or hardcoded
  int iseed = iseed0 ? iseed0 : rand();
  random_number_generator rng(iseed);
  // Run timings
  double time_warmup=0;
  double time_total=0;
  std::clock_t start = clock();
  time_t now = time(0);
  tm* localtm = localtime(&now);
  std::string m=get_filename((char*)ad_comm::adprogram_name);
  cout << endl << endl << "Chain " << chain << ": Starting NUTS for model '" << m <<
    "' at " << asctime(localtm);
  if(use_duration==1){
    cout << "Chain " << chain << ": Model will run for " << duration/60 <<
      " minutes or until " << nmcmc << " total iterations" << endl;
  }
  if(adapt_mass || adapt_mass_dense){
    if(warmup < 150){
      // Turn off if too few samples to properly do it. But keep using
      // diagonal efficiency.
      cerr << "Chain " << chain << ": Mass matrix adaptation not allowed when warmup<150" << endl;
      ad_exit(1);
    }
    if( adapt_mass){ 
      cout << "Chain " << chain << ": Using diagonal mass matrix adaptation" << endl;
    } else {
      cout << "Chain " << chain << ": Using dense mass matrix adaptation" << endl;
    }
    if(verbose_adapt_mass==1){
      dvector tmp=diagonal(S);
      cout << "Chain " << chain << ": Initial variances, min=" << min(tmp) << " and max=" << max(tmp) << endl;
    }
  }
  // write sampler parameters in format used by Shinystan
  dvector epsvec(1,nmcmc+1), epsbar(1,nmcmc+1), Hbar(1,nmcmc+1);
  epsvec.initialize(); epsbar.initialize(); Hbar.initialize();
  double mu;
  ofstream adaptation("adaptation.csv", ios::trunc);
  adaptation << "accept_stat__,stepsize__,treedepth__,n_leapfrog__,divergent__,energy__" << endl;
  //// End of input processing and preparation
  // --------------------------------------------------

  /// Start initializing the algorithm at the initial point. z0
  // was specified by user, but need y0 and x0. First, pass z0
  // through the model. Since this wasn't necessarily the last
  // vector evaluated, need to propogate it through ADMB
  // internally so can use xinit().
  initial_params::restore_all_values(z0,1);
  independent_variables y0(1,nvar); // inits in unbounded space
  dvector current_scale(1,nvar);
  gradient_structure::set_YES_DERIVATIVES(); // don't know what this does
  // This copies the unbounded parameters into y0
  initial_params::xinit(y0);
  // Don't know what this does or if necessary
  dvector pen_vector(1,nvar);
  initial_params::reset(dvar_vector(y0),pen_vector);
  initial_params::mc_phase=0;
  initial_params::stddev_scale(current_scale,y0);
  initial_params::mc_phase=1;

  //// ---------- Start of algorithm
  // Declare and initialize the variables needed for the algorithm
  // Get NLL and gradient in unbounded space for initial value y0.
  dvector gr(1,nvar);		// gradients in unbounded space
  dvector gr2(1,nvar);		// gradients in rotated space
  std::clock_t start0 = clock();
  double nll=get_hybrid_monte_carlo_value(nvar,y0,gr);
  double time_gradient = ( std::clock()-start0)/(double) CLOCKS_PER_SEC;
  gr2=rotate_gradient(gr, chd);
  // Can now inverse rotate y0 to be x0 (algorithm space)
  independent_variables x0(1,nvar); // inits in algorithm space
  x0=rotate_pars(chdinv,y0);
  // Now have z0, y0, x0, objective fn value, gradients in
  // unbounded (y) and rotated (x) space all at the intial value.
  cout << "Chain " << chain << ": Initial negative log density= " << nll << endl;
  cout << "Chain " << chain << ": Gradient eval took " << time_gradient <<
    " sec. " << nmcmc << " iter w/ 100 steps would take " ;
  printf("%.2f", nmcmc*100*time_gradient); cout << " sec." << endl;
  // Now initialize these into the algorithm arguments needed.
  independent_variables theta(1,nvar);
  // kind of a misnomer here: theta is in "x" or algorithm space
  // (before applying the mass matrix rotation, and before the
  // bounding functions are applied) 
  theta=x0;
  independent_variables z(1,nvar);
  independent_variables ynew(1,nvar); // local copy of y
  z=z0; ynew=y0;
  dvector p(1,nvar);		// momentum vector
  double alphasum=0;		// running sum for calculating final accept ratio
  // Global variables to track the extreme left and rightmost nodes of the
  // entire tree. This gets overwritten due to passing things by reference
  // in buildtree
  dvector thetaminus_end(1,nvar); dvector thetaplus_end(1,nvar);
  dvector rminus_end(1,nvar); dvector rplus_end(1,nvar);
  dvector gr2minus_end(1,nvar); dvector gr2plus_end(1,nvar);
  // References to left most and right most theta and momentum for current
  // subtree inside of buildtree. The ones proceeded with _ are passed
  // through buildtree by reference. Inside build_tree, _thetaplus is left
  // the same if moving in the left direction. Thus these are the global
  // left and right points.
  dvector _thetaminus(1,nvar); dvector _thetaplus(1,nvar);
  dvector _rminus(1,nvar); dvector _rplus(1,nvar);
  // Hold temporary copies of these as new points are chosen to
  // avoid recalculations at end of trajetory
  dvector thetaprime(1,nvar); dvector _thetaprime(1,nvar);
  dvector grprime(1,nvar); dvector _grprime(1,nvar);
  dvector gr2prime(1,nvar); dvector _gr2prime(1,nvar);
  double nllprime, _nllprime;
  independent_variables parsaveprime(1,nvar);
  independent_variables _parsaveprime(1,nvar);

  // These are used inside NUTS by reference
  int _nalphaprime, _nprime, _nfevals;
  double _alphaprime;
  bool _sprime, _divergent;
  int ndivergent=0; // # divergences post-warmup
  int nsamples=0; // total samples, not always nmcmc if duration option used
  // Declare some local variables used below.
  double H0, logu, value, rn, alpha;
  int n, j, v;
  bool s,b;
  // Mass matrix adapatation algorithm variables for diagonal
  dvector am(1,nvar);
  dvector am2(1,nvar);
  // and dense
  dvector adm(1,nvar);
  dmatrix adm2(1,nvar,1,nvar);
  int is2=0; int is3=0;
  int w1 = 75; int w2 = 50; int w3 = 25;
  int aws = w2; // adapt window size
  int anw = w1+w2; // adapt next window
  dmatrix metric(1,nvar,1,nvar); // holds updated metric
  if(diagnostic_flag){
    cout << "Initial chd=" << chd << endl;
    cout << "Initial negative log density=" << nll << endl;
    cout << "Initial gr in unbounded space= " << gr << endl;
    cout << "Initial gr in rotated space= " << gr2 << endl;
    cout << "Initial bounded parameters=" << z0 << endl;
    cout << "Initial unbounded parameters=" << y0 << endl;
    cout << "Initial rotated, unbounded parameters=" << x0 << endl;
  }
  // Start of MCMC chain
  for (int is=1;is<=nmcmc;is++) {
    // Randomize momentum for next iteration, update H, and reset the tree
    // elements.
    p.fill_randn(rng);
    _rminus=p; _rplus=p;
    // Note: theta, nll, gr, and gr2 are caried over from end of last loop
    _thetaprime=theta; _thetaminus=theta; _thetaplus=theta;
    H0=-nll-0.5*norm2(p); // initial Hamiltonian value
    logu=H0+log(randu(rng)); // slice variable
    if(useDA && is==1){
      // Setup dual averaging components to adapt step size
      eps=find_reasonable_stepsize(nvar,theta,p,chd,true, verbose_find_epsilon, chain);
      mu=log(10*eps);
      epsvec(1)=eps; epsbar(1)=1; Hbar(1)=0;
    }
    // Generate single NUTS trajectory by repeatedly doubling build_tree
    _nprime=0; _divergent=0; _nfevals=0;
    n=1; s=1; j=0;
    // Reset global ones to initial point of this trajectory
    thetaminus_end=theta; thetaplus_end=theta; thetaprime=theta;
    rminus_end=p; rplus_end=p;
    gr2minus_end=gr2; gr2plus_end=gr2; gr2prime=gr2;
    nllprime=nll; grprime=gr;
    while (s) {
      value = randu(rng);	   // runif(1)
      v = 2 * (value < 0.5) - 1;
      // Add a trajectory of length 2^j, built to the left or right of
      // edges of the current entire tree.
      if (v == 1) {
	// Build a tree to the right from thetaplus. The leftmost
	// point in the new subtree, which gets overwritten in
	// both the global _end variable, but also the _ ref
	// version.  Need to reset to the rightmost point, since
	// this may not have been last one executed and thus the
	// gradients are wrong
	gr2=gr2plus_end;
	build_tree(nvar, gr, chd, eps, rplus_end, thetaplus_end, gr2, logu, v, j,
		   H0, _thetaprime,  _thetaplus, _thetaminus, _rplus, _rminus,
		   _alphaprime, _nalphaprime, _sprime,
		   _nprime, _nfevals, _divergent, rng,
		   gr2plus_end, _grprime, _gr2prime, _nllprime, _parsaveprime);
	// Moved right, so update extreme right tree. Done by
	// reference in gr2plus_end, which is the gradient at the
	// rightmost point of the global trajectory.
	thetaplus_end=_thetaplus; rplus_end=_rplus;
      } else {
	// Same but to the left from thetaminus
	gr2=gr2minus_end;
	build_tree(nvar, gr, chd, eps, rminus_end, thetaminus_end, gr2, logu, v, j,
		   H0, _thetaprime,  _thetaplus, _thetaminus, _rplus, _rminus,
		   _alphaprime, _nalphaprime, _sprime,
		   _nprime, _nfevals, _divergent, rng,
		   gr2minus_end, _grprime, _gr2prime, _nllprime, _parsaveprime);
	thetaminus_end=_thetaminus; rminus_end=_rminus;
      }
      // _thetaprime is the proposed point from that sample (drawn
      // uniformly), but still need to detemine whether to accept it at
      // each doubling. The last accepted point becomes the next sample. If
      // none are accepted, the same point is repeated twice.
      rn = randu(rng);	   // Runif(1)
      if (_sprime == 1 && rn < double(_nprime)/double(n)){
	thetaprime=_thetaprime; // rotated, unbounded
	gr2prime=_gr2prime; //
	nllprime=_nllprime;
	parsaveprime=_parsaveprime;
	ynew=rotate_pars(chd,thetaprime); // unbounded
      }

      // Test if a u-turn occured across the whole subtree j. Previously we
      // only tested sub-subtrees.
      b= stop_criterion(nvar, thetaminus_end, thetaplus_end, rminus_end, rplus_end);
      s = _sprime*b;
      // Increment valid points and depth
      n += _nprime; ++j;
      if(j>=max_treedepth) break;
    } // end of single NUTS trajectory
    // Rerun model to update saved parameters internally before saving. Is
    // there a way to avoid doing this? I think I need to because of the
    // bounding functions??
    nll=nllprime;
    gr2=gr2prime;
    theta=thetaprime;
    parsave=parsaveprime;// initial_params::copy_all_values(parsave,1.0);
    // Write the rotated, unbounded, and bounded draws to csv files for
    // sampling draws only
    if(is>0){
      for(int i=1;i<nvar;i++) unbounded << ynew(i) << ", ";
      unbounded << ynew(nvar) << endl;
    }
    (*pofs_psave) << parsave; // save all bounded draws to psv file
    // Calculate estimated acceptance probability
     alpha=0;
    if(_nalphaprime>0) alpha=double(_alphaprime)/double(_nalphaprime);
    if(is > warmup){
      if(_divergent==1) ndivergent++;  // Increment divergences only after warmup
      // running sum of alpha to calculate average acceptance rate below
      alphasum+=alpha;
    }
    // Adaptation of step size (eps).
    if(useDA){
      if(is <= warmup){
	eps=adapt_eps(is, eps,  alpha, adapt_delta, mu, epsvec, epsbar, Hbar);
      } else {
	eps=epsbar(warmup);
      }
    }

    // Mass matrix adaptation. For now only diagonal
    bool slow=slow_phase(is, warmup, w1, w3);
    if( (adapt_mass || adapt_mass_dense) & slow){
      // If in slow phase, do adaptation of mass matrix
      if(is== w1){ // start of slow window
        // Initialize algorithm
	am.initialize();
	am2.initialize();
	adm.initialize();
	adm2.initialize();
	is2=0; is3=0;
      } else if(is<anw){ // middle of slow window
	// Update metric with newest sample in unboudned space (ynew)
	if(adapt_mass) add_sample_diag(nvar, is2, am, am2, ynew);
	if(adapt_mass_dense) add_sample_dense(nvar, is3, adm, adm2, ynew);
      } else if(is==anw){ // end of slow window
        // Update the mass matrix and chd
	if(adapt_mass){
	  metric.initialize();
	  dvector tmp=am2/(is2-1);
	  for(int i=1; i<=nvar; i++){
	    metric(i,i) = tmp(i);
	  }
	  if(verbose_adapt_mass==1){
	    cout << "Chain " << chain << ": Estimated variances, min=" << min(tmp) << " and max=" << max(tmp) << endl;
	  }
	} else {
	  // dense metric
	  metric=adm2/(is3-1);
	  if(verbose_adapt_mass==1){
	    dvector tmp=diagonal(metric);
	    cout << "Chain " << chain << ": Estimated dense variances, min=" << min(tmp) << " and max=" << max(tmp) << endl;
	  }
	}
	// Update chd and chdinv by reference, since metric changed
	calculate_chd_and_inverse(nvar, metric, chd, chdinv);
	// Since chd changed need to refresh values and gradients
	// in x space
	nll=get_hybrid_monte_carlo_value(nvar,ynew,gr);
	theta=rotate_pars(chdinv,ynew);
	gr2=rotate_gradient(gr, chd);
        // Calculate the next end window. If this overlaps into the final fast
        // period, it will be stretched to that point (warmup-w3)
	aws *=2;
        anw = compute_next_window(is, anw, warmup, w1, aws, w3);
	// Refind a reasonable step size since it can be really
	// different after changing M and reset algorithm
	// parameters
	eps=find_reasonable_stepsize(nvar,theta,p,chd, verbose_adapt_mass, verbose_find_epsilon, chain);
	epsvec.initialize(); epsbar.initialize(); Hbar.initialize();
	mu=log(10*eps);
	epsvec(is)=eps; epsbar(is)=1; Hbar(is)=0;
      } else {
	cerr << "error in adaptation" << endl;
	ad_exit(1);
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
      cout << "Chain " << chain << ":" <<  is << " samples generated after " << duration/60 <<
	" minutes running." << endl;
      break;
    }
  } // end of MCMC chain

  // Information about run
  if(ndivergent>0)
    cout << "Chain " << chain <<": There were " << ndivergent << " divergent transitions after warmup" << endl;
  if(useDA)
    cout << "Chain " << chain << ": Final step size=" << eps << "; after " << warmup << " warmup iterations"<< endl;
  cout << "Chain " << chain << ": Final acceptance ratio=";
  printf("%.2f", alphasum /(nsamples-warmup));
  if(useDA) cout << ", and target=" << adapt_delta << endl; else cout << endl;
  print_mcmc_timing(time_warmup, time_total, chain);
  // Close .psv file connection
  if (pofs_psave) {
    delete pofs_psave;
    pofs_psave=NULL;
  }
} // end of NUTS function

