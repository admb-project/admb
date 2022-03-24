#include <iostream>
#include <cfenv>
#include <cstdlib>

using std::cerr;
using std::cout;
using std::endl;

void fpe_init()
{
  cout << "Clear FPE" << endl;
  std::feclearexcept(FE_ALL_EXCEPT);
}

void fpe_check()
{
  cout << "Detected FPE:" << endl;
  bool found = false;
  if (std::fetestexcept(FE_DIVBYZERO))
    { cerr << "\nDetected division by zero" << endl; found = true; }
  if (std::fetestexcept(FE_INVALID))
    { cerr << "\nDetected invalid argument" << endl; found = true; }
  if (std::fetestexcept(FE_OVERFLOW))
    { cerr << "\nDetected overflow" << endl; found = true; }
  if (std::fetestexcept(FE_UNDERFLOW))
    { cerr << "\nDetected underflow" << endl; found = true; }
  if (!found)
    { cerr << "None" << endl; }
}
