#include <gtest/gtest.h>
#include <fvar.hpp>

class test_move: public ::testing::Test {};

TEST_F(test_move, default_constructor)
{
  gradient_structure gs;

  auto sum = [](const double lhs, const double rhs)
  {
    dvariable a(lhs);
    dvariable b(rhs);
    return a + b;
  };

  ASSERT_EQ(0, gradient_structure::GRAD_STACK1->total());
  ASSERT_EQ(1750, gradient_structure::GRAD_LIST->total_addresses());
  dvariable result = sum(1.5, 3.5);
  ASSERT_EQ(4, gradient_structure::GRAD_STACK1->total());
  ASSERT_EQ(1752, gradient_structure::GRAD_LIST->total_addresses());

  ASSERT_DOUBLE_EQ(value(result), 5.0);

  grad_stack_entry* ptr = gradient_structure::GRAD_STACK1->ptr;

  --ptr;
  ASSERT_TRUE(ptr->func == &default_evaluation1);
  ASSERT_TRUE(ptr->dep_addr == gradient_structure::GRAD_LIST->get(1750));
  //ASSERT_TRUE(ptr->ind_addr1 == );
  ASSERT_TRUE(ptr->ind_addr2 == NULL);
  ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);

  --ptr;
  ASSERT_TRUE(ptr->func == &default_evaluation4);
  //ASSERT_TRUE(ptr->dep_addr == );
  ASSERT_TRUE(ptr->ind_addr1 == gradient_structure::GRAD_LIST->get(1750));
  ASSERT_TRUE(ptr->ind_addr2 == gradient_structure::GRAD_LIST->get(1751));
  ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);

  --ptr;
  ASSERT_TRUE(ptr->func == &default_evaluation0);
  ASSERT_TRUE(ptr->dep_addr == gradient_structure::GRAD_LIST->get(1751));
  ASSERT_TRUE(ptr->ind_addr1 == NULL);
  ASSERT_TRUE(ptr->ind_addr2 == NULL);
  ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);

  --ptr;
  ASSERT_TRUE(ptr->func == &default_evaluation0);
  ASSERT_TRUE(ptr->dep_addr == gradient_structure::GRAD_LIST->get(1750));
  ASSERT_TRUE(ptr->ind_addr1 == NULL);
  ASSERT_TRUE(ptr->ind_addr2 == NULL);
  ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
}
