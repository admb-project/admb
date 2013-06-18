/**
 * Tests errors for "ivector& imatrix::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_imat1_01)
{
  imatrix m;
  m.allocate(1, 5);
  try
  {
    ivector iv1 = m(1);
    ivector iv0 = m(0);
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
 * Tests errors for "ivector& imatrix::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_imat1_02)
{
  imatrix m;
  m.allocate(1, 5);
  try
  {
    ivector iv5 = m(5);
    ivector iv6 = m(6);
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
 * Tests errors for "int& imatrix::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_imat2_01)
{
  imatrix m;
  m.allocate(1, 5);
  try
  {
    int i0 = m(0, -1);
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
 * Tests errors for "int& imatrix::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_imat2_02)
{
  imatrix m;
  m.allocate(1, 5);
  try
  {
    int i6 = m(6, -1);
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
 * Tests errors for "int& imatrix::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_imat2_03)
{
  imatrix m;
  m.allocate(1, 5);
  try
  {
    int i0 = m(1, 0);
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
 * Tests errors for "int& imatrix::operator() (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_imat2_04)
{
  imatrix m;
  m.allocate(1, 5);
  try
  {
    int i6 = m(1, 6);
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
 * Tests errors for "ivector& imatrix::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_imat4_01)
{
  imatrix m;
  m.allocate(1, 5);
  try
  {
    ivector iv1 = m[1];
    ivector iv0 = m[0];
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
 * Tests errors for "ivector& imatrix::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_imat4_02)
{
  imatrix m;
  m.allocate(1, 5);
  try
  {
    ivector iv5 = m[5];
    ivector iv6 = m[6];
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
 * Tests errors for "int colsum(_CONST imatrix& m,int col)"
 */
TEST_F(test_admb_messages, linad99_imat7_01)
{
  imatrix m;
  m.allocate(1, 5);
  try
  {
    int i1 = colsum(m, 1);
    int i0 = colsum(m, 0);
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
 * Tests errors for "int colsum(_CONST imatrix& m,int col)"
 */
TEST_F(test_admb_messages, linad99_imat7_02)
{
  imatrix m;
  m.allocate(1, 5);
  try
  {
    int i1 = colsum(m, 5);
    int i0 = colsum(m, 6);
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
 * Tests errors for "ivector column(_CONST imatrix& m,int col)"
 */
TEST_F(test_admb_messages, linad99_imat7_03)
{
  imatrix m;
  m.allocate(1, 5);
  try
  {
    ivector i1 = column(m, 1);
    ivector i0 = column(m, 0);
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
 * Tests errors for "ivector column(_CONST imatrix& m,int col)"
 */
TEST_F(test_admb_messages, linad99_imat7_04)
{
  imatrix m;
  m.allocate(1, 5);
  try
  {
    ivector i1 = column(m, 5);
    ivector i0 = column(m, 6);
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
