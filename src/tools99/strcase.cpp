/**
@file
@author John Sibert
@copyright Copyright (c) 2010-2020 ADMB Foundation

@brief Functions for adstring used to_lower and to_upper.
*/

#include "adstring.hpp"

void adstring::to_lower(void)
{
  for (unsigned int i=1; i <= size(); i++)
#ifdef _MSC_VER
    s[i] = (unsigned char)tolower(s[i]);
#else
    s[i] = (unsigned char)std::tolower(s[i]);
#endif
}

void adstring::to_upper(void)
{
  for (unsigned int i=1; i <= size(); i++)
#ifdef _MSC_VER
    s[i] = (unsigned char)toupper(s[i]);
#else
    s[i] = (unsigned char)std::toupper(s[i]);
#endif
}

adstring to_lower(adstring& s)
{
  adstring t = s;
  t.to_lower();
  return(t);
}

adstring to_upper(adstring& s)
{
  adstring t = s;
  t.to_upper();
  return(t);
}
