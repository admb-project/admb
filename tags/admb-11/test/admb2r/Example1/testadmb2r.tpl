//*****************************************************************************************
//  test-admb2r.tpl     August, 2006
//  Simple AD Model Builder template (program) to demonstrate capabilities of ADMB2R.
//  This template slightly modified from "catage.tpl" distributed by Otter Research with
//      its AD Model Builder software.  Redistributed by NOAA by permission of Otter
//      Research, http://www.otter-rsch.com/
//  ADMB2R = File-based interface from AD Model Builder to R.
//  ADMB2R available from CRAN - Comprehensive R Archive Network, http://cran.r-project.org/
//  For questions or comments regarding ADMB2R, contact
//      mike.prager@noaa.gov   or   jennifer.martin@noaa.gov
//*****************************************************************************************
DATA_SECTION
  init_int nyrs;
  init_int nages;
  init_matrix obs_catch_at_age(1,nyrs,1,nages);
  init_vector effort(1,nyrs);
  init_number M;
  imatrix NA(1,nyrs,1,nages);
  vector testcol(1,nyrs);
  vector relwt(2,nages);
  ivector ages(1,nages);
INITIALIZATION_SECTION
  log_q -1;
  log_popscale 5;
PARAMETER_SECTION
  init_number log_q(1);
  init_number log_popscale(1);
  init_bounded_dev_vector log_sel_coff(1,nages-1,-15.,15.,2);
  init_bounded_dev_vector log_relpop(1,nyrs+nages-1,-15.,15.,2);
  init_bounded_dev_vector effort_devs(1,nyrs,-5.,5.,3);
  vector log_sel(1,nages);
  vector log_initpop(1,nyrs+nages-1);
  matrix F(1,nyrs,1,nages);
  matrix Z(1,nyrs,1,nages);
  matrix S(1,nyrs,1,nages);
  matrix N(1,nyrs,1,nages);
  matrix C(1,nyrs,1,nages);
  objective_function_value f;
  number recsum;
  number initsum;
  sdreport_number avg_F;
  sdreport_vector predicted_N(2,nages);
  sdreport_vector ratio_N(2,nages);
  // changed from the manual because adjusted likelihood routine doesn't
  // work
  likeprof_number pred_B;
PRELIMINARY_CALCS_SECTION
  // this is just to ``invent'' some relative average
  // weight at age numbers
  relwt.fill_seqadd(1.,1.);
  relwt=pow(relwt,.5);
  relwt/=max(relwt);
PROCEDURE_SECTION
  // example of using FUNCTION to structure the procedure section
  get_mortality_and_survivial_rates();

  get_numbers_at_age();

  get_catch_at_age();

  evaluate_the_objective_function();

FUNCTION get_mortality_and_survivial_rates
  // calculate the selectivity from the sel_coffs
  for (int j=1;j<nages;j++)
  {
    log_sel(j)=log_sel_coff(j);
  }
  // the selectivity is the same for the last two age classes
  log_sel(nages)=log_sel_coff(nages-1);

  // This is the same as F(i,j)=exp(q)*effort(i)*exp(log_sel(j));
  F=outer_prod(mfexp(log_q)*effort,mfexp(log_sel));
  if (active(effort_devs))
  {
    for (int i=1;i<=nyrs;i++)
    {
      F(i)=F(i)*exp(effort_devs(i));
    }
  }
  // get the total mortality
  Z=F+M;
  // get the survival rate
  S=mfexp(-1.0*Z);

FUNCTION get_numbers_at_age
  log_initpop=log_relpop+log_popscale;
  for (int i=1;i<=nyrs;i++)
  {
    N(i,1)=mfexp(log_initpop(i));
  }
  for (int j=2;j<=nages;j++)
  {
    N(1,j)=mfexp(log_initpop(nyrs+j-1));
  }
  for (int i=1;i<nyrs;i++)
  {
    for (int j=1;j<nages;j++)
    {
      N(i+1,j+1)=N(i,j)*S(i,j);
    }
  }
  // calculated predicted numbers at age for next year
  for (int j=1;j<nages;j++)
  {
    predicted_N(j+1)=N(nyrs,j)*S(nyrs,j);
    ratio_N(j+1)=predicted_N(j+1)/N(1,j+1);
  }
  // calculated predicted Biomass for next year for
  // adjusted profile likelihood
  pred_B=(predicted_N * relwt);

FUNCTION get_catch_at_age
  C=elem_prod(elem_div(F,Z),elem_prod(1.-S,N));

FUNCTION evaluate_the_objective_function
  // penalty functions to ``regularize '' the solution
  f+=.01*norm2(log_relpop);
  avg_F=sum(F)/double(size_count(F));
  if (last_phase())
  {
    // a very small penalty on the average fishing mortality
    f+= .001*square(log(avg_F/.2));
  }
  else
  {
    f+= 1000.*square(log(avg_F/.2));
  }
  f+=0.5*double(size_count(C)+size_count(effort_devs))
    * log( sum(elem_div(square(C-obs_catch_at_age),.01+C))
    + 0.1*norm2(effort_devs));

REPORT_SECTION
  report << "Estimated numbers of fish " << endl;
  report << N << endl;
  report << "Estimated numbers in catch " << endl;
  report << C << endl;
  report << "Observed numbers in catch " << endl;
  report << obs_catch_at_age << endl;
  report << "Estimated fishing mortality " << endl;
  report << F << endl;

  #include "make-Rfile.cxx"
GLOBALS_SECTION
  #include <admodel.h>
  // Note: "admb2r.cpp" must be in current or $ADMB_HOME/include directory:
  #include "admb2r.cpp"

