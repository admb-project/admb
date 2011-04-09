// This is used to test the following functions:
// 
//   df1b2vector solve(const df1b2matrix & aa, const df1b2vector & z,
//      df1b2variable & ln_unsigned_det,
//      const df1b2variable & _sign);
//
// test should have a value of 1.0
DATA_SECTION
  init_int n
  init_matrix CM(1,n,1,n)
  init_vector cv(1,n)
  number test
PARAMETER_SECTION
  init_number lndet
  init_number sgn
  init_matrix M(1,n,1,n)
  random_effects_vector u(1,n)
  objective_function_value f
PROCEDURE_SECTION
  test = 1.0 + value(norm2((M+CM)*solve(M+CM,u,lndet,sgn)-u));
  f=0.5*norm2(cv-solve(M+CM,u,lndet,sgn));
  f+=0.5*norm2(u);
  f+=0.5*norm2(M);
  f+=0.5*square(lndet);
  f+=0.5*square(sgn);

GLOBALS_SECTION
  #include <df1b2fun.h>
  df1b2vector solve(const df1b2matrix & aa, const df1b2vector & z,
        df1b2variable & ln_unsigned_det,
        const df1b2variable & _sign);

REPORT_SECTION
  report << "#test" << endl;
  report << test << endl;
