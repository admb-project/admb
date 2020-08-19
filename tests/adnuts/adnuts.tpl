// Simple model to test typical calls by R package adnuts. Copied from hysimple example. Cole Monnahan, 7/2020
DATA_SECTION
  int n
 !! n=10;
PARAMETER_SECTION
  init_bounded_number p(-1,1) // just to test bounded pars
  init_vector x(1,n)
  //sdreport_number x1 // note no sdreport is needed for -nuts or -rwm
  objective_function_value f
PROCEDURE_SECTION
  //x1=x(1);
  f+=0.5*norm2(x);
  f+=0.5*p*p;
 // if (mceval_phase())
   // cout << x1 << endl;
