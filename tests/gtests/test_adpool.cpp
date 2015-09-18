#include <gtest/gtest.h>
#include <adpool.h>

class test_adpool: public ::testing::Test {};

TEST_F(test_adpool, default_constructor_set_size)
{
  //ASSERT_EQ(0, adpool::num_adpools);

  adpool a;
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.size);
  ASSERT_EQ(0, a.head);
  ASSERT_TRUE(a.first == NULL);
  ASSERT_EQ(0, a.on_adpool_vector());
  ASSERT_EQ(0, a.last_chunk);
  ASSERT_EQ(0, a.num_chunks);
  ASSERT_EQ(0, a.nvar);
  ASSERT_EQ(0, a.nelem);

  a.set_size(1);
  ASSERT_EQ(1, a.size);

  a.set_size(-1);
  ASSERT_LT(0, a.size);

  a.set_size(0);
  ASSERT_EQ(0, a.size);
}
TEST_F(test_adpool, constructor_set_size)
{
  adpool a(sizeof(double));
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(sizeof(double), a.size);
  ASSERT_EQ(0, a.head);
  ASSERT_TRUE(a.first == NULL);
  ASSERT_EQ(0, a.on_adpool_vector());
  ASSERT_EQ(0, a.last_chunk);
  ASSERT_EQ(0, a.num_chunks);
  ASSERT_EQ(0, a.depth_check());
  ASSERT_TRUE(a.nelem == 0);
}
TEST_F(test_adpool, constructor_size_small)
{
  adpool a(0);
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(sizeof(adpool::link*), a.size);
  ASSERT_EQ(0, a.head);
  ASSERT_TRUE(a.first == NULL);
  ASSERT_EQ(0, a.on_adpool_vector());
  ASSERT_EQ(0, a.last_chunk);
  ASSERT_EQ(0, a.num_chunks);
  ASSERT_EQ(0, a.depth_check());
  ASSERT_TRUE(a.nelem == 0);
}
TEST_F(test_adpool, grow_deallocate)
{
  adpool a;
  const size_t n = 2;
  size_t size = sizeof(double) * (6 * n + 5);
  a.set_size(size);

  a.grow();
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(size, a.size);
  ASSERT_TRUE(a.head != NULL);
  ASSERT_TRUE(a.first != NULL);
  ASSERT_EQ((void*)a.head, (void*)a.first);
  ASSERT_EQ(0, a.on_adpool_vector());
  ASSERT_TRUE(a.last_chunk != NULL);
  ASSERT_EQ(1, a.num_chunks);
  ASSERT_EQ(a.depth_check(), a.nelem);
  a.deallocate();
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.size);
  ASSERT_TRUE(a.head == NULL);
  ASSERT_TRUE(a.first == NULL);
  ASSERT_EQ(0, a.on_adpool_vector());
  ASSERT_TRUE(a.last_chunk == NULL);
  ASSERT_EQ(0, a.num_chunks);
  ASSERT_TRUE(a.depth_check() == 0);
  ASSERT_TRUE(a.nelem == 0);
}
TEST_F(test_adpool, grow2x_deallocate)
{
  adpool a;
  const size_t n = 2;
  size_t size = sizeof(double) * (6 * n + 5);
  a.set_size(size);

  a.grow();
  a.grow();
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(size, a.size);
  ASSERT_TRUE(a.head != NULL);
  ASSERT_TRUE(a.first != NULL);
  ASSERT_EQ((void*)a.head, (void*)a.first);
  ASSERT_EQ(0, a.on_adpool_vector());
  ASSERT_TRUE(a.last_chunk != NULL);
  ASSERT_EQ(2, a.num_chunks);
  ASSERT_EQ(a.depth_check(), a.nelem);
  a.deallocate();
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.size);
  ASSERT_TRUE(a.head == NULL);
  ASSERT_TRUE(a.first == NULL);
  ASSERT_EQ(0, a.on_adpool_vector());
  ASSERT_TRUE(a.last_chunk == NULL);
  ASSERT_EQ(0, a.num_chunks);
  ASSERT_TRUE(a.depth_check() == 0);
  ASSERT_TRUE(a.nelem == 0);
}
TEST_F(test_adpool, grow3x_deallocate)
{
  adpool a;
  const size_t n = 2;
  size_t size = sizeof(double) * (6 * n + 5);
  a.set_size(size);

  ASSERT_EQ(0, a.depth_check());
  ASSERT_EQ(0, a.num_chunks);
  a.grow();
  ASSERT_EQ(1, a.num_chunks);
  a.grow();
  ASSERT_EQ(2, a.num_chunks);
  a.grow();
  ASSERT_EQ(3, a.num_chunks);

  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(size, a.size);
  ASSERT_TRUE(a.head != NULL);
  ASSERT_TRUE(a.first != NULL);
  ASSERT_EQ((void*)a.head, (void*)a.first);
  ASSERT_EQ(0, a.on_adpool_vector());
  ASSERT_TRUE(a.last_chunk != NULL);
  ASSERT_EQ(3, a.num_chunks);
  ASSERT_EQ(a.depth_check(), a.nelem);
  a.deallocate();
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.size);
  ASSERT_TRUE(a.head == NULL);
  ASSERT_TRUE(a.first == NULL);
  ASSERT_EQ(0, a.on_adpool_vector());
  ASSERT_TRUE(a.last_chunk == NULL);
  ASSERT_EQ(0, a.num_chunks);
  ASSERT_TRUE(a.depth_check() == 0);
  ASSERT_TRUE(a.nelem == 0);
}
TEST_F(test_adpool, alloc_deallocate)
{
  adpool a;
  const size_t n = 2;
  size_t size = sizeof(double) * (6 * n + 5);
  a.set_size(size);

  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());

  a.alloc();
  ASSERT_EQ(1, a.num_allocated);

  a.deallocate();
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());
}
TEST_F(test_adpool, alloc2x_deallocate)
{
  adpool a;
  const size_t n = 2;
  size_t size = sizeof(double) * (6 * n + 5);
  a.set_size(size);

  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());

  a.alloc();
  a.alloc();
  ASSERT_EQ(2, a.num_allocated);

  a.deallocate();
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());
}
TEST_F(test_adpool, alloc3x_deallocate)
{
  adpool a;
  const size_t n = 2;
  size_t size = sizeof(double) * (6 * n + 5);
  a.set_size(size);

  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());

  a.alloc();
  a.alloc();
  a.alloc();
  ASSERT_EQ(3, a.num_allocated);

  a.deallocate();
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());
}
TEST_F(test_adpool, intptr_t)
{
  char* allocated = new char[8]; 
  intptr_t address = (intptr_t)allocated;
  char* save[100]; 
  memcpy(&save[10], &address, sizeof(intptr_t));

  intptr_t retrived = 0;
  memcpy(&retrived, &save[10], sizeof(intptr_t));

  char* allocated2 = (char*)retrived;

  ASSERT_EQ(address, retrived);
  ASSERT_EQ(allocated, allocated2);

  delete [] allocated2;
  allocated2 = NULL;
}
TEST_F(test_adpool, alloc_free_deallocate)
{
  adpool a;
  const size_t n = 2;
  size_t size = sizeof(double) * (6 * n + 5);
  a.set_size(size);

  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());

  void* b = a.alloc();
  ASSERT_EQ(1, a.num_allocated);
  ASSERT_EQ(a.depth_check(), a.nelem - 1);

  a.free(b);
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(a.depth_check(), a.nelem);

  a.deallocate();
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());
}
TEST_F(test_adpool, alloc_free2x1_deallocate)
{
  adpool a;
  const size_t n = 2;
  size_t size = sizeof(double) * (6 * n + 5);
  a.set_size(size);

  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());

  void* b1 = a.alloc();
  void* b2 = a.alloc();
  ASSERT_EQ(2, a.num_allocated);
  ASSERT_EQ(a.depth_check(), a.nelem - 2);

  a.free(b1);
  ASSERT_EQ(1, a.num_allocated);
  ASSERT_EQ(a.depth_check(), a.nelem - 1);

  a.deallocate();
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());
}
TEST_F(test_adpool, alloc_free2x2_deallocate)
{
  adpool a;
  const size_t n = 2;
  size_t size = sizeof(double) * (6 * n + 5);
  a.set_size(size);

  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());

  void* b1 = a.alloc();
  void* b2 = a.alloc();
  ASSERT_EQ(2, a.num_allocated);
  ASSERT_EQ(a.depth_check(), a.nelem - 2);

  a.free(b2);
  ASSERT_EQ(1, a.num_allocated);
  ASSERT_EQ(a.depth_check(), a.nelem - 1);

  a.deallocate();
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());
}
TEST_F(test_adpool, alloc_free2xstart_deallocate)
{
  adpool a;
  const size_t n = 2;
  size_t size = sizeof(double) * (6 * n + 5);
  a.set_size(size);

  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());

  void* start = a.alloc();
  void* b2 = a.alloc();
  void* b3 = a.alloc();
  ASSERT_EQ(3, a.num_allocated);
  ASSERT_EQ(a.depth_check(), a.nelem - 3);

  a.free(start);
  ASSERT_EQ(2, a.num_allocated);
  ASSERT_EQ(a.depth_check(), a.nelem - 2);

  a.deallocate();
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());
}
TEST_F(test_adpool, alloc_free2xmiddle_deallocate)
{
  adpool a;
  const size_t n = 2;
  size_t size = sizeof(double) * (6 * n + 5);
  a.set_size(size);

  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());

  void* b1 = a.alloc();
  void* middle = a.alloc();
  void* b3 = a.alloc();
  ASSERT_EQ(3, a.num_allocated);
  ASSERT_EQ(a.depth_check(), a.nelem - 3);

  a.free(middle);
  ASSERT_EQ(2, a.num_allocated);
  ASSERT_EQ(a.depth_check(), a.nelem - 2);

  a.deallocate();
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());
}
TEST_F(test_adpool, alloc_free2xend_deallocate)
{
  adpool a;
  const size_t n = 2;
  size_t size = sizeof(double) * (6 * n + 5);
  a.set_size(size);

  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());

  void* b1 = a.alloc();
  void* b2 = a.alloc();
  void* end = a.alloc();
  ASSERT_EQ(3, a.num_allocated);
  ASSERT_EQ(a.depth_check(), a.nelem - 3);

  a.free(end);
  ASSERT_EQ(2, a.num_allocated);
  ASSERT_EQ(a.depth_check(), a.nelem - 2);

  a.deallocate();
  ASSERT_EQ(0, a.num_allocated);
  ASSERT_EQ(0, a.depth_check());
}
