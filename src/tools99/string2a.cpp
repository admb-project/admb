/**
/file
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
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
