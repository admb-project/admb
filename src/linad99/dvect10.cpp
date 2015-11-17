/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

#ifdef __ZTC__
  #include <iostream.hpp>
  #if (__ZTC__ < 0x310)
    #include <sstream.hpp>
  #else
    #include <strstream.h>
  #endif
#endif

#ifdef __SUN__
   #include <iostream.h>
  #include <strstream.h>
  #define __USE_IOSTREAM__
#endif

#ifdef __NDPX__
   #include <iostream.h>
   #include <sstream.h>
#endif

#include <string.h>
#include <ctype.h>

#include <sstream>
using std::istringstream;

#include <cassert>

const int MAX_FIELD_LENGTH = 500;

/**
Fill vectors from values in string s.

\param s should be in {v1, ..., vn} format.
*/
void dvector::fill(const char* s)
{
  int lbraces = 0;
  int rbraces = 0;
  int commas  = 0;

  const size_t n = strlen(s);
  char* t = new char[n + 1];
  assert(t);
  t[n] = '\0';

  for (size_t k = 0; k < n; k++)
  {
    if (s[k] == '{')
    {
      lbraces++;
      t[k] = ' ';
    }
    else if (s[k] == '}')
    {
      rbraces++;
      t[k] = ' ';
    }
    else if (s[k] == ',')
    {
      commas++;
      t[k] = ' ';
    }
    else
    {
      t[k] = s[k];
    }
  }

  if (lbraces == 1 && rbraces == 1)
  {
    int nch = commas + 1;

    if (nch != size())
    {
      if (nch < size())
      {
        cerr << "Not enough elements to fill vector in "
        "dvector::fill(const char * s)\n";
        cerr << s << "\n";
        ad_exit(1);
      }
      else
      {
        cerr << "Too many elements for size of vector in "
        "dvector::fill(const char * s)\n";
        cerr << s << "\n";
        ad_exit(1);
      }
    }
    istringstream ss(t);

//   char * field = (char *) new[size_t(MAX_FIELD_LENGTH+1)];
   char* field = new char[size_t(MAX_FIELD_LENGTH+1)];
   char* err_ptr = NULL;

   for (int i=indexmin();i<=indexmax();i++)
   {
     ss >> field;
     elem(i)=strtod(field,&err_ptr); // increment column counter

     if (isalpha((unsigned char)err_ptr[0]))
     {
       cerr << "Error decoding field "
         << " in dvector::dvector(char * filename) " << "\n";
       cerr << "Error occurred at element " << i << "\n";
       cerr << "Offending characters start with "
           << field << endl;
       ad_exit(1);
     }

     if (elem(i)== HUGE_VAL ||elem(i)== -HUGE_VAL)
     {
       cerr << "Overflow Error decoding field "
           " in dvector::dvector(char * ) " << "\n";
       cerr << "Error occurred at element " << i << "\n";
       cerr << "Offending characters start with "
           << field << endl;
       ad_exit(1);
     }
   }
   delete[] field;
   field = 0;
  }
  else
  {
    delete[] t;
    t = 0;

    if (lbraces != rbraces)
    {
      cerr << "Unbalanced braces in dvector::fill(const char * s)\n";
      cerr << s << "\n";
      ad_exit(1);
    }
    if (lbraces > 1)
    {
      cerr << "Only one level of braces allowed in dvector::fill(const char* s)"
           << '\n' << s << '\n';
      ad_exit(1);
    }
    if (lbraces == 0)
    {
      cerr << "Missing braces { ... } in dvector::fill(const char * s)\n";
      cerr << s << "\n";
      ad_exit(1);
    }
  }
  delete[] t;
  t = 0;
}
