DATA_SECTION
  init_3iarray a(1,4,1,3,1,2)
  init_4iarray b(1,4,1,4,1,2,1,2)
  3iarray c
  4iarray d
  3iarray y(1,4,1,3,1,2)
  4iarray z(1,4,1,4,1,2,1,2)

PARAMETER_SECTION
  init_number x;
  objective_function_value objfun;

PROCEDURE_SECTION
  objfun += x*x;

FINAL_SECTION
  std::cout << a << '\n' << std::endl;
  std::cout << b << '\n' << std::endl;
  y.initialize();
  std::cout << y << '\n' << std::endl;
  z.initialize();
  std::cout << z << '\n' << std::endl;
