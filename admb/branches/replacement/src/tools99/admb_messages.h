#ifndef __ADMB_MESSAGES_H__
#define __ADMB_MESSAGES_H__
#include <iostream>
#include <fvar.hpp>

#define ADMB_ERROR(x) admb::messages::error(x);
#define ADMB_ARRAY_BOUNDS_ERROR(message,function,lower_bounds,upper_bounds,index) admb::messages::array_bounds_error(message,function,lower_bounds,upper_bounds,index);

namespace admb
{
const int ARRAY_BOUNDS_ERROR = 42;

/**
 *
 */
class messages
{
public:
  /**
   *
   */
  messages() {;}
  /**
   *
   */
  messages(const messages&);
  /**
   *
   */
  virtual ~messages() {;}

public:
  /**
   *
   */
  static 
  void error(const adstring& message)
  {
    error(message, 1);
  }
  /**
   *
   */
  static 
  void error(const int error_code)
  {
    adstring message  = "Error: ";
    switch (error_code)
    {
    case 1:
      message += "allocating memory in dmatrix contructor";
      break;
    case 2:
      message += "attempting to access non-allocated ivector in ivector::operator()";
      break;
    default:
      break;
    };
    error(message, error_code);
  }
  /**
   *
   */
  static 
  void error(const adstring& message, const adstring& function_name, const int error_code)
  {
    adstring m = message;
    if (function_name.size() > 0)
    {
      m += " in " + function_name;
    }
    error(m, error_code);
  }
  /**
   *
   */
  static 
  void array_bounds_error(const adstring& message,
                          const adstring& function,
                          const int lower_bounds, 
                          const int upper_bounds,
                          const int index)
  {
    //tools99/string1.cpp
    //cerr << "First index out of bounds in adstring::operator () (int,int)\n"
    //<< "Index value was " << i << " The size of this adstring is "
    //<< shape->size() << "\n";
    //cerr << "Index out of bounds in adstring::operator () (const int)\n"
    //<< "Index value was " << i << " The size of this adstring is "
    //<< shape->size() << "\n";
    //tools99/string5.cpp
    //cerr << "Error index too low in adstring& operator [] (int i)" << endl;
    //cerr << "value was " << i << " minimum valid index is "
    /*
    adstring m = message + " in \"" + function +  "\"\n"
                 + adstring("Index value was ")
                 + str(index)
                 + " The size of this adstring is "
                 + str(upper_bounds);
    */
    adstring m = adstring("Error: Invalid index ")
                 + str(index)
                 + " used for array range ["
                 + str(lower_bounds)
                 + ", "
                 + str(upper_bounds)
                 + "] in \"" + function +  "\".\n"
                 + message + "\n"; 
    error(m, ARRAY_BOUNDS_ERROR);
  }
  /**
   *
   */
  static 
  void error(const adstring& message, const int error_code)
  {
    cerr << message << '\n';
    ad_exit(error_code);
  }
};
}
#endif
