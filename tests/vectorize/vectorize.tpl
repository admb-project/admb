GLOBALS_SECTION
  #include <fvar.hpp>
  dvariable logBH(dvariable ssb, dvariable loga, dvariable logb){
    return loga+log(ssb)-log(1+exp(logb)*ssb); 
  }
  #include <Vectorize.hpp>
  VECTORIZE3_ttt(logBH);

DATA_SECTION
  init_int n
  init_vector ssb(1,n)
  init_vector logR(1,n)
PARAMETER_SECTION
  init_number loga;
  init_number logb;
  init_number logSigma;
  sdreport_number sigmaSq;
  vector pred(1,n);
  objective_function_value nll;
PROCEDURE_SECTION
  sigmaSq=exp(2.0*logSigma);
  pred=logBH((dvar_vector)ssb,loga,logb);
  nll=0.5*(n*log(2*M_PI*sigmaSq)+sum(square(logR-pred))/sigmaSq);
