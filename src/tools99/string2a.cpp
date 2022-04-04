/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Member functions for class line_adstring.
*/
#include <adstring.hpp>

line_adstring& line_adstring::operator=(const adstring& _s)
{
  this->adstring::operator=(_s);
  return *this;
}

line_adstring& line_adstring::operator=(const char* _s)
{
  this->adstring::operator=(_s);
  return *this;
}
