/**
 * Tests errors for "init_df1b2variable& init_df1b2vector::operator () (int i)"
 */
TEST_F(test_admb_messages, df1b2_separable_df1b2fn2_01)
{
  df1b2variable::noallocate=1; 
  df1b2variable::pool->set_size(100000);
  init_df1b2variable::noallocate=1; 
  init_df1b2variable::pool->set_size(100000);
  df1b2_gradlist::no_derivatives = 1;

  init_df1b2vector v;
  v.allocate(1, 5);
  try
  {
    init_df1b2variable v0 = v(0);
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
 * Tests errors for "init_df1b2variable& init_df1b2vector::operator () (int i)"
 */
TEST_F(test_admb_messages, df1b2_separable_df1b2fn2_02)
{
  df1b2variable::noallocate=1; 
  df1b2variable::pool->set_size(100000);
  init_df1b2variable::noallocate=1; 
  init_df1b2variable::pool->set_size(100000);
  df1b2_gradlist::no_derivatives = 1;

  init_df1b2vector v;
  v.allocate(1, 5);
  try
  {
    init_df1b2variable v0 = v(6);
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
 * Tests errors for "init_df1b2variable& init_df1b2vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, df1b2_separable_df1b2fn2_03)
{
  df1b2variable::noallocate=1; 
  df1b2variable::pool->set_size(100000);
  init_df1b2variable::noallocate=1; 
  init_df1b2variable::pool->set_size(100000);
  df1b2_gradlist::no_derivatives = 1;

  init_df1b2vector v;
  v.allocate(1, 5);
  try
  {
    init_df1b2variable v0 = v[0];
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
 * Tests errors for "init_df1b2variable& init_df1b2vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, df1b2_separable_df1b2fn2_04)
{
  df1b2variable::noallocate=1; 
  df1b2variable::pool->set_size(100000);
  init_df1b2variable::noallocate=1; 
  init_df1b2variable::pool->set_size(100000);
  df1b2_gradlist::no_derivatives = 1;

  init_df1b2vector v;
  v.allocate(1, 5);
  try
  {
    init_df1b2variable v0 = v[6];
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
 * Tests errors for "df1b2variable& df1b23array::operator () (int i, int j, int k)"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b23d1_01)
{
  df1b2variable::noallocate=1; 
  df1b23array a;
  a.allocate(1, 5);
  try
  {
    df1b2variable v0 = a(0, -1, -1);
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
 * Tests errors for "df1b2variable& df1b23array::operator () (int i, int j, int k)"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b23d1_02)
{
  df1b2variable::noallocate=1; 
  df1b23array a;
  a.allocate(1, 5);
  try
  {
    df1b2variable v0 = a(6, -1, -1);
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
 * Tests errors for "df1b2vector& df1b23array::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b23d1_03)
{
  df1b2variable::noallocate=1; 
  df1b23array a;
  a.allocate(1, 5);
  try
  {
    df1b2vector v0 = a(0, -1);
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
 * Tests errors for "df1b2vector& df1b23array::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b23d1_04)
{
  df1b2variable::noallocate=1; 
  df1b23array a;
  a.allocate(1, 5);
  try
  {
    df1b2vector v0 = a(6, -1);
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
 * Tests errors for "df1b2matrix& df1b23array::operator () (int i)"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b23d1_05)
{
  df1b2variable::noallocate=1; 
  df1b23array a;
  a.allocate(1, 5);
  try
  {
    df1b2matrix v0 = a(0);
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
 * Tests errors for "df1b2matrix& df1b23array::operator () (int i)"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b23d1_06)
{
  df1b2variable::noallocate=1; 
  df1b23array a;
  a.allocate(1, 5);
  try
  {
    df1b2matrix v0 = a(6);
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
 * Tests errors for "df1b2matrix& df1b23array::operator [] (int i)"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b23d1_07)
{
  df1b2variable::noallocate=1; 
  df1b23array a;
  a.allocate(1, 5);
  try
  {
    df1b2matrix v0 = a[0];
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
 * Tests errors for "df1b2matrix& df1b23array::operator [] (int i)"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b23d1_08)
{
  df1b2variable::noallocate=1; 
  df1b23array a;
  a.allocate(1, 5);
  try
  {
    df1b2matrix v0 = a[6];
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
 * Tests errors for "df1b2variable& df1b2vector::operator [] (int i) const"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b2vc1_01)
{
  df1b2variable::noallocate=1; 
  df1b2vector a;
  a.allocate(1, 5);
  try
  {
    df1b2variable v0 = a[0];
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
 * Tests errors for "df1b2variable& df1b2vector::operator [] (int i) const"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b2vc1_02)
{
  df1b2variable::noallocate=1; 
  df1b2vector a;
  a.allocate(1, 5);
  try
  {
    df1b2variable v0 = a[6];
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
 * Tests errors for "df1b2variable& df1b2vector::operator () (int i) const"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b2vc1_03)
{
  df1b2variable::noallocate=1; 
  df1b2vector a;
  a.allocate(1, 5);
  try
  {
    df1b2variable v0 = a(0);
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
 * Tests errors for "df1b2variable& df1b2vector::operator () (int i) const"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b2vc1_04)
{
  df1b2variable::noallocate=1; 
  df1b2vector a;
  a.allocate(1, 5);
  try
  {
    df1b2variable v0 = a(6);
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
 * Tests errors for "df1b2vector& df1b2matrix::operator () (int i) const"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b2vc1_05)
{
  df1b2variable::noallocate=1; 
  df1b2matrix a;
  a.allocate(1, 5, 1, 5);
  try
  {
    df1b2vector v0 = a(0);
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
 * Tests errors for "df1b2vector& df1b2matrix::operator () (int i) const"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b2vc1_06)
{
  df1b2variable::noallocate=1; 
  df1b2matrix a;
  a.allocate(1, 5, 1, 5);
  try
  {
    df1b2vector v0 = a(6);
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
 * Tests errors for "df1b2vector& df1b2matrix::operator [] (int i) const"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b2vc1_07)
{
  df1b2variable::noallocate=1; 
  df1b2matrix a;
  a.allocate(1, 5, 1, 5);
  try
  {
    df1b2vector v0 = a[0];
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
 * Tests errors for "df1b2vector& df1b2matrix::operator [] (int i) const"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b2vc1_08)
{
  df1b2variable::noallocate=1; 
  df1b2matrix a;
  a.allocate(1, 5, 1, 5);
  try
  {
    df1b2vector v0 = a[6];
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
 * Tests errors for "df1b2variable& df1b2matrix::operator () (int i, int j) const"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b2vc1_09)
{
  df1b2variable::noallocate=1; 
  df1b2matrix a;
  a.allocate(1, 5, 1, 5);
  try
  {
    df1b2variable v0 = a(0, -1);
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
 * Tests errors for "df1b2variable& df1b2matrix::operator () (int i, int j) const"
 */
TEST_F(test_admb_messages, df1b2_separable_f1b2vc1_10)
{
  df1b2variable::noallocate=1; 
  df1b2matrix a;
  a.allocate(1, 5, 1, 5);
  try
  {
    df1b2variable v0 = a(6, -1);
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
 * Tests errors for "df1b2_init_bounded_number& df1b2_init_bounded_number_vector::operator []"
 */
TEST_F(test_admb_messages, df1b2_separable_df1b2nv1_01)
{
  df1b2variable::noallocate=1; 
  df1b2variable::pool->set_size(100000);
  init_df1b2variable::noallocate=1; 
  init_df1b2variable::pool->set_size(100000);
  df1b2_gradlist::no_derivatives = 1;

  dvector v15(1, 5);
  double_index_type dmin(v15);
  double_index_type dmax(v15);

  df1b2_init_bounded_number_vector v;
  v.allocate(1, 5, dmin, dmax, "TEST");
  try
  {
    df1b2_init_bounded_number v0 = v[0];
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
 * Tests errors for "df1b2_init_bounded_number& df1b2_init_bounded_number_vector::operator []"
 */
TEST_F(test_admb_messages, df1b2_separable_df1b2nv1_02)
{
  df1b2variable::noallocate=1; 
  df1b2variable::pool->set_size(100000);
  init_df1b2variable::noallocate=1; 
  init_df1b2variable::pool->set_size(100000);
  df1b2_gradlist::no_derivatives = 1;

  dvector v15(1, 5);
  double_index_type dmin(v15);
  double_index_type dmax(v15);

  df1b2_init_bounded_number_vector v;
  v.allocate(1, 5, dmin, dmax, "TEST");
  try
  {
    df1b2_init_bounded_number v0 = v[6];
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
 * Tests errors for "df1b2_init_bounded_number& df1b2_init_bounded_number_vector::operator ()"
 */
TEST_F(test_admb_messages, df1b2_separable_df1b2nv1_03)
{
  df1b2variable::noallocate=1; 
  df1b2variable::pool->set_size(100000);
  init_df1b2variable::noallocate=1; 
  init_df1b2variable::pool->set_size(100000);
  df1b2_gradlist::no_derivatives = 1;

  dvector v15(1, 5);
  double_index_type dmin(v15);
  double_index_type dmax(v15);

  df1b2_init_bounded_number_vector v;
  v.allocate(1, 5, dmin, dmax, "TEST");
  try
  {
    df1b2_init_bounded_number v0 = v(0);
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
 * Tests errors for "df1b2_init_bounded_number& df1b2_init_bounded_number_vector::operator ()"
 */
TEST_F(test_admb_messages, df1b2_separable_df1b2nv1_04)
{
  df1b2variable::noallocate=1; 
  df1b2variable::pool->set_size(100000);
  init_df1b2variable::noallocate=1; 
  init_df1b2variable::pool->set_size(100000);
  df1b2_gradlist::no_derivatives = 1;

  dvector v15(1, 5);
  double_index_type dmin(v15);
  double_index_type dmax(v15);

  df1b2_init_bounded_number_vector v;
  v.allocate(1, 5, dmin, dmax, "TEST");
  try
  {
    df1b2_init_bounded_number v0 = v(6);
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
 * Tests errors for "df1b2_init_number& df1b2_init_number_vector::operator () (int i)"
 */
TEST_F(test_admb_messages, df1b2_separable_df1b2nv1_05)
{
  df1b2variable::noallocate=1; 
  df1b2variable::pool->set_size(100000);
  init_df1b2variable::noallocate=1; 
  init_df1b2variable::pool->set_size(100000);
  df1b2_gradlist::no_derivatives = 1;

  df1b2_init_number_vector v;
  v.allocate(1, 5, "TEST");
  try
  {
    df1b2_init_number v0 = v(0);
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
 * Tests errors for "df1b2_init_number& df1b2_init_number_vector::operator () (int i)"
 */
TEST_F(test_admb_messages, df1b2_separable_df1b2nv1_06)
{
  df1b2variable::noallocate=1; 
  df1b2variable::pool->set_size(100000);
  init_df1b2variable::noallocate=1; 
  init_df1b2variable::pool->set_size(100000);
  df1b2_gradlist::no_derivatives = 1;

  df1b2_init_number_vector v;
  v.allocate(1, 5, "TEST");
  try
  {
    df1b2_init_number v0 = v(6);
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
 * Tests errors for "df1b2_init_number& df1b2_init_number_vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, df1b2_separable_df1b2nv1_07)
{
  df1b2variable::noallocate=1; 
  df1b2variable::pool->set_size(100000);
  init_df1b2variable::noallocate=1; 
  init_df1b2variable::pool->set_size(100000);
  df1b2_gradlist::no_derivatives = 1;

  df1b2_init_number_vector v;
  v.allocate(1, 5, "TEST");
  try
  {
    df1b2_init_number v0 = v[0];
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
 * Tests errors for "df1b2_init_number& df1b2_init_number_vector::operator [] (int i)"
 */
TEST_F(test_admb_messages, df1b2_separable_df1b2nv1_08)
{
  df1b2variable::noallocate=1; 
  df1b2variable::pool->set_size(100000);
  init_df1b2variable::noallocate=1; 
  init_df1b2variable::pool->set_size(100000);
  df1b2_gradlist::no_derivatives = 1;

  df1b2_init_number_vector v;
  v.allocate(1, 5, "TEST");
  try
  {
    df1b2_init_number v0 = v[6];
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
