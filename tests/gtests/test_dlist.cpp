#include <gtest/gtest.h>
#include <thread>
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
TEST_F(test_dlist, thread)
{
  auto f = [](const int id)
  {
    grad_stack gs(100, sizeof(double), 1, 0, 0, id);

    dlink* link = gs.GRAD_LIST->create();
    gs.GRAD_LIST->append(link);

    ASSERT_EQ(gs.GRAD_LIST->total_addresses(), 1);
    dlink* link2 = gs.GRAD_LIST->last_remove();
    ASSERT_EQ(gs.GRAD_LIST->total_addresses(), 1);

    ASSERT_TRUE(link == link2);
  };
  std::thread t0(f, 0);
  t0.join();
}
TEST_F(test_dlist, thread5x)
{
  std::srand(std::time(nullptr));
  auto f = [](const int id)
  {
    int random0 = std::rand() % 3;

    grad_stack gs(100, sizeof(double), 3, 0, 0, id);

    dlink* link0 = gs.GRAD_LIST->create();
    gs.GRAD_LIST->append(link0);
    dlink* link1 = gs.GRAD_LIST->create();
    gs.GRAD_LIST->append(link1);
    dlink* link2 = gs.GRAD_LIST->create();
    gs.GRAD_LIST->append(link2);
    ASSERT_EQ(gs.GRAD_LIST->total_addresses(), 3);

    std::this_thread::sleep_for (std::chrono::seconds(random0));

    dlink* link_last = gs.GRAD_LIST->last_remove();
    ASSERT_EQ(gs.GRAD_LIST->total_addresses(), 3);

    ASSERT_TRUE(link2 == link_last);
  };
  std::thread t0(f, 0);
  std::thread t3(f, 3);
  std::thread t1(f, 1);
  std::thread t4(f, 4);
  std::thread t2(f, 2);
  t0.join();
  t1.join();
  t2.join();
  t3.join();
  t4.join();
}
