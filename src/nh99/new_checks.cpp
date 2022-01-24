
#include "admodel.h"
#include<ctime>

/**
  Experimental feature to take Newton steps using the inverse
  Hessian to get much closer to the optimum and reduce the
  maximum gradient arbitrarily close to 0.

  Let x be the current MLE parameter vector. Then a single step
  consists of calculating x'=x-inv(Hessian)*gradient. This
  calculation is done in the unbounded parameter space.

  This feature is initiated by calling "-hess_step N
  -hess_step_tol eps" to specify the maximum number of steps (N)
  and a minimum threshold for the maximum gradient (eps), below
  which is deemed sufficient and causes the function to exit
  early with success. The defaults are N=1 and eps=1e-12. The
  function will also exit early if the gradients get worse as a
  result of a step, printing information about which
  parameters. If successful, the new MLE is deemed improved and
  is propagated through the model to update all output files.

  The upside of this feature is it confirms that the geometry
  near the mode is quadratic and well represented by the
  Hessian. It may also slightly improve the MLE and uncertainty
  estimates. The downside is that the Hessian needs to be
  recalculated and inverted at each step so it is costly
  computationally.

  Typical usage is to optimize model, then use this feature if
  convergence is suspect.

  \author Cole Monnahan
*/
void function_minimizer::hess_step(){
  // Read in the number of steps and optional tolerance
  int N_hess_steps=1;
  int _N_hess_steps;
  int on, nopt;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hess_step",nopt))>-1) {
    if (!nopt){ 
      cout << "Number of hess_steps not specified, using default of 1" << endl;
    } else {			
      istringstream ist(ad_comm::argv[on+1]);
      ist >> _N_hess_steps;
      if (_N_hess_steps<=0) {
	cerr << "Error: hess_step tolerance must be positive";
	ad_exit(1);
      } else {
	N_hess_steps=_N_hess_steps;
      }
    }
  }
  double eps=1e-12;
  double _eps;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hess_step_tol",nopt))>-1) {
    if (!nopt){ 
      cout << "No tolerance given, using default of 1e-12" << endl;
    } else {			
      istringstream ist(ad_comm::argv[on+1]);
      ist >> _eps;
      if (_eps<=0) {
	cerr << "Error: hess_step tolerance must be positive";
	ad_exit(1);
      } else {
	eps=_eps;
      }
    }
  }
  cout << "Experimental feature to take up to " << N_hess_steps;
  cout << " Newton step(s) using the inverse Hessian" << endl;
  // Let x'=x-inv(Hessian)*gradient, where x is MLE in
  // unbounded space and it's corresponding gradient and
  // Hessian. Need to calculate x' then push through
  // model and calculate SD report stuff
  initial_params::current_phase=initial_params::max_number_phases;
  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  independent_variables mle(1,nvar); // original bounded MLE
  independent_variables mle2(1,nvar); // updated bounded MLE
  independent_variables x(1,nvar); // original unbounded MLE
  independent_variables x2(1,nvar); // updated unbounded MLE
  dvector gr0(1,nvar);		// original gradients
  dvector gr(1,nvar);		// 
  dvector gr2(1,nvar);		// updated gradients
  double maxgrad0, mingrad0, maxgrad, maxgrad2, mingrad2;
  read_mle_hmc(nvar, mle); // takes MLE from admodel.hes file

  // Push the original bounded MLE through the model
  initial_params::restore_all_values(mle,1);
  gradient_structure::set_YES_DERIVATIVES(); // don't know what this does
  // This copies the unbounded parameters into x
  initial_params::xinit(x);
  dvar_vector vx=dvar_vector(x);
  initial_params::reset(vx);
  *objective_function_value::pobjfun=0.0;
  userfunction();
  gradcalc(nvar,gr0);			      // initial unbounded gradient
  maxgrad0=max(fabs(gr0));
  mingrad0=min(fabs(gr0));
	  
  cout << "Initial max gradient=" << maxgrad0 << " and min gradient= " << mingrad0 << endl;
  dmatrix S(1,nvar,1,nvar); // covar (inverse Hess) in unbounded space
  dvector scale(1,nvar); // dummy var
  int hbf; // dummy var

  // Initial for first iteration
  gr=gr0; maxgrad=maxgrad0; 

  int Nstep=0;
  for(int ii=1; ii<=N_hess_steps; ii++){
    Nstep++;
    // Get the covar matrix from file, assuming last run was good
    read_covariance_matrix(S,nvar, hbf, scale);
    x2=x-S*gr; // the updated MLE in unbounded space
    // Push the new unbounded MLE through the model
    dvar_vector vx2=dvar_vector(x2);
    initial_params::reset(vx2);
    *objective_function_value::pobjfun=0.0;
    userfunction();
    // Updated quantities after taking step
    gradcalc(nvar,gr2);
    maxgrad2=max(fabs(gr2));
    mingrad2=min(fabs(gr2));
    initial_params::copy_all_values(mle2,1.0);
    // Check whether to break out of loop early
    if( (maxgrad2 < eps) & (ii < N_hess_steps)){
      cout << "Step " << ii << ": Max gradient "<< maxgrad2 <<
	" below threshold of " << eps << " so exiting early" << endl;
      break;
    } else if(maxgrad2>maxgrad) {
      // which ones got worse?
      int jj = 1;
      for (int i = 0; i < initial_params::num_initial_params; ++i) {
        if (active(*initial_params::varsptr[i])) {
          int jmax = (int)initial_params::varsptr[i]->size_count();
          for (int j = 1; j <= jmax; ++j) {
            if(abs(gr(jj)) < abs(gr2(jj))){
              cout << (initial_params::varsptr[i])->label();
              if (jmax > 1) {
                cout << "(" << j << ")";
              }
              cout << ": original grad=" << gr(jj) << " and updated grad=" << gr2(jj) << endl;
            }
	    ++jj;
          }
        }
      }
      cerr << endl <<
	"Experimental feature -hess_step resulted in worse gradients (above)." << endl <<  
	"Consider reoptimizing model to reset files. This suggests that the" << endl <<
	"the negative log-likelihood is not quadratic at the mode, or that the" << endl <<
	"Hessian does not approximate it well. In short, it suggests the model is" << endl <<
	"not converged. Check model structure and other output files to investigate" << endl <<
	"potential causes and solutions." << endl;
      ad_exit(1);
    } else {
      // Was successful but not good enough to break early
      cout << "Step " << ii << ": Updated max gradient=" << maxgrad2 <<
	" and min gradient= " << mingrad2 << endl; 
      x=x2; gr=gr2; maxgrad=maxgrad2; 
      // If not the last step then want to skip the sd_calcs
      // which are slow so manually update admodel.cov whereas
      // below computations1() runs everything so do that if last
      // step
      if(ii!=N_hess_steps){
	hess_routine(); // Calculate new Hessian
	depvars_routine(); // calculate derivatives of sdreport variables
	hess_inv(); // Invert Hess and write to admodel.cov
      }
    } 
  }// end loop over hess_steps
  // Finished successfully so run the optimizer without
  // taking any steps to produce updated output files
  // with this new MLE value.
  function_minimizer::maxfn=0;
  computations1(ad_comm::argc,ad_comm::argv);
  cout << endl << "The " << Nstep << " Hessian step(s) reduced maxgrad from " <<
    maxgrad0 << " to " << maxgrad2 << "." << endl <<
    "All output files should be updated, but confirm as this is experimental still." << endl <<
    "The fact this was successful gives strong evidence of convergence to a mode" << endl <<
    "with quadratic log-likelihood surface." << endl;
}

