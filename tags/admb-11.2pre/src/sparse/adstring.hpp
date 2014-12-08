/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
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
#ifndef __STRING_HPP__
#define __STRING_HPP__

#if defined(__BORLANDC__ )
  #if defined(__GNUC__)
    #if (__GNUC__ < 3)
      #pragma interface
    #endif
  #else
    #pragma interface
  #endif
#endif

#include "clist.h"
#include <string.h>
#include <fvar.hpp>

#include <stdio.h>

#define USE_CONST

class adstring_shape
{
  unsigned int sz;
protected :
  friend class adstring;
  adstring_shape(unsigned int n)
  {
    sz = n;
  }
  unsigned int & size()
  {
    return (sz);
  }
};

class adstring_array;

class adstring : public clist
{
  adstring_shape * shape;
#if (defined __ZTC__) || (defined __NDPX__)
  char * s;
#else
  unsigned char * s;
#endif
  void allocate(int sz);
  friend class adstring_array;
public :
  friend ostream & operator<<(ostream & c, const adstring &t);
  friend istream & operator >> (istream & c, adstring & t);

  adstring(const char *t);
  void allocate(const char *t);
  adstring(int lb, int ub);
  adstring(const adstring &v);
  void realloc(const char * t);
  //adstring(const unsigned char v);
  adstring(const char v);
  adstring(void);
  ~adstring();
  unsigned int size(void) const;
  unsigned int buff_size(void);
  unsigned char& operator()(const int i);
  unsigned char& operator[](const int i);
#ifdef USE_CONST
   const unsigned char& operator()(const int i) const;
   const unsigned char& operator[](const int i) const;
#endif

  friend adstring operator+(const adstring &u, const adstring &v);

  friend adstring operator+(const adstring &u, const unsigned char v);

  friend adstring operator+(const adstring &u, const signed char v);

  friend adstring operator+(const adstring &u, const unsigned char *v);

  friend adstring operator+(const adstring &u, const signed char *v);

  friend adstring operator+(const unsigned char *v, const adstring& u);

  friend adstring operator+(const char *v, const adstring &u);

  friend adstring operator+(const unsigned char u, const adstring &v);

  adstring& operator+=(const adstring &u);
  inline adstring& operator+=(const char u)
    { return(*this += adstring(u)); }

  int operator==(const adstring &u);

  inline int operator == (const char* u)
    { return *this == adstring(u); }

  inline int operator!=(const adstring &u);

  adstring operator()(int i, int j);
  #if defined(USE_CONST)
  int operator==(const char* u) const;

  int operator==(const adstring &u) const;
  adstring operator()(int i, int j) const;
  #endif

  adstring& operator=(const adstring &t);
  adstring& operator=(const char t);
   // { return (*this = adstring(t)); }

  operator unsigned char * ();
  operator char * ();
#ifdef USE_CONST
  operator const unsigned char*() const;
  operator const char*() const;
#endif

  // Pascal-like adstring functions

  // returns the starting position of substr
  int pos(const adstring& substr) const;

  // converts a double into a adstring
  friend adstring str(double x, int minwidth, int decplaces);
  friend adstring str(const int x);
  friend void val(const adstring& s, int& v, int& code);
  friend int val(const adstring& s);
};

adstring str(double x, int minwidth=17, int decplaces=-1);
adstring str(const int x);
void val(const adstring& s, int& v, int& code);
int val(const adstring& s);

class cifstream;

class line_adstring : public adstring
{
public:
  line_adstring(void) : adstring() {}
  line_adstring(const adstring& s) : adstring(s) {}
  line_adstring& operator=(const adstring& s);
  line_adstring& operator=(const char *s);
  friend istream & operator >> (istream & c, line_adstring & t);
};

adstring itoa(int n,int d);

void str(const int, adstring&);
adstring chr(int c);
int length(const adstring& t);
int pos(const adstring& substr, const adstring& s);

//adstring operator+(const char u, const char v)
//  { return (adstring(u) + adstring(v) ); }
#if defined(__BORLANDC__)
#  if (__BORLANDC__  <= 0x0520)
     class ifstream;
     class ofstream;
     class cifstream;
#  endif
#endif

#ifndef _VECTOR_SHAPE
  #define _VECTOR_SHAPE
  class vector_shape
  {
    unsigned int ncopies;
    int index_min;
    int index_max;
    void shift(int min);
    friend class dvector;
    friend class dvar_vector;
    friend class ivector;
    friend class lvector;
    friend class ptr_vector;
  public:
    vector_shape(int& lb, int& lu) {index_min=lb;index_max=lu;ncopies=0;}
    const int indexmin(void) const { return index_min; }
    const int indexmax(void) const { return index_max; }
  };
#endif


class adstring_array : public clist
{
  vector_shape * shape;
  adstring ** ptr;
public:
  int size() const { return shape->indexmax()-shape->indexmin() + 1; }
  const int indexmin(void) const { return shape->indexmin(); }
  const int indexmax(void) const { return shape->indexmax(); }
  adstring_array(const adstring_array& sa);
  ~adstring_array();
  adstring_array(int min,int max);
  void allocate(int min,int max);
  adstring_array(void);
  #ifdef USE_CONST
  const adstring& operator[](int i) const;
  const adstring& operator()(int i) const;
  #endif
  adstring& operator [] (int i);
  adstring& operator () (int i);
  adstring_array& adstring_array::operator += (const adstring& s);
  adstring_array& adstring_array::append_distinct(const adstring& s);
  friend ifstream& operator >> (ifstream& ifs,adstring_array& sa);
  friend ostream& operator<<(const ostream& ifs, const adstring_array& sa);
  friend cifstream& operator >> (cifstream& ifs,adstring_array& sa);
};   // end class adstring_array

ostream& operator<<(const ostream& ifs, const adstring_array& sa);


int atoi(adstring& s);
#endif //#ifndef __STRING_HPP__
