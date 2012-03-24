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
#include <math.h>


#if defined(__TURBOC__) && !defined(__linux__)
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
  #define __USE_IOSTREAM__
#endif

#ifdef __NDPX__
  #include <iostream.h>
  #include <sstream.h>
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
dvector::dvector(const char * s)
{
  int n = strlen(s);
  int lbraces = 0;
  int rbraces = 0;
  int commas  = 0;

  char *t = new char[n+1];
  t[n]=0;

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
    cerr << "Unbalanced braces in dvector::dvector(const char * s)\n";
    cerr << s << "\n";
    ad_exit(1);
  }

  if (lbraces > 1)
  {
    cerr << "Only one level of braces allowed in dvector::dvector(const char * s)\n";
    cerr << s << "\n";
    ad_exit(1);
  }

  if (lbraces == 1)
  {
    int ncl = 1;
    int nch = commas + 1;

    allocate(ncl,nch);

    istrstream ss(t);

   char *field =  new char[size_t(MAX_FIELD_LENGTH+1)];
   char *err_ptr;

   for (int i=ncl;i<=nch;i++)
   {
     ss >> field;
     v[i]=strtod(field,&err_ptr); // increment column counter

     if (isalpha(err_ptr[0]))
     {
       cerr << "Error decoding field "
         << " in dvector::dvector(char * filename) " << "\n";
       cerr << "Error occurred at element " << i << "\n";
       cerr << "Offending characters start with "
           << field << endl;
       ad_exit(1);
     }

     #ifdef __GNU__
       if (elem(i)== HUGE ||elem(i)== -HUGE)
     #else
       if (elem(i)== HUGE_VAL ||elem(i)== -HUGE_VAL)
     #endif
     {
       cerr << "Overflow Error decoding field "
           " in dvector::dvector(char * ) " << "\n";
       cerr << "Error occurred at element " << i << "\n";
       cerr << "Offending characters start with "
           << field << endl;
       ad_exit(1);
     }
   }
   delete [] field;
   field=0;

    delete [] t;
    t=0;
  }
  else // if lbraces == 0
  {
   const char * filename=s;
   ifstream infile(filename);
   if (!infile)
   {
     cerr << "Error opening file " << filename << " in dvector constructor "
      << "dvector::dvector(char * filename)\n";
      ad_exit(1);
   }

   int i=0;

//   char * field = (char*) new[size_t(MAX_FIELD_LENGTH+1)];
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

    if ( (v = new double [count+2]) ==0)
    {
      cerr << " Error trying to allocate memory for dvector\n";
      ad_exit(21);
    }
 #if defined(THREAD_SAFE)
  if ( (shape=new ts_vector_shapex(1,count,v)) == NULL)
 #else
  if ( (shape=new vector_shapex(1,count,v)) == NULL)
 #endif
    {
      cerr << "Error trying to allocate memory for dvector\n";
      ad_exit(1);
    }


    index_min=1;
    index_max=count;
    v -= indexmin();

   #ifdef DIAG
     cout << "Created a ncopies with address " << _farptr_tolong(ncopies) <<"\n";
     cout << "Created a dvector with address " << _farptr_tolong(v) <<"\n";
   #endif
   char * err_ptr;
   for (i=1;i<=count;i++)
   {
     infile >> field;
     elem(i)=strtod(field,&err_ptr); // increment column counter

     if (isalpha(err_ptr[0]))
     {
       cerr << "Error decoding field " << filename
         << " in dvector::dvector(char * filename) " << "\n";
       cerr << "Error occurred at element " << count << "\n";
       cerr << "Offending characters start with "
           << err_ptr[0]
           << err_ptr[1]
           << err_ptr[2]
           << err_ptr[3] << "\n";
       ad_exit(1);
     }

     #ifdef __GNU__
       if (elem(i)== HUGE ||elem(i)== -HUGE)
     #else
       if (elem(i)== HUGE_VAL ||elem(i)== -HUGE_VAL)
     #endif
     {
       cerr << "Overflow Error decoding field " << filename
           << " in dvector::dvector(char * filename) " << "\n";
       cerr << "Error occurred at element " << count << "\n";
       cerr << "Offending characters start with "
           << err_ptr[0]
           << err_ptr[1]
           << err_ptr[2]
           << err_ptr[3] << "\n";
       ad_exit(1);
     }
   }
   delete[] field;
   field = 0;
 }
}

