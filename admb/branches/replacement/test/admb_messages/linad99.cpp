/**
 * Tests errors for "AD_LONG_INT& lvector::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_lvec1_01)
{
  lvector lv(1, 5);
  try
  {
    AD_LONG_INT lv1 = lv(1);
    AD_LONG_INT lv0 = lv(0);
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
 * Tests errors for "AD_LONG_INT& lvector::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_lvec1_02)
{
  lvector lv(1, 5);
  try
  {
    AD_LONG_INT lv5 = lv(5);
    AD_LONG_INT lv6 = lv(6);
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
 * Tests errors for "AD_LONG_INT& lvector::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_lvec1_03)
{
  lvector lv(1, 5);
  try
  {
    AD_LONG_INT lv1 = lv[1];
    AD_LONG_INT lv0 = lv[0];
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
 * Tests errors for "AD_LONG_INT& lvector::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_lvec1_04)
{
  lvector lv(1, 5);
  try
  {
    AD_LONG_INT lv5 = lv[5];
    AD_LONG_INT lv6 = lv[6];
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
 * Tests errors for "dvector extract_column(_CONST dmatrix& m, int j)"
 */
TEST_F(test_admb_messages, linad99_dmat6_01)
{
  dmatrix m(1, 5, 1, 5);
  try
  {
    dvector v1 = extract_column(m, 1);
    dvector v0 = extract_column(m, 0);
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
 * Tests errors for "dvector extract_row(_CONST dmatrix& m, int i)"
 */
TEST_F(test_admb_messages, linad99_dmat6_02)
{
  dmatrix m(1, 5, 1, 5);
  try
  {
    dvector v1 = extract_row(m, 1);
    dvector v0 = extract_row(m, 0);
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
 * Tests errors for "dvector& dmatrix::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_dmat_acc_01)
{
  dmatrix m(1, 5, 1, 5);
  try
  {
    dvector v1 = m[1];
    dvector v0 = m[0];
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
 * Tests errors for "dvector& dmatrix::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_dmat_acc_02)
{
  dmatrix m(1, 5, 1, 5);
  try
  {
    dvector v5 = m[5];
    dvector v6 = m[6];
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
 * Tests errors for "dvector& dmatrix::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_dmat8_01)
{
  dmatrix m(1, 5, 1, 5);
  try
  {
    dvector v1 = m(1);
    dvector v0 = m(0);
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
 * Tests errors for "dvector& dmatrix::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_dmat8_02)
{
  dmatrix m(1, 5, 1, 5);
  try
  {
    dvector v5 = m(5);
    dvector v6 = m(6);
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
 * Tests errors for "dmatrix& d3_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_01)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dmatrix d3a1 = d3a(1);
    dmatrix d3a0 = d3a(0);
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
 * Tests errors for "dmatrix& d3_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_02)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dmatrix d3a5 = d3a(5);
    dmatrix d3a6 = d3a(6);
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
 * Tests errors for "dmatrix& d3_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_03)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dmatrix d3a1 = d3a[1];
    dmatrix d3a0 = d3a[0];
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
 * Tests errors for "dmatrix& d3_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_04)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dmatrix d3a5 = d3a[5];
    dmatrix d3a6 = d3a[6];
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
 * Tests errors for "dvector& d3_array::operator() (int k, int i)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_05)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dvector v = d3a(0, 1);
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
 * Tests errors for "dvector& d3_array::operator() (int k, int i)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_06)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dvector v = d3a(6, 1);
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
 * Tests errors for "double& d3_array::operator() (int k, int i, int j)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_07)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    double d = d3a(0, 1, 1);
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
 * Tests errors for "double& d3_array::operator() (int k, int i, int j)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_08)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    double d = d3a(6, 1, 1);
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
