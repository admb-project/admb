DATA_SECTION
  init_matrix training_inputs(1,7,1,3)
  init_vector training_outputs(1,7)

PARAMETER_SECTION
  init_matrix weights_layer1(1,3,1,4);
  init_vector weights_layer2(1,4);
  objective_function_value f

PROCEDURE_SECTION
  dvar_matrix outputs_layer1(1,7,1,4);
  outputs_layer1 = training_inputs * weights_layer1;

  dvar_matrix outputs_layer1b(1,7,1,4);
  for (int i = 1; i <= 7; ++i)
  {
    for (int j = 1; j <= 4; ++j)
    {
      outputs_layer1b(i, j) = 1.0 / (1.0 + mfexp(-outputs_layer1(i, j)));
    }
  }

  dvar_vector outputs_layer2(1,7);
  outputs_layer2 = outputs_layer1b * weights_layer2;

  dvar_vector outputs_layer2b(1,7);
  for (int i = 1; i <= 7; ++i)
  {
    outputs_layer2b(i) = 1.0 / (1.0 + mfexp(-outputs_layer2(i)));
  }

  f = norm2(outputs_layer2b - training_outputs); 

REPORT_SECTION
  dvar_matrix outputs_layer1(1,7,1,4);
  outputs_layer1 = training_inputs * weights_layer1;
  for (int i = 1; i <= 7; ++i)
  {
    for (int j = 1; j <= 4; ++j)
    {
      outputs_layer1(i, j) = 1.0 / (1.0 + mfexp(-outputs_layer1(i, j)));
    }
  }
  dvar_vector outputs_layer2(1,7);
  outputs_layer2 = outputs_layer1 * weights_layer2;
  for (int i = 1; i <= 7; ++i)
  {
    outputs_layer2(i) = 1.0 / (1.0 + mfexp(-outputs_layer2(i)));
  }
  for (int i = 1; i <= 7; ++i)
  {
    for (int j = 1; j <= 3; ++j)
    {
      report << training_inputs(i,j);
      if (j != 3)
      {
        report << ", ";
      }
      else
      {
        report << "-> ";
      }
    }
    report << "Actual: " << outputs_layer2(i) << " Expected: " << training_outputs(i) << endl;
  }
