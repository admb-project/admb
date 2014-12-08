#include <iostream>      // standard input/output 
#include <vector>        // standard vector
#include <cppad/cppad.hpp> // the CppAD package http://www.coin-or.org/CppAD/

namespace { 
      // define y(x) = Poly(a, x) in the empty namespace
      template <class Type>
      Type Poly(const std::vector<double> &a, const Type &x)
      {     size_t k  = a.size();
            Type y   = 0.;  // initialize summation
            Type x_i = 1.;  // initialize x^i
            size_t i;
            for(i = 0; i < k; i++)
            {     y   += a[i] * x_i;  // y   = y + a_i * x^i
                  x_i *= x;           // x_i = x_i * x
            }
            return y;
      }
}
// main program
using CppAD::AD;           // use AD as abbreviation for CppAD::AD
using std::vector;         // use vector as abbreviation for std::vector

class dvar_vector
{
  //using CppAD::AD;
  int mmin;
  int mmax;
public:
  vector < AD<double> > * true_v; // vector of domain space variables
  AD<double> * v; // vector of domain space variables
  dvar_vector(int lb,int ub)
  {
    mmin=lb;
    mmax=ub;
    true_v= new vector < AD<double> > (ub-lb+1); 
    v=&((*true_v)[0]);
    v-=mmin;
  }
  ~dvar_vector()
  {
    delete true_v;
    true_v=0;
    v=0;
  }
  AD<double> & operator [] (int i) 
  {
    if (i<mmin || i> mmax)
    {
      std::cerr << "bounds error in operator []" << std::endl;
      exit(1);
    }
    return v[i];
  }
};

void Independent(const dvar_vector & X)
{
  CppAD::Independent( *(X.true_v));
}

CppAD::ADFun<double> ADFun(const dvar_vector& X,const dvar_vector& Y)
{
  CppAD::ADFun<double> f( *(X.true_v), *(Y.true_v) );
  return f;
}

int main(void)
{     using CppAD::AD;           // use AD as abbreviation for CppAD::AD
      using std::vector;         // use vector as abbreviation for std::vector
      size_t i;                  // a temporary index

      // vector of polynomial coefficients
      size_t k = 5;              // number of polynomial coefficients
      vector<double> a(k);       // vector of polynomial coefficients
      for(i = 0; i < k; i++)
            a[i] = 1.;           // value of polynomial coefficients

      // domain space vector
      size_t n = 1;              // number of domain space variables
      dvar_vector X(0,0);
      X[0] = 3.;                 // value corresponding to operation sequence

      // declare independent variables and start recording operation sequence
      Independent(X);

      // range space vector
      size_t m = 1;              // number of ranges space variables
      //vector< AD<double> > Y(m); // vector of ranges space variables
      dvar_vector Y(0,m-1);
      Y[0] = Poly(a, X[0]);      // value during recording of operations

      // store operation sequence in f: X -> Y and stop recording
      CppAD::ADFun<double> f=ADFun(X,Y);

      // compute derivative using operation sequence stored in f
      vector<double> jac(m * n); // Jacobian of f (m by n matrix)
      vector<double> x(n);       // domain space vector
      x[0] = 3.;                 // argument value for derivative
      jac  = f.Jacobian(x);      // Jacobian for operation sequence

      // print the results
      std::cout << "f'(3) computed by CppAD = " << jac[0] << std::endl;

      // check if the derivative is correct
      int error_code;
      if( jac[0] == 142. )
            error_code = 0;      // return code for correct case
      else  error_code = 1;      // return code for incorrect case

      return error_code;
}
