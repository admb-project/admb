DATA_SECTION
  dll_int n

PARAMETER_SECTION
  dll_init_vector x(1,n)
  dll_number output
  objective_function_value f

PROCEDURE_SECTION
  f = square(x(1)-1.0);
  for (int i=1; i<n; i++)
  {
    f += square(x(i+1)-x(i));
  }
  output = f;
