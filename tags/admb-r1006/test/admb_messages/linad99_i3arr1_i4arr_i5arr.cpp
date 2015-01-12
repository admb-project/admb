/**
 * Tests errors for "imatrix& i3_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_i3arr1_01)
{
  i3_array m;
  m.allocate(1, 5);
  try
  {
    imatrix m1 = m(1);
    imatrix m0 = m(0);
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
 * Tests errors for "imatrix& i3_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_i3arr1_02)
{
  i3_array m;
  m.allocate(1, 5);
  try
  {
    imatrix m5 = m(5);
    imatrix m6 = m(6);
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
 * Tests errors for "imatrix& i3_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_i3arr1_03)
{
  i3_array m;
  m.allocate(1, 5);
  try
  {
    imatrix m1 = m[1];
    imatrix m0 = m[0];
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
 * Tests errors for "imatrix& i3_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_i3arr1_04)
{
  i3_array m;
  m.allocate(1, 5);
  try
  {
    imatrix m5 = m[5];
    imatrix m6 = m[6];
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
 * Tests errors for "ivector& imatrix::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_i3arr1_05)
{
  i3_array m;
  m.allocate(1, 5);
  try
  {
    ivector v0 = m(0, -1);
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
 * Tests errors for "ivector& imatrix::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_i3arr1_06)
{
  i3_array m;
  m.allocate(1, 5);
  try
  {
    ivector v6 = m(6, -1);
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
 * Tests errors for "int& imatrix::operator() (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_i3arr1_07)
{
  i3_array m;
  m.allocate(1, 5);
  try
  {
    int i0 = m(0, -1, -1);
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
 * Tests errors for "int& imatrix::operator() (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_i3arr1_08)
{
  i3_array m;
  m.allocate(1, 5);
  try
  {
    int i6 = m(6, -1, -1);
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
 * Tests errors for "i3_array& i4_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_i4arr_01)
{
  i4_array m;
  m.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    i3_array m1 = m(1);
    i3_array m0 = m(0);
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
 * Tests errors for "i3_array& i4_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_i4arr_02)
{
  i4_array m;
  m.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    i3_array m5 = m(5);
    i3_array m6 = m(6);
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
 * Tests errors for "i3_array& i4_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_i4arr_03)
{
  i4_array m;
  m.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    i3_array m1 = m[1];
    i3_array m0 = m[0];
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
 * Tests errors for "i3_array& i4_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_i4arr_04)
{
  i4_array m;
  m.allocate(1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    i3_array m5 = m[5];
    i3_array m6 = m[6];
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
 * Tests errors for "i4_array& i5_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_i5arr_01)
{
  i5_array m;
  m.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    i4_array m1 = m(1);
    i4_array m0 = m(0);
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
 * Tests errors for "i4_array& i5_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_i5arr_02)
{
  i5_array m;
  m.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    i4_array m5 = m(5);
    i4_array m6 = m(6);
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
 * Tests errors for "i4_array& i5_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_i5arr_03)
{
  i5_array m;
  m.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    i4_array m1 = m[1];
    i4_array m0 = m[0];
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
 * Tests errors for "i4_array& i5_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_i5arr_04)
{
  i5_array m;
  m.allocate(1, 5, 1, 5, 1, 5, 1, 5, 1, 5);
  try
  {
    i4_array m5 = m[5];
    i4_array m6 = m[6];
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
