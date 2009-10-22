/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"


#if defined(__TURBOC__) && !defined(__linux__)
   #include <iostream.h>
   #include <strstrea.h>
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

 int get_non_blank_line(BOR_CONST ifstream& infile,char * & line,
   const unsigned int& line_length);

 struct dvec_ptr_ptr
 {
   void ** m;
 };

 dvector::dvector(char * filename, const int& column)
 {
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

     #ifndef __ZTC__
       istrstream f(line);
       while ( (f >> field).good() )
     #else
       while( sscanf(line,"%s",field)) // reads a field from line into field
     #endif
     {
       // f >> field;      // Need to derive a class so that this thing stops at
                           // , or maybe deals with strings
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
     if (j < column)
     {
       cerr << "Error -- not enough columns in line " << i  
        << "\n in dvector::dvector(char * filename, const int& column) "
           " in file:  "
        << filename << "\n";
       ad_exit(1);
     }
   }
   int nr=i;
   if (nr == 0)
   {
     cerr << "Error in dvector constructor There doesn't seem to be any data\n"
      << "in file:  " << filename << " called in dvector::dvector(char * filename,BOR_CONST const& column)\n";
      ad_exit(1);
   }
   infile.clear();
   infile.seekg(0,ios::beg);

   if ( (v = new double [(size_t) size()]) ==0)
   {
     cerr << " Error trying to allocate memory for dvector\n";
     ad_exit(21);
   }
#if defined(THREAD_SAFE)
   if ( (shape=new ts_vector_shapex(1,nr,v)) == NULL)
#else
   if ( (shape=new vector_shapex(1,nr,v)) == NULL)
#endif
   {
     cerr << "Error trying to allocate memory for dvector\n";
     ad_exit(21);
   }

   #ifdef DIAG
     cout << "Created a ncopies with address " << _farptr_tolong(ncopies) <<"\n";
     cout << "Created a dvector with address " << _farptr_tolong(v) <<"\n";
   #endif

   if (sizeof(int)==sizeof(char*))
   {
     if ( (unsigned) v < indexmin() * sizeof(double) )
     {
        //cerr << "Pointer wrap in dvector(unsigned int ncl, unsigned int nch)\n";
        //cerr << "pointer = "<< (unsigned int) v <<
                         //" indexmin() = "<<indexmin()<<"\n";
        denormalize_ptr(&v, indexmin() * sizeof(double));
     }
   }  

   v -= indexmin();


 i=0;
 // while ( (infile.getline(line,MAX_LINE_LENGTH)).good() )
 while ( get_non_blank_line(infile,line,MAX_LINE_LENGTH) )
 {
   strcat(line," ");
   // increment row counter
   i++;
   int j=0;              // j counts columns
   #ifndef __ZTC__
     istrstream f(line);
     while ( (f >> field).good() )
   #else
     while( sscanf(line,"%s",field)) // reads a field from line into field
   #endif
   {
     // f >> field;      // Need to derive a class so that this thing stops at
           // , or maybe deals with strings
     char * err_ptr;
     // increment row counter
     j++;

     if (j==column)
     {
       elem(i)=strtod(field,&err_ptr); // increment column counter

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
       if (elem(i)== HUGE ||elem(i)== -HUGE)
     #else
       if (elem(i)== HUGE_VAL ||elem(i)== -HUGE_VAL)
     #endif
       {
         cerr << "Overflow Error decoding field " << filename
                << " in dvector::dvector(char * filename) " << "\n";
         cerr << "Error occurred in line " << i << " at field " << j << "\n";
         ad_exit(1);
       }
     }
   }
   // Need to check error status f
 }

 delete line;
 delete field;

}
