/**
 * Tests errors for "param_init_vector& param_init_vector_vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_01)
{
  dvector v(1, 5);
  param_init_vector_vector pivv;
  index_type min(v);
  index_type max(v);
  pivv.allocate(1, 5, min, max, "TEST");
  try
  {
    param_init_vector piv1 = pivv[1];
    param_init_vector piv0 = pivv[0];
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
 * Tests errors for "param_init_vector& param_init_vector_vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_02)
{
  dvector v(1, 5);
  param_init_vector_vector pivv;
  index_type min(v);
  index_type max(v);
  pivv.allocate(1, 5, min, max, "TEST");
  try
  {
    param_init_vector piv5 = pivv[5];
    param_init_vector piv6 = pivv[6];
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
 * Tests errors for "param_init_vector& param_init_vector_vector::operator () (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_03)
{
  dvector v(1, 5);
  param_init_vector_vector pivv;
  index_type min(v);
  index_type max(v);
  pivv.allocate(1, 5, min, max, "TEST");
  try
  {
    param_init_vector piv1 = pivv(1);
    param_init_vector piv0 = pivv(0);
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
 * Tests errors for "param_init_vector& param_init_vector_vector::operator () (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_04)
{
  dvector v(1, 5);
  param_init_vector_vector pivv;
  index_type min(v);
  index_type max(v);
  pivv.allocate(1, 5, min, max, "TEST");
  try
  {
    param_init_vector piv5 = pivv(5);
    param_init_vector piv6 = pivv(6);
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
 * Tests errors for "prevariable param_init_vector_vector::operator()(int i, int j)" 
 */
