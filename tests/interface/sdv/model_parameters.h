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

class model_parameters : public ad_comm,
  public function_minimizer
{
public:
  friend class df1b2_pre_parameters;
  friend class df1b2_parameters;
  static model_parameters * model_parameters_ptr;
  static model_parameters * get_model_parameters_ptr(void)
  {
    return model_parameters_ptr;
  }
  ~model_parameters() {}
  void preliminary_calculations(void);
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
  ivector integer_control_flags;
  void begin_df1b2_funnel(void);
  void end_df1b2_funnel(void);
  dvector double_control_flags;
public:
  virtual void userfunction(void) {}
  virtual void report(const dvector& gradients);
  virtual void final_calcs(void) {}
  model_parameters(int sz,int argc, char * argv[]);
  virtual void initializationfunction(void){}
  virtual void AD_uf_inner(void){pre_userfunction();}
  virtual void AD_uf_outer(void){pre_userfunction();}
  virtual void user_function(void){;}
  virtual void allocate(void){;}
};

