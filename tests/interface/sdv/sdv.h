#include "model_parameters.h"

class sdv: public model_parameters
{
public:
  data_int n;
  data_vector y;
  param_init_bounded_number b;
  param_init_bounded_number log_sigma;
  param_init_bounded_number mu;
  param_init_bounded_number mu_x;
  random_effects_vector x;
  param_number prior_function_value;
  param_number likelihood_function_value;
  objective_function_value  g;

  sdv(int sz,int argc,char * argv[]);

  void userfunction(void);

  void sf1(const dvariable& ls,const dvariable& bb,const dvariable& x_1);
  void sf2(const dvariable& ls,const dvariable& bb,const dvariable& x_i,const dvariable& x_i1);
  void sf3(const dvariable& x_i ,const dvariable& mu ,const dvariable& mu_x ,int i);
};
  
class df1b2_parameters : public sdv
{ 
public: 
  df1b2_init_bounded_number b;
  df1b2_init_bounded_number log_sigma;
  df1b2_init_bounded_number mu;
  df1b2_init_bounded_number mu_x;
  df1b2_init_vector x;
  df1b2variable prior_function_value;
  df1b2variable likelihood_function_value;
  re_objective_function_value  g;

  df1b2_parameters(int sz,int argc, char * argv[]) : 
    sdv(sz,argc,argv)
  { 
  }
  virtual void allocate(void); 
  void deallocate(); 

  virtual void user_function(void); 

  void sf1(const funnel_init_df1b2variable& ls,const funnel_init_df1b2variable& bb,const funnel_init_df1b2variable& x_1);
  void sf2(const funnel_init_df1b2variable& ls,const funnel_init_df1b2variable& bb,const funnel_init_df1b2variable& x_i,const funnel_init_df1b2variable& x_i1);
  void sf3(const funnel_init_df1b2variable& x_i ,const funnel_init_df1b2variable& mu ,const funnel_init_df1b2variable& mu_x ,int i);
};
