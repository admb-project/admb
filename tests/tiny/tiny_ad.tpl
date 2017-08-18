GLOBALS_SECTION
  #include <df1b2fun.h>
  #include "beta/pbeta.hpp"

  template<class Float>
  Float ppbeta(Float x, Float a, Float b){
    return toms708::pbeta(x, a, b, 1, 0);
  }

  TINYFUN3(ppbeta,x,a,b);
  VECTORIZE3_ttt(ppbeta);

DATA_SECTION
  vector x(1,20000)
  !! x.fill_seqadd(0,.00005);
  vector y(1,20000)
  !! y=ppbeta(x,0.3,0.4);
  



PARAMETER_SECTION
  init_number loga
  init_number logb
  sdreport_number a
  sdreport_number b
  objective_function_value nll

PROCEDURE_SECTION
  nll=0;
  a=exp(loga);
  b=exp(logb);
  dvar_vector pred=ppbeta((dvar_vector)x,a,b);
  nll=sum(square(y-pred));
  
REPORT_SECTION
  for(int i=1; i<=20000; ++i)report<<x(i)<<" "<<0.3<<" "<<0.4<<" "<<setprecision(25)<<y(i)<<endl;
