/**
 * Self test for array_bounds_error.
 */
TEST_F(test_admb_messages, selftest01)
{
  try
  {
    adstring message("message");
    adstring function("function");
    const int lower_bounds = 1;
    const int upper_bounds = 5;
    const int index = 0;
    admb::messages::array_bounds_error(message,
                                       function,
                                       lower_bounds,
                                       upper_bounds,
                                       index);
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
 * Tests for errors in "adstring adstring::operator()(int i, int j)"
 */
TEST_F(test_admb_messages, tools99_string1_01)
{
  adstring a = "12345";
  try
  { 
    adstring substring = a(0, 3);
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
 * Tests for errors in "adstring adstring::operator()(int i, int j)"
 */
TEST_F(test_admb_messages, tools99_string1_02)
{
  adstring a = "12345";
  try
  { 
    adstring substring = a(1, a.size() + 1);
  }
  catch (int exit_code)
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
 * Tests for errors in "adstring adstring::operator()(int i, int j)"
 */
TEST_F(test_admb_messages, tools99_string1_03)
{
  adstring a = "12345";
  try
  { 
    adstring substring = a(3, 2);
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
 * Tests for errors in "unsigned char & adstring::operator()(_CONST int i)"
 */
TEST_F(test_admb_messages, tools99_string1_04)
{
  adstring a = "12345";
  try
  { 
    adstring substring = a(1, a.size() + 1);
  }
  catch (int exit_code)
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
 * Tests for errors in "unsigned char & adstring::operator()(_CONST int i)"
 */
TEST_F(test_admb_messages, tools99_string1_05)
{
  adstring a = "12345";
  try
  { 
    unsigned char c = a(0);
  }
  catch (int exit_code)
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
 * Tests for errors in "unsigned char & adstring::operator()(_CONST int i)"
 */
TEST_F(test_admb_messages, tools99_string1_06)
{
  adstring a = "12345";
  try
  { 
    unsigned char c = a(6);
  }
  catch (int exit_code)
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
