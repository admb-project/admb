/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Input operators for adstring and line_adstring.
*/
#include <fvar.hpp>
#include <stdlib.h>

/**
Input string from stream c into adstring t.

/param c input stream
/param t output adstring
*/
istream& operator>>(istream& c, adstring& t)
{
  const unsigned int max_length = 1025;
  char tmp[max_length + 1];
  tmp[max_length] = '\0';
  c >> tmp;
  if (tmp[max_length] != '\0')
  {
    cerr << "Error -- Maximum adstring length exceeded in "
         << "istream& operator>>(istream&, adstring&)" << endl;
    ad_exit(1);
  }
  t = tmp;

  return c;
}
/**
Input string from stream c into line_adstring t.

/param c input stream
/param t output line_adstring
*/
istream& operator>>(istream& c, line_adstring& t)
{
  const unsigned int max_length = 1025;
  char tmp[max_length + 1];

  // throw away the newline at the end of the last line if necessary
  //if (ch == '\r') ch = (char)c.get();

  unsigned int ii = 0;
  while (ii <= max_length)
  {
    char ch = (char)c.get();
    if (ch == '\r')
    {
      char p = (char)c.peek();
      if (p == '\n')
      {
        ch = (char)c.get();
      }
      break;
    }
    else if (ch == '\n')
    {
      break;
    }
    else if (ch == EOF)
    {
      break;
    }
    else
    {
      tmp[ii++] = ch;
    }
  }
  if (ii > max_length)
  {
    cerr << "Error -- Maximum line_adstring length exceeded in "
         << "istream& operator>>(istream&, line_adstring&)" << endl;
    ad_exit(1);
  }
  tmp[ii] = '\0';
  t = tmp;

  return c;
}
