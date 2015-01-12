/**
 * Tests errors for "dvar4_array& dvar5_array::operator () (int i)"
 */
TEST_F(test_admb_messages, linad99_f5arr_01)
{
  dvar5_array m;
  m.allocate(1, 5);
  try
  {
    dvar4_array m1 = m(1);
    dvar4_array m0 = m(0);
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
 * Tests errors for "dvar4_array& dvar5_array::operator () (int i)"
 */
TEST_F(test_admb_messages, linad99_f5arr_02)
{
  dvar5_array m;
  m.allocate(1, 5);
  try
  {
    dvar4_array m5 = m(5);
    dvar4_array m6 = m(6);
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
 * Tests errors for "dvar4_array& dvar5_array::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_f5arr_03)
{
  dvar5_array m;
  m.allocate(1, 5);
  try
  {
    dvar4_array m1 = m[1];
    dvar4_array m0 = m[0];
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
 * Tests errors for "dvar4_array& dvar5_array::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_f5arr_04)
{
  dvar5_array m;
  m.allocate(1, 5);
  try
  {
    dvar4_array m5 = m[5];
    dvar4_array m6 = m[6];
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
 * Tests errors for "dvar3_array& dvar5_array::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_f5arr_05)
{
  dvar5_array m;
  m.allocate(1, 5);
  try
  {
    dvar3_array m0 = m(0, -1);
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
 * Tests errors for "dvar3_array& dvar5_array::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_f5arr_06)
{
  dvar5_array m;
  m.allocate(1, 5);
  try
  {
    dvar3_array m6 = m(6, -1);
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
 * Tests errors for "dvar_matrix& dvar5_array::operator () (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_f5arr_07)
{
  dvar5_array m;
  m.allocate(1, 5);
  try
  {
    dvar_matrix m0 = m(0, -1, -1);
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
 * Tests errors for "dvar_matrix& dvar5_array::operator () (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_f5arr_08)
{
  dvar5_array m;
  m.allocate(1, 5);
  try
  {
    dvar_matrix m6 = m(6, -1, -1);
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
 * Tests errors for "dvar_vector& dvar5_array::operator () (int i, int j, int k, int l)"
 */
TEST_F(test_admb_messages, linad99_f5arr_09)
{
  dvar5_array m;
  m.allocate(1, 5);
  try
  {
    dvar_vector m0 = m(0, -1, -1, -1);
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
 * Tests errors for "dvar_vector& dvar5_array::operator () (int i, int j, int k, int l)"
 */
TEST_F(test_admb_messages, linad99_f5arr_010)
{
  dvar5_array m;
  m.allocate(1, 5);
  try
  {
    dvar_vector m6 = m(6, -1, -1, -1);
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
 * Tests errors for "prevariable& dvar6_array::operator () (int i, int j, int k, int l, int m)"
 */
TEST_F(test_admb_messages, linad99_f5arr_11)
{
  dvar5_array m;
  m.allocate(1, 5);
  try
  {
    prevariable m0 = m(0, -1, -1, -1, -1);
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
 * Tests errors for "prevariable& dvar6_array::operator () (int i, int j, int k, int l, int m)"
 */
TEST_F(test_admb_messages, linad99_f5arr_012)
{
  dvar5_array m;
  m.allocate(1, 5);
  try
  {
    prevariable m6 = m(6, -1, -1, -1, -1);
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
