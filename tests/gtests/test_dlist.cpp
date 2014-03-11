#include <gtest/gtest.h>
#include <fvar.hpp>

extern char* ddlist_space;

class test_dlist: public ::testing::Test {};

TEST_F(test_dlist, constructor)
{
  dlist lst;
  EXPECT_STRNE(0, ddlist_space);
  EXPECT_EQ(0, lst.total_addresses());
}
TEST_F(test_dlist, destructor)
{
  dlist* lst = new dlist();
  delete lst;
  lst = 0;

  EXPECT_EQ(0, ddlist_space);
}
TEST_F(test_dlist, last_remove_empty_list)
{
  dlist lst;
  EXPECT_EQ(0, lst.last_remove());
}
/*
TEST_F(test_dlist, create)
{
  dlist lst;

  //EXPECT_EQ(sizeof(double) * 2, sizeof(dlink));

  dlink* a = lst.create();
  //EXPECT_EQ((intptr_t)ddlist_space + (0 * sizeof(double)), (intptr_t)a);
  EXPECT_EQ((intptr_t)ddlist_space + (0 * sizeof(dlink)), (intptr_t)a);
  EXPECT_EQ(0, (intptr_t)a->previous());

  dlink* b = lst.create();
  //EXPECT_EQ((intptr_t)ddlist_space + (2 * sizeof(double)), (intptr_t)b);
  EXPECT_EQ((intptr_t)ddlist_space + (1 * sizeof(dlink)), (intptr_t)b);
  EXPECT_EQ(0, (intptr_t)b->previous());

  dlink* c = lst.create();
  //EXPECT_EQ((intptr_t)ddlist_space + (4 * sizeof(double)), (intptr_t)c);
  EXPECT_EQ((intptr_t)ddlist_space + (2 * sizeof(dlink)), (intptr_t)c);
  EXPECT_EQ(0, (intptr_t)c->previous());
}
*/
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
