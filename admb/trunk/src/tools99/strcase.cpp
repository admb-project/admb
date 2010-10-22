/*
 * $Id$
 *
 * Author: John Sibert
 * Copyright (c) 2010 ADMB Foundation
 */
#include "fvar.hpp"
#include "adstring.hpp"

void adstring::to_lower(void)
{
  for (unsigned int i=1; i <= size(); i++)
    s[i] = tolower(s[i]);
}

void adstring::to_upper(void)
{
  for (unsigned int i=1; i <= size(); i++)
    s[i] = toupper(s[i]);
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
