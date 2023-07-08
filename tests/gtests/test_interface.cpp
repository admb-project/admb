#include <gtest/gtest.h>
#include <fvar.hpp>
#include <chrono>
#include <future>
#include <minimizer.h>

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
double model(std::function<void()>&& f)
{
  f();
  return 0;
}
TEST_F(test_interface, thread_funnel_model_function)
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
    auto f = std::async(model, [](){ return 0; });
    //f.wait();
    futures.emplace_back(std::move(f));
  }

  int index = 0;
  for (auto& f : futures)
  {
    ASSERT_EQ((int)f.get(), 0);
    ++index;
  }

  delete [] gradients;
  gradients = nullptr;
}
double model2(std::function<double(const int)>&& f, const int i)
{
  return f(i);
}
TEST_F(test_interface, thread_funnel_model2_function)
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
    auto f = std::async(model2, [&gradients](const int i)->double
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
TEST_F(test_interface, interface)
{
  char* argv[] = { "model" };
  minimizer m(1, argv);

  dvector x("{ -1, 0, 1, 2, 3, 4, 5, 6, 7, 8 }");
  dvector y("{ 1.4, 4.7, 5.1, 8.3, 9.0, 14.5, 14.0, 13.4, 19.2, 18.0 }");

  param_init_number b0("b0");
  param_init_number b1("b1");
  objective_function_value f("f");

  m.minimize([&]()
  {
    auto yhat = b0 + b1 * x;
    f = regression(y, yhat);
  });

  cout << "b0: " << value(b0) << endl;
  cout << "b1: " << value(b1) << endl;
  cout << "f: " << value(f) << endl;
}
TEST_F(test_interface, interface_duplicate)
{
  char* argv[] = { "model" };
  minimizer m(1, argv);

  dvector x("{ -1, 0, 1, 2, 3, 4, 5, 6, 7, 8 }");
  dvector y("{ 1.4, 4.7, 5.1, 8.3, 9.0, 14.5, 14.0, 13.4, 19.2, 18.0 }");

  param_init_number b0("b0");
  param_init_number b1("b1");
  objective_function_value f("f");

  m.minimize([&]()
  {
    auto yhat = b0 + b1 * x;
    f = regression(y, yhat);
  });

  cout << "b0: " << value(b0) << endl;
  cout << "b1: " << value(b1) << endl;
  cout << "f: " << value(f) << endl;
}
class my_initial_params: public initial_params
{
public:
  void set_value(const dvar_vector&, const int&, const dvariable& pen) {}
  void dev_correction(const dmatrix&, const int&) {}
  void set_simulation_bounds(const dmatrix& symbds, const int& ii) {}
  void set_value_inv(const dvector&, const int&) {}
  void add_value(const dvector&, const int&) {}
  void add_value(const dvector&, const dvector&, const int&, const double&, const dvector&) {}
  void get_jacobian(const dvector&, const dvector&, const int&) {}
  void copy_value_to_vector(const dvector&, const int&) {}
  void restore_value_from_vector(const dvector&, const int&) {}
  void sd_scale(const dvector& d, const dvector& x, const int& ii) {}
  void sd_vscale(const dvar_vector& d,const dvar_vector& x, const int& ii) {}
  void mc_scale(const dvector& d, const dvector& x, const int& ii) {}
  void curv_scale(const dvector& d, const dvector& x, const int& ii) {}
  void hess_scale(const dvector& d, const dvector& x, const int& ii) {}
  unsigned int size_count() const { return 1; }
  void save_value(ofstream& ofs) {}
  void bsave_value(uostream& uos) {}
  void save_value(const ofstream& ofs, int prec) {}
  void save_value(const ofstream& ofs, int prec,const dvector&, int& offset) {}
  const char* label() { return nullptr; }
  void restore_value(const ifstream& ifs) {}
};
/*
TEST_F(test_interface, minimium)
{
  char* argv[] = { "model", "-nohess" };
  minimizer m(2, argv);

  //MUST preallocate total number of independents
  initial_params::varsptr.allocate(2);

  EXPECT_EQ(0, initial_params::nvarcalc());
  my_initial_params b0;

  EXPECT_EQ(0, initial_params::nvarcalc());
  b0.add_to_list();
  EXPECT_EQ(1, initial_params::nvarcalc());
  b0.add_to_list();
  EXPECT_EQ(2, initial_params::nvarcalc());

  objective_function_value f("f");
  EXPECT_EQ(2, initial_params::nvarcalc());
  m.minimize([&]()
  {
  });
}
*/
void minimize()
{
  char* argv[] = { "model" };
  minimizer m(1, argv);

  dvector x("{ -1, 0, 1, 2, 3, 4, 5, 6, 7, 8 }");
  dvector y("{ 1.4, 4.7, 5.1, 8.3, 9.0, 14.5, 14.0, 13.4, 19.2, 18.0 }");

  param_init_number b0("b0");
  param_init_number b1("b1");
  objective_function_value f("f");

  m.minimize([&]()
  {
    auto yhat = b0 + b1 * x;
    f = regression(y, yhat);
  });

  cout << "b0: " << value(b0) << endl;
  cout << "b1: " << value(b1) << endl;
  cout << "f: " << value(f) << endl;
}
TEST_F(test_interface, minimize_function)
{
  minimize();
}
void test_parameter(std::function<int(void)>&& func)
{
  ASSERT_EQ(func(), 2);
}
TEST_F(test_interface, test_parameter)
{
  test_parameter([]()->int { return 2; });
}
void minimize2(std::function<void(void)>&& func)
{
  char* argv[] = { "model" };
  cout << __FILE__ << ':' << __LINE__ << endl;
  minimizer m(1, argv);
  cout << __FILE__ << ':' << __LINE__ << endl;

  m.minimize(func);
  cout << __FILE__ << ':' << __LINE__ << endl;
}
TEST_F(test_interface, minimize2_function)
{
  /*
  minimize2([]()
  {
    dvector x("{ -1, 0, 1, 2, 3, 4, 5, 6, 7, 8 }");
    dvector y("{ 1.4, 4.7, 5.1, 8.3, 9.0, 14.5, 14.0, 13.4, 19.2, 18.0 }");

    param_init_number b0("b0");
    param_init_number b1("b1");
    objective_function_value f("f");

    auto yhat = b0 + b1 * x;
    f = regression(y, yhat);
    cout << "b0: " << value(b0) << endl;
    cout << "b1: " << value(b1) << endl;
    cout << "f: " << value(f) << endl;
  });
  */
}
