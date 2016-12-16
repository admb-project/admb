double function_minimizer::exprnd(double p)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  // if particles decay once per second on average,
  // how much time, in seconds, until the next one?
  std::exponential_distribution<> d(p);
  return d(gen);
}


void function_minimizer::build_tree(int nvar, dvector& gr, dmaxtrix& chd, double eps, dvector& p,
		dvector& y, dvector& gr2, double logu, int v, int j, double H0) {
  if (j == 0) {
    //% Base case: Take a single leapfrog step in the direction v.
    //[thetaprime, rprime, gradprime, logpprime] = leapfrog(theta, r, grad, v*epsilon, f);
    // original    leapfrog(theta, r, grad, v * epsilon);
    cout << y << endl;
    double nll= leapfrog(nvar, gr, chd, eps, p, y, gr2);
    double Ham=nll+0.5*norm2(p);

    // Check for divergence. Either numerical (nll is nan) or a big
    // difference in H.
    _sprime = (logu - 1000) < Ham;
    if(std::isnan(nll)){
      _sprime=0;
      _divergent=1;
    }
    // Update the tree elements, which are returned by reference in
    // leapfrog.
    _thetaminus = y;
    _thetaplus = y;
    _rminus = p;
    _rplus = p;
    _nprime = logu < Ham;
    _nalphaprime = 1;
    // Acceptance probability
    _alphaprime=min(1.0, exp(H0-Ham));

  } else { // j > 1
    //% Recursion: Implicitly build the height j-1 left and right subtrees.
    //[thetaminus, rminus, gradminus, thetaplus, rplus, gradplus, thetaprime, gradprime, logpprime, nprime, sprime, alphaprime, nalphaprime] = ...
    build_tree(nvar, gr, chd, eps, p, y, gr2, logu, v, j-1, H0);

    // Temp, local copies of the global ones due to rerunning build_tree
    // below which will overwrite some of the global variables we need to
    // save.
    dvector thetaminus(1,nvar);
    dvector rminus(1,nvar);
    dvector thetaplus(1,nvar);
    dvector rplus(1,nvar);
    dvector thetaprime(1,nvar);
    thetaminus=_thetaminus;
    thetaplus=_thetaplus;
    thetaprime=_thetaprime;
    rminus=_rminus;
    rplus=_rplus;
    int nprime1 = _nprime;
    bool sprime1 = _sprime;
    double alphaprime1 = _alphaprime;
    int nalphaprime1 = _nalphaprime;

    // If valid trajectory keep building, otherwise exit function
    if (_sprime == 1) {
      // Make subtree to the left
      if (v == -1) {
	//[thetaminus, rminus, gradminus, ~, ~, ~, thetaprime2, gradprime2, logpprime2, nprime2, sprime2, alphaprime2, nalphaprime2] = ...
	build_tree(nvar, gr, chd, eps, rminus, thetaminus, gr2, logu, v, j-1, H0);
	thetaminus = _thetaminus;
	rminus = _rminus;
      } else { // make subtree to the right
	//[~, ~, ~, thetaplus, rplus, gradplus, thetaprime2, gradprime2, logpprime2, nprime2, sprime2, alphaprime2, nalphaprime2] = ...
	build_tree(nvar, gr, chd, eps, rplus, thetaplus, gr2, logu, v, j-1, H0);
	thetaplus = _thetaplus;
	rplus = _rplus;
      }//end

      // Update stopping and selection criteria using both subtrees.
      int nprime = nprime1 + _nprime;
      bool sprime = sprime1 + _sprime;
      double alphaprime = alphaprime1 + _alphaprime;
      int nalphaprime = nalphaprime1 + _nalphaprime;

      // Choose whether to keep the proposal thetaprime.
      double random_number = _rand();
      if(std::isnan(nprime)) nprime=0;
      if (nprime != 0 && random_number < double(_nprime)/double(nprime)) {
	// _thetaprime already updated globally above so do nothing
      } else {
	// Reuse the first instance by reverting to the local copy
	_thetaprime = thetaprime;
      }

      // Update the global variables for next subtree
      _nprime = nprime;
      _sprime = sprime && sprime2 && stop_criterion(thetaminus, thetaplus, rminus, rplus);
      _alphaprime = alphaprime;
      _nalphaprime = nalphaprime;
      _thetaminus=thetaminus;
      _thetaplus=thetaplus;
      _rminus=rminus;
      _rplus=rplus;
    } // end building trajectory
  }   // end recursion
}     // end function


