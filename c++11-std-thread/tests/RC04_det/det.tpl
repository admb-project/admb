// This is used to test the following functions:
// 
// dvariable det(const dvar_matrix & aa);
// double det(_CONST dmatrix & m1);

DATA_SECTION
  int n
 !! n=10;
 matrix M(1,n,1,n)
 !! random_number_generator rng(177);
 !! M.fill_randn(rng);
PARAMETER_SECTION
 init_matrix VM(1,n,1,n)
 !! VM=M;
 objective_function_value f
PROCEDURE_SECTION
 f=square(det(VM)-1.0)+det(M);
