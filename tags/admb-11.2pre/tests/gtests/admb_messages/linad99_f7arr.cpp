/**
 * Tests errors for "dvar6_array& dvar7_array::operator ( ) (int i)"
 */
TEST_F(test_admb_messages, linad99_f7arr_01)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvar6_array d6a1 = d7a(1);
    dvar6_array d6a0 = d7a(0);
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "dvar6_array& dvar7_array::operator ( ) (int i)"
 */
TEST_F(test_admb_messages, linad99_f7arr_02)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvar6_array d6a5 = d7a(5);
    dvar6_array d6a6 = d7a(6);
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "dvar6_array& dvar7_array::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_f7arr_03)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvar6_array d6a1 = d7a[1];
    dvar6_array d6a0 = d7a[0];
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "dvar6_array& dvar7_array::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_f7arr_04)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvar6_array d6a5 = d7a[5];
    dvar6_array d6a6 = d7a[6];
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "dvar5_array& dvar7_array::operator ( ) (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_f7arr_05)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvar5_array d5a0 = d7a(0, -1);
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "dvar5_array& dvar7_array::operator ( ) (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_f7arr_06)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvar5_array d5a6 = d7a(6, -1);
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "dvar4_array& dvar7_array::operator ( ) (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_f7arr_07)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvar4_array d4a0 = d7a(0, -1, -1);
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "dvar4_array& dvar7_array::operator ( ) (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_f7arr_08)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvar4_array d4a6 = d7a(6, -1, -1);
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "dvar3_array& dvar7_array::operator ( ) (int i, int j, int k, int l)"
 */
TEST_F(test_admb_messages, linad99_f7arr_09)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvar3_array d3a0 = d7a(0, -1, -1, -1);
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "dvar3_array& dvar7_array::operator ( ) (int i, int j, int k, int l)"
 */
TEST_F(test_admb_messages, linad99_f7arr_10)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvar3_array d3a6 = d7a(6, -1, -1, -1);
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "dmatrix& dvar7_array::operator ( ) (int i, int j, int k, int l, int m)"
 */
TEST_F(test_admb_messages, linad99_f7arr_11)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvar_matrix m0 = d7a(0, -1, -1, -1, -1);
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "dmatrix& dvar7_array::operator ( ) (int i, int j, int k, int l, int m)"
 */
TEST_F(test_admb_messages, linad99_f7arr_12)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvar_matrix m0 = d7a(6, -1, -1, -1, -1);
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "dvector& dvar7_array::operator ( ) (int i, int j, int k, int l, int m, int n)"
 */
TEST_F(test_admb_messages, linad99_f7arr_13)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvar_vector v0 = d7a(0, -1, -1, -1, -1, -1);
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "dvector& dvar7_array::operator ( ) (int i, int j, int k, int l, int m, int n)"
 */
TEST_F(test_admb_messages, linad99_f7arr_14)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvar_vector v6 = d7a(6, -1, -1, -1, -1, -1);
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "double& dvar7_array::operator ( ) (int i, int j, int k, int l, int m, int n, int _p)"
 */
TEST_F(test_admb_messages, linad99_f7arr_15)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvariable d0 = d7a(0, -1, -1, -1, -1, -1, -1);
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
/**
 * Tests errors for "double& dvar7_array::operator ( ) (int i, int j, int k, int l, int m, int n, int _p)"
 */
TEST_F(test_admb_messages, linad99_f7arr_16)
{
  dvar7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvariable d6 = d7a(6, -1, -1, -1, -1, -1, -1);
  } 
  catch (const int exit_code)          
  {   
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
      return;
    }
  }
  FAIL();
}
