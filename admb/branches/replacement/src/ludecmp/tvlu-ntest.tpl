GLOBALS_SECTION
  #include "ntest.cpp"

DATA_SECTION
  int n
 !! n=25;
  matrix C(1,n,1,n)
  matrix Id(1,n,1,n)
 LOC_CALCS
  random_number_generator rng(873);
  C.fill_randn(rng);
  Id.initialize();
  for (int i=1;i<=n;i++)
    Id(i,i)=1.0;
PARAMETER_SECTION
  init_matrix A(1,n,1,n)
  objective_function_value f
PROCEDURE_SECTION
  cout << norm2(inv(A+C)*(A+C)-Id)<< endl;
  f=norm2(inv(A+C));

TOP_OF_MAIN_SECTION
  gradient_structure::set_MAX_NVAR_OFFSET(625);
