/**
 * Tests errors for "lvector& lmatrix::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_lmat1_lmat2_lmat4_01)
{
  lmatrix m(1, 5, 1, 5);
  try
  {
    lvector v1 = m(1);
    lvector v0 = m(0);
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
 * Tests errors for "lvector& lmatrix::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_lmat1_lmat2_lmat4_02)
{
  lmatrix m(1, 5, 1, 5);
  try
  {
    lvector v5 = m(5);
    lvector v6 = m(6);
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
 * Tests errors for "AD_LONG_INT& lmatrix::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_lmat1_lmat2_lmat4_03)
{
  lmatrix m(1, 5, 1, 5);
  try
  {
    AD_LONG_INT& value = m(0, -1);
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
 * Tests errors for "AD_LONG_INT& lmatrix::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_lmat1_lmat2_lmat4_04)
{
  lmatrix m(1, 5, 1, 5);
  try
  {
    AD_LONG_INT& value = m(6, -1);
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
 * Tests errors for "AD_LONG_INT& lmatrix::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_lmat1_lmat2_lmat4_05)
{
  lmatrix m(1, 5, 1, 5);
  try
  {
    AD_LONG_INT& value = m(1, 0);
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
 * Tests errors for "AD_LONG_INT& lmatrix::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_lmat1_lmat2_lmat4_06)
{
  lmatrix m(1, 5, 1, 5);
  try
  {
    AD_LONG_INT& value = m(1, 6);
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
 * Tests errors for "lvector& lmatrix::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_lmat1_lmat2_lmat4_07)
{
  lmatrix m(1, 5, 1, 5);
  try
  {
    lvector v1 = m[1];
    lvector v0 = m[0];
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
 * Tests errors for "lvector& lmatrix::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_lmat1_lmat2_lmat4_08)
{
  lmatrix m(1, 5, 1, 5);
  try
  {
    lvector v5 = m[5];
    lvector v6 = m[6];
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
