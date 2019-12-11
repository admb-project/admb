#include <gtest/gtest.h>
#include <gradient_structure.h>

class test_humungous_pointer: public ::testing::Test {};

TEST_F(test_humungous_pointer, operators)
{
  humungous_pointer hp;
  ASSERT_TRUE(hp.ptr == NULL);
  ASSERT_TRUE((char*)hp == NULL);
  ASSERT_TRUE((double_and_int*)hp == NULL);
  ASSERT_TRUE((void*)hp == NULL);
  ASSERT_TRUE((double*)hp == NULL);

  //If ptr is a null pointer, the function does nothing.
  hp.free();

  void* ptr = (void*)malloc(1000);
  hp = ptr;
  ASSERT_TRUE(hp.ptr == ptr);
  ASSERT_TRUE((char*)hp == ptr);
  ASSERT_TRUE((double_and_int*)hp == ptr);
  ASSERT_TRUE((void*)hp == ptr);
  ASSERT_TRUE((double*)hp == ptr);
  ASSERT_TRUE(hp == ptr);
  ASSERT_FALSE(hp != ptr);

  size_t adjustment = 10;
  hp.adjust(adjustment);
  void* adjusted = ptr + adjustment;
  ASSERT_TRUE(hp.ptr == adjusted);
  ASSERT_TRUE((char*)hp == adjusted);
  ASSERT_TRUE((double_and_int*)hp == adjusted);
  ASSERT_TRUE((void*)hp == adjusted);
  ASSERT_TRUE((double*)hp == adjusted);
  ASSERT_TRUE(hp == adjusted);
  ASSERT_FALSE(hp != adjusted);

  hp.free();
  ASSERT_TRUE(hp.ptr == NULL);
  ASSERT_TRUE((char*)hp == NULL);
  ASSERT_TRUE((double_and_int*)hp == NULL);
  ASSERT_TRUE((void*)hp == NULL);
  ASSERT_TRUE((double*)hp == NULL);
  ptr = NULL;
  ASSERT_TRUE(hp == ptr);
  ASSERT_FALSE(hp != ptr);
}
