GLOBALS_SECTION
  #include "ADMB_XMLDoc.h"
DATA_SECTION
  init_xml_doc ixml
  init_int nobs(ixml)
  init_vector Y(ixml)
  init_vector x(ixml)
PARAMETER_SECTION
  // these two parameter do not have bounds, initial value, or phases
  // xml allocator is not required
  // except if an initial vialue were desired
  init_number a(ixml)
  init_number b(ixml)
  vector pred_Y(1,nobs)
  objective_function_value f
PRELIMINARY_CALCS_SECTION
  // save data and initial parameter values in xml file .x00
  f = 0.0;
  saveXMLFile();

PROCEDURE_SECTION
  pred_Y=a*x+b;
  f=(norm2(pred_Y-Y)); 
  f=nobs/2.*log(f);    // make it a likelihood function so that
                       // covariance matrix is correct
FUNCTION saveXMLFile
  ADMB_XMLDoc oxml;

  if (fabs(f) <= 0.0)
    oxml.allocate("FIT","simple","Starting Values", "simple.x00");
  else
  {
    oxml.allocate("FIT","simple","Final Estimates", "simple.x01");
    oxml.createXMLcomment("fit statistics");
    oxml.createXMLelement(f);
  }
  oxml.createXMLelement(nobs,"Number of Observations");  
  oxml.createXMLelement(Y,"Observed Y values");
  oxml.createXMLelement(x,"Observed x values");

  oxml.createXMLelement(a, "Slope Parameter");
  oxml.createXMLelement(b, "Intercept Parameter");
  oxml.createXMLelement(pred_Y, "Predicted Y values");
  oxml.write();


REPORT_SECTION
  saveXMLFile();

