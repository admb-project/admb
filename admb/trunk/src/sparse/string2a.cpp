
#include <fvar.hpp>
#include <string.h>
#include <stdlib.h>
#include <safe_mem.h>

  line_adstring& line_adstring::operator = (_CONST adstring& s)
  {
   this->adstring::operator =(s);
   return *this;
  }

  line_adstring& line_adstring::operator = (_CONST char * s)
  {
    this->adstring::operator =(s);
    return *this;
  }
