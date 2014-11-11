//======================================================================================================================
// File:        pella.tpl
// Model:       Pella-Tomlinson model, with Binit=k*a
// Parameters:  r, k, a, p, q, sigma
// Fitted data: Abundance index
// Likelihood:  Log-transformed normal
// References:  Polacheck et al. (1993)
// Notes:       q and sigma are free parameters, to allow full uncertainty in MCMC analysis
// History:     24 Jan 2014 hacked by John Sibert to use xml
//               6 Jan 2011 Arni Magnusson improved vector extraction
//               7 Oct 2010 Arni Magnusson improved string handling and comments
//               9 Mar 2010 Arni Magnusson created, to benchmark against R optimizers
//======================================================================================================================
// Implementation notes
//   Abundance index may not exist for all years
//   Vectors that include all years: B, C
//   Vectors that include abundance index years: I, Ifit, X
//   X links long and short vectors
//======================================================================================================================

GLOBALS_SECTION
  #include "ADMB_XMLDoc.h"
  #include <string>
  #include "trace.h"  
  using std::string;
  const double pi = 3.141592654;
  int mcmc_iteration = 0;
  //int phz;    // phase
  //double lb;  // lower bound
  //double ub;  // upper bound
  ofstream mcmc_par("mcmc_par.csv");
  ofstream mcmc_bio("mcmc_bio.csv");

  ofstream clogf("trace.log");

DATA_SECTION
  // Read data xml file
  init_xml_doc xml
  init_int nc(xml)
  init_matrix Cdata(xml)  // Year | C

  init_int ni(xml)
  init_matrix Idata(xml)  // Year | I

  // Vectors
  ivector Cyear(1,nc)
  ivector Iyear(1,ni)
  vector C(1,nc)
  vector I(1,ni)
  ivector X(1,ni)  // years with abundance index: 1995 | 1998 | ...
  // Constants
  number halfnlog2pi
  vector logI(1,ni)
  
PARAMETER_SECTION
  // Estimated
  init_bounded_number logr(xml)
  init_bounded_number logk(xml)
  init_bounded_number loga(xml)
  init_bounded_number logp(xml);
  init_bounded_number logq(xml)
  init_bounded_number logsigma(xml)
  // Derived
  number r
  number k
  number a
  number p
  sdreport_number q
  number sigma
  // Updated
  vector B(1,nc)
  vector Bfit(1,ni)
  vector Ifit(1,ni)
  number RSS
  // Report
  matrix summary(1,nc,1,5)  // Year | B | C | I | Ifit
  // Objfun
  objective_function_value neglogL

PRELIMINARY_CALCS_SECTION
  // Data
  Cyear = (ivector) column(Cdata,1);
  C = column(Cdata,2);
  Iyear = (ivector) column(Idata,1);
  I = column(Idata,2);
  X = Iyear - Cyear(1) + 1;
  halfnlog2pi = 0.5*ni*log(2*pi);
  logI = log(I);

  // save data and initial parameter values in xml file .x00
  neglogL = 0.0;
  saveXMLFile();
  TRACE(xml.getControlVector("logr"));
  TRACE(xml.getControlVector("logk"));
  TRACE(xml.getControlVector("loga"));
  TRACE(xml.getControlVector("logp"));
  TRACE(xml.getControlVector("logq"));
  TRACE(xml.getControlVector("logsigma"));

PROCEDURE_SECTION
  get_fit();
  get_neglogL();
  if(mceval_phase())
    write_mcmc();

REPORT_SECTION

  /*
  for (int i=0;i< initial_params::num_initial_params;i++)
  {
     //(varsptr[i])->save_value();
     xml.createXMLelement(*initial_params::varsptr[i],"varptr");
  }
  */
  summary.initialize();
  get_summary();

  // save data and parameter estimates in xml file .x01
  saveXMLFile();
  report<<setprecision(12)
        <<"# r"      <<endl<<r      <<endl
        <<"# k"      <<endl<<k      <<endl
        <<"# a"      <<endl<<a      <<endl
        <<"# p"      <<endl<<p      <<endl
        <<"# q"      <<endl<<q      <<endl
        <<"# sigma"  <<endl<<sigma  <<endl
        <<"# RSS"    <<endl<<RSS    <<endl
        <<"# neglogL"<<endl<<neglogL<<endl<<endl;
  report<<setprecision(4)
        <<"# Model summary"<<endl
        <<" Year Biomass Catch Index IndexFit"<<endl
        <<summary<<endl;

