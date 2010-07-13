#include <admodel.h>
/**
 * Tests errors for "adstring& adstring_array::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_01)
{
  param_init_vector v(1, 5);
  try
  {
  }
  catch (const int exit_code)
  {
    const int expected_exit_code = admb::ARRAY_BOUNDS_ERROR;
    if (exit_code == expected_exit_code)
    {
      SUCCEED();
    }
    else
    {
      FAIL();
    }
  }
}
