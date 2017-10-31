// Added these from Johnoel's code for the RNG below. Hopefully play nice
// with everything else
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <random>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
//#include "nuts_da.h"

using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::istringstream;
using std::pow;
using std::stack;
using std::queue;

#include "admodel.h"
#ifndef OPT_LIB
#include <cassert>
#endif
#include<ctime>


int function_minimizer::compute_next_window(int i, int anw, int warmup, int w1, int aws, int w3){
  anw = i+aws;
  if(anw == (warmup-w3) )
    return(anw);
  // Check that the next anw is not too long. This will be the anw for the
  // next time this is computed.
  int nwb = anw+2*aws;
  if(nwb >= warmup-w3){
    // if(i != warmup-w3){
    // cout << "Extending last slow window from" <<
    // anw << "to" << warmup-w3 << endl;
    // }
    anw = warmup-w3;
  }
  return(anw);
}


bool function_minimizer::slow_phase(int i, int warmup, int w1, int w3)
{
  // After w1, before start of w3
  bool x1 = i>= w1; // after initial fast window
  bool x2 = i<= (warmup-w3); // but before last fast window
  bool x3 = i < warmup; // definitely not during sampling
  return(x1 & x2 & x3);
}

double function_minimizer::exprnd(double p)
{
  // Johnoel sent me this to use
  std::random_device rd;
  std::mt19937 gen(rd());
  // if particles decay once per second on average,
  // how much time, in seconds, until the next one?
  std::exponential_distribution<> d(p);
  return d(gen);
}

// Strip out the model name given full path
std::string function_minimizer::get_filename(const char* f) {
  std::string s(f);
  size_t pos = s.find_last_of("/\\");
  std::string filename_exe = s.substr(pos + 1);
  size_t dot_pos = s.find_last_of(".");
  std::string filename = s.substr(pos + 1, dot_pos - pos - 1);
  return filename;
}