// Quick experimental function to test whether MLE parameters are
// on or near a bound and print to console. To be executed only
// after optimization when the hessian has been calculated, 
// not things like mceval, profiles, MCMC etc.
//
// NOTE: bounds checking is not done here on random effects, only fixed effects parameters.
void function_minimizer::check_parameters_on_bounds(){
  //if (function_minimizer::random_effects_flag) {return;}//does not work for models with random effects
  bool tmp=false;
  
  std::ofstream os("parameters_on_bounds_after_hessian.txt", std::ofstream::out|std::ofstream::trunc);

  cout << endl << "Checking for parameters on bounds (experimental; hbf=" << gradient_structure::Hybrid_bounded_flag << ")..." << endl;
  cout << "    NOTE: bounds checking is not done here on random effects, only fixed effects parameters." << endl;
  os   << "Checking for parameters on bounds (experimental; hbf=" << gradient_structure::Hybrid_bounded_flag << ")..." << endl;
  os   << "    NOTE: bounds checking is not done here on random effects, only fixed effects parameters." << endl;
  // Don't technically need this but I don't know how to consistently get the MLE 
  // without reading it here (it may not be the last par vec executed)
  // NOTE: random effects are not included in the MLE written to admodel.hes (see mod_rhes.cpp)
  adstring tmpstring = "admodel.hes";
  uistream cif((char*)tmpstring);
  if (!cif) {
    cerr << "  File admodel.hes required for bound checking but not found... skipping." << endl;
  } else {
    // Experiment to test for parameters near bounds
    initial_params::set_inactive_only_random_effects();
    int nvar=initial_params::nvarcalc(); // get the number of active parameters
    independent_variables bounded(1,nvar); // original bounded MLE
    independent_variables unbounded(1,nvar); // original unbounded MLE
    adstring_array pars=initial_params::get_param_names();
    cout<<"nvar = "<<nvar<<".  # params = "<<pars.size()<<endl;
    // takes MLE from admodel.hes file. It would be better to
    // get this another way in case the model can't write it
    // for some reason (like if on a bound?). I'm not sure
    // where else to get it
    // NOTE: random effects are not included in the MLE written to admodel.hes (see mod_rhes.cpp)
    read_mle_hmc(nvar, bounded); 
    //cout<<"1"<<endl;
//    cout<<"bounded parameter values = "<<endl;
//    for (int i=1;i<=nvar;i++){
//        cout<<pars[i]<<" = "<<bounded[i]<<endl;
//    }
    initial_params::restore_all_values(bounded,1);  // Push the original bounded MLE through the model
//    //cout<<"2"<<endl;
//    gradient_structure::set_YES_DERIVATIVES(); // don't know what this does
//    //cout<<"3"<<endl;
//    initial_params::xinit(unbounded); // This copies the unbounded parameters into x
//    //cout<<"4"<<endl;
//    dvar_vector vx=dvar_vector(bounded);
//    initial_params::reset(vx);
    initial_params::check_for_params_on_bounds(std::cout);
    initial_params::check_for_params_on_bounds(os);
    os.close();
//    for(int i=1; i<=nvar; i++){
//      // dangerous way to check for bounded is if unbounded=bounded??
//      //  cout<<"checking parameter i = "<<i<<" (i.e., "<<pars[i]<<")"<<endl;
//      if(unbounded(i)!=bounded(i)){
//	tmp=true;
//	// These values depend on the bounding
//	// function. Here "close" is defined on the (0,1)
//	// bounded scale as 0.001 or 0.999, and "on" is
//	// 0.00001 or 0.9999. See boundpin function.
//	if(gradient_structure::Hybrid_bounded_flag==0){
//	  if(unbounded(i)> .9959737)
//	    cout << "  '"<<pars[i]<<"'" << " appears to be on upper bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	  else if(unbounded(i) < -.9959737)
//	    cout << "  '"<<pars[i]<<"'" << " appears to be on lower bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	  else if(unbounded(i) > .9597299) 
//	    cout << "  '"<<pars[i]<<"'" << " appears to be near upper bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	  else if(unbounded(i)< -.9597299)
//	    cout << "  '"<<pars[i]<<"'" << " appears to be near lower bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	}
//	if(gradient_structure::Hybrid_bounded_flag==1){
//	  if(unbounded(i)< -11.51292)
//	    cout << "  '"<<pars[i]<<"'" << " appears to be on lower bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	  else if(unbounded(i)> 11.51292)
//	    cout << "  '"<<pars[i]<<"'" << " appears to be on upper bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	  else if(unbounded(i)< -6.906755)
//	    cout << "  '"<<pars[i]<<"'" << " appears to be near lower bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	  else if(unbounded(i)> 6.906755)
//	    cout << "  '"<<pars[i]<<"'" << " appears to be near upper bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	}
//
//	// same thing but write to log file
//	if(gradient_structure::Hybrid_bounded_flag==0){
//	  if(unbounded(i)> .9959737)
//	    *ad_comm::global_logfile << "  '"<<pars[i]<<"'" << " appears to be on upper bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	  else if(unbounded(i) < -.9959737)
//	    *ad_comm::global_logfile << "  '"<<pars[i]<<"'" << " appears to be on lower bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	  else if(unbounded(i) > .9597299) 
//	    *ad_comm::global_logfile << "  '"<<pars[i]<<"'" << " appears to be near upper bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	  else if(unbounded(i)< -.9597299)
//	    *ad_comm::global_logfile << "  '"<<pars[i]<<"'" << " appears to be near lower bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	}
//	if(gradient_structure::Hybrid_bounded_flag==1){
//	  if(unbounded(i)< -11.51292)
//	    *ad_comm::global_logfile << "  '"<<pars[i]<<"'" << " appears to be on lower bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	  else if(unbounded(i)> 11.51292)
//	    *ad_comm::global_logfile << "  '"<<pars[i]<<"'" << " appears to be on upper bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	  else if(unbounded(i)< -6.906755)
//	    *ad_comm::global_logfile << "  '"<<pars[i]<<"'" << " appears to be near lower bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	  else if(unbounded(i)> 6.906755)
//	    *ad_comm::global_logfile << "  '"<<pars[i]<<"'" << " appears to be near upper bound: " <<  bounded(i) << " (unbounded=" << unbounded(i) << ")" << endl;
//	}
//      }
//    }//-i loop
  } // if (admodel.hes exists)
  // close out
//  if(!tmp) {
//    cout <<" done checking fixed effects parameter bounds!" << endl;
//    *ad_comm::global_logfile << " done checking fixed effects parameter bounds!" << endl;
//  } else {
//    *ad_comm::global_logfile << endl;
//  }
}
