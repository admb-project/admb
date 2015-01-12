// This is used to test the following functions:
// 
// dmatrix inv(_CONST dmatrix & aa);
// dvar_matrix inv(_CONST dvar_matrix & aa);
//
// test1 and test2 should have a value of 3.0
DATA_SECTION
  int n
 !! n=3;
  matrix C(1,n,1,n)
  number test1
  number test2
 LOC_CALCS
  random_number_generator rng(177);
  C.fill_randn(rng);

PARAMETER_SECTION
  init_matrix B(1,n,1,n)
  objective_function_value f

PROCEDURE_SECTION
  test1 = value(norm2(inv(B+C)*(B+C)));
  test2 = norm2(inv(C)*C);
  f=norm2(inv(B+C))+norm2(B+inv(C));

REPORT_SECTION
  report << "#test1" << endl;
  report << test1 << endl;
  report << "#test2" << endl;
  report << test2 << endl;