// This function is the heart of NUTS. It builds a single trajectory whose
// length depends on input j. It keeps doubling in  direction v until
// finished or a U-turn occurs.
void function_minimizer::build_tree(int nvar, dvector& gr, dmatrix& chd, double eps, dvector& p,
				    dvector& y, dvector& gr2, double logu, int v, int j, double H0,
				    dvector& _thetaprime, dvector& _thetaplus, dvector& _thetaminus,
				    dvector& _rplus, dvector& _rminus,
				    double& _alphaprime, int& _nalphaprime, bool& _sprime,
				    int& _nprime, int& _nfevals, bool& _divergent,
				    const random_number_generator& rng) {

  if (j==0) {
    // Take a single step in direction v from points p,y, which are updated
    // internally by reference and thus represent the new point.
    double nll= leapfrog(nvar, gr, chd, eps*v, p, y, gr2);
    // The new Hamiltonian value. ADMB returns negative log density so
    // correct it
    double Ham=-(nll+0.5*norm2(p));

    // Check for divergence. Either numerical (nll is nan) or a big
    // difference in H. Screws up all the calculations so catch it here.
    _divergent = (std::isnan(Ham) || logu > 1000+Ham);
    if(_divergent){
      _sprime=0;
      _alphaprime=0; // these will be NaN otherwise
      _nprime=0;
    } else {
      // No divergence
      _nprime = logu < Ham;
      _sprime=1;
      _alphaprime = min(1.0, exp(Ham-H0));
      // Update the tree elements, which are returned by reference in
      // leapfrog.
      _thetaprime = y;
      _thetaminus = y;
      _rminus = p;
      _thetaplus = y;
      _rplus = p;
    }
    _nalphaprime=1;
    _nfevals++;
  } else { // j > 1
    // Build first half of tree.
    build_tree(nvar, gr, chd, eps, p, y, gr2, logu, v, j-1,
	       H0, _thetaprime,  _thetaplus, _thetaminus, _rplus, _rminus,
	       _alphaprime, _nalphaprime, _sprime,
	       _nprime, _nfevals, _divergent, rng);
    // If valid trajectory, build second half.
    if (_sprime == 1) {
      // Save copies of the global ones due to rerunning build_tree below
      // which will overwrite some of the global variables we need to
      // save. These are the ' versions of the paper, e.g., sprime'.
      dvector thetaprime0(1,nvar);
      dvector thetaplus0(1,nvar);
      dvector thetaminus0(1,nvar);
      dvector rplus0(1,nvar);
      dvector rminus0(1,nvar);
      thetaprime0=_thetaprime;
      thetaplus0=_thetaplus;
      thetaminus0=_thetaminus;
      rplus0=_rplus;
      rminus0=_rminus;
      int nprime0 = _nprime;
      double alphaprime0 = _alphaprime;
      int nalphaprime0 = _nalphaprime;

      // Make subtree to the left
      if (v == -1) {
	build_tree(nvar, gr, chd, eps, _rminus, _thetaminus, gr2, logu, v, j-1,
		   H0, _thetaprime,  _thetaplus, _thetaminus, _rplus, _rminus,
		   _alphaprime, _nalphaprime, _sprime,
		   _nprime, _nfevals, _divergent, rng);
	// Update the leftmost point
	rminus0=_rminus;
	thetaminus0=_thetaminus;
	// Rest rightmost tree
	_thetaplus=thetaplus0;
	_rplus=rplus0;
      } else {
	// Make subtree to the right
	build_tree(nvar, gr, chd, eps, _rplus, _thetaplus, gr2, logu, v, j-1,
		   H0, _thetaprime,  _thetaplus, _thetaminus, _rplus, _rminus,
		   _alphaprime, _nalphaprime, _sprime,
		   _nprime, _nfevals, _divergent, rng);
	// Update the rightmost point
	rplus0=_rplus;
	thetaplus0=_thetaplus;
	// Reset leftmost tree
	_thetaminus=thetaminus0;
	_rminus=rminus0;
      }

      // This is (n'+n''). Can be zero so need to be careful??
      int nprime_temp = nprime0 + _nprime;
      if(std::isnan(nprime_temp)) nprime_temp=0;
      // Choose whether to keep the proposal thetaprime.
      double rr=randu(rng); // runif(1)
      if (nprime_temp != 0 && rr < double(_nprime)/double(nprime_temp)) {
	// Update theta prime to be the new proposal for this tree so far.
	// _thetaprime already updated globally above so do nothing
      } else {
	// Reject it for the proposal from the last doubling.
	_thetaprime = thetaprime0;
      }

      // Update the global reference variables
      _alphaprime = alphaprime0 + _alphaprime;
      _nalphaprime = nalphaprime0 + _nalphaprime;
      // s' from the first execution above is 1 by definition (inside this
      // if statement), while _sprime is s''. So need to reset s':
      bool b = stop_criterion(nvar, thetaminus0, thetaplus0, rminus0, rplus0);
      _sprime = _sprime*b;
      _nprime = nprime_temp;
    } // end building second trajectory
  }   // end recursion branch (j>0)
}     // end function


bool function_minimizer::stop_criterion(int nvar, dvector& thetaminus, dvector& thetaplus,
					dvector& rminus, dvector& rplus)
{
  dvector thetavec(1, nvar);
  thetavec=thetaplus-thetaminus;
  // Manual implementation of inner_product, equivalent to this
  // criterion = (thetavec*rminus+thetavec*rminus>=0) *
  // 			      (thetavec*rplus+thetavec*rplus>=0);
  double x1=0;
  double x2=0;
  for(int i=1; i<=nvar; i++){
    x1+=thetavec(i)*rminus(i);
    x2+=thetavec(i)*rplus(i);
  }
  // TRUE if both are TRUE, FALSE if at least one.
  bool criterion = (x1 >=0) * (x2 >=0);
  return criterion;
}


