
void build_tree(
  double* theta,
  double* r,
  double* grad,
  double logu,
  int v,
  int j,
  double epsilon,
  double joint0
)
{
  if (j == 0)
  {
    //% Base case: Take a single leapfrog step in the direction v.
    //[thetaprime, rprime, gradprime, logpprime] = leapfrog(theta, r, grad, v*epsilon, f);
    leapfrog(theta, r, grad, v * epsilon);

    //joint = logpprime - 0.5 * (rprime * rprime');
    double joint = _logpprime;
    for (size_t d = 0; d < _D; ++d)
    {
      joint -= 0.5 * _rprime[d] * _rprime[d];
    }

    //% Is the new point in the slice?
    //nprime = logu < joint;
    _nprime = logu < joint;

    //% Is the simulation wildly inaccurate?
    //sprime = logu - 1000 < joint;
    _sprime = (logu - 1000) < joint;

    //% Set the return values---minus=plus for all things here, since the
    //% "tree" is of depth 0.
    for (int d = 0; d < _D; ++d)
    {
      //thetaminus = thetaprime;
      _thetaminus[d] = _thetaprime[d];

      //thetaplus = thetaprime;
      _thetaplus[d] = _thetaprime[d];

      //rminus = rprime;
      _rminus[d] = _rprime[d];

      //rplus = rprime;
      _rplus[d] = _rprime[d];

      //gradminus = gradprime;
      _gradminus[d] = _gradprime[d];

      //gradplus = gradprime;
      _gradplus[d] = _gradprime[d];
    }

    //% Compute the acceptance probability.
    //alphaprime = min(1, exp(logpprime - 0.5 * (rprime * rprime') - joint0));
    double v = std::exp(joint - joint0);
    _alphaprime = v < 1.0 ? v : 1.0;

    //nalphaprime = 1;
    _nalphaprime = 1;
  }
  else
  {
    //% Recursion: Implicitly build the height j-1 left and right subtrees.
    //[thetaminus, rminus, gradminus, thetaplus, rplus, gradplus, thetaprime, gradprime, logpprime, nprime, sprime, alphaprime, nalphaprime] = ...
    build_tree(theta, r, grad, logu, v, j - 1, epsilon, joint0);

    //% No need to keep going if the stopping criteria were met in the first
    //% subtree.
    if (_sprime == 1)
    {
      double thetaminus[2] = { _thetaminus[0], _thetaminus[1]};
      double rminus[2] = { _rminus[0], _rminus[1]};
      double gradminus[2] = { _gradminus[0], _gradminus[1]};
      double thetaplus[2] = { _thetaplus[0], _thetaplus[1]};
      double rplus[2] = { _rplus[0], _rplus[1]};
      double gradplus[2] = { _gradplus[0], _gradplus[1]};
      double thetaprime[2] = { _thetaprime[0], _thetaprime[1]};
      double gradprime[2] = { _gradprime[0], _gradprime[1]};
      double logpprime = _logpprime;
      int nprime = _nprime;
      bool sprime = _sprime;
      double alphaprime = _alphaprime;
      int nalphaprime = _nalphaprime;
      if (v == -1)
      {
        //[thetaminus, rminus, gradminus, ~, ~, ~, thetaprime2, gradprime2, logpprime2, nprime2, sprime2, alphaprime2, nalphaprime2] = ...
        build_tree(thetaminus, rminus, gradminus, logu, v, j - 1, epsilon, joint0);
        thetaminus[0] = _thetaminus[0];
        thetaminus[1] = _thetaminus[1];
        rminus[0] = _rminus[0];
        rminus[1] = _rminus[1];
        gradminus[0] = _gradminus[0];
        gradminus[1] = _gradminus[1];
      }
      else
      {
        //[~, ~, ~, thetaplus, rplus, gradplus, thetaprime2, gradprime2, logpprime2, nprime2, sprime2, alphaprime2, nalphaprime2] = ...
        build_tree(thetaplus, rplus, gradplus, logu, v, j - 1, epsilon, joint0);
        thetaplus[0] = _thetaplus[0];
        thetaplus[1] = _thetaplus[1];
        rplus[0] = _rplus[0];
        rplus[1] = _rplus[1];
        gradplus[0] = _gradplus[0];
        gradplus[1] = _gradplus[1];
      }//end
      double thetaprime2[2] = { _thetaprime[0], _thetaprime[1]};
      double gradprime2[2] = { _gradprime[0], _gradprime[1]};
      double logpprime2 = _logpprime;
      int nprime2 = _nprime;
      bool sprime2 = _sprime;
      double alphaprime2 = _alphaprime;
      int nalphaprime2 = _nalphaprime;

      //% Choose which subtree to propagate a sample up from.
      double random_number = _rand();
      if (nprime + nprime2 != 0 && random_number < double(nprime2) / double(nprime + nprime2))
      {
        for (int d = 0; d < _D; ++d)
        {
          //thetaprime = thetaprime2;
          _thetaprime[d] = thetaprime2[d];

          //gradprime = gradprime2;
          _gradprime[d] = gradprime2[d];
        }
        _logpprime = logpprime2;
      }
      else
      {
        for (int d = 0; d < _D; ++d)
        {
          //thetaprime = thetaprime;
          _thetaprime[d] = thetaprime[d];

          //gradprime = gradprime;
          _gradprime[d] = gradprime[d];
        }
        _logpprime = logpprime;
      }

      //% Update the number of valid points.
      //nprime = nprime + nprime2;
      _nprime = nprime + nprime2;

      //% Update the stopping criterion.
      _sprime = sprime && sprime2 && stop_criterion(thetaminus, thetaplus, rminus, rplus);

      //% Update the acceptance probability statistics.
      //alphaprime = alphaprime + alphaprime2;
      _alphaprime = alphaprime + alphaprime2;

      //nalphaprime = nalphaprime + nalphaprime2;
      _nalphaprime = nalphaprime + nalphaprime2;

      _thetaminus[0] = thetaminus[0];
      _thetaminus[1] = thetaminus[1];
      _rminus[0] = rminus[0];
      _rminus[1] = rminus[1];
      _gradminus[0] = gradminus[0];
      _gradminus[1] = gradminus[1];

      _thetaplus[0] = thetaplus[0];
      _thetaplus[1] = thetaplus[1];
      _rplus[0] = rplus[0];
      _rplus[1] = rplus[1];
      _gradplus[0] = gradplus[0];
      _gradplus[1] = gradplus[1];
    }//end
  }
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
