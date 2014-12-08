/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <fvar.hpp>
#include <stdlib.h>

istream & operator >> (istream & c, adstring & t)
{
  const unsigned int max_length=1025;
  char * tmp= new char[max_length+1];
  c >> tmp;
  if (strlen(tmp)>max_length)
  {
    cerr << "Error -- Maximum adstring length exceeded in"
      " istream & operator >> (istream & c, adstring & t)"<<endl;
    exit(1);
  }
  t=tmp;
  delete [] tmp;
  tmp = 0;

  return (c);
}

/**
Input string from stream c into line_adstring t.

/param c input stream
/param t ouput line_adstring
*/
istream& operator>>(istream& c, line_adstring& t)
{
  const unsigned int max_length=1025;
  char* tmp = new char[max_length+1];
  char ch = (char)c.get();
  // throw away the newline at the end of the last line if necessary
  if (ch == '\n') ch = (char)c.get();
  unsigned int ii=0;
  while (ch != '\n' && ch != EOF)
  {
    if (ii==max_length)
    {
      cerr << "Error -- Maximum adstring length exceeded in"
        " istream& operator>>(istream& c, line_adstring& t)" <<endl;
      exit(1);
    }
    tmp[ii++] = ch;
    ch = (char)c.get();
  }
  tmp[ii]='\0';
  t=tmp;
  delete [] tmp;
  tmp = 0;

  return c;
}
