// This is used to test the following functions:
//
// sing_val_decomp singval_decomp(const dmatrix &_a);
// found in linad99/dmat42.cpp
//
// test should have a value of 1.0
DATA_SECTION
  int n
  int m
  !! n=7;
  !! m=11;
  matrix mat(1,m,1,n)
  number test
  !! random_number_generator rng(586);
  !! mat.fill_randn(rng);

PARAMETER_SECTION
  init_matrix Vmat(1,m,1,n)
  !! Vmat = mat;
  objective_function_value f

PROCEDURE_SECTION
  sing_val_decomp singval = singval_decomp(mat);
  dmatrix u = singval.get_u();
  dvector w = singval.get_w();
  dmatrix v = singval.get_v();
  dmatrix s(1,n,1,n);
  s.initialize();
  for(int i=1;i<=n;i++)
  {
    s(i,i)=w(i);
  }
  test = 1.0 + norm2(u*s*trans(v)-mat);
  f=square(norm2(Vmat)-norm2(u));

REPORT_SECTION
  report << "#test:" << endl;
  report << test << endl;

