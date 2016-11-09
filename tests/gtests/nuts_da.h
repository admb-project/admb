double urand();
double randn();
double exprnd(double p);
//[logpprime, gradprime] = f(thetaprime);
void f(const size_t D, const double* theta, double& logp, double* grad);
extern int _D;
//global nfevals;
extern int _nfevals;
extern double _rprime[2];
extern double _thetaprime[2];
extern double _gradprime[2];
extern double _logpprime;
void correlated_normal(double* theta);
void f(double* theta);
void leapfrog
(
  double* theta,
  double* r,
  double* grad,
  double epsilon
);
double find_reasonable_epsilon
(
  double* theta0,
  double* grad0,
  double logp0,
  double* r0
);
bool stop_criterion
(
  double* thetaminus,
  double* thetaplus,
  double* rminus,
  double* rplus
);
extern double _thetaminus[2];
extern double _rminus[2];
extern double _gradminus[2];
extern double _thetaplus[2];
extern double _rplus[2];
extern double _gradplus[2];
extern int _nprime;
extern int _sprime;
extern double _alphaprime;
extern int _nalphaprime;
double exprnd(const int m);
void build_tree(
  double* theta,
  double* r,
  double* grad,
  double logu,
  int v,
  int j,
  double epsilon,
  double joint0
);
//function [samples, epsilon] = nuts_da(f, M, Madapt, theta0, delta)
extern double _samples[1000][2];
extern double _epsilon;
void nuts_da(const int M, const int Madapt, double* theta0, const double delta);
