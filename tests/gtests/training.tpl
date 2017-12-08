DATA_SECTION
  init_vector training_inputs(1,12)
  init_vector training_outputs(1,4)

PARAMETER_SECTION
  init_number weight1
  init_number weight2
  init_number weight3
  vector output(1,4)
  objective_function_value f

PROCEDURE_SECTION
  int j = 1;
  for (int i = 1; i <= 4; ++i)
  {
    dvariable sum = training_inputs(j) * weight1 + training_inputs(j + 1) * weight2 + training_inputs(j + 2) * weight3;
    output(i) = 1.0 / (1.0 + exp(-sum));

    cout << training_inputs(j) << ", "  << training_inputs(j + 1) << ", "  << training_inputs(j + 2) << " -> "  << value(output(i)) << endl;
    j += 3;
  }
  f = norm2(output - training_outputs); 

REPORT_SECTION
  dvar_vector think(1,5);
  int j = 1;
  for (int i = 1; i <= 4; ++i)
  {
    dvariable sum = training_inputs(j) * weight1 + training_inputs(j + 1) * weight2 + training_inputs(j + 2) * weight3;
    dvariable output = 1.0 / (1.0 + exp(-sum));

    report << training_inputs(j) << ", "  << training_inputs(j + 1) << ", "  << training_inputs(j + 2) << " -> "  << value(output) << endl;
    j += 3;
  }
  dvariable new_situation = 1.0 * weight1 + 0.0 * weight2 +  0.0 * weight3;
  dvariable new_output  = 1.0 / (1.0 + exp(-new_situation));
  report << "1, 0, 0 -> "  << new_output << endl;
