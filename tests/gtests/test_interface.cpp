#include <gtest/gtest.h>
#include <fvar.hpp>
#include <chrono>
#include <future>

class test_interface: public ::testing::Test {};

TEST_F(test_interface, thread_funnel)
{
  using namespace std::chrono_literals;

  unsigned int id = gradient_structure::id;

  gradient_structure** gradients = new gradient_structure*[10];
  for (int i = 0; i < 10; ++i)
  {
    gradients[i] = new gradient_structure();
  }
  EXPECT_EQ(id + 10, gradient_structure::id);

  std::vector<std::future<double>> futures;

  for (int i = 0; i < 10; ++i)
  {
    // Use function parameter to copy memory for the thread 
    auto f = std::async([&gradients](const int i)
    {
      gradient_structure* gs = gradients[i];
      gradient_structure::_instance = gs;
      gradient_structure::fp = gs->get_fp();
      gradient_structure::GRAD_STACK1 = gs->get_GRAD_STACK1();

      independent_variables independents(1, 1);

      independents[1] = 0.5;

      dvar_vector variables(independents);

      dvariable result = i * variables[1];

      dvector g(1, 1);

      gradcalc(1, g);

      std::this_thread::sleep_for((std::rand() % 5) * 1000ms);

      return g(1);
    }, i);
    //f.wait();
    futures.emplace_back(std::move(f));
  }

  int index = 0;
  for (auto& f : futures)
  {
    ASSERT_EQ((int)f.get(), index);
    ++index;
  }

  delete [] gradients;
  gradients = nullptr;
}
