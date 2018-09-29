#include <gtest/gtest.h>
#include <fvar.hpp>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_dlist: public ::testing::Test {};

TEST_F(test_dlist, constructor)
{
  dlist lst;
  EXPECT_EQ(0, lst.total_addresses());
}
TEST_F(test_dlist, sizes)
{
  EXPECT_EQ(sizeof(double) * 2, sizeof(dlink));
}
TEST_F(test_dlist, create)
{
  ad_exit=&test_ad_exit;
  gradient_structure gs;
  ASSERT_TRUE(gradient_structure::GRAD_LIST->last_remove() == NULL);

  dlink* ptr = gradient_structure::GRAD_LIST->create();
  ASSERT_TRUE(ptr->previous() == NULL);

  size_t total_addresses = gradient_structure::GRAD_LIST->total_addresses();
  for (int i = total_addresses; i < gradient_structure::get_MAX_DLINKS(); ++i)
  {
    dlink* next = gradient_structure::GRAD_LIST->create();
    ASSERT_TRUE(next->previous() == NULL);

    ++ptr;
    ASSERT_TRUE(next == ptr);

    dlink* lst = (dlink*)gradient_structure::GRAD_LIST->get(i);
    ASSERT_TRUE(next == lst);
  }

  //Exceed maximum dlinks allocated
  EXPECT_DEATH(gradient_structure::GRAD_LIST->create(), "Assertion");
}
TEST_F(test_dlist, destructor)
{
  {
    dlist* lst = new dlist();
    delete lst;
    lst = 0;
  }
}
TEST_F(test_dlist, last_remove_empty_list)
{
  dlist lst;
  EXPECT_EQ(0, lst.last_remove());
}
TEST_F(test_dlist, append)
{
  dlist lst;

  dlink* a = lst.create();
  dlink* lasta = lst.append(a);
  EXPECT_EQ((intptr_t)lasta, (intptr_t)a);
  EXPECT_EQ(0, (intptr_t)a->previous());

  dlink* b = lst.create();
  dlink* lastb = lst.append(b);
  EXPECT_EQ((intptr_t)lastb, (intptr_t)b);
  EXPECT_EQ((intptr_t)a, (intptr_t)b->previous());

  dlink* c = lst.create();
  dlink* lastc = lst.append(c);
  EXPECT_EQ((intptr_t)lastc, (intptr_t)c);
  EXPECT_EQ((intptr_t)b, (intptr_t)c->previous());
}
TEST_F(test_dlist, remove)
{
  dlist lst;

  dlink* a = lst.create();
  lst.append(a);

  dlink* b = lst.create();
  lst.append(b);

  dlink* c = lst.create();
  lst.append(c);

  EXPECT_EQ((intptr_t)c, (intptr_t)lst.last_remove());
  EXPECT_EQ((intptr_t)b, (intptr_t)lst.last_remove());
  EXPECT_EQ((intptr_t)a, (intptr_t)lst.last_remove());
}
TEST_F(test_dlist, dvariable)
{
  gradient_structure gs;

  EXPECT_EQ(gradient_structure::GRAD_LIST->total_addresses(), 1750);
  dvariable variable;
  EXPECT_EQ(gradient_structure::GRAD_LIST->total_addresses(), 1751);
  EXPECT_TRUE(static_cast<void*>(gradient_structure::GRAD_LIST->get(1750)) == static_cast<void*>(variable.v));
  dlink* link = (dlink*)variable.v;
  EXPECT_TRUE(link->previous() == NULL);
  EXPECT_TRUE(link->get_address() == variable.v);
}
TEST_F(test_dlist, dvariable2x)
{
  gradient_structure gs;

  EXPECT_EQ(gradient_structure::GRAD_LIST->total_addresses(), 1750);
  dvariable variable;
  dvariable variable2;
  EXPECT_EQ(gradient_structure::GRAD_LIST->total_addresses(), 1752);

  EXPECT_TRUE(static_cast<void*>(gradient_structure::GRAD_LIST->get(1750)) == static_cast<void*>(variable.v));
  EXPECT_TRUE(static_cast<void*>(gradient_structure::GRAD_LIST->get(1751)) == static_cast<void*>(variable2.v));

  dlink* link = (dlink*)variable.v;
  EXPECT_TRUE(link->previous() == NULL);
  EXPECT_TRUE(link->get_address() == variable.v);

  dlink* link2 = (dlink*)variable2.v;
  EXPECT_TRUE(link2->previous() == NULL);
  EXPECT_TRUE(link2->get_address() == variable2.v);
}
TEST_F(test_dlist, dvariable2x_scoped)
{
  gradient_structure gs;

  EXPECT_EQ(gradient_structure::GRAD_LIST->total_addresses(), 1750);
  {
    dvariable variable;
    dvariable variable2;
  }
  EXPECT_EQ(gradient_structure::GRAD_LIST->total_addresses(), 1752);

  dlink* link = (dlink*)gradient_structure::GRAD_LIST->get(1750);
  dlink* link2 = (dlink*)gradient_structure::GRAD_LIST->get(1751);

  EXPECT_TRUE(link->previous() == link2);
  EXPECT_TRUE(link2->previous() == NULL);
}
