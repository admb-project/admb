/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 * 
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "BSD" license.
 * 
 * License:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2.  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * 3.  Neither the name of the  University of California, Otter Research,
 * nor the ADMB Foundation nor the names of its contributors may be used
 * to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef CIFSTREM_H
  #define CIFSTREM_H
#  include <fvar.hpp>

#if defined(__GNUDOS__)
  #if defined(__GNUC__)
    #if (__GNUC__ < 3)
      #pragma interface
    #endif
  #else
    #pragma interface
  #endif
#endif

#if defined(linux) || defined(__GNUDOS__)
#define USE_LONG_LONG
#endif


#include <stdio.h>


#if defined (__WAT32__)
  #include <iostream.h>
  #include <strstrea.h>
#endif

#if  defined( __BCPLUSPLUS__) && !defined(__linux__)
  #include <strstrea.h>
#endif

#ifdef __ZTC__
  #include <iomanip.hpp>
  #include <strstrea.hpp>
#endif
#ifdef __NDPX__
  #include <sstream.h>
  extern "C" {
  #include <dos.h>
  }
#endif

#if defined(__GNU__) || defined(__GNUDOS__)
#if !defined(linux) && !defined(__CYGWIN32__) && !defined(__MINGW32__)
  #include <strstrea.h>
#else
#  if (__GNUC__  >= 3) 
#    include <sstream>
#  else
#    include <strstream.h>
#  endif
#endif
#endif

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <adstring.hpp>

#ifndef FVAR_HPP
  class dvar_vector;
  class dvector;
  class svector;
  class ivector;
  class lvector;
  class dvar_matrix;
  class d3_array;
  class d4_array;
  class dvar3_array;
  class dvar4_array;
  class s3_array;
  class dmatrix;
  class smatrix;
  class imatrix;
  class lmatrix;
  class prevariable;
  class dvariable;
#endif

#ifndef DOUBLE
  class svector;
  class smatrix;
  class s3_array;
#endif


#define FILTER_BUF_SIZE 8000
#define SIGNATURE_LENGTH  80

//#define HERE cout << "reached line " << __LINE__ << " in " << __FILE__ << endl;
class cifstream : public ifstream
{
#if defined(__ZTC__) || defined(__GNUDOS__) || defined (__WAT32__)
  streambuf* bp;
#endif
#if defined(__BORLANDC__)
#  if (__BORLANDC__  >= 0x0520) 
  streambuf* bp;
#  endif
#endif

#if ( defined(__MSVC32__) && __MSVC32__ >=7 )
  streambuf* bp;
#endif
  char COMMENT_CHAR;
  char comment_line[SIGNATURE_LENGTH+1];
  char signature_line[SIGNATURE_LENGTH+1];
  adstring file_name;
  int  line;
  int  field;
  int  ignore_eof;

  void filter(void);
  void get_field(char * s,int space_flag=0);
  void report_error(const char* s = NULL);
  void set_eof_bit(void);

public:
  adstring get_file_name(void);
  ~cifstream(){/*cout << "In cifstream destructor" << endl;*/}
#if defined(__BORLANDC__)
#  if (__BORLANDC__  > 0x0520) 
      cifstream(const char*, int=0 , char cc = '#');
#  else
      cifstream(const char*, int = ios::nocreate, char cc = '#');
#  endif
#else
#  if defined(__GNUC__) 
#    if (__GNUC__  >= 3) 
       cifstream(const char*, int = std::ios_base::in , char cc = '#');
#    else
       cifstream(const char*, int = ios::nocreate, char cc = '#');
#    endif
#  elif ( defined(__MSVC32__) && __MSVC32__ >=7)
       cifstream(const char*, int = std::ios_base::in , char cc = '#');
#  else  
     cifstream(const char*, int = ios::nocreate, char cc = '#');
#  endif
#endif
  #ifdef __BCPLUSPLUS__
  cifstream() : ifstream() { ; }
  #endif
  #ifdef __NDPX__
  cifstream() : ifstream() { ; }
  #endif
  #ifdef __ZTC__
  cifstream() : ios(&buffer), ifstream() { ; }
  #endif

#if defined(__BORLANDC__)
#  if (__BORLANDC__  > 0x0520) 
  void open(const char*, int );
#  else
    void open(const char*, int = ios::nocreate);
#  endif
#else // not BORLAND
#  if defined(__GNUC__) 
#    if (__GNUC__  >= 3) 
       void open(const char*, int);
#    else
       void open(const char*, int = ios::nocreate);
#    endif
#  elif ( defined(__MSVC32__) && __MSVC32__ >=7)
       void open(const char*, int);
#  else  
     void open(const char*, int = ios::nocreate);
#  endif
#endif


#include <stdio.h>






  char* comment() { return comment_line; }
  char* signature();

  cifstream& operator>>(BOR_CONST dvariable& z);
 //  cifstream& operator>>(BOR_CONST prevariable& z);
#if defined(USE_LONG_LONG)
  cifstream& operator >> (long long& i);
#endif
  cifstream& operator >> (BOR_CONST long& i);
  cifstream& operator >> (BOR_CONST int& i);
  cifstream& operator >> (BOR_CONST double& x);
  cifstream& operator >> (BOR_CONST float& x);
  cifstream& operator >> (char* x);
  cifstream& operator >> (const char* x);
  cifstream& operator >> (const adstring& x);
  cifstream& operator >> (adstring& x);
  cifstream& operator >> (const line_adstring& x);
  cifstream& getline(char*, int, char = '\n');

  cifstream& operator>>(BOR_CONST dvar_vector& z);
  cifstream& operator>>(BOR_CONST dvector& z);
  //cifstream& operator>>(svector& z);
  cifstream& operator>>(BOR_CONST lvector& z);
  cifstream& operator>>(BOR_CONST ivector& z);

  void set_ignore_eof() {ignore_eof = 0;}
  void set_use_eof() {ignore_eof = 1;}
};

cifstream& operator>>(cifstream& istr,BOR_CONST  prevariable& z);
cifstream& operator>>(cifstream& istr,BOR_CONST  dvar_matrix& z);
cifstream& operator>>(cifstream& istr,BOR_CONST  d3_array& z);
cifstream& operator>>(cifstream& istr,BOR_CONST  d4_array& z);
cifstream& operator>>(cifstream& istr,BOR_CONST  d5_array& z);
cifstream& operator>>(cifstream& istr,BOR_CONST  dvar3_array& z);
cifstream& operator>>(cifstream& istr,BOR_CONST  dvar4_array& z);
cifstream& operator>>(cifstream& istr,BOR_CONST  dvar5_array& z);
//cifstream& operator>>(cifstream& istr, s3_array& z);
cifstream& operator>>(cifstream& istr,BOR_CONST  dmatrix& z);
//cifstream& operator>>(cifstream& istr,smatrix& z);
cifstream& operator>>(cifstream& istr,BOR_CONST  imatrix& z);
cifstream& operator>>(cifstream& istr,BOR_CONST  i3_array& z);
cifstream& operator>>(cifstream& istr,BOR_CONST  i4_array& z);
//cifstream& operator>>(cifstream& istr, lmatrix& z);

#endif //#define CIFSTREM_H