/**
 * Description not yet available.
 * \param
 */
void dvector::allocate(const char * s)
{
  int n = strlen(s);
  int lbraces = 0;
  int rbraces = 0;
  int commas  = 0;

  char *t = new char[n+1];
  t[n+1]=0;

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
    cerr << "Unbalanced braces in dvector::dvector(const char * s)\n";
    cerr << s << "\n";
    ad_exit(1);
  }

  if (lbraces > 1)
  {
    cerr << "Only one level of braces allowed in dvector::dvector(const char * s)\n";
    cerr << s << "\n";
    ad_exit(1);
  }

  if (lbraces == 1)
  {
    int ncl = 1;
    int nch = commas + 1;

    allocate(ncl,nch);

    istrstream ss(t);

   char * field =  new char[size_t(MAX_FIELD_LENGTH+1)];
   char * err_ptr;

   for (int i=ncl;i<=nch;i++)
   {
     ss >> field;
     v[i]=strtod(field,&err_ptr); // increment column counter

     if (isalpha(err_ptr[0]))
     {
       cerr << "Error decoding field "
         << " in dvector::dvector(char * filename) " << "\n";
       cerr << "Error occurred at element " << i << "\n";
       cerr << "Offending characters start with "
           << err_ptr[0]
           << err_ptr[1]
           << err_ptr[2]
           << err_ptr[3] << "\n";
       ad_exit(1);
     }

     #ifdef __GNU__
       if (elem(i)== HUGE ||elem(i)== -HUGE)
     #else
       if (elem(i)== HUGE_VAL ||elem(i)== -HUGE_VAL)
     #endif
     {
       cerr << "Overflow Error decoding field "
           " in dvector::dvector(char * ) " << "\n";
       cerr << "Error occurred at element " << i << "\n";
       ad_exit(1);
     }
   }
   delete [] field;
   field=0;

    delete [] t;
    t=0;
  }
  else // if lbraces == 0
  {
   const char * filename=s;
   ifstream infile(filename);
   if (!infile)
   {
     cerr << "Error opening file " << filename << " in dvector constructor "
      << "dvector::dvector(char * filename)\n";
      ad_exit(1);
   }

   int i=0;

//   char * field = (char*) new[size_t(MAX_FIELD_LENGTH+1)];
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

   if ( (v = new double [(size_t) size()]) ==0)
   {
     cerr << " Error trying to allocate memory for dvector\n";
     ad_exit(21);
   }
#if defined(THREAD_SAFE)
   if ( (shape=new ts_vector_shapex(1,count,v)) == NULL)
#else
   if ( (shape=new vector_shapex(1,count,v)) == NULL)
#endif
   {
     cerr << "Error trying to allocate memory for dvector\n";
     ad_exit(21);
   }

   #ifdef DIAG
     cout << "Created a ncopies with address " << _farptr_tolong(ncopies) <<"\n";
     cout << "Created a dvector with address " << _farptr_tolong(v) <<"\n";
   #endif
   v -= indexmin();
   char * err_ptr;
   for (i=1;i<=count;i++)
   {
     infile >> field;
     elem(i)=strtod(field,&err_ptr); // increment column counter

     if (isalpha(err_ptr[0]))
     {
       cerr << "Error decoding field " << filename
         << " in dvector::dvector(char * filename) " << "\n";
       cerr << "Error occurred at element " << count << "\n";
       cerr << "Offending characters start with "
           << err_ptr[0]
           << err_ptr[1]
           << err_ptr[2]
           << err_ptr[3] << "\n";
       ad_exit(1);
     }

     #ifdef __GNU__
       if (elem(i)== HUGE ||elem(i)== -HUGE)
     #else
       if (elem(i)== HUGE_VAL ||elem(i)== -HUGE_VAL)
     #endif
     {
       cerr << "Overflow Error decoding field " << filename
           << " in dvector::dvector(char * filename) " << "\n";
       cerr << "Error occurred at element " << count << "\n";
       cerr << "Offending characters start with "
           << err_ptr[0]
           << err_ptr[1]
           << err_ptr[2]
           << err_ptr[3] << "\n";
       ad_exit(1);
       ad_exit(1);
     }
   }
   delete [] field;
   field=0;
 }
}
