#include <gtest/gtest.h>
#include <fvar.hpp>

class test_dlist: public ::testing::Test {};

TEST_F(test_dlist, default)
{
  dlist dl;

  ASSERT_TRUE(dl.last_remove() == nullptr);
  ASSERT_EQ(dl.total_addresses(), 0);
}
TEST_F(test_dlist, create)
{
  dlist dl;

  dl.create();

  ASSERT_EQ(dl.total_addresses(), 1);
  ASSERT_TRUE(dl.last_remove() == nullptr);
}
TEST_F(test_dlist, create_append_remove)
{
  dlist dl;

  dlink* link = dl.create();
  dl.append(link);

  ASSERT_EQ(dl.total_addresses(), 1);
  dlink* link2 = dl.last_remove();
  ASSERT_EQ(dl.total_addresses(), 1);

  ASSERT_TRUE(link == link2);
}
