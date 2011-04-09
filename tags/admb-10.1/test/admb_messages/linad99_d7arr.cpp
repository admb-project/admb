/**
 * Tests errors for "d6_array& d7_array::operator ( ) (int i)"
 */
TEST_F(test_admb_messages, linad99_d7arr_01)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    d6_array d6a1 = d7a(1);
    d6_array d6a0 = d7a(0);
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
 * Tests errors for "d6_array& d7_array::operator ( ) (int i)"
 */
TEST_F(test_admb_messages, linad99_d7arr_02)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    d6_array d6a5 = d7a(5);
    d6_array d6a6 = d7a(6);
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
 * Tests errors for "d6_array& d7_array::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_d7arr_03)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    d6_array d6a1 = d7a[1];
    d6_array d6a0 = d7a[0];
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
 * Tests errors for "d6_array& d7_array::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_d7arr_04)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    d6_array d6a5 = d7a[5];
    d6_array d6a6 = d7a[6];
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
 * Tests errors for "d5_array& d7_array::operator ( ) (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_d7arr_05)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    d5_array d5a0 = d7a(0, -1);
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
 * Tests errors for "d5_array& d7_array::operator ( ) (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_d7arr_06)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    d5_array d5a6 = d7a(6, -1);
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
 * Tests errors for "d4_array& d7_array::operator ( ) (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_d7arr_07)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    d4_array d4a0 = d7a(0, -1, -1);
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
 * Tests errors for "d4_array& d7_array::operator ( ) (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_d7arr_08)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    d4_array d4a6 = d7a(6, -1, -1);
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
 * Tests errors for "d3_array& d7_array::operator ( ) (int i, int j, int k, int l)"
 */
TEST_F(test_admb_messages, linad99_d7arr_09)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    d3_array d3a0 = d7a(0, -1, -1, -1);
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
 * Tests errors for "d3_array& d7_array::operator ( ) (int i, int j, int k, int l)"
 */
TEST_F(test_admb_messages, linad99_d7arr_10)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    d3_array d3a6 = d7a(6, -1, -1, -1);
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
 * Tests errors for "dmatrix& d7_array::operator ( ) (int i, int j, int k, int l, int m)"
 */
TEST_F(test_admb_messages, linad99_d7arr_11)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dmatrix m0 = d7a(0, -1, -1, -1, -1);
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
 * Tests errors for "dmatrix& d7_array::operator ( ) (int i, int j, int k, int l, int m)"
 */
TEST_F(test_admb_messages, linad99_d7arr_12)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dmatrix m0 = d7a(6, -1, -1, -1, -1);
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
 * Tests errors for "dvector& d7_array::operator ( ) (int i, int j, int k, int l, int m, int n)"
 */
TEST_F(test_admb_messages, linad99_d7arr_13)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvector v0 = d7a(0, -1, -1, -1, -1, -1);
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
 * Tests errors for "dvector& d7_array::operator ( ) (int i, int j, int k, int l, int m, int n)"
 */
TEST_F(test_admb_messages, linad99_d7arr_14)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    dvector v6 = d7a(6, -1, -1, -1, -1, -1);
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
 * Tests errors for "double& d7_array::operator ( ) (int i, int j, int k, int l, int m, int n, int _p)"
 */
TEST_F(test_admb_messages, linad99_d7arr_15)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    double d0 = d7a(0, -1, -1, -1, -1, -1, -1);
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
 * Tests errors for "double& d7_array::operator ( ) (int i, int j, int k, int l, int m, int n, int _p)"
 */
TEST_F(test_admb_messages, linad99_d7arr_16)
{
  d7_array d7a;
  d7a.allocate(1, 5);
  try
  {
    double d6 = d7a(6, -1, -1, -1, -1, -1, -1);
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
