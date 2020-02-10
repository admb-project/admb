#include <gtest/gtest.h>
#include "fvar.hpp"

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

  const size_t overhead = 12+sizeof(char*);
  const size_t chunk_size= 65000-overhead;
  const size_t expected_nelem = chunk_size / size;

  dfpool pool(size);
  pool.grow();

  ASSERT_EQ(pool.on_dfpool_vector(), 0);
  ASSERT_EQ(pool.nvar, 0);
  ASSERT_TRUE(pool.last_chunk != NULL);
  ASSERT_EQ(pool.num_allocated, 0);
  ASSERT_EQ(pool.num_chunks, 1);
  ASSERT_EQ(pool.nelem, expected_nelem);
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
  ASSERT_EQ(count, expected_nelem);
}
TEST_F(test_dfpool, constructor_size_alloc)
{
  size_t size = sizeof(double);

  const size_t overhead = 12+sizeof(char*);
  const size_t chunk_size= 65000-overhead;
  const size_t expected_nelem = chunk_size / size;

  dfpool pool(size);
  pool.grow();

  void* original_head = static_cast<void*>(pool.head);

  dfpool::link* p = pool.head; 
  for (int i = 0; i < expected_nelem; ++i)
  {
    void* ptr = pool.alloc();
    ASSERT_TRUE(static_cast<void*>(p) == static_cast<void*>(ptr));

    p = p->next;
  }

  ASSERT_EQ(pool.on_dfpool_vector(), 0);
  ASSERT_EQ(pool.nvar, 0);
  ASSERT_TRUE(pool.last_chunk != NULL);
  ASSERT_EQ(pool.num_allocated, expected_nelem);
  ASSERT_EQ(pool.num_chunks, 1);
  ASSERT_EQ(pool.nelem, expected_nelem);
  ASSERT_EQ(pool.size, size);
  ASSERT_TRUE(static_cast<void*>(pool.first) == original_head);
  ASSERT_TRUE(pool.head == NULL);
}
TEST_F(test_dfpool, constructor_size_alloc_grow_2x)
{
  size_t size = sizeof(double);

  const size_t overhead = 12+sizeof(char*);
  const size_t chunk_size= 65000-overhead;
  const size_t expected_nelem = chunk_size / size;

  dfpool pool(size);
  pool.grow();

  void* original_head = static_cast<void*>(pool.head);

  dfpool::link* p = pool.head; 
  for (int i = 0; i < expected_nelem; ++i)
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
  ASSERT_EQ(pool.num_allocated, expected_nelem + 1);
  ASSERT_EQ(pool.num_chunks, 2);
  ASSERT_EQ(pool.nelem, expected_nelem);
  ASSERT_EQ(pool.size, size);
  ASSERT_TRUE(static_cast<void*>(pool.first) != original_head);
  ASSERT_TRUE(pool.head != NULL);
}
TEST_F(test_dfpool, dvar_vector1to4)
{
  gradient_structure gs;

  dvar_vector v(1, 4); 
}
