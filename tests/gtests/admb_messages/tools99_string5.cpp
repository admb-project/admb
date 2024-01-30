/**
 * Tests errors for "adstring& adstring_array::operator [] (int i)"
 */
TEST_F(test_admb_messages, tools99_string5_01)
{
#ifdef DEBUG
  adstring_array a(1, 4);
  EXPECT_DEATH({
    adstring a1 = a[1];
    adstring a0 = a[0];
  }, "Assertion");
#endif
}
/**
 * Tests errors for "adstring& adstring_array::operator [] (int i)"
 */
TEST_F(test_admb_messages, tools99_string5_02)
{
#ifdef DEBUG
  adstring_array a(1, 4);
  EXPECT_DEATH({
    adstring a4 = a[4];
    adstring a0 = a[5];
  }, "Assertion");
#endif
}
/**
 * Tests errors for "adstring& adstring_array::operator () (int i)"
 */
TEST_F(test_admb_messages, tools99_string5_03)
{
  adstring_array a(1, 4);
  EXPECT_DEATH({
    adstring a1 = a(1);
    adstring a0 = a(0);
  }, "Assertion");
}
