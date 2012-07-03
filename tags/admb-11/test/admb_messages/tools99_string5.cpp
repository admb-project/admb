/**
 * Tests errors for "adstring& adstring_array::operator [] (int i)"
 */
TEST_F(test_admb_messages, tools99_string5_01)
{
  adstring_array a(1, 4);
  try
  {
    adstring a1 = a[1];
    adstring a0 = a[0];
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
 * Tests errors for "adstring& adstring_array::operator [] (int i)"
 */
TEST_F(test_admb_messages, tools99_string5_02)
{
  adstring_array a(1, 4);
  try
  {
    adstring a4 = a[4];
    adstring a0 = a[5];
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
 * Tests errors for "adstring& adstring_array::operator () (int i)"
 */
TEST_F(test_admb_messages, tools99_string5_03)
{
  adstring_array a(1, 4);
  try
  {
    adstring a1 = a(1);
    adstring a0 = a(0);
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
