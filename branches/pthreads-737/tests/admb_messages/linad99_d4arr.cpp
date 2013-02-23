/**
 * Tests errors for "d3_array& d4_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_d4arr_01)
{
  d4_array d4a;
  d4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    d3_array d4a1 = d4a(1);
    d3_array d4a0 = d4a(0);
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
 * Tests errors for "d3_array& d4_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_d4arr_02)
{
  d4_array d4a;
  d4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    d3_array d4a5 = d4a(5);
    d3_array d4a6 = d4a(6);
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
 * Tests errors for "d3_array& d4_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_d4arr_03)
{
  d4_array d4a;
  d4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    d3_array d4a1 = d4a[1];
    d3_array d4a0 = d4a[0];
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
 * Tests errors for "d3_array& d4_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_d4arr_04)
{
  d4_array d4a;
  d4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    d3_array d4a5 = d4a[5];
    d3_array d4a6 = d4a[6];
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
 * Tests errors for "dmatrix& d4_array::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_d4arr_05)
{
  d4_array d4a;
  d4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dmatrix d4a0 = d4a(0, 1);
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
 * Tests errors for "dmatrix& d4_array::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_d4arr_06)
{
  d4_array d4a;
  d4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dmatrix d4a0 = d4a(6, 1);
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
 * Tests errors for "dvector& d4_array::operator() (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_d4arr_07)
{
  d4_array d4a;
  d4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dvector d4a0 = d4a(0, 1, 1);
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
 * Tests errors for "dvector& d4_array::operator() (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_d4arr_08)
{
  d4_array d4a;
  d4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dvector d4a0 = d4a(6, 1, 1);
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
 * Tests errors for "double& d4_array::operator() (int i, int j, int k, int l)"
 */
TEST_F(test_admb_messages, linad99_d4arr_09)
{
  d4_array d4a;
  d4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    double d4a0 = d4a(0, 1, 1, 1);
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
 * Tests errors for "double& d4_array::operator() (int i, int j, int k, int l)"
 */
TEST_F(test_admb_messages, linad99_d4arr_10)
{
  d4_array d4a;
  d4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    double d4a0 = d4a(6, 1, 1, 1);
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
