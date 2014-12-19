#include <iostream>

extern "C" {

void __stdcall __declspec(dllexport) example()
{
  std::cout << __func__ << ':' << __LINE__ << std::endl;
}

};
