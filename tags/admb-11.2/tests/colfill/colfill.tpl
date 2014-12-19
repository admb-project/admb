DATA_SECTION
  init_matrix dat(1,3,1,2);

PARAMETER_SECTION
  init_number x;

  matrix Mat1(1,3,1,2);
  //Just uncomment this and try compiling
  //with –r flag
  //random_effects_vector rx(1,2);
  objective_function_value ff;

PROCEDURE_SECTION
  cout << dat << endl;
  ff = 0;
  Mat1.colfill(1,column(dat,1));  //fill Mat1 column 1 with dat column 1
  //ff =  norm2(rx);
  ff += -1*square(x);

REPORT_SECTION
  cout<<Mat1<<endl;
