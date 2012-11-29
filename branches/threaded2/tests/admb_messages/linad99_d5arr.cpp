/**
 * Tests errors for "d4_array& d5_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_d5arr_01)
{
  d5_array d5a;
  d5a.allocate(1, 5);
  try
  {
    d4_array d5a1 = d5a(1);
    d4_array d5a0 = d5a(0);
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
 * Tests errors for "d4_array& d5_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_d5arr_02)
{
  d5_array d5a;
  d5a.allocate(1, 5);
  try
  {
    d4_array d5a5 = d5a(5);
    d4_array d5a6 = d5a(6);
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
 * Tests errors for "d4_array& d5_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_d5arr_03)
{
  d5_array d5a;
  d5a.allocate(1, 5);
  try
  {
    d4_array d5a1 = d5a[1];
    d4_array d5a0 = d5a[0];
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
 * Tests errors for "d4_array& d5_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_d5arr_04)
{
  d5_array d5a;
  d5a.allocate(1, 5);
  try
  {
    d4_array d5a5 = d5a[5];
    d4_array d5a6 = d5a[6];
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
 * Tests errors for "d3_array& d5_array::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_d5arr_05)
{
  d5_array d5a;
  d5a.allocate(1, 5);
  try
  {
    d3_array d5a0 = d5a(0, 1);
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
 * Tests errors for "d3_array& d5_array::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_d5arr_06)
{
  d5_array d5a;
  d5a.allocate(1, 5);
  try
  {
    d3_array d5a6 = d5a(6, 0);
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
 * Tests errors for "dmatrix& d5_array::operator() (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_d5arr_07)
{
  d5_array d5a;
  d5a.allocate(1, 5);
  try
  {
    dmatrix d5a0 = d5a(0, 1, 1);
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
 * Tests errors for "dmatrix& d5_array::operator() (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_d5arr_08)
{
  d5_array d5a;
  d5a.allocate(1, 5);
  try
  {
    dmatrix d5a6 = d5a(6, 0, 0);
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
 * Tests errors for "dvector& d5_array::operator() (int i, int j, int k, int l)"
 */
TEST_F(test_admb_messages, linad99_d5arr_09)
{
  d5_array d5a;
  d5a.allocate(1, 5);
  try
  {
    dvector d5a0 = d5a(0, 1, 1, 1);
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
 * Tests errors for "dvector& d5_array::operator() (int i, int j, int k, int l)"
 */
TEST_F(test_admb_messages, linad99_d5arr_10)
{
  d5_array d5a;
  d5a.allocate(1, 5);
  try
  {
    dvector d5a6 = d5a(6, 0, 0, 0);
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
 * Tests errors for "double& d5_array::operator() (int i, int j, int k, int l, int m)"
 */
TEST_F(test_admb_messages, linad99_d5arr_11)
{
  d5_array d5a;
  d5a.allocate(1, 5);
  try
  {
    double d5a0 = d5a(0, 1, 1, 1, 1);
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
 * Tests errors for "double& d5_array::operator() (int i, int j, int k, int l, int m)"
 */
TEST_F(test_admb_messages, linad99_d5arr_12)
{
  d5_array d5a;
  d5a.allocate(1, 5);
  try
  {
    double d5a6 = d5a(6, 0, 0, 0, 0);
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
