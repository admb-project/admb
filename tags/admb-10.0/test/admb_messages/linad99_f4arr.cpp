/**
 * Tests errors for "dvar3_array& dvar4_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_dvar4arr_01)
{
  dvar4_array dvar4a;
  dvar4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dvar3_array dvar4a1 = dvar4a(1);
    dvar3_array dvar4a0 = dvar4a(0);
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
 * Tests errors for "dvar3_array& dvar4_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_dvar4arr_02)
{
  dvar4_array dvar4a;
  dvar4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dvar3_array dvar4a5 = dvar4a(5);
    dvar3_array dvar4a6 = dvar4a(6);
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
 * Tests errors for "dvar3_array& dvar4_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_dvar4arr_03)
{
  dvar4_array dvar4a;
  dvar4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dvar3_array dvar4a1 = dvar4a[1];
    dvar3_array dvar4a0 = dvar4a[0];
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
 * Tests errors for "dvar3_array& dvar4_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_dvar4arr_04)
{
  dvar4_array dvar4a;
  dvar4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dvar3_array dvar4a5 = dvar4a[5];
    dvar3_array dvar4a6 = dvar4a[6];
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
 * Tests errors for "dvar_matrix& dvar4_array::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_dvar4arr_05)
{
  dvar4_array dvar4a;
  dvar4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dvar_matrix dvar4a0 = dvar4a(0, 1);
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
 * Tests errors for "dvar_matrix& dvar4_array::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_dvar4arr_06)
{
  dvar4_array dvar4a;
  dvar4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dvar_matrix dvar4a0 = dvar4a(6, 1);
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
 * Tests errors for "dvar_vector& dvar4_array::operator() (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_dvar4arr_07)
{
  dvar4_array dvar4a;
  dvar4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dvar_vector dvar4a0 = dvar4a(0, 1, 1);
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
 * Tests errors for "dvar_vector& dvar4_array::operator() (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_dvar4arr_08)
{
  dvar4_array dvar4a;
  dvar4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    dvar_vector dvar4a0 = dvar4a(6, 1, 1);
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
 * Tests errors for "prevariable& dvar4_array::operator() (int i, int j, int k, int l)"
 */
TEST_F(test_admb_messages, linad99_dvar4arr_09)
{
  dvar4_array dvar4a;
  dvar4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    prevariable dvar4a0 = dvar4a(0, 1, 1, 1);
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
 * Tests errors for "prevariable& dvar4_array::operator() (int i, int j, int k, int l)"
 */
TEST_F(test_admb_messages, linad99_dvar4arr_10)
{
  dvar4_array dvar4a;
  dvar4a.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    prevariable dvar4a0 = dvar4a(6, 1, 1, 1);
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
