#include <stdlib.h>
// Increases the seed for the random number generators in robsim
int main()
{
  for (int i=1;i<=490;i++)
  {
    system("robsims > robust.dat");

    system("ch_rob");

    system("update");
  }
  return 0;
}
