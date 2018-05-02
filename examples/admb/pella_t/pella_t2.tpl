// Author: David Fournier
// Copyright (c) 2009-2018 ADMB Foundation

DATA_SECTION
  init_int nobs;
  init_matrix data(1,nobs,1,3)
  vector obs_catch(1,nobs);
  vector cpue(1,nobs);
  vector effort(1,nobs);
  number avg_effort
INITIALIZATION_SECTION
  m 2.
  beta 1.
  r 1.
PARAMETER_SECTION
  init_bounded_number r(0.,5,2)
  init_bounded_number beta(0.,5.)
  init_number log_binit(2)
  init_bounded_number q(0.,1.)
  init_bounded_number m(1,10.,4)
  init_bounded_vector effort_devs(1,nobs,-5.,5.,3)
  init_bounded_vector k_devs(2,nobs,-5.,5.,4)
  number binit
  vector pred_catch(1,nobs)
  vector biomass(1,nobs)
  vector f(1,nobs)
  vector k(1,nobs)
  vector k_trend(1,nobs)
  sdreport_number k_1
  sdreport_number k_last
  sdreport_number k_change
  sdreport_number k_ratio
  sdreport_number B_projected
  number tmp_mort;
  number bio_tmp;
  number c_tmp;
  objective_function_value ff;
PRELIMINARY_CALCS_SECTION
  // get the data out of the data matrix into 
  obs_catch=column(data,2);  
  cpue=column(data,3);  
  // divide the catch by the cpue to get the effort
  effort=elem_div(obs_catch,cpue);
  // normalize the effort and save the average
  double avg_effort=mean(effort);
  effort/=avg_effort;
  cout << " beta" << beta << endl;
PROCEDURE_SECTION
  dvariable mean = sum(effort_devs) / static_cast<double>(effort_devs.size());
  effort_devs -= mean;

  // calculate the fishing mortality
  calculate_fishing_mortality();
  // calculate the biomass and predicted catch
  calculate_biomass_and_predicted_catch();
  // calculate the objective function
  calculate_the_objective_function();

  ff += 100.0 * square(total);

FUNCTION calculate_fishing_mortality
  // calculate the fishing mortality
  f=q*effort;
  if (active(effort_devs)) f=elem_prod(f,exp(effort_devs));

FUNCTION calculate_biomass_and_predicted_catch
  // calculate the biomass and predicted catch
  if (!active(log_binit))
  {
    log_binit=log(obs_catch(1)/(q*effort(1)));
  }
  binit=exp(log_binit);
  biomass[1]=binit;
  if (active(k_devs))
  {
    k(1)=binit/beta;
    for (int i=2;i<=nobs;i++)
    {
      k(i)=k(i-1)*exp(k_devs(i));
    }
  }
  else
  {
    // set the whole vector equal to the constant k value
    k=binit/beta;
  }
  // only calculate these for the standard deviation report
  if (sd_phase())
  {
    k_1=k(1);
    k_last=k(nobs);
    k_ratio=k(nobs)/k(1);
    k_change=k(nobs)-k(1);
  }
  // two time steps per year desired
  int nsteps=2;
  double delta=1./nsteps;
  // Integrate the logistic dynamics over n time steps per year
  for (int i=1; i<=nobs; i++)
  {
    bio_tmp=1.e-20+biomass[i];
    c_tmp=0.;
    for (int j=1; j<=nsteps; j++)
    {
      //This is the new biomass after time step delta
      bio_tmp=bio_tmp*(1.+r*delta)/
	(1.+ (r*pow(bio_tmp/k(i),m-1.)+f(i))*delta );
      // This is the catch over time step delta
      c_tmp+=f(i)*delta*bio_tmp;
    }
    pred_catch[i]=c_tmp;        // This is the catch for this year
    if (i<nobs)
    {
      biomass[i+1]=bio_tmp;// This is the biomass at the begining of the next
    }			   // year
    else
    {
      B_projected=bio_tmp; // get the projected biomass for std dev report
    }
  }

FUNCTION calculate_the_objective_function
  if (!active(effort_devs))
  {
    ff=nobs/2.*log(norm2(log(obs_catch)-log(1.e-10+pred_catch)));
  }
  else if(!active(k_devs))
  {
    ff= .5*(size_count(obs_catch)+size_count(effort_devs))*
      log(norm2(log(obs_catch)-log(1.e-10+pred_catch))
			      +0.1*norm2(effort_devs));
  }
  else 
  {
    ff= .5*( size_count(obs_catch)+size_count(effort_devs)
	     +size_count(k_devs) )*
      log(norm2(log(obs_catch)-log(pred_catch))
	   + 0.1*norm2(effort_devs)+10.*norm2(k_devs));
  }
  // Bayesian contribution for Pella Tomlinson m
  ff+=2.*square(log(m-1.));
  if (initial_params::current_phase<3)
  {
    ff+=1000.*square(log(mean(f)/.4));
  }
