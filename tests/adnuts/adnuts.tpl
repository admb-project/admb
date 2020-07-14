// Simple model to test typical calls by R package adnuts. Copied from hysimple example. Cole Monnahan, 7/2020
DATA_SECTION
  int n
 !! n=10;
PARAMETER_SECTION
  init_vector x(1,n)
  //sdreport_number x1 // note no sdreport is needed for -nuts or -rwm
  objective_function_value f
PROCEDURE_SECTION
  //x1=x(1);
  f+=0.5*norm2(x);
 // if (mceval_phase())
   // cout << x1 << endl;