bool function_minimizer::stop_criterion(int nvar, dvector* thetaminus, dvector* thetaplus,
					dvector* rminus, dvector* rplus)
{
  bool criterion;
  //thetavec = thetaplus - thetaminus;
  dvector(1, nvar) thetavec;
  thetavec=thetaplus-thetaminus;
  //criterion = (thetavec * rminus' >= 0) && (thetavec * rplus' >= 0);
  criterion = (thetavec*rminus+thetavec*rminus>=0) &&
			      (thetavec*rplus+thetavec*rplus>=0);
  return criterion;
}


double function_minimizer::adapt_eps(int ii, double eps, double alpha,
				     double& adapt_delta, double& mu,
				     dvector& epsvec, dvector& epsbar,
				     dvector& Hbar){
  double gamma=0.05;  double t0=10;  double kappa=0.75;
  // If divergence, there is 0 acceptance probability so alpha=0.
  if(std::isnan(alpha)) alpha=0;
  Hbar(ii+1)= (1-1/(ii+t0))*Hbar(ii) + (adapt_delta-alpha)/(ii+t0);
  double logeps=mu-sqrt(ii)*Hbar(ii+1)/gamma;
  epsvec(ii+1)=exp(logeps);
  double logepsbar= pow(ii, -kappa)*logeps+(1-pow(ii,-kappa))*log(epsbar(ii));
  epsbar(ii+1)=exp(logepsbar);
  return(epsvec(ii+1));
}

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

double function_minimizer::find_reasonable_stepsize(int nvar, dvector y, dvector p, dmatrix& chd)
{
  // This function holds the position (y) and momentum (p) vectors fixed
  // and takes a single step of size eps. This process repeats until a
  // reasonable eps is found. Thus need to make sure y and p are constant
  // and only eps changes.

  independent_variables z(1,nvar); // rotated bounded parameters
  dvector gr(1,nvar);		   // gradients
  double eps=1;			   // initial eps
  dvector p2(1,nvar);		// updated momentum
  dvector gr2(1,nvar);		// updated rotated gradient
  dvector y2(1,nvar);		// updated position

  // Calculate initial Hamiltonian value
  double pprob1=0.5*norm2(p);
  z=chd*y;
  double nllbegin=get_hybrid_monte_carlo_value(nvar,z,gr);
  dvector gr2begin=gr*chd; // rotated gradient
  double H1=nllbegin+pprob1;
  double a=-1;			// whether to double or halve eps
  bool success=0; // whether or not algorithm worked after 50 iterations

  for(int k=1; k<50; k++){
    // Reinitialize position and momentum at each step.
    p2=p;
    y2=y;
    gr2=gr2begin;

    // Make one leapfrog step and check acceptance ratio
    double nll2=leapfrog(nvar, gr, chd, eps, p2, y2, gr2);
    double pprob2=0.5*norm2(p2);
    double H2=nll2+pprob2;
    double alpha=exp(H1-H2);

    // On first step, determine whether to halve or double. If a=1, then
    // eps keeps doubling until alpha passes 0.5; otherwise it halves until
    // that happens.
    if(k==1){
      // Determine initial acceptance ratio is too big or too small
      bool result = alpha >0.5;
      // if divergence occurs, acceptance prob is 0 so a=-1
      if(std::isnan(result)) result=0;
      if(result) a=1;
    }
    // Check if the 1/2 threshold has been crossed
    double x1=pow(alpha,a);
    double x2=pow(2,-a);
    if(x1 < x2){
      cout << "Found reasonable step size of " << eps << " after " << k << " steps." << endl;
      success=1;
      break;
    }
    // Otherwise either halve or double eps and do another iteration
    eps=pow(2,a)*eps;
  }
  if(success==0) {
    cerr << "Did not find reasonable initial step size after 50 iterations -- " <<
      "is something wrong with model?" << endl;
    ad_exit(1);
  }
  return(eps);
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
