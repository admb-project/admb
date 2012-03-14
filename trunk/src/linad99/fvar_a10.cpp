/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
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

#if defined(__TURBOC__) && !defined(__linux__)
   #include <iostream.h>
   #include <strstrea.h>
#endif

#ifdef __SUN__
   #include <iostream.h>
#if !defined(__MSVC32__)
  #include <strstream.h>
#else
  #include <strstrea.h>
#endif
  #define __USE_IOSTREAM__
#endif

#ifdef __NDPX__
   #include <iostream.h>
   #include <sstream.h>
#endif

#include <string.h>
#include <ctype.h>
const unsigned int MAX_LINE_LENGTH = 10000;
const int MAX_FIELD_LENGTH = 500;
const int MAX_NUMBER_COLUMNS = 6550;
const int MAX_NUMBER_ROWS = 6550;
#if !defined(HUGE) 
#define HUGE 1.e+100
#endif

/**
 * Description not yet available.
 * \param
 */
void dvar_vector::fill(const char * s)
{
  int n = strlen(s);
  int lbraces = 0;
  int rbraces = 0;
  int commas  = 0;

  char *t = new char[n];

  int k;
  for (k = 0; k < n; k++)
  {
    if (s[k] == '{')
    {
      lbraces ++;
      t[k] = ' ';
    }
    else if (s[k] == '}')
    {
      rbraces ++;
      t[k] = ' ';
    }
    else if (s[k] == ',')
    {
      commas ++;
      t[k] = ' ';
    }
    else
    {
      t[k] = s[k];
    }
  }

  if (lbraces != rbraces)
  {
    cerr << "Unbalanced braces in dvar_vector::fill(const char * s)\n";
    cerr << s << "\n";
    ad_exit(1);
  }

  if (lbraces > 1)
  {
    cerr << "Only one level of braces allowed in dvar_vector::fill(const char * s)\n";
    cerr << s << "\n";
    ad_exit(1);
  }

  if (lbraces ==0)
  {
    cerr << "Missing braces { ... } in dvar_vector::fill(const char * s)\n";
    cerr << s << "\n";
    ad_exit(1);
  }

  if (lbraces == 1)
  {
    int nch = commas + 1;

    if (nch != size())
    {
      if (nch < size())
      {
        cerr << "Not enough elements to fill vector in dvar_vector::fill(const char * s)\n";
        cerr << s << "\n";
        ad_exit(1);
      }
      else
      {
        cerr << "Too many elements for size of vector in dvar_vector::fill(const char * s)\n";
        cerr << s << "\n";
        ad_exit(1);
      }
    }
    istrstream ss(t);

//   char * field = (char *) new[size_t(MAX_FIELD_LENGTH+1)];
   char * field = new char[size_t(MAX_FIELD_LENGTH+1)];
   char * err_ptr;

   for (int i=indexmin();i<=indexmax();i++)
   {
     ss >> field;
     elem(i)=strtod(field,&err_ptr); // increment column counter

     if (isalpha(err_ptr[0]))
     {
       cerr << "Error decoding field "
         << " in dmatrix::dmatrix(char * filename) " << "\n";
       cerr << "Error occurred at element " << i << "\n";
       cerr << "Offending characters start with "
           << err_ptr[0]
           << err_ptr[1]
           << err_ptr[2]
           << err_ptr[3] << "\n";
       ad_exit(1);
     }
#if defined( __SUN__) && !defined(__GNUDOS__)
  dvariable  cmp = elem(i);
     if (cmp == HUGE_VAL || cmp== -HUGE_VAL)
#elif defined( __GNU__) || defined( __GNUDOS__)
     if (elem(i)== HUGE ||elem(i)== -HUGE)
#else
     if (elem(i)== HUGE_VAL ||elem(i)== -HUGE_VAL)
#endif
     {
       cerr << "Overflow Error decoding field "
           " in dmatrix::dmatrix(char * ) " << "\n";
       cerr << "Error occurred at element " << i << "\n";
       ad_exit(1);
     }
   }
   delete field;

   delete t;
  }
}
