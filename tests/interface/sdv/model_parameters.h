#ifdef DEBUG
  #ifndef __SUNPRO_C
    #include <cfenv>
    #include <cstdlib>
  #endif
#endif
  //#include <df1b2fun.h>
#ifdef DEBUG
  #include <chrono>
#endif
#include <admodel.h>
#ifdef USE_ADMB_CONTRIBS
#include <contrib.h>
#endif
#include <df1b2fun.h>
#include <adrndeff.h>
extern "C"  {
  void ad_boundf(int i);
}

class df1b2_parameters;

class model_parameters : public ad_comm,
  public function_minimizer
{
public:
/*
  static model_parameters* df1b2_parameters_ptr;
  static model_parameters* get_df1b2_parameters_ptr()
  {
    return df1b2_parameters_ptr;
  }

  static model_parameters* model_parameters_ptr;
  static model_parameters* get_model_parameters_ptr()
  {
    return model_parameters_ptr;
  }
*/

  df1b2_parameters* model = nullptr;

  ~model_parameters() {}
  void preliminary_calculations();
  void set_runtime() {}
  static int mc_phase()
  {
    return initial_params::mc_phase;
  }
  static int mceval_phase()
  {
    return initial_params::mceval_phase;
  }
  static int hessian_phase()
  {
    return initial_params::in_hessian_phase;
  }
  static int sd_phase()
  {
    return initial_params::sd_phase;
  }
  static int current_phase()
  {
    return initial_params::current_phase;
  }
  static int last_phase()
  {
    return (initial_params::current_phase
      >=initial_params::max_number_phases);
  }
  static prevariable current_feval()
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
  void begin_df1b2_funnel();
  void end_df1b2_funnel();
  dvector double_control_flags;
public:
  virtual void userfunction();
  virtual void report(const dvector& gradients);
  virtual void final_calcs() {}
  model_parameters(int sz,int argc, char * argv[]);
  model_parameters(int argc, char * argv[]): model_parameters(150000, argc, argv) {}
  virtual void initializationfunction(){}
  virtual void AD_uf_inner(){pre_userfunction();}
  virtual void AD_uf_outer(){pre_userfunction();}
  virtual void user_function();
  virtual void allocate();
  virtual void deallocate();

  void begin_df1b2_funnel2();
  void setup_quadprior_calcs();
  void end_df1b2_funnel2();
};
