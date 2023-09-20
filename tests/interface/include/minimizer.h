#include "model_parameters.cpp"

class minimizer: public model_parameters
{
  std::function<void(void)> f;

public:
  minimizer() = delete;
  minimizer(const minimizer&) = delete;
  minimizer(const minimizer&&) = delete;

  minimizer(int argc, char * argv[]):
    model_parameters(argc, argv)
  {
  }
  void minimize(std::function<void(void)> user_function)
  {
    f = std::move(user_function);
    model_parameters::minimize(ad_comm::argc, ad_comm::argv);
  }
  void userfunction()
  {
    f();
  }
};
