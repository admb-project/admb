#include <iostream>

extern "C" {

#ifdef _WIN32
void __stdcall __declspec(dllexport) example()
#else
void example()
#endif
{
  std::cout << __func__ << ':' << __LINE__ << std::endl;
}

};
