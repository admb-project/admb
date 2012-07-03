// This is used to test the following functions:
// 
// df1b2variable ln_det(const df1b2matrix & m1);
DATA_SECTION
  init_int n
  init_matrix CM(1,n,1,n)
  matrix Id
  init_number cv
 !! Id=identity_matrix(1,n);
PARAMETER_SECTION
  init_matrix VCM(1,n,1,n)
  random_effects_matrix M(1,n,1,n)
  objective_function_value f
PROCEDURE_SECTION
  dvar_matrix S=M+VCM;
  f=square(ln_det(Id+S*trans(S)));
  f+=norm2(S-2.0*Id);
  f+=0.5*(norm2(VCM));
  f+=0.5*(norm2(M));
  f+=square(VCM(n,n-1)-10.0);
  f+=square(VCM(n,n-2)-15.0);

GLOBALS_SECTION
  #include <df1b2fun.h>
  #include <fvar.hpp>
  df1b2variable ln_det(const df1b2matrix & m1);
