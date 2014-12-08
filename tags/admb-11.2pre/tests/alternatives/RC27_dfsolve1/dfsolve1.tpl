// This is used to test the following functions:
// 
//df1b2vector solve(const df1b2matrix& aa,const df1b2vector& z)
//df1b2vector solve(const df1b2matrix& aa,const dvector& z)
//
// test1 and test2 should have a value of 1.0
DATA_SECTION
  init_int n
  init_matrix CM(1,n,1,n)
  init_vector cv(1,n)
  number test1
  number test2
PARAMETER_SECTION
  init_matrix M(1,n,1,n)
  random_effects_vector u(1,n)
  objective_function_value f
PROCEDURE_SECTION
  test1 = 1.0 + value(norm2((M+CM)*(solve(M+CM,u))-u));
  test2 = 1.0 + value(norm2((M+CM)*(solve(M+CM,cv))-cv));
  f=square(norm2(cv-solve(M+CM,u)));
  f+=0.5*square(norm2(u));
  f+=0.5*square(norm2(M));

REPORT_SECTION
  report << "#test1" << endl;
  report << test1 << endl;
  report << "#test2" << endl;
  report << test2 << endl;
