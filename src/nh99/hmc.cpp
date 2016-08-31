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

void read_empirical_covariance_matrix(int nvar, const dmatrix& S, const adstring& prog_name);
void read_hessian_matrix_and_scale1(int nvar, const dmatrix& _SS, double s, int mcmc2_flag);

void function_minimizer::hmc_mcmc_routine(int nmcmc,int iseed0,double dscale,
					  int restart_flag) {
  cout << "yes it worked" << endl << endl;
  uostream * pofs_psave=NULL;
  dmatrix mcmc_display_matrix;
  //int mcmc_save_index=1;
  //int mcmc_wrap_flag=0;

  int on2=-1;
  //int nvar1=0;
  if ( (on2=option_match(ad_comm::argc,ad_comm::argv,"-nosdmcmc"))>-1)
    {
      //int no_sd_mcmc = 1;
    }
  if (mcmc2_flag==1)
    {
      initial_params::restore_start_phase();
      //nvar1=initial_params::nvarcalc(); // get the number of active parameters
    }

  // if (stddev_params::num_stddev_params==0)
  // {
  //   cerr << " You must declare at least one object of type sdreport "
  //        << endl << " to do the mcmc calculations" << endl;
  //    return;
  // }
  //ofstream of_bf("testbf");

  //if (adjm_ptr) set_labels_for_mcmc();

  ivector number_offsets;
  dvector lkvector;
  //double current_bf=0;
  //double lcurrent_bf=0;
  //double size_scale=1.0;
  //double total_spread=200;
  //double total_spread=2500;
  //uostream * pofs_sd = NULL;

  initial_params::set_inactive_random_effects();
  // int nvar_x=initial_params::nvarcalc();
  initial_params::set_active_random_effects();
  int nvar_re=initial_params::nvarcalc();

  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  dmatrix s_covar;
  dvector s_mean;
  //int ncsim=25000;
  //int nslots=800;
  //int nslots=3600;
  //int initial_nsim=4800;
  //int ntmp=0;
  //int ncor=0;
  //double bfsum=0;
  //int ibfcount=0;
  //double lbmax;

  s_covar.allocate(1,nvar,1,nvar);
  s_mean.allocate(1,nvar);
  s_mean.initialize();
  s_covar.initialize();

  int ndvar=stddev_params::num_stddev_calc();
  //int numdvar=stddev_params::num_stddev_number_calc();

  if (mcmc2_flag==0)
    {
      initial_params::set_inactive_random_effects();
      nvar=initial_params::nvarcalc(); // get the number of active parameters
    }

  independent_variables parsave(1,nvar_re);
  initial_params::restore_start_phase();

  dvector x(1,nvar);
  //dvector scale(1,nvar);
  dmatrix values;
  //int have_hist_flag=0;
  initial_params::xinit(x);
  dvector pen_vector(1,nvar);
  {
    initial_params::reset(dvar_vector(x),pen_vector);
    //cout << pen_vector << endl << endl;
  }

  initial_params::mc_phase=0;
  //initial_params::stddev_scale(scale,x);
  initial_params::mc_phase=1;
  dvector bmn(1,nvar);
  dvector mean_mcmc_values(1,ndvar);
  dvector s(1,ndvar);
  dvector h(1,ndvar);
  //dvector h;
  dvector square_mcmc_values(1,ndvar);
  square_mcmc_values.initialize();
  mean_mcmc_values.initialize();
  bmn.initialize();
  int use_empirical_flag=0;
  int diag_option=0;
  //int topt=0;
  int L=10;
  double eps=0.1;
  double _eps=-1.0;
  double adapt_delta=0.8; // target acceptance rate specified by the user
  int old_Hybrid_bounded_flag=-1;

  int on,nopt = 0;
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hyeps",nopt))>-1)
    {
      if (!nopt)
	{
	  cerr << "Usage -hyeps option needs number  -- ignored" << endl;
	}
      else
	{
	  istringstream ist(ad_comm::argv[on+1]);
	  ist >> _eps;

	  if (_eps<=0)
	    {
	      cerr << "Usage -hyeps option needs positive number  -- ignored\n";
	      _eps=-1.0;
	    }
	}
    }
  if (_eps>0.0)
    eps=_eps;

  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-hynstep",nopt))>-1)
    {
      if (nopt)
	{
	  int iii=atoi(ad_comm::argv[on+1]);
	  if (iii < 1 )
	    {
	      cerr << " -hynstep argument must be integer between > 0 --"
		" using default of 10" << endl;
	    }
	  else
	    {
	      L=iii;
	    }
	}
    }

  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-adapt_delta",nopt))>-1)
    {
      if (nopt)
	{
	  istringstream ist(ad_comm::argv[on+1]);
	  double delta;
	  ist >> delta;
	  if (delta < 0 || delta > 1 )
	    {
	      cerr << " -adapt_delta argument must be between 0 and 1"
		" using default of 0.8" << endl;
	    }
	  else
	    {
	      adapt_delta=delta;
	    }
	}
    }
      
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcdiag"))>-1)
    {
      diag_option=1;
      cout << " Setting covariance matrix to diagonal with entries " << dscale
	   << endl;
    }
  int mcrestart_flag=option_match(ad_comm::argc,ad_comm::argv,"-mcr");
  dmatrix S(1,nvar,1,nvar);
  dvector old_scale(1,nvar);
  int old_nvar;
  if (!diag_option)
    {
      int rescale_bounded_flag=0;
      double rescale_bounded_power=0.5;
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcrb",nopt))>-1)
	{
	  if (nopt)
	    {
	      int iii=atoi(ad_comm::argv[on+1]);
	      if (iii < 1 || iii > 9)
		{
		  cerr << " -mcrb argument must be integer between 1 and 9 --"
		    " using default of 5" << endl;
		  rescale_bounded_power=0.5;
		}
	      else
		rescale_bounded_power=iii/10.0;
	    }
	  else
	    {
	      rescale_bounded_power=0.5;
	    }
	  rescale_bounded_flag=1;
	}
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcec"))>-1)
	{
	  use_empirical_flag=1;
	}
      if (use_empirical_flag)
	{
	  read_empirical_covariance_matrix(nvar,S,ad_comm::adprogram_name);
	}
      else if (!rescale_bounded_flag)
	{
	  if (mcmc2_flag==0)
	    {
	      read_covariance_matrix(S,nvar,old_Hybrid_bounded_flag,old_scale);
	    }
	  else
	    {
	      int tmp_nvar = 0;
	      adstring tmpstring = ad_comm::adprogram_name + ".bgs";
	      uistream uis((char*)(tmpstring));
	      if (!uis)
		{
		  cerr << "error opening file " << tmpstring << endl;
		  ad_exit(1);
		}
	      uis >> tmp_nvar;
	      if (!uis)
		{
		  cerr << "error reading from file " << tmpstring << endl;
		  ad_exit(1);
		}
	      if (tmp_nvar != nvar)
		{
		  cerr << "size error reading from " <<  tmpstring << endl;
		  ad_exit(1);
		}
	      uis >> S;
	      if (!uis)
		{
		  cerr << "error reading from file " << tmpstring << endl;
		  ad_exit(1);
		}
	      dvector tmp=read_old_scale(old_nvar);
	      old_scale=1.0;
	      old_scale(1,old_nvar)=tmp;
	    }
	}
      else
	{
	  read_hessian_matrix_and_scale1(nvar,S,rescale_bounded_power,
					 mcmc2_flag);
	  //read_hessian_matrix_and_scale(nvar,S,pen_vector);
	}

      // maybe we dont want to do this?
      /*
	{  // scale covariance matrix for model space
	dmatrix tmp(1,nvar,1,nvar);
	for (int i=1;i<=nvar;i++)
	{
	tmp(i,i)=S(i,i)*(scale(i)*scale(i));
	for (int j=1;j<i;j++)
	{
	tmp(i,j)=S(i,j)*(scale(i)*scale(j));
	tmp(j,i)=tmp(i,j);
	}
	}
	S=tmp;
	}
      */
    }
  else			// set covariance to be diagonal
    {
      S.initialize();
      for (int i=1;i<=nvar;i++)
	{
	  S(i,i)=dscale;
	}
    }

  // for hybrid mcmc option always save output
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-mcsave"))>-1)
    {
      cerr << "Option -mcsave does not work with HMC -- every iteration is saved" << endl;
    }
  if ( mcrestart_flag>-1)
    {
      // check that nvar is correct
      uistream uis((char*)(ad_comm::adprogram_name + adstring(".psv")));
      if (!uis)
	{
	  cerr << "Error trying to open file" <<
	    ad_comm::adprogram_name + adstring(".psv") <<
	    " for mcrestart" <<   endl;
	  ad_exit(1);
	} else {
	int nv1 = 0;
	uis >> nv1;
	if (nv1 !=nvar) {
	  cerr << "wrong number of independent variables in" <<
	    ad_comm::adprogram_name + adstring(".psv") << endl
	       << " I found " << nv1 << " instead of " << nvar  << endl;
	  ad_exit(1);
	}
	// get last x vector from file
#ifndef OPT_LIB
	assert(parsave.size() >= 0);
#endif
	std::streamoff sz = (unsigned int)parsave.size() * sizeof(double);
	// backup from end of file
	uis.seekg(-sz, ios::end);
	uis >> parsave;
	cout << " restored "  << parsave(parsave.indexmin()) << " "
	     << parsave(parsave.indexmax()) << endl;
	if (!uis)
	  {
	    cerr << "error resotring last mcmc poistion from file "
		 << ad_comm::adprogram_name + adstring(".psv") << endl;
	    ad_exit(1);
	  }
	int ii=1;
	dvector x0(1,nvar);
	initial_params::restore_all_values(parsave,ii);
	//x0.initialize();
	//dvector pen_vector(1,nvar);
	//initial_params::reset(dvar_vector(parsave),pen_vector);
	//initial_params::xinit(x0);
	//cout << " x0 " << x0(x0.indexmin()) << endl;
      }
    }


  if ( mcrestart_flag>-1)
    {
      pofs_psave= new uostream( (char*)(ad_comm::adprogram_name
					+ adstring(".psv")),ios::app);
      /*
	pofs_psave->seekp(0,std::ios::end);
	*pofs_psave << 123;
	delete pofs_psave;
	uistream uis((char*)(ad_comm::adprogram_name + adstring(".psv")));
	if (!uis)
	{
	cerr << "Error trying to open file" <<
	ad_comm::adprogram_name + adstring(".psv") <<
	" for mcrestart" <<   endl;
	ad_exit(1);
	} else {
	int nv1;
	uis >> nv1;
	if (nv1 !=nvar) {
	cerr << "wrong number of independent variables in" <<
	ad_comm::adprogram_name + adstring(".psv") << endl
	<< " I found " << nv1 << " instead of " << nvar  << endl;
	ad_exit(1);
	}
	}
      */
    }
  else
    {
      pofs_psave=
	new uostream((char*)(ad_comm::adprogram_name + adstring(".psv")));
    }

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
  // cout << "starting with " << x0(x0.indexmin()) << " "
  //    << x0(x0.indexmax()) << endl;
  int mctmp=initial_params::mc_phase;
  initial_params::mc_phase=0;
  initial_params::stddev_scale(current_scale,x);
  initial_params::mc_phase=mctmp;
  for (int i=1;i<=nvar;i++)
    {
      for (int j=1;j<=nvar;j++)
	{
	  S(i,j)*=old_scale(i)*old_scale(j);
	}
    }
  for (int i=1;i<=nvar;i++)
    {
      for (int j=1;j<=nvar;j++)
	{
	  S(i,j)/=current_scale(i)*current_scale(j);
	}
    }

  //cout << sort(eigenvalues(S)) << endl;
  //dmatrix tchd = trans(chd);
  //dmatrix chdinv=inv(chd);
  //int sgn;
  // ***************************************************************
  // ***************************************************************
  // NEW HYBRID MCMC
  // ***************************************************************
  // ***************************************************************
  int number_sims;
  if (nmcmc<=0)
    {
      number_sims=  1000;
    }
  else
    {
      number_sims=  nmcmc;
    }

  gradient_structure::set_NO_DERIVATIVES();

  if (mcmc2_flag==0)
    {
      initial_params::set_inactive_random_effects();
    }

  int iseed=2197;
  if (iseed0) iseed=iseed0;
  if ( mcrestart_flag>-1)
    {
      ifstream ifs("hybrid_seed");
      ifs >> iseed;
      if (!ifs)
	{
	  cerr << "error reading random number seed" << endl;
	}
    }
  random_number_generator rng(iseed);
  gradient_structure::set_YES_DERIVATIVES();
  initial_params::xinit(x0);

  // Declare the variables needed
  dmatrix chd = choleski_decomp(S); // cholesky decomp of mass matrix
  dvector y(1,nvar); // unbounded parameters
  y.initialize();    
  dvector yold(1,nvar);	// unbounded parameters 2
  independent_variables z(1,nvar); // rotated bounded parameters???
  z=chd*y;			     
  // This 
  dvector gr(1,nvar);		// gradients in unbounded space
  get_hybrid_monte_carlo_value(nvar,z,gr);
  dvector gr2begin=gr*chd; // rotated gradient
  dvector gr2(1,nvar);	  // rotated gradient

  dvector p(1,nvar);  // momentum
  p.fill_randn(rng);
  //    dmatrix xvalues(1,number_sims,1,nvar);

  // Initialize the algorithm: momenta and position, H
  yold=y;
  gr2=gr2begin;		// rotated gradient
  double pprob=0.5*norm2(p);	// probability of momenta
  double nll=get_hybrid_monte_carlo_value(nvar,z,gr); // probability of position
  double H0=nll+pprob;			       // initial Hamiltonian
  int ii=1;
  initial_params::copy_all_values(parsave,ii); // does bounding??
  double iaccept=0.0;
  int accepted;		// boolean for whether iteration accepted
  dvector phalf;
  // Dual averaging components
  int useDA=1;
  double gamma=0.5;
  double t0=10;
  double kappa=0.75;
  double mu=log(10*eps);
  dvector epsvec(1,number_sims+1), epsbar(1,number_sims+1), Hbar(1,number_sims+1);
  epsvec.initialize();
  epsbar.initialize();
  Hbar.initialize();
  epsvec(1)=eps;
  epsbar(1)=eps;
  Hbar(1)=0;
    
  // Start of MCMC chain
  for (int is=1;is<=number_sims;is++) {
    // Start of single trajectory
    for (int i=1;i<=L;i++) {
      phalf=p-eps/2*gr2; // update momentum by half step (why negative?)
      y+=eps*phalf;	      // update parameters by full step
      z=chd*y;		      // transform parameters via mass matrix
      // This function returns the negative log density/likelihood but also sets gradients in gr
      nll=get_hybrid_monte_carlo_value(nvar,z,gr);
      gr2=gr*chd;		// transform gradient via mass matrix
      p=phalf-eps/2*gr2; // update momentum by half step (why negatiev?)
    } // end of trajectory
    pprob=0.5*norm2(p);	   // probability of momentum (iid standard normal)
    double Ham=nll+pprob; // H at proposed state
    double alpha=exp(H0-Ham); // acceptance ratio
    // this looks like a bug -- should leave momentum alone here until after saving values?
    p.fill_randn(rng);
    pprob=0.5*norm2(p);
	
    // Test whether to accept the proposed state
    double rr=randu(rng);	   // Runif(1)
    if (rr<alpha) // accept 
      {
	accepted=1;
	iaccept++;
	yold=y;		// Update parameters
	H0=nll+pprob;	// 
	gr2begin=gr2;
	ii=1;
	initial_params::copy_all_values(parsave,ii);
      }
    else // reject 
      {
	accepted=0;
	y=yold;		// Don't update params
	z=chd*y;		// 
	H0=nll+pprob;
	gr2=gr2begin;	// don't update gradients
      }
    // Do dual averaging to adapt step size
    if(useDA){
      Hbar(is+1)=
	(1-1/(is+t0))*Hbar(is) + (adapt_delta-min(1.0,alpha))/(is+t0);
      double logeps=mu-sqrt(is)*Hbar(is+1)/gamma;
      epsvec(is+1)=exp(logeps);
      double logepsbar= pow(is, -kappa)*logeps+(1-pow(is,-kappa))*log(epsbar(is));
      epsbar(is+1)=exp(logepsbar);
      eps=epsvec(is+1);	// this is the adapted step size for the next iteration
    }
    if ((is%5)==1)
      cout << "iteration=" << is << "; eps=" << eps << "; accepted="<< accepted<<
	"; accept ratio " << min(1.0,alpha) << endl;
    // Copy parameters to the .psv file
    (*pofs_psave) << parsave;
  } // end of MCMC chain
    // This final ratio should closely match adapt_delta
  cout << "Final acceptance ratio=" << iaccept/number_sims << " and target is " << adapt_delta<<endl;

  // This saves a new seed for if the chain is restarted, making it
  // reproducible.
  ofstream ofs("hybrid_seed");
  int seed=(int) (10000*randu(rng));
  ofs << seed;
  if (pofs_psave)
    {
      delete pofs_psave;
      pofs_psave=NULL;
    }
}

/**
 * Written by Dave, commented by Cole starting 8/31/2016
 * Description not yet available.
 * \param
 * x is vector of Choleski decomposed parameters (i.e., x=y*chd).
 * g is a vector of empty gradients
 * returns the negative log likelihood (density), but also stores gradients for x in g
 */
double function_minimizer::get_hybrid_monte_carlo_value(int nvar,
							const independent_variables& x,dvector& g)
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