double function_minimizer::adapt_eps(int ii, double eps, double alpha,
				     double& adapt_delta, double& mu,
				     dvector& epsvec, dvector& epsbar,
				     dvector& Hbar){
  double gamma=0.05;  double t0=10;  double kappa=0.75;
  int m=ii+1;
  // If divergence, there is 0 acceptance probability so alpha=0.
  if(std::isnan(alpha)) alpha=0;
  Hbar(m)= (1-1/(m+t0))*Hbar(m-1) + (adapt_delta-alpha)/(m+t0);
  double logeps=mu-sqrt(m)*Hbar(m)/gamma;
  epsvec(m)=exp(logeps);
  double logepsbar= pow(m, -kappa)*logeps+(1-pow(m,-kappa))*log(epsbar(m-1));
  epsbar(m)=exp(logepsbar);
  return(epsvec(m));
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

void function_minimizer::print_mcmc_progress(int is, int nmcmc, int nwarmup, int chain)
{
  // Modified from Stan: sample::progress.hpp; 9/9/2016
  int refresh = (int)floor(nmcmc/10);
  if (is==1 || is == nmcmc || is % refresh ==0 ){
    int width=1+(int)std::ceil(std::log10(static_cast<double>(nmcmc)));
    cout << "Chain " << chain << ", " << "Iteration: " << std::setw(width) << is
	 << " / " << nmcmc << " [" << std::setw(3)
	 << int(100.0 * (double(is) / double(nmcmc) ))
	 << "%] " << (is <= nwarmup ? " (Warmup)" : " (Sampling)") << endl;
  }
}

void function_minimizer::print_mcmc_timing(double time_warmup, double start) {
  double time_total = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
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

// This function holds the position (y) and momentum (p) vectors fixed and
// takes a single step of size eps. This process repeats until a reasonable
// eps is found. Thus need to make sure y and p are constant and only eps
// changes.
double function_minimizer::find_reasonable_stepsize(int nvar, dvector y, dvector p, dmatrix& chd)
{

  double eps=1;			   // initial eps
  independent_variables z(1,nvar); // rotated bounded parameters
  dvector p2(1,nvar);		// updated momentum
  dvector y2(1,nvar);		// updated position
  dvector gr(1,nvar);		   // gradients
  dvector gr2(1,nvar);		// updated rotated gradient

  // Calculate initial Hamiltonian value
  double pprob1=0.5*norm2(p);
  z=chd*y;
  double nllbegin=get_hybrid_monte_carlo_value(nvar,z,gr);
  dvector gr2begin=gr*chd; // rotated gradient
  double H1=nllbegin+pprob1;

  // Calculate H after a single step of size eps
  double nll2=leapfrog(nvar, gr, chd, eps, p2, y2, gr2);
  double pprob2=0.5*norm2(p2);
  double H2=nll2+pprob2;
  double alpha=exp(H1-H2);
  // Determine whether eps=1 is too big or too small, i.e. whether to halve
  // or double. If a=1, then eps keeps doubling until alpha passes 0.5;
  // otherwise it halves until that happens.
  double a;
  if(alpha < 0.5 || std::isnan(alpha)){
    // If divergence occurs or eps too big, halve it
    a=-1;
  } else {
    // If stepsize too small, double it
    a=1;
  }

  for(int k=2; k<50; k++){
    // Reinitialize position and momentum at each step.
    p2=p;
    y2=y;
    gr2=gr2begin;

    // Make one leapfrog step and check acceptance ratio
    nll2=leapfrog(nvar, gr, chd, eps, p2, y2, gr2);
    pprob2=0.5*norm2(p2);
    H2=nll2+pprob2;
    alpha=exp(H1-H2);

    // Check if the 1/2 threshold has been crossed
    if(pow(alpha,a) < pow(2,-a)){
      cout << "Found reasonable step size of " << eps << " after "
	   << k << " steps." << endl;
      return(eps);
    } else {
      // Otherwise either halve or double eps and do another iteration
      eps=pow(2,a)*eps;
    }
  }
  cerr << "Did not find reasonable initial step size after 50 iterations -- " <<
    "is something wrong with model?" << endl;
  ad_exit(1);
  return(eps); // dummy to avoid compile warnings
} // end of function


/**
   Function to take a single HMC leapfrog step, given current position and
   momentum variables. Returns nll value but also updates position and
   momentum variables by reference.
 **/
double function_minimizer::leapfrog(int nvar, dvector& gr, dmatrix& chd, double eps, dvector& p, dvector& y,
				    dvector& gr2)
{
  independent_variables z(1,nvar); // bounded parameters
  dvector phalf;
  // Update momentum by half step
  phalf=p-eps/2*gr2;
  // Update parameters by full step
  y+=eps*phalf;
  // Transform parameters via mass matrix to get new gradient
  z=chd*y;
  // Get NLL and set updated gradient in gr by reference
  double nll=get_hybrid_monte_carlo_value(nvar,z,gr);
  // Update gradient via mass matrix
  gr2=gr*chd;
  // Last half step for momentum
  p=phalf-eps/2*gr2;
  return(nll);
}

// This function reads in the hessian file to get the MLE values at the
// end. This is needed when the user doesn't pass an initial vector with
// -mcpin b/c the model is not necessarily run with -est. With adnuts it is
// not by default so need a default starting value.
void function_minimizer::read_mle_hmc(int nvar, dvector& mle) {
  adstring tmpstring = "admodel.hes";
  uistream cif((char*)tmpstring);
  if (!cif) {
    cerr << "Error reading the bounded MLE values from admodel.hes which are needed "
	 << endl <<  "to rescale the mass matrix. Try re-optimizing model." << endl;
    ad_exit(1);
  }
  int tmp_nvar = 0;
  cif >> tmp_nvar;
  if (nvar !=tmp_nvar) {
    cerr << "Error reading the bounded MLE values from admodel.hes which are needed "
	 << endl <<  "to rescale the mass matrix. Try re-optimizing model." << endl;
    ad_exit(1);
  }
  dmatrix hess(1,tmp_nvar,1,tmp_nvar);
  cif >> hess;
  if (!cif) {
    cerr << "Error reading the bounded MLE values from admodel.hes which are needed "
	 << endl <<  "to rescale the mass matrix. Try re-optimizing model." << endl;
    ad_exit(1);
  }
  int oldHbf;
  cif >> oldHbf;
  if (!cif) {
    cerr << "Error reading the bounded MLE values from admodel.hes which are needed "
	 << endl <<  "to rescale the mass matrix. Try re-optimizing model." << endl;
    ad_exit(1);
  }
  dvector sscale(1,tmp_nvar);
  cif >> sscale;
  if (!cif) {
    cerr << "Error reading the bounded MLE values from admodel.hes which are needed "
	 << endl <<  "to rescale the mass matrix. Try re-optimizing model." << endl;
    ad_exit(1);
  }
  // Read in the MLEs finally
  int temp=0;
  cif >> temp;
  cif >> mle;
  // Temp is a unique flag to make sure the mle values were written (that
  // admodel.hes is not too old)
  if(temp != -987 || !cif){
    cerr << "Error reading the bounded MLE values from admodel.hes. Try re-optimizing model." << endl;
    ad_exit(1);
  }
}

// Function written by Dave to help speed up some of the MCMC
// calculations. The code has chd*x which rotates the space but this is
// often a vector or at least a lower triangular matrix. Thus we can make
// it more efficient
dvector function_minimizer::rotate_space(const dmatrix& m, const dvector& x)
  {
     if (x.indexmin() != m.colmin() || x.indexmax() != m.colmax())
     {
       cerr << " Incompatible array bounds in "
       "dvector rotate_space(const dmaxtrix& m, const dvector& x)\n";
       ad_exit(21);
     }
  
     dvector tmp(m.rowmin(),m.rowmax());
     int mmin=m.rowmin();
     int mmax=m.rowmax();
     int xmin=x.indexmin();
     int xmax=x.indexmax();
  
     for (int i=mmin; i<=mmax; i++)
     {
       tmp[i]=0;
       double * pm= (double *) &(m(i,xmin));
       double * px= (double *) &(x(xmin));
       double tt=0.0;
       for (int j=xmin; j<=i; j++)
       {
         tt+= *pm++ * *px++;
       }
       tmp[i]=tt;
     }
     return(tmp);
  }

dvector function_minimizer::rotate_space(const dvector& m, const dvector& x)
  {
     if (x.indexmin() != m.indexmin() || x.indexmax() != m.indexmax())
     {
       cerr << " Incompatible array bounds in "
       "dvector  rotate_space(const dvector& m, const dvector& x)\n";
       ad_exit(21);
     }
  
     dvector tmp(x.indexmin(),x.indexmax());
     tmp=x * m;
     return(tmp);
  }
