#include <gtest/gtest.h>

class test_idea: public ::testing::Test {};

TEST_F(test_idea, if_literal_double)
{
  if (1.0e-10)
  {
  }
  else
  {
    FAIL();
  }
  if (1.0e+10)
  {
  }
  else
  {
    FAIL();
  }
  if (-1.0e-10)
  {
  }
  else
  {
    FAIL();
  }
  if (-1.0e+10)
  {
  }
  else
  {
    FAIL();
  }
  if (0.0)
  {
    FAIL();
  }
  else
  {
  }
}
TEST_F(test_idea, if_double)
{
  double d = 1.0e-10;
  if (d)
  {
  }
  else
  {
    FAIL();
  }
  d = 1.0e+10;
  if (d)
  {
  }
  else
  {
    FAIL();
  }
  d = -1.0e-10;
  if (d)
  {
  }
  else
  {
    FAIL();
  }
  d = -1.0e+10;
  if (d)
  {
  }
  else
  {
    FAIL();
  }
  d = 0.0;
  if (d)
  {
    FAIL();
  }
  else
  {
  }
}
