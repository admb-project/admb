// This is used to test the following functions:
// 
// dvar_matrix eigenvectors(_CONST dvar_matrix& m);
// dvar_vector eigenvalues(_CONST dvar_matrix& m);
// dvector eigenvalues(_CONST dmatrix& m);
// dmatrix eigenvectors(_CONST dmatrix& m);
DATA_SECTION
  int n
  !! n=5;
  matrix M(1,n,1,n)
  !! random_number_generator rng(132);
  !! M.fill_randn(rng);
  
PARAMETER_SECTION
  init_matrix VM(1,n,1,n)
  !! VM=M;
  objective_function_value f
PROCEDURE_SECTION
  f=norm2(eigenvectors(VM));
  f+=norm2(eigenvalues(VM));
  f+=norm2(eigenvectors(value(VM)));
  f+=norm2(eigenvalues(value(VM)));
  f+=square(norm2(VM));
