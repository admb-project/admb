#include <iostream>
#include <fvar.hpp>

adstring_array a(1, 2);
i4_array i4a(1, 2, 1, 2, 1, 2, 1, 2);

int main(int argc, char** argv)
{
  std::cout << "Globals created with pools...OKAY." << std::endl;
  return 0; 
}
