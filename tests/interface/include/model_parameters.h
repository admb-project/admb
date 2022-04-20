#include <fvar.hpp>
#include <admodel.h>

extern "C"  {
  void ad_boundf(int i);
}

class model_parameters : public ad_comm,
  public function_minimizer
{
public:
  ~model_parameters();
  void preliminary_calculations(void) {}
  void set_runtime(void) {}

  static int mc_phase(void)
  {
    return initial_params::mc_phase;
  }
  static int mceval_phase(void)
  {
    return initial_params::mceval_phase;
  }
  static int hessian_phase(void)
  {
    return initial_params::in_hessian_phase;
  }
  static int sd_phase(void)
  {
    return initial_params::sd_phase;
  }
  static int current_phase(void)
  {
    return initial_params::current_phase;
  }
  static int last_phase(void)
  {
    return (initial_params::current_phase
      >=initial_params::max_number_phases);
  }
  static prevariable current_feval(void)
  {
    return *objective_function_value::pobjfun;
  }
  /*
  dvariable adromb(dvariable(*f)(const dvariable&), double a, double b, int ns)
  {
    using namespace std::placeholders;
    auto func = std::bind(f, this, _1);
    return function_minimizer::adromb(func, a, b, ns);
  }
  */
  ivector integer_control_flags;
  dvector double_control_flags;
public:
  virtual void userfunction(void) {}
  virtual void report(const dvector& gradients) {}
  virtual void final_calcs(void) {}
  model_parameters(int sz,int argc, char * argv[]);
  model_parameters(int argc, char * argv[]): model_parameters(150000, argc, argv) {} 
  virtual void initializationfunction(void) {}
  void minimize(int argc,char * argv[])
  {
    iprint = 10;
    preliminary_calculations();
    computations(argc, argv);
  }
};
