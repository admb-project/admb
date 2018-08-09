#include <gtest/gtest.h>
#include <adpool.h>

class test_adpool: public ::testing::Test {};

TEST_F(test_adpool, default_constructor)
{
  ASSERT_EQ(0, adpool::get_num_adpools());
  adpool a;
  ASSERT_EQ(1, adpool::get_num_adpools());

  /*
  unsigned int nvar;
  int& on_adpool_vector(void) {return adpool_vector_flag;}
  */

  ASSERT_TRUE(a.last_chunk == NULL);
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.num_chunks);
  ASSERT_EQ(0, a.nelem);
  ASSERT_EQ(0, a.size);
  ASSERT_TRUE(a.head == NULL);
  ASSERT_TRUE(a.first == NULL);
}
TEST_F(test_adpool, constructor_size)
{
  adpool a(0);

  ASSERT_TRUE(a.last_chunk == NULL);
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.num_chunks);
  ASSERT_EQ(0, a.nelem);
  ASSERT_EQ(0, a.size);
  ASSERT_TRUE(a.head == NULL);
  ASSERT_TRUE(a.first == NULL);

  size_t size = sizeof(adpool::link*);

  for (size_t i = size - 1; i <= size; ++i)
  {
    ASSERT_EQ(1, adpool::get_num_adpools());
    adpool b(i);
    ASSERT_EQ(2, adpool::get_num_adpools());

    ASSERT_TRUE(b.last_chunk == NULL);
    ASSERT_EQ(0, b.num_allocated);
    ASSERT_EQ(0, b.num_chunks);
    ASSERT_EQ(0, b.nelem);
    ASSERT_EQ(size, b.size);
    ASSERT_TRUE(b.head == NULL);
    ASSERT_TRUE(b.first == NULL);
  }
  ASSERT_EQ(1, adpool::get_num_adpools());
  adpool c(size + 1);
  ASSERT_EQ(2, adpool::get_num_adpools());

  ASSERT_TRUE(c.last_chunk == NULL);
  ASSERT_EQ(0, c.num_allocated);
  ASSERT_EQ(0, c.num_chunks);
  ASSERT_EQ(0, c.nelem);
  ASSERT_EQ(size + 1, c.size);
  ASSERT_TRUE(c.head == NULL);
  ASSERT_TRUE(c.first == NULL);
}
