#include <admodel.h>

#include <pella-t.htp>

model_data::model_data()
{
  nobs.allocate("nobs");
  data.allocate(1,nobs,1,3,"data");
  obs_catch.allocate(1,nobs);
  cpue.allocate(1,nobs);
  effort.allocate(1,nobs);
}

void model_parameters::initializationfunction(void)
{
  m.set_initial_value(2.);
  beta.set_initial_value(1.);
  r.set_initial_value(1.);
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 ad_comm(argc,argv), model_data() , function_minimizer(sz)
{
  initializationfunction();
  r.allocate(0.,5,2,"r");
  beta.allocate(0.,5.,"beta");
  log_binit.allocate(2,"log_binit");
  q.allocate(0.,1.,"q");
  m.allocate(1,10.,4,"m");
  effort_devs.allocate(1,nobs,-5.,5.,3,"effort_devs");
  k_devs.allocate(2,nobs,-5.,5.,4,"k_devs");
  binit.allocate("binit");
  #ifndef NO_AD_INITIALIZE
  binit.initialize();
  #endif
  pred_catch.allocate(1,nobs,"pred_catch");
  #ifndef NO_AD_INITIALIZE
    pred_catch.initialize();
  #endif
  biomass.allocate(1,nobs,"biomass");
  #ifndef NO_AD_INITIALIZE
    biomass.initialize();
  #endif
  f.allocate(1,nobs,"f");
  #ifndef NO_AD_INITIALIZE
    f.initialize();
  #endif
  k.allocate(1,nobs,"k");
  #ifndef NO_AD_INITIALIZE
    k.initialize();
  #endif
  k_trend.allocate(1,nobs,"k_trend");
  #ifndef NO_AD_INITIALIZE
    k_trend.initialize();
  #endif
  k_1.allocate("k_1");
  k_last.allocate("k_last");
  k_change.allocate("k_change");
  k_ratio.allocate("k_ratio");
  B_projected.allocate("B_projected");
  tmp_mort.allocate("tmp_mort");
  #ifndef NO_AD_INITIALIZE
  tmp_mort.initialize();
  #endif
  bio_tmp.allocate("bio_tmp");
  #ifndef NO_AD_INITIALIZE
  bio_tmp.initialize();
  #endif
  c_tmp.allocate("c_tmp");
  #ifndef NO_AD_INITIALIZE
  c_tmp.initialize();
  #endif
  ff.allocate("ff");
}

void model_parameters::preliminary_calculations(void)
{
  // get the data out of the data matrix into 
  obs_catch=column(data,2);  
  cpue=column(data,3);  
  // divide the catch by the cpue to get the effort
  effort=elem_div(obs_catch,cpue);
  // normalize the effort and save the average
  double avg_effort=mean(effort);
  effort/=avg_effort;
  cout << " beta" << beta << endl;
}

void model_parameters::userfunction(void)
{
  // calculate the fishing mortality
  calculate_fishing_mortality();
  // calculate the biomass and predicted catch
  calculate_biomass_and_predicted_catch();
  // calculate the objective function
  calculate_the_objective_function();
}

void model_parameters::calculate_fishing_mortality(void)
{
  // calculate the fishing mortality
  f=q*effort;
  if (active(effort_devs)) f=elem_prod(f,exp(effort_devs));
}

void model_parameters::calculate_biomass_and_predicted_catch(void)
{
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
  if (sd_phase)
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
}

void model_parameters::calculate_the_objective_function(void)
{
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
}

  model_data::~model_data(){}

void model_parameters::report(void){}

void function_minimizer::set_runtime(void){}

#ifdef _BORLANDC_
  extern unsigned _stklen=10000U;
#endif


#ifdef __ZTC__
  extern unsigned int _stack=10000U;
#endif

  long int arrmblsize=0;

int main(int argc,char * argv[])
{
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
  #if defined(__GNUDOS__) || defined(DOS386) || defined(__DPMI32__)  || \
     defined(__MSVC32__)
    if (!arrmblsize) arrmblsize=150000;
  #else
    if (!arrmblsize) arrmblsize=25000;
  #endif
  model_parameters mp(arrmblsize,argc,argv);
  mp.iprint=10;
  mp.preliminary_calculations();
  mp.computations(argc,argv);
  return 0;
}
