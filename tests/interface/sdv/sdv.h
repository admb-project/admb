#include <fvar.hpp>
#include <admodel.h>
#include "model_interface.h"

class sdv: public model_interface
{
public:
  data_int n;
  data_vector y;
  param_init_bounded_number b;
  param_init_bounded_number log_sigma;
  param_init_bounded_number mu;
  param_init_bounded_number mu_x;
  random_effects_vector x;
  objective_function_value  g;

  sdv();

  void userfunction();

  void sf1(const dvariable& ls,const dvariable& bb,const dvariable& x_1);
  void sf2(const dvariable& ls,const dvariable& bb,const dvariable& x_i,const dvariable& x_i1);
  void sf3(const dvariable& x_i ,const dvariable& mu ,const dvariable& mu_x ,int i);
};

class df1b2_parameters : public model_interface
{
public:
  data_int n;
  data_vector y;

  df1b2_init_bounded_number b;
  df1b2_init_bounded_number log_sigma;
  df1b2_init_bounded_number mu;
  df1b2_init_bounded_number mu_x;
  df1b2_init_vector x;
  re_objective_function_value  g;

  df1b2_parameters() {}

  void allocate();
  void deallocate();

  void user_function();

  void sf1(const funnel_init_df1b2variable& ls,const funnel_init_df1b2variable& bb,const funnel_init_df1b2variable& x_1);
  void sf2(const funnel_init_df1b2variable& ls,const funnel_init_df1b2variable& bb,const funnel_init_df1b2variable& x_i,const funnel_init_df1b2variable& x_i1);
  void sf3(const funnel_init_df1b2variable& x_i ,const funnel_init_df1b2variable& mu ,const funnel_init_df1b2variable& mu_x ,int i);
};
