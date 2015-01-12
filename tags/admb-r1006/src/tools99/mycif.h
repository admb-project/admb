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

#ifdef __BCPLUSPLUS__
  #include <fstream.h>
  #include <strstrea.h>
#endif
#ifdef __ZTC__
  #include <iomanip.hpp>
  #include <fstream.hpp>
  #include <strstrea.hpp>
#endif
#ifdef __NDPX__
  #include <fstream.h>
  #include <sstream.h>
  extern "C" {
  #include <dos.h>
  }
#endif

#if defined(__GNU__) || defined(__GNUDOS__)
  #include <fstream.h>
  #include <strstrea.h>
#endif

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#ifndef FVAR_HPP
  class dvar_vector;
  class dvector;
  class svector;
  class ivector;
  class lvector;
  class dvar_matrix;
  class d3_array;
  class s3_array;
  class dmatrix;
  class smatrix;
  class imatrix;
  class lmatrix;
#endif

#ifndef DOUBLE
  class svector;
  class smatrix;
  class s3_array;
#endif

extern const int FILTER_BUF_SIZE;
extern const int SIGNATURE_LENGTH;

#define HERE cout << "reached line " << __LINE__ << " in " << __FILE__ << endl;

class myifstream : public ifstream , myistream; 

class myistream : public istream, myios;



class cifstream : public myifstream
{
#if defined(__ZTC__) || defined(__GNUDOS__)
  streambuf* bp;
#endif
  char COMMENT_CHAR;
  char comment_line[SIGNATURE_LENGTH+1];
  char signature_line[SIGNATURE_LENGTH+1];
  char file_name[13];
  int  line;
  int  field;
  int  ignore_eof;

  void filter(void);
  void get_field(char * s);
  void report_error(const char* s = NULL);
  void set_eof_bit(void);

public:

  cifstream(const char*, int = ios::nocreate, char cc = '#');
  #ifdef __BCPLUSPLUS__
  cifstream() : myifstream() { ; }
  #endif
  #ifdef __NDPX__
  cifstream() : myifstream() { ; }
  #endif
  #ifdef __ZTC__
  cifstream() : ios(&buffer), myifstream() { ; }
  #endif

  void open(const char*, int = ios::nocreate);

  char* comment() { return comment_line; }
  char* signature();

  cifstream& operator >> (long& i);
  cifstream& operator >> (int& i);
  cifstream& operator >> (double& x);
  cifstream& operator >> (float& x);
  cifstream& operator >> (char* x);
  cifstream& getline(char*, int, char = '\n');

  cifstream& operator>>(dvar_vector& z);
  cifstream& operator>>(dvector& z);
  //cifstream& operator>>(svector& z);
  cifstream& operator>>(lvector& z);
  cifstream& operator>>(ivector& z);

  void set_ignore_eof() {ignore_eof = 0;}
  void set_use_eof() {ignore_eof = 1;}
};

cifstream& operator>>(cifstream& istr, dvar_matrix& z);
cifstream& operator>>(cifstream& istr, d3_array& z);
//cifstream& operator>>(cifstream& istr, s3_array& z);
cifstream& operator>>(cifstream& istr, dmatrix& z);
//cifstream& operator>>(cifstream& istr, smatrix& z);
cifstream& operator>>(cifstream& istr, imatrix& z);
//cifstream& operator>>(cifstream& istr, lmatrix& z);

#endif //#define CIFSTREM_H
