/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include "fvar.hpp"
#include <math.h>

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
  #define __USE_IOSTREAM__
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

#include <cassert>

const unsigned int MAX_FIELD_LENGTH = 500;

/**
Construct dvector from s.  s is either a filename or a ascii text vector of
doubles with format "{ d[1], ..., d[n]}" where d are doubles with range 1 to n.

\param s file input or ascii text
*/
dvector::dvector(const char* s)
{
  const size_t n = strlen(s);
  int lbraces = 0;
  int rbraces = 0;
  int commas  = 0;

  char* t = new char[n+1];
  assert(t);
  t[n] = '\0';

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

    char *field =  new char[MAX_FIELD_LENGTH + 1];
    char *err_ptr;

    for (int i=ncl;i<=nch;i++)
    {
      ss >> field;
      v[i]=strtod(field,&err_ptr); // increment column counter

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
        cerr << "Overflow Error decoding field in dvector::dvector(char* )"
             << "\n";
        cerr << "Error occurred at element " << i << "\n";
        cerr << "Offending characters start with "
             << field << endl;
        ad_exit(1);
      }
    }
    delete [] field;
    field=0;
  }
  else // if lbraces == 0
  {
    const char * filename=s;
    ifstream infile(filename);
    if (!infile)
    {
      cerr << "Error opening file " << filename << " in dvector constructor "
           << "dvector::dvector(char* filename)\n";
      ad_exit(1);
    }
    char* field = new char[MAX_FIELD_LENGTH + 1];
    int count = 0;
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
          cerr << "Error reading file " << filename
               << " in dvector constructor "
               << "dvector::dvector(char * filename)\n";
          cerr << "Error appears to have occurred at element"
               << count+1 << endl;
          cerr << "Stream state is " << infile.rdstate() << endl;
          ad_exit(1);
        }
      }
    } while (!infile.eof());
    infile.clear();
    infile.seekg(0,ios::beg);

    if ((v = new double[static_cast<unsigned int>(count + 2)]) ==0)
    {
      cerr << " Error trying to allocate memory for dvector\n";
      ad_exit(21);
    }
 #if defined(THREAD_SAFE)
    if ((shape = new ts_vector_shapex(1, count, v)) == NULL)
 #else
    if ((shape = new vector_shapex(1, count, v)) == NULL)
 #endif
    {
      cerr << "Error trying to allocate memory for dvector\n";
      ad_exit(1);
    }
    index_min = 1;
    index_max = count;
    v -= indexmin();

#ifdef DIAG
    cout << "Created ncopies with address " << _farptr_tolong(ncopies) <<"\n";
    cout << "Created dvector with address " << _farptr_tolong(v) <<"\n";
#endif
    char* err_ptr;
    for (int i = 1; i <= count; ++i)
    {
      infile >> field;
      elem(i) = strtod(field,&err_ptr); // increment column counter

      if (isalpha((unsigned char)err_ptr[0]))
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
      if (elem(i) == HUGE_VAL || elem(i) == -HUGE_VAL)
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
  delete [] t;
  t = 0;
}
/**
Allocate dvector from s.  s is either a filename or a ascii text vector of
doubles with format "{ d[1], ..., d[n]}" where d are doubles with range 1 to n.

\param s file input or ascii text
*/
void dvector::allocate(const char* s)
{
  const size_t n = strlen(s);
  int lbraces = 0;
  int rbraces = 0;
  int commas  = 0;

  char* t = new char[n + 1];
  assert(t);
  t[n]= '\0';

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
    cerr << "Unbalanced braces in dvector::dvector(const char* s)\n";
    cerr << s << "\n";
    ad_exit(1);
  }
  if (lbraces > 1)
  {
    cerr << "Only one level of braces allowed in "
    "dvector::dvector(const char* s)\n";
    cerr << s << "\n";
    ad_exit(1);
  }
  if (lbraces == 1)
  {
    int ncl = 1;
    int nch = commas + 1;

    allocate(ncl,nch);

    istringstream ss(t);

    char* field =  new char[size_t(MAX_FIELD_LENGTH+1)];
    char* err_ptr;

    for (int i=ncl;i<=nch;i++)
    {
      ss >> field;
      v[i] = strtod(field,&err_ptr); // increment column counter

      if (isalpha((unsigned char)err_ptr[0]))
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

      if (elem(i) == HUGE_VAL ||elem(i) == -HUGE_VAL)
      {
       cerr << "Overflow Error decoding field "
           " in dvector::dvector(char * ) " << "\n";
       cerr << "Error occurred at element " << i << "\n";
       ad_exit(1);
      }
    }
    delete [] field;
    field = 0;
  }
  else // if lbraces == 0
  {
    const char* filename = s;
    ifstream infile(filename);
    if (!infile)
    {
     cerr << "Error opening file " << filename << " in dvector constructor "
      << "dvector::dvector(char * filename)\n";
      ad_exit(1);
    }

    char* field = new char[MAX_FIELD_LENGTH + 1];

    int count = 0;
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
          cerr << "Error reading file " << filename
               << " in dvector::allocate(char* filename)\n";
          cerr << "Error appears to have occurred at element"
               << count + 1 << endl;
          cerr << "Stream state is " << infile.rdstate() << endl;
          ad_exit(1);
        }
      }
    } while (!infile.eof());

    infile.clear();
    infile.seekg(0,ios::beg);

    if ((v = new double[size()]) == 0)
    {
      cerr << " Error trying to allocate memory for dvector\n";
      ad_exit(21);
    }
#if defined(THREAD_SAFE)
    if ((shape = new ts_vector_shapex(1, count, v)) == NULL)
#else
    if ((shape = new vector_shapex(1, count, v)) == NULL)
#endif
    {
      cerr << "Error trying to allocate memory for dvector\n";
      ad_exit(21);
    }

#ifdef DIAG
    cout << "Created ncopies with address " << _farptr_tolong(ncopies) << "\n";
    cout << "Created dvector with address " << _farptr_tolong(v) << "\n";
#endif
    v -= indexmin();
    char* err_ptr;
    for (int i = 1; i <= count; ++i)
    {
      infile >> field;
      elem(i) = strtod(field, &err_ptr); // increment column counter

      if (isalpha((unsigned char)err_ptr[0]))
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
      if (elem(i) == HUGE_VAL || elem(i) == -HUGE_VAL)
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
    delete [] field;
    field = 0;
  }
  delete [] t;
  t = 0;
}
