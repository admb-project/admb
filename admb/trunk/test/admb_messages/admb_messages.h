#ifndef __ADMB_MESSAGES_H__
#define __ADMB_MESSAGES_H__
#include <iostream>
#include <fvar.hpp>

namespace admb
{
class messages
{
public:
  messages() {;}
  messages(const messages&) {;}
  virtual ~messages() {;}
public:

/*
  static 
  adstring array_bounds_error(const adstring& operator_name,
                              const adstring& error_message,
                              const int lb, 
                              const int ub,
                              const int k,
                              int exitcode)
  {
    adstring m = "Error: Array bound error in " 
                 + operator_name + << " "
                 + error_message
                 + " valid range is " 
                 + lb 
                 + " to " 
                 + ub 
                 + "; you had "
                 + k;
      //ad_exit(42);
    return m;
  }

  static 
  void outofbounds()
  {
    std::cout << array_bounds_error("kdjfkd", "kdjkj", 2, 3, 5, 6) << std::endl;
  }
*/
};
}
#endif
