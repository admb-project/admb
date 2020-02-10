#include <gtest/gtest.h>
#include <fvar.hpp>
#include <cmath>

class test_dvar3_array: public ::testing::Test {};

TEST_F(test_dvar3_array, mean_null)
{
  gradient_structure gs;
  dvar3_array a;
  ASSERT_EQ(0, size_count(a));
  ASSERT_ANY_THROW(
    mean(a);
  );
}
TEST_F(test_dvar3_array, uiostream)
{
  gradient_structure gs;

  dvar3_array a(1, 2, 1, 2, 1, 2);

  double d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        a(i, j, k) = d;
        d += 2.0;
      }
    }
  }

  uostream uos("uos.txt");
  uos << a;
  uos.close();

  dvar3_array ret(1, 2, 1, 2, 1, 2);

  uistream uis("uos.txt");
  uis >> ret;
  uis.close();

  d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        ASSERT_DOUBLE_EQ(value(a(i, j, k)), value(ret(i, j, k)));
        d += 2.0;
      }
    }
  }
}

TEST_F(test_dvar3_array, mean)
{
  gradient_structure gs;
  dvar3_array a(1, 2, 1, 2, 1, 2);
  a = 1;
  ASSERT_EQ(8, size_count(a));
  ASSERT_DOUBLE_EQ(8, value(sum(a)));
  dvariable v = mean(a);
  ASSERT_DOUBLE_EQ(1, value(v));
}
TEST_F(test_dvar3_array, mean_double)
{
  gradient_structure gs;
  dvar3_array a(1, 2, 1, 2, 1, 2);
  a = 0.5;
  ASSERT_EQ(8, size_count(a));
  ASSERT_DOUBLE_EQ(4, value(sum(a)));
  dvariable v = mean(a);
  ASSERT_DOUBLE_EQ(0.5, value(v));
}
TEST_F(test_dvar3_array, square)
{
  gradient_structure gs;
  dvar3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  dvar3_array result = square(a);
  ASSERT_DOUBLE_EQ(1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(4, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(9, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(16, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(25, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(36, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(49, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(64, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, division)
{
  gradient_structure gs;
  dvar3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  dvariable d;
  d = 1;
  dvar3_array result = d / a;
  ASSERT_DOUBLE_EQ(1.0 / 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, division2)
{
  gradient_structure gs;
  d3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  dvariable d;
  d = 1;
  dvar3_array result = d / a;
  ASSERT_DOUBLE_EQ(1.0 / 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, division3)
{
  gradient_structure gs;
  dvar3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  double d;
  d = 1;
  dvar3_array result = d / a;
  ASSERT_DOUBLE_EQ(1.0 / 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(1.0 / 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(1.0 / 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, value)
{
  gradient_structure gs;
  dvar3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  double d;
  d = 1;
  d3_array result = value(a);
  ASSERT_DOUBLE_EQ(1, result(1, 1, 1));
  ASSERT_DOUBLE_EQ(2, result(1, 1, 2));
  ASSERT_DOUBLE_EQ(3, result(1, 2, 1));
  ASSERT_DOUBLE_EQ(4, result(1, 2, 2));
  ASSERT_DOUBLE_EQ(5, result(2, 1, 1));
  ASSERT_DOUBLE_EQ(6, result(2, 1, 2));
  ASSERT_DOUBLE_EQ(7, result(2, 2, 1));
  ASSERT_DOUBLE_EQ(8, result(2, 2, 2));
}
TEST_F(test_dvar3_array, cube)
{
  gradient_structure gs;
  dvar3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  dvar3_array result = cube(a);
  ASSERT_DOUBLE_EQ(1 * 1 * 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(2 * 2 * 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(3 * 3 * 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(4 * 4 * 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(5 * 5 * 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(6 * 6 * 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(7 * 7 * 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(8 * 8 * 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, elem_prod)
{
  gradient_structure gs;
  dvar3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  dvar3_array result = elem_prod(a, a);
  ASSERT_DOUBLE_EQ(1 * 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(2 * 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(3 * 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(4 * 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(5 * 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(6 * 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(7 * 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(8 * 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, elem_div)
{
  gradient_structure gs;
  dvar3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  dvar3_array result = elem_div(a, a);
  ASSERT_DOUBLE_EQ(1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(1, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(1, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(1, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(1, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(1, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(1, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(1, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, operator_plus)
{
  gradient_structure gs;
  dvar3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  dvar3_array result = a + a;
  ASSERT_DOUBLE_EQ(1 + 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(2 + 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(3 + 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(4 + 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(5 + 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(6 + 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(7 + 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(8 + 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, operator_minus)
{
  gradient_structure gs;
  dvar3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  dvar3_array result = a - a;
  ASSERT_DOUBLE_EQ(1 - 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(2 - 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(3 - 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(4 - 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(5 - 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(6 - 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(7 - 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(8 - 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, operator_plus_single)
{
  gradient_structure gs;
  d3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  dvariable d;
  d = 2;

  dvar3_array result = d + a;
  ASSERT_DOUBLE_EQ(2 + 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(2 + 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(2 + 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(2 + 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(2 + 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(2 + 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(2 + 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(2 + 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, operator_minus_single)
{
  gradient_structure gs;
  d3_array a(1, 2, 1, 2, 1, 2);

  a(1, 1, 1) = 1;
  a(1, 1, 2) = 2;
  a(1, 2, 1) = 3;
  a(1, 2, 2) = 4;
  a(2, 1, 1) = 5;
  a(2, 1, 2) = 6;
  a(2, 2, 1) = 7;
  a(2, 2, 2) = 8;

  dvariable d;
  d = 2;

  dvar3_array result = d - a;
  ASSERT_DOUBLE_EQ(2 - 1, value(result(1, 1, 1)));
  ASSERT_DOUBLE_EQ(2 - 2, value(result(1, 1, 2)));
  ASSERT_DOUBLE_EQ(2 - 3, value(result(1, 2, 1)));
  ASSERT_DOUBLE_EQ(2 - 4, value(result(1, 2, 2)));
  ASSERT_DOUBLE_EQ(2 - 5, value(result(2, 1, 1)));
  ASSERT_DOUBLE_EQ(2 - 6, value(result(2, 1, 2)));
  ASSERT_DOUBLE_EQ(2 - 7, value(result(2, 2, 1)));
  ASSERT_DOUBLE_EQ(2 - 8, value(result(2, 2, 2)));
}
TEST_F(test_dvar3_array, pow)
{
  gradient_structure gs;

  dvar3_array a(1, 2, 1, 2, 1, 2);

  double d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        a(i, j, k) = d;
        d += 2.0;
      }
    }
  }

  const int exp = 2;
  dvar3_array ret = pow(a, exp);

  d = 2.0;
  for (int i = 1; i <= 2; ++i)
  {
    for (int j = 1; j <= 2; ++j)
    {
      for (int k = 1; k <= 2; ++k)
      {
        ASSERT_DOUBLE_EQ(std::pow(d,  exp), value(ret(i, j, k)));
        d += 2.0;
      }
    }
  }
}
TEST_F(test_dvar3_array, incompatiblebounds)
{
  gradient_structure gs;

  dvar3_array a(1, 2, 1, 2, 1, 2);

  d3_array other(1, 3, 1, 2, 1, 2);

  ASSERT_ANY_THROW(
    a = other;
  );
}
TEST_F(test_dvar3_array, incompatiblebounds2)
{
  gradient_structure gs;

  dvar3_array a(1, 2, 1, 2, 1, 2);

  d3_array other(2, 2, 1, 2, 1, 2);

  ASSERT_ANY_THROW(
    a = other;
  );
}
/*
TEST_F(test_dvar3_array, unallocated)
{
  gradient_structure gs;

  dvar3_array a(1, 2, 1, 2, 1, 2);

  d3_array other;

#ifdef DEBUG
  EXPECT_DEATH({ a = other; }, "Assertion");
#endif
}
*/
TEST_F(test_dvar3_array, assigment)
{
  gradient_structure gs;
  dvar3_array a(1, 3, 1, 2, 1, 1);
  a(1, 1, 1) = 1;
  a(1, 2, 1) = 2;
  a(2, 1, 1) = 3;
  a(2, 2, 1) = 4;
  a(3, 1, 1) = 5;
  a(3, 2, 1) = 6;
  dvar3_array b(1, 3, 1, 2, 1, 1);
  b = a;
  ASSERT_DOUBLE_EQ(value(b(1, 1, 1)), 1);
  ASSERT_DOUBLE_EQ(value(b(1, 2, 1)), 2);
  ASSERT_DOUBLE_EQ(value(b(2, 1, 1)), 3);
  ASSERT_DOUBLE_EQ(value(b(2, 2, 1)), 4);
  ASSERT_DOUBLE_EQ(value(b(3, 1, 1)), 5);
  ASSERT_DOUBLE_EQ(value(b(3, 2, 1)), 6);
}
TEST_F(test_dvar3_array, assigmenterror)
{
  gradient_structure gs;
  dvar3_array a(1, 3);
  ASSERT_ANY_THROW({
    dvar3_array b(2, 3);
    a = b;
  });
  ASSERT_ANY_THROW({
    dvar3_array b(1, 4);
    a = b;
  });
}
TEST_F(test_dvar3_array, assigmentsame)
{
  gradient_structure gs;
  dvar3_array a(1, 3, 1, 2, 1, 1);
  a(1, 1, 1) = 1;
  a(1, 2, 1) = 2;
  a(2, 1, 1) = 3;
  a(2, 2, 1) = 4;
  a(3, 1, 1) = 5;
  a(3, 2, 1) = 6;
  a = a;
  ASSERT_DOUBLE_EQ(value(a(1, 1, 1)), 1);
  ASSERT_DOUBLE_EQ(value(a(1, 2, 1)), 2);
  ASSERT_DOUBLE_EQ(value(a(2, 1, 1)), 3);
  ASSERT_DOUBLE_EQ(value(a(2, 2, 1)), 4);
  ASSERT_DOUBLE_EQ(value(a(3, 1, 1)), 5);
  ASSERT_DOUBLE_EQ(value(a(3, 2, 1)), 6);
}
TEST_F(test_dvar3_array, deallocatecopies)
{
  gradient_structure gs;

  dvar3_array a(1, 2, 1, 2, 1, 2);
  ASSERT_EQ(0, a.get_ncopies());
  dvar3_array firstcopy(a);
  ASSERT_EQ(1, a.get_ncopies());
  ASSERT_EQ(1, firstcopy.get_ncopies());
  dvar3_array secondcopy(a);
  ASSERT_EQ(2, a.get_ncopies());
  ASSERT_EQ(2, firstcopy.get_ncopies());
  ASSERT_EQ(2, secondcopy.get_ncopies());

  firstcopy.deallocate();
  ASSERT_EQ(1, a.get_ncopies());
  ASSERT_EQ(0, firstcopy.get_ncopies());
  ASSERT_EQ(1, secondcopy.get_ncopies());

  secondcopy.deallocate();
  ASSERT_EQ(0, a.get_ncopies());
  ASSERT_EQ(0, firstcopy.get_ncopies());
  ASSERT_EQ(0, secondcopy.get_ncopies());
}
TEST_F(test_dvar3_array, indexeselem)
{
  gradient_structure gs;
  dvar3_array a(1, 2, 3, 4, 5, 6);
  a(1, 3, 5) = 1;
  a(1, 3, 6) = 2;
  a(1, 4, 5) = 3;
  a(1, 4, 6) = 4;
  a(2, 3, 5) = 5;
  a(2, 3, 6) = 6;
  a(2, 4, 5) = 7;
  a(2, 4, 6) = 8;
  ASSERT_DOUBLE_EQ(value(a.elem(1, 3, 5)), 1);
  ASSERT_DOUBLE_EQ(value(a.elem(1, 3, 6)), 2);
  ASSERT_DOUBLE_EQ(value(a.elem(1, 4, 5)), 3);
  ASSERT_DOUBLE_EQ(value(a.elem(1, 4, 6)), 4);
  ASSERT_DOUBLE_EQ(value(a.elem(2, 3, 5)), 5);
  ASSERT_DOUBLE_EQ(value(a.elem(2, 3, 6)), 6);
  ASSERT_DOUBLE_EQ(value(a.elem(2, 4, 5)), 7);
  ASSERT_DOUBLE_EQ(value(a.elem(2, 4, 6)), 8);
}
