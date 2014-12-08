// This is used to test the following functions:
// 
// dvar_vector solve(const dvar_matrix & aa, const dvar_vector & z)
// dvar_vector solve(const dvar_matrix& aa,const dvector& z)
// dvector solve(const dmatrix & aa, const dvector & z)
//
// test1, test2, test3 should all have avalue of 1.0
DATA_SECTION
  int n
  !! n=4;
  matrix M(1,n,1,n)
  vector B(1,n)
  number test1
  number test2
  number test3
  !! random_number_generator rng(132);
  !! M.fill_randn(rng);
  !! B.fill_randn(rng);

PARAMETER_SECTION
  init_matrix VM(1,n,1,n)
  !! VM=M;
  init_vector VB(1,n)
  !! VB=B;
  objective_function_value f
PROCEDURE_SECTION
  test1 = 1.0 + norm2(value(VM*solve(VM,B))-B);
  test2 = 1.0 + norm2(M*solve(M,B)-B);
  test3 = 1.0 + value(norm2(VM*solve(VM,VB)-VB));
  f=norm2(solve(VM,VB))+square(norm2(VB)-1.0)+norm2(VM);

REPORT_SECTION
  report << "#test1" << endl;
  report << test1 << endl;
  report << "#test2" << endl;
  report << test2 << endl;
  report << "#test3" << endl;
  report << test3 << endl;

