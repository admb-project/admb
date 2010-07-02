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
  enum exit_code
  {
    error_array_bounds_error = 42
  };

public:
  static 
  adstring error_array_bounds(const adstring& function_name,
                              const adstring& error_message,
                              const int lower_bounds, 
                              const int upper_bounds,
                              const int index,
                              const int error_code)
  {
    adstring m = "Error: Array bound error in " 
                 + function_name +  " "
                 + error_message
                 + adstring(" valid range is ")
                 + str(lower_bounds)
                 + " to "
                 + str(upper_bounds)
                 + "; you had "
                 + str(index);
    if (error_code != 0)
    {
    }

    return m;
  }
};
}
#endif
