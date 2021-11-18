#include <fvar.hpp>
#include <admodel.h>
#include "model_interface.h"

template <typename T, typename U, typename V, typename W, typename X>
class sdv: public model_interface
{
public:
  data_int n;
  data_vector y;
  U b;
  U log_sigma;
  U mu;
  U mu_x;
  V x;
  W g;

  sdv() {}

  void allocate();
  void deallocate();

  void userfunction();

  void sf1(const T& ls, const T& bb, const T& x_1);
  void sf2(const T& ls, const T& bb, const T& x_i,const T& x_i1);
  void sf3(const T& x_i, const T& mu, const T& mu_x, int i);
};

template <typename T, typename U, typename V, typename W, typename X>
class df1b2_parameters : public model_interface
{
public:
  data_int n;
  data_vector y;

  U b;
  U log_sigma;
  U mu;
  U mu_x;
  V x;
  W g;

  df1b2_parameters() {}

  void allocate();
  void deallocate();

  void user_function();
  void userfunction();

  void sf1(const T& ls, const T& bb, const T& x_1);
  void sf2(const T& ls, const T& bb, const T& x_i, const T& x_i1);
  void sf3(const T& x_i , const T& mu, const T& mu_x, int i);
};
