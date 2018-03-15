#include <gtest/gtest.h>
#include <fvar.hpp>

class test_move: public ::testing::Test {};

TEST_F(test_move, temporary)
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
  ASSERT_TRUE(ptr->func == NULL);

  --ptr;
  ASSERT_TRUE(ptr->func == &default_evaluation1);
  ASSERT_TRUE(ptr->dep_addr == gradient_structure::GRAD_LIST->get(1750));
  ASSERT_TRUE(ptr->ind_addr1 == &(gradient_structure::RETURN_PTR->v->x));
  ASSERT_TRUE(ptr->ind_addr2 == NULL);
  ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);

  --ptr;
  ASSERT_TRUE(ptr->func == &default_evaluation4);
  ASSERT_TRUE(ptr->dep_addr == &(gradient_structure::RETURN_PTR->v->x));
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
TEST_F(test_move, independents2)
{
  independent_variables independents(1, 2);
  independents(1) = 1.5;
  independents(2) = 3.5;

  gradient_structure gs;

  ASSERT_EQ(0, gradient_structure::GRAD_STACK1->total());
  ASSERT_EQ(1750, gradient_structure::GRAD_LIST->total_addresses());

  dvar_vector variables(independents);

  auto sum = [&variables]()
  {
    dvariable a(variables(1));
    dvariable b(variables(2));
    return a + b;
  };

  dvariable result = sum();
  ASSERT_EQ(4, gradient_structure::GRAD_STACK1->total());
  ASSERT_EQ(1752, gradient_structure::GRAD_LIST->total_addresses());

  ASSERT_DOUBLE_EQ(value(result), 5.0);

  grad_stack_entry* ptr = gradient_structure::GRAD_STACK1->ptr;
  ASSERT_TRUE(ptr->func == NULL);

  --ptr;
  ASSERT_TRUE(ptr->func == &default_evaluation1);
  ASSERT_TRUE(ptr->dep_addr == gradient_structure::GRAD_LIST->get(1750));
  ASSERT_DOUBLE_EQ(*ptr->dep_addr, 5.0);
  ASSERT_TRUE(ptr->ind_addr1 == &(gradient_structure::RETURN_PTR->v->x));
  ASSERT_DOUBLE_EQ(*ptr->ind_addr1, 5.0);
  ASSERT_TRUE(ptr->ind_addr2 == NULL);
  ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);

  --ptr;
  ASSERT_TRUE(ptr->func == &default_evaluation4);
  ASSERT_TRUE(ptr->dep_addr == &(gradient_structure::RETURN_PTR->v->x));
  ASSERT_DOUBLE_EQ(*ptr->dep_addr, 5.0);
  ASSERT_TRUE(ptr->ind_addr1 == gradient_structure::GRAD_LIST->get(1750));
  ASSERT_DOUBLE_EQ(*ptr->ind_addr1, 5.0);
  ASSERT_TRUE(ptr->ind_addr2 == gradient_structure::GRAD_LIST->get(1751));
  ASSERT_DOUBLE_EQ(*ptr->ind_addr2, 3.5);
  ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);

  --ptr;
  ASSERT_TRUE(ptr->func == &default_evaluation1);
  ASSERT_TRUE(ptr->dep_addr == gradient_structure::GRAD_LIST->get(1751));
  ASSERT_DOUBLE_EQ(*ptr->dep_addr, 3.5);
  ASSERT_TRUE(ptr->ind_addr1 == &(variables(2).v->x));
  ASSERT_DOUBLE_EQ(*ptr->ind_addr1, 3.5);
  ASSERT_TRUE(ptr->ind_addr2 == NULL);
  ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);

  --ptr;
  ASSERT_TRUE(ptr->func == &default_evaluation1);
  ASSERT_TRUE(ptr->dep_addr == gradient_structure::GRAD_LIST->get(1750));
  ASSERT_DOUBLE_EQ(*ptr->dep_addr, 5.0);
  ASSERT_TRUE(ptr->ind_addr1 == &(variables(1).v->x));
  ASSERT_DOUBLE_EQ(*ptr->ind_addr1, 1.5);
  ASSERT_TRUE(ptr->ind_addr2 == NULL);
  ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
}
TEST_F(test_move, independents)
{
  independent_variables independents(1, 2);
  independents(1) = 1.5;
  independents(2) = 3.5;

  gradient_structure gs;

  ASSERT_EQ(0, gradient_structure::GRAD_STACK1->total());
  ASSERT_EQ(1750, gradient_structure::GRAD_LIST->total_addresses());

  dvar_vector variables(independents);

  dvariable a(variables(1));
  dvariable b(variables(2));
  auto sum = [&a, &b]()
  {
    return a + b;
  };

  dvariable result = sum();
  ASSERT_EQ(4, gradient_structure::GRAD_STACK1->total());
  ASSERT_EQ(1753, gradient_structure::GRAD_LIST->total_addresses());

  ASSERT_DOUBLE_EQ(value(result), 5.0);

  grad_stack_entry* ptr = gradient_structure::GRAD_STACK1->ptr;
  ASSERT_TRUE(ptr->func == NULL);

  --ptr;
  ASSERT_TRUE(ptr->func == &default_evaluation1);
  ASSERT_TRUE(ptr->dep_addr == gradient_structure::GRAD_LIST->get(1752));
  ASSERT_TRUE(ptr->ind_addr1 == &(gradient_structure::RETURN_PTR->v->x));
  ASSERT_TRUE(ptr->ind_addr2 == NULL);
  ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);

  --ptr;
  ASSERT_TRUE(ptr->func == &default_evaluation4);
  ASSERT_TRUE(ptr->dep_addr == &(gradient_structure::RETURN_PTR->v->x));
  ASSERT_TRUE(ptr->ind_addr1 == gradient_structure::GRAD_LIST->get(1750));
  ASSERT_TRUE(ptr->ind_addr2 == gradient_structure::GRAD_LIST->get(1751));
  ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);

  --ptr;
  ASSERT_TRUE(ptr->func == &default_evaluation1);
  ASSERT_TRUE(ptr->dep_addr == gradient_structure::GRAD_LIST->get(1751));
  ASSERT_TRUE(ptr->ind_addr1 == &(variables(2).v->x));
  ASSERT_TRUE(ptr->ind_addr2 == NULL);
  ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);

  --ptr;
  ASSERT_TRUE(ptr->func == &default_evaluation1);
  ASSERT_TRUE(ptr->dep_addr == gradient_structure::GRAD_LIST->get(1750));
  ASSERT_TRUE(ptr->ind_addr1 == &(variables(1).v->x));
  ASSERT_TRUE(ptr->ind_addr2 == NULL);
  ASSERT_DOUBLE_EQ(ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(ptr->mult2, 0.0);
}
TEST_F(test_move, independents_gradcalc)
{
  independent_variables independents(1, 2);
  independents(1) = 1.5;
  independents(2) = 3.5;

  gradient_structure gs;

  ASSERT_EQ(0, gradient_structure::GRAD_STACK1->total());
  ASSERT_EQ(1750, gradient_structure::GRAD_LIST->total_addresses());

  dvar_vector variables(independents);

  auto sum = [&variables]()
  {
    dvariable a(variables(1));
    dvariable b(variables(2));
    return a + b;
  };

  dvariable result = sum();
  double v = value(result);

  ASSERT_DOUBLE_EQ(value(variables(1)), 1.5);
  ASSERT_DOUBLE_EQ(value(variables(2)), 3.5);

  dvector g(1, 2);
  gradcalc(2, g);

  ASSERT_DOUBLE_EQ(g(1), 1.0);
  ASSERT_DOUBLE_EQ(g(2), 1.0);
  ASSERT_DOUBLE_EQ(value(variables(1)), 1.0);
  ASSERT_DOUBLE_EQ(value(variables(2)), 1.0);
}
TEST_F(test_move, independents_gradmanual)
{
  independent_variables independents(1, 2);
  independents(1) = 1.5;
  independents(2) = 3.5;

  gradient_structure gs;

  ASSERT_EQ(0, gradient_structure::GRAD_STACK1->total());
  ASSERT_EQ(1750, gradient_structure::GRAD_LIST->total_addresses());

  dvar_vector variables(independents);

  auto sum = [&variables]()
  {
    dvariable a(variables(1));
    dvariable b(variables(2));
    return a + b;
  };

  dvariable result = sum();
  ASSERT_EQ(4, gradient_structure::GRAD_STACK1->total());
  ASSERT_EQ(1752, gradient_structure::GRAD_LIST->total_addresses());

  ASSERT_DOUBLE_EQ(value(result), 5.0);

  --gradient_structure::GRAD_STACK1->ptr;

  double_and_int* ptr = (double_and_int*)gradient_structure::get_ARRAY_MEMBLOCK_BASE();
  unsigned long int imax = gradient_structure::ARR_LIST1->get_max_last_offset() / sizeof(double_and_int);
  for (unsigned int i = 0; i < imax; ++i)
  {
     ptr->x = 0.0;
     ++ptr;
  }
  gradient_structure::GRAD_LIST->initialize();
  *gradient_structure::GRAD_STACK1->ptr->dep_addr = 1.0;

  //Sum
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->dep_addr), 1.0);
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->ind_addr1), 0.0);
  (*(gradient_structure::GRAD_STACK1->ptr->func))();
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->dep_addr), 0.0);
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->ind_addr1), 1.0);
  ASSERT_TRUE(gradient_structure::GRAD_STACK1->ptr->ind_addr2 == NULL);
  ASSERT_DOUBLE_EQ(gradient_structure::GRAD_STACK1->ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(gradient_structure::GRAD_STACK1->ptr->mult2, 0.0);

  //Addition
  --gradient_structure::GRAD_STACK1->ptr;
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->dep_addr), 1.0);
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->ind_addr1), 0.0);
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->ind_addr2), 0.0);
  (*(gradient_structure::GRAD_STACK1->ptr->func))();
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->dep_addr), 0.0);
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->ind_addr1), 1.0);
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->ind_addr2), 1.0);
  ASSERT_DOUBLE_EQ(gradient_structure::GRAD_STACK1->ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(gradient_structure::GRAD_STACK1->ptr->mult2, 0.0);

  //Constructor
  --gradient_structure::GRAD_STACK1->ptr;
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->dep_addr), 1.0);
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->ind_addr1), 0.0);
  (*(gradient_structure::GRAD_STACK1->ptr->func))();
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->dep_addr), 0.0);
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->ind_addr1), 1.0);
  ASSERT_TRUE(gradient_structure::GRAD_STACK1->ptr->ind_addr2 == NULL);
  ASSERT_DOUBLE_EQ(gradient_structure::GRAD_STACK1->ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(gradient_structure::GRAD_STACK1->ptr->mult2, 0.0);

  //Constructor
  --gradient_structure::GRAD_STACK1->ptr;
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->dep_addr), 1.0);
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->ind_addr1), 0.0);
  (*(gradient_structure::GRAD_STACK1->ptr->func))();
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->dep_addr), 0.0);
  ASSERT_DOUBLE_EQ(*(gradient_structure::GRAD_STACK1->ptr->ind_addr1), 1.0);
  ASSERT_TRUE(gradient_structure::GRAD_STACK1->ptr->ind_addr2 == NULL);
  ASSERT_DOUBLE_EQ(gradient_structure::GRAD_STACK1->ptr->mult1, 0.0);
  ASSERT_DOUBLE_EQ(gradient_structure::GRAD_STACK1->ptr->mult2, 0.0);

  //ASSERT_DOUBLE_EQ(*gradient_structure::INDVAR_LIST->get_address(1), 0.0);
  //ASSERT_DOUBLE_EQ(*gradient_structure::INDVAR_LIST->get_address(2), 0.0);
  ASSERT_DOUBLE_EQ(value(variables(1)), 1.0);
  ASSERT_DOUBLE_EQ(value(variables(2)), 1.0);
}
