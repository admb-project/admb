DATA_SECTION
PARAMETER_SECTION
  init_bounded_number a(1,3)
  init_bounded_number b(1,3)
  init_bounded_number x(0.001,.999)
  random_effects_vector u(1,1)
  objective_function_value f
PROCEDURE_SECTION
  f+=square(replacement::incbet(a,b,x)-4.0+u(1));
  f+=square(u(1)-0.5);
  f+=square(a-2.0);
  f+=square(b-3.0);
  f+=square(x-5.0);

GLOBALS_SECTION
  #include <admodel.h>
  #include <df1b2fun.h>

  namespace replacement 
  {
    //df33tester.cpp:871
    df1b2variable incbet(const df1b2variable& _a,const df1b2variable& _b, const df1b2variable& _x);

    //df13tester.cpp:870
    dvariable incbet(const dvariable& _a,const dvariable& _b, const dvariable& _x);
  }