FUNCTION saveXMLFile
  ADMB_XMLDoc oxml;
  int ret = 0;

  if (fabs(neglogL) <= 0.0)
    oxml.allocate("FIT","xpella","Starting Values", "xpella.x00");
  else
  {
    oxml.allocate("FIT","xpella","Final Estimates", "xpella.x01");
    ret = oxml.createXMLcomment("fit statistics");
    ret = oxml.createXMLelement(neglogL);
  } 
  ret = oxml.createXMLelement(nc,"Catch Data Years");
  ret = oxml.createXMLelement(Cdata,"Catch Data");
  ret = oxml.createXMLelement(ni,"Survey Data Years");
  ret = oxml.createXMLelement(Idata,"Survey Data");

  ret = oxml.createXMLelement(logr,"log growth rate");
  ret = oxml.createXMLelement(logk,"log carrying capacity");
  ret = oxml.createXMLelement(loga,"log a");
  ret = oxml.createXMLelement(logp,"log p");
  ret = oxml.createXMLelement(logq,"log q");
  ret = oxml.createXMLelement(logsigma,"log sigma");

  if (fabs(neglogL) > 0.0)
  {
     ret = oxml.createXMLcomment("Derived and updated variable objects.");
     ret = oxml.createXMLelement(r,"Growth Rate");
     ret = oxml.createXMLelement(k,"Carrying Capacity");
     ret = oxml.createXMLelement(a,"Definition of a");
     ret = oxml.createXMLelement(p,"Definition of p");
     ret = oxml.createXMLelement(q,"Catchability");
     ret = oxml.createXMLelement(sigma,"Standard Deviation");
     ret = oxml.createXMLelement(B,"Biomass");
     ret = oxml.createXMLelement(Bfit,"Biomass Fit");
     ret = oxml.createXMLelement(Ifit,"Predicted Catch?");
     ret = oxml.createXMLelement(RSS,"Residual Sum of Squares");
     ret = oxml.createXMLelement(summary,"Year Biomass Catch Index IndexFit");

  }

  int nbytes = oxml.write();

FUNCTION get_fit
  r = mfexp(logr);
  k = mfexp(logk);
  a = mfexp(loga);
  p = mfexp(logp);
  q = mfexp(logq);
  sigma = mfexp(logsigma);
  B(1) = k * a;
  for(int t=1; t<=nc-1; t++)
    B(t+1) = sfabs(B(t) + r/p*B(t)*(1-pow(B(t)/k,p)) - C(t));
  Ifit = q*B(X);

FUNCTION get_neglogL
  RSS = norm2(logI-log(Ifit));
  neglogL = halfnlog2pi + ni*log(sigma) + RSS/(2*sigma*sigma);

FUNCTION get_summary
  summary.colfill(1,(dvector)Cyear);
  summary.colfill(2,B);
  summary.colfill(3,C);
  for(int i=1; i<=ni; i++)  // allow missing years in abundance index
  {
    summary(X(i),4) = I(i);
    summary(X(i),5) = Ifit(i);
  }

FUNCTION write_mcmc
  mcmc_iteration++;
  // Parameters
  if(mcmc_iteration == 1)
    mcmc_par<<"neglogL,r,k,a,p,q,sigma"<<endl;
  mcmc_par<<neglogL<<","
          <<r      <<","
          <<k      <<","
          <<a      <<","
          <<p      <<","
          <<q      <<","
          <<sigma  <<endl;
  // Biomass
  if(mcmc_iteration == 1)
  {
    mcmc_bio<<Cyear(1);
    for(int t=2; t<=nc; t++)
      mcmc_bio<<","<<Cyear(t);
    mcmc_bio<<endl;
  }
  mcmc_bio<<B(1);
  for(int t=2; t<=nc; t++)
    mcmc_bio<<","<<B(t);
  mcmc_bio<<endl;