TEST_F(test_admb_messages, linad99_model49_05)
{
  dvector v(1, 5);
  param_init_vector_vector pivv;
  index_type min(v);
  index_type max(v);
  pivv.allocate(1, 5, min, max, "TEST");
  try
  {
    prevariable p = pivv(0, 1);
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
 * Tests errors for "prevariable param_init_vector_vector::operator()(int i, int j)" 
 */
TEST_F(test_admb_messages, linad99_model49_06)
{
  dvector v(1, 5);
  param_init_vector_vector pivv;
  index_type min(v);
  index_type max(v);
  pivv.allocate(1, 5, min, max, "TEST");
  try
  {
    //INCOMPLETE checks
    prevariable p = pivv(6, 1);
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
 * Tests errors for "param_init_matrix& param_init_matrix_vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_07)
{
  dvector v(1, 5);
  param_init_matrix_vector pimv;
  index_type min(v);
  index_type max(v);
  index_type min1(v);
  index_type max1(v);
  pimv.allocate(1, 5, min, max, min1, max1, "TEST");
  try
  {
    param_init_matrix pim1 = pimv[1];
    param_init_matrix pim0 = pimv[0];
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
 * Tests errors for "param_init_matrix& param_init_matrix_vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_08)
{
  dvector v(1, 5);
  param_init_matrix_vector pimv;
  index_type min(v);
  index_type max(v);
  index_type min1(v);
  index_type max1(v);
  pimv.allocate(1, 5, min, max, min1, max1, "TEST");
  try
  {
    param_init_matrix pim1 = pimv[5];
    param_init_matrix pim0 = pimv[6];
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
 * Tests errors for "param_init_matrix& param_init_matrix_vector::operator () (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_09)
{
  dvector v(1, 5);
  param_init_matrix_vector pimv;
  index_type min(v);
  index_type max(v);
  index_type min1(v);
  index_type max1(v);
  pimv.allocate(1, 5, min, max, min1, max1, "TEST");
  try
  {
    param_init_matrix pim1 = pimv(1);
    param_init_matrix pim0 = pimv(0);
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
 * Tests errors for "param_init_matrix& param_init_matrix_vector::operator () (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_10)
{
  dvector v(1, 5);
  param_init_matrix_vector pimv;
  index_type min(v);
  index_type max(v);
  index_type min1(v);
  index_type max1(v);
  pimv.allocate(1, 5, min, max, min1, max1, "TEST");
  try
  {
    param_init_matrix pim1 = pimv(5);
    param_init_matrix pim0 = pimv(6);
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
 * Tests errors for "dvar_vector& param_init_matrix_vector::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_model49_11)
{
  dvector v(1, 5);
  param_init_matrix_vector pimv;
  index_type min(v);
  index_type max(v);
  index_type min1(v);
  index_type max1(v);
  pimv.allocate(1, 5, min, max, min1, max1, "TEST");
  try
  {
    //THIS FAILS: dvar_vector dv = pimv(1, 2);
    dvar_vector dv = pimv(0, 1);
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
 * Tests errors for "dvar_vector& param_init_matrix_vector::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_model49_12)
{
  dvector v(1, 5);
  param_init_matrix_vector pimv;
  index_type min(v);
  index_type max(v);
  index_type min1(v);
  index_type max1(v);
  pimv.allocate(1, 5, min, max, min1, max1, "TEST");
  try
  {
    //THIS FAILS: dvar_vector dv = pimv(1, 2);
    dvar_vector dv = pimv(6, 1);
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
 * Tests errors for "prevariable param_init_matrix_vector::operator () (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_model49_13)
{
  dvector v(1, 5);
  param_init_matrix_vector pimv;
  index_type min(v);
  index_type max(v);
  index_type min1(v);
  index_type max1(v);
  pimv.allocate(1, 5, min, max, min1, max1, "TEST");
  try
  {
    prevariable p = pimv(0, 1, 2);
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
 * Tests errors for "prevariable param_init_matrix_vector::operator () (int i, int j, int k)"
 */
TEST_F(test_admb_messages, linad99_model49_14)
{
  dvector v(1, 5);
  param_init_matrix_vector pimv;
  index_type min(v);
  index_type max(v);
  index_type min1(v);
  index_type max1(v);
  pimv.allocate(1, 5, min, max, min1, max1, "TEST");
  try
  {
    prevariable p = pimv(6, 1, 2);
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
 * Tests errors for "param_init_bounded_vector& param_init_bounded_vector_vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_15)
{
  dvector v(1, 5);
  param_init_bounded_vector_vector pibvv;
  index_type min(v);
  index_type max(v);
  double_index_type dmin(v);
  double_index_type dmax(v);
  pibvv.allocate(1, 5, min, max, dmin, dmax, "TEST");
  try
  {
    param_init_bounded_vector pibv1 = pibvv[1];
    param_init_bounded_vector pibv0 = pibvv[0];
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
 * Tests errors for "param_init_bounded_vector& param_init_bounded_vector_vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_16)
{
  dvector v(1, 5);
  param_init_bounded_vector_vector pibvv;
  index_type min(v);
  index_type max(v);
  double_index_type dmin(v);
  double_index_type dmax(v);
  pibvv.allocate(1, 5, min, max, dmin, dmax, "TEST");
  try
  {
    param_init_bounded_vector pibv5 = pibvv[5];
    param_init_bounded_vector pibv6 = pibvv[6];
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
 * Tests errors for "param_init_bounded_vector& param_init_bounded_vector_vector::operator () (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_17)
{
  dvector v(1, 5);
  param_init_bounded_vector_vector pibvv;
  index_type min(v);
  index_type max(v);
  double_index_type dmin(v);
  double_index_type dmax(v);
  pibvv.allocate(1, 5, min, max, dmin, dmax, "TEST");
  try
  {
    param_init_bounded_vector pibv1 = pibvv(1);
    param_init_bounded_vector pibv0 = pibvv(0);
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
 * Tests errors for "param_init_bounded_vector& param_init_bounded_vector_vector::operator () (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_18)
{
  dvector v(1, 5);
  param_init_bounded_vector_vector pibvv;
  index_type min(v);
  index_type max(v);
  double_index_type dmin(v);
  double_index_type dmax(v);
  pibvv.allocate(1, 5, min, max, dmin, dmax, "TEST");
  try
  {
    param_init_bounded_vector pibv5 = pibvv(5);
    param_init_bounded_vector pibv6 = pibvv(6);
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
 * Tests errors for "prevariable param_init_bounded_vector_vector::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_model49_19)
{
  dvector v(1, 5);
  param_init_bounded_vector_vector pibvv;
  index_type min(v);
  index_type max(v);
  double_index_type dmin(v);
  double_index_type dmax(v);
  pibvv.allocate(1, 5, min, max, dmin, dmax, "TEST");
  try
  {
    prevariable p0 = pibvv(0, 2);
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
 * Tests errors for "prevariable param_init_bounded_vector_vector::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_model49_20)
{
  dvector v(1, 5);
  param_init_bounded_vector_vector pibvv;
  index_type min(v);
  index_type max(v);
  double_index_type dmin(v);
  double_index_type dmax(v);
  pibvv.allocate(1, 5, min, max, dmin, dmax, "TEST");
  try
  {
    prevariable p6 = pibvv(6, 5);
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
 * Tests errors for "param_init_bounded_matrix& param_init_bounded_matrix_vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_21)
{
  dvector v(1, 5);
  param_init_bounded_matrix_vector pibmv;
  index_type min(v);
  index_type max(v);
  index_type min2(v);
  index_type max2(v);
  double_index_type dmin2(v);
  double_index_type dmax2(v);
  pibmv.allocate(1, 5, min, max, min2, max2, dmin2, dmax2, "TEST");
  try
  {
    param_init_bounded_matrix pibm = pibmv[0];
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
 * Tests errors for "param_init_bounded_matrix& param_init_bounded_matrix_vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_22)
{
  dvector v(1, 5);
  param_init_bounded_matrix_vector pibmv;
  index_type min(v);
  index_type max(v);
  index_type min2(v);
  index_type max2(v);
  double_index_type dmin2(v);
  double_index_type dmax2(v);
  pibmv.allocate(1, 5, min, max, min2, max2, dmin2, dmax2, "TEST");
  try
  {
    param_init_bounded_matrix pibm = pibmv[6];
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
 * Tests errors for "param_init_bounded_matrix& param_init_bounded_matrix_vector::operator () (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_23)
{
  dvector v(1, 5);
  param_init_bounded_matrix_vector pibmv;
  index_type min(v);
  index_type max(v);
  index_type min2(v);
  index_type max2(v);
  double_index_type dmin2(v);
  double_index_type dmax2(v);
  pibmv.allocate(1, 5, min, max, min2, max2, dmin2, dmax2, "TEST");
  try
  {
    param_init_bounded_matrix pibm = pibmv(0);
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
 * Tests errors for "param_init_bounded_matrix& param_init_bounded_matrix_vector::operator () (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_24)
{
  dvector v(1, 5);
  param_init_bounded_matrix_vector pibmv;
  index_type min(v);
  index_type max(v);
  index_type min2(v);
  index_type max2(v);
  double_index_type dmin2(v);
  double_index_type dmax2(v);
  pibmv.allocate(1, 5, min, max, min2, max2, dmin2, dmax2, "TEST");
  try
  {
    param_init_bounded_matrix pibm = pibmv(6);
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
 * Tests errors for "dvar_vector& param_init_bounded_matrix_vector::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_model49_25)
{
  dvector v(1, 5);
  param_init_bounded_matrix_vector pibmv;
  index_type min(v);
  index_type max(v);
  index_type min2(v);
  index_type max2(v);
  double_index_type dmin2(v);
  double_index_type dmax2(v);
  pibmv.allocate(1, 5, min, max, min2, max2, dmin2, dmax2, "TEST");
  try
  {
    dvar_vector dv = pibmv(0, 1);
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
 * Tests errors for "dvar_vector& param_init_bounded_matrix_vector::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_model49_26)
{
  dvector v(1, 5);
  param_init_bounded_matrix_vector pibmv;
  index_type min(v);
  index_type max(v);
  index_type min2(v);
  index_type max2(v);
  double_index_type dmin2(v);
  double_index_type dmax2(v);
  pibmv.allocate(1, 5, min, max, min2, max2, dmin2, dmax2, "TEST");
  try
  {
    dvar_vector dv = pibmv(6, 5);
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
 * Tests errors for "prevariable param_init_bounded_matrix_vector::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_model49_27)
{
  dvector v(1, 5);
  param_init_bounded_matrix_vector pibmv;
  index_type min(v);
  index_type max(v);
  index_type min2(v);
  index_type max2(v);
  double_index_type dmin2(v);
  double_index_type dmax2(v);
  pibmv.allocate(1, 5, min, max, min2, max2, dmin2, dmax2, "TEST");
  try
  {
    prevariable p = pibmv(0, 6, 5);
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
 * Tests errors for "prevariable param_init_bounded_matrix_vector::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_model49_28)
{
  dvector v(1, 5);
  param_init_bounded_matrix_vector pibmv;
  index_type min(v);
  index_type max(v);
  index_type min2(v);
  index_type max2(v);
  double_index_type dmin2(v);
  double_index_type dmax2(v);
  pibmv.allocate(1, 5, min, max, min2, max2, dmin2, dmax2, "TEST");
  try
  {
    prevariable p = pibmv(6, 6, 5);
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
 * Tests errors for "param_init_number& param_init_number_vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_29)
{
  param_init_number_vector pinv;
  pinv.allocate(1, 5, "TEST");
  try
  {
    param_init_number pin1 = pinv[1];
    param_init_number pin0 = pinv[0];
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
 * Tests errors for "param_init_number& param_init_number_vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_30)
{
  param_init_number_vector pinv;
  pinv.allocate(1, 5, "TEST");
  try
  {
    param_init_number pin5 = pinv[5];
    param_init_number pin6 = pinv[6];
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
 * Tests errors for "param_init_number& param_init_number_vector::operator () (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_31)
{
  param_init_number_vector pinv;
  pinv.allocate(1, 5, "TEST");
  try
  {
    param_init_number pin1 = pinv(1);
    param_init_number pin0 = pinv(0);
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
 * Tests errors for "param_init_number& param_init_number_vector::operator () (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_32)
{
  param_init_number_vector pinv;
  pinv.allocate(1, 5, "TEST");
  try
  {
    param_init_number pin5 = pinv(5);
    param_init_number pin6 = pinv(6);
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
 * Tests errors for "param_init_bounded_number& param_init_bounded_number_vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_33)
{
  param_init_bounded_number_vector pinv;
  dvector v(1, 5);
  double_index_type bmin(v);
  double_index_type bmax(v);
  pinv.allocate(1, 5, bmin, bmax, "TEST");
  try
  {
    param_init_bounded_number pin1 = pinv[1];
    param_init_bounded_number pin0 = pinv[0];
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
 * Tests errors for "param_init_bounded_number& param_init_bounded_number_vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_34)
{
  param_init_bounded_number_vector pinv;
  dvector v(1, 5);
  double_index_type bmin(v);
  double_index_type bmax(v);
  pinv.allocate(1, 5, bmin, bmax, "TEST");
  try
  {
    param_init_bounded_number pin5 = pinv[5];
    param_init_bounded_number pin6 = pinv[6];
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
 * Tests errors for "param_init_bounded_number& param_init_bounded_number_vector::operator () (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_35)
{
  param_init_bounded_number_vector pinv;
  dvector v(1, 5);
  double_index_type bmin(v);
  double_index_type bmax(v);
  pinv.allocate(1, 5, bmin, bmax, "TEST");
  try
  {
    param_init_bounded_number pin1 = pinv(1);
    param_init_bounded_number pin0 = pinv(0);
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
 * Tests errors for "param_init_bounded_number& param_init_bounded_number_vector::operator () (int i)"
 */
TEST_F(test_admb_messages, linad99_model49_36)
{
  param_init_bounded_number_vector pinv;
  dvector v(1, 5);
  double_index_type bmin(v);
  double_index_type bmax(v);
  pinv.allocate(1, 5, bmin, bmax, "TEST");
  try
  {
    param_init_bounded_number pin5 = pinv(5);
    param_init_bounded_number pin6 = pinv(6);
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
