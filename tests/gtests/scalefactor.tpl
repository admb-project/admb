DATA_SECTION
PARAMETER_SECTION
  init_vector x(1,2)
 !! x.set_scalefactor(100.);
  init_bounded_vector y(1,2,-5.0,5.0)
 !! y.set_scalefactor(50.);
  random_effects_vector u(1,2);
  objective_function_value f;
PROCEDURE_SECTION
  f=norm2(x-2.0)+norm2(u-1.0)+norm2(y-2.0)+norm2(x-u)+norm2(y-u);
