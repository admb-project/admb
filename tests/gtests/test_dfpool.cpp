#include <gtest/gtest.h>
#include "fvar.hpp"

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dfpool: public ::testing::Test {};

TEST_F(test_dfpool, constructor)
{
  dfpool pool;

  ASSERT_EQ(pool.on_dfpool_vector(), 0);
  ASSERT_EQ(pool.nvar, 0);
  ASSERT_TRUE(pool.last_chunk == NULL);
  ASSERT_EQ(pool.num_allocated, 0);
  ASSERT_EQ(pool.num_chunks, 0);
  ASSERT_EQ(pool.nelem, 0);
  ASSERT_EQ(pool.size, 0);
  ASSERT_TRUE(pool.head == NULL);
  ASSERT_TRUE(pool.first == NULL);
}
TEST_F(test_dfpool, constructor_grow_with_zero_size)
{
  ad_exit=&test_ad_exit;

  dfpool pool;

  ASSERT_ANY_THROW({
    pool.grow();
  });
}
TEST_F(test_dfpool, constructor_set_size)
{
  size_t size = sizeof(double);

  dfpool pool;

  pool.set_size(size);

  ASSERT_EQ(pool.on_dfpool_vector(), 0);
  ASSERT_EQ(pool.nvar, 0);
  ASSERT_TRUE(pool.last_chunk == NULL);
  ASSERT_EQ(pool.num_allocated, 0);
  ASSERT_EQ(pool.num_chunks, 0);
  ASSERT_EQ(pool.nelem, 0);
  ASSERT_EQ(pool.size, size);
  ASSERT_TRUE(pool.head == NULL);
  ASSERT_TRUE(pool.first == NULL);
}
TEST_F(test_dfpool, constructor_size)
{
  size_t size = sizeof(double);
  dfpool pool(size);

  ASSERT_EQ(pool.on_dfpool_vector(), 0);
  ASSERT_EQ(pool.nvar, 0);
  ASSERT_TRUE(pool.last_chunk == NULL);
  ASSERT_EQ(pool.num_allocated, 0);
  ASSERT_EQ(pool.num_chunks, 0);
  ASSERT_EQ(pool.nelem, 0);
  ASSERT_EQ(pool.size, size);
  ASSERT_TRUE(pool.head == NULL);
  ASSERT_TRUE(pool.first == NULL);
}
TEST_F(test_dfpool, constructor_size_set_size)
{
  size_t size = sizeof(double);
  dfpool pool(size);
  pool.set_size(size * 2);

  ASSERT_EQ(pool.on_dfpool_vector(), 0);
  ASSERT_EQ(pool.nvar, 0);
  ASSERT_TRUE(pool.last_chunk == NULL);
  ASSERT_EQ(pool.num_allocated, 0);
  ASSERT_EQ(pool.num_chunks, 0);
  ASSERT_EQ(pool.nelem, 0);
  ASSERT_EQ(pool.size, size);
  ASSERT_TRUE(pool.head == NULL);
  ASSERT_TRUE(pool.first == NULL);
}
TEST_F(test_dfpool, constructor_size_grow)
{
  size_t size = sizeof(double);
  dfpool pool(size);
  pool.grow();

  ASSERT_EQ(pool.on_dfpool_vector(), 0);
  ASSERT_EQ(pool.nvar, 0);
  ASSERT_TRUE(pool.last_chunk != NULL);
  ASSERT_EQ(pool.num_allocated, 0);
  ASSERT_EQ(pool.num_chunks, 1);
  ASSERT_EQ(pool.nelem, 8122);
  ASSERT_EQ(pool.size, size);
  ASSERT_TRUE(static_cast<void*>(pool.head) == static_cast<void*>(pool.first));
  ASSERT_TRUE(pool.head != NULL);
  size_t count = 0;
  dfpool::link* p = pool.head; 
  while (p != NULL)
  {
    p = p->next;
    ++count;
  }
  ASSERT_EQ(count, 8122);
}
TEST_F(test_dfpool, constructor_size_alloc)
{
  size_t size = sizeof(double);
  dfpool pool(size);
  pool.grow();

  void* original_head = static_cast<void*>(pool.head);

  dfpool::link* p = pool.head; 
  for (int i = 0; i < 8122; ++i)
  {
    void* ptr = pool.alloc();
    ASSERT_TRUE(static_cast<void*>(p) == static_cast<void*>(ptr));

    p = p->next;
  }

  ASSERT_EQ(pool.on_dfpool_vector(), 0);
  ASSERT_EQ(pool.nvar, 0);
  ASSERT_TRUE(pool.last_chunk != NULL);
  ASSERT_EQ(pool.num_allocated, 8122);
  ASSERT_EQ(pool.num_chunks, 1);
  ASSERT_EQ(pool.nelem, 8122);
  ASSERT_EQ(pool.size, size);
  ASSERT_TRUE(static_cast<void*>(pool.first) == original_head);
  ASSERT_TRUE(pool.head == NULL);
}
TEST_F(test_dfpool, constructor_size_alloc_grow_2x)
{
  size_t size = sizeof(double);
  dfpool pool(size);
  pool.grow();

  void* original_head = static_cast<void*>(pool.head);

  dfpool::link* p = pool.head; 
  for (int i = 0; i < 8122; ++i)
  {
    void* ptr = pool.alloc();
    ASSERT_TRUE(static_cast<void*>(p) == static_cast<void*>(ptr));

    p = p->next;
  }
  pool.alloc();
  //ASSERT_TRUE(p->next!= pool.head);

  ASSERT_EQ(pool.on_dfpool_vector(), 0);
  ASSERT_EQ(pool.nvar, 0);
  ASSERT_TRUE(pool.last_chunk != NULL);
  ASSERT_EQ(pool.num_allocated, 8123);
  ASSERT_EQ(pool.num_chunks, 2);
  ASSERT_EQ(pool.nelem, 8122);
  ASSERT_EQ(pool.size, size);
  ASSERT_TRUE(static_cast<void*>(pool.first) != original_head);
  ASSERT_TRUE(pool.head != NULL);
}
TEST_F(test_dfpool, arr_link)
{
  arr_link link;
}
