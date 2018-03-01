#include <gtest/gtest.h>
#include "fvar.hpp"

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_arr_link: public ::testing::Test {};

TEST_F(test_arr_link, arr_remove_null)
{
  void arr_remove(arr_link** pptr);
  ASSERT_DEATH(arr_remove(NULL), "Assertion");
}
TEST_F(test_arr_link, arr_remove)
{
  ad_exit=&test_ad_exit;
  arr_link** pptr = new arr_link*[1];
  pptr[0] = NULL;
  try
  {
    void arr_remove(arr_link** pptr);
    arr_remove(pptr);
  }
  catch (const int exit_code)
  {
    delete [] pptr;
    pptr = NULL;

    const int expected_exit_code = 23;
    if (exit_code == expected_exit_code)
    {
      return;
    }
  }
  FAIL();
}
TEST_F(test_arr_link, dvar_vector1to4)
{
  gradient_structure gs;

  dvar_vector v(1, 4);

  arr_link* last = gradient_structure::ARR_LIST1->get_last();

  ASSERT_TRUE(last->get_prev() == NULL);
  ASSERT_TRUE(last->get_next() == NULL);
  ASSERT_EQ(last->get_size(), sizeof(double_and_int) * 4);
  ASSERT_EQ(last->get_offset(), 0);
  ASSERT_EQ(last->get_status(), 1);
}
