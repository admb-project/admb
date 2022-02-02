
#include "admodel.h"
#include<ctime>

/**
  Feature to try and get closer to the optimal point
  (minimum) using Newton steps with the inverse Hessian. If
  successful it gives evidence that the mode has been reached and
  the nearby curvature is well approximated by a quadratic form. 

  Let x be the current MLE parameter vector. Then a single step
  consists of calculating x'=x-inv(Hessian)*gradient. This
  calculation is done in the unbounded parameter space.

  This feature is initiated by calling "-hess_step N
  -hess_step_tol eps" to specify the maximum number of steps (N)
  and a minimum threshold (eps) for the maximum absolute gradient
  ('maxgrad'), below which is deemed sufficient and causes the function
  to exit early with success. The defaults are N=5 and
  eps=1e-12. The function will continue even if the maxgrad gets
  bigger because often sucessive steps improve the Hessian and
  can finish successfully. If successful, the new MLE is deemed
  improved and is propagated through the model to update all
  output files.

  The upside of this feature is it confirms that the geometry
  near the mode is quadratic and well represented by the
  Hessian. It may also slightly improve the MLE and uncertainty
  estimates. The downside is that the Hessian needs to be
  recalculated and inverted at each step so it is costly
  computationally.

  One technical issue is that because this is run after
  optimization, the model initialization needs to be
  considered. If there are inactive parameters in some cases they
  may not be intialized to what is in the template. A workaround
  is to specify initial values via the -ainp or -binp arguments,
  as is standard. Future versions should explore how to automate
  this, or only warn the user when there are inactive parameters.

  Typical usage is to optimize model, then use this feature if
  convergence is suspect. If it reduces the maxgrad to zero this
  gives strong evidence for convergence.

  \author Cole Monnahan
*/
void function_minimizer::hess_step(){
  // Read in the number of steps and optional tolerance
  int N_hess_steps=5;
  int _N_hess_steps;
  int on, nopt;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hess_step",nopt))>-1) {
    if (!nopt){ 
      //cout << "Number of hess_steps not specified, using default of 1" << endl;
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
  cout <<  endl << "Experimental feature to take up to " << N_hess_steps;
  cout << " Newton step(s) using the inverse Hessian" << endl << endl;

  initial_params::current_phase=initial_params::max_number_phases;
  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  int aiopt,biopt;
  biopt=option_match(ad_comm::argc,ad_comm::argv,"-binp");
  aiopt=option_match(ad_comm::argc,ad_comm::argv,"-ainp");
  if(biopt==-1 && aiopt==-1){
    std::string m=get_filename((char*)ad_comm::adprogram_name);
    cout << "Warning: Parameter inputs via '-ainp' and '-binp' were not detected." << endl;
    cout << "         It is recommended to add option '-binp " << m << ".bar' when using -hess_step." << endl;
    cout << "         Otherwise inactive parameters (and thus gradients) may not initialize correctly." << endl << endl;
  }
    
  // Let x'=x-inv(Hessian)*gradient, where x is MLE in
  // unbounded space and it's corresponding gradient and
  // Hessian. Need to calculate x' then push through
  // model and calculate SD report stuff
  independent_variables mle(1,nvar); // original bounded MLE
  independent_variables mle2(1,nvar); // updated bounded MLE
  independent_variables x(1,nvar); // original unbounded MLE
  independent_variables x2(1,nvar); // updated unbounded MLE
  dvector gr0(1,nvar);		// original gradients
  dvector gr(1,nvar);		// 
  dvector gr2(1,nvar);		// updated gradients
  dvariable nll,nll2;		// minimal values
  double maxgrad0, mingrad0,maxgrad, maxgrad2, mingrad2;
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
  nll=*objective_function_value::pobjfun;
  adstring_array pars(1,nvar);
  pars=initial_params::get_param_names();

  int maxpar=1;
  dvariable grMax=fabs(gr0[1]);
  for (int i = 1; i<=nvar; i++){
    if (fabs(gr0[i]) > grMax){
      grMax = fabs(gr0[i]);
      maxpar=i;
    }
  }
  
  if(maxgrad0<eps) {
    cout << "Initial max gradient already below threshold of " << eps << " so quitting now" << endl;
    return;
  }

  cout << "Hess step 0: Max gradient=" << maxgrad0 << " (" << pars[maxpar] << ") and min gradient= " << mingrad0 << endl;
  // for(int i=1; i<=5; i++) {cout << "i=" << i << " varsptr=" << 1 << " mle=" << mle(i) << " gradient=" << gr0(i) << endl;}
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
    nll2=*objective_function_value::pobjfun;
    // Updated quantities after taking step
    gradcalc(nvar,gr2);
    maxgrad2=max(fabs(gr2));
    mingrad2=min(fabs(gr2));
    // stupid way to do which.max()
    maxpar=1; grMax=fabs(gr2[1]);
    for (int i = 1; i<=nvar; i++){
      if (fabs(gr2[i]) > grMax){
	grMax = fabs(gr2[i]);
	maxpar=i;
      }
    }
    if(grMax!=maxgrad2) cerr << "Warning: which parameter has largest gradient may be unreliable" << endl;

    initial_params::copy_all_values(mle2,1.0);
    // Check whether to break out of loop early
    if(maxgrad2 < eps){
      cout << "Hess step " << ii << ": Max gradient="<< maxgrad2 << " (" << pars[maxpar] <<
	") is below threshold of " << eps << " so exiting early" << endl;
      break;
    }
    // Was successful but not good enough to break early
    cout << "Hess step " << ii << ": Max gradient=" << maxgrad2 << " (" << pars[maxpar] <<
      ") and min gradient= " << mingrad2 << endl; 
    x=x2; gr=gr2; maxgrad=maxgrad2; 
    // If not the last step then want to skip the sd_calcs
    // which are slow so manually update admodel.cov whereas
    // below computations1() runs everything so do that if last
    // step
    if(ii!=N_hess_steps){
      int oldoutput = function_minimizer::output_flag;
      function_minimizer::output_flag=0;
      cout << "             Updating Hessian for next step (output suppressed)...";
      hess_routine(); // Calculate new Hessian
      depvars_routine(); // calculate derivatives of sdreport variables
      hess_inv(); // Invert Hess and write to admodel.cov
      function_minimizer::output_flag=oldoutput;
      cout << "done!" << endl;
    }
  } // end loop over hess_steps
  
  if(maxgrad2>maxgrad0){
    // worse gradient
    cerr << "Experimental feature -hess_step resulted in worse gradients." << endl <<  
      "Consider reoptimizing model to reset files. This suggests that the" << endl <<
      "the negative log-likelihood is not quadratic at the mode, or that the" << endl <<
      "Hessian does not approximate it well. In short, it suggests the model is" << endl <<
      "not converged. Check model structure and other output files to investigate" << endl <<
      "potential causes and solutions." << endl;
    ad_exit(1);
  } else {
    // Finished successully so run the opitmizer without
    // taking any steps to produce updated output files
    // with this new MLE value.
    function_minimizer::maxfn=0;
    cout << endl << "Redoing uncertainty calculations and updating files (output suppressed)...";
    int oldoutput = function_minimizer::output_flag;
    function_minimizer::output_flag=0;
    computations1(ad_comm::argc,ad_comm::argv);
    function_minimizer::output_flag=oldoutput;
    cout << " done!" << endl;
    cout << endl << "The " << Nstep << " Hessian step(s) reduced maxgrad from " <<
      maxgrad0 << " to " << maxgrad2 << " and NLL by " << nll-nll2 << "." << endl <<
      "All output files should be updated, but confirm as this is experimental still." << endl <<
      "The fact this was successful gives strong evidence of convergence to a mode" << endl <<
      "with quadratic log-likelihood surface." << endl;
  }
}

