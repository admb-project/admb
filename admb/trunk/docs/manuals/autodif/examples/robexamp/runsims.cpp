#include <stdlib.h>
// Increases the seed for the random number generators in robsim
main()
{
  for (int i=1;i<=490;i++)
  {
    system("robsims > robust.dat");

    system("ch_rob");

    system("update");
  }
  exit(0);
}
