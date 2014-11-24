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
#define __USE_IOSTREAM__

#include "fvar.hpp"

#if defined(__TURBOC__)
  #pragma hdrstop
  #include <iostream.h>
  #include <iomanip.h>
  #include <fstream.h>
  #include <strstrea.h>
#endif

#ifdef __SUN__
  #include <iostream.h>
  #include <iomanip.h>
  #include <fstream.h>
  #include <limits.h>
  #include <strstream.h>
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

#include <string.h>
#include <ctype.h>

#include <sstream>
using std::istringstream;

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

int mystrlen(const char* line);

const int MAX_LINE_LENGTH = 10000;
const int MAX_FIELD_LENGTH = 500;
const int MAX_NUMBER_COLUMNS = 6550;
const int MAX_NUMBER_ROWS = 6550;

int get_non_blank_line(const ifstream& infile,char * & line,
   const int& line_length);

/**
 * Description not yet available.
 * \param
 */
 struct dvec_ptr_ptr
 {
   void ** m;
 };

const int MAXROWS = 5050;

/**
 * Description not yet available.
 * \param
 */
dmatrix::dmatrix(char* s)
{
  #ifdef DIAG
    myheapcheck("Entering dmatrix( char * s)" );
  #endif

#ifdef OPT_LIB
  const int n = (int)strlen(s);
#else
  const size_t len = strlen(s);
  assert(len <= INT_MAX);
  const int n = (int)len;
#endif
  int braces = 0;
  int nrow = 0;
  int ncol = 0;

  ivector columns(1, MAXROWS);
  ivector k1(1, MAXROWS);
  ivector k2(1, MAXROWS);

  for (int k = 0; k < n; k++)
  {
    if (s[k] == '{')
    {
      braces ++;
      if (braces != 1)
      {
        cerr << "Unbalanced braces in dmatrix::dmatrix( char * s)\n";
        cerr << "at character " << k << "\n";
        ad_exit(1);
      }
      ncol = 1;
      k1[nrow+1] = k;
    }
    else if (s[k] == '}')
    {
      braces --;
      if (braces != 0)
      {
        cerr << "Unbalanced braces in dmatrix::dmatrix( char * s)\n";
        cerr << "at character " << k << "\n";
        ad_exit(1);
      }
      k2[nrow+1] = k;
      nrow ++;
      if (nrow > MAXROWS)
      {
        cerr << "Too many rows in dmatrix::dmatrix( char * s)\n";
        ad_exit(1);
      }
      columns[nrow] = ncol;
    }
    else if (s[k] == ',')
    {
      if (braces != 0)
      {
        ncol++;
      }
    }
  }

  if (braces != 0)
  {
    cerr << "Unbalanced braces in dmatrix::dmatrix(char * s)\n";
    cerr << s << "\n";
    ad_exit(1);
  }

  if (nrow > 0)
  {
    ivector ub(1,nrow);
    ivector lb(1,nrow);
    for (int i=1; i<=nrow; i++)
    {
       ub[i] = columns[i];
       lb[i] = 1;
    }
    index_min=1;
    index_max=nrow;
    int rs=rowsize();
    if ( (m = new dvector [rs]) == 0)
    {
      cerr << " Error allocating memory in dmatrix contructor\n";
      ad_exit(21);
    }
    if ( (shape = new mat_shapex(m))== 0)
    {
      cerr << " Error allocating memory in dmatrix contructor\n";
      ad_exit(21);
    }


    #ifdef DIAG
      cerr << "Created a dmatrix with adress "<< farptr_tolong(m)<<"\n";
    #endif

    m -= rowmin();

    //char * t = (char*) new[strlen(s)+1];
    char *t = new char[strlen(s)+1];
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      for (int k = k1[i]; k <= k2[i]; k++)
      {
        t[k-k1[i]] = s[k];
      }
      t[k2[i]-k1[i]+1] = '\0';

      m[i].allocate(t);
    }
    delete[] t;
    t = 0;
  }
  else // no rows implies s is a file name
  {
    char * filename = s;
    ifstream infile(filename);
    if (!infile)
    {
       cerr << "Error opening file " << filename << " in dmatrix constructor "
            << "dmatrix::dmatrix(char * filename)\n";
       ad_exit(1);
    }
    char *line = new char [MAX_LINE_LENGTH+2];
    char *field = new char [MAX_FIELD_LENGTH+1];

    int i=0;
    ivector nc(1,MAX_NUMBER_ROWS);

    //while ( (infile.getline(line,MAX_LINE_LENGTH)).good() )
    while ( get_non_blank_line(infile,line,MAX_LINE_LENGTH) )
    {
      strcat(line," ");
     // increment row counter
      if ( i++ > MAX_NUMBER_ROWS)
      {
        cerr << " MAX_NUMBER_ROWS exceeded in "
                " dmatrix::dmatrix(char * filename)\n";
        ad_exit(21);
      }

      int j=0;              // j counts columns
      istringstream f(line);
      while ( (f >> field).good() )
      {
       //char * err_ptr;
       // increment row counter
       if ( ++j > MAX_NUMBER_COLUMNS)
       {
         cerr << " MAX_NUMBER_COLUMNS exceeded in "
                 " dmatrix::dmatrix(char * filename)\n";
         ad_exit(21);
       }
     }
     // Need to check error status f
     nc[i]=j;
   }
   int nr=i;
   if (nr == 0)
   {
     cerr << "Error in dmatrix constructor There doesn't seem to be any data\n"
      << "in file " << filename
      << " caled in dmatrix::dmatrix(char * filename)\n";
      ad_exit(1);
   }

   infile.clear();
   infile.seekg(0,ios::beg);

   ivector index_up(1,nr);
   ivector index_down(1,nr);
     int One=1;
     int Zero=0;
   index_down.fill_seqadd(One,Zero);

   for (i=1;i<=nr;i++)
   {
     index_up[i]=nc[i];
   }
   index_min=1;
   index_max=nr;

   int rs=rowsize();
   if ( (m = new dvector [rs]) == 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }
   if ( (shape = new mat_shapex(m))== 0)
   {
     cerr << " Error allocating memory in dmatrix contructor\n";
     ad_exit(21);
   }

   #ifdef DIAG
     cerr << "Created a dmatrix with adress "<< farptr_tolong(m)<<"\n";
   #endif

   m -= rowmin();

   for (i=rowmin(); i<=rowmax(); i++)
   {
     m[i].allocate(index_down[i],index_up[i]);
     #ifdef DIAG
       cerr << "Created a dvector with address "<< farptr_tolong(*(m+i))<<"\n";
     #endif
   }
   #ifdef DIAG
     myheapcheck("Leaving dmatrix(nrl,nrh,ncl,nch)" );
   #endif

   i=0;
   while (get_non_blank_line(infile,line,MAX_LINE_LENGTH) )
   {
     strcat(line," ");
     // increment row counter
     i++;

     int j=0;              // j counts columns
     istringstream f(line);
     while ( (f >> field).good() )
     {
       char * err_ptr;
       // increment row counter
       j++;
       elem(i,j)=strtod(field,&err_ptr); // increment column counter

       if (isalpha((unsigned char)err_ptr[0]))
       {
         cerr << "Error decoding field " << filename
                << " in dmatrix::dmatrix(char * filename) " << "\n";
         cerr << "Error occurred in line " << i << " at field " << j << "\n";
         cerr << "Offending characters start with "
                << err_ptr[0]
                << err_ptr[1]
                << err_ptr[2]
         << err_ptr[3] << "\n";
         ad_exit(1);
       }

       if (elem(i,j) == HUGE_VAL ||elem(i,j) == -HUGE_VAL)
       {
         cerr << "Overflow Error decoding field " << filename
                << " in dmatrix::dmatrix(char * filename) " << "\n";
         cerr << "Error occurred in line " << i << " at field " << j << "\n";
         cerr << "Offending characters start with "
              << err_ptr[0]
              << err_ptr[1]
              << err_ptr[2]
              << err_ptr[3] << "\n";
         ad_exit(1);
       }
     }
     // Need to check error status f
   }
   delete[] line;
   line = 0;

   delete[] field;
   field = 0;
  }
}

/**
 * Description not yet available.
 * \param
 */
int get_non_blank_line(
  const ifstream& _infile,
  char* &line,
  const int& line_length)
{
  ifstream& infile = (ifstream&)_infile;

  int peek = infile.peek();
  while (infile.good() && (iscntrl(peek) || isspace(peek)))
  {
    infile.get();
    peek = infile.peek();
  }

  infile.get(line, line_length);

  return infile.good() ? mystrlen(line) : 0;
}

/**
 * Description not yet available.
 * \param
 */
int mystrlen(const char* line)
{
  int ii = 0;
  while(ii < MAX_LINE_LENGTH)
  {
    if (line[ii]=='\0')
    {
      return ii;
    }
    ii++;
  }
  return -1;
}
