#include <fvar.hpp>
int just_to_link_gdb1=0;

void dp(const ivector& x)
{
  cout << x << endl;
}

void dp(const dvar_vector& x)
{
  cout << x << endl;
}

void dp(const dvector& x)
{
  cout << x << endl;
}

void dp(int x)
{
  cout << x << endl;
}

void dp(const prevariable& x)
{
  cout << x << endl;
}

void dp(double x)
{
  cout << x << endl;
}

void dp(const imatrix& x)
{
  cout << x << endl;
}

void dp(const dvar_matrix& x)
{
  cout << x << endl;
}

void dp(const dmatrix& x)
{
  cout << x << endl;
}

void dp(const banded_symmetric_dmatrix& x)
{
  cout << x << endl;
}
