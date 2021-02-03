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

#if defined(__TURBOC__)
  #pragma hdrstop
  #include <iostream.h>
  #include <strstrea.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
  #if (__ZTC__ < 0x310)
    #include <sstream.hpp>
  #else
    #include <strstream.h>
  #endif
#endif

#ifdef __NDPX__
  #include <iostream.h>
  #include <sstream.h>
#endif

#ifdef __SUN__
  #include <iostream.h>
  #include <strstream.h>
  #define __USE_IOSTREAM__
#endif

#include <string.h>
#include <ctype.h>

#include <sstream>
using std::istringstream;

#ifndef OPT_LIB
  #include <cassert>
#endif

const int MAX_FIELD_LENGTH = 500;

/**
\todo Need Test case
*/
dvar_vector::dvar_vector(const char * s)
{
  size_t n = strlen(s);
  int lbraces = 0;
  int rbraces = 0;
  int commas  = 0;

  char* t = new char[n];

  for (size_t k = 0; k < n; k++)
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
    cerr << "Unbalanced braces in dvector::dvector(const char * s)\n";
    cerr << s << "\n";
    ad_exit(1);
  }

  if (lbraces > 1)
  {
    cerr << "Only one level of braces allowed in "
    "dvector::dvector(const char * s)\n";
    cerr << s << "\n";
    ad_exit(1);
  }

  if (lbraces == 1)
  {
    int ncl = 1;
    int nch = commas + 1;

    allocate(ncl,nch);
    istringstream ss(t);

    for (int k = ncl; k <= nch; k++)
    {
      ss >> this->elem(k);
      //va[k].nc=0.;
    }
  }
  else
  {
    const char* filename = s;
    ifstream infile(filename);
    if (!infile)
    {
     cerr << "Error opening file " << filename << " in dvector constructor "
      << "dvector::dvector(char * filename)\n";
      ad_exit(1);
   }

   int i=0;

//   char * field = (char *) new[size_t(MAX_FIELD_LENGTH+1)];
   char * field = new char[size_t(MAX_FIELD_LENGTH+1)];
   int count=0;
   do
   {
     infile >> field;
     if (infile.good())
     {
       count++;
     }
     else
     {
       if (!infile.eof())
       {
         cerr << "Error reading file " << filename << " in dvector constructor "
           << "dvector::dvector(char * filename)\n";
         cerr << "Error appears to have occurred at element"
          << count+1 << endl;
         cerr << "Stream state is " << infile.rdstate() << endl;
         ad_exit(1);
       }
     }
   }
   while (!infile.eof());

   infile.clear();
   infile.seekg(0,ios::beg);

   allocate(1,count);

   #ifdef DIAG
     cout << "Created a ncopies with address " << _farptr_tolong(ncopies)<<"\n";
     cout << "Created a dvector with address " << _farptr_tolong(v) <<"\n";
   #endif
#ifndef OPT_LIB
  assert(size() > 0);
#endif
   if ((va = arr_new((unsigned int)size()))==0 )
   {
     cerr << " Error trying to allocate memory for dvector\n";
     ad_exit(21);
   }
   char* err_ptr;
   for (i=1;i<=count;i++)
   {
     infile >> field;
     elem(i)=strtod(field,&err_ptr); // increment column counter

     if (isalpha((unsigned char)err_ptr[0]))
     {
       cerr << "Error decoding field " << filename
         << " in dmatrix::dmatrix(char * filename) " << "\n";
       cerr << "Error occurred at element " << count << "\n";
       cerr << "Offending characters start with "
           << err_ptr[0]
           << err_ptr[1]
           << err_ptr[2]
           << err_ptr[3] << "\n";
       ad_exit(1);
     }
     if (value(elem(i))== HUGE_VAL ||value(elem(i))== -HUGE_VAL)
     {
       cerr << "Overflow Error decoding field " << filename
           << " in dmatrix::dmatrix(char * filename) " << "\n";
       cerr << "Error occurred at element " << count << "\n";
       ad_exit(1);
     }
   }
   delete[] field;
   field = 0;
 }
 delete [] t;
 t = 0;
}
