#include <gtest/gtest.h>
#include <fvar.hpp>
#include <adthread.h>

class test_adthread_manager: public ::testing::Test {};

TEST_F(test_adthread_manager, constructor)
{
  adpthread_manager am(1, 1);
}
