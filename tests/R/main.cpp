#include "example.h"

int main(int argc, char** argv)
{
  example();

  int n = 100;
  double x[n] {0.0};
  double output = 0.0;
  simple(&n, &x[0], &output, argv);

  return 0;
}
