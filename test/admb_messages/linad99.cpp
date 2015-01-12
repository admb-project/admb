/**
 * Tests errors for "AD_LONG_INT& lvector::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_lvec1_01)
{
  lvector lv(1, 5);
  try
  {
    AD_LONG_INT lv1 = lv(1);
    AD_LONG_INT lv0 = lv(0);
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
 * Tests errors for "AD_LONG_INT& lvector::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_lvec1_02)
{
  lvector lv(1, 5);
  try
  {
    AD_LONG_INT lv5 = lv(5);
    AD_LONG_INT lv6 = lv(6);
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
 * Tests errors for "AD_LONG_INT& lvector::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_lvec1_03)
{
  lvector lv(1, 5);
  try
  {
    AD_LONG_INT lv1 = lv[1];
    AD_LONG_INT lv0 = lv[0];
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
 * Tests errors for "AD_LONG_INT& lvector::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_lvec1_04)
{
  lvector lv(1, 5);
  try
  {
    AD_LONG_INT lv5 = lv[5];
    AD_LONG_INT lv6 = lv[6];
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
 * Tests errors for "dvector extract_column(_CONST dmatrix& m, int j)"
 */
TEST_F(test_admb_messages, linad99_dmat6_01)
{
  dmatrix m(1, 5, 1, 5);
  try
  {
    dvector v1 = extract_column(m, 1);
    dvector v0 = extract_column(m, 0);
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
 * Tests errors for "dvector extract_row(_CONST dmatrix& m, int i)"
 */
TEST_F(test_admb_messages, linad99_dmat6_02)
{
  dmatrix m(1, 5, 1, 5);
  try
  {
    dvector v1 = extract_row(m, 1);
    dvector v0 = extract_row(m, 0);
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
 * Tests errors for "dvector& dmatrix::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_dmat_acc_01)
{
  dmatrix m(1, 5, 1, 5);
  try
  {
    dvector v1 = m[1];
    dvector v0 = m[0];
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
 * Tests errors for "dvector& dmatrix::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_dmat_acc_02)
{
  dmatrix m(1, 5, 1, 5);
  try
  {
    dvector v5 = m[5];
    dvector v6 = m[6];
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
 * Tests errors for "dvector& dmatrix::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_dmat8_01)
{
  dmatrix m(1, 5, 1, 5);
  try
  {
    dvector v1 = m(1);
    dvector v0 = m(0);
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
 * Tests errors for "dvector& dmatrix::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_dmat8_02)
{
  dmatrix m(1, 5, 1, 5);
  try
  {
    dvector v5 = m(5);
    dvector v6 = m(6);
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
 * Tests errors for "dmatrix& d3_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_01)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dmatrix d3a1 = d3a(1);
    dmatrix d3a0 = d3a(0);
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
 * Tests errors for "dmatrix& d3_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_02)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dmatrix d3a5 = d3a(5);
    dmatrix d3a6 = d3a(6);
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
 * Tests errors for "dmatrix& d3_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_03)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dmatrix d3a1 = d3a[1];
    dmatrix d3a0 = d3a[0];
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
 * Tests errors for "dmatrix& d3_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_04)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dmatrix d3a5 = d3a[5];
    dmatrix d3a6 = d3a[6];
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
 * Tests errors for "dvector& d3_array::operator() (int k, int i)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_05)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dvector v = d3a(0, 1);
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
 * Tests errors for "dvector& d3_array::operator() (int k, int i)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_06)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dvector v = d3a(6, 1);
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
 * Tests errors for "double& d3_array::operator() (int k, int i, int j)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_07)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    double d = d3a(0, 1, 1);
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
 * Tests errors for "double& d3_array::operator() (int k, int i, int j)"
 */
TEST_F(test_admb_messages, linad99_d3arr1_08)
{
  d3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    double d = d3a(6, 1, 1);
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
 * Tests errors for "prevariable dvar3_array::operator() (int k, int i, int j)"
 */
TEST_F(test_admb_messages, linad99_f3arr1_01)
{
  dvar3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    prevariable p = d3a(0, -1, -1);
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
 * Tests errors for "prevariable dvar3_array::operator() (int k, int i, int j)"
 */
TEST_F(test_admb_messages, linad99_f3arr1_02)
{
  dvar3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    prevariable p = d3a(6, -1, -1);
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
 * Tests errors for "dvar_vector& dvar3_array::operator() (int k, int i)"
 */
TEST_F(test_admb_messages, linad99_f3arr1_03)
{
  dvar3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dvar_vector v = d3a(0, 1);
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
 * Tests errors for "dvar_vector& dvar3_array::operator() (int k, int i)"
 */
TEST_F(test_admb_messages, linad99_f3arr1_04)
{
  dvar3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dvar_vector v = d3a(6, 1);
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
 * Tests errors for "dvar_matrix& dvar3_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_f3arr1_05)
{
  dvar3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dvar_matrix v = d3a(0);
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
 * Tests errors for "dvar_matrix& dvar3_array::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_f3arr1_06)
{
  dvar3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dvar_matrix v = d3a(6);
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
 * Tests errors for "dvar_matrix& dvar3_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_f3arr1_07)
{
  dvar3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dvar_matrix v = d3a[0];
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
 * Tests errors for "dvar_matrix& dvar3_array::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_f3arr1_08)
{
  dvar3_array d3a(1, 5, 1, 5, 1, 5);
  try
  {
    dvar_matrix v = d3a[6];
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
 * Tests errors for "double& dvar_vector::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_dvec_acc_01)
{
  dvector v(1, 5);
  try
  {
    double d1 = v[1];
    double d0 = v[0];
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
 * Tests errors for "double& dvar_vector::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_dvec_acc_02)
{
  dvector v(1, 5);
  try
  {
    double d5 = v[5];
    double d6 = v[6];
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
 * Tests errors for "double& dvar_vector::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_dvec_acc_03)
{
  dvector v(1, 5);
  try
  {
    double d1 = v(1);
    double d0 = v(0);
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
 * Tests errors for "double& dvar_vector::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_dvec_acc_04)
{
  dvector v(1, 5);
  try
  {
    double d5 = v(5);
    double d6 = v(6);
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
 * Tests errors for "dvar_vector extract_column(_CONST dvar_matrix& m,int j)"
 */
TEST_F(test_admb_messages, linad99_fvar_ar7_01)
{
  dvar_matrix m(1, 5, 1, 5);
  try
  {
    dvar_vector v1 = extract_column(m, 1);
    dvar_vector v0 = extract_column(m, 0);
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
 * Tests errors for "dvector extract_column(_CONST dvar_matrix& m,int j)"
 */
TEST_F(test_admb_messages, linad99_fvar_ar7_02)
{
  dmatrix m(1, 5, 1, 5);
  try
  {
    dvector v1 = column_value(m, 1);
    dvector v0 = column_value(m, 0);
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
 * Tests errors for "dvar_vector extract_row(_CONST dvar_matrix& m,int j)"
 */
TEST_F(test_admb_messages, linad99_fvar_ar7_03)
{
  dvar_matrix m(1, 5, 1, 5);
  try
  {
    dvar_vector v1 = extract_row(m, 1);
    dvar_vector v0 = extract_row(m, 0);
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
 * Tests errors for "dvariable colsum(_CONST dvar_matrix& m,int col)"
 */
TEST_F(test_admb_messages, linad99_fvar_m35_01)
{
  dvar_matrix m(1, 5, 1, 5);
  try
  {
    dvariable v1 = colsum(m, 1);
    dvariable v0 = colsum(m, 0);
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
 * Tests errors for "prevariable dvar_matrix::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_fvma_acc_01)
{
  dvar_matrix m(1, 5, 1, 5);
  try
  {
    prevariable v0 = m(0, -1);
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
 * Tests errors for "prevariable dvar_matrix::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_fvma_acc_02)
{
  dvar_matrix m(1, 5, 1, 5);
  try
  {
    prevariable v0 = m(6, -1);
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
 * Tests errors for "prevariable dvar_matrix::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_fvma_acc_03)
{
  dvar_matrix m(1, 5, 1, 5);
  try
  {
    prevariable v0 = m(1, 0);
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
 * Tests errors for "prevariable dvar_matrix::operator () (int i, int j)"
 */
TEST_F(test_admb_messages, linad99_fvma_acc_04)
{
  dvar_matrix m(1, 5, 1, 5);
  try
  {
    prevariable v0 = m(1, 6);
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
 * Tests errors for "dvar_vector& dvar_matrix::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_fvma_acc_05)
{
  dvar_matrix m(1, 5, 1, 5);
  try
  {
    dvar_vector v0 = m[0];
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
 * Tests errors for "dvar_vector& dvar_matrix::operator [] (int i)"
 */
TEST_F(test_admb_messages, linad99_fvma_acc_06)
{
  dvar_matrix m(1, 5, 1, 5);
  try
  {
    dvar_vector v6 = m[6];
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
 * Tests errors for "AD_LONG_INT colsum(_CONST lmatrix& m,int col)"
 */
TEST_F(test_admb_messages, linad99_lmat7_01)
{
  lmatrix m(1, 5, 1, 5);
  try
  {
    AD_LONG_INT colsum(_CONST lmatrix& m,int col);
    AD_LONG_INT v0 = colsum(m, 0);
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
 * Tests errors for "AD_LONG_INT colsum(_CONST lmatrix& m,int col)"
 */
TEST_F(test_admb_messages, linad99_lmat7_02)
{
  lmatrix m(1, 5, 1, 5);
  try
  {
    AD_LONG_INT colsum(_CONST lmatrix& m,int col);
    AD_LONG_INT v0 = colsum(m, 6);
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
 * Tests errors for "lvector column(_CONST lmatrix& m,int col)"
 */
TEST_F(test_admb_messages, linad99_lmat7_03)
{
  lmatrix m(1, 5, 1, 5);
  try
  {
    lvector column(_CONST lmatrix& m,int col);
    lvector v0 = column(m, 0);
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
 * Tests errors for "lvector column(_CONST lmatrix& m,int col)"
 */
TEST_F(test_admb_messages, linad99_lmat7_04)
{
  lmatrix m(1, 5, 1, 5);
  try
  {
    lvector column(_CONST lmatrix& m,int col);
    lvector v6 = column(m, 6);
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
 * Tests errors for "int& ivector::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_ivec7_01)
{
  ivector v(1, 5);
  try
  {
    int i0 = v[0];
    int i1 = v[1];
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
 * Tests errors for "int& ivector::operator() (int i)"
 */
TEST_F(test_admb_messages, linad99_ivec7_02)
{
  ivector v(1, 5);
  try
  {
    int i0 = v(0);
    int i1 = v(1);
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
 * Tests errors for "int& ivector::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_ivec7_03)
{
  ivector v(1, 5);
  try
  {
    int i5 = v[5];
    int i6 = v[6];
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
 * Tests errors for "int& ivector::operator[] (int i)"
 */
TEST_F(test_admb_messages, linad99_ivec7_04)
{
  ivector v(1, 5);
  try
  {
    int i5 = v(5);
    int i6 = v(6);
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
