DATA_SECTION

PARAMETER_SECTION
  init_bounded_number mu(-5.0,5.0) 
  random_effects_vector u(1,5,2)
  objective_function_value g    

PROCEDURE_SECTION
  //test cases df1b2vector * df1b2matrix
  f1();
  f2();
  f3();
  f4();
  f5();
  f6();

SEPARABLE_FUNCTION void f1()
  dvar_vector v14(1, 4);
  for (int i = 1; i <= 4; ++i)
  {
    v14(i) = i;
  }
  dvar_matrix m1414(1, 4, 1, 4);
  for (int i = 1; i <= 4; ++i)
  {
    for (int j = 1; j <= 4; ++j)
    {
      m1414(i, j) = j;
    }
  }
  dvar_vector mv14 = v14 * m1414;
  assert(int(value(mv14(1))) == 10);
  assert(int(value(mv14(2))) == 20);
  assert(int(value(mv14(3))) == 30);
  assert(int(value(mv14(4))) == 40);

SEPARABLE_FUNCTION void f2()
  dvar_vector v24(2, 4);
  for (int i = 2; i <= 4; ++i)
  {
    v24(i) = i;
  }
  dvar_matrix m2456(2, 4, 5, 6);
  for (int i = 2; i <= 4; ++i)
  {
    for (int j = 5; j <= 6; ++j)
    {
      m2456(i, j) = j;
    }
  }
  dvar_vector mv24 = v24 * m2456;
  assert(int(value(mv24(5))) == 45);
  assert(int(value(mv24(6))) == 54);

SEPARABLE_FUNCTION void f3()
  dvar_vector v14(1, 4);
  for (int i = 1; i <= 4; ++i)
  {
    v14(i) = i;
  }
  dmatrix m1414(1, 4, 1, 4);
  for (int i = 1; i <= 4; ++i)
  {
    for (int j = 1; j <= 4; ++j)
    {
      m1414(i, j) = j;
    }
  }
  dvar_vector mv14 = v14 * m1414;
  assert(int(value(mv14(1))) == 10);
  assert(int(value(mv14(2))) == 20);
  assert(int(value(mv14(3))) == 30);
  assert(int(value(mv14(4))) == 40);

SEPARABLE_FUNCTION void f4()
  dvar_vector v24(2, 4);
  for (int i = 2; i <= 4; ++i)
  {
    v24(i) = i;
  }
  dmatrix m2456(2, 4, 5, 6);
  for (int i = 2; i <= 4; ++i)
  {
    for (int j = 5; j <= 6; ++j)
    {
      m2456(i, j) = j;
    }
  }
  dvar_vector mv24 = v24 * m2456;
  assert(int(value(mv24(5))) == 45);
  assert(int(value(mv24(6))) == 54);

SEPARABLE_FUNCTION void f5()
  dvector v14(1, 4);
  for (int i = 1; i <= 4; ++i)
  {
    v14(i) = i;
  }
  dvar_matrix m1414(1, 4, 1, 4);
  for (int i = 1; i <= 4; ++i)
  {
    for (int j = 1; j <= 4; ++j)
    {
      m1414(i, j) = j;
    }
  }
  dvar_vector mv14 = v14 * m1414;
  assert(int(value(mv14(1))) == 10);
  assert(int(value(mv14(2))) == 20);
  assert(int(value(mv14(3))) == 30);
  assert(int(value(mv14(4))) == 40);

SEPARABLE_FUNCTION void f6()
  dvector v24(2, 4);
  for (int i = 2; i <= 4; ++i)
  {
    v24(i) = i;
  }
  dvar_matrix m2456(2, 4, 5, 6);
  for (int i = 2; i <= 4; ++i)
  {
    for (int j = 5; j <= 6; ++j)
    {
      m2456(i, j) = j;
    }
  }
  dvar_vector mv24 = v24 * m2456;
  assert(int(value(mv24(5))) == 45);
  assert(int(value(mv24(6))) == 54);

GLOBALS_SECTION
  #include <cassert>
