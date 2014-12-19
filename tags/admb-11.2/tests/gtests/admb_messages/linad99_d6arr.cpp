/**
 * Tests errors for "d5_array& d6_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_d6arr_01)
{
  d6_array d6a;
  d6a.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    d5_array d6a0 = d6a(0);
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
 * Tests errors for "d5_array& d6_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_d6arr_02)
{
  d6_array d6a;
  d6a.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    d5_array d6a6 = d6a(6);
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
 * Tests errors for "d5_array& d6_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_d6arr_03)
{
  d6_array d6a;
  d6a.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    d5_array d6a6 = d6a[0];
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
 * Tests errors for "d5_array& d6_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_d6arr_04)
{
  d6_array d6a;
  d6a.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    d5_array d6a6 = d6a[6];
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
 * Tests errors for "d4_array& d6_array::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_d6arr_05)
{
  d6_array d6a;
  d6a.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    d4_array d6a0 = d6a(0, 1);
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
 * Tests errors for "d4_array& d6_array::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_d6arr_06)
{
  d6_array d6a;
  d6a.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    d4_array d6a0 = d6a(6, 1);
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
 * Tests errors for "d3_array& d6_array::operator() (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_d6arr_07)
{
  d6_array d6a;
  d6a.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    d3_array d6a0 = d6a(0, 1, 1);
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
 * Tests errors for "d3_array& d6_array::operator() (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_d6arr_08)
{
  d6_array d6a;
  d6a.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    d3_array d6a6 = d6a(6, 0, 0);
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
 * Tests errors for "dmatrix& d6_array::operator() (int i, int j, int k, int l)"
 */
TEST_F(test_admb_messages, linad99_d6arr_09)
{
  d6_array d6a;
  d6a.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dmatrix d6a0 = d6a(0, 1, 1, 1);
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
 * Tests errors for "dmatrix& d6_array::operator() (int i, int j, int k, int l)"
 */
TEST_F(test_admb_messages, linad99_d6arr_10)
{
  d6_array d6a;
  d6a.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dmatrix d6a6 = d6a(6, 0, 0, 0);
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
 * Tests errors for "dvector& d6_array::operator() (int i, int j, int k, int l, int m)"
 */
TEST_F(test_admb_messages, linad99_d6arr_11)
{
  d6_array d6a;
  d6a.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dvector d6a0 = d6a(0, 1, 1, 1, 1);
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
 * Tests errors for "dvector& d6_array::operator() (int i, int j, int k, int l, int m)"
 */
TEST_F(test_admb_messages, linad99_d6arr_12)
{
  d6_array d6a;
  d6a.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dvector d6a6 = d6a(6, 0, 0, 0, 0);
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
 * Tests errors for "double& d6_array::operator() (int i, int j, int k, int l, int m, int n)"
 */
TEST_F(test_admb_messages, linad99_d6arr_13)
{
  d6_array d6a;
  d6a.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    double d6a0 = d6a(0, 1, 1, 1, 1, 1);
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
 * Tests errors for "double& d6_array::operator() (int i, int j, int k, int l, int m, int n)"
 */
TEST_F(test_admb_messages, linad99_d6arr_14)
{
  d6_array d6a;
  d6a.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    double d6a6 = d6a(6, 0, 0, 0, 0, 0);
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
