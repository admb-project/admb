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

#ifdef DEBUG
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
   char* field = new char[size_t(MAX_FIELD_LENGTH+1)];
   infile.width(size_t(MAX_FIELD_LENGTH+1));
   int count=0;
   char c;
   infile.get(c);
   while (!infile.eof())
   {
     if (isspace(c))
     {
       infile.get(c);
     }
     else if (c == ',')
     {
       infile.get(c);
     }
     else
     {
       ++count;
       do
       {
         infile.get(c);
       } while (!isspace(c) && c != ',');
     }
   }

   infile.clear();
   infile.seekg(0,ios::beg);

   allocate(1,count);

   #ifdef DIAG
     cout << "Created a ncopies with address " << _farptr_tolong(&(shape->ncopies))<<"\n";
     cout << "Created a dvector with address " << _farptr_tolong(va) <<"\n";
   #endif
#ifdef DEBUG
  assert(size() > 0);
#endif
   gradient_structure* gs = gradient_structure::_instance;
   if (!gs)
   {
     cerr << "Error: instance of gradient_structure is a nullptr.\n";
     ad_exit(1);
   }
   if ((va = gs->ARR_LIST1->arr_new((unsigned int)size()))==0 )
   {
     cerr << " Error trying to allocate memory for dvector\n";
     ad_exit(21);
   }
   char* err_ptr;
   infile.width(size_t(MAX_FIELD_LENGTH+1));
   for (i=1;i<=count;i++)
   {
     int index = 0;
     infile.get(c);
     while (!infile.eof())
     {
       if (isspace(c))
       {
         infile.get(c);
       }
       else if (c == ',')
       {
         infile.get(c);
       }
       else
       {
         do
         {
           field[index] = c;

           infile.get(c);
           ++index;
         } while (!isspace(c) && c != ',');
         field[index] = '\0';
         break;
       }
     }
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

   infile.close();
 }
 delete [] t;
 t = 0;
}
