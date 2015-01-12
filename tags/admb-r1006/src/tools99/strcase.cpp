/*
 * $Id$
 *
 * Author: John Sibert
 * Copyright (c) 2010-2011 ADMB Foundation
 */
#include "adstring.hpp"

void adstring::to_lower(void)
{
  for (unsigned int i=1; i <= size(); i++)
#ifdef _MSC_VER  
    s[i] = tolower(s[i]);
#else
    s[i] = std::tolower(s[i]);
#endif
}

void adstring::to_upper(void)
{
  for (unsigned int i=1; i <= size(); i++)
#ifdef _MSC_VER  
    s[i] = toupper(s[i]);
#else
    s[i] = std::toupper(s[i]);
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