int initial_params::debug = 0;//flag to print debugging info

/**
 * Get names of active parameters
 */
adstring_array initial_params::get_param_names(void){
  //define and allocate adstring array
  int nvar=nvarcalc(); // get the number of active parameters
  if (debug) cout<<"--num initial params = "<<num_initial_params<<endl;
  if (debug) cout<<"--num active  params = "<<nvar<<endl;
  adstring_array par_names;
  if (nvar>0){
    par_names.allocate(1,nvar);

    //loop over parameters and vectors and create names  
    int kk = 0;
    for (int i = 0; i < num_initial_params; ++i) {
      if (withinbound(0,(varsptr[i])->phase_start,current_phase)) {
	int jmax = (varsptr[i])->size_count();
	for (int j = 1; j <= jmax; ++j) {
	  kk++;
	  par_names[kk] = (varsptr[i])->label();
	  if (jmax > 1) par_names[kk] += "["+str(j)+"]";//might have to do something similar to alternative above if this doesn't work
	}//--j loop
      }//--if
    }//--i loop
    if (nvar!=kk) cerr<<"Error in initial_params::get_param_names: number of parameters does not match"<<endl;
  } else {
    if (debug) cout<<"--initial_params::get_param_names(): Model appears to be autodiff only."<<endl;
    par_names.allocate();
  }
  return(par_names);
}
  
