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

int get_non_blank_line(const ifstream& infile, char* & line,
   const int& line_length);

/**
 * Description not yet available.
 * \param
 */
 struct dvec_ptr_ptr
 {
   void ** m;
 };

/**
Construct dvector using matrix input from text filename.
Select column from matrix.
*/
dvector::dvector(char* filename, const int& column)
{
  if (column < 1)
  {
    cerr << "Error[" << __FILE__ << ':' << __LINE__
         << "]: column should be positive number.\n";
    ad_exit(1);
  }
  ifstream infile(filename);
  if (!infile)
  {
     cerr << "Error opening file " << filename << " in dmatrix constructor "
      << "dmatrix::dmatrix(char * filename)\n";
      ad_exit(1);
  }
  char* line = new char[MAX_LINE_LENGTH + 2];
  char* field = new char[MAX_FIELD_LENGTH + 1];

  int i = 0;
  ivector nc(1, MAX_NUMBER_ROWS);

  while ( get_non_blank_line(infile,line,MAX_LINE_LENGTH) )
  {
    strcat(line, " ");

    // increment row counter
    if ( i++ > MAX_NUMBER_ROWS)
    {
       cerr << " MAX_NUMBER_ROWS exceeded in "
               " dmatrix::dmatrix(char * filename)\n";
       ad_exit(21);
    }

    int j = 0;              // j counts columns
#ifdef __ZTC__
    while( sscanf(line,"%s",field)) // reads a field from line into field
#else
    size_t index = 0;
    size_t length = strlen(line);
    while (index < length)
#endif
    {
      char c = line[index];
      while (c != ' ' && c != ',')
      {
        ++index;
        c = line[index];
      }
      ++j;
      if (j > MAX_NUMBER_COLUMNS)
      {
        cerr << " MAX_NUMBER_COLUMNS exceeded in "
                " dvector::dvector(char* filename)\n";
        ad_exit(21);
      }
      while (c == ' ' || c == ',')
      {
        ++index;
        if (index >= length) break;

        c = line[index];
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
  int nr = i;
  if (nr == 0)
  {
     cerr << "Error in dvector constructor There doesn't seem to be any data\n"
      << "in file:  " << filename
      << " called in dvector::dvector(char * filename,const const& column)\n";
      ad_exit(1);
  }
  infile.clear();
  infile.seekg(0,ios::beg);

  index_min = 1;
  index_max = nr;

  if ((v = new double[(size_t) size()]) == 0)
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
   cout << "Created a ncopies with address " << _farptr_tolong(&(shape->ncopies))
        <<"\n";
   cout << "Created a dvector with address " << _farptr_tolong(v) <<"\n";
   if (sizeof(int)==sizeof(char*))
   {
#if (defined(__GNUC__) && defined(__i386)) || (defined(_MSC_VER) && defined(_M_IX86))
     if ( (unsigned) v < indexmin() * sizeof(double) )
#else
     if ((intptr_t)v < indexmin() * sizeof(double))
#endif
     {
      //cerr << "Pointer wrap in dvector(unsigned int ncl, unsigned int nch)\n";
      //cerr << "pointer = "<< (unsigned int) v <<
      //" indexmin() = "<<indexmin()<<"\n";
        void denormalize_ptr(void * ptr, unsigned int byte_offset);
        denormalize_ptr(&v, indexmin() * sizeof(double));
     }
   }
#endif

  v -= indexmin();

  i=0;
  // while ( (infile.getline(line,MAX_LINE_LENGTH)).good() )
  while ( get_non_blank_line(infile,line,MAX_LINE_LENGTH) )
  {
    strcat(line," ");
    // increment row counter
    i++;
    int j=0;              // j counts columns
#ifdef __ZTC__
   while( sscanf(line,"%s",field)) // reads a field from line into field
#else
      size_t index = 0;
      size_t length = strlen(line);
      while (index < length)
#endif
      {
        int field_index = 0;
        char c = line[index];
        while (c != ' ' && c != ',')
        {
          field[field_index] = c;
          ++field_index;

          ++index;
          c = line[index];
        }
        field[field_index] = '\0';
        ++j;
        if (j == column)
        {
          char* err_ptr;
          elem(i)=strtod(field,&err_ptr); // increment column counter

          if (isalpha((unsigned char)err_ptr[0]))
          {
            cerr << "Error decoding field " << filename
                 << " in dvector::dvector(char* filename) " << "\n";
            cerr << "Error occurred in line " << i << " at field " << j << "\n";
            cerr << "Offending characters start with "
                 << err_ptr[0]
                 << err_ptr[1]
                 << err_ptr[2]
                 << err_ptr[3] << "\n";
            ad_exit(1);
          }
          if (elem(j) == HUGE_VAL || elem(j) == -HUGE_VAL)
          {
            cerr << "Overflow Error decoding field " << filename
                 << " in dvector::dvector(char * filename) " << "\n";
            cerr << "Error occurred in line " << i << " at field " << j << "\n";
            cerr << "Offending characters start with "
                 << err_ptr[0]
                 << err_ptr[1]
                 << err_ptr[2]
                 << err_ptr[3] << "\n";
            ad_exit(1);
          }
        }
        if (j > MAX_NUMBER_COLUMNS)
        {
          cerr << " MAX_NUMBER_COLUMNS exceeded in "
                  " dmatrix::dmatrix(char * filename)\n";
          ad_exit(1);
        }
        while (c == ' ' || c == ',')
        {
          ++index;
          if (index >= length) break;

          c = line[index];
        }
      }
  }

  delete [] line;
  line = NULL;

  delete [] field;
  field = NULL;
}
