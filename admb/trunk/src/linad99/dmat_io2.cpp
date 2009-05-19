/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"


#if defined(__TURBOC__) && !defined(__linux__)
  #pragma hdrstop
  #include <iostream.h>
  #include <iomanip.h>
  #include <fstream.h>
  #include <strstrea.h>
  #define __USE_IOSTREAM__
#endif

#ifdef __GNU__
  #define __USE_IOSTREAM__
#endif

#ifdef __SUN__
  #include <iostream.h>
  #include <iomanip.h>
  #include <fstream.h>
  #include <limits.h>
#if !defined(__MSVC32__)
  #include <strstream.h>
#else
  #include <strstrea.h>
#endif
  #define __USE_IOSTREAM__
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
  #define __USE_IOSTREAM__
#endif

#include <string.h>
#include <ctype.h>

int mystrlen(char * line);

const unsigned int MAX_LINE_LENGTH = 10000;
const int MAX_FIELD_LENGTH = 500;
const int MAX_NUMBER_COLUMNS = 6550;
const int MAX_NUMBER_ROWS = 6550;

 int get_non_blank_line(BOR_CONST ifstream& infile,char * & line,
   const unsigned int& line_length);

 struct dvec_ptr_ptr
 {
   void ** m;
 };

#if !defined(HUGE) 
#define HUGE 1.e+100
#endif

const int MAXROWS = 5050;

dmatrix::dmatrix(char * s)
{
  int i;
  #ifdef DIAG
    myheapcheck("Entering dmatrix( char * s)" );
  #endif

  int n = strlen(s);
  int braces = 0;
  int nrow = 0;
  int ncol = 0;

  ivector columns(1, MAXROWS);
  ivector k1(1, MAXROWS);
  ivector k2(1, MAXROWS);

  int k;
  for (k = 0; k < n; k++)
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
    for (i=1; i<=nrow; i++)
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

    k = 0;
    //char * t = (char*) new[strlen(s)+1];
    char * t = new char[strlen(s)+1];
    for (i=rowmin(); i<=rowmax(); i++)
    {
      for (k = k1[i]; k <= k2[i]; k++)
      {
        t[k-k1[i]] = s[k];
      }
      t[k2[i]-k1[i]+1] = '\0';

      m[i].allocate(t);
    }
    delete t;
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
    char * line=new char [MAX_LINE_LENGTH+2];
    char * field=new char [MAX_FIELD_LENGTH+1];

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
      istrstream f(line);
      while ( (f >> field).good() )
      {
       char * err_ptr;
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
      << "in file " << filename << " caled in dmatrix::dmatrix(char * filename)\n";
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
     istrstream f(line);
     while ( (f >> field).good() )
     {
       char * err_ptr;
       // increment row counter
       j++;
       elem(i,j)=strtod(field,&err_ptr); // increment column counter

       if (isalpha(err_ptr[0]))
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
       
       #ifdef __GNU__
          if (elem(i,j)== HUGE ||elem(i,j)== -HUGE)
       #else
         if (elem(i,j)== HUGE_VAL ||elem(i,j)== -HUGE_VAL)
       #endif
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
   delete line;
   delete field;
  }
}


   int get_non_blank_line(BOR_CONST ifstream& _infile,char * & line,
     const unsigned int& line_length)
   {
     ifstream& infile=(ifstream&) _infile;
     char ch;
     int tmp;
     while ( (tmp=(infile.get(line,line_length)).good()) !=0)
     {
       //cout << line << endl;
       infile >> ch; // get rid of the terminating character
       if (ch != '\0') infile.putback(ch); // If character is not null 
                                           // put if back
       int length=mystrlen(line);
       if (length == -1)
       {
         cerr << "Error computing input line length field reading file\n";
         ad_exit(1);
       }

       for (int i=0;i<length;i++)
       {
         if (line[i] != ' ')
         {
           return tmp;
         }
       }
     }
     return tmp;
   }


   int mystrlen(char * line)
   {
     long int ii=0;
     while(ii<1000000L)
     {
       if (line[ii]=='\0') return(ii);
       ii++;
     }
     return(-1);
   }