void initial_params::check_for_params_on_bounds(ostream& os){
  if (debug) os<<std::endl<<"Starting initial_params::check_parameters_on_bounds"<<std::endl;
  int nvar=nvarcalc(); // get the number of active parameters
  if (debug) os<<"--num initial params = "<<num_initial_params<<endl;
  if (debug) os<<"--num active  params = "<<nvar<<endl;
  if (nvar>0){
    //loop over parameters and vectors and create names  
    int kk = 0;
    for (int i = 0; i < num_initial_params; ++i) {
      adstring par_name_base = (varsptr[i])->label();
      if (withinbound(0,(varsptr[i])->phase_start,current_phase)) {        
	if ((varsptr[i])->has_bounds) {
	  if (debug) os<<"----"<<par_name_base<<" is active, bounded, and will be checked."<<endl;
	  int jmax = (varsptr[i])->size_count();
	  if (debug) os<<"   jmax = "<<jmax<<endl;
	  if (dynamic_cast<param_init_bounded_number*>(varsptr[i])!=nullptr){
	    if (debug) os<<"   "<<par_name_base<<" is a param_init_bounded_number."<<endl;
	    param_init_bounded_number* p = dynamic_cast<param_init_bounded_number*>(varsptr[i]);
	    double minb = p->get_minb();
	    double maxb = p->get_maxb();
	    double valp = ::value(*p);
	    adstring par_name = par_name_base;
	    if (debug) os<<"   "<<par_name<<": "<<minb<<" < "<<valp<<" < "<<maxb<<"?"<<endl;
	    if ((valp-minb)/(maxb-minb)<0.001) 
	      os<<"   "<<par_name<<" is near lower bound: "<<minb<<" < "<<valp<<" < "<<maxb<<endl;
	    if ((maxb-valp)/(maxb-minb)<0.001) 
	      os<<"   "<<par_name<<" is near upper bound: "<<minb<<" < "<<valp<<" < "<<maxb<<endl;
	  } else if (dynamic_cast<param_init_bounded_dev_vector*>(varsptr[i]) != nullptr) {
	    if (debug) os<<"   "<<par_name_base<<" is a param_init_bounded_dev_vector with "<<jmax<<" elements."<<endl;
	    param_init_bounded_vector* p = dynamic_cast<param_init_bounded_vector*>(varsptr[i]);//note: can cast to _vector here
	    double minb = p->get_minb();
	    double maxb = p->get_maxb();
	    for (int j=p->indexmin();j<=p->indexmax();j++){
	      double valp = ::value(p->elem(j));
	      adstring par_name = par_name_base+"["+str(j)+"]";
	      if (debug) os<<"   "<<par_name<<": "<<minb<<" < "<<valp<<" < "<<maxb<<"?"<<endl;
	      if ((valp-minb)/(maxb-minb)<0.001) 
		os<<"   "<<par_name<<" is near lower bound: "<<minb<<" < "<<valp<<" < "<<maxb<<endl;
	      if ((maxb-valp)/(maxb-minb)<0.001) 
		os<<"   "<<par_name<<" is near upper bound: "<<minb<<" < "<<valp<<" < "<<maxb<<endl;
	    }//-j
	  } else if (dynamic_cast<param_init_bounded_vector*>(varsptr[i]) != nullptr) {
	    if (debug) os<<"   "<<par_name_base<<" is a param_init_bounded_vector with "<<jmax<<" elements."<<endl;
	    param_init_bounded_vector* p = dynamic_cast<param_init_bounded_vector*>(varsptr[i]);
	    double minb = p->get_minb();
	    double maxb = p->get_maxb();
	    for (int j=p->indexmin();j<=p->indexmax();j++){
	      double valp = ::value(p->elem(j));
	      adstring par_name = par_name_base+"["+str(j)+"]";
	      if (debug) os<<"   "<<par_name<<": "<<minb<<" < "<<valp<<" < "<<maxb<<"?"<<endl;
	      if ((valp-minb)/(maxb-minb)<0.001) 
		os<<"   "<<par_name<<" is near lower bound: "<<minb<<" < "<<valp<<" < "<<maxb<<endl;
	      if ((maxb-valp)/(maxb-minb)<0.001) 
		os<<"   "<<par_name<<" is near upper bound: "<<minb<<" < "<<valp<<" < "<<maxb<<endl;
	    }//-j
	  } else if (dynamic_cast<param_init_bounded_matrix*>(varsptr[i])!=nullptr) {
	    param_init_bounded_matrix* p = dynamic_cast<param_init_bounded_matrix*>(varsptr[i]);
	    if (debug) os<<"   "<<par_name_base<<" is a param_init_bounded_matrix with "<<jmax<<" elements."<<endl;
	    double minb = p->get_minb();
	    double maxb = p->get_maxb();
	    for (int j=p->indexmin();j<=p->indexmax();j++){
	      dvar_vector v = p->elem(j);
	      for (int k=v.indexmin();k<=v.index_max;k++){
		adstring par_name = par_name_base+"["+str(j)+"]"+"["+str(k)+"]";
		double valp = ::value(v[k]);
		if (debug) os<<"   "<<par_name<<": "<<minb<<" < "<<valp<<" < "<<maxb<<"?"<<endl;
		if ((valp-minb)/(maxb-minb)<0.001) 
		  os<<"   "<<par_name<<" is near lower bound: "<<minb<<" < "<<valp<<" < "<<maxb<<endl;
		if ((maxb-valp)/(maxb-minb)<0.001) 
		  os<<"   "<<par_name<<" is near upper bound: "<<minb<<" < "<<valp<<" < "<<maxb<<endl;
	      }//-k
	    }//-j
	  }
	} else {
	  if (debug) os<<"----"<<par_name_base<<" is active but not bounded and will not be checked."<<endl;
	}
      } else {
	if (debug) os<<"--"<<par_name_base<<" is inactive and will not be checked for bounds."<<endl;
      }
    }//--i loop
  } else {
    if (debug) os<<"--Model appears to be autodiff only: no bounds checking performed."<<endl;
  }
  if (debug) os<<"Finished initial_params::check_parameters_on_bounds"<<endl;
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

  // cout <<  "Checking for parameters on bounds (experimental; hbf=" << gradient_structure::Hybrid_bounded_flag << ")..." << endl;
  // if(function_minimizer::random_effects_flag)
  //   cout << "    NOTE: bounds checking is not done here on random effects, only fixed effects parameters." << endl;
  os   << "Checking for parameters on bounds (experimental; hbf=" << gradient_structure::Hybrid_bounded_flag << ")..." << endl;
  if(function_minimizer::random_effects_flag)
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
    // cout<<"nvar = "<<nvar<<".  # params = "<<pars.size()<<endl;

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
