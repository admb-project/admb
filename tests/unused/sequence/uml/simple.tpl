  //Version of simple ADMB example with superflous SECTIONs
  //for following program flow with debugger.

GLOBALS_SECTION
  #include "trace.h"
  ofstream clogf("trace.log");


DATA_SECTION
  init_int nobs
  init_vector Y(1,nobs)
  init_vector x(1,nobs)
  number initial_answer
  number final_answer

INITIALIZATION_SECTION
  a 0
  b 0

PARAMETER_SECTION
  init_number a   
  init_number b   
  vector pred_Y(1,nobs)
  objective_function_value f

PRELIMINARY_CALCS_SECTION
  initial_answer = 0;
  final_answer = 0;

PROCEDURE_SECTION
  pred_Y=a*x+b;
  f=(norm2(pred_Y-Y)); 
  f=nobs/2.*log(f);    // make it a likelihood function so that
                       // covariance matrix is correct

FINAL_SECTION
  final_answer = 42;
  TRACE(initial_answer)
  TRACE(final_answer)

REPORT_SECTION
  report << "a = " << a << endl;
  report << "b = " << b << endl;
  report << "pred_Y = " << pred_Y << endl;
  report << "initial_answer = " << initial_answer << endl;
  report << "final_answer = " << final_answer << endl;

TOP_OF_MAIN_SECTION
  HERE
  clogf << "top of main start" << endl;
  arrmblsize= 10000000;
  gradient_structure::set_CMPDIF_BUFFER_SIZE( 1500000000L);
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(50000000L);
  gradient_structure::set_MAX_NVAR_OFFSET(1000);
  clogf << "top of main finish" << endl;
  HERE
 
